/*
 * stm32407xx_i2c_driver.h
 *
 *  Created on: Jan 15, 2023
 *      Author: MY PC
 */

#ifndef INC_STM32407XX_I2C_DRIVER_H_
#define INC_STM32407XX_I2C_DRIVER_H_

#include "stm32f407xx.h"


/*
 *********** Configuration structure for I2C ***********
 */
typedef struct // I2C_Config_t
{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress; //mentioned by user; no init options for this
	uint8_t  I2C_ACKControl;
	uint8_t I2C_FMDutyCycle;
}I2C_Config_t;


/*
 *********** Handle structure for I2C ***********
 */
typedef struct // I2C_Handle_t // Contains I2Cx peri base-addr & config settings
{
	I2C_RegDef_t *pI2Cx;
	I2C_Config_t I2C_Config; // This holds I2Cx's configuration settings
}I2C_Handle_t;


/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM	 100000
#define I2C_SCL_SPEED_FM400K 400000
#define I2C_SCL_SPEED_FM200K 200000

/*
 * @I2C_ACKControl
 */
#define I2C_ACK_ENABLE		1
#define I2C_ACK_DISABLE		0

/*
 * @I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2		0
#define I2C_FM_DUTY_16_9	1


/*
 * ********************** APIs supported by this driver **********************
 *
 */
/*
 * Peripheral clock setup
 */
void I2C_PClk_Ctrl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

/*
 * Init & DeInit
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * Data send and receive
 */



/*
 * I2C peripheral control APIs
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);




#endif /* INC_STM32407XX_I2C_DRIVER_H_ */
