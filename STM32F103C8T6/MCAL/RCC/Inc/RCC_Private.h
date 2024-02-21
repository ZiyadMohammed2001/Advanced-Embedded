#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#define 	RCC_SET_CLR_BIT	1U

/********************CR ********************/
#define  	RCC_PLLRDY 	25U     /* PLL clock ready flag*/
#define  	RCC_PLLON  	24U     /*PLL enable*/
#define  	RCC_CSSON  	19U     /*Clock security system enable*/
#define  	RCC_HSEBYP 	18U     /*External high-speed clock bypass*/
#define  	RCC_HSERDY 	17U     /*External high-speed clock ready flag*/
#define  	RCC_HSEON  	16U     /*HSE clock enable*/
#define  	RCC_HSIRDY 	1U      /*Internal high-speed clock ready flag*/
#define  	RCC_HSION  	0      /*Internal high-speed clock enable*/
/************************* CFGR ****************************/
#define 	RCC_PLLXTPRE 	17U
#define  	RCC_PLLSRC 		16U
/************************* SW : System clock switch ****************************/
#define 	RCC_SW_MASK   0b11 //(System clock switch) mask
#define 	RCC_HSI       0b00  /*HSI selected as system clock*/
#define 	RCC_HSE       0b01  /*HSE selected as system clock*/
#define 	RCC_PLL       0b10  /*PLL selected as system clock*/

#define 	RCC_PLL_MASK 		0b1111
#define 	RCC_HSE_BYBASS_MASK 0b1
#define 	RCC_HSE_SW_MASK 	0b1
#define 	RCC_PLLMUL			18U

#endif /* RCC_PRIVATE_H_ */
