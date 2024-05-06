/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: Jan 15, 2023
 *      Author: MY PC
 */


void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
		pI2Cx->I2C_CR1 |= (1 << I2C_CR1_PE);
		//pI2C_BaseAddress->CR1 |= I2C_CR1_PE_Bit_Mask;
	else
		pI2Cx->I2C_CR1 &= ~(1 << 0);
}



void I2C_PClk_Ctrl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
	if( EnOrDi == ENABLE ) // ??alt - switch st. and typecasting - onenote
	{
			 if(pI2Cx == I2C1)
				I2C1_PCLK_EN();

		else if(pI2Cx == I2C2)
				I2C2_PCLK_EN();

		else if(pI2Cx == I2C3)
				I2C3_PCLK_EN();
	}
	else
	{
		 	 if(pI2Cx == I2C1)
		 		 I2C1_PCLK_DI();

		else if(pI2Cx == I2C2)
		 		 I2C2_PCLK_DI();

		else if(pI2Cx == I2C3)
		 		 I2C3_PCLK_DI();
	}

}



/*
 ***************************** Init & DeInit *****************************
 */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;

	//ack control bit
	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << 10;
	pI2CHandle->pI2Cx->I2C_CR1 = tempreg;

	//configure FREQ field of CCR reg
	//tempreg = 0;
	pI2CHandle->pI2Cx->I2C_CR2 = 16;

	//program device own address


	//CCR calculations - need to be updated
	pI2CHandle->pI2Cx->I2C_CCR = 0x50;

}






