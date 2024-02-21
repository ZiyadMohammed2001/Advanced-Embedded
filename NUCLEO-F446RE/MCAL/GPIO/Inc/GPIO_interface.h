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
	PORTH
}GPIO_Port_t;

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
}GPIO_Pin_t;


typedef enum
{
	GPIO_INPUT = 0,
	GPIO_OUTPUT,
	GPIO_ALTERNATE_FUNCTION,
	GPIO_ANALOG
}GPIO_Mode_t;

typedef enum
{
	GPIO_LOW=0,
	GPIO_MEDIUM,
	GPIO_FAST,
	GPIO_HIGH
}GPIO_OutputSpeed_t;

typedef enum
{
	GPIO_PUSH_PULL=0,
	GPIO_OPEN_DRAIN
}GPIO_OutputType_t;

typedef enum
{
	GPIO_NOPULL=0,
	GPIO_PULLUP,
	GPIO_PULLDOWN
}GPIO_PullUpDown_t;
/*
 * @PinVal_t enum
 */
typedef enum
{
	GPIO_PIN_LOW=0,
	GPIO_PIN_HIGH
}GPIO_PinVal_t;

typedef enum
{
	GPIO_AF0=0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,
	GPIO_AF8,
	GPIO_AF9,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15
}GPIO_AltFunc_t;

typedef struct
{
	GPIO_Port_t Port;
	GPIO_Pin_t PinNum;
	GPIO_Mode_t Mode;
	GPIO_OutputSpeed_t GPIO_Speed;
	GPIO_OutputType_t GPIO_OutputType;
	GPIO_PullUpDown_t GPIO_PullType;
	GPIO_AltFunc_t GPIO_AltFunc;
}GPIO_PinConfig_t;

/********************************************************************
 * @fn GPIO_u8PinInit.
 * @berief	the function initializes the GPIO pin according to the input parameters.
 * @Parameters	[in]  PinConfig : Initialize values of the pin.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8PinInit (const GPIO_PinConfig_t* GPIO_PinConfig);

/********************************************************************
 * @fn GPIO_u8SetPinValue.
 * @berief	the function outputs a certain value on an autput pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @Parameters	[in]  PinVal : The Output value , get options @PinVal_t enum
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8SetPinValue (GPIO_Port_t GPIO_Port, GPIO_Pin_t GPIO_PinNum,GPIO_PinVal_t GPIO_PinVal);

/*
 * @fn GPIO_u8TogglePinValue.
 * @berief	the function toggle outputs value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8TogglePinValue (GPIO_Port_t GPIO_Port, GPIO_Pin_t GPIO_PinNum);

/*
 * @fn GPIO_u8ReadPinValue.
 * @berief	the function Read output value on an output pin.
 * @Parameters	[in]  Port : Port number, Get options @Port_t enum.
 * @Parameters	[in]  PinNum : Pin number, Get options @Pin_t enum.
 * @retval ErrorStatus.
 ********************************************************************/

uint8_t GPIO_u8ReadPinValue (GPIO_Port_t GPIO_Port, GPIO_Pin_t GPIO_PinNum,GPIO_PinVal_t* GPIO_PinVal);

#endif
