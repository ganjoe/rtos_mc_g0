/*
 * DRV83.c
 *
 *  Created on: Feb 12, 2021
 *      Author: pymd02
 */
#include "DRV83.h"
#include "spi.h"
#include "utils.h"

/* Registeradressen sind durchnummeriert */
typedef enum
{
	faultstatus = 0,
	vgsStatus,
	driverControl,
	gateDriveHS,
	gateDriveLS,
	OCPcontrol,
	CSAcontrol,
}
EN_DRV_ADDR;

typedef struct
	{
	uint16_t shadowRegister[8];
	EN_DRV_ADDR regAdress;
	EN_DRV_MODES modeSelect;
	}
TD_DRV83;

typedef struct TD_DRV83 drv83;

void drv_setPwmMode(EN_DRV_MODES select)
{
	uint16_t bitMask = 0;

	drv_readRegister((uint8_t)select, &bitMask);
/*
	switch (select) {
		case pwm_1x:
			utils_set_bit_in_Word(&bitMask, 5, 0);
			utils_set_bit_in_Word(&bitMask, 6, 1);
			drv_writeRegister(driverControl, bitMask);
			break;
		case pwm_3x:
			utils_set_bit_in_Word(&bitMask, 5, 1);
			utils_set_bit_in_Word(&bitMask, 6, 0);
			drv_writeRegister(driverControl, bitMask);
			break;
		case pwm_6x:
			utils_set_bit_in_Word(&bitMask, 5, 0);
			utils_set_bit_in_Word(&bitMask, 6, 0);
			drv_writeRegister(driverControl, bitMask);
			break;

		default:


			break;
	}
	*/
}

void drv_writeRegister	(uint8_t regNr, uint16_t bitMask)
{
	uint8_t pTxData[2];
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 0);
	utils_get_bytes_in_word(&bitMask, &pTxData[0], &pTxData[1] );

	//HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, 2, HAL_TIMEOUT);
	HAL_SPI_Transmit(&hspi1, pTxData, 2, HAL_TIMEOUT);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 1);
}

void drv_readRegister	(uint8_t regNr, uint16_t* data)
{
	uint8_t pTxData[2];
	uint8_t pRxData[2];
	pTxData[1] =0x90;
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 0);
	HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, 1, HAL_TIMEOUT);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 1);

}

