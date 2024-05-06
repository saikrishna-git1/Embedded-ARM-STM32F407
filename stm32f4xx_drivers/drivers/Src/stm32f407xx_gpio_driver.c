/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Sep 17, 2022
 *      Author: MY PC
 */

#include "stm32f407xx_gpio_driver.h"

/*
 ***************************** Peri clk setup ******************************************************
 */
/***************************************************************************************************
 * @fn					- GPIO_PClk_Ctrl
 *
 * @brief				- Enables or disables peri clock for a given GPIO port based on EnOrDi param
 *
 * @param[in]			- Base-addr of the GPIO peri
 * @param[in]			- ENABLE or DISABLE macros (in MCU header file)
 *
 * @return				- none
 *
 * @Note				- none
 */
void GPIO_PClk_Ctrl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi)
{
	if( EnOrDi == ENABLE ) // ??alt - switch st. and typecasting - onenote
	{
			 if(pGPIOx == GPIOA)
				GPIOA_PCLK_EN();

		else if(pGPIOx == GPIOB)
				GPIOB_PCLK_EN();

		else if(pGPIOx == GPIOC)
				GPIOC_PCLK_EN();

		else if(pGPIOx == GPIOD)
				GPIOD_PCLK_EN();

		else if(pGPIOx == GPIOE)
				GPIOE_PCLK_EN();

		else if(pGPIOx == GPIOF)
				GPIOF_PCLK_EN();

		else if(pGPIOx == GPIOG)
				GPIOG_PCLK_EN();

		else if(pGPIOx == GPIOH)
				GPIOH_PCLK_EN();

		else if(pGPIOx == GPIOI)
				GPIOI_PCLK_EN();
	}
	else
	{
		 	 if(pGPIOx == GPIOA)
		 		 GPIOA_PCLK_DI();

		 	 else if(pGPIOx == GPIOB)
		 		 GPIOB_PCLK_DI();

		 	 else if(pGPIOx == GPIOC)
		 		 GPIOC_PCLK_DI();

		 	 else if(pGPIOx == GPIOD)
		 		 GPIOD_PCLK_DI();

		 	 else if(pGPIOx == GPIOE)
		 		 GPIOE_PCLK_DI();

		 	 else if(pGPIOx == GPIOF)
		 		 GPIOF_PCLK_DI();

		 	 else if(pGPIOx == GPIOG)
		 		 GPIOG_PCLK_DI();

		 	 else if(pGPIOx == GPIOH)
		 		 GPIOH_PCLK_DI();

		 	 else if(pGPIOx == GPIOI)
		 		 GPIOI_PCLK_DI();
	}

}

/*
 ***************************** Init & DeInit *****************************
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle) // initialize the GPIOx peri // takes pointer to the handle struct
{
	uint32_t temp = 0;
	// 1. config the mode of GPIO pin
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMODE <= GPIO_MODE_ANALOG ) { // non-interrupt mode
		temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMODE << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ); // storing the MODE value into 'temp' after left-shifting it to the corresponding pin number // every pin has 2 MODER bits
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ); // clearing the corresponding MODER bits using 0x3 as the mask
		pGPIOHandle->pGPIOx->MODER |= temp; // setting the corresponding MODER bits
	}
	else {	// Custom interrupt modes - not defined in Reference Manual
		if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMODE <= GPIO_MODE_IT_FT ) {
			//1. config FTSR and clear RTSR
			EXTI->EXTI_FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->EXTI_RTSR &=~ ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}
		else if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMODE <= GPIO_MODE_IT_RT ) {
			//1. config RTSR and clear FTSR
			EXTI->EXTI_RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->EXTI_FTSR &=~ ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}
		else if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMODE <= GPIO_MODE_IT_RFT ) {
			//1. config both FTSR and RTSR
			EXTI->EXTI_RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->EXTI_FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}

		//2. config SYSCFG_EXTICR for GPIO port selection
		uint8_t temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portCode = GPIOBASE_TO_PORTCODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->SYSCFG_EXTICR[temp] = ( portCode << (temp2*4) );

		//3. enable EXTI intr delivery using IMR
		EXTI->EXTI_IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	}

	// 2. config o/p speed
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinOSPEED << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ); // storing the OSPEED value into 'temp' after left-shifting it to the corresponding pin number // every pin has 2 OSPEEDR bits
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	// 3. config PuPd settings
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinPUPD << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ); // storing the PUPD value into 'temp' after left-shifting it to the corresponding pin number // every pin has 2 PUPDR bits
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	// 4. config o/p type
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinOTYPE << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // storing the OTYPE value into 'temp' after left-shifting it to the corresponding pin number // every pin has 1 OTYPER bit
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	// 5. config alt. func. (if required) // valid only if PinMODE = AF mode, config with the value in var PinAF
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMODE == GPIO_MODE_ALTFN )
	{
		// config alt. func. regs
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~( 0xF << ( 4 * temp2 ) ); //clearing - 4 bits per pin
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAF << ( 4 * temp2 ) ); //setting
	}
}


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) // de-initialize the GPIOx peri - config back to reset state // takes base-addr of GPIOx peri
{
			if(pGPIOx == GPIOA)
					GPIOA_PERI_RST();

			else if(pGPIOx == GPIOB)
					GPIOB_PERI_RST();

			else if(pGPIOx == GPIOC)
					GPIOC_PERI_RST();

			else if(pGPIOx == GPIOD)
					GPIOD_PERI_RST();

			else if(pGPIOx == GPIOE)
					GPIOE_PERI_RST();

			else if(pGPIOx == GPIOF)
					GPIOF_PERI_RST();

			else if(pGPIOx == GPIOG)
					GPIOG_PERI_RST();

			else if(pGPIOx == GPIOH)
					GPIOH_PERI_RST();

			else if(pGPIOx == GPIOI)
					GPIOI_PERI_RST();
}


/*
 ***************************** Data write & read *****************************
 */

