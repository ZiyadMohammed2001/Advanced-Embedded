#ifndef STM32F446xx_H
#define STM32F446xx_H

/****************************  Various Memories Base Addresses  ****************************/


#define FLASH_BASE_ADDRESS		0x08000000UL
#define SRAM_BASE_ADDRESS		0x20000000UL
#define ROM_BASE_ADDRESS	  	0x1FFF0000UL

/*****************************    PPB Peripheral Base Addresses  ****************************/

/* Defining Base Address Of RCC */
#define SysTick_BASE_ADDRESS 		0xE000E010UL

#define SCB_BASE_ADDRESS			0xE000ED00//0xE000E008UL


/************************  AHB1 Peripheral Memories Base Addresses  ************************/

#define USB_OTG_HS_BASE_ADDRESS				0x40040000UL
#define DMA2_BASE_ADDRESS					0x40026400UL
#define DMA1_BASE_ADDRESS					0x40026000UL
#define BKPSRAM_BASE_ADDRESS				0x40024000UL
#define FLASH_INTERFACE_REG_BASE_ADDRESS	0x40023C00UL
#define RCC_BASE_ADDREESS					0x40023800UL
#define CRC_BASE_ADDRESS					0x40023000UL
#define GPIOA_BASE_ADDRESS					0x40020000UL
#define GPIOB_BASE_ADDRESS					0x40020400UL
#define GPIOC_BASE_ADDRESS					0x40020800UL
#define GPIOD_BASE_ADDRESS					0x40020C00UL
#define GPIOE_BASE_ADDRESS					0x40021000UL
#define GPIOF_BASE_ADDRESS					0x40021400UL
#define GPIOG_BASE_ADDRESS					0x40021800UL
#define GPIOH_BASE_ADDRESS					0x40021C00UL


/************************  AHB2 Peripheral Memories Base Addresses  ************************/

#define DCMI_BASE_ADDRESS					0x50050000UL
#define USB_OTG_FS_BASE_ADDRESS				0x50000000UL


/************************  AHB3 Peripheral Memories Base Addresses  ************************/

#define FMC_BASE_ADDRESS					0xA0000000UL
#define QUADSPI_BASE_ADDRESS				0xA0001000UL

/************************  APB1 Peripheral Memories Base Addresses  ************************/

#define DAC_BASE_ADDRESS					0x40012C00UL
#define PWR_BASE_ADDRESS					0x40007000UL
#define HDMI_CEC_BASE_ADDRESS				0x40006C00UL
#define CAN2_BASE_ADDRESS					0x40006800UL
#define CAN1_BASE_ADDRESS					0x40006400UL
#define I2C3_BASE_ADDRESS					0x40005C00UL
#define I2C2_BASE_ADDRESS					0x40005800UL
#define I2C1_BASE_ADDRESS					0x40005400UL
#define UART5_BASE_ADDRESS					0x40005000UL
#define UART4_BASE_ADDRESS					0x40004C00UL
#define USART3_BASE_ADDRESS					0x40004800UL
#define USART2_BASE_ADDRESS					0x40004400UL
#define SPDIF_RX_BASE_ADDRESS				0x40004000UL
#define SPI3_I2S3_BASE_ADDRESS				0x40003C00UL
#define SPI2_I2S2_BASE_ADDRESS				0x40003800UL
#define IWDG_BASE_ADDRESS					0x40003000UL
#define WWDG_BASE_ADDRESS					0x40002C00UL
#define RTC_BKP_BASE_ADDRESS				0x40002800UL
#define TIM14_BASE_ADDRESS					0x40002000UL
#define TIM13_BASE_ADDRESS					0x40001C00UL
#define TIM12_BASE_ADDRESS					0x40001800UL
#define TIM7_BASE_ADDRESS					0x40001400UL
#define TIM6_BASE_ADDRESS					0x40001000UL
#define TIM5_BASE_ADDRESS					0x40000C00UL
#define TIM4_BASE_ADDRESS					0x40000800UL
#define TIM3_BASE_ADDRESS					0x40000400UL
#define TIM2_BASE_ADDRESS					0x40000000UL

/************************  APB2 Peripheral Memories Base Addresses  ************************/

