
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
	USART_INTERRUPT_CTS=0,
	USART_INTERRUPT_LBD,
	USART_INTERRUPT_TXE,
	USART_INTERRUPT_TC,
	USART_INTERRUPT_RXNE,
	USART_INTERRUPT_IDLE,
	USART_INTERRUPT_ORE,
	USART_INTERRUPT_NF,
	USART_INTERRUPT_FE,
	USART_INTERRUPT_PE
}USART_Interrupt_Name_t;
typedef struct
{
	USART_Number_t			USART_Number;
	USART_Tx_Mode_t			USART_Tx_Mode;
	USART_Rx_Mode_t			USART_Rx_Mode;
	USART_Stop_Bit_t		USART_Stop_Bit;
	USART_ParityControl_t	USART_ParityControl;
	USART_ParitySelection_t	USART_ParitySelection;
	USART_WordLength_t		USART_WordLength;
	USART_WakeUpMethod_t	USART_WakeUpMethod;
	USART_CTSE_Mode_t		USART_CTSE_Mode;
	USART_RTSE_Mode_t		USART_RTSE_Mode;
	USART_Interrupt_t		USART_Interrupt;
	USART_DMA_Transmit_t	USART_DMA_Transmit;
	USART_DMA_Recieve_t		USART_DMA_Recieve;
	uint32_t 				BaudRate;
}USART_Config_t;

uint8_t USART_u8Init(const USART_Config_t* USART_Config);

uint8_t USART_u8_EnableTransfer(uint8_t Copy_u8_USART_Num);

uint8_t USART_u8_DisableTransfer(uint8_t Copy_u8_USART_Num);

uint8_t USART_u8_TransferData (uint8_t Copy_u8_USART_Num, uint32_t Copy_Pu32Data);

uint8_t USART_u8_RecieveData (uint8_t Copy_u8_USART_Num, uint32_t *Copy_Pu32Data);

uint8_t USART_u8_SetCallBack (uint8_t Copy_u8_USART_Num,USART_Interrupt_Name_t USART_Interrupt_Name,void(*Copy_pf)(void));

#endif /* USART_INTERFACE_H_ */
