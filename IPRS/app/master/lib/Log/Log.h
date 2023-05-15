#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

class Log
{
    public:
        Log(uint8_t numberRooms, uint8_t numberPeople, double** roomHistory);
        void setRoomConnection(uint8_t roomNumber, bool* connections);
        void setRoomName(uint8_t roomNumber, char* roomName);
        void setPersonName(size_t personNumber, char* personName);
        void setAddress(uint8_t address, uint32_t addressType);
        void logActivity(uint8_t roomNumber);
        void logMovement(uint8_t roomNumber1, uint8_t roomNumber2);
    private:
        bool** rooms_;
        double** roomChances_;
        double** roomHistory_;
        bool** roomConnections_;
        char** roomNames_;
        char** peopleNames_;
        uint32_t* addresses_[256] = {300};
};