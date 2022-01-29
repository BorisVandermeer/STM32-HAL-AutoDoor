// MotorDriver.c
// Created By ZBQ
// Created Date 2021_11_04
// Edit Date    2021_11_04

#include "MotorDriver.h"
#include "stm32f1xx_hal.h"

#define USEPWM
#define USEGPIO

int Motor_State = MOTORBRAKED;
 
void MOTOR_INIT_IO(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = MOTOR_EN_PIN | MOTOR_PH_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(MOTOR_EN_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(MOTOR_EN_PORT,MOTOR_EN_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_PH_PORT,MOTOR_PH_PIN,GPIO_PIN_RESET);
	Motor_State = MOTORBRAKED;
}

void SET_MOTOR_PUSH_IO(void)  //设为推出状态
{
		HAL_GPIO_WritePin(MOTOR_PH_PORT,MOTOR_PH_PIN,GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_EN_PORT,MOTOR_EN_PIN,GPIO_PIN_SET);
	  Motor_State = MOTORPUSHING;
}


void SET_MOTOR_PULL_IO(void)  //设为拉回状态
{
		HAL_GPIO_WritePin(MOTOR_PH_PORT,MOTOR_EN_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_EN_PORT,MOTOR_PH_PIN,GPIO_PIN_SET);
		Motor_State = MOTORPULLING;
}

void SET_MOTOR_BRAKE_IO(void) //设为能耗刹车状态
{
		HAL_GPIO_WritePin(MOTOR_EN_PORT,MOTOR_EN_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_PH_PORT,MOTOR_PH_PIN,GPIO_PIN_RESET);
	  Motor_State = MOTORBRAKED;
}

