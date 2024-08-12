/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* Definitions for led */
osThreadId_t ledHandle;
const osThreadAttr_t led_attributes = {
    .name = "led",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for chassis */
osThreadId_t chassisHandle;
const osThreadAttr_t chassis_attributes = {
    .name = "chassis",
    .stack_size = 512 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal,
};
/* Definitions for ins */
osThreadId_t insHandle;
const osThreadAttr_t ins_attributes = {
    .name = "ins",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityRealtime,
};
/* Definitions for vin */
osThreadId_t vinHandle;
const osThreadAttr_t vin_attributes = {
    .name = "vin",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityBelowNormal,
};
/* Definitions for pwm */
osThreadId_t pwmHandle;
const osThreadAttr_t pwm_attributes = {
    .name = "pwm",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityBelowNormal,
};
/* Definitions for ins_event */
osEventFlagsId_t ins_eventHandle;
const osEventFlagsAttr_t ins_event_attributes = {
    .name = "ins_event"};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void led_task(void *argument);
extern void chassis_task(void *argument);
extern void ins_task(void *argument);
extern void vin_task(void *argument);
extern void pwm_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
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
  /* creation of led */
  ledHandle = osThreadNew(led_task, NULL, &led_attributes);

  /* creation of chassis */
  chassisHandle = osThreadNew(chassis_task, NULL, &chassis_attributes);

  /* creation of ins */
  insHandle = osThreadNew(ins_task, NULL, &ins_attributes);

  /* creation of vin */
  vinHandle = osThreadNew(vin_task, NULL, &vin_attributes);

  /* creation of pwm */
  pwmHandle = osThreadNew(pwm_task, NULL, &pwm_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of ins_event */
  ins_eventHandle = osEventFlagsNew(&ins_event_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_led_task */
/**
 * @brief  Function implementing the led thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_led_task */
void led_task(void *argument)
{
  /* USER CODE BEGIN led_task */
  /* Infinite loop */
  for (;;)
  {
    LED_G_Toggle();
    osDelay(1000);
  }
  /* USER CODE END led_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
