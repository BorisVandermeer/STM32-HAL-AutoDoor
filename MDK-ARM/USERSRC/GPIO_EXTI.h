// Created By ZBQ
// Created Date 2021_11_02
// Edit Date    2021_11_02

#ifndef _GPIO_EXTI_H_
#define _GPIO_EXTI_H_

#include "stm32f1xx_hal.h"


#define SW2_EXTI_PIN GPIO_PIN_1
#define SW3_EXTI_PIN GPIO_PIN_15

#define SW2_EXTI_GROUP GPIOB
#define SW3_EXTI_GROUP GPIOB

//GPIO中断配置函数
void GPIO_EXTI_Init(void);



#endif

