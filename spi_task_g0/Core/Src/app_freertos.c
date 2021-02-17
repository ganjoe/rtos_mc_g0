/* USER CODE BEGIN Header */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "terminal.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticSemaphore_t osStaticSemaphoreDef_t;
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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTxTask */
osThreadId_t myTxTaskHandle;
uint32_t myTxTaskBuffer[ 128 ];
osStaticThreadDef_t myTxTaskControlBlock;
const osThreadAttr_t myTxTask_attributes = {
  .name = "myTxTask",
  .stack_mem = &myTxTaskBuffer[0],
  .stack_size = sizeof(myTxTaskBuffer),
  .cb_mem = &myTxTaskControlBlock,
  .cb_size = sizeof(myTxTaskControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myRxQueue */
osMessageQueueId_t myRxQueueHandle;
uint8_t myRxQueueBuffer[ 16 * sizeof( uint8_t ) ];
osStaticMessageQDef_t myRxQueueControlBlock;
const osMessageQueueAttr_t myRxQueue_attributes = {
  .name = "myRxQueue",
  .cb_mem = &myRxQueueControlBlock,
  .cb_size = sizeof(myRxQueueControlBlock),
  .mq_mem = &myRxQueueBuffer,
  .mq_size = sizeof(myRxQueueBuffer)
};
/* Definitions for myTxQueue */
osMessageQueueId_t myTxQueueHandle;
uint8_t myTxQueueBuffer[ 64 * sizeof( uint8_t ) ];
osStaticMessageQDef_t myTxQueueControlBlock;
const osMessageQueueAttr_t myTxQueue_attributes = {
  .name = "myTxQueue",
  .cb_mem = &myTxQueueControlBlock,
  .cb_size = sizeof(myTxQueueControlBlock),
  .mq_mem = &myTxQueueBuffer,
  .mq_size = sizeof(myTxQueueBuffer)
};
/* Definitions for myFlagNewString */
osSemaphoreId_t myFlagNewStringHandle;
osStaticSemaphoreDef_t myFlagNewStringHandleControlBlock;
const osSemaphoreAttr_t myFlagNewString_attributes = {
  .name = "myFlagNewString",
  .cb_mem = &myFlagNewStringHandleControlBlock,
  .cb_size = sizeof(myFlagNewStringHandleControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTxTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myFlagNewString */
  myFlagNewStringHandle = osSemaphoreNew(1, 1, &myFlagNewString_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myRxQueue */
  myRxQueueHandle = osMessageQueueNew (16, sizeof(uint8_t), &myRxQueue_attributes);

  /* creation of myTxQueue */
  myTxQueueHandle = osMessageQueueNew (64, sizeof(uint8_t), &myTxQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTxTask */
  myTxTaskHandle = osThreadNew(StartTxTask, NULL, &myTxTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */

	term_qPrintf(myTxQueueHandle, "hallo welt!");
	osDelay(250);
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTxTask */
/**
* @brief Function implementing the myTxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTxTask */
void StartTxTask(void *argument)
{
  /* USER CODE BEGIN StartTxTask */

	    /* Infinite loop */
	    for (;;)

		{
		//term_lol_sendQueue(myTxQueueHandle);
		osStatus val;

		uint8_t lReceivedValue=0;

		val = osMessageQueueGet(myTxQueueHandle, &lReceivedValue, 0, 100);

		switch (val)
		    {
		    case osOK:	HAL_UART_Transmit(&huart2, &lReceivedValue, 1, 199);
		    }

		//xQueueReceive(myTxQueueHandle, &lReceivedValue, 0);

		}

  /* USER CODE END StartTxTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
