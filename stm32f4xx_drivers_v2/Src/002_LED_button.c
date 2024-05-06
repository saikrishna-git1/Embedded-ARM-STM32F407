/*
 * 002_LED_button.c
 *
 *  Created on: Oct 11, 2022
 *      Author: MY PC
 */

#include <stm32f407xx.h> // device-specific header file

#define HIGH 1
#define LOW 0
#define BTN_PRESSED HIGH // in nucleo board, #define BTN_PRESSED LOW
#define EXT_BTN_PRESSED LOW



void delay() {
	for(uint32_t i=0; i<500000/2; i++);
}

int main()	{

	GPIO_Handle_t GpioLed, GpioPushButton; // first create 2 vars for LED and PushButton

#if 1	// PA8 - external LED
	GpioLed.pGPIOx = GPIOA; // select the port
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_8;
	GpioLed.GPIO_PinConfig.GPIO_PinMODE = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinOSPEED = GPIO_OPSPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_PP; // use push-pull unless open-drain is really required
	GpioLed.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD;
	//GpioLed.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_OD;
	//GpioLed.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD; // int. PU resistor value too high (40Kohms), so use ext. PU resistor
	GPIO_PClk_Ctrl(GPIOA, ENABLE);
	GPIO_Init(&GpioLed); // calling API - GPIO_Init

	// PB12  - external push-button
	GpioPushButton.pGPIOx = GPIOB; // select the port
	GpioPushButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GpioPushButton.GPIO_PinConfig.GPIO_PinMODE = GPIO_MODE_IN;
	GpioPushButton.GPIO_PinConfig.GPIO_PinOSPEED = GPIO_OPSPEED_FAST; // ?
	//GpioPushButton.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_PP; // use push-pull unless open-drain is really required
	GpioPushButton.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_PU;
	GPIO_PClk_Ctrl(GPIOB, ENABLE);
	GPIO_Init(&GpioPushButton); // calling API - GPIO_Init
#endif

	//using GPIO_Handle_t
	// PD12 - LED
	// PA0  - push-button
#if 0	// PD12 - LED
	GpioLed.pGPIOx = GPIOD; // select the port
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMODE = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinOSPEED = GPIO_OPSPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_PP; // use push-pull unless open-drain is really required
	GpioLed.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD;
	//GpioLed.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_OD;
	//GpioLed.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD; // int. PU resistor value too high (40Kohms), so use ext. PU resistor
	GPIO_PClk_Ctrl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed); // calling API - GPIO_Init

	// PA0  - push-button
	//GPIO_Handle_t GpioPushButton; // see above -- create a variable for GPIO handle
	GpioPushButton.pGPIOx = GPIOA; // select the port
	GpioPushButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	GpioPushButton.GPIO_PinConfig.GPIO_PinMODE = GPIO_MODE_IN;
	GpioPushButton.GPIO_PinConfig.GPIO_PinOSPEED = GPIO_OPSPEED_FAST; // ?
	//GpioPushButton.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_PP; // use push-pull unless open-drain is really required
	GpioPushButton.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD;
	GPIO_PClk_Ctrl(GPIOA, ENABLE);
	GPIO_Init(&GpioPushButton); // calling API - GPIO_Init
#endif

/////////////////////////////////////////////
	while(1) {
				#if 0	// on-board LED and push-button
					if( GPIO_RdIp_Pin(GPIOA, GPIO_PIN_0) == BTN_PRESSED ) {
						delay();
						GPIO_ToggleOp_Pin(GPIOD, GPIO_PIN_12);
					}
				#endif

				#if 1	// external LED and push-button
					if( GPIO_RdIp_Pin(GPIOB, GPIO_PIN_12) == EXT_BTN_PRESSED ) {
						delay();
						GPIO_ToggleOp_Pin(GPIOA, GPIO_PIN_8);
					}
				#endif
	}



	return 0;
}
