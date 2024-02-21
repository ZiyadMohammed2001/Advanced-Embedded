#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/******************* SYSCLK *******************/
typedef enum RCC_SYS_CLK
{
	RCC_HSI = 0,
	RCC_HSE,
	RCC_PLL,
	RCC_PLLI2S,
	RCC_PLLSAI
}SYSCLK;

/******************* CLK State *******************/
typedef enum RCC_CLK_STATE
{
	CLK_ON = 0 ,
	CLK_OFF
}CLK_State;

typedef struct
{
	uint8_t RCC_SYSCLK;
	uint8_t RCC_CLkState;
}RCC_CLKStatus;

/******************* HSI Configuration *********************/
#define TRIMMING_CLK 	0b00000U // Select from Zero to 16.

/******************* HSE Configuration *********************/
typedef enum
{
	RCC_HSE_CLOCK_SECURITY_SYS_OFF = 0,
	RCC_HSE_CLOCK_SECURITY_SYS_ON
}RCC_HSE_CLOCK_SECURITY_SYS_t;

typedef enum
{
	RCC_HSE_Oscillator_Not_Bypassed = 0,
	RCC_HSE_Oscillator_Bypassed
}RCC_HSE_Clock_Bypass_t;

typedef enum
{
	HSE_NOT_DIVIDED = 0,
	HSE_DIVIDED_BY_2 = 2,
	HSE_DIVIDED_BY_3,
	HSE_DIVIDED_BY_4,
	HSE_DIVIDED_BY_5,
	HSE_DIVIDED_BY_6,
	HSE_DIVIDED_BY_7,
	HSE_DIVIDED_BY_8,
	HSE_DIVIDED_BY_9,
	HSE_DIVIDED_BY_10,
	HSE_DIVIDED_BY_11,
	HSE_DIVIDED_BY_12,
	HSE_DIVIDED_BY_13,
	HSE_DIVIDED_BY_14,
	HSE_DIVIDED_BY_15,
	HSE_DIVIDED_BY_16,
	HSE_DIVIDED_BY_17,
	HSE_DIVIDED_BY_18,
	HSE_DIVIDED_BY_19,
	HSE_DIVIDED_BY_20,
	HSE_DIVIDED_BY_21,
	HSE_DIVIDED_BY_22,
	HSE_DIVIDED_BY_23,
	HSE_DIVIDED_BY_24,
	HSE_DIVIDED_BY_25,
	HSE_DIVIDED_BY_26,
	HSE_DIVIDED_BY_27,
	HSE_DIVIDED_BY_28,
	HSE_DIVIDED_BY_29,
	HSE_DIVIDED_BY_30,
	HSE_DIVIDED_BY_31,
}RCC_HSE_Divider_t;

typedef struct
{
	uint8_t RCC_HSE_CLOCK_SECURITY_SYS;
	uint8_t RCC_HSE_Clock_Bypass;
	uint8_t RCC_HSE_Divider;
}RCC_HSE_CONFIG_t;
/******************* HSE bypass *********************/
#define  	HSE_NOTBYPASS  		0U
#define 	HSE_BYPASS			0x10000UL 		//00000000000000010000000000000000

#define HSE_BYPASS_NOTBYPASSED_SELECTION	HSE_BYPASS
/******************* HSE Clock Security System *********************/
typedef enum
{
	HSE_WITH_CLK_SECURITY_SYSTEM = 0,
	HSE_WITH_NO_CLK_SECURITY_SYSTEM
}HSE_Config_CSSR;

// Select Configuration of the HSE
typedef struct
{
	uint8_t HSE_divider_Factor;
	uint8_t HSE_WITH_OR_WITHOUT_CLK_SECURITY_SYSTEM;
}HSE_CONFIG;

/************************* RCC_CFGR ****************************/
typedef enum
{
	RCC_MCO_1,
	RCC_MCO_2
}RCC_Microcontroller_Output_Number;
/********************* Microcontroller clock output 1 ************************/
typedef enum
{
	RCC_MCO1_SYSCLK = 0,
	RCC_MCO1_PLLI2S,
	RCC_MCO1_HSE,
	RCC_MCO1_PLL
}RCC_MCO1_t;

