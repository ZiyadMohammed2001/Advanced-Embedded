/*
 * Systic.c
 *
 *  Created on: Jul 2, 2023
 *      Author: Ziyad
 */

#include <stdint.h>
#include "Stm32f446.h"
#include "ErrType.h"

#include "Systic_interface.h"
#include "Systic_Config.h"
#include "Systic_prv.h"

uint8_t SysTick_u8_Delay_ms(const Systic_Config_t* Systic_Config)
{
	uint8_t		Local_u8ErrorState = OK;
	uint32_t	Local_u32NumberOfCounts = 0;
	uint32_t	Local_u32NumberOfUnderflow = 0;

	if(Systic_Config != NULL)
	{

	if (Local_u32NumberOfUnderflow == 0)
	{
		/*Select SysTick Source*/
		SysTick_REG->STK_CTRL &= ~(SYST_MASK << STK_CTRL_CLKSOURCE);
		SysTick_REG->STK_CTRL |= ( Systic_Config -> Systic_CLKSource << STK_CTRL_CLKSOURCE);/*Select processor clock divided by 8 or not*/
		/*Disable exception*/
		SysTick_REG->STK_CTRL &= ~(SYST_MASK << STK_CTRL_TICKINT);
	}

	/*Transform milli second to ticks */
	uint32_t Local_u32_NumberOfTicks = ((Systic_Config -> Time) *(SYSTIC_CLK_USED/SYST_MILLISECOUND_DIVITION_FACTROR)); /*8MHz means 1.25*10^-7(1/8MHz) Sec for tick*/
	if (!(SysTick_REG->STK_CTRL && (SYST_MASK << STK_CTRL_TICKINT)))
	{
		Local_u32_NumberOfTicks = Local_u32_NumberOfTicks / 8;
	}
	/*Case NumberOfTicks <= Copy_u32Time_ms*/
	if (Local_u32_NumberOfTicks <= (Systic_Config -> Time))
		{
			/*Store Preload Value*/
			SysTick_REG->STK_LOAD = (Local_u32_NumberOfTicks);
			Local_u32NumberOfCounts++;
		}
	else if (Local_u32_NumberOfTicks > (Systic_Config -> Time))
		{
			Local_u32NumberOfCounts = (Local_u32_NumberOfTicks / SYST_DELAY_LIMIT_US_8MHz);
			SysTick_REG->STK_LOAD = (Local_u32_NumberOfTicks - (SYST_DELAY_LIMIT_US_8MHz * Local_u32NumberOfCounts));
			Local_u32NumberOfCounts++;
		}
	/*Enable Systic clock*/
	SysTick_REG->STK_CTRL |= (SYST_MASK << STK_CTRL_ENABLE);
	/*Check Count Flag*/
	while (((SysTick_REG ->STK_CTRL) << STK_CTRL_COUNTFLAG) != SYST_MASK); /*Wait till finished. */
	if (Local_u32NumberOfCounts != Local_u32NumberOfUnderflow)
	{
		Local_u32NumberOfUnderflow++;
		Systic_Config_t CallAgain=
		{
				.Time = (SYST_DELAY_LIMIT_US_8MHz/((SYSTIC_CLK_USED/SYST_MILLISECOUND_DIVITION_FACTROR))),
				.Systic_CLKSource = (Systic_Config -> Systic_CLKSource)
		};
		SysTick_u8_Delay_ms (&CallAgain) ;
	}
	/*Disable Systic clock*/
	SysTick_REG->STK_CTRL &= ~(SYST_MASK << STK_CTRL_ENABLE);
	Local_u32NumberOfCounts = SYST_DISABLE;
	Local_u32NumberOfUnderflow = SYST_DISABLE;
	SysTick_REG->STK_LOAD = SYST_DISABLE;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return	Local_u8ErrorState ;
}
uint8_t SysTick_u8_Delay_us(const Systic_Config_t* Systic_Config)
{
	uint8_t		Local_u8ErrorState = OK;
	uint32_t	Local_u32NumberOfCounts = 0;
	uint32_t	Local_u32NumberOfUnderflow = 0;

	if(Systic_Config != NULL)
	{

	if (Local_u32NumberOfUnderflow == 0)
	{
		/*Select SysTick Source*/
		SysTick_REG->STK_CTRL &= ~(SYST_MASK << STK_CTRL_CLKSOURCE);
		SysTick_REG->STK_CTRL |= ( Systic_Config -> Systic_CLKSource << STK_CTRL_CLKSOURCE);/*Select processor clock divided by 8 or not*/
		/*Disable exception*/
		SysTick_REG->STK_CTRL &= ~(SYST_MASK << STK_CTRL_TICKINT);
	}

	/*Transform milli second to ticks */
	uint32_t Local_u32_NumberOfTicks = ((Systic_Config -> Time) *(SYSTIC_CLK_USED/SYST_MICREOSECOUND_DIVITION_FACTROR)); /*8MHz means 1.25*10^-7(1/8MHz) Sec for tick*/
	if (!(SysTick_REG->STK_CTRL && (SYST_MASK << STK_CTRL_TICKINT)))
	{
		Local_u32_NumberOfTicks = Local_u32_NumberOfTicks / 8;
	}
	/*Case NumberOfTicks <= Copy_u32Time_ms*/
	if (Local_u32_NumberOfTicks <= (Systic_Config -> Time))
		{
			/*Store Preload Value*/
			SysTick_REG->STK_LOAD = (Local_u32_NumberOfTicks);
			Local_u32NumberOfCounts++;
		}
	else if (Local_u32_NumberOfTicks > (Systic_Config -> Time))
		{
			Local_u32NumberOfCounts = (Local_u32_NumberOfTicks / SYST_DELAY_LIMIT_US_8MHz);
			SysTick_REG->STK_LOAD = (Local_u32_NumberOfTicks - (SYST_DELAY_LIMIT_US_8MHz * Local_u32NumberOfCounts));
			Local_u32NumberOfCounts++;
		}
	/*Enable Systic clock*/
	SysTick_REG->STK_CTRL |= (SYST_MASK << STK_CTRL_ENABLE);
	/*Check Count Flag*/
	while (((SysTick_REG ->STK_CTRL) << STK_CTRL_COUNTFLAG) != SYST_MASK); /*Wait till finished. */
	if (Local_u32NumberOfCounts != Local_u32NumberOfUnderflow)
	{
		Local_u32NumberOfUnderflow++;
		Systic_Config_t CallAgain=
		{
				.Time = (SYST_DELAY_LIMIT_US_8MHz/((SYSTIC_CLK_USED/SYST_MICREOSECOUND_DIVITION_FACTROR))),
				.Systic_CLKSource = (Systic_Config -> Systic_CLKSource)
		};
		SysTick_u8_Delay_ms (&CallAgain) ;
	}
	/*Disable Systic clock*/
	SysTick_REG->STK_CTRL &= ~(SYST_MASK << STK_CTRL_ENABLE);
	Local_u32NumberOfCounts = SYST_DISABLE;
	Local_u32NumberOfUnderflow = SYST_DISABLE;
	SysTick_REG->STK_LOAD = SYST_DISABLE;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return	Local_u8ErrorState ;
}
