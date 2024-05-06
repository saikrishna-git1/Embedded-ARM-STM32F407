/*
 * stm32f407xx.h
 *
 *  Created on: Sep 12, 2022
 *      Author: MY PC
 */

/*
 * //////////////// STM32F407xx device-specific header file ////////////////
 */

/////////////////////////////////////////////////////////////////////
// Contains ---	 Base addresses of various memories, bus domains, peripheral registers,
// 				Clock enable/disable macros as C-macros
//	This file basically describes the uC


#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

/*	Base addresses of Flash and SRAM memories	*/
// By default, compiler treats all numbers as signed
// Must explicitly mention that addresses are unsigned
#define FLASH_BASE					0x08000000U // Main memory is Flash mem.
#define SRAM1_BASE					0x20000000U // 112 KB
#define SRAM2_BASE					0x2001C000U // SRAM1_BASEADDR + 112 KB // 16KB
#define ROM_BASE					0x1FFF0000U	// System memory is ROM
#define SRAM 						SRAM1_BASEADDR // Main RAM is SRAM1
#define OTP_BASE					0x1FFF7800U

/*	Base addresses of Bus domains	*/
#define PERIPH_BASE					0x40000000U
#define APB1PERIPH_BASE 			PERIPH_BASE
#define APB2PERIPH_BASE			  	0x40010000U // ( PERIPH_BASE + 0x00010000 )
#define AHB1PERIPH_BASE			  	0x40020000U // ( PERIPH_BASE + 0x00020000 )
#define AHB2PERIPH_BASE			  	0x50000000U // ( PERIPH_BASE + 0x10000000 )
#define AHB3PERIPH_BASE			  	0xA0000000U // ( PERIPH_BASE + 0x60000000 )

/* Addresses of NVIC regs*/
#define NVIC_ISER0					( (uint32_t volatile *) 0xE000E100 )
#define NVIC_ISER1					( (uint32_t volatile *) 0xE000E104 )
#define NVIC_ISER2					( (uint32_t volatile *) 0xE000E108 )
#define NVIC_ISER3					( (uint32_t volatile *) 0xE000E10C )
#define NVIC_ISER4					( (uint32_t volatile *) 0xE000E110 )
#define NVIC_ISER5					( (uint32_t volatile *) 0xE000E114 )
#define NVIC_ISER6					( (uint32_t volatile *) 0xE000E118 )
#define NVIC_ISER7					( (uint32_t volatile *) 0xE000E11C )

#define NVIC_ICER0					( (uint32_t volatile *) 0xE000E180 )
#define NVIC_ICER1					( (uint32_t volatile *) 0xE000E184 )
#define NVIC_ICER2					( (uint32_t volatile *) 0xE000E188 )
#define NVIC_ICER3					( (uint32_t volatile *) 0xE000E18C )
#define NVIC_ICER4					( (uint32_t volatile *) 0xE000E190 )
#define NVIC_ICER5					( (uint32_t volatile *) 0xE000E194 )
#define NVIC_ICER6					( (uint32_t volatile *) 0xE000E198 )
#define NVIC_ICER7					( (uint32_t volatile *) 0xE000E19C )

#define NVIC_IPR_BASE				( (uint32_t volatile *) 0xE000E400 )
#define NO_OF_IPRBITS_IMPL			4

/*	Base addresses of peripherals hanging on AHB1 bus	*/
#define GPIOA_BASE					( AHB1PERIPH_BASE + 0x0000 )
#define GPIOB_BASE					( AHB1PERIPH_BASE + 0x0400 )
#define GPIOC_BASE					( AHB1PERIPH_BASE + 0x0800 )
#define GPIOD_BASE					( AHB1PERIPH_BASE + 0x0C00 )
#define GPIOE_BASE					( AHB1PERIPH_BASE + 0x1000 )
#define GPIOF_BASE					( AHB1PERIPH_BASE + 0x1400 )
#define GPIOG_BASE					( AHB1PERIPH_BASE + 0x1800 )
#define GPIOH_BASE					( AHB1PERIPH_BASE + 0x1C00 )
#define GPIOI_BASE					( AHB1PERIPH_BASE + 0x2000 )

