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
#include "datatypes.h"
#include "string.h"
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
/* Definitions for myRxTask */
osThreadId_t myRxTaskHandle;
uint32_t myRxTaskBuffer[ 128 ];
osStaticThreadDef_t myRxTaskControlBlock;
const osThreadAttr_t myRxTask_attributes = {
  .name = "myRxTask",
  .stack_mem = &myRxTaskBuffer[0],
  .stack_size = sizeof(myRxTaskBuffer),
  .cb_mem = &myRxTaskControlBlock,
  .cb_size = sizeof(myRxTaskControlBlock),
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
/* Definitions for myCmdLineObjQueue */
osMessageQueueId_t myCmdLineObjQueueHandle;
uint8_t myCmdLineObjQueueBuffer[ 1 * 64 ];
osStaticMessageQDef_t myCmdLineObjQueueBlock;
const osMessageQueueAttr_t myCmdLineObjQueue_attributes = {
  .name = "myCmdLineObjQueue",
  .cb_mem = &myCmdLineObjQueueBlock,
  .cb_size = sizeof(myCmdLineObjQueueBlock),
  .mq_mem = &myCmdLineObjQueueBuffer,
  .mq_size = sizeof(myCmdLineObjQueueBuffer)
};
/* Definitions for myFlagNewString */
osSemaphoreId_t myFlagNewStringHandle;
osStaticSemaphoreDef_t myFlagNewStringHandleControlBlock;
const osSemaphoreAttr_t myFlagNewString_attributes = {
  .name = "myFlagNewString",
  .cb_mem = &myFlagNewStringHandleControlBlock,
  .cb_size = sizeof(myFlagNewStringHandleControlBlock),
};
/* Definitions for myCountNewCmd */
osSemaphoreId_t myCountNewCmdHandle;
osStaticSemaphoreDef_t myCountNewCmdControlBlock;
const osSemaphoreAttr_t myCountNewCmd_attributes = {
  .name = "myCountNewCmd",
  .cb_mem = &myCountNewCmdControlBlock,
  .cb_size = sizeof(myCountNewCmdControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTxTask(void *argument);
void StartRxTask(void *argument);

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

  /* creation of myCountNewCmd */
  myCountNewCmdHandle = osSemaphoreNew(8, 8, &myCountNewCmd_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myRxQueue */
  myRxQueueHandle = osMessageQueueNew (16, sizeof(uint8_t), &myRxQueue_attributes);

  /* creation of myTxQueue */
  myTxQueueHandle = osMessageQueueNew (64, sizeof(uint8_t), &myTxQueue_attributes);

  /* creation of myCmdLineObjQueue */
  myCmdLineObjQueueHandle = osMessageQueueNew (1, 64, &myCmdLineObjQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTxTask */
  myTxTaskHandle = osThreadNew(StartTxTask, NULL, &myTxTask_attributes);

  /* creation of myRxTask */
  myRxTaskHandle = osThreadNew(StartRxTask, NULL, &myRxTask_attributes);

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
for (;;)
{
	HAL_UART_Receive_DMA(HUART, (uint8_t*) &readbyte, 1);
	term_qPrintf(myTxQueueHandle, "hallo welt!");
	osDelay(250);
}

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

/* USER CODE BEGIN Header_StartRxTask */
/**
* @brief Function implementing the myRxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRxTask */
void StartRxTask(void *argument)
{
  /* USER CODE BEGIN StartRxTask */

    BaseType_t xStatus;
    /* Infinite loop */
    for (;;)
	{
	if( xSemaphoreTake( myFlagNewStringHandle, 0)==pdPASS)
	     {
	    int ItemsLeft = uxQueueMessagesWaiting( myRxQueueHandle);

	    if (ItemsLeft)
		{
		TD_LINEOBJ lobj;
		char rxbuff[ ItemsLeft];

		memset(rxbuff,'\0',ItemsLeft);

		for (int var = 0; var < ItemsLeft; ++var)
		    {
		    uint8_t pvBuffer=0;

		    xQueueReceive( myRxQueueHandle, &pvBuffer, 0);

		    rxbuff[ var ] = pvBuffer;

		    }
		rxbuff[ ItemsLeft-1 ] = '\0';


		dbase_Make( &lobj, strdup("cmd"), strdup(rxbuff), 0, 0, 0, 0);

		xStatus = dBase_StoreQueue( myCmdLineObjQueueHandle, &lobj );

		xSemaphoreGive(myCountNewCmdHandle);

		}
	    }

	osDelay(1);
	}
    //
  /* USER CODE END StartRxTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
