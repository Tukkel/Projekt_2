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

	while(1)
	{
		for(size_t i=0; i<10; ++i)
		{
			UART.SendInteger(X10.readHalfBit());
		}
		UART.SendChar('\n');
	}
}