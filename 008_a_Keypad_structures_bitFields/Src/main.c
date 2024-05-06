/*
 * main_2.c
 *
 *  Created on: Jul 7, 2022
 *      Author: MY PC
 */

#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define RCC    0x40023800
#define GPIO_D 0x40020C00

/* --------------------Approx. delay value calculation--------------------
 * Processor is at 16MHz internal RC osc.
 * Assume 1 instr. takes 1 clk cycle to execute
 * 1 instr. takes 0.0625 micro seconds
 * For 1 iteration of the 'for' loop, it takes 7 instructions
 * 7 instr.  = 7 x 0.0625 = 0.4375 ~= 0.5 micro seconds
 *
 * Therefore, 0.5 micro seconds --> 1 iteration of the 'for' loop
 * 			  150 milli seconds --> 300,000 iterations
 */
#define DELAY 300000
void delay(void)	{
	for(uint32_t i=0; i<DELAY; i++);
}


int main(void)
{

	RCC_AHB1ENR_t* pRCC_AHB1ENR = (RCC_AHB1ENR_t*) (RCC + 0x30);

	GPIOx_MODER_t* pGPIOD_MODER = (GPIOx_MODER_t*) (GPIO_D + 0x0);
	GPIOx_PUPDR_t* pGPIOD_PUPDR = (GPIOx_PUPDR_t*) (GPIO_D + 0x0C);
	GPIOx_IDR_t*   pGPIOD_IDR   = (GPIOx_IDR_t*)   (GPIO_D + 0x10);
	GPIOx_ODR_t*   pGPIOD_ODR   = (GPIOx_ODR_t*)   (GPIO_D + 0x14);

	//Enable clk for GPIO-D peripheral in RCC_AHB1ENR
	pRCC_AHB1ENR -> gpioD_en = 1;


	//Keep all Col gpios in i/p mode & all Row gpios in o/p mode
	//C1,2,3,4 - PD0,1,2,3 - i/p
	//R1,2,3,4 - PD8,9,10,11 - o/p
	pGPIOD_MODER -> pin_0 = 0x0;
	pGPIOD_MODER -> pin_1 = 0x0;
	pGPIOD_MODER -> pin_2 = 0x0;
	pGPIOD_MODER -> pin_3 = 0x0;

	pGPIOD_MODER -> pin_8  = 0x1;
	pGPIOD_MODER -> pin_9  = 0x1;
	pGPIOD_MODER -> pin_10 = 0x1;
	pGPIOD_MODER -> pin_11 = 0x1;

	//Enable pull-up registers for C1-4
	pGPIOD_PUPDR -> pin_0 = 0x1;
	pGPIOD_PUPDR -> pin_1 = 0x1;
	pGPIOD_PUPDR -> pin_2 = 0x1;
	pGPIOD_PUPDR -> pin_3 = 0x1;

	while(1)	{

		//Make all Row gpios HIGH
		pGPIOD_ODR -> pin_8  = 0x1;
		pGPIOD_ODR -> pin_9  = 0x1;
		pGPIOD_ODR -> pin_10 = 0x1;
		pGPIOD_ODR -> pin_11 = 0x1;

		//R1=LOW, rest=HIGH
		pGPIOD_ODR -> pin_8  = 0x0;
		pGPIOD_ODR -> pin_9  = 0x1;
		pGPIOD_ODR -> pin_10 = 0x1;
		pGPIOD_ODR -> pin_11 = 0x1;
		//Read C1
		if( !(pGPIOD_IDR->pin_0) )	{
			delay();
			printf("Key pressed is: S1\n");
		}
		//Read C2
		if( !(pGPIOD_IDR->pin_1) )	{
			delay();
			printf("Key pressed is: S2\n");
		}
		//Read C3
		if( !(pGPIOD_IDR->pin_2) )	{
			delay();
			printf("Key pressed is: S3\n");
		}
		//Read C4
		if( !(pGPIOD_IDR->pin_3) )	{
			delay();
			printf("Key pressed is: S4\n");
		}


		//R2=LOW, rest=HIGH
		pGPIOD_ODR -> pin_8  = 0x1;
		pGPIOD_ODR -> pin_9  = 0x0;
		pGPIOD_ODR -> pin_10 = 0x1;
		pGPIOD_ODR -> pin_11 = 0x1;
		//Read C1
		if( !(pGPIOD_IDR->pin_0) )	{
			delay();
			printf("Key pressed is: S5\n");
		}
		//Read C2
		if( !(pGPIOD_IDR->pin_1) )	{
			delay();
			printf("Key pressed is: S6\n");
		}
		//Read C3
		if( !(pGPIOD_IDR->pin_2) )	{
			delay();
			printf("Key pressed is: S7\n");
		}
		//Read C4
		if( !(pGPIOD_IDR->pin_3) )	{
			delay();
			printf("Key pressed is: S8\n");
		}


		//R3=LOW, rest=HIGH
		pGPIOD_ODR -> pin_8  = 0x1;
		pGPIOD_ODR -> pin_9  = 0x1;
		pGPIOD_ODR -> pin_10 = 0x0;
		pGPIOD_ODR -> pin_11 = 0x1;
		//Read C1
		if( !(pGPIOD_IDR->pin_0) )	{
			delay();
			printf("Key pressed is: S9\n");
		}
		//Read C2
		if( !(pGPIOD_IDR->pin_1) )	{
			delay();
			printf("Key pressed is: S10\n");
		}
		//Read C3
		if( !(pGPIOD_IDR->pin_2) )	{
			delay();
			printf("Key pressed is: S11\n");
		}
		//Read C4
		if( !(pGPIOD_IDR->pin_3) )	{
			delay();
			printf("Key pressed is: S12\n");
		}


		//R4=LOW, rest=HIGH
		pGPIOD_ODR -> pin_8  = 0x1;
		pGPIOD_ODR -> pin_9  = 0x1;
		pGPIOD_ODR -> pin_10 = 0x1;
		pGPIOD_ODR -> pin_11 = 0x0;
		//Read C1
		if( !(pGPIOD_IDR->pin_0) )	{
			delay();
			printf("Key pressed is: S13\n");
		}
		//Read C2
		if( !(pGPIOD_IDR->pin_1) )	{
			delay();
			printf("Key pressed is: S14\n");
		}
		//Read C3
		if( !(pGPIOD_IDR->pin_2) )	{
			delay();
			printf("Key pressed is: S15\n");
		}
		//Read C4
		if( !(pGPIOD_IDR->pin_3) )	{
			delay();
			printf("Key pressed is: S16\n");
		}

	}//while(1) end




}//main() end
