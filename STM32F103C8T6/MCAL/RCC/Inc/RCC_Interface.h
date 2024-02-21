#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_


typedef enum
{
	RCC_HSI=0,
	RCC_HSE,
	RCC_PLL
}RCC_SYSCLK_t;
/******************* CLK State *******************/
typedef enum
{
	CLK_OFF =0,
	CLK_ON
}RCC_CLkState_t;

typedef struct
{
	RCC_SYSCLK_t RCC_SYSCLK;
	RCC_CLkState_t RCC_CLkState;
}RCC_CLKStatus_t;

/******************* HSE divider for PLL entry *********************/
typedef enum
{
	HSE_NOT_DIVIDED = 0,
	HSE_DIVIDED_BY_TWO
}RCC_HSE_DividerPll_t;
/******************* HSE bypass *********************/
typedef enum
{
	HSE_NOTBYPASS = 0,
	HSE_BYPASS
}RCC_HSE_ByPass_t;

/*************************PLL****************************/
/***************PLL input clock options******************/

typedef enum
{
	PLL_X2 = 0,		/* PLL input clock x 2    */
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
	PLL_X17			/* PLL input clock x 17   */
}RCC_PLL_Factor_t;


/******************PLL entry clock source*********************/

typedef enum
{
	PLL_HSI = 0,
	PLL_HSE
}RCC_PLL_CLK_t;

typedef struct
{
	RCC_PLL_CLK_t RCC_PLL_CLK;
	RCC_PLL_Factor_t RCC_PLL_Factor;
	RCC_HSE_DividerPll_t RCC_HSE_DividerPll;
}PLL_CFg_t;

/**************************************************/

/********************* AHB _Peripheral **********************/

#define DMA1EN     0
#define DMA2EN     1
#define SRAMEN     2
#define FLITFEN    4
#define CRCEN      6
#define FSMCEN     8
#define SDIOEN     10

/********************* AHB2 _Peripheral **********************/
#define AFIOEN   0
#define IOPAEN   2
#define IOPBEN   3
#define IOPCEN   4
#define IOPDEN   5
#define IOPEEN   6
#define IOPFEN   7
#define IOPGEN   8
#define ADC1EN   9
#define ADC2EN   10
#define TIM1EN   11
#define SPI1EN   12
#define TIM8EN   13
#define USART1EN 14
#define ADC3EN   15
#define TIM9EN   19
#define TIM10EN  20
#define TIM11EN  21
/********************* AHB1 _Peripheral **********************/
#define TIM2EN   0
#define TIM3EN   1
#define TIM4EN   2
#define TIM5EN   3
#define TIM6EN   4
#define TIM7EN   5
#define TIM12EN  6
#define TIM13EN  7
#define TIM14EN  8
#define WWDGEN   11
#define SPI2EN   14
#define SPI3EN   15
#define USART2EN 17
#define USART3EN 18
#define UART4EN  19
#define UART5EN  19
#define I2C1EN   21
#define I2C2EN   22
#define USBEN    23
#define CANEN    25
#define BKPEN    27
#define PWREN    28
#define DACEN    29


/******************************************************************************
 * Function Name:  RCC_u8SetClkStatusSynch
 * Description:	The Function that Set Clock Status
 * Parameters: CLKStatus structure hold configuration
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8SetClkStatusSynch(RCC_CLKStatus_t * RCC_CLKStatus);
/******************************************************************************/
/******************************************************************************
 * Function Name:  RCC_u8DisableClkStatus
 * Description:	The Function disable CLK
 * Parameters: Copy_u8clock RCC_HSI  | RCC_HSE |RCC_PLL
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8DisableClkStatus(uint8_t Copy_u8clock);
/******************************************************************************/
/******************************************************************************
 * Function Name:  RCC_u8SetSysClk
 * Description:	The Function Set SYSCLk source (System clock switch)
 * Parameters: Copy_u8SysClk SYSCLK  option   RCC_HSI  | RCC_HSE |RCC_PLL
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8SetSysClk(uint8_t Copy_u8SysClk);
/******************************************************************************/
/******************************************************************************
 * Function Name:  RCC_u8SetSysClk
 * Description:	The Function Set HSE Configuration
 * Parameters: Copy_u8HSE_Div  option  HSE_NOT_DIVIDED | HSE_DIVIDED_BY_TOW
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8HSEConfig(uint8_t Copy_u8HSE_Div);
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8HSESource
 * Description:	The Function Select HES
 * Parameters: Copy_u8HSE_Div  option  HSE_NOTBYPASS	HSE_BYPASS
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8HSESource(uint8_t Copy_u8Source );
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8PLLConfig
 * Description:	The Function Set PLL Configuration)
 * Parameters: PLL_Cfg
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8PLLConfig(PLL_CFg_t  * PLL_Cfg);
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8SetSysClock
 * Description:	The Function Select sys=tem clock and disable others.
 * Parameters: Copy_u8Peripheral : RCC_SYSCLK
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/

uint8_t RCC_u8SetSysClock(RCC_SYSCLK_t RCC_SYSCLK);

/******************************************************************************
 * Function Name:  RCC_u8AHBEnableCLK
 * Description:	The Function enable AHB Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:u8
 ******************************************************************************/
uint8_t RCC_u8AHBEnableCLK(uint8_t Copy_u8Peripheral);
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8AHB1EnableCLK
 * Description:	The Function enable APB1 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB1EnableCLK(uint8_t Copy_u8Peripheral);
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8AHB1EnableCLK
 * Description:	The Function enable APB2 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB2EnableCLK(uint8_t Copy_u8Peripheral);
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8AHBEnableCLK
 * Description:	The Function Disable AHB Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8AHBDisableCLK(uint8_t Copy_u8Peripheral);
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8AHB1EnableCLK
 * Description:	The Function Disable APB1 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB1DisableCLK(uint8_t Copy_u8Peripheral);
/******************************************************************************/

/******************************************************************************
 * Function Name:  RCC_u8AHB1EnableCLK
 * Description:	The Function Disable APB2 Peripheral CLK
 * Parameters: Copy_u8Peripheral : peripheral number
 * Return:	ErrorState , Type:uint8_t
 ******************************************************************************/
uint8_t RCC_u8APB2DisableCLK(uint8_t Copy_u8Peripheral);
/*****************************************************************************/

/******************************************************************************
 * Function Name:  RCC_ClockSecuritySystemEnable
 * Description:	Clock Security System Enable
 * Parameters: non
 * Return:	non
 ******************************************************************************/
void RCC_ClockSecuritySystemEnable(void);
/*****************************************************************************/

/******************************************************************************
 * Function Name:  RCC_ClockSecuritySystemEnable.
 * Description:	Clock Security System Disable.
 * Parameters: non.
 * Return:	non.
 ******************************************************************************/
void RCC_ClockSecuritySystemDisable(void);
/*****************************************************************************/

#endif /* RCC_INTERFACE_H_ */
