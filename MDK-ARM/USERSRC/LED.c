// GPIO_IO.c
// Created By ZBQ
// Created Date 2021_11_03
// Edit Date    2021_11_03

#include "LED.h"

//初始化LED
void LED_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = D3_PIN | D2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(D3_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(D3_PORT,D3_PIN,D3_LED_ENABLE);
}

