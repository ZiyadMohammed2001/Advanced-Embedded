#ifndef USART_PRV_H
#define USART_PRV_H

#define USART_F_CK					(FREQUENCT_CLK_OF_MC_MHz * (10^6))UL
#define USART_SET					1U
#define USART_TOTAL_NUM				5U
#define USART_TOTAL_INTERRUPT_NUM	9U

#define USART_CR1_RX_Mask			0xFFFFFFFBUL
#define USART_CR1_RX_BIT			2U
#define USART_CR1_RXNEIE_BIT		5U
#define USART_CR1_ENABLE_DISABLE	13U

#define USART_CR1_TX_Mask			0xFFFFFFF7UL
#define USART_CR1_TX_BIT			3U
#define USART_CR1_TXEIE_BIT			7U
#define USART_CR1_TC_BIT			6U

#define USART_CR1_WL_Mask			0xFFFFEFFFUL
#define USART_CR1_WL_BIT			12U

#define USART_CR1_WAKE_Mask			0xFFFFF7FFUL
#define USART_CR1_WAKE_BIT			11U

#define USART_CR1_PE_ENABLE_DISABLE	8U

#define USART_CR1_IDLEIE_BIT		4U

#define USART_CR2_LBDIE_BIT			6U

#define USART_CR3_CTS_Mask			0xFFFFFDFFUL
#define USART_CR3_CTS_BIT			9U

#define USART_CR3_RTS_Mask			0xFFFFFEFFUL
#define USART_CR3_RTS_BIT			8U

#define USART_CR3_DMA_T_Mask		0xFFFFFF7FUL
#define USART_CR3_DMA_T_BIT			7U

#define USART_CR3_DMA_R_Mask		0xFFFFFFBFUL
#define USART_CR3_DMA_R_BIT			6U
#define USART_CR3_CTSIE_BIT			10U

#define USART_STOP_BITS_MasK		0xFFFFCFFFUL
#define USART_STOP_BITS_BIT			12U

#define USART_PCE_BIT_MasK			0xFFFFFBFFUL
#define USART_PCE_BIT_BIT			10U

#define USART_PS_BIT_MasK			0xFFFFFDFFUL
#define USART_PS_BIT_BIT			9U

#define USART_DIV_Fraction_Round	500U
#define USART_DIV_Fraction_REAl		1000U
#define USART_Mantissa_SHIFT		4U

#define USART_SR_CTS_FALG_BIT		9U
#define USART_SR_CTS_FALG_MASK		0xFFFFFDFFUL

#define USART_SR_LBD_BIT			8U

#define USART_SR_CTS_BIT			9U
#define USART_SR_LBD_BIT			8U
#define USART_SR_TXE_BIT			7U
#define USART_SR_TC_BIT				6U
#define USART_SR_RXNE_BIT			5U
#define USART_SR_IDLE_BIT			4U
#define USART_ORE_BIT				3U
#define USART_NF_BIT				2U
#define USART_FE_BIT				1U
#define USART_PE_BIT				0U

#define USART_BAUDRATE				16.0F
#define USART_OS					1000000000UL


#endif