#define SAI2_BASE_ADDRESS					0x40045C00UL
#define SAI1_BASE_ADDRESS					0x40015800UL
#define TIM11_BASE_ADDRESS					0x40014800UL
#define TIM10_BASE_ADDRESS					0x40014400UL
#define TIM9_BASE_ADDRESS					0x40014000UL
#define EXTI_BASE_ADDRESS					0x40013C00UL
#define SYSCFG_BASE_ADDRESS					0x40013800UL
#define SPI4_BASE_ADDRESS					0x40013800UL
#define SPI1_BASE_ADDRESS					0x40013000UL
#define SDMMC_BASE_ADDRESS					0x40012C00UL
#define ADC1_ADC2_ADC3_BASE_ADDRESS			0x40012000UL
#define USART6_BASE_ADDRESS					0x40011400UL
#define USART1_BASE_ADDRESS					0x40011000UL
#define TIM8_BASE_ADDRESS					0x40010400UL
#define TIM1_BASE_ADDRESS					0x40010000UL

/***************************  GPIO Register Definition Structure ***************************/

typedef struct
{
	volatile uint32_t MODER; 		  		/*GPIO PORT Mode Register*/
	volatile uint32_t OTYPER; 				/*GPIO PORT Output type Register*/
	volatile uint32_t OSPEEDR; 				/*GPIO PORT Output speed Register*/
	volatile uint32_t PUPDR; 		  		/*GPIO PORT Pull Up / Down Register*/
	volatile uint32_t IDR; 			  		/*GPIO PORT Input Data Register*/
	volatile uint32_t ODR; 				  	/*GPIO PORT Output Data Register*/
	volatile uint32_t BSRR; 			  	/*GPIO PORT Port Bit set / Reset Register*/
	volatile uint32_t LCKR; 			  	/*GPIO PORT Lock Register*/
	volatile uint32_t AFR[2]; 				/*GPIO PORT Alternate function Register*/
}GPIO_RegDef_t;


/****************************  RCC Register Definition Structure ****************************/


typedef struct
{
  volatile uint32_t CR;            /*!< RCC clock control register,                                   */
  volatile uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                               */
  volatile uint32_t CFGR;          /*!< RCC clock configuration register,                             */
  volatile uint32_t CIR;           /*!< RCC clock interrupt register,                                 */
  volatile uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                           */
  volatile uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                           */
  volatile uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                           */
  uint32_t      RESERVED0;     	 	/*!< Reserved, 0x1C                                                */
  volatile uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           */
  volatile uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           */
  uint32_t      RESERVED1[2];  		/*!< Reserved, 0x28-0x2C                                           */
  volatile uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                           */
  volatile uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                           */
  volatile uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                           */
  uint32_t      RESERVED2;     		/*!< Reserved, 0x3C                                                */
  volatile uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                    */
  volatile uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                    */
  uint32_t      RESERVED3[2];  		/*!< Reserved, 0x48-0x4C                                           */
  volatile uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register,  */
  volatile uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register,  */
  uint32_t      RESERVED4;     		/*!< Reserved, 0x5C                                                */
  volatile uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register,  */
  uint32_t      RESERVED5[2];  		/*!< Reserved, 0x68-0x6C                                           */
  volatile uint32_t BDCR;          /*!< RCC Backup domain control register,                           */
  volatile uint32_t CSR;           /*!< RCC clock control & status register,                          */
  uint32_t      RESERVED6[2];  		/*!< Reserved, 0x78-0x7C                                           */
  volatile uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,                */
  volatile uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                            */
  volatile uint32_t PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                            */
  volatile uint32_t DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                  */
  volatile uint32_t CKGATENR;      /*!< RCC Clocks Gated ENable Register,                             */
  volatile uint32_t DCKCFGR2;      /*!< RCC Dedicated Clocks configuration register 2,                */
} RCC_RegDef_t;

/*******************************  RCC Peripheral Definition   *******************************/
#define RCC					((RCC_RegDef_t*)RCC_BASE_ADDREESS)

/*******************************  GPIO Peripheral Definition  *******************************/


#define GPIOA 				((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB 				((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC 				((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD 				((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE 				((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF 				((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG 				((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH 				((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)

/************************  System Time Systic Peripheral Definition  ************************/
typedef struct
{
	volatile uint32_t STK_CTRL;		/* SysTick Control and Status Register */
	volatile uint32_t STK_LOAD;		/* SysTick Reload Value Register */
	volatile uint32_t STK_VAL;		/* SysTick current Value Register */
	volatile uint32_t STK_CALIB;	/* SysTick Calibration Register */
} SysTick_REG_t;


/***************************  System Time Systic Base Addresses  ****************************/


#define SysTick_REG ((SysTick_REG_t *)SysTick_BASE_ADDRESS)


