/********************************************************************/
/* @file	RCC_program.c
 * @author	Ziyad Mohammed
 * @brief	The RCC Main Source File , Including function definitions.
 */


#include <stdint.h>
#include "Stm32f446.h"
#include "ErrType.h"

#include "RCC_interface.h"
#include "RCC_prv.h"

extern HSE_CONFIG HSE_CONFIG_t;

/******************************************************************************
 * Function Name:  RCC_u8SetClkStatusSynch
 * Description:	The Function that Set Clock Status
 * Parameters: CLKStatus structure hold configuration
 * Return:	ErrorState , Type:u8
 ******************************************************************************/
uint8_t RCC_u8SetClkStatusSynch(RCC_CLKStatus * CLKStatus)
{
	uint8_t	Local_u8ErrorState = OK;
	uint32_t Local_TimeOut=0;
	if ((((CLKStatus -> RCC_SYSCLK)<= RCC_PLLSAI))&&((CLKStatus -> RCC_CLkState) <= CLK_OFF ))
	{
		switch (CLKStatus -> RCC_SYSCLK)
		{
		case RCC_HSI:
			// Clear and set the HSI bit to enable the clock.
			if((CLKStatus->RCC_CLkState)==CLK_ON)
			{
				//Set bit 0 to on the HSI
				RCC -> CR &= HSI_DISABLE_BIT;
				RCC -> CR |= HSI_ENABLE_BIT;
				// Wait till time out or the ready flag is raised by HW.
				while(((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)  && (Local_TimeOut<THRESHOLD_VALUE))
				{
					Local_TimeOut++;
				}
				//Check if the CLK is ready or not.
				if (Local_TimeOut==THRESHOLD_VALUE)
				{
					Local_u8ErrorState = NOK;
				}
			}
			else if ((CLKStatus->RCC_CLkState)==CLK_OFF)
			{
				// Check if another clock is enabled.
				if (((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(PLL_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLI2S_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
				{
					//Clear the HSI Bit.
					RCC -> CR &= HSI_DISABLE_BIT;
				}
				else
				{
					// Its NOK to shift Now.
					Local_u8ErrorState = NOK;
				}
			}
			// Trimming
			RCC -> CR &= HSI_TRIMMING_CLEAR_BITS;
			RCC -> CR |= HSI_OPTIMIZING_TRIMMING_BITS;
			break;
		case RCC_HSE:
			// Clear and set the HSI bit to enable the clock.
			if((CLKStatus->RCC_CLkState)==CLK_ON)
			{
				//Set bit 16 to on the HSE.
				RCC -> CR &= HSE_DISABLE_BIT;
				RCC -> CR |= HSE_ENABLE_BIT;
				// Wait till time out or the ready flag is raised by HW.
				while(((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)  && (Local_TimeOut<THRESHOLD_VALUE))
				{
					Local_TimeOut++;
				}
				//Check if the CLK is ready or not.
				if (Local_TimeOut==THRESHOLD_VALUE)
				{
					Local_u8ErrorState = NOK;
				}
			}
			else if ((CLKStatus->RCC_CLkState)==CLK_OFF)
			{
				// Check if another clock is enabled.
				if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(PLL_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLI2S_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
				{
					//Clear the HSI Bit.
					RCC -> CR &= HSE_DISABLE_BIT;
				}
				else
				{
					// Its NOK to shift Now.
					Local_u8ErrorState = NOK;
				}
			}
			break;
		case RCC_PLL:
			// Clear and set the PLL bit to enable the clock.
			if((CLKStatus->RCC_CLkState)==CLK_ON)
			{
				//Set bit 24 to on the PLL.
				RCC -> CR &= PLL_DISABLE_BIT;	 //Clear Bit.
				RCC -> CR |= PLL_ENABLE_BIT;	//Set Bit.
				// Wait till time out or the ready flag is raised by HW.
				while(((((RCC -> CR)>>(PLL_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)  && (Local_TimeOut<THRESHOLD_VALUE))
				{
					Local_TimeOut++;
				}
				//Check if the CLK is ready or not.
				if (Local_TimeOut==THRESHOLD_VALUE)
				{
					Local_u8ErrorState = NOK;
				}
			}
			else if ((CLKStatus->RCC_CLkState)==CLK_OFF)
			{
				// Check if another clock is enabled.
				if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLI2S_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
				{
					//Clear the HSI Bit.
					RCC -> CR &= PLL_DISABLE_BIT;
				}
				else
				{
					// Its NOK to shift Now.
					Local_u8ErrorState = NOK;
				}
			}
			break;
		case RCC_PLLI2S:
			// Clear and set the PLL bit to enable the clock.
			if((CLKStatus->RCC_CLkState)==CLK_ON)
			{
				//Set bit 26 to on the PLLI2S.
				RCC -> CR &= PLLI2S_DISABLE_BIT;	 //Clear Bit.
				RCC -> CR |= PLLI2S_ENABLE_BIT;	//Set Bit.
				// Wait till time out or the ready flag is raised by HW.
				while(((((RCC -> CR)>>(PLLI2S_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)  && (Local_TimeOut<THRESHOLD_VALUE))
				{
					Local_TimeOut++;
				}
				//Check if the CLK is ready or not.
				if (Local_TimeOut==THRESHOLD_VALUE)
				{
					Local_u8ErrorState = NOK;
				}
			}
			else if ((CLKStatus->RCC_CLkState)==CLK_OFF)
			{
				// Check if another clock is enabled.
				if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
				{
					//Clear the HSI Bit.
					RCC -> CR &= PLLI2S_DISABLE_BIT;
				}
				else
				{
					// Its NOK to shift Now.
					Local_u8ErrorState = NOK;
				}
			}
			break;
		case RCC_PLLSAI:
			// Clear and set the PLL bit to enable the clock.
			if((CLKStatus->RCC_CLkState)==CLK_ON)
			{
				//Set bit 28 to on the PLLSAI.
				RCC -> CR &= PLLSAI_DISABLE_BIT;	 //Clear Bit.
				RCC -> CR |= PLLSAI_ENABLE_BIT;	//Set Bit.
				// Wait till time out or the ready flag is raised by HW.
				while(((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)  && (Local_TimeOut<THRESHOLD_VALUE))
				{
					Local_TimeOut++;
				}
				//Check if the CLK is ready or not.
				if (Local_TimeOut==THRESHOLD_VALUE)
				{
					Local_u8ErrorState = NOK;
				}
			}
			else if ((CLKStatus->RCC_CLkState)==CLK_OFF)
			{
				// Check if another clock is enabled.
				if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLI2S_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
				{
					//Clear the HSI Bit.
					RCC -> CR &= PLLSAI_DISABLE_BIT;
				}
				else
				{
					// Its NOK to shift Now.
					Local_u8ErrorState = NOK;
				}
			}
			break;
		default: Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}


/******************************************************************************
 * Function Name:  RCC_uint8_tDisableClkStatus
 * Description:	The Function disable CLK
 * Parameters: Copy_uint8_tclock RCC_HSI  | RCC_HSE |RCC_PLL
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tDisableClkStatus(uint8_t Copy_uint8_tclock)
{
	uint8_t	Local_u8ErrorState = OK;
	if (Copy_uint8_tclock <= RCC_PLLSAI)
	{
		switch (Copy_uint8_tclock)
		{
		case RCC_HSI:
			// Clear and set the HSI bit to enable the clock.
			// Check if another clock is enabled.
			if (((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(PLL_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
			{
				//Clear the HSI Bit.
				RCC -> CR &= HSI_DISABLE_BIT;
			}
			else
			{
				// Its NOK to shift Now.
				Local_u8ErrorState = NOK;
			}
			break;
		case RCC_HSE:
			// Check if another clock is enabled.
			if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(PLL_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
			{
				//Clear the HSI Bit.
				RCC -> CR &= HSE_DISABLE_BIT;
			}
			else
			{
				// Its NOK to shift Now.
				Local_u8ErrorState = NOK;
			}
			break;
		case RCC_PLL:
			// Check if another clock is enabled.
			if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
			{
				//Clear the HSI Bit.
				RCC -> CR &= PLL_DISABLE_BIT;
			}
			else
			{
				// Its NOK to shift Now.
				Local_u8ErrorState = NOK;
			}
			break;
		case RCC_PLLI2S:
			// Check if another clock is enabled.
			if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
			{
				//Clear the HSI Bit.
				RCC -> CR &= PLLI2S_DISABLE_BIT;
			}
			else
			{
				// Its NOK to shift Now.
				Local_u8ErrorState = NOK;
			}
			break;
		case RCC_PLLSAI:
			// Check if another clock is enabled.
			if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLI2S_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH) || ((((RCC -> CR)>>(PLLSAI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
			{
				//Clear the HSI Bit.
				RCC -> CR &= PLLSAI_DISABLE_BIT;
			}
			else
			{
				// Its NOK to shift Now.
				Local_u8ErrorState = NOK;
			}
			break;

		default: Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_uint8_tSetSysClk
 * Description:	The Function Set SYSCLk source (System clock switch)
 * Parameters: MCO_CONFIG_t
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tSetSysClk(RCC_MCO_CONFIG_t*MCO_CONFIG_t)
{
	uint8_t	Local_u8ErrorState = OK;
	if (((MCO_CONFIG_t->RCC_Microcontroller_Output_Number) <= RCC_MCO_2) && ((MCO_CONFIG_t-> RCC_Microcontroller_Output_SYSCLK) <= RCC_MCO1_PLL) && (((((MCO_CONFIG_t-> RCC_Microcontroller_Output_Prescaler ) >= RCC_MCO1_PRESCALER_DVIVSION_BY_2)) && ((MCO_CONFIG_t-> RCC_Microcontroller_Output_Prescaler ) <= RCC_MCO1_PRESCALER_DVIVSION_BY_5)) || ((MCO_CONFIG_t-> RCC_Microcontroller_Output_Prescaler )== RCC_MCO1_PRESCALER_DVIVSION_BY_1 )))
	{
		switch (MCO_CONFIG_t->RCC_Microcontroller_Output_Number)
		{
		case RCC_MCO_1:
			// Set Prescaler.
			RCC->CFGR = (MCO_CONFIG_t -> RCC_Microcontroller_Output_Prescaler) << RCC_MCO1_PRESCALER ;
			// Switch Clock Source.
			RCC->CFGR = (MCO_CONFIG_t -> RCC_Microcontroller_Output_SYSCLK) << RCC_MCO1_CLK_SELECT ;
			break;
		case RCC_MCO_2:
			// Set Prescaler.
			RCC->CFGR = (MCO_CONFIG_t -> RCC_Microcontroller_Output_Prescaler) << RCC_MCO2_PRESCALER ;
			// Switch Clock Source.
			RCC->CFGR = (MCO_CONFIG_t -> RCC_Microcontroller_Output_SYSCLK) << RCC_MCO2_CLK_SELECT ;
			break;
		default: Local_u8ErrorState=NOK;
		}
		/*selected  system clock*/
		(RCC->CFGR) &= RCC_CFGR_SYSTEMCLK_CLEAR_BITS;
		//(RCC->CFGR) |= (Copy_uint8_tSysClk);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}


/******************************************************************************
 * Function Name:  RCC_uint8_tSetSysClk
 * Description:	The Function Set HSE Configuration
 * Parameters: Copy_uint8_tHSE_Div  option  HSE_NOT_DIVIDED | HSE_DIVIDED_BY_TOW
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tHSEConfig(RCC_HSE_CONFIG_t * RCC_HSE_CONFIG)
{
	uint8_t	Local_u8ErrorState = OK;
	// Switch CLK to HSI.
	RCC_MCO_CONFIG_t HSEConfig =
	{
			.RCC_Microcontroller_Output_Number = RCC_MCO_1,
			.RCC_Microcontroller_Output_Prescaler = RCC_MCO1_SYSCLK,
			.RCC_Microcontroller_Output_SYSCLK =RCC_MCO1_PRESCALER_DVIVSION_BY_1
	};
	Local_u8ErrorState = RCC_uint8_tSetSysClk (&HSEConfig);
	if (Local_u8ErrorState)
	{
		// Disable HSE.
		Local_u8ErrorState = RCC_uint8_tDisableClkStatus (RCC_HSE);
		if (Local_u8ErrorState == OK)
		{
			// Check if another clock is enabled.
			if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
			{
				//Clear the HSE Bit.
				RCC -> CR &= HSE_DISABLE_BIT;
				//Change Configuration.
				if (((RCC_HSE_CONFIG ->RCC_HSE_CLOCK_SECURITY_SYS) <= RCC_HSE_CLOCK_SECURITY_SYS_ON) && ((RCC_HSE_CONFIG ->RCC_HSE_Clock_Bypass) <= RCC_HSE_Oscillator_Bypassed) && ((RCC_HSE_CONFIG ->RCC_HSE_Divider) <= HSE_DIVIDED_BY_31))
				{
					//Configure Security System. // Note.
					RCC -> CR &= HSE_CLOCK_SECURITY_SYSTEM_BIT_DISABLE << HSE_CLOCK_SECURITY_SYSTEM_BIT; // Clear bit.
					RCC -> CR |= (RCC_HSE_CONFIG ->RCC_HSE_CLOCK_SECURITY_SYS) << HSE_CLOCK_SECURITY_SYSTEM_BIT ; // Put value selected.
					//Configure By Pass OR Not By Pass.
					RCC -> CR &= HSE_BY_PASSED_OR_NOT_BY_PASSED_DISABLE << HSE_BY_PASSED_OR_NOT_BY_PASSED; // Clear bit.
					RCC -> CR |= (RCC_HSE_CONFIG ->RCC_HSE_Clock_Bypass) << HSE_BY_PASSED_OR_NOT_BY_PASSED ; // Put value selected.
					// Select Division Factor.
					RCC ->CFGR &=HSE_DIVISION_BITS_CLEAR; //Clear Bits.
					RCC ->CFGR |=((RCC_HSE_CONFIG ->RCC_HSE_CLOCK_SECURITY_SYS) << HSE_DIVISION_BITS_BEGIN); //Select the needed Value.
				}
				else
				{
					Local_u8ErrorState = NOK;
				}
			}
			else
			{
				// Its NOK to shift Now.
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
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}


/******************************************************************************
 * Function Name:  RCC_uint8_tPLLConfig
 * Description:	The Function Set PLL Configuration)
 * Parameters: PLL_Cfg
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/

uint8_t RCC_uint8_tPLLConfig(PLL_CONFIG  * PLL_Cfg)
{
	uint8_t	Local_u8ErrorState = OK;
	//Switch clock to HSI.
	RCC_MCO_CONFIG_t HSEConfig =
	{
			.RCC_Microcontroller_Output_Number = RCC_MCO_1,
			.RCC_Microcontroller_Output_Prescaler = RCC_MCO1_SYSCLK,
			.RCC_Microcontroller_Output_SYSCLK =RCC_MCO1_PRESCALER_DVIVSION_BY_1
	};
	Local_u8ErrorState = RCC_uint8_tSetSysClk (&HSEConfig);
	if(Local_u8ErrorState == OK)
	{
		//Disable PLL.
		// Check if another clock is enabled.
		if (((((RCC -> CR)>>(HSI_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH)||((((RCC -> CR)>>(HSE_READY_BIT_NUMBER))&GET_BIT_VALUS_BY_ORING) == GET_BIT_VALUS_HIGH))
		{
			//Clear the HSI Bit.
			RCC -> CR &= PLL_DISABLE_BIT;
		}
		else
		{
			// Its NOK to shift Now.
			Local_u8ErrorState = NOK;
		}
		//Change Configuration.
		//Configure PLL Source.
		(RCC -> PLLCFGR) &= PLL_SELECT_SOURCE_MASK; 	// Clear bit of selection.
		(RCC -> PLLCFGR) |= ((PLL_Cfg->PLL_ClkOption)<< PLL_SELECT_SOURCE_BIT );	// Select clock option.
		// Configure Multiple Factor.
		(RCC -> PLLCFGR) &= PLL_SELECT_MULTIPLY_FACTOR_MASK;	// Clear bit of selection of Multiply Factor of PLL.
		(RCC -> PLLCFGR) |= (PLL_Cfg->PLL_ClkOption);
		// Configure HSE Division Factor if HSE is the source of PLL.
		if (((PLL_Cfg -> PLL_ClkOption) == PLL_HSE) && (PLL_Cfg ->PLL_HSEClkOption <= PLL_X63))
		{
			// Select Division Factor.
			RCC ->CFGR &=HSE_DIVISION_BITS_CLEAR; //Clear Bits.
			RCC ->CFGR |= ((PLL_Cfg ->PLL_HSEClkOption) << HSE_DIVISION_BITS_BEGIN); //Select the needed Value.
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
	return Local_u8ErrorState;
}


/******************************************************************************
 * Function Name:  RCC_uint8_tAHBEnableCLK
 * Description:	The Function enable AHB Peripheral CLK
 * Parameters: GPIO_CONFIG.
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_AHB_1_CLKConfiguration(const RCC_AHB1ENR_CONFIG_t * RCC_AHB1ENR_CONFIG)
{
	uint8_t	Local_u8ErrorState = OK;
	if(((RCC_AHB1ENR_CONFIG -> RCC_AHB1ENR_PORT) <= OTGHSULPIEN)&&(((RCC_AHB1ENR_CONFIG -> RCC_AHB1ENR_STATE) <= RCC_AHB1ENR_STATE_RESET)))
	{
		// Configure Port.
		RCC->AHB1ENR &= (RCC_AHB1_MASKING<< (RCC_AHB1ENR_CONFIG -> RCC_AHB1ENR_PORT)); //Clear Bit of GPIO Port.
		// Configure State Enable or Disable.
		RCC->AHB1ENR |= ((RCC_AHB1ENR_CONFIG->RCC_AHB1ENR_STATE) << (RCC_AHB1ENR_CONFIG -> RCC_AHB1ENR_PORT)); //Set Bit of GPIO Port.
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}


/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_APB1ENR_CONFIG
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_1_CLKConfiguration(const RCC_APB1ENR_CONFIG_t * RCC_APB1ENR_CONFIG)
{
	uint8_t	Local_u8ErrorState = OK;
	if(((RCC_APB1ENR_CONFIG -> RCC_APB1ENR_PORT) <= DAC)&&(((RCC_APB1ENR_CONFIG -> RCC_APB1ENR_STATE) <= RCC_APB1ENR_STATE_No_RESET)))
	{
		// Configure Port.
		RCC->APB1ENR &= (RCC_APB1_MASKING<< (RCC_APB1ENR_CONFIG -> RCC_APB1ENR_PORT)); //Clear Bit of GPIO Port.
		// Configure State Enable or Disable.
		if ((RCC_APB1ENR_CONFIG -> RCC_APB1ENR_STATE) == RCC_APB1ENR_STATE_No_RESET)
		{
			RCC->APB1ENR &= (RCC_APB1_MASKING<< (RCC_APB1ENR_CONFIG -> RCC_APB1ENR_PORT)); //Clear Bit of GPIO Port.
		}
		else if ((RCC_APB1ENR_CONFIG -> RCC_APB1ENR_STATE) == RCC_APB1ENR_STATE_RESET)
		{
			RCC->APB1ENR |= (RCC_APB1_SET_BIT<< (RCC_APB1ENR_CONFIG -> RCC_APB1ENR_PORT)); //Set Bit of GPIO Port.
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}


/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_APB1ENR_CONFIG
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_2_CLKConfiguration(RCC_APB2ENR_CONFIG_t * RCC_APB2ENR_CONFIG)
{
	uint8_t	Local_u8ErrorState = OK;
	if(((RCC_APB2ENR_CONFIG -> RCC_APB2ENR_PORT) <= SAI2)&&(((RCC_APB2ENR_CONFIG -> RCC_APB2ENR_STATE) <= RCC_APB2ENR_STATE_No_RESET)))
	{
		// Configure Port.
		RCC->APB2ENR &= (RCC_APB2_MASKING<< (RCC_APB2ENR_CONFIG -> RCC_APB2ENR_PORT)); //Clear Bit of GPIO Port.
		// Configure State Enable or Disable.
		if ((RCC_APB2ENR_CONFIG -> RCC_APB2ENR_STATE) == RCC_APB2ENR_STATE_No_RESET)
		{
			RCC->APB2ENR &= (RCC_APB2_MASKING<< (RCC_APB2ENR_CONFIG -> RCC_APB2ENR_PORT)); //Clear Bit of GPIO Port.
		}
		else if ((RCC_APB2ENR_CONFIG -> RCC_APB2ENR_STATE) == RCC_APB2ENR_STATE_RESET)
		{
			RCC->APB2ENR |= (RCC_APB2_SET_BIT<< (RCC_APB2ENR_CONFIG -> RCC_APB2ENR_PORT)); //Set Bit of GPIO Port.
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_ClockSecuritySystemEnable
 * Description:	Clock Security System Enable
 * Parameters: non
 * Return:	non
 ******************************************************************************/
void RCC_ClockSecuritySystemEnable(void)
{
	RCC -> CR |= (! HSE_CLOCK_SECURITY_SYSTEM_BIT_DISABLE) << HSE_CLOCK_SECURITY_SYSTEM_BIT; ; // Put value selected.
}
/******************************************************************************
 * Function Name:  RCC_ClockSecuritySystemEnable
 * Description:	Clock Security System Disable
 * Parameters: non
 * Return:	non
 ******************************************************************************/
void RCC_ClockSecuritySystemDisable(void)
{
	RCC -> CR &= HSE_CLOCK_SECURITY_SYSTEM_BIT_DISABLE << HSE_CLOCK_SECURITY_SYSTEM_BIT; // Clear bit.
}

/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_APB1ENR_CONFIG_LPM
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_1_CLKConfiguration_LPM(RCC_APB1ENR_CONFIG_LPM_t * RCC_APB1ENR_CONFIG_LPM)
{
	uint8_t	Local_u8ErrorState = OK;
	if(((RCC_APB1ENR_CONFIG_LPM -> RCC_APB1ENR_PORT_LPM) <= DAC_LPM)&&(((RCC_APB1ENR_CONFIG_LPM  -> RCC_APB1ENR_STATE_LPM) <= RCC_APB1ENR_STATE_No_RESET_LPM)))
	{
		// Configure Port.
		RCC->APB1LPENR &= (RCC_APB1_MASKING_LPM << (RCC_APB1ENR_CONFIG_LPM -> RCC_APB1ENR_PORT_LPM)); //Clear Bit of GPIO Port.
		// Configure State Enable or Disable.
		if ((RCC_APB1ENR_CONFIG_LPM -> RCC_APB1ENR_STATE_LPM) == RCC_APB1ENR_STATE_No_RESET_LPM)
		{
			RCC->APB1LPENR &= (RCC_APB1_MASKING_LPM << (RCC_APB1ENR_CONFIG_LPM -> RCC_APB1ENR_PORT_LPM)); //Clear Bit of GPIO Port.
		}
		else if ((RCC_APB1ENR_CONFIG_LPM -> RCC_APB1ENR_STATE_LPM) == RCC_APB1ENR_STATE_RESET_LPM)
		{
			RCC->APB1LPENR |= (RCC_APB1_SET_BIT_LPM<< (RCC_APB1ENR_CONFIG_LPM -> RCC_APB1ENR_PORT_LPM)); //Set Bit of GPIO Port.
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}


/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_APB1ENR_CONFIG
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_2_CLKConfiguration_LPM_LPM(RCC_APB2ENR_CONFIG_LPM_t * RCC_APB2ENR_CONFIG_LPM)
{
	uint8_t	Local_u8ErrorState = OK;
	if(((RCC_APB2ENR_CONFIG_LPM -> RCC_APB2ENR_PORT_LPM) <= SAI2)&&(((RCC_APB2ENR_CONFIG_LPM -> RCC_APB2ENR_STATE_LPM) <= RCC_APB2ENR_STATE_No_RESET_LPM)))
	{
		// Configure Port.
		RCC->APB2LPENR &= (RCC_APB2_MASKING_LPM << (RCC_APB2ENR_CONFIG_LPM -> RCC_APB2ENR_PORT_LPM)); //Clear Bit of GPIO Port.
		// Configure State Enable or Disable.
		if ((RCC_APB2ENR_CONFIG_LPM -> RCC_APB2ENR_STATE_LPM) == RCC_APB2ENR_STATE_No_RESET_LPM)
		{
			RCC->APB2LPENR &= (RCC_APB2_MASKING_LPM << (RCC_APB2ENR_CONFIG_LPM -> RCC_APB2ENR_PORT_LPM)); //Clear Bit of GPIO Port.
		}
		else if ((RCC_APB2ENR_CONFIG_LPM -> RCC_APB2ENR_STATE_LPM) == RCC_APB2ENR_STATE_RESET_LPM)
		{
			RCC->APB2LPENR |= (RCC_APB2_SET_BIT_LPM<< (RCC_APB2ENR_CONFIG_LPM -> RCC_APB2ENR_PORT_LPM)); //Set Bit of GPIO Port.
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
