/*
 * rpm.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Me
 */

#ifndef APPLICATION_USER_RPM_H_
#define APPLICATION_USER_RPM_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ltdc.h"
#include "tim.h"
#include "math.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void SetLED (int ledNum, int red, int green, int blue);
void SetBrightness (int brightness);
void WS2812Send (void);
void SetRPMLights(uint16_t rpm);
void BlinkAllLED(void);
/* USER CODE END Prototypes */



#endif /* APPLICATION_USER_RPM_H_ */
