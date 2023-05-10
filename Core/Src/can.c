/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
CAN_FilterTypeDef canfilter;
CAN_RxHeaderTypeDef RxHeader;
CAN_TxHeaderTypeDef TxHeader;
uint8_t RxData[8];
CAN_FilterTypeDef filterConfig;

extern osMessageQueueId_t canQueueHandle;
extern osMessageQueueId_t driverDataQueueHandle;
canData_t *canData_q;
driverScreenData_t *driverScreenData_q;

double ecuAnalogScale = 0.004882813;

uint8_t inputStateDiagnostics;
float inputVoltage;
uint8_t outputState;
uint8_t outputVoltage;
uint8_t outputCurrent;
uint8_t outputLoad;
uint8_t deviceInformation;

uint8_t coolSwitch;
uint8_t neutralSwitch;
//uint8_t maxCoolSwitch;
uint8_t fuelPump;
uint8_t waterPump;
float powerOutputVoltage;
uint8_t powerOutputCurrent;
uint8_t powerOutputLoad;


double accelX;
double accelY;
double accelZ;
double yaw;
double pitch;
double roll;
double flPot;
double frPot;
double rlPot;
double rrPot;
double frontBreak;
double rearBreak;
double gpsLat;
double gpsLong;
double gpsSpeed;


// EMU1 0x600
uint16_t rpm;
float tps;
int8_t iat;
int16_t map;
float injpw;

// EMU2 0x601
double ai1;
double ai2;
double ai3;
double ai4;

// EMU3 0x602
uint16_t vspd;
uint8_t baro;
uint8_t oilTemp;
float oilPressure;
float fuelPressure;
int16_t coolantTemp;

// EMU4 0x603
double ignitionAngle;
double dwell;
double lambda;
double lambcorr;
uint16_t egt1;
uint16_t egt2;

// EMU5 0x604
uint8_t gear;
int8_t ecuTemp;
uint16_t batteryVoltageECU;
uint16_t errFlag;
uint8_t flags1;
uint8_t ethanolContent;

uint16_t egt3;
uint16_t egt4;


int frequency1;
int frequency2;
int frequency3;
int frequency4;

int batteryVoltage;
int airTemp;


/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  	filterConfig.FilterBank = 12;
    filterConfig.FilterActivation = ENABLE;
    filterConfig.FilterFIFOAssignment = 0;
    filterConfig.FilterMaskIdLow = 0x0000;
    filterConfig.FilterMaskIdHigh = 0x0000;
    filterConfig.FilterIdHigh = 0x0000;
    filterConfig.FilterIdLow = 0x0000;
    filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;

    if(HAL_CAN_ConfigFilter(&hcan1, &filterConfig)){
  	  Error_Handler(); //Assign the filter
    }

    TxHeader.StdId = 0x660;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = 4;
  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, &RxData) != HAL_OK){
		Error_Handler();
	}

//	if(osMessageQueueGetSpace(canQueueHandle) > 0){
//		osMessageQueuePut(canQueueHandle, &canData_q, 0, 0);
//	}
	canData_q->canID = RxHeader.StdId;
	memcpy(canData_q->data, RxData, sizeof(RxData));
	ParseCANData(canData_q);
	SendDriverScreenData();
}

void SendDriverScreenData(void){
	if(neutralSwitch){
		driverScreenData_q->gear = gear;
	}else{
		driverScreenData_q->gear = 0;
	}
//	driverScreenData_q->gear = gear;
	driverScreenData_q->rpm = rpm;
	driverScreenData_q->leftDataField1 = oilPressure;
	driverScreenData_q->leftDataField2 = oilTemp;
	driverScreenData_q->leftDataField3 = fuelPressure;
	driverScreenData_q->rightDataField1 = batteryVoltageECU;
	driverScreenData_q->rightDataField2 = coolantTemp;
	driverScreenData_q->rightDataField3 = vspd;
	driverScreenData_q->batteryLow = (batteryVoltageECU < BATTERY_LOW_VOLTAGE);
	driverScreenData_q->coolantHigh = (coolantTemp > COOLANT_HIGH_TEMPERATURE);
}

