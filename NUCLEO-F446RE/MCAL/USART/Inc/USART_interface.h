
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/*enum for USART Number*/
typedef enum
{
	USART_1=0,
	USART_2,
	USART_3,
	USART_4,
	USART_5,
	USART_6,
}USART_Number_t;

/*Interrupt action*/
typedef enum
{
	USART_DIASBLE=0,
	USART_ENABLE
}USART_InitialState_t;

/*enum for the mode*/
typedef enum
{
	USART_TRANSMITTER_DISABLE=0,
	USART_TRANSMITTER_ENABLE,
}USART_Tx_Mode_t;
typedef enum
{
	USART_RECEIVER_DISABLE = 0,
	USART_RECEIVER_ENABLE
}USART_Rx_Mode_t;
/*Enum for stop bit*/
typedef enum
{
	USART_STOP_BIT_1=0,
	USART_STOP_BIT_HALF,
	USART_STOP_BIT_2,
	USART_STOP_BIT_1_AND_HALF
}USART_Stop_Bit_t;

/*USART Parity Control*/
typedef enum
{
	USART_PARITY_CONTROL_DISABLE=0,
	USART_PARITY_CONTROL_ENABLE,
}USART_ParityControl_t;

/*USART Parity Selection*/
typedef enum
{
	USART_PARITY_EVEN=0,
	USART_PARITY_ODD,
}USART_ParitySelection_t;

/*USART Over Sampling*/
typedef enum
{
	USART_OVER_SAMPLING_BY_16=0,
	USART_OVER_SAMPLING_BY_8,
}USART_OverSampling_t;

/*USART Word Length*/
typedef enum
{
	USART_WORD_LENGTH_8=0,
	USART_WORD_LENGTH_9,
}USART_WordLength_t;

/*USART Wake up method*/
typedef enum
{
	USART_IDLE_LINE=0,
	USART_ADDRESS_MARK,
}USART_WakeUpMethod_t;

/*Sample Method*/
typedef enum
{
	USART_THREE_SAMPLE_BIT_METHOD = 0,
	USART_ONE_SAMPLE_BIT_METHOD
}USART_Sample_Method_t;

/*enum for the mode of hardware flow control.*/
typedef enum
{
	USART_HW_FLOW_CTRL_CTSE_DISABLE = 0,
	USART_HW_FLOW_CTRL_CTSE_ENABLE
}USART_CTSE_Mode_t;
typedef enum
{
	USART_HW_FLOW_CTRL_RTSE_DISABLE = 0,
	USART_HW_FLOW_CTRL_RTSE_ENABLE
}USART_RTSE_Mode_t;

/*DMA Transfer*/
typedef enum
{
	USART_DMA_TRANSMIT_DISABLE = 0,
	USART_DMA_TRANSMIT_ENABLE
}USART_DMA_Transmit_t;

typedef enum
{
	USART_DMA_RECIEVE_DISABLE = 0,
	USART_DMA_RECIEVE_ENABLE
}USART_DMA_Recieve_t;
/*Interrupt action*/
typedef enum
{
	USART_INTERRUPT_DIASBLE=0,
	USART_INTERRUPT_ENABLE
}USART_Interrupt_t;

typedef enum
{
	USART_INTERRUPT_PE_Flage=0,		/* Parity Error Flag*/
	USART_INTERRUPT_FE_Flage,		/* Framing Error Flag*/
	USART_INTERRUPT_NF_Flage,		/* Noise Error Flag*/
	USART_INTERRUPT_ORE_Flage,		/* OverRun Error Flag*/
	USART_INTERRUPT_IDLE_Flage,		/* IDLE Line Detected Flag*/
	USART_INTERRUPT_RXNE_Flage,		/* Read Data Register Not Empty Flag*/
	USART_INTERRUPT_TC_Flage,		/* Transmission Complete Flag*/
	USART_INTERRUPT_TXE_Flage,		/* Transmit Data Register Empty Flag*/
	USART_INTERRUPT_LBD_Flage,		/* LIN Break Detection Flag*/
	USART_INTERRUPT_CTS_Flage,	/* CTS Flag*/
}USART_Interrupt_Flag_t;

typedef struct
{
	USART_Number_t		USART_Number;
	USART_Interrupt_t	USART_PE;
	USART_Interrupt_t	USART_TX;
	USART_Interrupt_t	USART_TC;
	USART_Interrupt_t	USART_RXN;
	USART_Interrupt_t	USART_IDLE;
}USART_Interrupts_t;

