#include <stdint.h>
#include "Stm32F103.h"
#include "ErrType.h"

#include "RCC_Interface.h"
#include "RCC_Cfg.h"
#include "RCC_Private.h"

/******************************************************************************
 * Function Name:  RCC_u8SetClkStatusSynch
 * Description:	The Function that Set Clock Status
 * Parameters: CLKStatus structure hold configuration
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8SetClkStatusSynch(RCC_CLKStatus_t * RCC_CLKStatus)
{
	uint8_t Local_u8ErrorState=OK;
	uint32_t Local_u8TimeOut=0;
	switch(RCC_CLKStatus->RCC_SYSCLK)
	{
	case RCC_HSI:
		/* high-speed Internal  is  SYSCLK*/
		if(RCC_CLKStatus->RCC_CLkState)
		{
			/*HSI clock enable.*/
			RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSION));
			RCC->RCC_CR |= (RCC_SET_CLR_BIT<<RCC_HSION);
			/*Wait to ready flag - THRESHOLD_VALUE  time out*/
			while(((((RCC->RCC_CR) >> RCC_HSIRDY)&RCC_SET_CLR_BIT)==0) && (Local_u8TimeOut <= THRESHOLD_VALUE))
			{
				Local_u8TimeOut++;
			}
			if (Local_u8TimeOut >= THRESHOLD_VALUE)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if (!(RCC_CLKStatus->RCC_CLkState))
		{
			/*HSI clock disable.*/
			RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSION));
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
		break;
	case RCC_HSE:// high-speed External (CR/CY) is  SYSCLK
		if(RCC_CLKStatus->RCC_CLkState)
		{
			// HSE clock enable
			RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSEON));
			RCC->RCC_CR |= (RCC_SET_CLR_BIT<<RCC_HSEON);
			// wait to ready flag - THRESHOLD_VALUE  time out
			while(((((RCC->RCC_CR) >> RCC_HSERDY)&RCC_SET_CLR_BIT)==0) && (Local_u8TimeOut <= THRESHOLD_VALUE))
			{
				Local_u8TimeOut++;
			}
			if (Local_u8TimeOut >= THRESHOLD_VALUE)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if (!(RCC_CLKStatus->RCC_CLkState))
		{
			// HSE clock disable
			RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSEON));
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
		break;
	case RCC_PLL:// PLL is  SYSCLK


		if(RCC_CLKStatus->RCC_CLkState)
		{
			/*Enable PLL*/
			RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_PLLON));
			RCC->RCC_CR |= (RCC_SET_CLR_BIT<<RCC_PLLON);
			// Wait Ready flag.
			while(((((RCC->RCC_CR) >> RCC_PLLRDY)&RCC_SET_CLR_BIT)==0) && (Local_u8TimeOut <= THRESHOLD_VALUE))
			{
				Local_u8TimeOut++;
			}
			if (Local_u8TimeOut >= THRESHOLD_VALUE)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if (!(RCC_CLKStatus->RCC_CLkState))
		{
			/*Disable*/
			RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_PLLON));
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
		break;
	default :Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8SetSysClk
 * Description:	The Function Set SYSCLk source (System clock switch)
 * Parameters: Copy_u8SysClk SYSCLK  option   RCC_HSI  | RCC_HSE |RCC_PLL
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tSetSysClk(uint8_t Copy_u8SysClk)
{
	uint8_t Local_u8ErrorState=OK;
	if (Copy_u8SysClk <=RCC_PLL)
	{
		/*selected  system clock*/
		(RCC->RCC_CFGR) &=~(RCC_SW_MASK);
		(RCC->RCC_CFGR) |=(Copy_u8SysClk);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8DisableClkStatus
 * Description:	The Function disable CLK
 * Parameters: Copy_u8clock RCC_HSI  | RCC_HSE |RCC_PLL
 * Return:	ErrorState , Type:u8
 ******************************************************************************/
uint8_t RCC_u8DisableClkStatus(uint8_t Copy_u8clock)
{
	uint8_t Local_u8ErrorState=OK;
	switch (Copy_u8clock)
	{
	case RCC_HSI : RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSION));break;
	case RCC_HSE : RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSEON));break;
	case RCC_PLL : RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_PLLON));break;
	default :Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8SetSysClk
 * Description:	The Function Set HSE Configuration
 * Parameters: Copy_u8HSE_Div  option  HSE_NOT_DIVIDED | HSE_DIVIDED_BY_TOW
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8HSEConfig(uint8_t Copy_u8HSE_Div)
{
	uint8_t Local_u8ErrorState=OK;
	/*switch SYSCLK */
	RCC_u8SetSysClk(RCC_HSI);
	// HSE clock disable
	RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSION));
	/*change configuration*/
	if (Copy_u8HSE_Div<=HSE_DIVIDED_BY_TWO)
	{
		RCC->RCC_CFGR &=	~((RCC_HSE_SW_MASK)<<RCC_PLLXTPRE);
		RCC->RCC_CFGR |=	(Copy_u8HSE_Div<<RCC_PLLXTPRE);
	}
	else if (Copy_u8HSE_Div<=HSE_NOT_DIVIDED)
	{
		RCC->RCC_CFGR &=	~((RCC_HSE_SW_MASK)<<RCC_PLLXTPRE);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8HSESource
 * Description:	The Function Select HES
 * Parameters: Copy_u8HSE_Div  options:  HSE_NOTBYPASS	HSE_BYPASS
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8HSESource(uint8_t Copy_u8Source )
{
	uint8_t Local_u8ErrorState=OK;
	/*switch SYSCLK */
	RCC_u8SetSysClk(RCC_HSI);
	// HSE clock disable
	RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSEON));
	if (Copy_u8Source<=HSE_BYPASS)
	{
		(RCC->RCC_CR)&=~((RCC_HSE_BYBASS_MASK)<<RCC_HSEBYP);
		(RCC->RCC_CR)|=((Copy_u8Source)<<RCC_HSEBYP);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8PLLConfig
 * Description:	The Function Set PLL Configuration)
 * Parameters: PLL_Cfg
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8PLLConfig(PLL_CFg_t * PLL_Cfg)
{
	uint8_t Local_u8ErrorState=OK;
	/*switch SYSCLK */
	RCC_u8SetSysClk(RCC_HSI);
	// HSE clock disable.
	RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_PLLON));
	/*change configuration*/
	// PLL input clock options
	RCC->RCC_CFGR &=~ ((RCC_PLL_MASK)<<RCC_PLLMUL);
	RCC->RCC_CFGR |=((PLL_Cfg->RCC_PLL_Factor)<<RCC_PLLMUL);
	//PLL source
	switch (PLL_Cfg->RCC_PLL_CLK)
	{
	case PLL_HSI :
		RCC->RCC_CFGR &= (~(RCC_SET_CLR_BIT<<RCC_PLLSRC));
		break;
	case PLL_HSE :
		if ((PLL_Cfg->RCC_HSE_DividerPll)==HSE_NOT_DIVIDED)
		{
			RCC_u8HSEConfig(PLL_Cfg->RCC_HSE_DividerPll);
			RCC->RCC_CFGR &= (~(RCC_SET_CLR_BIT<<RCC_PLLSRC));
		}
		else if ((PLL_Cfg->RCC_HSE_DividerPll)==HSE_DIVIDED_BY_TWO)
		{
			RCC_u8HSEConfig(PLL_Cfg->RCC_HSE_DividerPll);
			RCC->RCC_CFGR &= (~(RCC_SET_CLR_BIT<<RCC_PLLSRC));
			RCC->RCC_CFGR |= (RCC_SET_CLR_BIT<<RCC_PLLSRC);
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
		break;
	default :Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/******************************************************************************
 * Function Name:  RCC_u8SetSysClock
 * Description:	The Function Select sys=tem clock and disable others.
 * Parameters: Copy_u8Peripheral : RCC_SYSCLK
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/

uint8_t RCC_u8SetSysClock(RCC_SYSCLK_t RCC_SYSCLK)
{
	uint8_t Local_u8ErrorState = 0;

	switch (RCC_SYSCLK)
	{
	/*Set HSI as sysclk*/
	case RCC_HSI :
		/*HSI clock enable.*/
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSION));
		RCC->RCC_CR |= (RCC_SET_CLR_BIT<<RCC_HSION);
		// HSE clock disable
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSEON));
		/*PLL Clock Disable*/
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_PLLON));
		break;
		/*Set HSE as sysclk*/
	case RCC_HSE :
		// HSE clock enable
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSEON));
		RCC->RCC_CR |= (RCC_SET_CLR_BIT<<RCC_HSEON);
		/*PLL Clock Disable*/
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_PLLON));
		/*HSI clock disable.*/
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSION));
		break;
		/*Set PLL as sysclk*/
	case RCC_PLL :
		/*Enable PLL*/
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_PLLON));
		RCC->RCC_CR |= (RCC_SET_CLR_BIT<<RCC_PLLON);
		// HSE clock disable
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSEON));
		/*HSI clock disable.*/
		RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_HSION));
		break;
	default : Local_u8ErrorState = 1;
	}
	return Local_u8ErrorState;
}