#define RCC_BASE 					( AHB1PERIPH_BASE + 0x3800 )

/*	Base addresses of peripherals hanging on APB1 bus	*/
#define I2C1_BASE					( APB1PERIPH_BASE + 0x5400 )
#define I2C2_BASE					( APB1PERIPH_BASE + 0x5800 )
#define I2C3_BASE					( APB1PERIPH_BASE + 0x5C00 )
#define SPI2_BASE					( APB1PERIPH_BASE + 0x3800 )
#define I2S2_BASE					SPI2_BASE
#define SPI3_BASE					( APB1PERIPH_BASE + 0x3C00 )
#define I2S3_BASE					SPI3_BASE
#define USART2_BASE					( APB1PERIPH_BASE + 0x4400 )
#define USART3_BASE					( APB1PERIPH_BASE + 0x4800 )
#define UART4_BASE					( APB1PERIPH_BASE + 0x4C00 )
#define UART5_BASE					( APB1PERIPH_BASE + 0x5000 )

/*	Base addresses of peripherals hanging on APB2 bus	*/
#define EXTI_BASE					( APB2PERIPH_BASE + 0x3C00 )
#define SPI1_BASE					( APB2PERIPH_BASE + 0x3000 )
#define SYSCFG_BASE					( APB2PERIPH_BASE + 0x3800 )
#define USART1_BASE					( APB2PERIPH_BASE + 0x1000 )
#define USART6_BASE					( APB2PERIPH_BASE + 0x1400 )


/*
 * ******************* peripheral register definition structures *******************
 */
typedef struct //GPIO_RegDef_t // generic structure for all GPIOs
{
	volatile uint32_t MODER;		// GPIO port mode register		// Address offset = 0x00
	volatile uint32_t OTYPER;									    // Address offset = 0x04
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;									// Address offset = 0x20, 0x24
	volatile uint32_t AFR[2]; // array -- AFR[0] = GPIO alternate function low register,
					          //		  AFR[1] = GPIO alternate function high register
//	uint32_t AFRL;
//	uint32_t AFRH;
}GPIO_RegDef_t; // generic structure for all GPIOs


typedef struct //USART_RegDef_t // generic structure for all USARTx
{
	volatile uint32_t STATUS_REG;
	volatile uint32_t DATA_REG;
	volatile uint32_t BAUDRATE_REG;
	volatile uint32_t CONFIG_REG1;
	volatile uint32_t CONFIG_REG2;
	volatile uint32_t CONFIG_REG3;
	volatile uint32_t GAURDTIME_PRESCALAR_REG;
}USART_RegDef_t; // generic structure for all USARTx


typedef struct //I2C_RegDef_t // generic structure for all I2Cx
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
	volatile uint32_t I2C_FLTR;
}I2C_RegDef_t; // generic structure for all I2Cx


typedef struct {
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
} SPI_RegDef_t;


typedef struct // RCC_RegDef_t
{
	volatile uint32_t CR;		// Address offset = 0x00
	volatile uint32_t PLLCFGR;  // Address offset = 0x04
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR; // Address offset = 0x10
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t Reserved_1;
	volatile uint32_t APB1RSTR; // Address offset = 0x20
	volatile uint32_t APB2RSTR;
	uint32_t Reserved_2; //can also be an array - Reserved_2[2]
	uint32_t Reserved_3;
	volatile uint32_t AHB1ENR; // Address offset = 0x30
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t Reserved_4;
	volatile uint32_t APB1ENR; // Address offset = 0x40
	volatile uint32_t APB2ENR;
	uint32_t Reserved_5;
	uint32_t Reserved_6;
	volatile uint32_t AHB1LPENR; // Address offset = 0x50
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t Reserved_7;
	volatile uint32_t APB1LPENR; // Address offset = 0x60
	volatile uint32_t APB2LPENR;
	uint32_t Reserved_8;
	uint32_t Reserved_9;
	volatile uint32_t BDCR;		// Address offset = 0x70
	volatile uint32_t CSR;
	uint32_t Reserved_10;
	uint32_t Reserved_11;
	volatile uint32_t SSCGR;	// Address offset = 0x80
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
}RCC_RegDef_t;