void ParseCANData(canData_t *canData){
	switch(canData->canID){
		case 0x500:
			inputStateDiagnostics = canData->data[0];
			inputVoltage = canData->data[1] * 0.1216;
			outputState = canData->data[2];
			outputVoltage = canData->data[3];
			outputCurrent = canData->data[4];
			outputLoad = canData->data[5];
			deviceInformation = canData->data[6];
			break;
		case 0x420:
			coolSwitch = canData->data[0];
			neutralSwitch = canData->data[1];
			fuelPump = canData->data[2];
			waterPump = canData->data[3];
			powerOutputVoltage = canData->data[4]  * 0.1216;
			powerOutputCurrent = canData->data[5];
			powerOutputLoad = canData->data[6];
			break;
		case 0x250:
			accelX = canData->data[0];
			break;
		case 0x251:
			accelY = canData->data[0];
			break;
		case 0x252:
			accelZ = canData->data[0];
			break;
		case 0x253:
			yaw = canData->data[0];
			break;
		case 0x254:
			pitch = canData->data[0];
			break;
		case 0x255:
			roll = canData->data[0];
			break;
		case 0x260:
			flPot = canData->data[0];
			break;
		case 0x261:
			frPot = canData->data[0];
			break;
		case 0x262:
			rlPot = canData->data[0];
			break;
		case 0x263:
			rrPot = canData->data[0];
			break;
		case 0x264:
			frontBreak= canData->data[0];
			break;
		case 0x265:
			rearBreak = canData->data[0];
			break;
		case 0x280:
			gpsLat = canData->data[0];
			break;
		case 0x281:
			gpsLong = canData->data[0];
			break;
		case 0x282:
			gpsSpeed = canData->data[0];
			break;
		case 0x600:
			rpm = (uint16_t)CombineUnsigned(canData->data[0], canData->data[1], 1);
			tps = canData->data[2] * 0.5;
			iat = (int8_t)canData->data[3];
			map = (int16_t)CombineSigned(canData->data[4], canData->data[5], 1);
			injpw = CombineUnsigned(canData->data[6], canData->data[7], 0.016129);
//			if(osMessageQueueGetSpace(rpmTaskHandle) > 0){
//				osMessageQueuePut(rpmTaskHandle, &rpm, 0, 0);
//			}
			break;
		case 0x601:
			ai1 = CombineUnsigned(canData->data[0], canData->data[1], ecuAnalogScale);
			ai2 = CombineUnsigned(canData->data[2], canData->data[3], ecuAnalogScale);
			ai3 = CombineUnsigned(canData->data[4], canData->data[5], ecuAnalogScale);
			ai4 = CombineUnsigned(canData->data[6], canData->data[7], ecuAnalogScale);
			break;
		case 0x602:
			vspd = (uint16_t)CombineUnsigned(canData->data[0], canData->data[1], 1);
			baro = canData->data[2];
			oilTemp = canData->data[3];
			oilPressure = canData->data[4] * 0.0625;
			fuelPressure = canData->data[5] * 0.0625;
			coolantTemp = (int16_t)CombineSigned(canData->data[6], canData->data[7], 1);
			break;
		case 0x603:
			ignitionAngle = (int8_t)RxData[0] * 0.5;
			dwell = RxData[1] * 0.05;
			lambda = RxData[2] * 0.0078125;
			lambcorr = RxData[3] * 0.5;
			egt1 = CombineUnsigned(canData->data[4], canData->data[5], 1);
			egt2 = CombineUnsigned(canData->data[6], canData->data[7], 1);
			break;
		case 0x604:
			gear = canData->data[0];
			ecuTemp = (int8_t) canData->data[1];
			batteryVoltageECU = CombineUnsigned(canData->data[2], canData->data[3], 0.027);
			errFlag = CombineUnsigned(canData->data[4], canData->data[5], 1);
			flags1 = canData->data[6];
			ethanolContent = canData->data[7];
			break;
		default:
			break;
	}
}

float CombineUnsigned(uint8_t data1, uint8_t data2, double scale){
	uint16_t combinedData = (data2 << 8) | data1;
	float finalData = combinedData * scale;
	return finalData;
}

float CombineSigned(uint8_t data1, uint8_t data2, double scale){
	int16_t combinedData = (data2 << 8) | data1;
	float finalData = combinedData * scale;
	return finalData;
}
/* USER CODE END 1 */
