#ifndef STM32F103xx_H
#define STM32F103xx_H

/****************************  Various Memories Base Addresses  ****************************/

#define FLASH_BASE_ADDRESS			0x40023000UL
#define SRAM_BASE_ADDRESS	  	 	0x20000000UL
#define ROM_BASE_ADDRESS	  		0x1FFFF000UL

/************************  AHB Peripheral Memories Base Addresses  ************************/

#define FSMC_BASE_ADDRESS			0xA0000000UL
#define USB_OTG_FS_BASE_ADDRESS		0x50000000UL
#define ETHERNET_BASE_ADDRESS		0x40028000UL
#define CRC_BASE_ADDRESS			0x40023000UL
#define FLASH_MEMORY_BASE_ADDRESS	0x40022000UL
#define RCC_BASE_ADDREESS			0x40021000UL
#define DMA2_BASE_ADDRESS			0x40020400UL
#define DMA1_BASE_ADDRESS			0x40020000UL
#define SDIO_BASE_ADDRESS			0x40018000UL
#define FSMC_BASE_ADDRESS			0xA0000000UL
#define FSMC_BASE_ADDRESS			0xA0000000UL
#define FSMC_BASE_ADDRESS			0xA0000000UL
#define FSMC_BASE_ADDRESS			0xA0000000UL
#define FSMC_BASE_ADDRESS			0xA0000000UL
#define FSMC_BASE_ADDRESS			0xA0000000UL
#define FSMC_BASE_ADDRESS			0xA0000000UL

/************************  APB2 Peripheral Memories Base Addresses  ************************/

#define TIM_11_BASE_ADDRESS			0x40015400UL
#define TIM_10_BASE_ADDRESS			0x40015000UL
#define TIM_9_BASE_ADDRESS			0x40014C00UL
#define ADC_3_BASE_ADDRESS			0x40013C00UL
#define USART1_BASE_ADDRESS			0x40013800UL
#define TIM_8_BASE_ADDRESS			0x40013400UL
#define SPI1_BASE_ADDRESS			0x40013000UL
#define TIM_1_BASE_ADDRESS			0x40012C00UL
#define ADC2_BASE_ADDRESS			0x40012800UL
#define ADC1_BASE_ADDRESS			0x40012400UL
#define GPIOA_BASE_ADDRESS			0x40010800UL
#define GPIOB_BASE_ADDRESS			0x40010C00UL
#define GPIOC_BASE_ADDRESS			0x40011000UL
#define GPIOD_BASE_ADDRESS			0x40011400UL
#define GPIOE_BASE_ADDRESS			0x40011800UL
#define GPIOF_BASE_ADDRESS			0x40011C00UL
#define GPIOG_BASE_ADDRESS			0x40012000UL
#define EXTI_BASE_ADDRESS			0x40010400UL
#define AFIO_BASE_ADDRESS			0x40010000UL

/************************  APB1 Peripheral Memories Base Addresses  ************************/
#define DAC_BASE_ADDRESS			0x40007400UL
#define PWR_BASE_ADDRESS			0x40007000UL
#define BKP_BASE_ADDRESS			0x40006C00UL
#define BxCAN1_BASE_ADDRESS			0x40006400UL
#define BxCAN2_BASE_ADDRESS			0x40006800UL
#define USB_CAN_SRAM_BASE_ADDRESS	0x40006000UL
#define USB_FS_BASE_ADDRESS			0x40005C00UL
#define I2C2_BASE_ADDRESS			0x40005800UL
#define I2C1_BASE_ADDRESS			0x40005400UL
#define USART2_BASE_ADDRESS			0x40004400UL
#define USART3_BASE_ADDRESS			0x40004800UL
#define UART4_BASE_ADDRESS			0x40004C00UL
#define UART5_BASE_ADDRESS			0x40005000UL
#define SPI3_I2S_BASE_ADDRESS		0x40003C00UL
#define SPI2_I2S_BASE_ADDRESS		0x40003800UL
#define IWDG_BASE_ADDRESS			0x40003000UL
#define WWDG_BASE_ADDRESS			0x40002C00UL
#define RTC_BASE_ADDRESS			0x40002800UL
#define TIM_14_BASE_ADDRESS			0x40002000UL
#define TIM_13_BASE_ADDRESS			0x40001C00UL
#define TIM_12_BASE_ADDRESS			0x40001800UL
#define TIM_7_BASE_ADDRESS			0x40001400UL
#define TIM_6_BASE_ADDRESS			0x40001000UL
#define TIM_5_BASE_ADDRESS			0x40000C00UL
#define TIM_4_BASE_ADDRESS			0x40000800UL
#define TIM_3_BASE_ADDRESS			0x40000400UL
#define TIM_2_BASE_ADDRESS			0x40000000UL

