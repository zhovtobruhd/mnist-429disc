/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "app_x-cube-ai.h"
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

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId ledTaskHandle;
osThreadId myTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern uint8_t ai_res;
extern float net[28*28];
AI_ALIGNED(4)
float dws[28*28];
uint8_t dwnscaled[28*28];
void Downscale(uint8_t * res);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartLedTask(void const * argument);
void StartMyTask(void const * argument);

extern void MX_USB_HOST_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
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
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 4096);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of ledTask */
  osThreadDef(ledTask, StartLedTask, osPriorityNormal, 0, 128);
  ledTaskHandle = osThreadCreate(osThread(ledTask), NULL);

  /* definition and creation of myTask */
  osThreadDef(myTask, StartMyTask, osPriorityNormal, 0, 2048);
  myTaskHandle = osThreadCreate(osThread(myTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartLedTask */
/**
* @brief Function implementing the ledTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLedTask */
void StartLedTask(void const * argument)
{
  /* USER CODE BEGIN StartLedTask */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	  if (ai_res) {
		  HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	  }
    osDelay(500);
  }
  /* USER CODE END StartLedTask */
}

/* USER CODE BEGIN Header_StartMyTask */
/**
* @brief Function implementing the myTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMyTask */
void StartMyTask(void const * argument)
{
  /* USER CODE BEGIN StartMyTask */
	static TS_StateTypeDef  ts_state;
	static uint16_t radius = 9;
	uint8_t clear = 1;
  /* Infinite loop */
  for(;;)
  {
	  BSP_TS_GetState(&ts_state);
	  osDelay(4);
	  if (ts_state.TouchDetected == 1) {
		if ((ts_state.X > (21 + radius)) && ((ts_state.X + radius) < 217) && (ts_state.Y > (7 + radius)) && ((ts_state.Y + radius) < 203)) {
			//BSP_LCD_SetTextColor(0xFFBFBFBF);
			//BSP_LCD_FillCircle(ts_state.X, ts_state.Y, radius);
			BSP_LCD_SetTextColor(0xFFAFAFAF);
			BSP_LCD_FillCircle(ts_state.X, ts_state.Y, radius);
			clear = 0;
		}
		if ((ts_state.Y > 219) && (!clear)) {
			Downscale(dwnscaled);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_FillRect(105, 219, 28, 28);
			BSP_LCD_FillRect(109, 270, 20, 20);
			for(uint16_t i = 0; i < 28; ++i) {
				for (uint16_t j = 0; j< 28; ++j) {
					uint32_t pxl = dwnscaled[i*28+j];
					BSP_LCD_DrawPixel(105+i, 219+j, (uint32_t)((0xFF000000) | (pxl) | (pxl << 8) | (pxl << 16)));
				}

			}
			BSP_LCD_FillRect(X_RECT, Y_RECT, W_RECT, H_RECT);
			MX_X_CUBE_AI_Process();
			if (ai_res != 255) {
				BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
				BSP_LCD_SetFont(&Font20);
				BSP_LCD_DisplayChar(109, 270, 48 + ai_res);
			}
			clear = 1;
			osDelay(50);
		}
		osDelay(1);
	  }
  }
  /* USER CODE END StartMyTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void Downscale(uint8_t * res) {
	uint32_t pixel;
	uint32_t avg;
	for (uint16_t i = 0; i < 28; ++i) {
		for (uint16_t j = 0; j < 28; ++j) {
			avg = 0.0;
			for (uint16_t ik = 0; ik < 7; ++ik) {
				for (uint16_t jk = 0; jk < 7; ++jk) {
					pixel = BSP_LCD_ReadPixel(X_RECT + i * 7 + ik, Y_RECT + j * 7 + jk);
					avg += (pixel & 0xFF);
					//avg += (((pixel >> 0) & 0xFF) + ((pixel >> 8) & 0xFF) + ((pixel >> 16) & 0xFF)) / 3;
				}
			}
			net[j*28+i] = (float)(avg) / 49.0;
			//dws[i*28+j] = avg / 49.0;
			//dws[i*28+j] = dws[i*28+j] > 128.0 ? 255.0 : 0.0;
			res[i*28+j] = ((avg / 49UL) & 0xFF);
		}
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
