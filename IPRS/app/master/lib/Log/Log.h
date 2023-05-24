#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU 16000000
#include <util/delay.h>

class Log
{
    public:
        Log(uint8_t numberRooms, size_t numberPeople);
        void setRoomConnection(uint8_t roomNumber, bool* connections);
        void setRoomName(uint8_t roomNumber, char* roomName);
        void setPersonName(size_t personNumber, char* personName);
        void setAddress(uint8_t address, uint32_t addressType);
        void setPersonHistory(size_t personNumber, double* personHistory);
        void logActivity(uint8_t roomNumber);
        void logMovement(uint8_t roomNumber1, uint8_t roomNumber2);
        void logID(uint8_t roomNumber, size_t personNumber);
        void setTime(size_t timeMin);
        size_t offset(size_t logNumber, size_t roomNumber, size_t personNumber);
        const uint8_t numberRooms_;
        const size_t numberPeople_;
        bool** rooms_;
        char** roomNames_;
        char** peopleNames_;
        double* log_;
        size_t* logTime_;
        size_t nextEntry_;
        uint32_t addresses_[256] = {300};
    private:
        void setLog();
        double** roomChances_;
        double** peopleHistory_;
        bool** roomConnections_;
        size_t timeMin_;
};