/******************************************************************************
 * Function Name:  RCC_u8AHBEnableCLK
 * Description:	The Function enable AHB Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8AHBEnableCLK(uint8_t Copy_u8Peripheral)
{
	uint8_t Local_u8ErrorState =OK;
	if (Copy_u8Peripheral <=SDIOEN)
	{

		/* Enable  Peripheral CLK */
		RCC->RCC_AHBENR &= (~(RCC_SET_CLR_BIT<<Copy_u8Peripheral));
		RCC->RCC_AHBENR |= (RCC_SET_CLR_BIT<<Copy_u8Peripheral);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8AHB1EnableCLK
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB1EnableCLK(uint8_t Copy_u8Peripheral)
{
	uint8_t Local_u8ErrorState =OK;
	if (Copy_u8Peripheral <=DACEN)
	{
		/*Enable  Peripheral CLK*/
		RCC->RCC_APB1ENR &= (~(RCC_SET_CLR_BIT<<Copy_u8Peripheral));
		RCC->RCC_APB1ENR |= (RCC_SET_CLR_BIT<<Copy_u8Peripheral);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8AHB2EnableCLK
 * Description:	The Function enable APB2 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB2EnableCLK(uint8_t Copy_u8Peripheral)
{
	uint8_t Local_u8ErrorState =OK;
	if (Copy_u8Peripheral <=TIM11EN)
	{
		/*Enable  Peripheral CLK*/
		RCC->RCC_APB2ENR &= (~(RCC_SET_CLR_BIT<<Copy_u8Peripheral));
		RCC->RCC_APB2ENR |= (RCC_SET_CLR_BIT<<Copy_u8Peripheral);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8AHBEnableCLK
 * Description:	The Function Disable AHB Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8AHBDisableCLK(uint8_t Copy_u8Peripheral)
{
	uint8_t Local_u8ErrorState =OK;
	if (Copy_u8Peripheral <=SDIOEN)
	{

		/*Disable  Peripheral CLK */
		RCC->RCC_AHBENR &= (~(RCC_SET_CLR_BIT<<Copy_u8Peripheral));
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;

}
/******************************************************************************
 * Function Name:  RCC_u8AHB1EnableCLK
 * Description:	The Function Disable APB1 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB1DisableCLK(uint8_t Copy_u8Peripheral)
{
	uint8_t Local_u8ErrorState =OK;
	if (Copy_u8Peripheral <=DACEN)
	{
		/* disable  Peripheral CLK */
		RCC->RCC_APB1ENR &= (~(RCC_SET_CLR_BIT<<Copy_u8Peripheral));
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/******************************************************************************
 * Function Name:  RCC_u8AHB1EnableCLK
 * Description:	The Function Disable APB2 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB2DisableCLK(uint8_t Copy_u8Peripheral)
{
	uint8_t Local_u8ErrorState =OK;
	if (Copy_u8Peripheral <=TIM11EN)
	{
		/* disable  Peripheral CLK */
		RCC->RCC_APB2ENR &= (~(RCC_SET_CLR_BIT<<Copy_u8Peripheral));
	}
	else
	{
		Local_u8ErrorState=NOK;
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
	RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_CSSON));
	RCC->RCC_CR |= (RCC_SET_CLR_BIT<<RCC_CSSON);
}
/******************************************************************************
 * Function Name:  RCC_ClockSecuritySystemEnable
 * Description:	Clock Security System Disable
 * Parameters: non
 * Return:	non
 ******************************************************************************/
void RCC_ClockSecuritySystemDisable(void)
{
	RCC->RCC_CR &= (~(RCC_SET_CLR_BIT<<RCC_CSSON));
}
