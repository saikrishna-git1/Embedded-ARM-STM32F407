/*
 * main_button.c
 *
 *  Created on: Jun 26, 2022
 *      Author: MY PC
 */

#include <stdint.h>
#include <stdio.h>


int main(void)
{
    //PG13 - LED1
	uint32_t* pClkCtrlReg   = (uint32_t* ) 0x40023830;
    uint32_t* pPortDModeReg = (uint32_t* ) 0x40021800;
    uint32_t* pPortDOutReg  = (uint32_t* ) 0x40021814;

    //PA0 - B1
    uint32_t* pPortAModeReg = (uint32_t* ) 0x40020000;
    uint32_t const volatile *const pPortAInReg   = (uint32_t* ) 0x40020010;


    //Enable clk for GPIO-D and A peripheral in RCC_AHB1ENR
    *pClkCtrlReg |= (1<<6);	//LED1
    *pClkCtrlReg |= (1<<0);	//B1

    //Configure PG13 as OP
    //a. Clear [27:26] bits ??
    *pPortDModeReg &= ~(1<<27);
    //b. Set 26 bit
    *pPortDModeReg |= (1<<26);

    //Configure PA0 as i/p
    *pPortAModeReg &= ~(3<<0);


    //Assign i/p to o/p
    while(1)	{
    	//Read the status of PA0
    	uint8_t PA0_status = (uint8_t) *pPortAInReg & 0x01;
    	if(PA0_status)
    		*pPortDOutReg |= (1<<13);
    	else
    		*pPortDOutReg &= ~(1<<13);
    }



    //while(1);


}


