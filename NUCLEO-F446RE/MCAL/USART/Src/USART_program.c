
#include <stdint.h>
#include "Stm32f446.h"
#include "ErrType.h"

#include "USART_interface.h"
#include "USART_prv.h"
#include "USART_Config.h"

static void(*USART_Apf[USART_TOTAL_NUM][USART_TOTAL_INTERRUPT_NUM])(void) = {NULL}; //Array of pointer to functions For call back Function.

static USART_RegDef_t * USART_Num [USART_TOTAL_NUM] = {USART_1_REGISTER,USART_2_REGISTER,USART_3_REGISTER,UART_4_REGISTER,UART_5_REGISTER,USART_6_REGISTER};

static uint8_t USART_RecieveBufferFlag[USART_TOTAL_NUM] 	= {0};

static uint8_t USART_TransmitBufferFlag[USART_TOTAL_NUM] 	= {0};

static uint8_t USART_RecieveBufferSize[USART_TOTAL_NUM] 	= {0};

static uint8_t *USART_RecievedBuffer[USART_TOTAL_NUM] 		= {NULL};

static uint8_t USART_TransmitBufferSize[USART_TOTAL_NUM] 	= {0};

static uint8_t *USART_TransmitBuffer[USART_TOTAL_NUM] 		= {NULL};


void USART_SettingBaudRate(USART_BaudRate_Config_t *USART_BaudRate_Config)
{
	float USART_DIV = 0;

	uint32_t DIV_Fraction = 0;
	USART_Num[USART_BaudRate_Config -> USART_Number]->USART_BRR = 0;

	/* BaudRate Equation */
	USART_DIV = FREQUENCT_CLK_OF_MC_MHz / (float)(8U * (2U - (USART_BaudRate_Config -> USART_OverSampling)) * (USART_BaudRate_Config ->USART_BaudRate));
	USART_DIV *= 1000UL;

	/* Set the Mantissa Part */
	USART_Num[USART_BaudRate_Config -> USART_Number]-> USART_BRR |= ((uint32_t)USART_DIV / 1000UL) << USART_Mantissa_SHIFT;

	/* Calculte the Fraction */
	DIV_Fraction = (uint32_t)USART_DIV % 1000UL;

	DIV_Fraction = DIV_Fraction * (USART_BAUDRATE / ((USART_BaudRate_Config -> USART_OverSampling) + 1));

	/* get Round */
	DIV_Fraction += USART_DIV_Fraction_Round;

	USART_Num[USART_BaudRate_Config -> USART_Number]-> USART_BRR  |= (uint32_t)(DIV_Fraction / 1000UL);
}

void USART_voidInterruptConfig(USART_Interrupts_t *USART_Interrupts)
{
	/* Clearing Interrupt Bits */
	USART_Num[USART_Interrupts->USART_Number]->USART_CR1 &= USART_INTERRUPT_BIT_MASKING;
	/* Configure Interrupt Bits */
	/* Setting IDLE Interrupt */
	USART_Num[USART_Interrupts->USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_IDLEIE_BIT);
	/* Setting RXNE Interrupt */
	USART_Num[USART_Interrupts->USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_RXNEIE_BIT);
	/* Setting TC Interrupt */
	USART_Num[USART_Interrupts->USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_TC_BIT);
	/* Setting TXE Interrupt */
	USART_Num[USART_Interrupts->USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_TXEIE_BIT);
	/* Setting PE Interrupt */
	USART_Num[USART_Interrupts->USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_PE_ENABLE_DISABLE);
}

uint8_t USART_ReadFlag(USART_Number_t USART_Number, USART_Interrupt_Flag_t USART_Interrupt_Flag, uint8_t *Copy_pu8_FlagStatus)
{
	uint8_t Local_u8ErrorState = OK;
	/* Read Flag & return it */
	*Copy_pu8_FlagStatus = ((USART_Num[USART_Number]->USART_SR >> USART_Interrupt_Flag) & USART_SET);
	return Local_u8ErrorState;
}

