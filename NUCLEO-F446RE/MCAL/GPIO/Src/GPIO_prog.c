/********************************************************************/
/* @file	GPIO_program.c
 * @author	Ziyad Mohammed
 * @brief	The GPIO Main Source File , Including function definitions.
 */

#include <stdint.h>
#include "Stm32f446.h"
#include "ErrType.h"

#include "GPIO_interface.h"
#include "GPIO_prv.h"

static GPIO_RegDef_t * GPIOPort[GPIO_PERIPHERAL_NUM] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

/********************************************************************
 * @fn GPIO_u8PinInit.
 * @berief	the function initializes the GPIO pin according to the input parameters.
 * @Parameters	[in]  PinConfig : Initialize values of the pin.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8PinInit (const GPIO_PinConfig_t* GPIO_PinConfig)
{
	uint8_t	Local_u8ErrorState = OK;
	if(GPIO_PinConfig != NULL)
	{
		if((GPIO_PinConfig->Port <= PORTH) && (GPIO_PinConfig->PinNum <= PIN15) &&(GPIO_PinConfig->Mode <= GPIO_ANALOG) && (GPIO_PinConfig->GPIO_Speed <= GPIO_HIGH) && (GPIO_PinConfig->GPIO_OutputType <= GPIO_OPEN_DRAIN) && (GPIO_PinConfig->GPIO_PullType <= GPIO_PULLDOWN) && (GPIO_PinConfig->GPIO_AltFunc <= GPIO_AF15))
		{
			/*Select GPIO Mode ; Input , Output , Analog , Alternative function*/
			(GPIOPort[GPIO_PinConfig->Port]->MODER) &= ~ (MODER_MASK << ((GPIO_PinConfig -> PinNum) * MODER_PIN_ACCESS)); 							/* Clear Mode Bits. */
			(GPIOPort[GPIO_PinConfig->Port]->MODER) |= ((GPIO_PinConfig->Mode) << ((GPIO_PinConfig -> PinNum) * MODER_PIN_ACCESS));						/* Select Mode And putting these bits. */

			/*Select GPIO Pull State : Pull-Up, Pull-Down, NoPull*/
			(GPIOPort[GPIO_PinConfig->Port]->PUPDR) &= ~ (PUPDR_MASK << ((GPIO_PinConfig -> PinNum) * PUPDR_PIN_ACCESS)); 							/* Clear Mode Bits. */
			(GPIOPort[GPIO_PinConfig->Port]->PUPDR) |= ~ ((GPIO_PinConfig->GPIO_PullType) << ((GPIO_PinConfig -> PinNum) * PUPDR_PIN_ACCESS));					/* Select Mode And putting these bits. */

			/*Select Output type & output speed in case of general purpose output or alternate function.*/
			if(((GPIO_PinConfig -> Mode) == GPIO_OUTPUT) || ((GPIO_PinConfig -> Mode) == GPIO_ALTERNATE_FUNCTION))
			{
				/*Select Output Type : Push Pull or Open Drain.*/
				(GPIOPort[GPIO_PinConfig->Port]->OTYPER) &= ~ ( OTYPER_MASK << (GPIO_PinConfig -> PinNum));											/* Clear Mode Bits. */
				(GPIOPort[GPIO_PinConfig->Port]->OTYPER) |= ( (GPIO_PinConfig -> GPIO_OutputType) << (GPIO_PinConfig -> PinNum));								/* Select Mode And putting these bits. */

				/*Select Output Speed : Low, Medium, High, Fast*/
				(GPIOPort[GPIO_PinConfig->Port]->OSPEEDR) &= ~ (OSPEEDR_MASK << ((GPIO_PinConfig -> PinNum) * OSPEEDR_PIN_ACCESS));   				/* Clear Mode Bits. */
				(GPIOPort[GPIO_PinConfig->Port]->OSPEEDR) &= ((GPIO_PinConfig -> GPIO_Speed) << ((GPIO_PinConfig -> PinNum) * OSPEEDR_PIN_ACCESS)); 			/* Select Mode And putting these bits. */

				/*Select The Pin of Alternative Function.*/
				if((GPIO_PinConfig -> Mode) == GPIO_ALTERNATE_FUNCTION)
				{
					uint8_t Local_u8RegNum = (GPIO_PinConfig -> PinNum) / AFR_PIN_SHIFTTING;
					uint8_t Local_u8BitNum = (GPIO_PinConfig -> PinNum) % AFR_PIN_SHIFTTING;
					(GPIOPort[GPIO_PinConfig->Port] -> AFR[Local_u8RegNum] &= ~ ( AFR_MASK << Local_u8BitNum * AFR_PIN_ACCESS));					/* Clear Mode Bits. */
					(GPIOPort[GPIO_PinConfig->Port] -> AFR[Local_u8RegNum] |= ( (GPIO_PinConfig -> GPIO_AltFunc) << Local_u8BitNum * AFR_PIN_ACCESS));		/* Select Mode And putting these bits */
				}
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
 * @berief	the function outputs a certain value on an autput pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @Parameters	[in]  PinVal : The Output value , get options @PinVal_t enum
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8SetPinValue (GPIO_Port_t GPIO_Port, GPIO_Pin_t GPIO_PinNum,GPIO_PinVal_t GPIO_PinVal)
{
	uint8_t	Local_u8ErrorState = OK;
	if((GPIO_Port <= PORTH) && (GPIO_PinNum <= PIN15))
	{
		if(GPIO_PinVal == GPIO_PIN_LOW)
		{
			GPIOPort[GPIO_Port] -> ODR &= ~ (1<< GPIO_PinNum);
			/* GPIOPort[Port] -> BSRR = 1 << ( 16 + PinNum ); */
		}
		else if (GPIO_PinVal == GPIO_PIN_HIGH)
		{
			GPIOPort[GPIO_Port] -> ODR |= (1<< GPIO_PinNum);
			/* GPIOPort[Port] -> BSRR = 1 << ( PinNum ); */
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


/*
 * @fn GPIO_u8TogglePinValue.
 * @berief	the function toggle outputs value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @retval ErrorStatus.
 ********************************************************************/


uint8_t GPIO_u8TogglePinValue (GPIO_Port_t GPIO_Port, GPIO_Pin_t GPIO_PinNum)
{
	uint8_t	Local_u8ErrorState = OK;
	if((GPIO_Port <= PORTH) && (GPIO_PinNum <= PIN15))
	{

		GPIOPort[GPIO_Port] -> ODR ^= ~ (1<< GPIO_PinNum);
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
 * @Parameters	[in] 	 Port 	:	 Port number, Get options @Port_t enum.
 * @Parameters	[in]  	PinNum 	:	 Pin number, Get options @Pin_t enum.
 * @Parameters 	[in] 	PinVal	:	 Pin Value variable to know the pin value.
 * @retval ErrorStatus.
 ********************************************************************/


uint8_t GPIO_u8ReadPinValue (GPIO_Port_t GPIO_Port, GPIO_Pin_t GPIO_PinNum,GPIO_PinVal_t* GPIO_PinVal)
{
	uint8_t	Local_u8ErrorState = OK;
	if((GPIO_Port <= PORTH) && (GPIO_PinNum <= PIN15))
	{
		*(GPIO_PinVal) = (GPIOPort[GPIO_Port] -> IDR) ;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return	Local_u8ErrorState ;
}