typedef enum
{
	USART_BaudRate_2400 	= 2400UL,		// Baud Rate 2400
	USART_BaudRate_4800 	= 4800UL,		// Baud Rate 4800
	USART_BaudRate_9600 	= 9600UL,		// Baud Rate 9600
	USART_BaudRate_14400 	= 14400UL,		// Baud Rate 14400
	USART_BaudRate_19200 	= 19200UL,		// Baud Rate 19200
	USART_BaudRate_28800 	= 28800UL,		// Baud Rate 28800
	USART_BaudRate_38400 	= 38400UL,		// Baud Rate 38400
	USART_BaudRate_57600 	= 57600UL,		// Baud Rate 57600
	USART_BaudRate_76800 	= 76800UL,		// Baud Rate 76800
	USART_BaudRate_115200 	= 115200UL, 	// Baud Rate 115200
	USART_BaudRate_230400 	= 230400UL, 	// Baud Rate 230400
	USART_BaudRate_250000 	= 250000UL, 	// Baud Rate 250000
}USART_BaudRate_t;

typedef struct
{
	USART_Number_t			USART_Number;
	USART_BaudRate_t 		USART_BaudRate;
	USART_OverSampling_t	USART_OverSampling;
}USART_BaudRate_Config_t;

typedef struct
{
	USART_Number_t			USART_Number;
	USART_BaudRate_t 		USART_BaudRate;
	USART_WordLength_t		USART_WordLength;
	USART_InitialState_t	USART_InitialState;
	USART_Stop_Bit_t		USART_Stop_Bit;
	USART_ParityControl_t	USART_ParityControl;
	USART_ParitySelection_t	USART_ParitySelection;
	USART_Tx_Mode_t			USART_Tx_Mode;
	USART_Rx_Mode_t			USART_Rx_Mode;
	USART_OverSampling_t	USART_OverSampling;
	USART_Interrupt_t		*USART_Interrupt;
	USART_WakeUpMethod_t	USART_WakeUpMethod;
	USART_Sample_Method_t	USART_Sample_Method;
	USART_CTSE_Mode_t		USART_CTSE_Mode;
	USART_RTSE_Mode_t		USART_RTSE_Mode;

}USART_Config_t;

void USART_SettingBaudRate(USART_BaudRate_Config_t *USART_BaudRate_Config);

void USART_voidInterruptConfig(USART_Interrupts_t *USART_Interrupts);

uint8_t USART_ReadFlag(USART_Number_t USART_Number, USART_Interrupt_Flag_t USART_Interrupt_Flag, uint8_t *Copy_pu8_FlagStatus);

uint8_t USART_u8Init(const USART_Config_t* USART_Config ,const USART_Interrupts_t *USART_Interrupts);

uint8_t USART_u8_EnableTransfer(uint8_t Copy_u8_USART_Num);

uint8_t USART_u8_DisableTransfer(uint8_t Copy_u8_USART_Num);

uint8_t USART_u8_TransferData (uint8_t Copy_u8_USART_Num, uint16_t Copy_u16Data);

uint8_t USART_u8_RecieveData (uint8_t Copy_u8_USART_Num, uint16_t *Copy_Pu16Data);

uint8_t USART_u8_SetCallBack (uint8_t Copy_u8_USART_Num,USART_Interrupt_Flag_t USART_Interrupt_Flag,void(*Copy_pf)(void));

uint8_t USART_u8ReceiveIT(USART_Number_t USART_Number, void (*pv_CallBackFunc)(void));

uint8_t USART_u8ReceiveBuffer(USART_Number_t USART_Number, uint8_t *Copy_pu8ReceivedData, uint8_t Copy_u8Size);

uint8_t USART_u8TransmitBuffer(USART_Number_t USART_Number, uint16_t *Copy_pu16Buffer, uint16_t Copy_u8BufferSize);

void USART_VoidEnableDMATransmit(USART_Number_t USART_Number);

void USART_VoidEnableDMAReieve(USART_Number_t USART_Number);

uint8_t USART_SendBuffer(USART_Number_t USART_Number, uint8_t *Copy_pu8Data, uint8_t Copy_u8Size);

uint8_t USART_u8TransmitBufferIT(USART_Number_t USART_Number, uint8_t *Copy_pu8Buffer, uint8_t Copy_u8BufferSize, void (*pv_CallBackFunc)(void));

uint8_t USART_u8RecieveBufferIT(USART_Number_t USART_Number, uint8_t *Copy_pu8Buffer, uint8_t Copy_u8BufferSize, void (*pv_CallBackFunc)(void));

#endif /* USART_INTERFACE_H_ */
