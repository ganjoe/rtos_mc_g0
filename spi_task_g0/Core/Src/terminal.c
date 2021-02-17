#include "terminal.h"
#include "utils.h"


/*-----------------------------------------------------------*/
void term_qPrintf(osMessageQueueId_t QueueHandle, char *fmt, ...)
    {
    int ItemsLeft = uxQueueSpacesAvailable(QueueHandle);

    if (ItemsLeft)
	{
	va_list argp;

	va_start(argp, fmt);

	char pbuffer[UART_PRINTBUFFER];

	int bytesWrote = 0;

	bytesWrote = vsnprintf(pbuffer, UART_PRINTBUFFER, fmt, argp);

	va_end(argp);

	utils_truncate_number_int(&bytesWrote, 0, ItemsLeft);

	for (int var = 0; var < bytesWrote; ++var)
	    {
	    osMessageQueuePut(QueueHandle,  &pbuffer[var], 0, osWaitForever);
	   // xQueueSendToBack(QueueHandle, &pbuffer[var], 0);
	    }
	}
    else
	{
	xQueueReset(QueueHandle);

	xQueueSendToBack(QueueHandle, "!F", 0);

	}
    }

TD_TERMINAL btTerm;

/*-----------------------------------------------------------*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
    {
    uint8_t byte_received = huart->Instance->RDR;

    xQueueSendToBackFromISR(myRxQueueHandle, &byte_received, 0);

    if (byte_received == (uint8_t) 13)
	xSemaphoreGiveFromISR(myFlagNewStringHandle, 0);

    HAL_UART_Receive_DMA(HUART, (uint8_t*) &readbyte, 1);
    }
