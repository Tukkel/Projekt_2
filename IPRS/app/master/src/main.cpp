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
	uint8_t hvad[8] = {0, 0, 0, 0, 0, 0, 0, 1};
	uint8_t addresstwo[8] = {0, 0, 0, 0, 0, 0, 1, 0};
	X10 x10(1, 2, 4, hvad, sizeof(hvad)/sizeof(hvad[0]), 'm');
	uint8_t data[1] = {1};
	uint8_t dataRead = 0;
	DDRB = 0xFF;
	bool recived = false;
	while(true)
	{
		while(dataRead == 0)
		{
			while(recived == false)
			{
				recived = x10.writeData(data, sizeof(data)/sizeof(data[0]), addresstwo, sizeof(addresstwo)/sizeof(addresstwo[0]));
				PORTB = 1;
			}
			recived = false;
			x10.readData();
			dataRead = x10.getValue();
			PORTB = dataRead+1;
		}
		while(recived == false)
		{
			recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), hvad, sizeof(addresstwo)/sizeof(addresstwo[0]));
			PORTB = 4;
		}
		recived = false;
		dataRead = 0;
		PORTB = 8;
		_delay_ms(3000);
		while(recived == false)
		{
			recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), hvad, sizeof(addresstwo)/sizeof(addresstwo[0]));
			PORTB = 16;
		}
		recived = false;
		_delay_ms(2000);
	}
	
}