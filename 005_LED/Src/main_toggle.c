/*
 * main_toggle.c
 *
 *  Created on: Jun 25, 2022
 *      Author: MY PC
 */

#include <stdint.h>
#include <stdio.h>


int main(void)
{
    uint32_t* pClkCtrlReg   = (uint32_t* ) 0x40023830;
    uint32_t* pPortDModeReg = (uint32_t* ) 0x40021800;
    uint32_t* pPortDOutReg  = (uint32_t* ) 0x40021814;

    //1. Enable clk for GPIO-D peripheral in RCC_AHB1ENR
    *pClkCtrlReg |= (1<<6);

    //2. Configure the mode of the IO pin as OP
    //a. Clear [27:26] bits ??
    *pPortDModeReg &= ~(1<<27);
    //b. Set 26 bit
    *pPortDModeReg |= (1<<26);

    //3. Toggle 13 bit of ODR to make PG13-LED (Green)
    //*pPortDOutReg |= (1<<13);
    while(1)	{
    	for(uint32_t i=300000; i>0 ; i--);
    	*pPortDOutReg ^= (1<<13);
    }



    //while(1);


}

