#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <math.h>

class UARTDE
{
    public:
        UARTDE(unsigned long BaudRate, unsigned char DataBit);
        unsigned char CharReady();
        char ReadChar();
        void SendChar(char Tegn);
        void SendString(char* Streng);
        void SendInteger(int Tal);
    private:
};

/****************
 * "~~ " Begynder
 * "~/8bit\!" Rummed folk
 * Efter rum efterspørgelse "~~ Rumnavn som chars mellemrum antal som char mellemrum første navn som char !"
 * "~~ !" clear
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * ************************/
