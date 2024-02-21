/*
 * Systic_interface.h
 *
 *  Created on: Jul 2, 2023
 *      Author: Ziyad
 */

#ifndef SYSTIC_INTERFACE_H_
#define SYSTIC_INTERFACE_H_

typedef enum
{
	SYSTIC_CLK_SOURCE_AHB_CLK_DIVIDED_BY_8=0,
	SYSTIC_CLK_SOURCE_AHB_CLK
}Systic_CLKSource_t;

typedef struct
{
	uint32_t Time;
	Systic_CLKSource_t Systic_CLKSource;
}Systic_Config_t;

uint8_t SysTick_u8_Delay_ms(const Systic_Config_t* Systic_Config);
uint8_t SysTick_u8_Delay_us(const Systic_Config_t* Systic_Config);

#endif /* SYSTIC_INTERFACE_H_ */
