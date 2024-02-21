/*
 * SYSCFG_Interface.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Ziyad
 */

#ifndef SYSCFG_INTERFACE_H_
#define SYSCFG_INTERFACE_H_

typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG
}SYSCFG_Port_t;

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}SYSCFG_LineNum_t;


void SysCfg_voidSetEXTIPort(SYSCFG_LineNum_t copy_PinNum, SYSCFG_Port_t copy_Port);

#endif /* SYSCFG_INTERFACE_H_ */
