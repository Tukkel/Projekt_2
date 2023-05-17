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
	UART uart(9600, 8);
	uint8_t address[8] = {0, 0, 0, 0, 0, 0, 0, 1};
	X10 x10(1, 2, 4, address,  'm');
	uint8_t data[6] = {0,0,0,0, 0, 1};
	DDRB = 0xFF;
	bool recived;

	while(1)
	{
		recived = x10.writeData(data, sizeof(data)/sizeof(data[0]), address, sizeof(address)/sizeof(address[0]));
	}
}