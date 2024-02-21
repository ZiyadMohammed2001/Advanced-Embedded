
#include <stdint.h>
#include "Stm32F103.h"
#include "ErrType.h"

#include "USART_interface.h"
#include "USART_prv.h"
#include "USART_Config.h"

static void(*USART_Apf[USART_TOTAL_NUM][USART_TOTAL_INTERRUPT_NUM])(void) = {NULL}; //Array of pointer to functions For call back Function.
static USART_RegDef_t * USART_Num [USART_TOTAL_NUM] = {USART_1_REGISTER,USART_2_REGISTER,USART_3_REGISTER,UART_4_REGISTER,UART_5_REGISTER};

uint8_t USART_u8Init(const USART_Config_t* USART_Config)
{
	uint8_t Local_u8ErrorState = OK;
	uint32_t Local_u32Baudrate = 0;
	uint32_t Local_u32Mantissa = 0;
	uint32_t Local_u32DIV_Fraction = 0;
	/*Select Rx Mode*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_RX_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_Rx_Mode)<<USART_CR1_RX_BIT);
	/*Select Tx Mode*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_TX_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_Tx_Mode)<<USART_CR1_TX_BIT);
	/*Enable transfer Data interrupts*/
	if (USART_Config->USART_Tx_Mode)
	{
		/*Enable Interrupt for data register empty*/
		USART_Num[USART_Config->USART_Number]->USART_CR1 &= (~(USART_SET <<USART_CR1_TXEIE_BIT));
		USART_Num[USART_Config->USART_Number]->USART_CR1 |= (USART_SET <<USART_CR1_TXEIE_BIT);
		/*Enable Interrupt for Transmission Complete*/
		USART_Num[USART_Config->USART_Number]->USART_CR1 &= (~(USART_SET <<USART_CR1_TC_BIT));
		USART_Num[USART_Config->USART_Number]->USART_CR1 |= (USART_SET <<USART_CR1_TC_BIT);
	}
	if (USART_Config->USART_Rx_Mode)
	{
		/*Enable Interrupt for read data register empty*/
		USART_Num[USART_Config->USART_Number]->USART_CR1 &= (~(USART_SET <<USART_CR1_RXNEIE_BIT));
		USART_Num[USART_Config->USART_Number]->USART_CR1 |= (USART_SET <<USART_CR1_RXNEIE_BIT);
	}
	/*Select Stop Bit*/
	USART_Num[USART_Config->USART_Number]->USART_CR2 &= USART_STOP_BITS_MasK;
	USART_Num[USART_Config->USART_Number]->USART_CR2 |= ((USART_Config->USART_Stop_Bit)<<USART_STOP_BITS_BIT);
	/*Select parity Control*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_PCE_BIT_MasK;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |=((USART_Config->USART_ParityControl)<<USART_PCE_BIT_BIT);
	/*Select parity Selection odd or even*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_PS_BIT_MasK;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |=((USART_Config->USART_ParitySelection)<<USART_PS_BIT_BIT);
	/*Select Word Length*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_WL_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_WordLength)<<USART_CR1_WL_BIT);
	/*Select Wake up method*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_WL_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR1_WAKE_BIT);
	/*Hardware flow control.*/
	/*CTSE Mode:*/
	USART_Num[USART_Config->USART_Number]->USART_CR3 &= USART_CR3_CTS_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR3 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR3_CTS_BIT);
	/*CTSE Mode:*/
	USART_Num[USART_Config->USART_Number]->USART_CR3 &= USART_CR3_RTS_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR3 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR3_RTS_BIT);
	/*DMA Mode*/
	/*DMA Enable transmitter*/
	USART_Num[USART_Config->USART_Number]->USART_CR3 &= USART_CR3_DMA_T_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR3 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR3_DMA_T_BIT);
	/*DMA Enable Receiver*/
	USART_Num[USART_Config->USART_Number]->USART_CR3 &= USART_CR3_DMA_R_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR3 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR3_DMA_R_BIT);

	/*Security interrupt*/
	/*Check if hardware flow control is used*/
	if (USART_Config->USART_CTSE_Mode)
	{
		/*Enable CTSE Interrupt*/
		USART_Num[USART_Config->USART_Number]->USART_CR3 |= (USART_SET	<<	USART_CR3_CTSIE_BIT);
	}
	/*Enable LBDIE*/
	USART_Num[USART_Config->USART_Number]->USART_CR2 |= (USART_SET	<<	USART_CR2_LBDIE_BIT);
	/*Enable IDLE*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= (USART_SET	<<	USART_CR1_IDLEIE_BIT);
	/*Over run error*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= (USART_SET<<USART_CR1_RXNEIE_BIT);
	/*Enable PE*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_PE_ENABLE_DISABLE);
	/*Calculate baud rate*/

	/*Over sample by 8.*/
	Local_u32Baudrate = ((FREQUENCT_CLK_OF_MC_MHz * USART_OS)/(USART_BAUDRATE*(USART_Config->BaudRate))) ;

	Local_u32Mantissa = Local_u32Baudrate%1000;
	Local_u32DIV_Fraction = (((Local_u32Mantissa * FREQUENCT_CLK_OF_MC_MHz) + USART_DIV_Fraction_Round )/USART_DIV_Fraction_REAl);
	USART_Num[USART_Config->USART_Number]->USART_BRR = Local_u32Mantissa	<<	USART_Mantissa_SHIFT;
	USART_Num[USART_Config->USART_Number]->USART_BRR |= Local_u32DIV_Fraction;
	return Local_u8ErrorState;
}

