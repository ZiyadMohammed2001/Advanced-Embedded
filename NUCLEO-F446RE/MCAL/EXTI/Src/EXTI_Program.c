/********************************************************************/
/* @file	EXTI_program.c
 * @author	Ziyad Mohammed
 * @brief	The EXTI Main Source File , Including function definitions.
 */
#include <stdint.h>
#include "Stm32f446.h"
#include "ErrType.h"

#include "EXTI_interface.h"
#include "EXTI_Config.h"
#include "EXTI_private.h"

/*Array for call back functions of external interrupt.*/
static void(*EXTI_CallBackFunc[EXTI_TOTAL_INTERRUPT])(void) = {NULL};

/*
 * @fn EXTI_u8_Init.
 * @berief	the function set configuration of external interrupt.
 * @Parameters	[in]  EXTI_Init : Initialize values of the external interrupt.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8Init (const EXTI_Init_Config_t *EXTI_Init_Config)
{
	uint8_t Local_u8ErrorState = OK;
	if (EXTI_Init_Config != NULL)
	{
		/*Setting trigger source configuration.*/
		switch ( EXTI_Init_Config -> EXTI_Trigger_Config )
		{
		case EXTI_RISING_TRIGGER:
			EXTI_REGISTER -> RTSR |= (EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum));
			EXTI_REGISTER -> FTSR &= (~(EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum)));
			break;
		case EXTI_FALLING_TRIGGER:
			EXTI_REGISTER -> FTSR |= (EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum));
			EXTI_REGISTER -> RTSR &= (~(EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum)));
			break;
		case EXTI_RISING_FALLING_TRIGGER:
		EXTI_REGISTER -> RTSR |= (EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum));
		EXTI_REGISTER -> FTSR |= (EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum));
			break;
		default:Local_u8ErrorState = NOK; break;
		}
		/*Set Interrupt enable / disable initial state.*/
		if (EXTI_ENABLE == (EXTI_Init_Config -> EXTI_InitStatus))
		{
			EXTI_REGISTER -> IMR |= (EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum));
		}
		else if (EXTI_DISABLE == (EXTI_Init_Config -> EXTI_InitStatus))
		{
			EXTI_REGISTER -> IMR &=  (~(EXTI_SET_REGISTER << (EXTI_Init_Config ->EXTI_lineNum)));
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
		/*Setting call back function pointer*/
		if (NULL != (EXTI_Init_Config->EXTI_Copy_pf))
		{
			EXTI_CallBackFunc[EXTI_Init_Config->EXTI_lineNum] = EXTI_Init_Config->EXTI_Copy_pf;
		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/*
 * @fn EXTI_u8SetTriggerSource.
 * @berief	the function set Trigger source for line of external interrupt.
 * @Parameters	[in]  EXTI_Trigger_Config : Select trigger source.
 * @Parameters	[in]  EXTI_lineNum : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8SetTriggerSource (EXTI_Trigger_Config_t EXTI_Trigger_Config,EXTI_lineNum_t EXTI_lineNum)
{
	uint8_t Local_u8ErrorState = OK;
	if (EXTI_lineNum <= EXTI_TOTAL_INTERRUPT)
	{
	switch ( EXTI_Trigger_Config )
	{
	case EXTI_RISING_TRIGGER:
		EXTI_REGISTER -> RTSR |= (EXTI_SET_REGISTER << EXTI_lineNum);
		EXTI_REGISTER -> FTSR &= (~(EXTI_SET_REGISTER << EXTI_lineNum));
		break;
	case EXTI_FALLING_TRIGGER:
		EXTI_REGISTER -> FTSR |= (EXTI_SET_REGISTER << EXTI_lineNum);
		EXTI_REGISTER -> RTSR &= (~(EXTI_SET_REGISTER << EXTI_lineNum));
		break;
	case EXTI_RISING_FALLING_TRIGGER:
	EXTI_REGISTER -> RTSR |= (EXTI_SET_REGISTER << EXTI_lineNum);
	EXTI_REGISTER -> FTSR |= (EXTI_SET_REGISTER << EXTI_lineNum);
		break;
	default:
		Local_u8ErrorState = NOK;
		break;
	}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

/*
 * @fn EXTI_u8EnableInt.
 * @berief	the function set enable one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8EnableInt(EXTI_lineNum_t EXTI_lineNum)
{
	uint8_t Local_u8ErrorState = OK;
	/*Set Interrupt enable initial state.*/
	if (EXTI_lineNum < EXTI_TOTAL_INTERRUPT)
	{
		EXTI_REGISTER -> IMR |= (EXTI_SET_REGISTER << EXTI_lineNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

/*
 * @fn EXTI_u8DisableInt.
 * @berief	the function set Disable one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8DisableInt(EXTI_lineNum_t EXTI_lineNum)
{
	{
		uint8_t Local_u8ErrorState = OK;
		/*Set Interrupt disable  initial state.*/
		if (EXTI_lineNum < EXTI_TOTAL_INTERRUPT)
		{
			EXTI_REGISTER -> IMR &=  (~(EXTI_SET_REGISTER << EXTI_lineNum));
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
		return Local_u8ErrorState;
	}
}

/*
 * @fn EXTI_u8ClearPendingFlag.
 * @berief	the function clear pending flag for one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8ClearPendingFlag(EXTI_lineNum_t EXTI_lineNum)
{
	uint8_t Local_u8ErrorState = OK;
	if (EXTI_lineNum <= EXTI_TOTAL_INTERRUPT)
	{
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_lineNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

/*
 * @fn EXTI_u8ReadPendingFlag.
 * @berief	the function clear pending flag for one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @Parameters	[in]  copy_flagStatus : Pointer to know the flag status.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8ReadPendingFlag(EXTI_lineNum_t EXTI_lineNum, uint8_t* copy_flagStatus)
{
	uint8_t Local_u8ErrorState = OK;
	if (copy_flagStatus != NULL)
	{
	if (EXTI_lineNum <= EXTI_TOTAL_INTERRUPT)
	{
		*copy_flagStatus = (((EXTI_REGISTER ->PR)>>EXTI_lineNum)&1);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

void EXTI0_IRQHandler ()
{
	/*Clear pending flag.*/
	EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_1);
	/*Calling IRQ handler*/
	EXTI_CallBackFunc[EXTI_PIN_1]();
}

void EXTI1_IRQHandler ()
{
	/*Clear pending flag.*/
	EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_2);
	/*Calling IRQ handler*/
	EXTI_CallBackFunc[EXTI_PIN_2]();
}

