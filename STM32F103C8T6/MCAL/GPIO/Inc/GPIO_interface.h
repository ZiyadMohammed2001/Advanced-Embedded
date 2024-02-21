#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
/************************  AHB1 Peripheral Memories Base Addresses  ************************/
/*
 * @Port_t enum
 */
typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
}Port_t;

/*
 * @Pin_t enum
 */
typedef enum 
{
	PIN0 = 0,
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
}Pin_t;

typedef enum
{
	GPIO_INPUT=0,
	GPIO_OUTPUT
}GPIO_Input_OUTPUT_Mode_t;

typedef enum
{
	GPIO_ANALOG_MODE=0,
	GPIO_FLOATING_INPUT,
	GPIO_PULLUP_OR_PULLDOWN,
}GPIO_Input_Mode_t;

typedef enum
{
	GPIO_General_Purpose_Output_Push_Pull=0,
	GPIO_General_Purpose_Output_Open_Drain,
	GPIO_Alternate_Function_Output_Push_Pull,
	GPIO_Alternate_Function_Output_Open_Drain,
}GPIO_Ouput_Mode_t;

typedef enum
{
	INPUT_PULL_UP=0,
	INPUT_PULL_DOWN
}GPIO_Input_Pull_UP_Down_t;

typedef enum
{
	INPUT=0,
	OUTPUT_MEDIUM_SPEED_10MHZ,
	OUTPUT_LOW_SPEED_2MHZ,
	OUTPUT_HIGH_SPEED_50MHZ

}GPIO_Input_OutputSpeed_t;

/*
 * @PinVal_t enum
 */
typedef enum
{
	PIN_LOW=0,
	PIN_HIGH
}GPIO_PinVal_t;

typedef enum
{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}GPIO_AltFunc_t;

typedef struct
{
	Port_t Port;
	Pin_t PinNum;
	GPIO_Input_OUTPUT_Mode_t GPIO_Input_OUTPUT_Mode;
	GPIO_Input_Mode_t GPIO_Input_Mode;
	GPIO_Input_Pull_UP_Down_t GPIO_Input_Pull_UP_Down;
	GPIO_Ouput_Mode_t  GPIO_Ouput_Mode;
	GPIO_Input_OutputSpeed_t GPIO_Input_OutputSpeed;
	GPIO_PinVal_t GPIO_PinVal;
	GPIO_AltFunc_t GPIO_AltFunc;
}GPIO_PinConfig_t;

/********************************************************************
 * @fn GPIO_u8Set_4_PinValue.
 * @berief	the function outputs a certain value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : First Pin number, Get options @Pin_t enum.
 * @Parameters	[in]  PinVal : The Output value , get options @PinVal_t enum
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8Set_4_PinValue (Port_t Port, Pin_t GPIO_PinNum,GPIO_PinVal_t GPIO_PinVal);

/********************************************************************
 * @fn GPIO_u8PinInit.
 * @berief	the function initializes the GPIO pin according to the input parameters.
 * @Parameters	[in]  PinConfig : Initialize values of the pin.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8PinInit (const GPIO_PinConfig_t* PinConfig);

/********************************************************************
 * @fn GPIO_u8SetPinValue.
 * @berief	the function outputs a certain value on an autput pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @Parameters	[in]  PinVal : The Output value , get options @PinVal_t enum
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8SetPinValue (Port_t Port, Pin_t GPIO_PinNum,GPIO_PinVal_t GPIO_PinVal);//Finished

/*
 * @fn GPIO_u8TogglePinValue.
 * @berief	the function toggle outputs value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8TogglePinValue (Port_t Port, Pin_t PinNum);//Finished

/*
 * @fn GPIO_u8ReadPinValue.
 * @berief	the function Read output value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8ReadPinValue (Port_t Port, Pin_t PinNum,GPIO_PinVal_t* GPIO_PinVal);//Finished

#endif
