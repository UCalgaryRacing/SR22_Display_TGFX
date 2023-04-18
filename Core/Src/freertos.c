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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint16_t rpm;
extern CAN_TxHeaderTypeDef TxHeader;
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
/* Definitions for buttonTask */
osThreadId_t buttonTaskHandle;
const osThreadAttr_t buttonTask_attributes = {
  .name = "buttonTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for rpmTask */
osThreadId_t rpmTaskHandle;
const osThreadAttr_t rpmTask_attributes = {
  .name = "rpmTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for canTask */
osThreadId_t canTaskHandle;
const osThreadAttr_t canTask_attributes = {
  .name = "canTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for buttonQueue */
osMessageQueueId_t buttonQueueHandle;
const osMessageQueueAttr_t buttonQueue_attributes = {
  .name = "buttonQueue"
};
/* Definitions for rpmQueue */
osMessageQueueId_t rpmQueueHandle;
const osMessageQueueAttr_t rpmQueue_attributes = {
  .name = "rpmQueue"
};
/* Definitions for driverDataQueue */
osMessageQueueId_t driverDataQueueHandle;
const osMessageQueueAttr_t driverDataQueue_attributes = {
  .name = "driverDataQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern portBASE_TYPE IdleTaskHook(void* p);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void TouchGFX_Task(void *argument);
void StartButtonTask(void *argument);
void StartRPMTask(void *argument);
void StartCANTask(void *argument);

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

  /* creation of rpmQueue */
  rpmQueueHandle = osMessageQueueNew (8, sizeof(uint16_t), &rpmQueue_attributes);

  /* creation of driverDataQueue */
  driverDataQueueHandle = osMessageQueueNew (16, sizeof(driverScreenData_t), &driverDataQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TouchGFXTask */
  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

  /* creation of buttonTask */
  buttonTaskHandle = osThreadNew(StartButtonTask, NULL, &buttonTask_attributes);

  /* creation of rpmTask */
  rpmTaskHandle = osThreadNew(StartRPMTask, NULL, &rpmTask_attributes);

  /* creation of canTask */
  canTaskHandle = osThreadNew(StartCANTask, NULL, &canTask_attributes);

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
		SendDriverScreenData();
		osDelay(20);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartButtonTask */
/**
* @brief Function implementing the buttonTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartButtonTask */
void StartButtonTask(void *argument)
{
  /* USER CODE BEGIN StartButtonTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END StartButtonTask */
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
//	uint16_t rpm = 0;
	SetLED(0,255,0,0);		// These LEDS are going to be set to green as they are going to represent idle
	SetLED(1,255,0,0);
	SetLED(2,255,0,0);
	SetLED(3,255,0,0);
	SetLED(4,255,0,0);
	SetLED(5,255,0,0);
	SetLED(6,255,0,0);
	SetLED(7,255,0,0);

  /* Infinite loop */
	for(;;){

		SetRPMLights(rpm);
		osDelay(100);
	}
  /* USER CODE END StartRPMTask */
}

/* USER CODE BEGIN Header_StartCANTask */
/**
* @brief Function implementing the canTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCANTask */
void StartCANTask(void *argument)
{
  /* USER CODE BEGIN StartCANTask */
//	canData_t *canData_r;
//	uint32_t canID = 0x000;
	uint32_t TxMailbox;
	uint8_t data[8] = {10, 10, 10, 10, 10, 10, 10, 10};
  /* Infinite loop */
	for(;;){
//		if(osMessageQueueGetCount(canQueueHandle) > 0){
//			if(osMessageQueueGet(canQueueHandle, &canData_r, 0, 0) == osOK){
//				ParseCANData(canData_r);
//			}
//		}
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, data, &TxMailbox);
		osDelay(500);
  }
  /* USER CODE END StartCANTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

