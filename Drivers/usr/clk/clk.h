/*
 * clk.h
 *
 *  Created on: Aug 23, 2023
 *      Author: mikita.shary
 */

#ifndef USR_CLK_CLK_H_
#define USR_CLK_CLK_H_

#include "main.h"

#define	RCC_PLL_PLLM 				4U
#define RCC_PLL_PLLN				168U
#define RCC_PLL_PLLQ				4U

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void);

#endif /* USR_CLK_CLK_H_ */
