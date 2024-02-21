/*********************************************************************************/
/*                               Name : Ziyad Mohammed                           */
/*                               Date : 24/9/2021                                */
/*                               SWC  : LCD                                      */
/*                            version : 1.0                                      */
/*********************************************************************************/
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

/* Options : 1- LCD_u8_8_BIT_MODE
 * 			 2- LCD_u8_4_BIT_MODE */
#define LCD_u8_MODE                   	LCD_u8_4_BIT_MODE


#define LCD_u8_RS_PIN                  	PIN11
#define LCD_u8_RS_PORT                 	PORTA

#define LCD_u8_EN_PIN                  	PIN8
#define LCD_u8_EN_PORT                 	PORTA

#define LCD_u8_DATA_PORT               	PORTB

/* Configuration of 4 Bit Mode Pins */
#define LCD_u8_D4_PIN                 	PIN15
#define LCD_u8_D4_PORT                	PORTB

#define LCD_u8_D5_PIN                 	PIN14
#define LCD_u8_D5_PORT                	PORTB

#define LCD_u8_D6_PIN                 	PIN13
#define LCD_u8_D6_PORT                	PORTB

#define LCD_u8_D7_PIN              		PIN12
#define LCD_u8_D7_PORT                	PORTB

#endif