typedef enum
{
	RCC_MCO1_PRESCALER_DVIVSION_BY_1 =0,
	RCC_MCO1_PRESCALER_DVIVSION_BY_2 =4,
	RCC_MCO1_PRESCALER_DVIVSION_BY_3,
	RCC_MCO1_PRESCALER_DVIVSION_BY_4,
	RCC_MCO1_PRESCALER_DVIVSION_BY_5
}RCC_MCO1_PRESCALER_DVIVSION_FACTOR_t;
/********************* Microcontroller clock output 2 ************************/
typedef enum
{
	RCC_MCO2_SYSCLK = 0,
	RCC_MCO2_PLLI2S,
	RCC_MCO2_HSE,
	RCC_MCO2_PLL
}RCC_MCO2_t;

typedef enum
{
	RCC_MCO2_PRESCALER_DVIVSION_BY_1 =0,
	RCC_MCO2_PRESCALER_DVIVSION_BY_2 =4,
	RCC_MCO2_PRESCALER_DVIVSION_BY_3,
	RCC_MCO2_PRESCALER_DVIVSION_BY_4,
	RCC_MCO2_PRESCALER_DVIVSION_BY_5
}RCC_MCO2_PRESCALER_DVIVSION_FACTOR_t;

typedef struct
{
	uint8_t RCC_Microcontroller_Output_Number;
	uint8_t RCC_Microcontroller_Output_Prescaler;
	uint8_t	RCC_Microcontroller_Output_SYSCLK;
}RCC_MCO_CONFIG_t;
/************************* PLL ****************************/
/*PLL Source.*/
typedef enum
{
	PLL_HSI = 0,
	PLL_HSE
}PLL_Source;
/***************PLL input clock options******************/
typedef enum
{
	PLL_X2 = 2,		/* PLL input clock x 2    */
	PLL_X3,			/* PLL input clock x 3    */
	PLL_X4,			/* PLL input clock x 4    */
	PLL_X5,			/* PLL input clock x 5    */
	PLL_X6,			/* PLL input clock x 6    */
	PLL_X7,			/* PLL input clock x 7    */
	PLL_X8,			/* PLL input clock x 8    */
	PLL_X9,			/* PLL input clock x 9    */
	PLL_X10,		/* PLL input clock x 10   */
	PLL_X11,		/* PLL input clock x 11   */
	PLL_X12,		/* PLL input clock x 12   */
	PLL_X13,		/* PLL input clock x 13   */
	PLL_X14,		/* PLL input clock x 14   */
	PLL_X15,		/* PLL input clock x 15   */
	PLL_X16,		/* PLL input clock x 16   */
	PLL_X17,		/* PLL input clock x 17   */
	PLL_X18,		/* PLL input clock x 18   */
	PLL_X19,		/* PLL input clock x 19   */
	PLL_X20,		/* PLL input clock x 20   */
	PLL_X21,		/* PLL input clock x 21   */
	PLL_X22,		/* PLL input clock x 22   */
	PLL_X23,		/* PLL input clock x 23   */
	PLL_X24,		/* PLL input clock x 24   */
	PLL_X25,		/* PLL input clock x 25   */
	PLL_X26,		/* PLL input clock x 26   */
	PLL_X27,		/* PLL input clock x 27   */
	PLL_X28,		/* PLL input clock x 28   */
	PLL_X29,		/* PLL input clock x 29   */
	PLL_X30,		/* PLL input clock x 30   */
	PLL_X31,		/* PLL input clock x 31   */
	PLL_X32,		/* PLL input clock x 32   */
	PLL_X33,		/* PLL input clock x 32   */
	PLL_X34,		/* PLL input clock x 34   */
	PLL_X35,		/* PLL input clock x 35   */
	PLL_X36,		/* PLL input clock x 36   */
	PLL_X37,		/* PLL input clock x 37   */
	PLL_X38,		/* PLL input clock x 38   */
	PLL_X39,		/* PLL input clock x 39   */
	PLL_X40,		/* PLL input clock x 40   */
	PLL_X41,		/* PLL input clock x 41   */
	PLL_X42,		/* PLL input clock x 42   */
	PLL_X43,		/* PLL input clock x 43   */
	PLL_X44,		/* PLL input clock x 44   */
	PLL_X45,		/* PLL input clock x 45   */
	PLL_X46,		/* PLL input clock x 46   */
	PLL_X47,		/* PLL input clock x 47   */
	PLL_X48,		/* PLL input clock x 48   */
	PLL_X49,		/* PLL input clock x 49   */
	PLL_X50,		/* PLL input clock x 50   */
	PLL_X51,		/* PLL input clock x 51   */
	PLL_X52,		/* PLL input clock x 52   */
	PLL_X53,		/* PLL input clock x 53   */
	PLL_X54,		/* PLL input clock x 54   */
	PLL_X55,		/* PLL input clock x 55   */
	PLL_X56,		/* PLL input clock x 56   */
	PLL_X57,		/* PLL input clock x 57   */
	PLL_X58,		/* PLL input clock x 58   */
	PLL_X59,		/* PLL input clock x 59   */
	PLL_X60,		/* PLL input clock x 60   */
	PLL_X61,		/* PLL input clock x 61   */
	PLL_X62,		/* PLL input clock x 62   */
	PLL_X63		    /* PLL input clock x 63   */
}PLL_Multiple_Factor;

