/*************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 24/9/2021          */
/*                     SWC: LCD                 */
/*                     Version: 1.0             */
/************************************************/
#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

//put them here not to the see see VALUES
#define LCD_u8_8_BIT_MODE            1
#define LCD_u8_4_BIT_MODE            2

//Macros for address of characters.
#define LCD_u8_DRAWCHARACTER_0       0x40
#define LCD_u8_DRAWCHARACTER_1       0x40+8
#define LCD_u8_DRAWCHARACTER_2       0x40+16
#define LCD_u8_DRAWCHARACTER_3       0x40+24
#define LCD_u8_DRAWCHARACTER_4       0x40+32
#define LCD_u8_DRAWCHARACTER_5       0x40+40
#define LCD_u8_DRAWCHARACTER_6       0x40+48
#define LCD_u8_DRAWCHARACTER_7       0x40+56


//easy for me
static void PRIVATE_voidSetHalfPort (u8 Copy_u8Value);

#endif // LCD_PRIVATE_H
