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
	uint8_t address1[8] = {0, 0, 0, 0, 0, 0, 0, 1};
	uint8_t address2[8] = {0, 0, 0, 0, 0, 0, 1, 0};
	X10 x10(1, 2, 4, address1,  'm');
	uint8_t data[1] = {1};
	uint8_t dataRead = 0;
	DDRB = 0xFF;
	bool recived = false;
	while(true)
	{
		while(recived == false)
		{
			recived = x10.writeData(data, sizeof(data)/sizeof(data[0]), address2, sizeof(address2)/sizeof(address2[0]));
		}
		while(dataRead == 0)
		{
			
			recived = false;
			x10.readData();
			dataRead = x10.getValue();
		}
		while(recived == false)
		{
			recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), address1, sizeof(address1)/sizeof(address1[0]));
		}
		recived = false;
		dataRead = 0;
		_delay_ms(5000);
		while(recived == false)
		{
			recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), address1, sizeof(address1)/sizeof(address1[0]));
		}
		recived = false;
	}
	
}