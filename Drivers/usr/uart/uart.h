/*
 * uart.h
 *
 *  Created on: Aug 23, 2023
 *      Author: mikita.shary
 */

#ifndef USR_UART_UART_H_
#define USR_UART_UART_H_

#include "main.h"

#define UART_BAUD_RATE_115200				115200U
#define UART_TASK_SIZE						512U

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
void MX_USART2_UART_Init(void);

/**
 * @brief USART6 Initialization Function
 * @param None
 * @retval None
 */
void MX_USART6_UART_Init(void);

/**
 * @brief create uart2 task
 * @param None
 * @retval pdPASS if create successful, else - pfFAIL
 */
uint8_t uart2_task_init(void);

/**
 * @brief create uart2 task
 * @param None
 * @retval pdPASS if create successful, else - pfFAIL
 */
uint8_t uart6_task_init(void);

#endif /* USR_UART_UART_H_ */