typedef struct //EXTI_RegDef_t // generic structure for EXTI
{
	volatile uint32_t EXTI_IMR   ;
	volatile uint32_t EXTI_EMR   ;
	volatile uint32_t EXTI_RTSR  ;
	volatile uint32_t EXTI_FTSR  ;
	volatile uint32_t EXTI_SWIER ;
	volatile uint32_t EXTI_PR    ;
}EXTI_RegDef_t; // generic structure for EXTI


typedef struct //SYSCFG_RegDef_t // generic structure for SYSCFG
{
	volatile uint32_t SYSCFG_MEMRMP		;
	volatile uint32_t SYSCFG_PMC        ;
	volatile uint32_t SYSCFG_EXTICR[4]    ;
//	volatile uint32_t SYSCFG_EXTICR2    ;
//	volatile uint32_t SYSCFG_EXTICR3    ;
//	volatile uint32_t SYSCFG_EXTICR4    ;
	uint32_t Reserved_1;
	uint32_t Reserved_2;
	volatile uint32_t SYSCFG_CMPCR      ;
}SYSCFG_RegDef_t; // generic structure for all SYSCFG


////////////////////////////////////////////////////////////////
/*
 * peripheral definitions - peripheral base addresses type-casted to <xxxx_RegDef_t>
 */
#define GPIOA 			(	(GPIO_RegDef_t*) GPIOA_BASE		)
#define GPIOB 			( 	(GPIO_RegDef_t*) GPIOB_BASE 	)
#define GPIOC 			( 	(GPIO_RegDef_t*) GPIOC_BASE 	)
#define GPIOD 			( 	(GPIO_RegDef_t*) GPIOD_BASE 	)
#define GPIOE 			( 	(GPIO_RegDef_t*) GPIOE_BASE 	)
#define GPIOF 			( 	(GPIO_RegDef_t*) GPIOF_BASE 	)
#define GPIOG 			( 	(GPIO_RegDef_t*) GPIOG_BASE 	)
#define GPIOH 			( 	(GPIO_RegDef_t*) GPIOH_BASE 	)
#define GPIOI 			( 	(GPIO_RegDef_t*) GPIOI_BASE		)
// Analogy & Example use-case:
// uint32_t *ptr 		 = (	(uint32_t*) 0x20000000		)
// GPIO_RegDef_t *pGPIOA = (	(GPIO_RegDef_t*) GPIOA_BASE	)

#define USART1 			(	(USART_RegDef_t*) USART1_BASE	)
#define USART2 			( 	(USART_RegDef_t*) USART2_BASE 	)
#define USART3 			( 	(USART_RegDef_t*) USART3_BASE 	)
#define UART4 			( 	(USART_RegDef_t*) UART4_BASE 	)
#define UART5 			( 	(USART_RegDef_t*) UART5_BASE 	)
#define USART6 			( 	(USART_RegDef_t*) USART6_BASE 	)

#define I2C1 			(	(I2C_RegDef_t*) I2C1_BASE	)

#define SPI1 			(	(SPI_RegDef_t*) SPI1_BASE	)
#define SPI2 			(	(SPI_RegDef_t*) SPI2_BASE	)
#define SPI3 			(	(SPI_RegDef_t*) SPI3_BASE	)
//#define SPI4 			(	(SPI_RegDef_t*) SPI4_BASE	)

#define EXTI			(	(EXTI_RegDef_t*) EXTI_BASE	)

#define SYSCFG			(	(SYSCFG_RegDef_t*) SYSCFG_BASE	)


/*
 * Bit position definitions of I2C regs
 */
/*
 * Bit position definitions of I2C_CR1 - 0 7 8 9 10 15
 */
#define I2C_CR1_PE				0
#define I2C_CR1_NOSTRETCH		7
#define I2C_CR1_START			8
#define I2C_CR1_STOP			9
#define I2C_CR1_ACK				10
#define I2C_CR1_SWRST			15

/*
 * Bit position definitions of I2C_CR2 - 0 8 9 10
 */
#define I2C_CR1_FREQ			0
#define I2C_CR1_ITERREN			8
#define I2C_CR1_ITEVTEN			9
#define I2C_CR1_ITBUFEN			10