uint8_t USART_u8_EnableTransfer(uint8_t Copy_u8_USART_Num)
{
	uint8_t Local_u8ErrorState = OK;
	USART_Num[Copy_u8_USART_Num]->USART_CR1 |= (USART_SET <<USART_CR1_ENABLE_DISABLE);
	return Local_u8ErrorState;
}

uint8_t USART_u8_DisableTransfer(uint8_t Copy_u8_USART_Num)
{
	uint8_t Local_u8ErrorState = OK;
	USART_Num[Copy_u8_USART_Num]->USART_CR1 &= (~(USART_SET <<USART_CR1_ENABLE_DISABLE));
	return Local_u8ErrorState;
}

uint8_t USART_u8_TransferData (uint8_t Copy_u8_USART_Num, uint32_t Copy_Pu32Data)
{
	uint8_t Local_u8ErrorState = OK;
	/*Check Transfer Data empty*/
	while (!((USART_Num[Copy_u8_USART_Num] -> USART_SR)>> USART_SR_TXE_BIT));
	/*Transmit data*/
	(USART_Num[Copy_u8_USART_Num] -> USART_DR ) = Copy_u8_USART_Num;
	/*Check if transfer complete*/
	while ((USART_Num[Copy_u8_USART_Num] -> USART_SR)>> USART_SR_TC_BIT);
	return Local_u8ErrorState;
}

