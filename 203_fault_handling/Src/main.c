/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

int main(void)
{
	//1. Enable the faults in SCB->SHCSR
	uint32_t *pSHCSR = (uint32_t *) 0xE000ED24;
	*pSHCSR |= (1 << 16); //MM F
	*pSHCSR |= (1 << 17); //Bus F
	*pSHCSR |= (1 << 18); //Usage F

	//2. Write fault handler functions

	//3. Force the p. to execute invalid instr.
	uint32_t* pInvalidInstr = (uint32_t *) 0x20010000;
	*pInvalidInstr = 0xFFFFFFFF;

	//__asm volatile("LDR PC, =0x20010001");

	void (*some_addr) (void);
	some_addr = (void *)0x20010000;
	some_addr();

	for(;;);
}


__attribute__((naked)) void UsageFault_Handler(void) { //asm handler
	__asm volatile("TST LR, #0x4"); //Test bit[2] of EXC_RETURN
	__asm volatile("ITE EQ"); //if MSP -> bit[2]=0 -> 0&1=0 -> Z=1 -> EQ
	__asm volatile("MRSEQ R0, MSP");
	__asm volatile("MRSNE R0, PSP");
	__asm volatile("MOV R1, LR");
	__asm volatile("B UsageFault_Handler_C");
}


void UsageFault_Handler_C(uint32_t *pBaseStackFrame, uint32_t excReturn) { //C handler
	printf("In UsageFaultHandler\n");

	uint16_t* pUFSR = (uint16_t *) 0xE000ED2A;
	printf("UFSR = 0x%x\n", *pUFSR);

#if 1
	printf("pBaseStackFrame = %p\n", pBaseStackFrame);
	printf("excReturn = 0x%lx\n", excReturn);

	printf("Stack frame:\n");
	printf("R0 = 0x%lx\n", pBaseStackFrame[0]);
	printf("R1 = 0x%lx\n", pBaseStackFrame[1]);
	printf("R2 = 0x%lx\n", pBaseStackFrame[2]);
	printf("R3 = 0x%lx\n", pBaseStackFrame[3]);
	printf("R12 = 0x%lx\n", pBaseStackFrame[4]);
	printf("LR = 0x%lx\n", pBaseStackFrame[5]);
	printf("PC = 0x%lx\n", pBaseStackFrame[6]);
	printf("xPSR = 0x%lx\n", pBaseStackFrame[7]);
	printf("------------------------------------\n");
#endif
	printf("FSR/FAR:\n");
	while(1);
}
