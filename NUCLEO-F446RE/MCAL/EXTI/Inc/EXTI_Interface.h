/*
 * EXTI_Interface.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Ziyad
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

typedef enum
{
	EXTI_PIN_1=0,
	EXTI_PIN_2,
	EXTI_PIN_3,
	EXTI_PIN_4,
	EXTI_PIN_5,
	EXTI_PIN_6,
	EXTI_PIN_7,
	EXTI_PIN_8,
	EXTI_PIN_9,
	EXTI_PIN_10,
	EXTI_PIN_11,
	EXTI_PIN_12,
	EXTI_PIN_13,
	EXTI_PIN_14,
	EXTI_PIN_15,
	EXTI_PIN_16,
	EXTI_PIN_17,
	EXTI_PIN_18,
	EXTI_PIN_19,
	EXTI_PIN_20,
	EXTI_PIN_21,
	EXTI_PIN_22,
}EXTI_lineNum_t;

typedef enum
{
	EXTI_RISING_TRIGGER=0,
	EXTI_FALLING_TRIGGER,
	EXTI_RISING_FALLING_TRIGGER
}EXTI_Trigger_Config_t;

typedef enum
{
	EXTI_ENABLE=0,
	EXTI_DISABLE
}EXTI_InitStatus_t;

typedef struct
{
	EXTI_lineNum_t EXTI_lineNum;
	EXTI_Trigger_Config_t EXTI_Trigger_Config;
	EXTI_InitStatus_t EXTI_InitStatus;
	void(*EXTI_Copy_pf)(void);
}EXTI_Init_Config_t;


/*
 * @fn EXTI_u8Init.
 * @berief	the function set configuration of external interrupt.
 * @Parameters	[in]  EXTI_Init : Initialize values of the external interrupt.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8Init (const EXTI_Init_Config_t *EXTI_Init_Config);

/*
 * @fn EXTI_u8SetTriggerSource.
 * @berief	the function set Trigger source for line of external interrupt.
 * @Parameters	[in]  EXTI_Trigger_Config : Select trigger source.
 * @Parameters	[in]  EXTI_lineNum : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8SetTriggerSource (EXTI_Trigger_Config_t EXTI_Trigger_Config,EXTI_lineNum_t EXTI_lineNum);

/*
 * @fn EXTI_u8EnableInt.
 * @berief	the function set enable one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8EnableInt(EXTI_lineNum_t EXTI_lineNum);

/*
 * @fn EXTI_u8DisableInt.
 * @berief	the function set Disable one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8DisableInt(EXTI_lineNum_t EXTI_lineNum);

/*
 * @fn EXTI_u8ClearPendingFlag.
 * @berief	the function clear pending flag for one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8ClearPendingFlag(EXTI_lineNum_t EXTI_lineNum);

/*
 * @fn EXTI_u8ReadPendingFlag.
 * @berief	the function clear pending flag for one of the external interrupt.
 * @Parameters	[in]  EXTI_line : the external interrupt line.
 * @Parameters	[in]  copy_flagStatus : Pointer to know the flag status.
 * @retval ErrorStatus.
 ********************************************************************/
uint8_t EXTI_u8ReadPendingFlag(EXTI_lineNum_t EXTI_lineNum, uint8_t* copy_flagStatus);

#endif /* EXTI_INTERFACE_H_ */
