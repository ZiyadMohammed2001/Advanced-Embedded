#ifndef RCC_PRV_H
#define RCC_PRV_H

#define RCC_SYS_CLK_NUM			3U

#define GET_BIT_VALUS_BY_ORING	1U
#define GET_BIT_VALUS_HIGH		1U
#define GET_BIT_VALUS_LOW		0U

#define THRESHOLD_VALUE			5000U


/******************* HSI Configuration *********************/
#define HSI_DISABLE_BIT			0xFFFFFFFEUL 	//1111 1111 1111 1111 1111 1111 1111 1110 by binary.
#define HSI_ENABLE_BIT			0x1UL			//0000 0000 0000 0000 0000 0000 0000 0001 by binary.
#define HSI_READY_BIT_NUMBER	1U

#define HSI_TRIMMING_CLEAR_BITS 0b1111111100000111UL
#define HSI_OPTIMIZING_TRIMMING_BITS	(TRIMMING_CLK)<<(3U)

/******************* HSE Configuration *********************/
#define HSE_BY_PASS_BIT_DIABLE			0xFFFEFFFFU					//1111 1111 1111 1110 1111 1111 1111 1111 by binary.

#define HSE_DISABLE_BIT					0xFFFEFFFFUL				//1111 1111 1111 1110 1111 1111 1111 1111 by binary.
#define HSE_ENABLE_BIT					0x00010000UL				//0000 0000 0000 0001 0000 0000 0000 0000 by binary.
#define HSE_READY_BIT_NUMBER			17U

#define HSE_BY_PASSED_OR_NOT_BY_PASSED_DISABLE		0U
#define HSE_BY_PASSED_OR_NOT_BY_PASSED 			    18U							//Selection bit of by passed or not by passed for HSE.
#define HSE_CLOCK_SECURITY_SYSTEM_BIT_DISABLE		0U
#define HSE_CLOCK_SECURITY_SYSTEM_BIT   			19U							//Selection bit of Clock Security System for HSE.

#define HSE_DIVISION_BITS_CLEAR			0xFFF0FFFFUL				//1111 1111 1111 0000 1111 1111 1111 1111
#define HSE_DIVISION_BITS_BEGIN			16U
/******************* PLL Configuration *********************/
#define PLL_DISABLE_BIT					0xFEFFFFFFUL				//1111 1110 1111 1111 1111 1111 1111 1111 by binary.
#define PLL_ENABLE_BIT					0x100000000UL				//0000 0001 0000 0000 0000 0000 0000 0000 by binary.
#define PLL_READY_BIT_NUMBER			25U

#define PLL_SELECT_SOURCE_MASK			0xFFBFFFFFUL	 			//1111 1111 1011 1111 1111 1111 1111 1111 by binary.
#define PLL_SELECT_SOURCE_BIT				22U
#define PLL_HSE_SOURCE_BIT				0x400000UL					//0000 0000 0100 0000 0000 0000 0000 0000 by binary.
#define PLL_SELECT_MULTIPLY_FACTOR_MASK 0xFFBFfFC0					//1111 1111 1011 1111 1111 1111 1100 0000 by binary.
/******************* PLLI2S Configuration *********************/
#define PLLI2S_DISABLE_BIT					0xFBFFFFFFUL				//1111 1011 1111 1111 1111 1111 1111 1111 by binary.
#define PLLI2S_ENABLE_BIT					0x4000000UL			    	//0000 0100 0000 0000 0000 0000 0000 0000 by binary.
#define PLLI2S_READY_BIT_NUMBER				27U

/******************* PLLSAI Configuration *********************/
#define PLLSAI_DISABLE_BIT					0xEFFFFFFFUL				//1110 1111 1111 1111 1111 1111 1111 1111 by binary.
#define PLLSAI_ENABLE_BIT					0x10000000UL				//0001 0000 0000 0000 0000 0000 0000 0000 by binary.
#define PLLSAI_READY_BIT_NUMBER				29U

/********************* Microcontroller clock output 1 ************************/
#define RCC_MCO1_PRESCALER					24U
#define RCC_MCO1_CLK_SELECT					21U

/********************* Microcontroller clock output 2 ************************/
#define RCC_MCO2_PRESCALER					27U
#define RCC_MCO2_CLK_SELECT					30U

#define RCC_CFGR_SYSTEMCLK_CLEAR_BITS		0xFFFFFFFCUL

/********************* AHB1 Configuration ************************/
#define RCC_AHB1_MASKING				0U
#define RCC_AHB1_SET_BIT				1U
/********************* APB1 Configuration ************************/
#define RCC_APB1_MASKING				0U
#define RCC_APB1_SET_BIT				1U
/********************* APB2 Configuration ************************/
#define RCC_APB2_MASKING				0U
#define RCC_APB2_SET_BIT				1U

/********************* APB1 Configuration in Low Power Mode ************************/
#define RCC_APB1_MASKING_LPM			0U
#define RCC_APB1_SET_BIT_LPM			1U
/********************* APB2 Configuration in Low Power Mode ************************/
#define RCC_APB2_MASKING_LPM			0U
#define RCC_APB2_SET_BIT_LPM			1U
#endif
