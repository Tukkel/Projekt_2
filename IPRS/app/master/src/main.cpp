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
	
	char DEstring[40];

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

	_delay_ms(500);
	
	
	log.setTime(I.getTime());
	_delay_ms(200);
	log.logID(1, 0);
	_delay_ms(200);
	log.logID(0, 2);
	

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
		
		recived = false;
		recived = x10.writeData(on, sizeof(on)/sizeof(on[0]), address3, sizeof(addresstwo)/sizeof(addresstwo[0]));
		
		PORTB = 4;

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

				if(room == 1)
				{
					if(full)
					{
						uartDe.SendString("~~ Rum 1: 1 person1!");
					}
					else
					{
						uartDe.SendString("~~ Rum 1: 0!");
					}
				}
				else
				{
					uartDe.SendString("~~ Rum ");
					uartDe.SendInteger(room);
					uartDe.SendString(": 0!");
				}
				/*
				size_t start = 3;
				DEstring[0] = '~';
				DEstring[1] = '~';
				DEstring[2] = ' ';

				for(size_t i=start; i<40; ++i)
				{
					if(log.roomNames_[room][i-start] != '\0')
					{
						DEstring[i] = log.roomNames_[room][i-start];
					}
					else
					{
						DEstring[i] = ' ';
						start = i+1;
						break;
					}
				}

				size_t people = 0;
				for(size_t j = 0; j<log.numberPeople_; ++j)
				{
					if(log.rooms_[room][j])
					{
						++people;
					}
				}
				if(people>9)
				{
					DEstring[start] = (people/10) + 48;
					DEstring[start+1] = (people%10) + 48;
					DEstring[start+2] = ' ';
					start += 3;
				}
				else
				{
					DEstring[start] = people + 48;
					DEstring[start] = ' ';
					start += 2;
				}

				bool nameFinished = false;
				for(size_t j = 0; j<log.numberPeople_; ++j)
				{
					if(log.rooms_[room][j])
					{
						for(size_t i=start; i<40; ++i)
						{
							if(log.peopleNames_[j][i-start] != '\0')
							{
								DEstring[i] = log.peopleNames_[j][i-start];
							}
							else
							{
								start = i;
								nameFinished = true;
								break;
							}
						}
					}
					if(nameFinished)
					{
						break;
					}
				}
				DEstring[start] = '!';
				DEstring[start+1] = '\0';
				uartDe.SendString(DEstring);
				*/
			}
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
						for(size_t k = 0; k<users; ++k)
						{
							for(size_t l = 0; l<rooms; ++l)
							{
								uartPc.SendInteger((int)(log.roomChances_[l][k]*1000));
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
									intToSend = log.log_[log.offset(j,l,k)]*1000;
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
						bool connections[log.numberRooms_] = {false};
						bool* boolPtr = &connections[0];
						uint8_t room = getRoom(I.string);
						getConnections(I.string, boolPtr);
						log.setRoomConnection(room, connections);
						PORTB = room;
						_delay_ms(1000);
					}
					else if(I.string[i-1] == 'D')
					{
						uartPc.SendString("Callibrated\n");
					}
				}
				++i;
			}
			I.stringRead();
		}
	}
}