void EXTI2_IRQHandler ()
{
	/*Clear pending flag.*/
	EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_3);
	/*Calling IRQ handler*/
	EXTI_CallBackFunc[EXTI_PIN_3]();
}

void EXTI3_IRQHandler ()
{
	/*Clear pending flag.*/
	EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_4);
	/*Calling IRQ handler*/
	EXTI_CallBackFunc[EXTI_PIN_4]();
}

void EXTI4_IRQHandler ()
{
	/*Clear pending flag.*/
	EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_5);
	/*Calling IRQ handler*/
	EXTI_CallBackFunc[EXTI_PIN_5]();
}

void EXTI5_9_IRQHandler ()
{
	/*Check which external interrupt*/
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_6)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_6);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_6]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_7)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_7);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_7]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_8)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_8);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_8]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_9)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_9);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_9]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_10)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_10);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_10]();
	}
}

void EXTI15_10_IRQHandler ()
{
	/*Check which external interrupt*/
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_11)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_11);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_11]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_12)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_12);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_12]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_13)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_13);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_13]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_14)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_14);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_14]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_15)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_15);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_15]();
	}
	if(((EXTI_REGISTER ->PR)>>EXTI_PIN_16)&1)
	{
		/*Clear pending flag.*/
		EXTI_REGISTER ->PR = (EXTI_SET_REGISTER << EXTI_PIN_16);
		/*Calling IRQ handler*/
		EXTI_CallBackFunc[EXTI_PIN_16]();
	}
}
