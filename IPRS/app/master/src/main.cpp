/********************************************
* MSYS, LAB 13. Part 3                      *
* ADC using multiplexing and regulating.    *
*                                           *
* Henning Hargaard 11/4 2019                *
*********************************************/
#include <avr/io.h>
#include "X10.h"
#include "uart.h"

int main()
{
	UART UART(9600, 8);
	bool address[8] = {false};
	X10 X10(1, 2, 4, address, 'm');
	bool data[4] = {1, 0, 0, 1};
	DDRB = 0xFF;

	while(1)
	{
		X10.readData();
		PORTB = X10.readAddress();
		UART.SendInteger(X10.readAddress());
		UART.SendChar(' ');
		UART.SendInteger(X10.readValue());
		UART.SendChar('\n');
	}
}