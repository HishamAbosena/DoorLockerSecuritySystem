 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: myuart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Youssef Elebiary
 *
 *******************************************************************************/

#ifndef MYUART_H_
#define MYUART_H_


#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                           User Defined Data Types                           *
 *******************************************************************************/
typedef enum{
	five_bits,six_bits,seven_bits,eight_bits,nine_bits=7
}DataSize;

typedef enum{
	no_parity,even_parity=2,odd_parity
}parityBit;

typedef enum{
	one_bit,two_bits
}numOfStopBits;

typedef struct{

	uint32 baud_rate;
	DataSize num_of_data_bits;
	parityBit parity;
	numOfStopBits stopBits;

}UART_config;
/*******************************************************************************
 *                           Functions Prototypes                              *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_config *ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* MYUART_H_ */
