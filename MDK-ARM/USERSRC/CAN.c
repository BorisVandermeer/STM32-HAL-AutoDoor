// CAN.c
// Created By ZBQ
// Created Date 2021_11_02
// Edit Date    2021_11_02
#include "CAN.h"
#include "LED.h"
#include "MotorDriver.h"
#include "stdio.h"

CAN_HandleTypeDef hcan; //必须叫hcan，这是个标准库，在stm32f1xx_it.c这个废物里面
 
CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8];
uint8_t               RxData[8];
uint32_t              TxMailbox;

//初始化CAN协议
void CAN_Init(void)
{
	CAN_FilterTypeDef  CANFilterConfig;
	//CAN handler 初始化设置
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 12;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
	//CAN过滤协议
  CANFilterConfig.FilterBank = 0;
  CANFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  CANFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  CANFilterConfig.FilterIdHigh = 0x0000;
  CANFilterConfig.FilterIdLow = 0x0000;
  CANFilterConfig.FilterMaskIdHigh = 0x0000;
  CANFilterConfig.FilterMaskIdLow = 0x0000;
  CANFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  CANFilterConfig.FilterActivation = ENABLE;
  CANFilterConfig.SlaveStartFilterBank = 14;
	//初始化CAN过滤器，出错进入Error_Handler
	if (HAL_CAN_ConfigFilter(&hcan, &CANFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  //开始CAN收发器，出错同上
  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
 
  //CAN输入中断激活
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    Error_Handler();
  }
  //CAN输出邮箱空的中断
  //if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
  //{
  //	Error_Handler();
  //}
	// 对TxHeader 进行一些初始化的设置
  TxHeader.StdId = 0x00;
  TxHeader.ExtId = 0x00;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 2;
  TxHeader.TransmitGlobalTime = DISABLE;	
}

// 接收中断的处理函数 
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *CanHandle)
{
	
	if (HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
    //接收出错了
    Error_Handler();
  }
	//收到了长度为2的标准帧
  if ((RxHeader.StdId == CAN_RX_ID) && (RxHeader.IDE == CAN_ID_STD) && (RxHeader.DLC == 2))
  {
		if(RxData[0] == 0)
		{
			if(RxData[1] == 1) MOTOR_BRAKE();
			if(RxData[1] == 2) MOTOR_PULL();
			if(RxData[1] == 3) MOTOR_PUSH();
		}
		if(RxData[0] == 1)
		{
			TxHeader.DLC = 2;
			TxHeader.StdId = COMPUTER_STDID;
			TxData[0] = 0x01;
			TxData[1] = Motor_State;
			SendCanPackage();
		}
  }
	
	return ;
}

// 发送邮箱为空时的中断处理函数
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
	//static uint8_t num = 0;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcan);
	HAL_CAN_DeactivateNotification(hcan, CAN_IT_TX_MAILBOX_EMPTY);
	HAL_CAN_AddTxMessage(hcan, &TxHeader, TxData, &TxMailbox);
	TxData[1] = TxData[1]+ 1;
}

//发送CAN包
void SendCanPackage()
{
	//HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY);//开启中断
	D3_TURNOFF;
	while(HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
	}
}

void USB_LP_CAN1_RX0_IRQHandler(void)  	
{
  HAL_CAN_IRQHandler(&hcan);
}

