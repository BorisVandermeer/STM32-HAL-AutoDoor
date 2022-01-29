// GPIO_EXTI.c
// Created By ZBQ
// Created Date 2021_11_02
// Edit Date    2021_11_04
#include "GPIO_EXTI.h"
#include "LED.h"
#include "MotorDriver.h"
#include "CAN.h"


void GPIO_EXTI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

  //两个按键的中断配置
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_15;   //SW2 和 SW3
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	 //四个遥控器口的中断配置
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;   //SW2 和 SW3
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);                 //设置EXIT4的外部中断优先级
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);                           //外部中断使能
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);                 //设置EXIT4的外部中断优先级
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);                 //设置EXIT4的外部中断优先级
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);                 //设置EXIT4的外部中断优先级
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);                 //设置EXIT4的外部中断优先级
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);                 //设置EXIT4的外部中断优先级
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}	//外部中断使能

void EXTI_DELAY(int32_t time)
{
	 int i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--) ;    
   }
}

//中断回调函数-已经定义IRQHandler进不来这个函数了
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	return;
}

//中断处理函数原本位于it.c中
void EXTI15_10_IRQHandler(void)
{
	EXTI_DELAY(10);
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)== 0)
	{
		D3_TOGGLE;
		if(Motor_State == MOTORPULLING)
		{
			MOTOR_PUSH();
		}
		else 
		{
			MOTOR_PULL();
		}
	}
	TxHeader.StdId = COMPUTER_STDID;
	TxData[0] = 0x04;
	TxData[1] = Motor_State;
	SendCanPackage();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
}


void EXTI1_IRQHandler(void)
{
	EXTI_DELAY(10);
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)== 0)
	{
		D3_TOGGLE;
		MOTOR_BRAKE();
	}
	TxData[0] = 0x04;
	TxData[1] = Motor_State;
	SendCanPackage();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
}

void EXTI2_IRQHandler(void)
{
	EXTI_DELAY(10);
	D3_TOGGLE;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)== 1)
	{
		
		MOTOR_PULL();
	}
	TxData[0] = 0x04;
	TxData[1] = Motor_State;
	SendCanPackage();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
}

void EXTI3_IRQHandler(void)
{
	EXTI_DELAY(10);
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)== 1)
	{
		D3_TOGGLE;
		MOTOR_PUSH();
	}
	TxData[0] = 0x04;
	TxData[1] = Motor_State;
	SendCanPackage();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
}

void EXTI4_IRQHandler(void)
{
	EXTI_DELAY(10);
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)== 1)
	{
		D3_TOGGLE;
		MOTOR_BRAKE();
	}
	TxData[0] = 0x04;
	TxData[1] = Motor_State;
	SendCanPackage();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
}

void EXTI9_5_IRQHandler(void)
{
	EXTI_DELAY(10);
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)== 1)
	{
		D3_TOGGLE;
		MOTOR_BRAKE();
	}
	TxData[0] = 0x04;
	TxData[1] = Motor_State;
	SendCanPackage();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
}

