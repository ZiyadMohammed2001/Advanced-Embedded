/*
 * DMA_Interface.h
 *
 *  Created on: Aug 11, 2023
 *      Author: Ziyad
 */

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

typedef enum
{
	DMA_FEIF0_FLAG =0,
	DMA_DMEIF0_FLAG=2,
	DMA_TEIF0_FLAG,
	DMA_HTIF0_FLAG,
	DMA_TCIF0_FLAG,
	DMA_FEIF1_FLAG,
	DMA_DMEIF1_FLAG=8,
	DMA_TEIF1_FLAG,
	DMA_HTIF1_FLAG,
	DMA_TCIF1_FLAG,
	DMA_FEIF2_FLAG = 16,
	DMA_DMEIF2_FLAG = 18,
	DMA_TEIF2_FLAG,
	DMA_HTIF2_FLAG,
	DMA_TCIF2_FLAG,
	DMA_FEIF3_FLAG,
	DMA_DMEIF3_FLAG = 24,
	DMA_TEIF3_FLAG,
	DMA_HTIF3_FLAG,
	DMA_TCIF3_FLAG
}DMA_ISR_Flag_t;

typedef enum
{
	DMA_1=5,
	DMA_2,
}DMA_Num_t;

typedef enum
{
	STREAM_0=0,
	STREAM_1,
	STREAM_2,
	STREAM_3,
	STREAM_4,
	STREAM_5,
	STREAM_6,
	STREAM_7,
}DMA_Stream_Num_t;

typedef enum
{
	DMA_CHANNEL_0=0,
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7
}DMA_Select_Channel_t;

typedef enum
{
	DMA_DISABLE,
	DMA_Enable
}DMA_InitState_t;

typedef enum
{
	DMA_PERIPHERAL_TO_MEMORY=0,
	DMA_MEMORY_TO_PERIPHERAL,
	DMA_MEMORY_TO_MEMORY
}DMA_Direction_t;

typedef enum
{
	DMA_PERIPHERAL_INCREMENT_DISABLE=0,
	DMA_PERIPHERAL_INCREMENT_ENABLE
}DMA_Peripheral_Increment_t;

typedef enum
{
	DMA_MEMORY_NO_INCREMENT=0,
	DMA_MEMORY_INCREMENT
}DMA_Memory_Increment_t;

typedef enum
{
	DMA_PERIPHERAL_BYTE=0,
	DMA_PERIPHERAL_HALFWORD,
	DMA_PERIPHERAL_WORD
}DMA_Peripheral_Data_Size_t;

typedef enum
{
	DMA_MEMORY_BYTE=0,
	DMA_MEMORY_HALFWORD,
	DMA_MEMORY_WORD
}DMA_Memory_Data_Size_t;

typedef enum
{
	DMA_MODE_CIRCULAR_DISABLE=0,
	DMA_MODE_CIRCULAR_ENABLE,
}DMA_Mode_t;

typedef enum
{
	DMA_PRIORITY_LOW=0,
	DMA_PRIORITY_MEDIUM,
	DMA_PRIORITY_HIGH,
	DMA_PRIORITY_VERY_HIGH
}DMA_Priority_t;

typedef enum
{
	DMA_FIFO_MODE_DISABLE=0,
	DMA_FIFO_MODE_ENABLE
}DMA_FIFO_Mode_t;

typedef enum
{
	DMA_FIFO_THRESHOLD_1_QUARTER_FULL=0,
	DMA_FIFO_THRESHOLD_HALF_FULL,
	DMA_FIFO_THRESHOLD_3_QUARTERS_FULL,
	DMA_FIFO_THRESHOLD_FULL
}DMA_FIFO_Threshold_t;

typedef enum
{
	DMA_TRNSFER_COMPELETE_FLAG=0,
	DMA_HALF_TRNSFER_FLAG,
}DMA_Transfer_flag_t;


typedef enum
{
	DMA_MEMORY_BURST_TRANSFER_SINGLE_TRANSFER=0,
	DMA_MEMORY_BURST_TRANSFER_INCR4,
	DMA_MEMORY_BURST_TRANSFER_INCR8,
	DMA_MEMORY_BURST_TRANSFER_INCR16,
}DMA_Memory_Burst_t;

typedef enum
{
	DMA_PERIPHERAL_BURST_TRANSFER_SINGLE_TRANSFER=0,
	DMA_PERIPHERAL_BURST_TRANSFER_INCR4,
	DMA_PERIPHERAL_BURST_TRANSFER_INCR8,
	DMA_PERIPHERAL_BURST_TRANSFER_INCR16,
}DMA_Peripheral_Burst_t;

typedef enum
{
	DMA_INTERRUPT_ENABLE=0,
	DMA_INTERRUPT_DISABLE
}DMA_InterruptState;

