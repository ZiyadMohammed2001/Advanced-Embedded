/********************************************************************/
/* @file	DMA_program.c
 * @author	Ziyad Mohammed
 * @brief	The DMA Main Source File , Including function definitions.
 */
#include <stdint.h>
#include "Stm32f446.h"
#include "ErrType.h"

#include "DMA_interface.h"
#include "DMA_Config.h"
#include "DMA_private.h"

static DMA_RegDef_t * DMA_Num[DMA_PERIPHERAL_NUM] = {DMA1_REGISTER,DMA2_REGISTER};
static uint32_t DMA_Stream_Offset[DMA_STRAM_NUMs] = {DMA_Stream0_OFFSET,DMA_Stream1_OFFSET,DMA_Stream2_OFFSET,DMA_Stream3_OFFSET,DMA_Stream4_OFFSET,DMA_Stream5_OFFSET,DMA_Stream6_OFFSET,DMA_Stream7_OFFSET};

static void (*DMA1_STREAM_PTR_TOFUNC[DMA_PERIPHERAL_NUM][DMA_STREAM_MAX][DMA_INTERRUPT_NUM])(void) = {NULL};

uint8_t DMA_u8_clearInterruptFlag(DMA_Clear_Flag_t * DMA_Clear_Flag)
{
	uint8_t	Local_u8ErrorState = OK;
	if (DMA_Clear_Flag ->DMA_ISR_Config)
	{
		DMA_Num[DMA_Clear_Flag->DMA_Num] ->DMA_HIFCR |= (DMA_SET_BIT << (DMA_Clear_Flag -> DMA_ISR_Flag));
	}
	else if ((DMA_Clear_Flag ->DMA_ISR_Config) == 0)
	{
		DMA_Num[DMA_Clear_Flag->DMA_Num] ->DMA_LIFCR |= (DMA_SET_BIT << (DMA_Clear_Flag -> DMA_ISR_Flag));
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t DMA_u8_ReadInterruptFlag(DMA_Read_Flag_t * DMA_Read_Flag)
{
	uint8_t	Local_u8ErrorState = OK;
	if (DMA_Read_Flag ->DMA_ISR_Config)
	{
		*(DMA_Read_Flag ->Copy_pu8FlagStatus) = (DMA_SET_BIT & ((DMA_Num[DMA_Read_Flag->DMA_Num] ->DMA_HISR) >> (DMA_Read_Flag -> DMA_ISR_Flag) ));
	}
	else if ((DMA_Read_Flag ->DMA_ISR_Config) == 0)
	{
		*(DMA_Read_Flag ->Copy_pu8FlagStatus) = (DMA_SET_BIT & ((DMA_Num[DMA_Read_Flag->DMA_Num] ->DMA_LISR) >> (DMA_Read_Flag -> DMA_ISR_Flag) ));
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

/*********************************************************************
 * @fn DMA_u8Init.
 * @berief	the function set configuration of DMA.
 * @Parameters	[in]  DMA_Init_Config : Initialize values of the DMA.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t DMA_u8Init (const DMA_Init_Config_t *DMA_Init_Config, const DMA_Interrupt_Config_t *DMA_Interrupt_Config)
{
	uint8_t	Local_u8ErrorState = OK;

	/*Disable DMA*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR = (!(DMA_SET_BIT));
	/*Wait till Steam is disabled*/
	while (DMA_SET_BIT & (((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR));
	/*Select stream number + channel number*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_CHSEL_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Select_Channel)<<DMA_SxCR_CHSEL_BITS_SHIFT);

	/*Select direction.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_DIR_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Direction)<<DMA_SxCR_DIR_BITS_SHIFT);

	/*Select peripheral increment or not*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_PINC_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Peripheral_Increment)<<DMA_SxCR_PINC_BITS_SHIFT);

	/*Select Memory increment or not*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_MINC_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Memory_Increment)<<DMA_SxCR_MINC_BITS_SHIFT);

	/*Select Peripheral data Size.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_PSIZE_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Peripheral_Data_Size)<<DMA_SxCR_PSIZE_BITS_SHIFT);

	/*Select Memory data Size.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_MSIZE_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Memory_Data_Size)<<DMA_SxCR_MSIZE_BITS_SHIFT);

	/*Select Mode direct mode or FIFO mode.*/

	/*Select Priority*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_PL_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Priority)<<DMA_SxCR_PL_BITS_SHIFT);

	/*Select FIFO Mode Enabled or disabled.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxFCR &= DMA_SxFCR_DMDIS_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxFCR |= ((DMA_Init_Config->DMA_FIFO_Mode)<<DMA_SxFCR_DMDIS_BITS_SHIFT);

	/*Select FIFO Threshold.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxFCR &= DMA_SxFCR_FTH_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxFCR |= ((DMA_Init_Config->DMA_FIFO_Threshold)<<DMA_SxFCR_FTH_BITS_SHIFT);

	/*Select Memory Burst*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_MBURST_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Memory_Burst_t)<<DMA_SxCR_MBURST_BITS_SHIFT);

	/*Select Peripheral Burst*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_PBURST_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Peripheral_Burst)<<DMA_SxCR_PBURST_BITS_SHIFT);

	/*Set DMA Mode*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_CIRC_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Mode)<<DMA_SxCR_CIRC_BITS_SHIFT);

	/*Select double buffer mode*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_DBM_MASK;
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Init_Config->DMA_Double_Buffer)<<DMA_SxCR_DBM_BITS_SHIFT);

	/*Interrupt Configuration.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_INTERRUPT_MASK;
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_DME)<<DMA_SxCR_DMEIE_BITS_SHIFT);
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_TE)<<DMA_SxCR_TEIE_BITS_SHIFT);
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_HT)<<DMA_SxCR_HTIE_BITS_SHIFT);
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Init_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Init_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_TC)<<DMA_SxCR_TCIE_BITS_SHIFT);
	/*Configure FIFO error interrupt enable.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_TC)<<DMA_SxCR_TCIE_BITS_SHIFT);
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxFCR &= DMA_SxFCR_FEIE_INTERRUPT_MASK;
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxFCR |= ((DMA_Interrupt_Config->DMA_FIFO_ERROR)<<DMA_SxFCR_FEIE_INTERRUPT_BIT_SHIFT);

	return Local_u8ErrorState;
}

uint8_t DMA_InterruptConfig (const DMA_Interrupt_Config_t *DMA_Interrupt_Config)
{
	uint8_t	Local_u8ErrorState = OK;
	/*Interrupt Configuration.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxCR &= DMA_SxCR_INTERRUPT_MASK;
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_DME)<<DMA_SxCR_DMEIE_BITS_SHIFT);
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_TE)<<DMA_SxCR_TEIE_BITS_SHIFT);
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_HT)<<DMA_SxCR_HTIE_BITS_SHIFT);
	/*Configure FIFO error interrupt enable.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxCR |= ((DMA_Interrupt_Config->DMA_TC)<<DMA_SxCR_TCIE_BITS_SHIFT);
	/*Configure DME interrupt.*/
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxFCR &= DMA_SxFCR_FEIE_INTERRUPT_MASK;
	((DMA_Num[DMA_Interrupt_Config->DMA_Num]) + (DMA_Stream_Offset[DMA_Interrupt_Config->DMA_Stream_Num]))->DMA_SxFCR |= ((DMA_Interrupt_Config->DMA_FIFO_ERROR)<<DMA_SxFCR_FEIE_INTERRUPT_BIT_SHIFT);
	return Local_u8ErrorState;
}

uint8_t DMA_u8DisableStream (const DMA_Num_t DMA_Number ,const DMA_Stream_Num_t DMA_Stream_Num)
{
	uint8_t	Local_u8ErrorState = OK;
	if ((DMA_Number <= DMA_2) && (DMA_Stream_Num <=STREAM_7))
	{
		/*Disable DMA*/
		((DMA_Num[DMA_Number]) + (DMA_Stream_Offset[DMA_Stream_Num]))->DMA_SxCR = (!(DMA_SET_BIT));
		/*Wait till Steam is disabled*/
		while (DMA_SET_BIT & (((DMA_Num[DMA_Number]) + (DMA_Stream_Offset[DMA_Stream_Num]))->DMA_SxCR));
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8_t DMA_StartTransfer (const DMA_Start_Transfer_t *DMA_Start_Transfer)
{
	uint8_t	Local_u8ErrorState = OK;
	if (((DMA_Start_Transfer -> DMA_SrcAddress) != NULL)&&((DMA_Start_Transfer->DMA_DestAddress) != NULL))
	{
		/*Set Data length.*/
		((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxNDTR = (DMA_Start_Transfer -> DMA_DataLength);
		/*Set Destination & source address According to data transfer direction*/
		switch (DMA_Start_Transfer -> DMA_Direction)
		{
		case DMA_MEMORY_TO_MEMORY :
			/*Set source.*/
			((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxPAR = (uint32_t) (DMA_Start_Transfer->DMA_SrcAddress);
			/*Set Destination.*/
			((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxM0AR = (uint32_t) (DMA_Start_Transfer->DMA_DestAddress);
			break;
		case DMA_MEMORY_TO_PERIPHERAL :
			/*Set source.*/
			((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxPAR = (uint32_t) (DMA_Start_Transfer -> DMA_DestAddress);
			/*Set Destination.*/
			((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxM0AR = (uint32_t) (DMA_Start_Transfer -> DMA_SrcAddress);
			break;
		case DMA_PERIPHERAL_TO_MEMORY :
			/*Set source.*/
			((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxPAR = (uint32_t) (DMA_Start_Transfer -> DMA_SrcAddress);
			/*Set Destination.*/
			((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxM0AR = (uint32_t) (DMA_Start_Transfer -> DMA_DestAddress);
			break;
		default: 		Local_u8ErrorState = NOK;		break;
		}
		/*Enable Stream*/
		((DMA_Num[DMA_Start_Transfer->DMA_Num]) + (DMA_Stream_Offset[DMA_Start_Transfer->DMA_Stream_Num]))->DMA_SxCR = DMA_SET_BIT;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t DMA_SetCallBack(const DMA_Num_t DMA_Number ,const DMA_Stream_Num_t DMA_Stream_Num, const DMA_Interrupt_CallBack_t DMA_Interrupt_CallBack, void (*Copy_pvCallBack)(void))
{
	uint8_t	Local_u8ErrorState = OK;
	if ((DMA_Number <= DMA_2) && (DMA_Stream_Num <=STREAM_7)&&(DMA_Interrupt_CallBack <= DMA_FIFO_ERROR)&&(Copy_pvCallBack != NULL))
	{
		DMA1_STREAM_PTR_TOFUNC [DMA_Number] [DMA_Stream_Num] [DMA_Interrupt_CallBack] = Copy_pvCallBack;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void DMA1_Stream0_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_0;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_0;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_0] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_0;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_0;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_0] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_0;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_0;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_0] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_0;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_0;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_0] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_0;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_0;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_0] [DMA_TCIF0_FLAG]();
	}
}
void DMA1_Stream1_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_1;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_1;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_1] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_1;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_1;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_1] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_1;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_1;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_1] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_1;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_1;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_1] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_1;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_1;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_1] [DMA_TCIF0_FLAG]();
	}
}
void DMA1_Stream2_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_2;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_2;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_2] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_2;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_2;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_2] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_2;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_2;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_2] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_2;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_2;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_2] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_2;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_2;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_2] [DMA_TCIF0_FLAG]();
	}
}
void DMA1_Stream3_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_3;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_3;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_3] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_3;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_3;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_3] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_3;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_3;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_3] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_3;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_3;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_3] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_3;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_3;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_3] [DMA_TCIF0_FLAG]();
	}
}
void DMA1_Stream4_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_4;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_4;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_4] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_4;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_4;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_4] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_4;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_4;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_4] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_4;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_4;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_4] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_4;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_4;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_4] [DMA_TCIF0_FLAG]();
	}
}
void DMA1_Stream5_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_5;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_5;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_5] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_5;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_5;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_5] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_5;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_5;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_5] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_5;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_5;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_5] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_5;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_5;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_5] [DMA_TCIF0_FLAG]();
	}
}
void DMA1_Stream6_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_6;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_6;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_6] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_6;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_6;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_6] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_6;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_6;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_6] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_6;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_6;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_6] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_6;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_6;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_6] [DMA_TCIF0_FLAG]();
	}
}
void DMA1_Stream7_IRQHandler(void)
{
	uint8_t	Local_u8FlagStatus=0;
	DMA_Read_Flag_t ISR_Flag;
	DMA_Clear_Flag_t Clear_ISRFlag;
	/*For FIFO error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_7;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_FEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_7;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_FIFO_ERROR;
		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_7] [DMA_FIFO_ERROR]();
	}
	/*For Direct Mode interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_7;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_7;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_DMEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_7] [DMA_DMEIF0_FLAG]();
	}
	/*For Transfer error interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_7;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TEIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_7;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TEIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_7] [DMA_TEIF0_FLAG]();
	}
	/*For Half Transfer interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_7;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_HTIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_7;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_HTIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_7] [DMA_HTIF0_FLAG]();
	}
	/*For Transfer Complete interrupt flag.*/
	ISR_Flag.DMA_Num =DMA_1,
	ISR_Flag.DMA_Stream_Num = STREAM_7;
	ISR_Flag.DMA_ISR_Config = DMA_LISR;
	ISR_Flag.DMA_ISR_Flag = DMA_TCIF0_FLAG;
	ISR_Flag.Copy_pu8FlagStatus = &Local_u8FlagStatus;

	DMA_u8_ReadInterruptFlag (&ISR_Flag);
	if (Local_u8FlagStatus)
	{
		/*Clear Flag*/
		Clear_ISRFlag.DMA_Num =DMA_1;
		Clear_ISRFlag.DMA_Stream_Num = STREAM_7;
		Clear_ISRFlag.DMA_ISR_Config = DMA_LISR;
		Clear_ISRFlag.DMA_ISR_Flag = DMA_TCIF0_FLAG;

		DMA_u8_clearInterruptFlag (&Clear_ISRFlag);
		/*Call Back Function.*/
		DMA1_STREAM_PTR_TOFUNC [DMA_1] [STREAM_7] [DMA_TCIF0_FLAG]();
	}
}