/******************PLL entry clock source*********************/
typedef struct
{
	uint8_t PLL_source;
	uint8_t PLL_ClkOption;
	uint8_t PLL_HSEClkOption;
}PLL_CONFIG;

/*************************************************************/
/********************* AHB _Peripheral **********************/
/********************* AHB1 _Peripheral **********************/
typedef enum
{
	GPIOAEN = 0 ,
	GPIOBEN,
	GPIOCEN,
	GPIODEN,
	GPIOEEN,
	GPIOFEN,
	GPIOGEN,
	GPIOHEN,
	CRCEN = 12,
	BKPSRAMEN = 18,
	DMA1EN = 21,
	DMA2EN,
	OTGHSEN=29,
	OTGHSULPIEN
}RCC_AHB1ENR_t;

typedef enum
{
	RCC_AHB1ENR_STATE_No_RESET = 0,
	RCC_AHB1ENR_STATE_RESET
}RCC_AHB1ENR_STATE_t;

typedef struct
{
	uint8_t RCC_AHB1ENR_PORT;
	uint8_t RCC_AHB1ENR_STATE;
}RCC_AHB1ENR_CONFIG_t;

/********************* APB1 _Peripheral **********************/
typedef enum
{
	TIM2 = 0,
	TIM3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	TIM12,
	TIM13,
	TIM14,
	WWDG = 11,
	SPI2 = 14,
	SPI3,
	SPDIFRX,
	USART2,
	USART3,
	USART4,
	USART5,
	I2C1,
	I2C2,
	I2C3,
	FMPI2C1,
	CAN1,
	CAN2,
	CEC,
	PWR,
	DAC
}RCC_APB1ENR_t;

typedef enum
{
	RCC_APB1ENR_STATE_No_RESET = 0,
	RCC_APB1ENR_STATE_RESET
}RCC_APB1ENR_STATE_t;

typedef struct
{
	uint8_t RCC_APB1ENR_PORT;
	uint8_t RCC_APB1ENR_STATE;
}RCC_APB1ENR_CONFIG_t;
/********************* APB2 _Peripheral **********************/
typedef enum
{
	TIM1 = 0,
	TIM8,
	USART1RST = 4,
	USART2RST,
	ADC = 8,
	SDIO = 11,
	SPI1,
	SPI4,
	SYSCFG,
	TIM9 = 16,
	TIM10,
	TIM11,
	SAI1 = 22,
	SAI2
}RCC_APB2ENR_t;

typedef enum
{
	RCC_APB2ENR_STATE_No_RESET = 0,
	RCC_APB2ENR_STATE_RESET
}RCC_APB2ENR_STATE_t;

typedef struct
{
	uint8_t RCC_APB2ENR_PORT;
	uint8_t RCC_APB2ENR_STATE;
}RCC_APB2ENR_CONFIG_t;

/********************* APB1 Peripheral Low Power Mode **********************/
typedef enum
{
	TIM2_LPM = 0,
	TIM3_LPM,
	TIM4_LPM,
	TIM5_LPM,
	TIM6_LPM,
	TIM7_LPM,
	TIM12_LPM,
	TIM13_LPM,
	TIM14_LPM,
	WWDG_LPM = 11,
	SPI2_LPM = 14,
	SPI3_LPM,
	SPDIFRX_LPM,
	USART2_LPM,
	USART3_LPM,
	USART4_LPM,
	USART5_LPM,
	I2C1_LPM,
	I2C2_LPM,
	I2C3_LPM,
	FMPI2C1_LPM,
	CAN1_LPM,
	CAN2_LPM,
	CEC_LPM,
	PWR_LPM,
	DAC_LPM
}RCC_APB1ENR_LPM_t;

typedef enum
{
	RCC_APB1ENR_STATE_No_RESET_LPM = 0,
	RCC_APB1ENR_STATE_RESET_LPM
}RCC_APB1ENR_STATE_LPM_t;

