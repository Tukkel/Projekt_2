#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

class Log
{
    public:
        Log(uint8_t numberRooms, uint8_t numberPeople, double** roomHistory);
    private:
        int** rooms_;
        double** roomChances_;
        double** roomHistory_;
        char** roomNames_;
        char** peopleNames_;
        uint32_t* addresses_[256] = {0};
};