typedef enum
{
    DMA_DOUBLE_BUFFER_DISABLE = 0,
    DMA_DOUBLE_BUFFER_ENABLE = 1
}DMA_Double_Buffer_t;

typedef struct
{
	DMA_Num_t 			DMA_Num;
	DMA_Stream_Num_t 	DMA_Stream_Num;
	DMA_InterruptState	DMA_TC;
	DMA_InterruptState 	DMA_HT;
	DMA_InterruptState 	DMA_TE;
	DMA_InterruptState 	DMA_DME;
	DMA_InterruptState	DMA_FIFO_ERROR;
}DMA_Interrupt_Config_t;

typedef enum
{
	DMA_TC = 0, 		/*Transfer Complete call back.*/
	DMA_HT,			/*Half Transfer Complete call back.*/
	DMA_TE,			/*Transfer Error Call Back.*/
	DMA_DME,		/*Direct Mode Call Back Error.*/
	DMA_FIFO_ERROR,	/*DMA FIFo ERROR call back.*/
}DMA_Interrupt_CallBack_t;

typedef enum
{
	DMA_LISR = 0,
	DMA_HISR,
}DMA_ISR_Config_t;

typedef struct
{
	DMA_Num_t			DMA_Num;
	DMA_Stream_Num_t	DMA_Stream_Num;
	DMA_ISR_Config_t	DMA_ISR_Config;
	DMA_ISR_Flag_t		DMA_ISR_Flag;
}DMA_Clear_Flag_t;

typedef struct
{
	DMA_Num_t			DMA_Num;
	DMA_Stream_Num_t	DMA_Stream_Num;
	DMA_ISR_Config_t	DMA_ISR_Config;
	DMA_ISR_Flag_t		DMA_ISR_Flag;
	uint8_t				*Copy_pu8FlagStatus;
}DMA_Read_Flag_t;

typedef struct
{
	DMA_Num_t 					DMA_Num;
	DMA_Stream_Num_t 			DMA_Stream_Num;
	DMA_Select_Channel_t 		DMA_Select_Channel;
	DMA_Direction_t 			DMA_Direction;
	DMA_Peripheral_Increment_t 	DMA_Peripheral_Increment;
	DMA_Memory_Increment_t 		DMA_Memory_Increment;
	DMA_Peripheral_Data_Size_t 	DMA_Peripheral_Data_Size;
	DMA_Memory_Data_Size_t 		DMA_Memory_Data_Size;
	DMA_Mode_t 					DMA_Mode;
	DMA_Double_Buffer_t			DMA_Double_Buffer;
	DMA_Priority_t 				DMA_Priority;
	DMA_FIFO_Mode_t 			DMA_FIFO_Mode;
	DMA_FIFO_Threshold_t 		DMA_FIFO_Threshold;
	DMA_Memory_Burst_t 			DMA_Memory_Burst_t;
	DMA_Peripheral_Burst_t 		DMA_Peripheral_Burst;
	DMA_InitState_t				DMA_InitState;
}DMA_Init_Config_t;

typedef struct
{
	DMA_Num_t 				DMA_Num;
	DMA_Stream_Num_t	 	DMA_Stream_Num;
	DMA_Direction_t 		DMA_Direction;
	uint32_t *				DMA_SrcAddress;
	uint32_t *				DMA_DestAddress;
	uint16_t 				DMA_DataLength;
}DMA_Start_Transfer_t;

uint8_t DMA_u8_clearInterruptFlag(DMA_Clear_Flag_t * DMA_Clear_Flag);

uint8_t DMA_u8_ReadInterruptFlag(DMA_Read_Flag_t * DMA_Read_Flag);

/********************************************************************
 * @fn DMA_u8Init.
 * @berief	the function set configuration of DMA.
 * @Parameters	[in]  DMA_Init_Config : Initialize values of the DMA.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t DMA_u8Init (const DMA_Init_Config_t *DMA_Init_Config, const DMA_Interrupt_Config_t *DMA_Interrupt_Config);

uint8_t DMA_InterruptConfig (const DMA_Interrupt_Config_t *DMA_Interrupt_Config);

uint8_t DMA_u8DisableStream (const DMA_Num_t DMA_Number ,const DMA_Stream_Num_t DMA_Stream_Num);

uint8_t DMA_StartTransfer (const DMA_Start_Transfer_t *DMA_Start_Transfer);

uint8_t DMA_SetCallBack(const DMA_Num_t DMA_Number ,const DMA_Stream_Num_t DMA_Stream_Num, const DMA_Interrupt_CallBack_t DMA_Interrupt_CallBack, void (*Copy_pvCallBack)(void));

#endif /* EXTI_INTERFACE_H_ */
