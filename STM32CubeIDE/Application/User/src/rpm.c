/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    rpm.c
 * @brief   This file provides code for the configuration
 *          of the RPM instances.
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <rpm.h>

/* Defines*/
#define PWM_HIGH 140
#define PWM_LOW 70
#define PWM_RESET 40
#define LED_DATA_LENGTH 23
#define MAX_LED 16
#define USE_BRIGHTNESS 0
#define PI 3.14159265
#define REDLINE 13000
#define GREEN_LED 5
#define RED_LED 11
#define BLUE_LED 16

/* Variables */
uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];  // for brightness
uint8_t lightsOn = 0;
uint8_t flash = 0b1;
uint16_t pwmData[(24*MAX_LED) + 50];
uint16_t rpmRanges[16] = {
    5000, 5800,
    6600, 7400,
    8200, 9000,
    9800, 10600,
    11400, 12200,
    13000, 13000,
    13000, 13000,
    13000, 14000
};

// 5 green, 6 red, five blue
// all blues turn on at same time at redline
//



/* Functions */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
}

void SetLED (int ledNum, int red, int green, int blue){
	LED_Data[ledNum][0] = ledNum;
	LED_Data[ledNum][1] = green;
	LED_Data[ledNum][2] = red;
	LED_Data[ledNum][3] = blue;
}

void SetBrightness (int brightness){  // 0-45 brightness and would have to scale based on a factor{
#if USE_BRIGHTNESS
	if (brightness > 45){
        brightness = 45;
    }
	for (int i=0; i < MAX_LED; i++){
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j = 1; j < 4; j++){
			float angle = 90 - brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}
#endif
}

void WS2812Send (void){
	uint32_t index = 0;
	uint32_t color;

	for (int i = 0; i < MAX_LED; i++){
#if USE_BRIGHTNESS
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i = LED_DATA_LENGTH; i >= 0; i--){
			if (color & (1<<i)){
				pwmData[index] = PWM_HIGH;
			}else {
                pwmData[index] = PWM_LOW;
            }
			index++;
		}
	}

	for (int i = 0; i < PWM_RESET; i++){
		pwmData[index] = 0;
		index++;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, index);
}

void SetRPMLights(uint16_t rpm){
	if(rpm > REDLINE){
		BlinkAllLED();
    }
	else{
		for(int i = 0; i < MAX_LED; i++){
			if(rpm > rpmRanges[i]){
				if(i < GREEN_LED){
					SetLED(i, 0, 255, 0);
				}else if(i < RED_LED){
					SetLED(i, 255, 0, 0);
				}else if(i < BLUE_LED){
					SetLED(i, 0, 0, 255);
				}
			}else{
				SetLED(i, 0, 0, 0);
			}
		}
	}
	WS2812Send();
}

void SetRPMNeutral(void){
	for(int i = 0; i < MAX_LED; i++){
		SetLED(i, 255, 255, 0);
	}
	WS2812Send();
}

void BlinkAllLED(void){
	for(int i = 0; i < GREEN_LED; i++){
		SetLED(i, 255*flash, 0, 0);
	}
	for(int i = GREEN_LED; i < RED_LED; i++){
		SetLED(i, 0, 255*flash, 0);
	}
	for(int i = RED_LED; i < BLUE_LED; i++){
		SetLED(i, 0, 0, 255*flash);
	}
	WS2812Send();
	flash = flash^1;
}

