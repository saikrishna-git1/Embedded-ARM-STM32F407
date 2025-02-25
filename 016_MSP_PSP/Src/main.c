/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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

#define SRAM_START 0x20000000
#define SRAM_SIZE  (128*1024)
#define SRAM_END   ( (SRAM_START) + (SRAM_SIZE) ) //why separate paranthesis //change and check

#define STACK_START SRAM_END
#define STACK_MSP_START STACK_START
#define STACK_MSP_END (STACK_MSP_START - 512)
#define STACK_PSP_START STACK_MSP_END



__attribute__((naked)) void change_SP_to_PSP(void) {
	//__asm volatile("LDR R0, =STACK_PSP_START"); //can't use C-macro in asm instr.
	__asm volatile(".equ SRAM_END, (0x20000000 + (128*1024) )");
	__asm volatile(".equ STACK_PSP_START, (SRAM_END-512)");
	__asm volatile("LDR R0, =STACK_PSP_START");//can't use MOV here coz its 32-bit value. To use MOV, value has to be 16-bit
	__asm volatile("MSR PSP, R0"); //PSP is initialized now
	__asm volatile("MOV R0, 0x02"); //use CONTROL reg bit[1]--SPSEL, to change SP from MSP to PSP
	__asm volatile("MSR CONTROL, R0");
	__asm volatile("BX LR"); //return instr. for control to go back to the main function //BX -- branch indirect
}

void generate_exception(void) {
	__asm volatile("SVC #0x2"); //SVC exception covered later //SVC instr. can be executed by Thread-mode code in order to get some services from Kernel-level code
	//when Thread-mode executes this, SVC exception will be triggered and SVC handler will be called
}

int func_add(int a, int b, int c, int d) {
    return a+b+c+d;
}


int main(void) {

	change_SP_to_PSP();

	int res;

    res = func_add(1, 4, 6, 9);
   	printf("Result = %d\n", res);

    generate_exception();

	/* Loop forever */
	for(;;);

}


void SVC_Handler(void) {
	printf("In SVC hanlder\n");
}
