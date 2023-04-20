/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */
#define BATTERY_LOW_VOLTAGE 11.5
#define COOLANT_HIGH_TEMPERATURE 95
typedef struct{
	uint32_t canID;
	uint8_t data[8];
}canData_t;

typedef struct{
	uint8_t gear;
	uint16_t rpm;
	float leftDataField1;
	uint8_t leftDataField2;
	float leftDataField3;
	float rightDataField1;
	int16_t rightDataField2;
	uint16_t rightDataField3;
	bool batteryLow;
	bool coolantHigh;
}driverScreenData_t;
/* USER CODE END Private defines */

void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */
void SendDriverScreenData(void);
void ParseCANData(canData_t *canData);
float CombineUnsigned(uint8_t data1, uint8_t data2, double scale);
float CombineSigned(uint8_t data1, uint8_t data2, double scale);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

