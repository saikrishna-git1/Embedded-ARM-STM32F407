/*
 * main.c
 *
 *  Created on: Jan 20, 2024
 *      Author: MY PC
 */

////////////////////////////////////////////////////////
// GPIO interrupt exercise
// Connect an ext button to PD5 and toggle the LED whenever intr, is triggered by the button press.
// Intr. should be triggered during falling edge of button press
////////////////////////////////////////////////////////

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

	//using GPIO_Handle_t
#if 1	// PD12 - LED
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

	// PB12  - external push-button
	GpioPushButton.pGPIOx = GPIOB; // select the port
	GpioPushButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GpioPushButton.GPIO_PinConfig.GPIO_PinMODE = GPIO_MODE_IT_FT;
	GpioPushButton.GPIO_PinConfig.GPIO_PinOSPEED = GPIO_OPSPEED_FAST; // ?
	//GpioPushButton.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_PP; // use push-pull unless open-drain is really required
	GpioPushButton.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_PU;
	GPIO_PClk_Ctrl(GPIOB, ENABLE);
	GPIO_Init(&GpioPushButton); // calling API - GPIO_Init
#endif


	//IRQ configurations
	GPIO_ITPriorityConfig(IRQ_NO_EXTI15_10, 15); //optional
	GPIO_ITConfig(IRQ_NO_EXTI15_10, ENABLE);

	while(1);

	return 0;
}


void EXTI15_10_IRQHandler(void) { //handle the intr
	//Call the driver provided GPIO intr handling API
	GPIO_IRQHandling(GPIO_PIN_12); //PinNumber
	GPIO_ToggleOp_Pin(GPIOD, GPIO_PIN_12);
}
