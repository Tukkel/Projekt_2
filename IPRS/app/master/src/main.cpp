#include <avr/io.h>
#include "X10.h"
#include "UARTPC.h"
#include "UARTDE.h"
#include "Log.h"

#include "Interrupts.h"
extern Interrupts I;

#include "Functions.cpp"

int main()
{
	UARTPC uartPc(9600, 8);
	UARTDE uartDe(9600, 8);
	uint8_t address[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t addresstwo[8] = {0, 0, 0, 0, 0, 0, 1, 0};
	X10 x10(1, 2, 4, address, sizeof(address)/sizeof(address[0]), 'm');
	uint8_t on[1] = {1};
	uint8_t off[1] = {0};
	uint8_t dataRead = 0;
	DDRB = 0xFF;
	bool recived = false;

	uint8_t rooms;
	size_t users;

	while(true)
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
						PORTB = users;
						I.stringRead();
						break;
						break;
					}
					else
					{
						I.stringRead();
						break;
					}
				}
				++i;
			}
		}
	}

	Log log(rooms, users);

	while(true)
	{
		/*
		recived = x10.writeData(on, sizeof(on)/sizeof(on[0]), addresstwo, sizeof(addresstwo)/sizeof(addresstwo[0]));
		if(recived)
		{
			x10.readData();
			dataRead = x10.getValue();
			PORTB = dataRead+1;
			address[7] = 1;
			recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), address, sizeof(address)/sizeof(address[0]));
		}
		recived = false;
		dataRead = 0;
		_delay_ms(1000);
		recived = x10.writeData(&dataRead, sizeof(&dataRead)/sizeof(&dataRead), address, sizeof(address)/sizeof(address[0]));
		recived = false;
		_delay_ms(1000);
		*/
		log.logID(1, 0);
		log.logID(0, 1);

		//PORTB = I.stringReady();
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
						I.stringRead();
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
						I.stringRead();
					}
					else if(I.string[i-1] == 'C')
					{
						bool connections[rooms] = {false};
						bool* boolPtr = &connections[0];
						uint8_t room = getRoom(I.string);
						getConnections(I.string, boolPtr);
						log.setRoomConnection(room, connections);
						PORTB = room;
						I.stringRead();
					}
					else if(I.string[i-1] == 'D')
					{
						char string[] = "Callibrated\n";
						uartPc.SendString(string);
						I.stringRead();
					}
				}
				++i;
			}
		}
	}
	
}