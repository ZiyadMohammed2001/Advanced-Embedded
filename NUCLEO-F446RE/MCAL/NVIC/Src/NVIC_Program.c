/********************************************************************/
/* @file	NVIC_program.c
 * @author	Ziyad Mohammed
 * @brief	The NVIC Main Source File , Including function definitions.
 */
#include <stdint.h>
#include "Stm32f446.h"
#include "ErrType.h"

#include "NVIC_interface.h"
#include "NVIC_Config.h"
#include "NVIC_private.h"

static void(*NVIC_Apf[NVIC_TOTAL_INTERRUPT])(void) = {NULL,NULL,NULL}; //Array of pointer to functions For call back Function.

/********************************************************************
 * @fn NVIC_u8_Enable_Interrupt.
 * @berief	the function Enables the System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Enable_Interrupt ( uint8_t Copy_u8IRQNum)
{

	uint8_t		Local_u8ErrorState = OK;
	uint8_t		Local_u8REG_NUM = Copy_u8IRQNum / NVIC_REG_SIZE;
	uint8_t		Local_u8Bit_NUM = Copy_u8IRQNum % NVIC_REG_SIZE;
	//NVIC_REG_t NVIC_REG;
	if ((Copy_u8IRQNum <=NVIC_TOTAL_INTERRUPT)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_1)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_2)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_3)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_4)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_5)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_6)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_7)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_8)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_9)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_10)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_11))
	{
		NVIC_REGISTER -> NVIC_ISER[Local_u8REG_NUM] = 1 << Local_u8Bit_NUM;
	}
	else
	{
		Local_u8ErrorState = OK;
	}
	return Local_u8ErrorState;
}

/********************************************************************
 * @fn NVIC_u8_Disable_Interrupt.
 * @berief	the function Disables the System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Disable_Interrupt ( uint8_t Copy_u8IRQNum)
{
	uint8_t		Local_u8ErrorState = OK;
	uint8_t		Local_u8REG_NUM = Copy_u8IRQNum / NVIC_REG_SIZE;
	uint8_t		Local_u8Bit_NUM = Copy_u8IRQNum % NVIC_REG_SIZE;
	if ((Copy_u8IRQNum <=NVIC_TOTAL_INTERRUPT)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_1)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_2)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_3)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_4)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_5)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_6)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_7)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_8)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_9)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_10)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_11))
	{
		NVIC_REGISTER -> NVIC_ICER[Local_u8REG_NUM] = 1 << Local_u8Bit_NUM;
	}
	else
	{
		Local_u8ErrorState = OK;
	}
	return Local_u8ErrorState;
}

/********************************************************************
 * @fn NVIC_u8_Set_Pending_Flag.
 * @berief	the function Enables the pending flag of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Set_Pending_Flag ( uint8_t Copy_u8IRQNum)
{
	uint8_t		Local_u8ErrorState = OK;
	uint8_t		Local_u8REG_NUM = Copy_u8IRQNum / NVIC_REG_SIZE;
	uint8_t		Local_u8Bit_NUM = Copy_u8IRQNum % NVIC_REG_SIZE;
	if ((Copy_u8IRQNum <=NVIC_TOTAL_INTERRUPT)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_1)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_2)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_3)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_4)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_5)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_6)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_7)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_8)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_9)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_10)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_11))
	{
		NVIC_REGISTER -> NVIC_ISPR[Local_u8REG_NUM] = 1 << Local_u8Bit_NUM;
	}
	else
	{
		Local_u8ErrorState = OK;
	}
	return Local_u8ErrorState;
}

/********************************************************************
 * @fn NVIC_u8_Clear_Pending_Flag.
 * @berief	the function Enables the pending flag of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Clear_Pending_Flag ( uint8_t Copy_u8IRQNum)
{
	uint8_t		Local_u8ErrorState = OK;
	uint8_t		Local_u8REG_NUM = Copy_u8IRQNum / NVIC_REG_SIZE;
	uint8_t		Local_u8Bit_NUM = Copy_u8IRQNum % NVIC_REG_SIZE;
	if ((Copy_u8IRQNum <=NVIC_TOTAL_INTERRUPT)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_1)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_2)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_3)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_4)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_5)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_6)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_7)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_8)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_9)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_10)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_11))
	{
		NVIC_REGISTER -> NVIC_ICPR[Local_u8REG_NUM] = 1 << Local_u8Bit_NUM;
	}
	else
	{
		Local_u8ErrorState = OK;
	}
	return Local_u8ErrorState;
}

/********************************************************************
 * @fn NVIC_u8_Get_Active_Flag.
 * @berief	the function get the active flag of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception , *Copy_u8ActiveFlagStatus : pointer to return the status of active flag.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Get_Active_Flag ( uint8_t Copy_u8IRQNum , uint8_t* Copy_u8ActiveFlagStatus)
{
	uint8_t		Local_u8ErrorState = OK;
	uint8_t		Local_u8REG_NUM = Copy_u8IRQNum / NVIC_REG_SIZE;
	uint8_t		Local_u8Bit_NUM = Copy_u8IRQNum % NVIC_REG_SIZE;
	if ((Copy_u8IRQNum <=NVIC_TOTAL_INTERRUPT)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_1)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_2)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_3)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_4)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_5)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_6)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_7)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_8)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_9)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_10)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_11)&& (Copy_u8ActiveFlagStatus!=NULL))
	{
		* Copy_u8ActiveFlagStatus = ((NVIC_REGISTER -> NVIC_IABR[Local_u8REG_NUM]) & (NVIC_GIT_ACTIVE_FLAG << Local_u8Bit_NUM));
	}
	else
	{
		Local_u8ErrorState = OK;
	}
	return Local_u8ErrorState;
}

/********************************************************************
 * @fn NVIC_u8_Set_Priority.
 * @berief	the function Set priority of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Set_Priority ( uint8_t Copy_u8IRQNum , uint8_t Copy_u8PriorityNum)
{
	uint8_t		Local_u8ErrorState = OK;
	uint8_t		Local_u8REG_NUM = Copy_u8IRQNum / NVIC_PRIORITY_REG;
	uint8_t		Local_u8Bit_NUM = (Copy_u8IRQNum % NVIC_PRIORITY_REG) * NVIC_PRIORITY_REG_SIZE;
	if ((Copy_u8IRQNum <=NVIC_TOTAL_INTERRUPT)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_1)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_2)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_3)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_4)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_5)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_6)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_7)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_8)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_9)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_10)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_11)&& (Copy_u8PriorityNum < NVIC_PRIORITY_SIZE_11))
	{
		NVIC_REGISTER -> NVIC_IPR[Local_u8REG_NUM] = Copy_u8PriorityNum << Local_u8Bit_NUM;
	}
	else
	{
		Local_u8ErrorState = OK;
	}
	return Local_u8ErrorState;
}

/********************************************************************
 * @fn NVIC_u8SetCallBack.
 * @berief	the function set a function to be execution in the ISR of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8SetCallBack(uint8_t Copy_u8IRQNum,void(*Copy_pf)(void))
{
	uint8_t		Local_u8ErrorState = OK;
	if((Copy_u8IRQNum <=NVIC_TOTAL_INTERRUPT)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_1)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_2)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_3)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_4)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_5)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_6)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_7)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_8)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_9)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_10)&& (Copy_u8IRQNum!=NVIC_RESERVED_INTERRUPT_11) && (Copy_pf!=NULL)) // because enum is signed value so it may be negative Value.
	{
		// Update global pointer to function.
		NVIC_Apf[Copy_u8IRQNum] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState ;
}

void USART3_IRQHandler ()
{
	if (NVIC_Apf[USART3_Interrupt] != NULL)
	{
		NVIC_Apf[USART3_Interrupt]();
	}
}