/*******************************  NVIC Peripheral Definition  *******************************/
typedef struct
{
	volatile uint32_t NVIC_ISER[8];
	volatile uint32_t RESERVED7[24];
	volatile uint32_t NVIC_ICER[8];
	volatile uint32_t RESERVED8[24];
	volatile uint32_t NVIC_ISPR[8];
	volatile uint32_t RESERVED9[24];
	volatile uint32_t NVIC_ICPR[8];
	volatile uint32_t NVIC_IABR[8];
	volatile uint32_t RESERVED10[32];
	volatile uint8_t NVIC_IPR[240];
	volatile uint32_t NVIC_STIR;
}NVIC_REG_t;

/***********************************  NVIC Base Address  ***********************************/
#define NVIC_BASE_ADDRESS		0xE000E100UL

#define NVIC_REGISTER			((NVIC_REG_t*)NVIC_BASE_ADDRESS)

/*******************  System control block Register Definition Structure *******************/

typedef struct
{
	//volatile uint32_t ACTLR;				/*Auxiliary Control Register.*/
	//volatile uint32_t RESERVED11[830];
	volatile uint32_t CPUID;				/*CPUID Base Register.*/
	volatile uint32_t ICSR;					/*Interrupt Control and State Register.*/
	volatile uint32_t VTOR;					/*Vector table Offset Register.*/
	volatile uint32_t AIRCR;				/*Application Interrupt and Reset Control Register.*/
	volatile uint32_t SCR;					/*System Control Register.*/
	volatile uint32_t CCR;					/*Configuration Control Register.*/
	volatile uint8_t SHPR [12U];			/*System Handlers priority Registers(4-7, 8-11, 12-15*/
	volatile uint32_t SHCSR;				/*System Handler control and state Register	*/
	volatile uint32_t CFSR;					/*Configurable fault status register (CFSR+UFSR+BFSR+MMFSR).*/
	volatile uint32_t HFSR;					/*HardFault Status Register*/
	volatile uint32_t DFSR;					/*Debug Fault Status Register.*/
	volatile uint32_t MMFAR;				/*MemManagre Fault Address Register.*/
	volatile uint32_t BFSR;					/*BusFault Address Register.*/
	volatile uint32_t AFSR;					/*Auxiliary Fault Status Register.*/
}SCB_REG_t;

/***********************************  SCB Base Address  ***********************************/

#define SCB_REGISTER			((SCB_REG_t*)SCB_BASE_ADDRESS)

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

/**************************  SYSCFG Register Definition Structure **************************/
typedef struct
{
	volatile uint32_t  MEMRMP;
	volatile uint32_t  PMC;
	volatile uint32_t  CR[4];
	volatile uint32_t  RESERVED_1[2];
	volatile uint32_t  CMPCR;
	volatile uint32_t  REVERSED[2];
	volatile uint32_t  CFGR;
}SYSCFG_RegDef_t;

/*******************************  SYSCFG Peripheral Definition  *******************************/

#define SYSCFG_REGISTER			((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)

/****************************  DMA Register Definition Structure ****************************/
typedef struct
{
	volatile uint32_t  DMA_LISR;
	volatile uint32_t  DMA_HISR;
	volatile uint32_t  DMA_LIFCR;
	volatile uint32_t  DMA_HIFCR;
	volatile uint32_t  DMA_SxCR;
	volatile uint32_t  DMA_SxNDTR;
	volatile uint32_t  DMA_SxPAR;
	volatile uint32_t  DMA_SxM0AR;
	volatile uint32_t  DMA_SxM1AR;
	volatile uint32_t  DMA_SxFCR;
}DMA_RegDef_t;

/***********************************  DMA Base Address  *************************************/

#define DMA1_REGISTER			((DMA_RegDef_t*)DMA1_BASE_ADDRESS)
#define DMA2_REGISTER			((DMA_RegDef_t*)DMA2_BASE_ADDRESS)

/***********************************  Stream Base Address  *************************************/

#define DMA1_Stream0        ((DMA_Stream_TypeDef *) DMA1_Stream0_BASE)
#define DMA1_Stream1        ((DMA_Stream_TypeDef *) DMA1_Stream1_BASE)
#define DMA1_Stream2        ((DMA_Stream_TypeDef *) DMA1_Stream2_BASE)
#define DMA1_Stream3        ((DMA_Stream_TypeDef *) DMA1_Stream3_BASE)
#define DMA1_Stream4        ((DMA_Stream_TypeDef *) DMA1_Stream4_BASE)
#define DMA1_Stream5        ((DMA_Stream_TypeDef *) DMA1_Stream5_BASE)
#define DMA1_Stream6        ((DMA_Stream_TypeDef *) DMA1_Stream6_BASE)
#define DMA1_Stream7        ((DMA_Stream_TypeDef *) DMA1_Stream7_BASE)

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
#define USART_6_REGISTER			((USART_RegDef_t*)	USART6_BASE_ADDRESS)

#endif
