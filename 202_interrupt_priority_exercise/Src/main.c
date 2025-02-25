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


#define IRQNO_TIM2 28
#define IRQNO_I2C1 31

uint8_t *NVIC_IPR_BASE = (uint8_t *) 0xE000E400;

void config_irq_priority(uint8_t irq_no, uint8_t priority_value);

int main(void)
{


	config_irq_priority(IRQNO_TIM2, 0x80);
	config_irq_priority(IRQNO_I2C1, 0x80);



	/* Loop forever */
	for(;;);
}


void config_irq_priority(uint8_t irq_no, uint8_t priority_value) {
	uint8_t *nvic_ipr = NVIC_IPR_BASE + irq_no;
	*nvic_ipr = priority_value;
}









