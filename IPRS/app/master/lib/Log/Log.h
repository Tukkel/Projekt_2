#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

class Log
{
    public:
        Log(uint8_t numberRooms, uint8_t numberPeople, double** roomHistory);
        void setRoomName(int roomNumber, char* roomName);
        void setPersonName(int personNumber, char* personName);
        void setAddress(size_t address, uint32_t addressType);
    private:
        int** rooms_;
        double** roomChances_;
        double** roomHistory_;
        char** roomNames_;
        char** peopleNames_;
        uint32_t* addresses_[256] = {300};
};