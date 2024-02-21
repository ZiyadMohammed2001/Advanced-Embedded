/*
 * SYSConfig_Program.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Ziyad
 */

#include <stdint.h>
#include "ErrType.h"
#include "Stm32f446.h"
#include "SYSCFG_Interface.h"
#include "SYSCFG_Private.h"

void SysCfg_voidSetEXTIPort(SYSCFG_LineNum_t copy_PinNum, SYSCFG_Port_t copy_Port)
{
	uint8_t Local_u8RegisterNum = copy_PinNum/SYSCFG_REG_SELECTION;
	uint8_t Local_u8BitNum = (copy_PinNum %SYSCFG_REG_SELECTION)*SYSCFG_REG_SELECTION;
	/*Clear the required bits*/
	SYSCFG_REGISTER -> CR[Local_u8RegisterNum] &= (~(SYSCFG_MASK<<Local_u8BitNum));
	/*Set the port Number Value*/
	SYSCFG_REGISTER -> CR[Local_u8RegisterNum] |= (copy_Port<<Local_u8BitNum);
}