/*
 * Bit position definitions of I2C_SR1 -
 */
#define I2C_SR1_SB				0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADDR10			3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RXNE			6
#define I2C_SR1_TXE			7
#define I2C_SR1_BERR			8
#define I2C_SR1_ARLO			9
#define I2C_SR1_AF			10
#define I2C_SR1_OVR			11
#define I2C_SR1_TIMEOUT			14

/*
 * Bit position definitions of I2C_SR2
 */
#define I2C_SR2_MSL				0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA		2
#define I2C_SR2_GENCALL			4
#define I2C_SR2_DUALF		7

/*
 * Bit position definitions of I2C_CCR
 */
#define I2C_CCR_CCR				0
#define I2C_CCR_DUTY		14
#define I2C_CCR_FS		15






#define RCC 			(	(RCC_RegDef_t*) RCC_BASE		)


/////////////////////// Clock-Enable Macros ///////////////////////
/*
 * Clock-Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN()			( RCC->AHB1ENR |= (1<<0) )	// function
// #define GPIOA_PCLK_EN()			( RCC->AHB1ENR = RCC->AHB1ENR | (1<<0) )
#define GPIOB_PCLK_EN()			( RCC->AHB1ENR |= (1<<1) )
#define GPIOC_PCLK_EN()			( RCC->AHB1ENR |= (1<<2) )
#define GPIOD_PCLK_EN()			( RCC->AHB1ENR |= (1<<3) )
#define GPIOE_PCLK_EN()			( RCC->AHB1ENR |= (1<<4) )
#define GPIOF_PCLK_EN()			( RCC->AHB1ENR |= (1<<5) )
#define GPIOG_PCLK_EN()			( RCC->AHB1ENR |= (1<<6) )
#define GPIOH_PCLK_EN()			( RCC->AHB1ENR |= (1<<7) )
#define GPIOI_PCLK_EN()			( RCC->AHB1ENR |= (1<<8) )


/*
 * Clock-Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()			( RCC->APB1ENR |= (1<<21) )
#define I2C2_PCLK_EN()			( RCC->APB1ENR |= (1<<22) )
#define I2C3_PCLK_EN()			( RCC->APB1ENR |= (1<<23) )


/*
 * Clock-Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()			( RCC->APB2ENR |= (1<<12) )
#define SPI2_PCLK_EN()			( RCC->APB1ENR |= (1<<14) )
#define SPI3_PCLK_EN()			( RCC->APB1ENR |= (1<<15) )


/*
 * Clock-Enable Macros for UARTx peripherals
 */
#define USART1_PCLK_EN()			( RCC->APB2ENR |= (1<<4) )
#define USART2_PCLK_EN()			( RCC->APB1ENR |= (1<<17) )
#define USART3_PCLK_EN()			( RCC->APB1ENR |= (1<<18) )
#define UART4_PCLK_EN()				( RCC->APB1ENR |= (1<<19) )
#define UART5_PCLK_EN()				( RCC->APB1ENR |= (1<<20) )
#define USART6_PCLK_EN()			( RCC->APB2ENR |= (1<<5) )


/*
 * Clock-Enable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN()			( RCC->APB2ENR |= (1<<14) )


/////////////////////// Clock-Disable Macros ///////////////////////
/*
 * Clock-Disable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<0) )	// function
// #define GPIOA_PCLK_DI()			( RCC->AHB1ENR = RCC->AHB1ENR & ~(1<<0) )
#define GPIOB_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<1) )
#define GPIOC_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<2) )
#define GPIOD_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<3) )
#define GPIOE_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<4) )
#define GPIOF_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<5) )
#define GPIOG_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<6) )
#define GPIOH_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<7) )
#define GPIOI_PCLK_DI()			( RCC->AHB1ENR &= ~(1<<8) )


/*
 * Clock-Disable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()			( RCC->APB1ENR &= ~(1<<21) )
#define I2C2_PCLK_DI()			( RCC->APB1ENR &= ~(1<<22) )
#define I2C3_PCLK_DI()			( RCC->APB1ENR &= ~(1<<23) )


/*
 * Clock-Disable Macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()			( RCC->APB2ENR &= ~(1<<12) )
#define SPI2_PCLK_DI()			( RCC->APB1ENR &= ~(1<<14) )
#define SPI3_PCLK_DI()			( RCC->APB1ENR &= ~(1<<15) )


/*
 * Clock-Disable Macros for UARTx peripherals
 */
