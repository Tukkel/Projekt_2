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
	X10 x10(1, 2, 4, address, sizeof(address)/sizeof(address[0]), 'm');
	uint8_t on[1] = {1};
	uint8_t off[1] = {0};
	uint8_t dataRead = 0;
	DDRB = 0xFF;
	bool recived = true;

	uint8_t rooms;
	size_t users;

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

	Log log(rooms, users);
	
	log.logID(1, 0);
	log.logID(0, 1);

	while(true)
	{
		/*
		recived = false;
		recived = x10.writeData(on, sizeof(on)/sizeof(on[0]), addresstwo, sizeof(addresstwo)/sizeof(addresstwo[0]));
		
		if(recived == true)
		{
			x10.readData();
			dataRead = x10.getValue();
			PORTB = dataRead+1;
			recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), address, sizeof(address)/sizeof(address[0]));
		}
		*/
		//recived = false;
		

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
				uartDe.SendString("~~ roomName count Name1!");
				/*
				size_t i = 0;
				size_t people = 0;
				uint8_t room = I.getRoomToSend();
				uartDe.SendString("~~ ");
				PORTB = 4;
				while(log.roomNames_[room][i] != '\0')
				{
					uartDe.SendChar(log.roomNames_[room][i]);
					++i;
				}
				PORTB = 8;
				uartDe.SendChar(' ');
				for(size_t j = 0; j<log.numberPeople_; ++j)
				{
					if(log.rooms_[room][j])
					{
						++people;
					}
				}
				uartDe.SendInteger(people);
				uartDe.SendChar(' ');
				i = 0;
				PORTB = 16;	
				for(size_t j = 0; j<log.numberPeople_; ++j)
				{
					if(log.rooms_[room][j])
					{
						while(log.peopleNames_[j][i] != '\0')
						{
							uartDe.SendChar(log.peopleNames_[j][i]);
							++i;
						}
					}
				}
				PORTB = 32;
				uartDe.SendChar('!');
				*/
			}
			//I.roomReady_ = false;
			I.setRoomReady(false);
		}

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
						/*
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
						*/
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