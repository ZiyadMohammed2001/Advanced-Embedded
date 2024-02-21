/********************************************************************/
/* @file	GPIO_program.c
 * @author	Ziyad Mohammed
 * @brief	The GPIO Main Source File , Including function definitions.
 */

#include <stdint.h>
#include "Stm32f103.h"
#include "ErrType.h"

#include "GPIO_interface.h"
#include "GPIO_prv.h"

static GPIO_RegDef_t * GPIOPort[GPIO_PERIPHERAL_NUM] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};

/********************************************************************
 * @fn GPIO_u8PinInit.
 * @berief	the function initializes the GPIO pin according to the input parameters.
 * @Parameters	[in]  PinConfig : Initialize values of the pin.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8PinInit (const GPIO_PinConfig_t* PinConfig)
{
	uint8_t	Local_u8ErrorState = OK;
	if(PinConfig != NULL)
	{
		if((PinConfig->Port <= PORTG) && (PinConfig->PinNum <= PIN15) && (PinConfig->GPIO_Input_OUTPUT_Mode <= GPIO_OUTPUT) && (PinConfig->GPIO_Input_Mode <= GPIO_PULLUP_OR_PULLDOWN)&& (PinConfig->GPIO_Input_Pull_UP_Down <=INPUT_PULL_DOWN) && ( PinConfig->GPIO_Ouput_Mode <= GPIO_Alternate_Function_Output_Open_Drain) && (PinConfig->GPIO_Input_OutputSpeed <= OUTPUT_HIGH_SPEED_50MHZ) && (PinConfig->GPIO_PinVal <= PIN_HIGH) && (PinConfig->GPIO_AltFunc <= AF15))
		{
			/*Select High or Low of register CR*/
			uint8_t Local_u8RegNum = (PinConfig -> PinNum) / CR_PIN_SHIFTTING;
			/*Select Pin number of register CR*/
			uint8_t Local_u8BitNum = ((PinConfig -> PinNum) % CR_PIN_SHIFTTING)*CR_PIN_MODE_ACCESS;

			/*Clear bits.*/
			GPIOPort[PinConfig->Port]->GPIO_CR[Local_u8RegNum] &= (CR_MASK << Local_u8BitNum);

			/*Check input or output*/
			if (((PinConfig->GPIO_Input_OUTPUT_Mode)== GPIO_INPUT)&&((PinConfig->GPIO_Input_OutputSpeed)==INPUT))
			{
				/*Select Configuration*/
				GPIOPort[PinConfig->Port]->GPIO_CR[Local_u8RegNum] |= (((PinConfig->GPIO_Input_Mode)<<Local_u8BitNum)<<CR_CNF_PIN_ACCESS);
				/*Select mode bits*/
				GPIOPort[PinConfig->Port]->GPIO_CR[Local_u8RegNum] |= (((PinConfig->GPIO_Input_OutputSpeed)<<Local_u8BitNum));
				/*clear Input pull up or pull down pin.*/
				GPIOPort[PinConfig->Port]->GPIO_ODR &= (GPIO_ODR_MASK << (PinConfig->PinNum));
				/*Configure Input pull up or pull down.*/
				GPIOPort[PinConfig->Port]->GPIO_ODR &= (PinConfig->GPIO_Input_Pull_UP_Down << (PinConfig->PinNum));
			}
			else if((PinConfig->GPIO_Input_OUTPUT_Mode)== GPIO_OUTPUT)
			{
				/*Select Configuration*/
				GPIOPort[PinConfig->Port]->GPIO_CR[Local_u8RegNum] |= (((PinConfig->GPIO_Ouput_Mode)<<Local_u8BitNum)<<CR_CNF_PIN_ACCESS);
				/*Select mode bits*/
				GPIOPort[PinConfig->Port]->GPIO_CR[Local_u8RegNum] |= (((PinConfig->GPIO_Input_OutputSpeed)<<Local_u8BitNum));
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
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

	return	Local_u8ErrorState ;
}

/********************************************************************
 * @fn GPIO_u8SetPinValue.
 * @berief	the function outputs a certain value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @Parameters	[in]  PinVal : The Output value , get options @PinVal_t enum
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8SetPinValue (Port_t Port, Pin_t GPIO_PinNum,GPIO_PinVal_t GPIO_PinVal)
{
	uint8_t	Local_u8ErrorState = OK;
	if((Port <= PORTG) && (GPIO_PinNum <= PIN15))
	{
		if(GPIO_PinVal == PIN_LOW)
		{
			GPIOPort[Port] -> GPIO_ODR &= ~ (1<< GPIO_PinNum);
		}
		else if (GPIO_PinVal == PIN_HIGH)
		{
			GPIOPort[Port] -> GPIO_ODR |= (1<< GPIO_PinNum);
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return	Local_u8ErrorState ;
}

/********************************************************************
 * @fn GPIO_u8Set_4_PinValue.
 * @berief	the function outputs a certain value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : First Pin number, Get options @Pin_t enum.
 * @Parameters	[in]  PinVal : The Output value , get options @PinVal_t enum
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8Set_4_PinValue (Port_t Port, Pin_t GPIO_PinNum,GPIO_PinVal_t GPIO_PinVal)
{
	uint8_t	Local_u8ErrorState = OK;
	if((Port <= PORTG) && (GPIO_PinNum <= PIN15))
	{
		uint32_t Local_u32_REGValue = 0;
		GPIOPort[Port] -> GPIO_ODR &= ~(GPIO_FOUR_BIT_MASKING<<GPIO_PinNum);
		Local_u32_REGValue = GPIOPort[Port] -> GPIO_ODR | (GPIO_PinVal<<GPIO_PinNum);
		GPIOPort[Port] -> GPIO_ODR = Local_u32_REGValue;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return	Local_u8ErrorState ;
}

/*
 * @fn GPIO_u8TogglePinValue.
 * @berief	the function toggle outputs value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @retval ErrorStatus.
 ********************************************************************/


uint8_t GPIO_u8TogglePinValue (Port_t Port, Pin_t PinNum)//Finished
{
	uint8_t	Local_u8ErrorState = OK;
	if((Port <= PORTG) && (PinNum <= PIN15))
	{

		GPIOPort[Port] -> GPIO_ODR ^= ~ (1<< PinNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return	Local_u8ErrorState ;
}


/*
 * @fn GPIO_u8ReadPinValue.
 * @berief	the function Read output value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @retval ErrorStatus.
 ********************************************************************/


uint8_t GPIO_u8ReadPinValue (Port_t Port, Pin_t PinNum,GPIO_PinVal_t* GPIO_PinVal)//Finished
{
	uint8_t	Local_u8ErrorState = OK;
	if((Port <= PORTG) && (PinNum <= PIN15))
	{
		*(GPIO_PinVal) = (GPIOPort[Port] -> GPIO_IDR) ;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return	Local_u8ErrorState ;
}
