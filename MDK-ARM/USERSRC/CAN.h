// CAN.h
// Created By ZBQ
// Created Date 2021_11_02
// Edit Date    2021_11_02

#ifndef _CAN_H_
#define	_CAN_H_

#include "stm32f1xx_hal.h"

#include "main.h"

#define CAN_RX_ID 0x0369
#define COMPUTER_STDID 0x000

extern CAN_HandleTypeDef hcan;
extern CAN_TxHeaderTypeDef   TxHeader;
extern CAN_RxHeaderTypeDef   RxHeader;
extern uint8_t               TxData[8];
extern uint8_t               RxData[8];
extern uint32_t              TxMailbox;

void CAN_Init(void);
//void USER_CAN_Send(void);
void SendCanPackage(void);

#endif 

