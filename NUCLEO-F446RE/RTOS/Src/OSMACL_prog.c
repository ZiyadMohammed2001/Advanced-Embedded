#include <OSMCAL_cfg.h>
#include <OSMCAL_interface.h>
#include <stdint.h>
#include "Stm32f446.h"

__attribute__ ((naked)) void Stack_voidSchedulerStackInit(uint32_t Copy_u32SchedTOS)
{
	/*Can use this instead.*/
	/*__asm volatile ("MSR MSP, %0"::"r"(Copy_u32SchedTOS));*/
	__asm volatile ("MSR MSP , R0");

	__asm volatile ("BX LR");
}

void STK_voidInit(uint32_t Copy_u32TickHz)
{
	/*Calculate the required Number of tick.*/
	uint32_t Local_u32ReloadVal = SYSTICK_TIM_CLK / Copy_u32TickHz;

	/*Decrement by one to consider the Multi-Shot Timer*/
	Local_u32ReloadVal--;

	SysTick_REG ->STK_LOAD = Local_u32ReloadVal;

	/*Enable Systick Exception.*/
	SysTick_REG->STK_CTRL |= 1<<1;

	/*Set Clock Source.*/
	SysTick_REG->STK_CTRL |= 1<<2;

	/*Enable the Systick Timer.*/
	SysTick_REG->STK_CTRL |= 1<<0;
}

void SysTick_Handler (void)
{

}