#define USART1_PCLK_DI()			( RCC->APB2ENR &= ~(1<<4) )
#define USART2_PCLK_DI()			( RCC->APB1ENR &= ~(1<<17) )
#define USART3_PCLK_DI()			( RCC->APB1ENR &= ~(1<<18) )
#define UART4_PCLK_DI()				( RCC->APB1ENR &= ~(1<<19) )
#define UART5_PCLK_DI()				( RCC->APB1ENR &= ~(1<<20) )
#define USART6_PCLK_DI()			( RCC->APB2ENR &= ~(1<<5) )


/*
 * Clock-Disable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_DI()			( RCC->APB2ENR &= ~(1<<14) )


/////////////////////// Macros to disable GPIOx peripherals ///////////////////////
#define GPIOA_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<0) ); ( RCC->AHB1RSTR &= ~(1<<0) );  }while(0)
#define GPIOB_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<1) ); ( RCC->AHB1RSTR &= ~(1<<1) );  }while(0)
#define GPIOC_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<2) ); ( RCC->AHB1RSTR &= ~(1<<2) );  }while(0)
#define GPIOD_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<3) ); ( RCC->AHB1RSTR &= ~(1<<3) );  }while(0)
#define GPIOE_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<4) ); ( RCC->AHB1RSTR &= ~(1<<4) );  }while(0)
#define GPIOF_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<5) ); ( RCC->AHB1RSTR &= ~(1<<5) );  }while(0)
#define GPIOG_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<6) ); ( RCC->AHB1RSTR &= ~(1<<6) );  }while(0)
#define GPIOH_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<7) ); ( RCC->AHB1RSTR &= ~(1<<7) );  }while(0)
#define GPIOI_PERI_RST()  			do { ( RCC->AHB1RSTR |= (1<<8) ); ( RCC->AHB1RSTR &= ~(1<<8) );  }while(0)

#define GPIOBASE_TO_PORTCODE(GPIOBASE)	(	(GPIOBASE == GPIOA) ? 0 : \
											(GPIOBASE == GPIOB) ? 1 : \
											(GPIOBASE == GPIOC) ? 2 : \
											(GPIOBASE == GPIOD) ? 3 : \
											(GPIOBASE == GPIOE) ? 4 : \
											(GPIOBASE == GPIOF) ? 5 : 0		)

/////////////////////// Macros to Reset USARTx peripherals ///////////////////////
#define USART1_PERI_RST()  			do { ( RCC->APB2RSTR |= (1<<4)  ); ( RCC->APB2RSTR &= ~(1<<4)  );  }while(0)
#define USART2_PERI_RST()  			do { ( RCC->APB1RSTR |= (1<<17) ); ( RCC->APB1RSTR &= ~(1<<17) );  }while(0)
#define USART3_PERI_RST()  			do { ( RCC->APB1RSTR |= (1<<18) ); ( RCC->APB1RSTR &= ~(1<<18) );  }while(0)
#define UART4_PERI_RST()  			do { ( RCC->APB1RSTR |= (1<<19) ); ( RCC->APB1RSTR &= ~(1<<19) );  }while(0)
#define UART5_PERI_RST()  			do { ( RCC->APB1RSTR |= (1<<20) ); ( RCC->APB1RSTR &= ~(1<<20) );  }while(0)
#define USART6_PERI_RST()  			do { ( RCC->APB2RSTR |= (1<<5)  ); ( RCC->APB2RSTR &= ~(1<<5)  );  }while(0)

/*
 * Some generic Macros
 */
#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define CLEAR 			DISABLE


//////////////////////////////////////////////////////////////
/*
 * IRQ numbers
 */
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40

//////////////////////////////////////////////////////////////


#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"
#include "stm32f407xx_usart_driver.h"
#include "stm32407xx_i2c_driver.h"

#endif /* INC_STM32F407XX_H_ */










