/*
 * main.c
 *
 *  Created on: Nov 26, 2022
 *      Author: MSAEED99
 */


// Libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_interface.h"
#include "USART_interface.h"


// Send data from PC and make the action on MCU
/* ====================================
 * UART protocol communication with PC:
 * ====================================
 * Setting UART communication with computer via USB-to-TTL Module, that converts the regular USB port to UART protocol.
 * Application:
	 - Click '1' on PC keypad -> turn on  LED, MCU UART send 'LED ON'  to PC in putty interface.
	 - Click '2' on PC keypad -> turn off LED, MCU UART send 'LED OFF' to PC in putty interface.
 * Putty: Interfacing between PC and USB-to-TTL.
 */
void main(void)
{
	u8 local_u8Data;

	/* =======================================
	 * Initialize the direction of USART pins:
	 * =======================================
	 * RX (PinD0) as input	: connect to TX in USB-to-TTL Module.
	 * TX (PinD1) as output	: connect to RX in USB-to-TTL Module.
	 */
	DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_INPUT);
	DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_OUTPUT);

	// Set LED pin as output
	DIO_voidSetPinDirection(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_OUTPUT);

	// Initialize USART
	USART_voidInit();

	while(1)
	{
		// Receive the data from TTL (receive from PC)
		local_u8Data = USART_u8ReceiveData();

		if(local_u8Data == '1')
		{
			// Turn on LED
			DIO_voidSetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);

			// Send Data to putty interface
			USART_voidSendDataString("LED ON; ");
		}
		else if(local_u8Data == '2')
		{
			// Turn off LED
			DIO_voidSetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);

			// Send Data to putty interface
			USART_voidSendDataString("LED OFF; ");
		}
		else
		{
			// Send Data to putty interface
			USART_voidSendDataString("Invalid input; ");
		}
	}
}


