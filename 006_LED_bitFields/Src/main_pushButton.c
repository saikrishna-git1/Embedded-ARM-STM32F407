/*
 * main_pushButton.c
 *
 *  Created on: Jul 3, 2022
 *      Author: MY PC
 */

#include <stdint.h>
#include "main.h"

int main(void)
{
	RCC_AHB1ENR_t* pRCCAHB1ENR    = (RCC_AHB1ENR_t* ) 0x40023830;
	GPIOx_MODER_t* pGpioGMode     = (GPIOx_MODER_t* ) 0x40021800;
	GPIOx_ODR_t*   pGpioGOutData  = (GPIOx_ODR_t* )   0x40021814;
    //PA0 - B1
	GPIOx_MODER_t* pGpioAMode     = (GPIOx_MODER_t* ) 0x40020000;
	GPIOx_IDR_t const volatile *const pGpioAInData   = (GPIOx_IDR_t* )   0x40020010;

    //1. Enable clk for GPIO-D peripheral in RCC_AHB1ENR
	pRCCAHB1ENR -> gpiog_en = 1;
	pRCCAHB1ENR -> gpioa_en = 1;

    //2. Configure the mode of the IO pin as OP
    //a. Clear [27:26] bits ??
    pGpioGMode -> moder_13 = 1;
    //b. Set 26 bit
    //*pPortDModeReg |= (1<<26);

    //Configure PA0 as i/p
    pGpioAMode -> moder_0 = 0;

    //Assign i/p to o/p
    while(1)	{
        //Read the status of PA0
       	//uint8_t PA0_status = (uint8_t) (pGpioAInData -> idr_0) & 0x01;
       	if((pGpioAInData -> idr_0))
       		pGpioGOutData -> odr_13 = 1;
       	else
       		pGpioGOutData -> odr_13 = 0;
    }

}


