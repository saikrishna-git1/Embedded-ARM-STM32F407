/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Sep 17, 2022
 *      Author: MY PC
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"


/*
 *********** Configuration structure for GPIO pin ***********
 */
typedef struct // GPIO_PinConfig_t
{
	uint8_t GPIO_PinNumber; // 1 Byte is sufficient to hold the values // possible values from @GPIO_PIN_NUMBERS
	uint8_t GPIO_PinMODE; // possible values from @GPIO_PIN_MODES
	uint8_t GPIO_PinOSPEED; // possible values from @GPIO_PIN_OPSPEEDS
	uint8_t GPIO_PinPUPD; // possible values from @GPIO_PIN_PUPD_CONFIGS
	uint8_t GPIO_PinOTYPE; // possible values from @GPIO_PIN_OTYPES
	uint8_t GPIO_PinAF; // this field has no meaning if PinMODE is not set to AF mode
}GPIO_PinConfig_t;


/*
 *********** Handle structure for GPIO pin ***********
 */
typedef struct // GPIO_Handle_t // Contains GPIOx peri base-addr & config settings
{
	GPIO_RegDef_t *pGPIOx; // GPIO_RegDef_t *pGPIOxBaseAddr;
							// pointer to hold the base address of the GPIOx peripheral
							// This holds the base-addr of the GPIO port to which the pin belongs
							// usage ex: GPIO_RegDef_t *pGPIOx = GPIOA; -- ??
	GPIO_PinConfig_t GPIO_PinConfig; // This holds GPIOx's pin configuration settings
}GPIO_Handle_t;


/*
 *@GPIO_PIN_NUMBERS
 ********************** GPIO pin numbers **********************
 */
#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_PIN_8		8
#define GPIO_PIN_9		9
#define GPIO_PIN_10		10
#define GPIO_PIN_11		11
#define GPIO_PIN_12		12
#define GPIO_PIN_13		13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15

/*
 *@GPIO_PIN_MODES
 ********************** GPIO pin possible modes **********************
 */
#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ALTFN			2
#define GPIO_MODE_ANALOG		3
// Custom interrupt modes - not defined in Reference Manual
#define GPIO_MODE_IT_FT 		4 // GPIO_MODE_INTERRUPT_FALLING-EDGE-TRIGGER detection
#define GPIO_MODE_IT_RT 		5 // GPIO_MODE_INTERRUPT_RISING-EDGE-TRIGGER detection
#define GPIO_MODE_IT_RFT 		6 // GPIO_MODE_INTERRUPT_RISING-EDGE-FALLING-EDGE-TRIGGER


/*
 * @GPIO_PIN_OPSPEEDS
 ********************** GPIO pin possible output speeds **********************
 */
#define GPIO_OPSPEED_LOW		0
#define GPIO_OPSPEED_MEDIUM		1
#define GPIO_OPSPEED_FAST		2
#define GPIO_OPSPEED_HIGH		3


/*
 * @GPIO_PIN_OTYPES
 ********************** GPIO pin possible output types **********************
 */
#define GPIO_OTYPE_PP	0 // Reset state
#define GPIO_OTYPE_OD	1


/*
 * @GPIO_PIN_PUPD_CONFIGS
 ********************** GPIO pin possible pull-up & pull-down configs **********************
 */
#define GPIO_PIN_NOPUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2







/********************************************************************************
 *				APIs supported by this driver
 *	For more info on APIs, check the function definitions
 ********************************************************************************/

/*
 * Peri clk setup
 */
void GPIO_PClk_Ctrl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi); // enable/disable GPIOx peri clock for a given GPIO base-addr


/*
 * Init & DeInit
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle); // initialize the GPIOx peri // takes pointer to the handle struct
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx); // de-initialize the GPIOx peri - config back to reset state // takes base-addr of GPIOx peri


/*
 * Data write & read
 */
uint8_t GPIO_RdIp_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber); // read from i/p pin // return-type = boolean or uint8_t
uint16_t GPIO_RdIp_Port(GPIO_RegDef_t *pGPIOx); // read from i/p port
void GPIO_WrOp_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t SetOrRst); // write to o/p pin
void GPIO_WrOp_Port(GPIO_RegDef_t *pGPIOx, uint16_t Value); // write to o/p port
void GPIO_ToggleOp_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber); // toggle o/p pin


/*
 * IRQ Config & ISR Handling
 */
void GPIO_ITConfig(uint8_t IRQNumber, uint8_t EnOrDi); // config the IRQ number of GPIOx pin, enabling/disabling it, setting up the priority
																			// optional parameter - IRQ grouping
void GPIO_ITPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber); // whenever an intr for GPIOx pin occurs, user_app can call this fn to service it



#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
