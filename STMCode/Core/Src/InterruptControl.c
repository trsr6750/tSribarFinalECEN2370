/*
 * InterruptControl.c
 *
 *  Created on: Sep 26, 2024
 *      Author: trevo
 */

#include <InterruptControl.h>

void IRQ_Enable (uint8_t IRQ_number){
	int IRQBitOffset = IRQ_number%NVIC_Bits_Per_Register;
	int NIVCregisterNumber = IRQ_number/NVIC_Bits_Per_Register;
	*(NVIC_ISER0+NIVCregisterNumber) |= (0x1<<IRQBitOffset);
	return;

	//uint32_t * NVIC_ISERx = NVIC_ISER0 + (Pointer_Addition_32_Bit_Offest*(IRQ_number/NVIC_Bits_Per_Register));
	//NVIC_ISERx |= (0x1<<(IRQ_number%NVIC_Bits_Per_Register));
}
void IRQ_Disable (uint8_t IRQ_number){
	//uint32_t * NVIC_ICERx = NVIC_ICER0 + Pointer_Addition_32_Bit_Offest*IRQ_number/NVIC_Bits_Per_Register;
	//NVIC_ICERx |= (0x1<<(IRQ_number%NVIC_Bits_Per_Register));
	int IRQBitOffset = IRQ_number%NVIC_Bits_Per_Register;
	int NIVCregisterNumber = IRQ_number/NVIC_Bits_Per_Register;
	*(NVIC_ICER0+NIVCregisterNumber) |= (0x1<<IRQBitOffset);
	return;
}
void IRQ_Clear_Pending (uint8_t IRQ_number){
	//uint32_t * NVIC_ISPRx = NVIC_ISPR0 + Pointer_Addition_32_Bit_Offest*(IRQ_number/NVIC_Bits_Per_Register);
	//NVIC_ISPRx |= (0x1<<(IRQ_number%NVIC_Bits_Per_Register));
	int IRQBitOffset = IRQ_number%NVIC_Bits_Per_Register;
	int NIVCregisterNumber = IRQ_number/NVIC_Bits_Per_Register;
	*(NVIC_ISPR0+NIVCregisterNumber) |= (0x1<<IRQBitOffset);
	return;
}
void IRQ_Set_Pending (uint8_t IRQ_number){
	//uint32_t * NVIC_ICPRx = NVIC_ICPR0 + Pointer_Addition_32_Bit_Offest*(IRQ_number/NVIC_Bits_Per_Register);
	//NVIC_ICPRx |= (0x1<<(IRQ_number%NVIC_Bits_Per_Register));
	int IRQBitOffset = IRQ_number%NVIC_Bits_Per_Register;
	int NIVCregisterNumber = IRQ_number/NVIC_Bits_Per_Register;
	*(NVIC_ICPR0+NIVCregisterNumber) |= (0x1<<IRQBitOffset);
	return;
}
void EXTI_Clear_Pending (uint8_t pinNumber){
	INTERRUPT_EXTI->PR |= (0x1<<pinNumber);
}
void TIMR_Clear_Pending(GPTIMR_RegDef_t * TIMRx){
	TIMRx->INTERRUPT_SR &= ~(0x1);
}
void TIMR_Mask_IRQ(GPTIMR_RegDef_t * TIMRx){
	TIMRx->INTERRUPT_DIER &= ~(0x1);
}
void TIMR_Unmask_IRQ(GPTIMR_RegDef_t * TIMRx){
	TIMRx->INTERRUPT_DIER |= (0x1);
}
