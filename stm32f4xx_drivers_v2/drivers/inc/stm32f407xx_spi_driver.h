/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: Jan 27, 2024
 *      Author: MY PC
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"

#define SPI_MASTER	1
#define SPI_SLAVE	0

#define SPI_FULL_DUPLEX			0
#define SPI_HALF_DUPLEX			1
#define SPI_SIMPLEX_TX_ONLY		2 //FULL_DUPLEX
#define SPI_SIMPLEX_RX_ONLY		3

#define SPI_DATA_FF_8BITS		0
#define SPI_DATA_FF_16BITS		1

#define SPI_CPOL_1			1
#define SPI_CPOL_0			0

#define SPI_CPHA_1			1
#define SPI_CPHA_0			0

#define SPI_SSM_SW_EN			1
#define SPI_SSM_SW_DI			0


#define SPI_SCLK_SPEED_DIV_2		0
#define SPI_SCLK_SPEED_DIV_4		1
#define SPI_SCLK_SPEED_DIV_8		2
#define SPI_SCLK_SPEED_DIV_16		3
#define SPI_SCLK_SPEED_DIV_32		4
#define SPI_SCLK_SPEED_DIV_64		5
#define SPI_SCLK_SPEED_DIV_128		6
#define SPI_SCLK_SPEED_DIV_256		7

//SPI configurable items for user application
typedef struct {
	uint8_t SPI_Master_or_Slave;
	uint8_t SPI_Bus_Config;
	uint8_t SPI_DataFrame_Format;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
	uint8_t SPI_Speed;
} SPI_Config_t;


typedef struct {
	SPI_RegDef_t *pSPIx;	//Base_address of SPI peripheral
	SPI_Config_t SPI_Config;
} SPI_Handle_t;


// APIs exposed to appln programmer
void SPI_PClk_Ctrl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_Init(SPI_Handle_t *pSPI_Handle); 
void SPI_DeInit(SPI_RegDef_t *pSPIx);
void SPI_Tx_Data(SPI_RegDef_t *pSPIx, uint8_t *pTx_Buff, uint32_t len); //blocking API
void SPI_Rx_Data(SPI_RegDef_t *pSPIx, uint8_t *pRx_Buff, uint32_t len);

void SPI_ITConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_ITPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPI_Handle); 


void SPI_PeriCtrl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
