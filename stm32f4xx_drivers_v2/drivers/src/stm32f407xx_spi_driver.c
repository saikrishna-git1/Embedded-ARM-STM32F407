/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Jan 27, 2024
 *      Author: MY PC
 */

#include "stm32f407xx_spi_driver.h"


void SPI_PClk_Ctrl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi) {
	if( EnOrDi == ENABLE ) { // ??alt - switch st. and typecasting - onenote
			if(pSPIx == SPI1)	SPI1_PCLK_EN();
		else if(pSPIx == SPI2)	SPI2_PCLK_EN();
		else if(pSPIx == SPI3)	SPI3_PCLK_EN();
		//else if(pSPIx == SPI4)	SPI4_PCLK_EN();
	} 
	else {
			if(pSPIx == SPI1)	SPI1_PCLK_DI();
		else if(pSPIx == SPI2)	SPI2_PCLK_DI();
		else if(pSPIx == SPI3)	SPI3_PCLK_DI();
		//else if(pSPIx == SPI4) 	SPI4_PCLK_DI();
	}
}


void SPI_Init(SPI_Handle_t *pSPI_Handle) {
	//Enable peri clk
	SPI_PClk_Ctrl(pSPI_Handle->pSPIx, ENABLE);

	//1. configure SPI_CR1 register
	uint32_t temp = 0;

	//1.1. Configure device mode - Master/Slave
	temp |= pSPI_Handle->SPI_Config.SPI_Master_or_Slave << 2;

	//1.2 Configure bus config
	if(pSPI_Handle->SPI_Config.SPI_Bus_Config == SPI_FULL_DUPLEX) {
		//bidi mode should be cleared
		temp &= ~(1 << 15);
	}
	else if(pSPI_Handle->SPI_Config.SPI_Bus_Config == SPI_HALF_DUPLEX) {
		//bidi mode should be set
		temp |= (1 << 15);
	}
	else if(pSPI_Handle->SPI_Config.SPI_Bus_Config == SPI_SIMPLEX_RX_ONLY) {
		//bidi mode should be cleared
		temp &= ~(1 << 15);
		//RXONLY bit must be set
		temp |= (1 << 10);
	}

	//1.3 Config SPI serial clk speed (baud rate)
	temp |= pSPI_Handle->SPI_Config.SPI_Speed << 3;

	//1.4 Config DataFrameFormat
	temp |= pSPI_Handle->SPI_Config.SPI_DataFrame_Format << 11;

	//1.5 Config CPOL
	temp |= pSPI_Handle->SPI_Config.SPI_CPOL << 1;

	//1.6 Config CPHA
	temp |= pSPI_Handle->SPI_Config.SPI_CPHA << 0;

	//1.7 Config SSM
	temp |= pSPI_Handle->SPI_Config.SPI_SSM << 9;

	pSPI_Handle->pSPIx->SPI_CR1 = temp;
}



uint32_t SPI_GetStatusReg(SPI_RegDef_t *pSPIx) {
	return pSPIx->SPI_SR;
}



void SPI_Tx_Data(SPI_RegDef_t *pSPIx, uint8_t *pTx_Buff, uint32_t len) {
	while(len > 0) {
		//1. wait until TXE is set
		while( (SPI_GetStatusReg(pSPIx) & (1 << 1) )== 0 ); //query TXE flag status

		//2. Check DataFrameFormat, tx data, incr Tx_Buff addr, decr len
		if( (pSPIx->SPI_CR1 & (1 << 11) ) == SPI_DATA_FF_8BITS) {
			pSPIx->SPI_DR = *pTx_Buff;
			pTx_Buff++;
			len--;
		}
		else {
			pSPIx->SPI_DR = *((uint16_t *) pTx_Buff);
			pTx_Buff+=2;
			len-=2;
		}
	}
}



void SPI_PeriCtrl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi) {
	if(ENABLE) {
		pSPIx->SPI_CR1 |= (1 << 6);
	}
	else {
		pSPIx->SPI_CR1 &=~ (1 << 6);
	}
}



void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi) {
	if(ENABLE) {
		pSPIx->SPI_CR1 |= (1 << 8);
	}
	else {
		pSPIx->SPI_CR1 &=~ (1 << 8);
	}
}
