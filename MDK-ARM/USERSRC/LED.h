// Created By ZBQ
// Created Date 2021_11_03
// Edit Date    2021_11_03
#ifndef _LED_H_
#define _LED_H_

#include "stm32f1xx_hal.h"

#define D2_PIN  GPIO_PIN_13
#define D3_PIN  GPIO_PIN_14
#define D2_PORT GPIOB
#define D3_PORT GPIOB
#define D2_LED_ENABLE GPIO_PIN_RESET
#define D3_LED_ENABLE GPIO_PIN_RESET
#define D2_LED_DISABLE GPIO_PIN_SET 
#define D3_LED_DISABLE GPIO_PIN_SET


#define D2_TURNON HAL_GPIO_WritePin(D2_PORT,D2_PIN,D2_LED_ENABLE);
#define D2_TURNOFF HAL_GPIO_WritePin(D2_PORT,D2_PIN,D2_LED_DISABLE);
#define D3_TURNON HAL_GPIO_WritePin(D3_PORT,D3_PIN,D3_LED_ENABLE);
#define D3_TURNOFF HAL_GPIO_WritePin(D3_PORT,D3_PIN,D3_LED_DISABLE);
#define D2_TOGGLE HAL_GPIO_TogglePin(D2_PORT,D2_PIN);
#define D3_TOGGLE HAL_GPIO_TogglePin(D3_PORT,D3_PIN);

void LED_INIT(void);

#endif