uint8_t USART_u8_RecieveData (uint8_t Copy_u8_USART_Num, uint32_t *Copy_Pu32Data)
{
	uint8_t Local_u8ErrorState = OK;
	if (Copy_Pu32Data != NULL)
	{
		/*Check read data register is empty*/
		while (!((USART_Num[Copy_u8_USART_Num] -> USART_SR)>> USART_SR_RXNE_BIT));
		/*Read Data*/
		*Copy_Pu32Data = (USART_Num[Copy_u8_USART_Num] -> USART_DR );
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t USART_u8_SetCallBack (uint8_t Copy_u8_USART_Num,USART_Interrupt_Name_t USART_Interrupt_Name,void(*Copy_pf)(void))
{
	uint8_t Local_u8ErrorState = OK;
	if((Copy_u8_USART_Num <=USART_TOTAL_NUM)&&(USART_Interrupt_Name<=USART_TOTAL_INTERRUPT_NUM)&& (Copy_pf!=NULL))
	{
		// Update global pointer to function.
		USART_Apf[Copy_u8_USART_Num][USART_Interrupt_Name] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/*Interrupt Handle*/
void USART1_IRQHandler (void)
{
	if ((USART_Num[USART_1] -> USART_SR)>> USART_SR_CTS_FALG_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_1] -> USART_SR) &= USART_SR_CTS_FALG_MASK;
		/*Action for CTS Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_CTS]();
	}
	if ((USART_Num[USART_1] -> USART_SR)>> USART_SR_LBD_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_1] -> USART_SR) &= (~(USART_SET	<<	USART_SR_LBD_BIT));
		/*Action for LBD Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_LBD]();
	}
	if((USART_Num[USART_1] -> USART_SR)>>USART_SR_TXE_BIT)
	{
		/*Action for TXE Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_TXE]();
	}
	if ((USART_Num[USART_1] -> USART_SR)>> USART_SR_TC_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_1] -> USART_SR) &= (~(USART_SET<<USART_SR_TC_BIT));
		/*Action for TC Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_TC]();
	}
	if ((USART_Num[USART_1] -> USART_SR)>> USART_SR_RXNE_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_1] -> USART_SR) &= (~(USART_SET<<USART_SR_RXNE_BIT));
		/*Action for RXNE Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_RXNE]();
	}
	if((USART_Num[USART_1] -> USART_SR)>>USART_SR_IDLE_BIT)
	{
		/*Action for IDLE Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_IDLE]();
	}
	if ((USART_Num[USART_1] -> USART_SR)>> USART_ORE_BIT )
	{
		/*Action for ORE Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_ORE]();
	}
	if ((USART_Num[USART_1] -> USART_SR)>> USART_NF_BIT )
	{
		/*Action for NF Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_NF]();
	}
	if((USART_Num[USART_1] -> USART_SR)>>USART_FE_BIT)
	{
		/*Action for FE Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_FE]();
	}
	if((USART_Num[USART_1] -> USART_SR)>>USART_PE_BIT)
	{
		/*Wait for RXNE Flag to be set*/
		while (!(((USART_Num[USART_1] -> USART_SR)>> USART_SR_RXNE_BIT )));
		/*Action for PE Flag*/
		USART_Apf[USART_1][USART_INTERRUPT_PE]();
	}
}
void USART2_IRQHandler (void)
{
	if ((USART_Num[USART_2] -> USART_SR)>> USART_SR_CTS_FALG_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_2] -> USART_SR) &= USART_SR_CTS_FALG_MASK;
		/*Action for CTS Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_CTS]();
	}
	if ((USART_Num[USART_2] -> USART_SR)>> USART_SR_LBD_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_2] -> USART_SR) &= (~(USART_SET	<<	USART_SR_LBD_BIT));
		/*Action for LBD Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_LBD]();
	}
	if((USART_Num[USART_2] -> USART_SR)>>USART_SR_TXE_BIT)
	{
		/*Action for TXE Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_TXE]();
	}
	if ((USART_Num[USART_2] -> USART_SR)>> USART_SR_TC_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_2] -> USART_SR) &= (~(USART_SET<<USART_SR_TC_BIT));
		/*Action for TC Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_TC]();
	}
	if ((USART_Num[USART_2] -> USART_SR)>> USART_SR_RXNE_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_2] -> USART_SR) &= (~(USART_SET <<USART_SR_RXNE_BIT));
		/*Action for RXNE Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_RXNE]();
	}
	if((USART_Num[USART_2] -> USART_SR)>>USART_SR_IDLE_BIT)
	{
		/*Action for IDLE Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_IDLE]();
	}
	if ((USART_Num[USART_2] -> USART_SR)>> USART_ORE_BIT )
	{
		/*Action for ORE Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_ORE]();
	}
	if ((USART_Num[USART_2] -> USART_SR)>> USART_NF_BIT )
	{
		/*Action for NF Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_NF]();
	}
	if((USART_Num[USART_2] -> USART_SR)>>USART_FE_BIT)
	{
		/*Action for FE Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_FE]();
	}
	if((USART_Num[USART_2] -> USART_SR)>>USART_PE_BIT)
	{
		/*Wait for RXNE Flag to be set*/
		while (!(((USART_Num[USART_2] -> USART_SR)>> USART_SR_RXNE_BIT )));
		/*Action for PE Flag*/
		USART_Apf[USART_2][USART_INTERRUPT_PE]();
	}
}
void USART3_IRQHandler (void)
{
	if ((USART_Num[USART_3] -> USART_SR)>> USART_SR_CTS_FALG_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_3] -> USART_SR) &= USART_SR_CTS_FALG_MASK;
		/*Action for CTS Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_CTS]();
	}
	if ((USART_Num[USART_3] -> USART_SR)>> USART_SR_LBD_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_3] -> USART_SR) &= (~(USART_SET	<<	USART_SR_LBD_BIT));
		/*Action for LBD Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_LBD]();
	}
	if((USART_Num[USART_3] -> USART_SR)>>USART_SR_TXE_BIT)
	{
		/*Action for TXE Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_TXE]();
	}
	if ((USART_Num[USART_3] -> USART_SR)>> USART_SR_TC_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_3] -> USART_SR) &= (~(USART_SET <<USART_SR_TC_BIT));
		/*Action for TC Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_TC]();
	}
	if ((USART_Num[USART_3] -> USART_SR)>> USART_SR_RXNE_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_3] -> USART_SR) &= (~(USART_SET <<USART_SR_RXNE_BIT));
		/*Action for RXNE Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_RXNE]();
	}
	if((USART_Num[USART_3] -> USART_SR)>>USART_SR_IDLE_BIT)
	{
		/*Action for IDLE Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_IDLE]();
	}
	if ((USART_Num[USART_3] -> USART_SR)>> USART_ORE_BIT )
	{
		/*Action for ORE Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_ORE]();
	}
	if ((USART_Num[USART_3] -> USART_SR)>> USART_NF_BIT )
	{
		/*Action for NF Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_NF]();
	}
	if((USART_Num[USART_3] -> USART_SR)>>USART_FE_BIT)
	{
		/*Action for FE Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_FE]();
	}
	if((USART_Num[USART_3] -> USART_SR)>>USART_PE_BIT)
	{
		/*Wait for RXNE Flag to be set*/
		while (!(((USART_Num[USART_3] -> USART_SR)>> USART_SR_RXNE_BIT )));
		/*Action for PE Flag*/
		USART_Apf[USART_3][USART_INTERRUPT_PE]();
	}
}
void UART4_IRQHandler (void)
{
	if ((USART_Num[USART_4] -> USART_SR)>> USART_SR_LBD_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_4] -> USART_SR) &= (~(USART_SET	<<	USART_SR_LBD_BIT));
		/*Action for LBD Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_LBD]();
	}
	if((USART_Num[USART_4] -> USART_SR)>>USART_SR_TXE_BIT)
	{
		/*Action for TXE Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_TXE]();
	}
	if ((USART_Num[USART_4] -> USART_SR)>> USART_SR_TC_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_4] -> USART_SR) &= (~(USART_SET <<USART_SR_TC_BIT));
		/*Action for TC Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_TC]();
	}
	if ((USART_Num[USART_4] -> USART_SR)>> USART_SR_RXNE_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_4] -> USART_SR) &= (~(USART_SET <<USART_SR_RXNE_BIT));
		/*Action for RXNE Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_RXNE]();
	}
	if((USART_Num[USART_4] -> USART_SR)>>USART_SR_IDLE_BIT)
	{
		/*Action for IDLE Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_IDLE]();
	}
	if ((USART_Num[USART_4] -> USART_SR)>> USART_ORE_BIT )
	{
		/*Action for ORE Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_ORE]();
	}
	if ((USART_Num[USART_4] -> USART_SR)>> USART_NF_BIT )
	{
		/*Action for NF Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_NF]();
	}
	if((USART_Num[USART_4] -> USART_SR)>>USART_FE_BIT)
	{
		/*Action for FE Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_FE]();
	}
	if((USART_Num[USART_4] -> USART_SR)>>USART_PE_BIT)
	{
		/*Wait for RXNE Flag to be set*/
		while (!(((USART_Num[USART_4] -> USART_SR)>> USART_SR_RXNE_BIT )));
		/*Action for PE Flag*/
		USART_Apf[USART_4][USART_INTERRUPT_PE]();
	}
}
void UART5_IRQHandler (void)
{
	if ((USART_Num[USART_5] -> USART_SR)>> USART_SR_LBD_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_5] -> USART_SR) &= (~(USART_SET	<<	USART_SR_LBD_BIT));
		/*Action for LBD Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_LBD]();
	}
	if((USART_Num[USART_5] -> USART_SR)>>USART_SR_TXE_BIT)
	{
		/*Action for TXE Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_TXE]();
	}
	if ((USART_Num[USART_5] -> USART_SR)>> USART_SR_TC_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_5] -> USART_SR) &= (~(USART_SET <<USART_SR_TC_BIT));
		/*Action for TC Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_TC]();
	}
	if ((USART_Num[USART_5] -> USART_SR)>> USART_SR_RXNE_BIT )
	{
		/*Clear flag*/
		(USART_Num[USART_5] -> USART_SR) &= (~(USART_SET <<USART_SR_RXNE_BIT));
		/*Action for RXNE Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_RXNE]();
	}
	if((USART_Num[USART_5] -> USART_SR)>>USART_SR_IDLE_BIT)
	{
		/*Action for IDLE Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_IDLE]();
	}
	if ((USART_Num[USART_5] -> USART_SR)>> USART_ORE_BIT )
	{
		/*Action for ORE Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_ORE]();
	}
	if ((USART_Num[USART_5] -> USART_SR)>> USART_NF_BIT )
	{
		/*Action for NF Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_NF]();
	}
	if((USART_Num[USART_5] -> USART_SR)>>USART_FE_BIT)
	{
		/*Action for FE Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_FE]();
	}
	if((USART_Num[USART_5] -> USART_SR)>>USART_PE_BIT)
	{
		/*Wait for RXNE Flag to be set*/
		while (!(((USART_Num[USART_5] -> USART_SR)>> USART_SR_RXNE_BIT )));
		/*Action for PE Flag*/
		USART_Apf[USART_5][USART_INTERRUPT_PE]();
	}
}