/***************************************************************************************************
 * @fn					- GPIO_RdIp_Pin
 *
 * @brief				- read from i/p pin; read the corresponding bit-position from IDR
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				- 0 or 1 (return-type = boolean or uint8_t)
 *
 * @Note				- none
 */
uint8_t GPIO_RdIp_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)	( (pGPIOx->IDR >> PinNumber) & 0x00000001 );
	return value;
}


uint16_t GPIO_RdIp_Port(GPIO_RegDef_t *pGPIOx) // read from i/p port
{
	uint16_t value;
	value = (uint16_t) 	(pGPIOx->IDR);
	return value;
}

void GPIO_WrOp_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t SetOrRst) // write to o/p pin
{
	pGPIOx->ODR &= ~( 0x1 << PinNumber );
	pGPIOx->ODR |= ( SetOrRst << PinNumber );	// if-else statement also can be used
}

void GPIO_WrOp_Port(GPIO_RegDef_t *pGPIOx, uint16_t Value) // write to o/p port
{
	pGPIOx->ODR = Value;
}

void GPIO_ToggleOp_Pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) // toggle o/p pin
{
	pGPIOx->ODR ^= ( 0x1 << PinNumber );
}


/*
 * IRQ Config & ISR Handling
 * To configure the NVIC regs of the ARM C-M4 processor
 */
void GPIO_ITConfig(uint8_t IRQNumber, uint8_t EnOrDi) // config the IRQ number of GPIOx pin, enabling/disabling it, setting up the priority
																			// optional parameter - IRQ grouping
{
	if(EnOrDi == ENABLE)
	{
		if(IRQNumber <= 31) {
			*NVIC_ISER0 = ( 1 << (IRQNumber) );
		} else if(IRQNumber > 31 && IRQNumber <= 63) {
			*NVIC_ISER1 = ( 1 << (IRQNumber % 32) );
		} else if(IRQNumber > 63 && IRQNumber <= 95) {
			*NVIC_ISER2 = ( 1 << (IRQNumber % 64) );
		}


	} else { //DISABLE
		if(IRQNumber <= 31) {
			*NVIC_ICER0 = ( 1 << (IRQNumber) );
		} else if(IRQNumber > 31 && IRQNumber <= 63) {
			*NVIC_ICER1 = ( 1 << (IRQNumber % 32) );
		} else if(IRQNumber > 63 && IRQNumber <= 95) {
			*NVIC_ICER2 = ( 1 << (IRQNumber % 64) );
		}
	}
}

void GPIO_ITPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority) {
	uint32_t ipr_reg = (IRQNumber / 4);
	uint32_t ipr_byte_offset = (IRQNumber % 4);
	uint8_t shift_val = (ipr_byte_offset*8) + (8 - NO_OF_IPRBITS_IMPL);
	*(NVIC_IPR_BASE + (ipr_reg*4) ) |= (IRQPriority << shift_val ) ;
}

void GPIO_IRQHandling(uint8_t PinNumber) { // whenever an intr for GPIOx pin occurs, user_app can call this fn to service it
	//clear the EXTI_PR corresponding to the PinNumber
	if(EXTI->EXTI_PR & (1 << PinNumber)) {
		EXTI->EXTI_PR |= ( 1 << PinNumber );
	}
}




#if 0
void IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t SetOrClear) {
	if(SetOrClear == SET) {
		uint8_t iser_reg = IRQNumber / 32;
		uint8_t iser_bit_pos = IRQNumber % 32;
		if()

	} else if(SetOrClear == CLEAR) {

	}
}
#endif
