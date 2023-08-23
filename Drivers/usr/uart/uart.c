/*
 * uart.c
 *
 *  Created on: Aug 23, 2023
 *      Author: mikita.shary
 */

#include "uart.h"

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* Definitions for uart6_task */
static osThreadId_t uart6_taskHandle;
static const osThreadAttr_t uart6_task_attributes = { .name = "uart6_task",
		.stack_size = UART_TASK_SIZE, .priority =
				(osPriority_t) osPriorityNormal, };
/* Definitions for uart2_task */
static osThreadId_t uart2_taskHandle;
static const osThreadAttr_t uart2_task_attributes = { .name = "uart2_task",
		.stack_size = UART_TASK_SIZE, .priority =
				(osPriority_t) osPriorityNormal, };
/* Definitions for uart2_to_uart6_queue */
static osMessageQueueId_t uart2_to_uart6_queueHandle;
static const osMessageQueueAttr_t uart2_to_uart6_queue_attributes = { .name =
		"uart2_to_uart6_queue" };
/* Definitions for uart6_to_uart2_queue */
static osMessageQueueId_t uart6_to_uart2_queueHandle;
static const osMessageQueueAttr_t uart6_to_uart2_queue_attributes = { .name =
		"uart6_to_uart2_queue" };
/* Definitions for uart2_mutex */
static osMutexId_t uart2_mutexHandle;
static const osMutexAttr_t uart2_mutex_attributes = { .name = "uart2_mutex" };
/* Definitions for uart6_mutex */
static osMutexId_t uart6_mutexHandle;
static const osMutexAttr_t uart6_mutex_attributes = { .name = "uart6_mutex" };

static void uart6_task_func(void *argument);
static void uart2_task_func(void *argument);
static uint8_t tx_data_uart2 = 0;
static uint8_t rx_data_uart2 = 0;
static uint8_t rx_data_uart6 = 0;
static uint8_t tx_data_uart6 = 0;

/**
 * @brief Function implementing the uart6_task thread.
 * @param argument: Not used
 * @retval None
 */
static void uart6_task_func(void *argument) {
	/* Infinite loop */
	for (;;) {
		xQueueReceive(uart2_to_uart6_queueHandle, &tx_data_uart6,
		portMAX_DELAY);
		HAL_UART_Transmit_IT(&huart6, &tx_data_uart6, 1);
		osDelay(1);
	}
}

/**
 * @brief Function implementing the uart2_task thread.
 * @param argument: Not used
 * @retval None
 */
static void uart2_task_func(void *argument) {
	/* Infinite loop */
	for (;;) {
		xQueueReceive(uart6_to_uart2_queueHandle, &tx_data_uart2,
		portMAX_DELAY);
		HAL_UART_Transmit_IT(&huart2, &tx_data_uart2, 1);
		osDelay(1);
	}
}

void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */
	osMutexAcquire(uart2_mutexHandle, portMAX_DELAY);
	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */
	HAL_UART_Receive_IT(&huart2, &rx_data_uart2, 1);
	/* USER CODE END USART2_Init 2 */
	osMutexRelease(uart2_mutexHandle);

}

void MX_USART6_UART_Init(void) {

	/* USER CODE BEGIN USART6_Init 0 */
	osMutexAcquire(uart6_mutexHandle, portMAX_DELAY);
	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	huart6.Init.BaudRate = UART_BAUD_RATE_115200;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART6_Init 2 */
	HAL_UART_Receive_IT(&huart6, &rx_data_uart6, 1);
	osMutexRelease(uart6_mutexHandle);
	/* USER CODE END USART6_Init 2 */

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == huart2.Instance) {
		xQueueSendFromISR(uart2_to_uart6_queueHandle, &rx_data_uart2, pdFALSE);
		HAL_UART_Receive_IT(&huart2, &rx_data_uart2, 1);
	}
	if (huart->Instance == huart6.Instance) {
		xQueueSendFromISR(uart6_to_uart2_queueHandle, &rx_data_uart6, pdFALSE);
		HAL_UART_Receive_IT(&huart6, &rx_data_uart6, 1);
	}
}

uint8_t uart2_task_init() {

	uint8_t res = pdFAIL;

	/* creation of uart2_to_uart6_queue */
	uart2_to_uart6_queueHandle = osMessageQueueNew(16, sizeof(uint8_t),
			&uart2_to_uart6_queue_attributes);

	/* creation of uart2_task */
	uart2_taskHandle = osThreadNew(uart2_task_func, NULL,
			&uart2_task_attributes);

	/* creation of uart2_mutex */
	uart2_mutexHandle = osMutexNew(&uart2_mutex_attributes);

	if (uart2_to_uart6_queueHandle != NULL && uart2_taskHandle != NULL
			&& uart2_mutexHandle != NULL) {
		res = pdPASS;
	}
	return res;

}

uint8_t uart6_task_init(void) {

	uint8_t res = pdFAIL;

	/* creation of uart6_to_uart2_queue */
	uart6_to_uart2_queueHandle = osMessageQueueNew(16, sizeof(uint8_t),
			&uart6_to_uart2_queue_attributes);

	/* creation of uart6_task */
	uart6_taskHandle = osThreadNew(uart6_task_func, NULL,
			&uart6_task_attributes);

	/* creation of uart6_mutex */
	uart6_mutexHandle = osMutexNew(&uart6_mutex_attributes);

	if (uart6_to_uart2_queueHandle != NULL && uart6_taskHandle != NULL
			&& uart6_mutexHandle != NULL) {
		res = pdPASS;
	}
	return res;

}

