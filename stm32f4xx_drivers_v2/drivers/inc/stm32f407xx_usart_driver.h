/*
 * stm32f407xx_usart_driver.h
 *
 *  Created on: Nov 21, 2022
 *      Author: MY PC
 */

#ifndef INC_STM32F407XX_USART_DRIVER_H_
#define INC_STM32F407XX_USART_DRIVER_H_

#include "stm32f407xx.h"

/*
 *********** Configuration structure for USART peri ***********
 */
typedef struct // USART_Config_t
{
	uint8_t  USART_Mode; //
	uint32_t USART_Baud; //
	uint8_t  USART_NoOfStopBits; //
	uint8_t  USART_WordLength; //
	uint8_t  USART_ParityControl; // possible values from @
	uint8_t  USART_HwFlowControl; //
}USART_Config_t;


/*
 *********** Handle structure for USART peri ***********
 */
typedef struct // USART_Handle_t // Contains USARTx peri base-addr & config settings
{
	USART_RegDef_t *pUSARTx;
	USART_Config_t USART_Config; // This holds USARTx's configuration settings
}USART_Handle_t;


/********************************************************************************
 *				APIs supported by this driver
 *	For more info on APIs, check the function definitions
 ********************************************************************************/

/*
 * Peripheral clock control
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);


/*
 * Init and DeInit
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);


/*
 * Data Send and Receive
 */
void USART_SendData(USART_RegDef_t *pUSARTx, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_RegDef_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len);
uint8_t SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);


/*
 * USART_Handle_t *pUSARTHandle
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);


/*
 * IRQ Config and Handling
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSARTHandle);


#endif /* INC_STM32F407XX_USART_DRIVER_H_ */
