/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 24/9/2021          */
/*                     SWC: LCD                 */
/*                     Version: 1.0             */
/************************************************/
//Any macros need to change in interface.

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LCD_u8_SizeOfString           14
#define LCD_u8_SizeOfArabicString     5

/*Macros For Line Numbers*/

#define LCD_u8_LINE_1       0
#define LCD_u8_LINE_2       1

/*Macros For Character Location*/

#define LCD_u8_LOCATION_0             0
#define LCD_u8_LOCATION_1             1
#define LCD_u8_LOCATION_2             2
#define LCD_u8_LOCATION_3             3
#define LCD_u8_LOCATION_4             4
#define LCD_u8_LOCATION_5             5
#define LCD_u8_LOCATION_6             6
#define LCD_u8_LOCATION_7             7
#define LCD_u8_LOCATION_8             8
#define LCD_u8_LOCATION_9             9

#define LCD_u8_LOCATION_10            10
#define LCD_u8_LOCATION_11            11
#define LCD_u8_LOCATION_12            12
#define LCD_u8_LOCATION_13            13
#define LCD_u8_LOCATION_14            14
#define LCD_u8_LOCATION_15            15
#define LCD_u8_LOCATION_16            16
#define LCD_u8_LOCATION_17            17
#define LCD_u8_LOCATION_18            18
#define LCD_u8_LOCATION_19            19

#define LCD_u8_LOCATION_20            20
#define LCD_u8_LOCATION_21            21
#define LCD_u8_LOCATION_22            22
#define LCD_u8_LOCATION_23            23
#define LCD_u8_LOCATION_24            24
#define LCD_u8_LOCATION_25            25
#define LCD_u8_LOCATION_26            26
#define LCD_u8_LOCATION_27            27
#define LCD_u8_LOCATION_28            28
#define LCD_u8_LOCATION_29            29

#define LCD_u8_LOCATION_30            30
#define LCD_u8_LOCATION_31            31
#define LCD_u8_LOCATION_32            32
#define LCD_u8_LOCATION_33            33
#define LCD_u8_LOCATION_34            34
#define LCD_u8_LOCATION_35            35
#define LCD_u8_LOCATION_36            36
#define LCD_u8_LOCATION_37            37
#define LCD_u8_LOCATION_38            38
#define LCD_u8_LOCATION_39            39

/*Macros For Character Numbers*/

#define LCD_u8_CHARACTER_0        0 //First character in CGRAM.
#define LCD_u8_CHARACTER_1        1 //Second character in CGRAM.
#define LCD_u8_CHARACTER_2        2 //Third character in CGRAM.
#define LCD_u8_CHARACTER_3        3 //Fourth character in CGRAM.
#define LCD_u8_CHARACTER_4        4 //Fifth character in CGRAM.
#define LCD_u8_CHARACTER_5        5 //Sixth character in CGRAM.
#define LCD_u8_CHARACTER_6        6 //Seventh character in CGRAM.
#define LCD_u8_CHARACTER_7        7 //Eighth character in CGRAM.

/*Macros for shifting type*/

#define LCD_u8_Shifting_Right       0
#define LCD_u8_Shifting_Left        1

u8 LCD_SelectMode(u8 Copy_u8Mode);
void LCD_voidFour_Init(void);
void LCD_voidInit(void);
void LCD_voidWriteChar(u8 Copy_u8Char);
void LCD_voidWriteCmnd(u8 Copy_u8Cmnd);
void LCD_voidWriteString (u8* Copy_pu8String, u8 Copy_u8NumberOfCharacters);
void LCD_voidPrintString (u8* Copy_pu8String);
void LCD_voidPrintNumber (u32 Copy_u32Number);
u8 LCD_u8GoToXY(u8 Copy_u8LineNumber ,u8 Copy_u8CharacterLocation );
u8 LCD_u8DrawCharacter(u8 Copy_u8NumberOfCharacter);
u8 LCD_u8PrintDrawnCharacter(u8 Copy_u8CharacterNumber);
void LCD_voidSavedCharacters(void);
u8 LCD_u8printSavedCharacters(u8 Copy_u8LineNumber ,u8 Copy_u8CharacterLocation );
u8 LCD_u8InfiniteShiftingDisplayRegion(u8 Copy_u8ShiftingDirection);
u8 LCD_u8ShiftingDisplayRegion(u8 Copy_u8ShiftingDirection,u8 Copy_u8ShiftingSteps);
u8 LCD_u8PrintTwoWordsInSinusoidalWave(u8* Copy_pu8String_1);//One from saved characters.
void LCD_u8ClearScreen(void);
#endif