uint8_t USART_u8Init(const USART_Config_t* USART_Config , const USART_Interrupts_t *USART_Interrupts)
{
	uint8_t Local_u8ErrorState = OK;
	/*Setting baud rate.*/
	USART_BaudRate_Config_t USART_BaudRate_Config_init =
	{
			.USART_Number = USART_Config->USART_Number,
			.USART_BaudRate = USART_Config->USART_BaudRate,
			.USART_OverSampling = USART_Config->USART_OverSampling,

	};
	USART_SettingBaudRate (&USART_BaudRate_Config_init);

	/*Select Rx Mode*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_RX_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_Rx_Mode)<<USART_CR1_RX_BIT);

	/*Select Tx Mode*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_TX_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_Tx_Mode)<<USART_CR1_TX_BIT);

	/*Select Stop Bit*/
	USART_Num[USART_Config->USART_Number]->USART_CR2 &= USART_STOP_BITS_MasK;
	USART_Num[USART_Config->USART_Number]->USART_CR2 |= ((USART_Config->USART_Stop_Bit)<<USART_STOP_BITS_BIT);

	/*Select parity Control*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_PCE_BIT_MasK;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |=((USART_Config->USART_ParityControl)<<USART_PCE_BIT_BIT);

	/*Select parity Selection odd or even*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_PS_BIT_MasK;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |=((USART_Config->USART_ParitySelection)<<USART_PS_BIT_BIT);

	/*Select over sampling.*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_OVER8_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_OverSampling)<<USART_CR1_OVER8_BIT);

	/*Select Word Length*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_WL_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_WordLength)<<USART_CR1_WL_BIT);

	/*Select Wake up method*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= USART_CR1_WL_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR1_WAKE_BIT);

	/*Sample Method.*/
	USART_Num[USART_Config->USART_Number]->USART_CR3 &= USART_CR3_SAMPLE_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR3 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR3_SAMPLE_BIT);

	/*Hardware flow control.*/
	/*CTSE Mode:*/
	USART_Num[USART_Config->USART_Number]->USART_CR3 &= USART_CR3_CTS_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR3 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR3_CTS_BIT);

	/*CTSE Mode:*/
	USART_Num[USART_Config->USART_Number]->USART_CR3 &= USART_CR3_RTS_Mask;
	USART_Num[USART_Config->USART_Number]->USART_CR3 |= ((USART_Config->USART_WakeUpMethod)<<USART_CR3_RTS_BIT);

	/*Setting initial state interrupts*/
	USART_Interrupts_t USART_Interrupts_init =
	{
			.USART_Number 	= USART_Interrupts->USART_Number,
			.USART_PE 		= USART_Interrupts->USART_PE,
			.USART_TX 		= USART_Interrupts->USART_TX,
			.USART_TC 		= USART_Interrupts->USART_TC,
			.USART_RXN 		= USART_Interrupts->USART_RXN,
			.USART_IDLE 	= USART_Interrupts->USART_IDLE,
	};
	USART_voidInterruptConfig (&USART_Interrupts_init);
	/*USART Initial State*/
	USART_Num[USART_Config->USART_Number]->USART_CR1 &= (~(USART_SET <<USART_CR1_ENABLE_DISABLE));
	USART_Num[USART_Config->USART_Number]->USART_CR1 |= ((USART_Config -> USART_InitialState) <<USART_CR1_ENABLE_DISABLE);
	return Local_u8ErrorState;
}

uint8_t USART_u8_EnableTransfer(uint8_t Copy_u8_USART_Num)
{
	uint8_t Local_u8ErrorState = OK;
	USART_Num[Copy_u8_USART_Num]->USART_CR1 &= (~(USART_SET <<USART_CR1_ENABLE_DISABLE));
	USART_Num[Copy_u8_USART_Num]->USART_CR1 |= (USART_SET <<USART_CR1_ENABLE_DISABLE);
	return Local_u8ErrorState;
}

uint8_t USART_u8_DisableTransfer(uint8_t Copy_u8_USART_Num)
{
	uint8_t Local_u8ErrorState = OK;
	USART_Num[Copy_u8_USART_Num]->USART_CR1 &= (~(USART_SET <<USART_CR1_ENABLE_DISABLE));
	return Local_u8ErrorState;
}