typedef struct
{
	uint8_t RCC_APB1ENR_PORT_LPM;
	uint8_t RCC_APB1ENR_STATE_LPM;
}RCC_APB1ENR_CONFIG_LPM_t;
/********************* APB2 _Peripheral **********************/
typedef enum
{
	TIM1_LPM = 0,
	TIM8_LPM,
	USART1RST_LPM = 4,
	USART2RST_LPM,
	ADC_LPM = 8,
	SDIO_LPM = 11,
	SPI1_LPM,
	SPI4_LPM,
	SYSCFG_LPM,
	TIM9_LPM = 16,
	TIM10_LPM,
	TIM11_LPM,
	SAI1_LPM = 22,
	SAI2_LPM
}RCC_APB2ENR_LPM_t;

typedef enum
{
	RCC_APB2ENR_STATE_No_RESET_LPM = 0,
	RCC_APB2ENR_STATE_RESET_LPM
}RCC_APB2ENR_STATE_LPM_t;

typedef struct
{
	uint8_t RCC_APB2ENR_PORT_LPM;
	uint8_t RCC_APB2ENR_STATE_LPM;
}RCC_APB2ENR_CONFIG_LPM_t;

/******************************************************************************
 * Function Name:  RCC_uint8_tSetClkStatusSynch
 * Description:	The Function that Set Clock Status
 * Parameters: CLKStatus structure hold configuration
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tSetClkStatusSynch(RCC_CLKStatus * CLKStatus);//Done
/******************************************************************************
 * Function Name:  RCC_uint8_tDisableClkStatus
 * Description:	The Function disable CLK
 * Parameters: Copy_uint8_tclock RCC_HSI  | RCC_HSE |RCC_PLL
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tDisableClkStatus(uint8_t Copy_uint8_tclock);//Done
/******************************************************************************
 * Function Name:  RCC_uint8_tSetSysClk
 * Description:	The Function Set SYSCLk source (System clock switch)
 * Parameters: Copy_uint8_tSysClk SYSCLK  option   RCC_HSI  | RCC_HSE |RCC_PLL
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tSetSysClk(RCC_MCO_CONFIG_t*MCO_CONFIG_t);//Done
/******************************************************************************
 * Function Name:  RCC_uint8_tSetSysClk
 * Description:	The Function Set HSE Configuration
 * Parameters: RCC_HSE_CONFIG
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tHSEConfig(RCC_HSE_CONFIG_t * RCC_HSE_CONFIG);//Done.
/******************************************************************************
 * Function Name:  RCC_uint8_tPLLConfig
 * Description:	The Function Set PLL Configuration)
 * Parameters: PLL_Cfg
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_tPLLConfig(PLL_CONFIG  * PLL_Cfg);//Done.
/******************************************************************************
 * Function Name:  RCC_uint8_t_AHB_1_CLKConfiguration
 * Description:	The Function enable AHB Peripheral CLK
 * Parameters: GPIO_CONFIG
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_AHB_1_CLKConfiguration(RCC_AHB1ENR_CONFIG_t * RCC_AHB1ENR_CONFIG);
/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_AHB1ENR_CONFIG.
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_1_CLKConfiguration(RCC_APB1ENR_CONFIG_t * RCC_APB1ENR_CONFIG);
/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_APB1ENR_CONFIG
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_2_CLKConfiguration(RCC_APB2ENR_CONFIG_t * RCC_APB2ENR_CONFIG);
/******************************************************************************
 * Function Name:  RCC_ClockSecuritySystemEnable
 * Description:	Clock Security System Enable
 * Parameters: non
 * Return:	non
 ******************************************************************************/
void RCC_ClockSecuritySystemEnable(void);
/******************************************************************************
 * Function Name:  RCC_ClockSecuritySystemEnable
 * Description:	Clock Security System Disable
 * Parameters: non
 * Return:	non
 ******************************************************************************/
void RCC_ClockSecuritySystemDisable(void);

/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration_LPM
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_AHB1ENR_CONFIG_LPM.
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_1_CLKConfiguration_LPM(RCC_APB1ENR_CONFIG_LPM_t * RCC_APB1ENR_CONFIG_LPM);//Done
/******************************************************************************
 * Function Name:  RCC_uint8_t_APB_1_CLKConfiguration_LPM
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: RCC_APB1ENR_CONFIG_LPM
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_uint8_t_APB_2_CLKConfiguration_LPM(RCC_APB2ENR_CONFIG_LPM_t * RCC_APB2ENR_CONFIG_LPM);//Done.
#endif /* RCC_INTERFACE_H_ */
