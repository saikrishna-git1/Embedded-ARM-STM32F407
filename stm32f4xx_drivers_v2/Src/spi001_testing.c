/*
 * spi001_testing.c
 *
 *  Created on: Feb 2, 2024
 *      Author: MY PC
 */

#include <string.h>
#include "stm32f407xx_spi_driver.h"

/*PB15 - SPI2_MOSI
PB14 - SPI2_MISO
PB13 - SPI2_SCLK
PB12 - SPI2_NSS
Alt fn mode = 5
*/

void SPI2_GPIOInit(void) {
	GPIO_Handle_t SPI2_pins;

	SPI2_pins.pGPIOx = GPIOB;

	SPI2_pins.GPIO_PinConfig.GPIO_PinMODE = GPIO_MODE_ALTFN;
	SPI2_pins.GPIO_PinConfig.GPIO_PinAF = 5;
	SPI2_pins.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_PP;
	SPI2_pins.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD;
	SPI2_pins.GPIO_PinConfig.GPIO_PinOSPEED = GPIO_OPSPEED_FAST;

	SPI2_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13; //SCLK
	GPIO_Init(&SPI2_pins);

	SPI2_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15; //MOSI
	GPIO_Init(&SPI2_pins);

#if 0
	SPI2_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14; //MISO
	GPIO_Init(&SPI2_pins);

	SPI2_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12; //NSS
	GPIO_Init(&SPI2_pins);
#endif
}


void SPI2_Init(void) {
	SPI_Handle_t SPI2_Handle;

	SPI2_Handle.pSPIx = SPI2;
	SPI2_Handle.SPI_Config.SPI_Bus_Config = SPI_FULL_DUPLEX;
	SPI2_Handle.SPI_Config.SPI_Master_or_Slave = SPI_MASTER;
	SPI2_Handle.SPI_Config.SPI_Speed = SPI_SCLK_SPEED_DIV_2;
	SPI2_Handle.SPI_Config.SPI_DataFrame_Format = SPI_DATA_FF_8BITS;
	SPI2_Handle.SPI_Config.SPI_CPOL = SPI_CPOL_0;
	SPI2_Handle.SPI_Config.SPI_CPHA = SPI_CPHA_1;
	SPI2_Handle.SPI_Config.SPI_SSM = SPI_SSM_SW_EN;
	SPI_Init(&SPI2_Handle);
}


int main(void) {

	char user_data[] = "Hello, world";

	SPI2_GPIOInit(); //config GPIO pins as SPI2 pins

	SPI2_Init(); //SPI2 peripheral configuration

	SPI_SSIConfig(SPI2, ENABLE); //makes NSS bit HIGH internally and avoids MODF err
	SPI_PeriCtrl(SPI2, ENABLE); //Enable SPI2 peri

	SPI_Tx_Data(SPI2, (uint8_t *)user_data, strlen(user_data) );

	while(1);

	return 0;
}