/***************************  GPIO Register Definition Structure ***************************/

typedef struct
{
  volatile uint32_t GPIO_CR[2]; 			  	/*GPIO PORT Mode Register*/
  volatile uint32_t GPIO_IDR; 			  		/*GPIO PORT Input Data Register*/
  volatile uint32_t GPIO_ODR; 				  	/*GPIO PORT Output Data Register*/
  volatile uint32_t GPIO_BSRR; 		  	  	/*GPIO PORT Port Bit set / Reset Register*/
  volatile uint32_t GPIO_BRR; 		  	  	/*GPIO PORT Port Bit Reset Register*/
  volatile uint32_t GPIO_LCKR; 			     	/*GPIO PORT Lock Register*/
	
}GPIO_RegDef_t;


/****************************  RCC Register Definition Structure ****************************/


typedef struct
{
  volatile uint32_t RCC_CR;            /*!< RCC clock control register,                                   */
  volatile uint32_t RCC_CFGR;          /*!< RCC clock configuration register,                             */
  volatile uint32_t RCC_CIR;           /*!< RCC clock interrupt register,                                 */
  volatile uint32_t RCC_APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           */
  volatile uint32_t RCC_APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           */
  volatile uint32_t RCC_AHBENR;        /*!< RCC AHB peripheral clock register,                           */
  volatile uint32_t RCC_APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                    */
  volatile uint32_t RCC_APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                    */
  volatile uint32_t RCC_BDCR;          /*!< RCC Backup domain control register,                           */
  volatile uint32_t RCC_CSR;           /*!< RCC clock control & status register,                          */
} RCC_RegDef_t;

/*******************************  RCC Peripheral Definition   *******************************/
#define RCC				                  	((RCC_RegDef_t*)RCC_BASE_ADDREESS)

/*******************************  GPIO Peripheral Definition  *******************************/


#define GPIOA 				((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB 				((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC 				((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD 				((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE 				((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF 				((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG 				((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)

/************************  System Time Systic Peripheral Definition  ************************/
typedef struct
{
	volatile uint32_t STK_CTRL;
	volatile uint32_t STK_LOAD;
	volatile uint32_t STK_VAL;
	volatile uint32_t STK_CALIB;
} SysTick_REG_t;


/***************************  System Time Systic Base Addresses  ****************************/
/* Defining Base Address Of RCC */
#define SysTick_BASE_ADDRESS 		0xE000E010

#define SysTick_REG ((SysTick_REG_t *)SysTick_BASE_ADDRESS)

/***************************  USART Register Definition Structure ***************************/
typedef struct
{
	volatile uint32_t USART_SR ;
	volatile uint32_t USART_DR ;
	volatile uint32_t USART_BRR ;
	volatile uint32_t USART_CR1 ;
	volatile uint32_t USART_CR2 ;
	volatile uint32_t USART_CR3 ;
	volatile uint32_t USART_GTPR ;
}USART_RegDef_t;

/**********************************  USART Base Address  ************************************/

#define USART_1_REGISTER			((USART_RegDef_t*)	USART1_BASE_ADDRESS)
#define USART_2_REGISTER			((USART_RegDef_t*)	USART2_BASE_ADDRESS)
#define USART_3_REGISTER			((USART_RegDef_t*)	USART3_BASE_ADDRESS)
#define UART_4_REGISTER				((USART_RegDef_t*)	UART4_BASE_ADDRESS)
#define UART_5_REGISTER				((USART_RegDef_t*)	UART5_BASE_ADDRESS)

/**************************  EXTI Register Definition Structure ***************************/

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_RegDef_t;;

/***********************************  EXTI Base Address  ***********************************/

#define EXTI_REGISTER			((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)

#endif
