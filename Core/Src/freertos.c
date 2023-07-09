/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "gpio.h"
#include "spi.h"
#include "adc.h"
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADCSHIFTUP 3000
#define ADCSHIFTDOWN 1700
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint32_t TxMailbox;
extern uint16_t rpm;
extern CAN_TxHeaderTypeDef TxHeader;
extern uint16_t egt3;
extern uint16_t egt4;
extern uint8_t gpsData[UARTBUFFERLENGTH];
extern uint8_t neutralSwitch;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TouchGFXTask */
osThreadId_t TouchGFXTaskHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .stack_size = 8192 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for rpmTask */
osThreadId_t rpmTaskHandle;
const osThreadAttr_t rpmTask_attributes = {
  .name = "rpmTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for egtTask */
osThreadId_t egtTaskHandle;
const osThreadAttr_t egtTask_attributes = {
  .name = "egtTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for shifterTask */
osThreadId_t shifterTaskHandle;
const osThreadAttr_t shifterTask_attributes = {
  .name = "shifterTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for gpsTask */
osThreadId_t gpsTaskHandle;
const osThreadAttr_t gpsTask_attributes = {
  .name = "gpsTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for debounceTask */
osThreadId_t debounceTaskHandle;
const osThreadAttr_t debounceTask_attributes = {
  .name = "debounceTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for buttonQueue */
osMessageQueueId_t buttonQueueHandle;
const osMessageQueueAttr_t buttonQueue_attributes = {
  .name = "buttonQueue"
};
/* Definitions for shifterQueue */
osMessageQueueId_t shifterQueueHandle;
const osMessageQueueAttr_t shifterQueue_attributes = {
  .name = "shifterQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern portBASE_TYPE IdleTaskHook(void* p);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void TouchGFX_Task(void *argument);
void StartRPMTask(void *argument);
void StartEGTTask(void *argument);
void StartShifterTask(void *argument);
void StartGPSTask(void *argument);
void StartDebounce(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
   vTaskSetApplicationTaskTag(NULL, IdleTaskHook);
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of buttonQueue */
  buttonQueueHandle = osMessageQueueNew (4, sizeof(uint8_t), &buttonQueue_attributes);

  /* creation of shifterQueue */
  shifterQueueHandle = osMessageQueueNew (8, sizeof(uint8_t), &shifterQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TouchGFXTask */
  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

  /* creation of rpmTask */
  rpmTaskHandle = osThreadNew(StartRPMTask, NULL, &rpmTask_attributes);

  /* creation of egtTask */
  egtTaskHandle = osThreadNew(StartEGTTask, NULL, &egtTask_attributes);

  /* creation of shifterTask */
  shifterTaskHandle = osThreadNew(StartShifterTask, NULL, &shifterTask_attributes);

  /* creation of gpsTask */
  gpsTaskHandle = osThreadNew(StartGPSTask, NULL, &gpsTask_attributes);

  /* creation of debounceTask */
  debounceTaskHandle = osThreadNew(StartDebounce, NULL, &debounceTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	for(;;){
//		SendDriverScreenData();
		osDelay(100);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartRPMTask */
/**
* @brief Function implementing the rpmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRPMTask */
void StartRPMTask(void *argument)
{
  /* USER CODE BEGIN StartRPMTask */

  /* Infinite loop */
	for(;;){
		if(neutralSwitch){
			SetRPMNeutral();
		}else{
			SetRPMLights(rpm);
		}
		osDelay(100);
	}
  /* USER CODE END StartRPMTask */
}

/* USER CODE BEGIN Header_StartEGTTask */
/**
* @brief Function implementing the egtTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartEGTTask */
void StartEGTTask(void *argument)
{
  /* USER CODE BEGIN StartEGTTask */

	uint8_t data[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  /* Infinite loop */
	for(;;){
		egt3 = ReadTemp(egt1Pin);
		egt4 = ReadTemp(egt2Pin);
		data[0] = egt3 >> 8;
		data[1] = (uint8_t)egt3;
		data[2] = egt4 >> 8;
		data[3] = (uint8_t)egt4;
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, data, &TxMailbox);
		osDelay(500);
	}
  /* USER CODE END StartEGTTask */
}

/* USER CODE BEGIN Header_StartShifterTask */
/**
* @brief Function implementing the shifterTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartShifterTask */
void StartShifterTask(void *argument)
{
  /* USER CODE BEGIN StartShifterTask */
	uint16_t rawADCData = 0;
	uint8_t adcGear = 0;
	uint8_t shiftPosition = 0;
  /* Infinite loop */
	for(;;){
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 200);
		rawADCData = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
		if(rawADCData > ADCSHIFTUP){
			if(shiftPosition != 1 && adcGear != 6){
				shiftPosition = 1;
				adcGear ++;
				osMessageQueuePut(shifterQueueHandle, &adcGear, 0, 0);
			}
		}else if(rawADCData < ADCSHIFTDOWN){
			if(shiftPosition != 1 && adcGear != 0){
				shiftPosition = 1;
				adcGear --;
				osMessageQueuePut(shifterQueueHandle, &adcGear, 0, 0);
			}
		}else{
			shiftPosition = 0;
		}
		osDelay(100);
	}
  /* USER CODE END StartShifterTask */
}

/* USER CODE BEGIN Header_StartGPSTask */
/**
* @brief Function implementing the gpsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGPSTask */
void StartGPSTask(void *argument)
{
  /* USER CODE BEGIN StartGPSTask */
	char start[] = "log bestpos ontime 0.1\r\n";
	HAL_UART_Transmit (&huart6, start, sizeof (start), 10);
//	HAL_UART_Receive_DMA(&huart6, gpsData, UARTBUFFERLENGTH);
	HAL_UARTEx_ReceiveToIdle_IT(&huart6, gpsData, UARTBUFFERLENGTH);
  /* Infinite loop */
	for(;;){
		// make queue for uart data
		// make function for parsing uart data
		// make function for line intersect function
		osDelay(100);
	}
  /* USER CODE END StartGPSTask */
}

/* USER CODE BEGIN Header_StartDebounce */
/**
* @brief Function implementing the debounceTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDebounce */
void StartDebounce(void *argument)
{
  /* USER CODE BEGIN StartDebounce */
	uint8_t count = 0;
	uint8_t state = 0;
  /* Infinite loop */
	for(;;){
		state = HAL_GPIO_ReadPin(CHANGE_SCREEN_BUTTON_GPIO_Port, CHANGE_SCREEN_BUTTON_Pin);
		if(state == 0){
			count ++;
		}else{
			count = 0;
		}
		if(count == 5){
			osMessageQueuePut(buttonQueueHandle, &state, 0, 0);
		}
		osDelay(5);
  }
  /* USER CODE END StartDebounce */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

