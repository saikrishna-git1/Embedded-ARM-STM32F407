/*
 * main.h
 *
 *  Created on: Dec 24, 2023
 *      Author: MY PC
 */

#ifndef MAIN_H_
#define MAIN_H_

#define TICK_RATE				1000U
#define HSI_CLOCK				16000000U
#define SYSTICK_TIM_CLK			HSI_CLOCK

#define MAX_TASKS				4

//Reserving stack areas and defining stack boundaries
#define SIZE_TASK_STACK			1024U
#define SIZE_SCHD_STACK			1024U

#define SRAM_START				0x20000000U
#define SIZE_SRAM				( (128) * (1024) )
#define SRAM_END				( (SRAM_START) + (SIZE_SRAM) )

#define T1_STACK_START			( (SRAM_END) - (SIZE_TASK_STACK) )	//Reserving 1KB of stack for main()
#define T2_STACK_START			( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T3_STACK_START			( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define T4_STACK_START			( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHD_STACK_START		( (SRAM_END) - (5 * SIZE_TASK_STACK) )

#define DUMMY_XPSR				0x01000000U
#define DUMMY_LR_EXC_RETURN		0xFFFFFFFDU

#endif /* MAIN_H_ */