uint8_t USART_u8_TransferData (uint8_t Copy_u8_USART_Num, uint16_t Copy_u16Data)
{
	uint8_t Local_u8ErrorState = OK;
	/*Check Transfer Data empty*/
	while (!((USART_Num[Copy_u8_USART_Num] -> USART_SR)>> USART_SR_TXE_BIT));
	/*Transmit data*/
	(USART_Num[Copy_u8_USART_Num] -> USART_DR ) = Copy_u16Data;
	/*Check if transfer complete*/
	while (!((USART_Num[Copy_u8_USART_Num] -> USART_SR)>> USART_SR_TC_BIT));
	return Local_u8ErrorState;
}

uint8_t USART_u8_RecieveData (uint8_t Copy_u8_USART_Num, uint16_t *Copy_Pu16Data)
{
	uint8_t Local_u8ErrorState = OK;
	if (Copy_Pu16Data != NULL)
	{
		/*Check read data register is empty*/
		while (!((USART_Num[Copy_u8_USART_Num] -> USART_SR)>> USART_SR_RXNE_BIT));
		/*Read Data*/
		*Copy_Pu16Data = (USART_Num[Copy_u8_USART_Num] -> USART_DR );
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t USART_u8_SetCallBack (uint8_t Copy_u8_USART_Num,USART_Interrupt_Flag_t USART_Interrupt_Flag,void(*Copy_pf)(void))
{
	uint8_t Local_u8ErrorState = OK;
	if((Copy_u8_USART_Num <=USART_TOTAL_NUM)&&(USART_Interrupt_Flag<=USART_TOTAL_INTERRUPT_NUM)&& (Copy_pf!=NULL))
	{
		// Update global pointer to function.
		USART_Apf[Copy_u8_USART_Num][USART_Interrupt_Flag] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t USART_u8ReceiveIT(USART_Number_t USART_Number, void (*pv_CallBackFunc)(void))
{
	uint8_t Local_u8ErrorState = OK;
	if ( pv_CallBackFunc != NULL )
	{
		/* Setting CallBack Function */
		USART_Apf[USART_Number][USART_INTERRUPT_RXNE_Flage] = pv_CallBackFunc;
		/* Enabling Read Data Register Not Empty Interrupt */
		USART_Num[USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_RXNEIE_BIT);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t USART_u8RecieveBuffer(USART_Number_t USART_Number, uint16_t *Copy_pu16Buffer, uint16_t Copy_u8BufferSize)
{
	uint8_t Local_u8ErrorState = OK;
	if ((Copy_pu16Buffer !=  NULL))
	{
		/* Local Variable to hold the counter */
		uint16_t Local_u8Counter = 0;
		/* Looping on the buffer */
		for (Local_u8Counter = 0; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++)
		{
			/* Receiving Data */
			USART_u8_RecieveData (USART_Number,&Copy_pu16Buffer[Local_u8Counter]);
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t USART_u8TransmitBuffer(USART_Number_t USART_Number, uint16_t *Copy_pu16Buffer, uint16_t Copy_u8BufferSize)
{
	uint8_t Local_u8ErrorState = OK;
	if (Copy_pu16Buffer != NULL)
	{
		/* Local Variable to hold the counter */
		uint16_t Local_u8Counter = 0;

		/* Looping on the buffer */
		for (Local_u8Counter = 0; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++)
		{
			/* Transmitting Data */
			USART_u8_TransferData(USART_Number, Copy_pu16Buffer[Local_u8Counter]);
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t USART_u8ReceiveBuffer(USART_Number_t USART_Number, uint8_t *Copy_pu8ReceivedData, uint8_t Copy_u8Size)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8Counter = 0;

	if (NULL != Copy_pu8ReceivedData)
	{
		for (Local_u8Counter = 0; Local_u8Counter < Copy_u8Size; Local_u8Counter++)
		{
			USART_u8_RecieveData(USART_Number, (uint16_t *)&Copy_pu8ReceivedData[Local_u8Counter]);
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


void USART_VoidEnableDMATransmit(USART_Number_t USART_Number)
{
	/* Enabling DMA for Transmit */
	USART_Num[USART_Number]->USART_CR3 &= (~(USART_SET << USART_CR3_DMA_T_BIT));
	USART_Num[USART_Number]->USART_CR3 |= (USART_SET << USART_CR3_DMA_T_BIT);
}

void USART_VoidEnableDMAReieve(USART_Number_t USART_Number)
{
	/* Enabling DMA for Transmit */
	USART_Num[USART_Number]->USART_CR3 &= (~(USART_SET << USART_CR3_DMA_R_BIT));
	USART_Num[USART_Number]->USART_CR3 |= (USART_SET << USART_CR3_DMA_R_BIT);
}

uint8_t USART_u8RecieveBufferIT(USART_Number_t USART_Number, uint8_t *Copy_pu8Buffer, uint8_t Copy_u8BufferSize, void (*pv_CallBackFunc)(void))
{
	uint8_t Local_u8ErrorState = OK;
	if ((Copy_pu8Buffer != NULL )|| (pv_CallBackFunc != NULL))
	{
		/* Setting IRQ Source */
		USART_RecieveBufferFlag[USART_Number] = 1;
		/* Setting Buffer to Size Global */
		USART_RecieveBufferSize[USART_Number] = Copy_u8BufferSize;
		/* Setting Buffer to Receive globally */
		USART_RecievedBuffer[USART_Number] = Copy_pu8Buffer;
		/* Setting CallBack Function */
		USART_Apf[USART_Number][USART_INTERRUPT_RXNE_Flage] = pv_CallBackFunc;
		/* Setting the Buffer */
		USART_RecievedBuffer[USART_Number] = Copy_pu8Buffer;
		/* Enabling Read Data Register Not Empty Interrupt */
		USART_Num[USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_RXNEIE_BIT);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t USART_u8TransmitBufferIT(USART_Number_t USART_Number, uint8_t *Copy_pu8Buffer, uint8_t Copy_u8BufferSize, void (*pv_CallBackFunc)(void))
{
	uint8_t Local_u8ErrorState = OK;
	if ((Copy_pu8Buffer != NULL )|| (pv_CallBackFunc != NULL))
	{
		/* Setting IRQ Source */
		USART_TransmitBufferFlag[USART_Number] = 1;
		/* Setting Buffer to Send Global */
		USART_TransmitBuffer[USART_Number]		=	Copy_pu8Buffer;
		/* Setting Buffer Size Global */
		USART_TransmitBufferSize[USART_Number]	=	Copy_u8BufferSize;
		/* Setting CallBack Function */
		USART_Apf[USART_Number][USART_INTERRUPT_TXE_Flage] = pv_CallBackFunc;
		/* Setting the Buffer */
		USART_TransmitBuffer[USART_Number] = Copy_pu8Buffer;
		/* Enabling Read Data Register Not Empty Interrupt */
		USART_Num[USART_Number]->USART_CR1 |= (USART_SET << USART_CR1_TXEIE_BIT);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/*Interrupt Handle*/
/* USART1 ISR */
void USART1_IRQHandler(void)
{
	/* Coming from USART_ReciveBufferIT*/
	uint8_t Local_u8FlagStatus = 0;
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && (USART_RecieveBufferFlag[USART_1] == USART_SET))
	{
		static uint8_t FlagCounter = 1;

		/* Reading Data */
		USART_RecievedBuffer[USART_1][FlagCounter] = USART_Num[USART_1]->USART_DR;
		FlagCounter++;

		if (FlagCounter == USART_RecieveBufferSize[USART_1])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_RecieveBufferFlag[USART_1] = 0;

			USART_Num[USART_1]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_1][USART_CR1_RXNEIE_BIT]();
		}
	}

	USART_ReadFlag (USART_1,USART_INTERRUPT_TXE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && (USART_RecieveBufferFlag[USART_1] == USART_SET))
	{
		static uint8_t FlagCounter = 1;
		/*Transmit data*/
		USART_Num[USART_1]->USART_DR = USART_RecievedBuffer[USART_1][FlagCounter];
		FlagCounter++;
		if (FlagCounter == USART_TransmitBufferSize[USART_1])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_TransmitBufferFlag[USART_1] = 0;

			USART_Num[USART_1]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_1][USART_CR1_TXEIE_BIT]();
		}
	}

	/* Coming From USART_RecieBuffer*/
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		*USART_RecievedBuffer[USART_1] = USART_Num[USART_1]->USART_DR;

		USART_Num[USART_1]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_1][USART_CR1_RXNEIE_BIT]();
	}
	/* Transmission Complete */
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TC Flag */
		USART_Num[USART_1]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TC_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_1][USART_INTERRUPT_TC_Flage]();
	}
	/* Transmit Data Register Empty */
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TXE Flag */
		USART_Num[USART_1]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_1][USART_INTERRUPT_TXE_Flage]();
	}

	/* Overrun Error */
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the ORE Flag */
		USART_Num[USART_1]->USART_SR &= ~(USART_SET << USART_INTERRUPT_ORE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_1][USART_INTERRUPT_ORE_Flage]();
	}

	/* Framing Error */
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the FE Flag */
		USART_Num[USART_1]->USART_SR &= ~(USART_SET << USART_INTERRUPT_FE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_1][USART_INTERRUPT_FE_Flage]();
	}
	/* Noise Error */
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the NE Flag */
		USART_Num[USART_1]->USART_SR &= ~(USART_SET << USART_INTERRUPT_NF_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_1][USART_INTERRUPT_NF_Flage]();
	}

	/* Parity Error */
	USART_ReadFlag (USART_1,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the PE Flag */
		USART_Num[USART_1]->USART_SR &= ~(USART_SET << USART_INTERRUPT_PE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_1][USART_INTERRUPT_PE_Flage]();
	}
}
/* USART2 ISR */
void USART2_IRQHandler(void)
{
	/* Coming from USART_ReciveBufferIT*/
	uint8_t Local_u8FlagStatus = 0;
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && USART_RecieveBufferFlag[USART_2] == USART_SET)
	{
		static uint8_t FlagCounter = 1;

		/* Reading Data */
		USART_RecievedBuffer[USART_2][FlagCounter] = USART_Num[USART_2]->USART_DR;
		FlagCounter++;

		if (FlagCounter == USART_RecieveBufferSize[USART_2])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_RecieveBufferFlag[USART_2] = 0;

			USART_Num[USART_2]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_2][USART_CR1_RXNEIE_BIT]();
		}
	}

	USART_ReadFlag (USART_2,USART_INTERRUPT_TXE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && (USART_RecieveBufferFlag[USART_2] == USART_SET))
	{
		static uint8_t FlagCounter = 1;
		/*Transmit data*/
		USART_Num[USART_2]->USART_DR = USART_RecievedBuffer[USART_2][FlagCounter];
		FlagCounter++;
		if (FlagCounter == USART_TransmitBufferSize[USART_2])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_TransmitBufferFlag[USART_2] = 0;

			USART_Num[USART_2]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_2][USART_CR1_TXEIE_BIT]();
		}
	}

	/* Coming From USART_RecieBuffer*/
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		*USART_RecievedBuffer[USART_2] = USART_Num[USART_2]->USART_DR;

		USART_Num[USART_2]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_2][USART_CR1_RXNEIE_BIT]();
	}
	/* Transmission Complete */
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TC Flag */
		USART_Num[USART_2]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TC_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_2][USART_INTERRUPT_TC_Flage]();
	}
	/* Transmit Data Register Empty */
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TXE Flag */
		USART_Num[USART_2]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_2][USART_INTERRUPT_TXE_Flage]();
	}

	/* Overrun Error */
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the ORE Flag */
		USART_Num[USART_2]->USART_SR &= ~(USART_SET << USART_INTERRUPT_ORE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_2][USART_INTERRUPT_ORE_Flage]();
	}

	/* Framing Error */
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the FE Flag */
		USART_Num[USART_2]->USART_SR &= ~(USART_SET << USART_INTERRUPT_FE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_2][USART_INTERRUPT_FE_Flage]();
	}
	/* Noise Error */
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the NE Flag */
		USART_Num[USART_2]->USART_SR &= ~(USART_SET << USART_INTERRUPT_NF_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_2][USART_INTERRUPT_NF_Flage]();
	}

	/* Parity Error */
	USART_ReadFlag (USART_2,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the PE Flag */
		USART_Num[USART_2]->USART_SR &= ~(USART_SET << USART_INTERRUPT_PE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_2][USART_INTERRUPT_PE_Flage]();
	}
}
/* USART3 ISR */
void USART3_IRQHandler(void)
{
	/* Coming from USART_ReciveBufferIT*/
	uint8_t Local_u8FlagStatus = 0;
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && USART_RecieveBufferFlag[USART_3] == USART_SET)
	{
		static uint8_t FlagCounter = 1;

		/* Reading Data */
		USART_RecievedBuffer[USART_3][FlagCounter] = USART_Num[USART_3]->USART_DR;
		FlagCounter++;

		if (FlagCounter == USART_RecieveBufferSize[USART_3])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_RecieveBufferFlag[USART_3] = 0;

			USART_Num[USART_3]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_3][USART_CR1_RXNEIE_BIT]();
		}
	}

	USART_ReadFlag (USART_3,USART_INTERRUPT_TXE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && (USART_RecieveBufferFlag[USART_3] == USART_SET))
	{
		static uint8_t FlagCounter = 1;
		/*Transmit data*/
		USART_Num[USART_3]->USART_DR = USART_RecievedBuffer[USART_3][FlagCounter];
		FlagCounter++;
		if (FlagCounter == USART_TransmitBufferSize[USART_3])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_TransmitBufferFlag[USART_3] = 0;

			USART_Num[USART_3]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_3][USART_CR1_TXEIE_BIT]();
		}
	}


	/* Coming From USART_RecieBuffer*/
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		*USART_RecievedBuffer[USART_3] = USART_Num[USART_3]->USART_DR;

		USART_Num[USART_3]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_3][USART_CR1_RXNEIE_BIT]();
	}
	/* Transmission Complete */
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TC Flag */
		USART_Num[USART_3]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TC_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_3][USART_INTERRUPT_TC_Flage]();
	}
	/* Transmit Data Register Empty */
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TXE Flag */
		USART_Num[USART_3]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_3][USART_INTERRUPT_TXE_Flage]();
	}

	/* Overrun Error */
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the ORE Flag */
		USART_Num[USART_3]->USART_SR &= ~(USART_SET << USART_INTERRUPT_ORE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_3][USART_INTERRUPT_ORE_Flage]();
	}

	/* Framing Error */
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the FE Flag */
		USART_Num[USART_3]->USART_SR &= ~(USART_SET << USART_INTERRUPT_FE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_3][USART_INTERRUPT_FE_Flage]();
	}
	/* Noise Error */
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the NE Flag */
		USART_Num[USART_3]->USART_SR &= ~(USART_SET << USART_INTERRUPT_NF_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_3][USART_INTERRUPT_NF_Flage]();
	}

	/* Parity Error */
	USART_ReadFlag (USART_3,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the PE Flag */
		USART_Num[USART_3]->USART_SR &= ~(USART_SET << USART_INTERRUPT_PE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_3][USART_INTERRUPT_PE_Flage]();
	}
}
/* USART4 ISR */
void USART4_IRQHandler(void)
{
	/* Coming from USART_ReciveBufferIT*/
	uint8_t Local_u8FlagStatus = 0;
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && USART_RecieveBufferFlag[USART_4] == USART_SET)
	{
		static uint8_t FlagCounter = 1;

		/* Reading Data */
		USART_RecievedBuffer[USART_4][FlagCounter] = USART_Num[USART_4]->USART_DR;
		FlagCounter++;

		if (FlagCounter == USART_RecieveBufferSize[USART_4])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_RecieveBufferFlag[USART_4] = 0;

			USART_Num[USART_4]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_4][USART_CR1_RXNEIE_BIT]();
		}
	}

	USART_ReadFlag (USART_4,USART_INTERRUPT_TXE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && (USART_RecieveBufferFlag[USART_4] == USART_SET))
	{
		static uint8_t FlagCounter = 1;
		/*Transmit data*/
		USART_Num[USART_4]->USART_DR = USART_RecievedBuffer[USART_4][FlagCounter];
		FlagCounter++;
		if (FlagCounter == USART_TransmitBufferSize[USART_4])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_TransmitBufferFlag[USART_4] = 0;

			USART_Num[USART_4]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_4][USART_CR1_TXEIE_BIT]();
		}
	}


	/* Coming From USART_RecieBuffer*/
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		*USART_RecievedBuffer[USART_4] = USART_Num[USART_4]->USART_DR;

		USART_Num[USART_4]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_4][USART_CR1_RXNEIE_BIT]();
	}
	/* Transmission Complete */
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TC Flag */
		USART_Num[USART_4]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TC_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_4][USART_INTERRUPT_TC_Flage]();
	}
	/* Transmit Data Register Empty */
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TXE Flag */
		USART_Num[USART_4]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_4][USART_INTERRUPT_TXE_Flage]();
	}

	/* Overrun Error */
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the ORE Flag */
		USART_Num[USART_4]->USART_SR &= ~(USART_SET << USART_INTERRUPT_ORE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_4][USART_INTERRUPT_ORE_Flage]();
	}

	/* Framing Error */
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the FE Flag */
		USART_Num[USART_4]->USART_SR &= ~(USART_SET << USART_INTERRUPT_FE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_4][USART_INTERRUPT_FE_Flage]();
	}
	/* Noise Error */
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the NE Flag */
		USART_Num[USART_4]->USART_SR &= ~(USART_SET << USART_INTERRUPT_NF_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_4][USART_INTERRUPT_NF_Flage]();
	}

	/* Parity Error */
	USART_ReadFlag (USART_4,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the PE Flag */
		USART_Num[USART_4]->USART_SR &= ~(USART_SET << USART_INTERRUPT_PE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_4][USART_INTERRUPT_PE_Flage]();
	}
}
/* USART5 ISR */
void USART5_IRQHandler(void)
{
	/* Coming from USART_ReciveBufferIT*/
	uint8_t Local_u8FlagStatus = 0;
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && USART_RecieveBufferFlag[USART_5] == USART_SET)
	{
		static uint8_t FlagCounter = 1;

		/* Reading Data */
		USART_RecievedBuffer[USART_5][FlagCounter] = USART_Num[USART_5]->USART_DR;
		FlagCounter++;

		if (FlagCounter == USART_RecieveBufferSize[USART_5])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_RecieveBufferFlag[USART_5] = 0;

			USART_Num[USART_5]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_5][USART_CR1_RXNEIE_BIT]();
		}
	}

	USART_ReadFlag (USART_5,USART_INTERRUPT_TXE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && (USART_RecieveBufferFlag[USART_5] == USART_SET))
	{
		static uint8_t FlagCounter = 1;
		/*Transmit data*/
		USART_Num[USART_5]->USART_DR = USART_RecievedBuffer[USART_5][FlagCounter];
		FlagCounter++;
		if (FlagCounter == USART_TransmitBufferSize[USART_5])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_TransmitBufferFlag[USART_5] = 0;

			USART_Num[USART_5]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_5][USART_CR1_TXEIE_BIT]();
		}
	}


	/* Coming From USART_RecieBuffer*/
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		*USART_RecievedBuffer[USART_5] = USART_Num[USART_5]->USART_DR;

		USART_Num[USART_5]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_5][USART_CR1_RXNEIE_BIT]();
	}
	/* Transmission Complete */
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TC Flag */
		USART_Num[USART_5]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TC_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_5][USART_INTERRUPT_TC_Flage]();
	}
	/* Transmit Data Register Empty */
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TXE Flag */
		USART_Num[USART_5]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_5][USART_INTERRUPT_TXE_Flage]();
	}

	/* Overrun Error */
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the ORE Flag */
		USART_Num[USART_5]->USART_SR &= ~(USART_SET << USART_INTERRUPT_ORE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_5][USART_INTERRUPT_ORE_Flage]();
	}

	/* Framing Error */
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the FE Flag */
		USART_Num[USART_5]->USART_SR &= ~(USART_SET << USART_INTERRUPT_FE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_5][USART_INTERRUPT_FE_Flage]();
	}
	/* Noise Error */
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the NE Flag */
		USART_Num[USART_5]->USART_SR &= ~(USART_SET << USART_INTERRUPT_NF_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_5][USART_INTERRUPT_NF_Flage]();
	}

	/* Parity Error */
	USART_ReadFlag (USART_5,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the PE Flag */
		USART_Num[USART_5]->USART_SR &= ~(USART_SET << USART_INTERRUPT_PE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_5][USART_INTERRUPT_PE_Flage]();
	}
}
/* USART6 ISR */
void USART6_IRQHandler(void)
{
	/* Coming from USART_ReciveBufferIT*/
	uint8_t Local_u8FlagStatus = 0;
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && USART_RecieveBufferFlag[USART_6] == USART_SET)
	{
		static uint8_t FlagCounter = 1;

		/* Reading Data */
		USART_RecievedBuffer[USART_6][FlagCounter] = USART_Num[USART_6]->USART_DR;
		FlagCounter++;

		if (FlagCounter == USART_RecieveBufferSize[USART_6])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_RecieveBufferFlag[USART_6] = 0;

			USART_Num[USART_6]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_6][USART_CR1_RXNEIE_BIT]();
		}
	}

	USART_ReadFlag (USART_6,USART_INTERRUPT_TXE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus && (USART_RecieveBufferFlag[USART_6] == USART_SET))
	{
		static uint8_t FlagCounter = 1;
		/*Transmit data*/
		USART_Num[USART_6]->USART_DR = USART_RecievedBuffer[USART_6][FlagCounter];
		FlagCounter++;
		if (FlagCounter == USART_TransmitBufferSize[USART_6])
		{
			/* Disabling Read Data Register Not Empty Interrupt */
			USART_TransmitBufferFlag[USART_6] = 0;

			USART_Num[USART_6]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

			/* Calling the CallBack Function */
			USART_Apf[USART_6][USART_CR1_TXEIE_BIT]();
		}
	}


	/* Coming From USART_RecieBuffer*/
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		*USART_RecievedBuffer[USART_6] = USART_Num[USART_6]->USART_DR;

		USART_Num[USART_6]->USART_CR1 &= ~(USART_SET << USART_INTERRUPT_RXNE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_6][USART_CR1_RXNEIE_BIT]();
	}
	/* Transmission Complete */
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TC Flag */
		USART_Num[USART_6]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TC_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_6][USART_INTERRUPT_TC_Flage]();
	}
	/* Transmit Data Register Empty */
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the TXE Flag */
		USART_Num[USART_6]->USART_SR &= ~(USART_SET << USART_INTERRUPT_TXE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_6][USART_INTERRUPT_TXE_Flage]();
	}

	/* Overrun Error */
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the ORE Flag */
		USART_Num[USART_6]->USART_SR &= ~(USART_SET << USART_INTERRUPT_ORE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_6][USART_INTERRUPT_ORE_Flage]();
	}

	/* Framing Error */
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the FE Flag */
		USART_Num[USART_6]->USART_SR &= ~(USART_SET << USART_INTERRUPT_FE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_6][USART_INTERRUPT_FE_Flage]();
	}
	/* Noise Error */
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the NE Flag */
		USART_Num[USART_6]->USART_SR &= ~(USART_SET << USART_INTERRUPT_NF_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_6][USART_INTERRUPT_NF_Flage]();
	}

	/* Parity Error */
	USART_ReadFlag (USART_6,USART_INTERRUPT_RXNE_Flage, &Local_u8FlagStatus);
	if (Local_u8FlagStatus)
	{
		/* Clearing the PE Flag */
		USART_Num[USART_6]->USART_SR &= ~(USART_SET << USART_INTERRUPT_PE_Flage);

		/* Calling the CallBack Function */
		USART_Apf[USART_6][USART_INTERRUPT_PE_Flage]();
	}
}
