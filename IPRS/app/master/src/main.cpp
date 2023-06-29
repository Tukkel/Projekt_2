#include <avr/io.h>
#include "X10.h"
#include "UARTPC.h"
#include "UARTDE.h"
#include "Log.h"

#define F_CPU 16000000
#include <util/delay.h>

#include "Interrupts.h"
extern Interrupts I;

#include "Functions.cpp"

int main()
{
	UARTPC uartPc(9600, 8);
	UARTDE uartDe(9600, 8);
	uint8_t address[8] = {0, 0, 0, 0, 0, 0, 0, 1};
	uint8_t addresstwo[8] = {0, 0, 0, 0, 0, 0, 1, 0};
	uint8_t address3[8] = {0, 0, 0, 0, 0, 0, 1, 1};
	X10 x10(1, 2, 4, address, sizeof(address)/sizeof(address[0]), 'm');
	uint8_t on[1] = {1};
	uint8_t off[1] = {0};
	uint8_t dataRead = 0;

	DDRB = 0xFF;
	bool recived = true;
	bool full = false;
	
	char DEstring[40];// = "~~ Rum 1: 0 personer!\0";

	uint8_t rooms = 4;
	size_t users = 4;

	uartDe.SendString("~/");
	uartDe.SendChar(0b00000000);
	uartDe.SendChar('!');
	
	while(recived)
	{
		PORTB = I.stringReady();
		if(I.stringReady())
		{
			size_t i = 0;
			while(I.string[i] != '\0')
			{
				if(I.string[i] == ',')
				{
					if(I.string[i-1] == 'E')
					{
						rooms = getRooms(I.string);
						users = getUsers(I.string);
						I.stringRead();
						recived = false;
						break;
					}
					else
					{
						break;
					}
				}
				++i;
			}
			I.stringRead();
		}
	}

	PORTB = rooms;
	_delay_ms(1000);

	PORTB = users;
	_delay_ms(1000);

	uartDe.SendString("~/");
	uartDe.SendChar(0b10011001);
	uartDe.SendChar('!');
	
	//Log log(rooms, users);
	
	//log.logID(1, 0);
	//log.logID(0, 1);

	while(true)
	{
		PORTB = 6;

		recived = false;
		recived = x10.writeData(on, sizeof(on)/sizeof(on[0]), addresstwo, sizeof(addresstwo)/sizeof(addresstwo[0]));
		
		PORTB = 8;

		if(recived == true)
		{
			x10.readData();
			dataRead = x10.getValue();
			PORTB = dataRead+1;
			if(full)
			{
				recived = x10.writeData(off, sizeof(off)/sizeof(off[0]), address, sizeof(address)/sizeof(address[0]));
				full = false;
				uartDe.SendString("~/");
				uartDe.SendChar(0b00000000);
				uartDe.SendChar('!');
			}
			else
			{
				recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), address, sizeof(address)/sizeof(address[0]));
				full = true;
				uartDe.SendString("~/");
				uartDe.SendChar(0b00000001);
				uartDe.SendChar('!');
			}
		}

		/*
		PORTB = 3;
		_delay_ms(1000);
		
		recived = false;
		recived = x10.writeData(on, sizeof(on)/sizeof(on[0]), address3, sizeof(addresstwo)/sizeof(addresstwo[0]));
		
		PORTB = 4;
		_delay_ms(1000);

		if(recived == true)
		{
			x10.readData();
			dataRead = x10.getValue();
			PORTB = dataRead+1;
			recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), address, sizeof(address)/sizeof(address[0]));
			full = true;
		}
		*/

		PORTB = I.roomReady();
		_delay_ms(100);
		if(I.roomReady())
		{
			if(I.getRoomToSend() == 0)
			{
				uartDe.SendString("~~ !");
			}
			else
			{	
				size_t room = I.getRoomToSend();

				DEstring[7] = room+48;

				if(full)
				{
					DEstring[10] = '1';
				}
				else
				{
					DEstring[10] = '0';
				}
				
				uartDe.SendString(DEstring);
				
			}
			//I.roomReady_ = false;
			I.setRoomReady(false);
		}
		/*
		PORTB = I.stringReady();
		_delay_ms(100);
		if(I.stringReady())
		{
			size_t i = 0;
			while(I.string[i] != '\0')
			{
				if(I.string[i] == ',')
				{
					if(I.string[i-1] == 'A')
					{
						uint16_t intToSend = 0;
						for(size_t k = 0; k<users; ++k)
						{
							for(size_t l = 0; l<rooms; ++l)
							{
								intToSend = log.log_[log.offset(log.nextEntry_-1,l,k)]/0.001;
								uartPc.SendInteger(intToSend);
								uartPc.SendChar(' ');
							}
							uartPc.SendChar('\n');
						}
						
						for(size_t j = 0; j<log.nextEntry_; ++j)
						{
							for(size_t k = 0; k<users; ++k)
							{
								for(size_t l = 0; l<rooms; ++l)
								{
									intToSend = log.log_[log.offset(j,l,k)]/0.001;
									uartPc.SendInteger(intToSend);
									uartPc.SendChar(' ');
								}
								uartPc.SendChar('\n');
							}
							uartPc.SendChar('\n');
						}
						
					}
					else if(I.string[i-1] == 'B')
					{
						uint8_t address = getAddress(I.string);
						uint32_t addressType = getAddressType(I.string);
						log.setAddress(address, addressType);
						PORTB = address;
						_delay_ms(1000);
					}
					else if(I.string[i-1] == 'C')
					{
						bool connections[rooms] = {false};
						bool* boolPtr = &connections[0];
						uint8_t room = getRoom(I.string);
						getConnections(I.string, boolPtr);
						log.setRoomConnection(room, connections);
						PORTB = room;
						_delay_ms(1000);
					}
					else if(I.string[i-1] == 'D')
					{
						char string[] = "Callibrated\n";
						uartPc.SendString(string);
					}
				}
				++i;
			}
			I.stringRead();
			//I.stringReady_ = false;
			I.setRoomReady(false);
		}
		//I.stringReady_ = false;
		*/
	}
}

/*
#include <avr/io.h>
#include "X10.h"
#include "UARTPC.h"

int main()
{
	UARTPC uartPc(9600, 8);
	uint8_t hvad[8] = {0, 0, 0, 0, 0, 0, 0, 1};
	uint8_t addresstwo[8] = {0, 0, 0, 0, 0, 0, 1, 0};
	X10 x10(1, 2, 4, hvad, sizeof(hvad)/sizeof(hvad[0]), 'm');
	uint8_t data[1] = {1};
	uint8_t off[1] = {0};
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
			recived = x10.writeData(off, sizeof(off)/sizeof(off[0]), hvad, sizeof(addresstwo)/sizeof(addresstwo[0]));
			PORTB = 4;
		}
	}
}
*/