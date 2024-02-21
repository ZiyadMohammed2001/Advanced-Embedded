/*
 * NVIC_Interface.h
 *
 *  Created on: Jul 5, 2023
 *      Author: Ziyad
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

typedef enum
{
	WWDG_Interrupt = 0,
	PVD_Interrupt,
	TAMP_STAMP_Interrupt,
	RTC_WKUP_Interrupt,
	FLASH_Interrupt,
	RCC_Interrupt,
	EXTI0_Interrupt,
	EXTI1_Interrupt,
	EXTI2_Interrupt,
	EXTI3_Interrupt,
	EXTI4_Interrupt,
	DMA1_Stream_0_Interrupt,
	DMA1_Stream_1_Interrupt,
	DMA1_Stream_2_Interrupt,
	DMA1_Stream_3_Interrupt,
	DMA1_Stream_4_Interrupt,
	DMA1_Stream_5_Interrupt,
	DMA1_Stream_6_Interrupt,
	ADC_Interrupt,
	CAN1_TX_Interrupt,
	CAN1_RX0_Interrupt,
	CAN1_RX1_Interrupt,
	CAN1_SCE_Interrupt,
	EXTI9_5_Interrupt,
	TIM1_BRK_TIM9_Interrupt,
	TIM1_UP_TIM10_Interrupt,
	TIM1_TRG_COM_TIM11_Interrupt,
	TIM1_CC_Interrupt,
	TIM2_Interrupt,
	TIM3_Interrupt,
	TIM4_Interrupt,
	I2C1_EV_Interrupt,
	I2C1_ER_Interrupt,
	I2C2_EV_Interrupt,
	I2C2_ER_Interrupt,
	SPI1_Interrupt,
	SPI2_Interrupt,
	USART1_Interrupt,
	USART2_Interrupt,
	USART3_Interrupt,
	EXTI15_10_Interrupt,
	RTC_Alarm_Interrupt,
	OTG_FS_WKUP_Interrupt,
	TIM8_BRK_TIM12_Interrupt,
	TIM8_UP_TIM13_Interrupt,
	TIM8_TRG_COM_TIM14_Interrupt,
	TIM8_CC_Interrupt,
	DMA1_Stream7_Interrupt,
	FMC_Interrupt,
	SDIO_Interrupt,
	TIM5_Interrupt,
	SPI3_Interrupt,
	UART4_Interrupt,
	UART5_Interrupt,
	TIM6_DAC_Interrupt,
	TIM7_Interrupt,
	DMA2_Stream_0_Interrupt,
	DMA2_Stream_1_Interrupt,
	DMA2_Stream_2_Interrupt,
	DMA2_Stream_3_Interrupt,
	DMA2_Stream_4_Interrupt,
	Reserved_1_Interrupt,
	Reserved_2_Interrupt,
	CAN2_TX_Interrupt,
	CAN2_RX0_Interrupt,
	CAN2_RX1_Interrupt,
	CAN2_SCE_Interrupt,
	OTG_FS_Interrupt,
	DMA2_Stream5_Interrupt,
	DMA2_Stream6_Interrupt,
	DMA2_Stream7_Interrupt,
	USART6_Interrupt,
	I2C3_EV_Interrupt,
	I2C3_ER_Interrupt,
	OTG_HS_EP1_OUT_Interrupt,
	OTG_HS_EP1_IN_Interrupt,
	OTG_HS_WKUP_Interrupt,
	OTG_HS_Interrupt,
	DCMI_Interrupt,
	Reserved_3_Interrupt,
	Reserved_4_Interrupt,
	FPU_Interrupt,
	Reserved_5_Interrupt,
	Reserved_6_Interrupt,
	SPI4_Interrupt,
	Reserved_7_Interrupt,
	Reserved_8_Interrupt,
	SAI1_Interrupt,
	Reserved_9_Interrupt,
	Reserved_10_Interrupt,
	Reserved_11_Interrupt,
	SAI2_Interrupt,
	QuadSPI_Interrupt,
	HDMI_CEC_Interrupt,
	SPDIF_Rx_Interrupt,
	FMPI2C1_Interrupt,
	FMPI2C1_error_Interrupt
}NVIC_INTERRUPT_REGQUEST_t;

/********************************************************************
 * @fn NVIC_u8_Enable_Interrupt.
 * @berief	the function Enables the System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t NVIC_u8_Enable_Interrupt ( uint8_t Copy_u8IRQNum);

/********************************************************************
 * @fn NVIC_u8_Disable_Interrupt.
 * @berief	the function Disables the System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Disable_Interrupt ( uint8_t Copy_u8IRQNum);

/********************************************************************
 * @fn NVIC_u8_Set_Pending_Flag.
 * @berief	the function Enables the pending flag of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Set_Pending_Flag ( uint8_t Copy_u8IRQNum);

/********************************************************************
 * @fn NVIC_u8_Clear_Pending_Flag.
 * @berief	the function Enables the pending flag of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Clear_Pending_Flag ( uint8_t Copy_u8IRQNum);

/********************************************************************
 * @fn NVIC_u8_Get_Active_Flag.
 * @berief	the function get the active flag of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception , *Copy_u8ActiveFlagStatus : pointer to return the status of active flag.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Get_Active_Flag ( uint8_t Copy_u8IRQNum , uint8_t* Copy_u8ActiveFlagStatus);

/********************************************************************
 * @fn NVIC_u8_Set_Priority.
 * @berief	the function Set priority of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8_Set_Priority ( uint8_t Copy_u8IRQNum , uint8_t Copy_u8PriorityNum);

/********************************************************************
 * @fn NVIC_u8SetCallBack.
 * @berief	the function set a function to be execution in the ISR of a System interrupt.
 * @Parameters	[in]  Copy_u8IRQNum : Select System exception .
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t NVIC_u8SetCallBack(uint8_t Copy_u8IRQNum,void(*Copy_pf)(void));

#endif /* NVIC_INTERFACE_H_ */
