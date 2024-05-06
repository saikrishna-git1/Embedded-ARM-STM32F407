/*
 * 001_LED_toggle.c
 *
 *  Created on: Oct 1, 2022
 *      Author: MY PC
 */

#include <stm32f407xx.h> // device-specific header file
// #include <stm32f407xx_gpio_driver.h> // included in <stm32f407xx.h> - device-specific header file

void delay() {
	for(uint32_t i=0; i<500000; i++);
}

int main()	{

	GPIO_Handle_t GpioLed; // first create a variable for GPIO handle

	GpioLed.pGPIOx = GPIOD; // select the port
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMODE = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinOSPEED = GPIO_OPSPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_PP; // use push-pull unless open-drain is really required
	GpioLed.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD;
	//GpioLed.GPIO_PinConfig.GPIO_PinOTYPE = GPIO_OTYPE_OD;
	//GpioLed.GPIO_PinConfig.GPIO_PinPUPD = GPIO_PIN_NOPUPD; // int. PU resistor value too high (40Kohms), so use ext. PU resistor

	GPIO_PClk_Ctrl(GPIOD, ENABLE);

	// calling API - GPIO_Init
	GPIO_Init(&GpioLed);

	while(1) {
		GPIO_ToggleOp_Pin(GPIOD, GPIO_PIN_12);
		delay();
	}

	return 0;
}
