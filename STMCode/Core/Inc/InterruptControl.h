/*
 * InterruptControl.h
 *
 *  Created on: Sep 26, 2024
 *      Author: trevo
 */
#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include <stdint.h>

#define IRQ_BUTTON_PIN_NUM 0
#define NVIC_Bits_Per_Register 32
#define Pointer_Addition_32_Bit_Offest 8
#define EXTI0_IRQ_NUMBER 6
#define TIM3_IRQ_NUMBER 29
#define TIM2_IRQ_NUMBER 28
#define InterruptController_NVIC_xxx0 0
#define InterruptController_NVIC_xxx1 1
#define InterruptController_NVIC_xxx2 2
#define InterruptController_NVIC_xxx3 3

typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;
typedef struct{
	volatile uint32_t INTERRUPT_CR1;
	volatile uint32_t INTERRUPT_CR2;
	volatile uint32_t INTERRUPT_SMCR;
	volatile uint32_t INTERRUPT_DIER;
	volatile uint32_t INTERRUPT_SR;
	volatile uint32_t INTERRUPT_EGR;
	volatile uint32_t INTERRUPT_CCMR1;
	volatile uint32_t INTERRUPT_CCMR2;
	volatile uint32_t INTERRUPT_CCER;
	volatile uint32_t INTERRUPT_CNT;
	volatile uint32_t INTERRUPT_PSC;
	volatile uint32_t INTERRUPT_ARR;
	volatile uint32_t INTERRUPT_Reserved1;
	volatile uint32_t INTERRUPT_CCR1;
	volatile uint32_t INTERRUPT_CCR2;
	volatile uint32_t INTERRUPT_CCR3;
	volatile uint32_t INTERRUPT_CCR4;
	volatile uint32_t INTERRUPT_Reserved2;
	volatile uint32_t INTERRUPT_DCR;
	volatile uint32_t INTERRUPT_DMAR;
	volatile uint32_t INTERRUPT_OR;
}GPTIMR_RegDef_t;

#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100)
#define NVIC_ICER0 ((volatile uint32_t*) 0XE000E180)
#define NVIC_ISPR0 ((volatile uint32_t*) 0XE000E200)
#define NVIC_ICPR0 ((volatile uint32_t*) 0XE000E280)
#define APB2_BUS_BASE_ADDR 0x40010000
#define APB1_BUS_BASE_ADDR 0x40000000
#define EXTI_BASE_ADDR (APB2_BUS_BASE_ADDR+0x3C00)
#define INTERRUPT_EXTI ((EXTI_RegDef_t*) EXTI_BASE_ADDR)
#define TIM2_BASE_ADDR APB1_BUS_BASE_ADDR
#define TIM3_BASE_ADDR (APB1_BUS_BASE_ADDR+0x400)

#define INTERRUPT_TIM2 ((GPTIMR_RegDef_t*) TIM2_BASE_ADDR)
#define INTERRUPT_TIM3 ((GPTIMR_RegDef_t*) TIM3_BASE_ADDR)

void IRQ_Enable (uint8_t);
void IRQ_Disable (uint8_t);
void IRQ_Clear_Pending (uint8_t);
void IRQ_Set_Pending (uint8_t);
void EXTI_Clear_Pending (uint8_t);
void TIMR_Clear_Pending(GPTIMR_RegDef_t *);
void TIMR_Mask_IRQ(GPTIMR_RegDef_t * TIMRx);
void TIMR_Unmask_IRQ(GPTIMR_RegDef_t * TIMRx);
#endif /* INTERRUPTCONTROL_H_ */
