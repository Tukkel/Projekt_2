#include <stddef.h>
#include <avr/io.h>
#include <math.h>

uint8_t getAddress(char* string)
{
    size_t i = 0;
    uint8_t seperators = 0;
    uint8_t address = 0;
    uint8_t power = 0;
    while(string[i] != '\0')
    {
        if(string[i] == ',')
        {
            seperators += 1;
        }
        if(seperators == 2)
        {
            --i;
            while(string[i] != ',')
            {
                address += (string[i]-48)*pow(10, power);
                ++power;
                --i;
            }
            return address;
        }
        ++i;
    }
}

uint32_t getAddressType(char* string)
{
    size_t i = 0;
    uint32_t addressType = 0;
    uint8_t power = 0;
    while(string[i] != '\0')
    {
        ++i;
    }
    --i;
    while(string[i] != ',')
    {
        addressType += (string[i]-48)*pow(10, power);
        ++power;
        --i;
    }
    return addressType;
}

uint8_t getRoom(char* string)
{
    size_t i = 0;
    uint8_t seperators = 0;
    uint8_t room = 0;
    uint8_t power = 0;
    while(string[i] != '\0')
    {
        if(string[i] == ',')
        {
            seperators += 1;
        }
        if(seperators == 2)
        {
            --i;
            while(string[i] != ',')
            {
                room += (string[i]-48)*pow(10, power);
                ++power;
                --i;
            }
            return room-1;
        }
        ++i;
    }
}

void getConnections(char* string, bool* connections)
{
    size_t i = 0;
    uint8_t seperators = 0;
    uint8_t seperatorsDone = 2;
    uint8_t roomNumber = 0;
    uint8_t power = 0;
    while(string[i] != '\0')
    {
        if(string[i] == ',')
        {
            seperators += 1;
        }
        if(seperators > seperatorsDone)
        {
            --i;
            while(string[i] != ',')
            {
                roomNumber += (string[i]-48)*pow(10, power);
                ++power;
                --i;
            }
            --seperators;
            connections[roomNumber-1] = true;
        }
        ++i;
    }
    --i;
    while(string[i] != ',')
    {
        roomNumber += (string[i]-48)*pow(10, power);
        ++power;
        --i;
    }
    connections[roomNumber-1] = true;
}

uint8_t getRooms(char* string)
{
    size_t i = 0;
    uint8_t seperators = 0;
    uint8_t rooms = 0;
    uint8_t power = 0;
    while(string[i] != '\0')
    {
        if(string[i] == ',')
        {
            seperators += 1;
        }
        if(seperators == 2)
        {
            --i;
            while(string[i] != ',')
            {
                rooms += (string[i]-48)*pow(10, power);
                ++power;
                --i;
            }
            return rooms;
        }
        ++i;
    }
}

size_t getUsers(char* string)
{
    size_t i = 0;
    size_t users = 0;
    uint8_t power = 0;
    while(string[i] != '\0')
    {
        ++i;
    }
    --i;
    while(string[i] != ',')
    {
        users += (string[i]-48)*pow(10, power);
        ++power;
        --i;
    }
    return users;
}