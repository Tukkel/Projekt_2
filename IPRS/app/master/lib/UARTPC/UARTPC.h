#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <math.h>

class UARTPC
{
    public:
        UARTPC(unsigned long BaudRate, unsigned char DataBit);
        unsigned char CharReady();
        char ReadChar();
        void SendChar(char Tegn);
        void SendString(char* Streng);
        void SendInteger(int Tal);
    private:
};