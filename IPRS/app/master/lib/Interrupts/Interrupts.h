#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

class Interrupts
{
public:
    Interrupts();
    void setTime(size_t timeMin);
    size_t getTime();
    void setSek(size_t time4Sek);
    uint8_t getSek();
    void setNextChar(uint8_t nextChar);
    void setTermChar(uint8_t termChar);
    void setStringReady(bool ready);
    uint8_t getNextChar();
    uint8_t getTermChar();
    bool stringReady();
    void stringRead();
    char string[256] = {' '};
private:
    size_t timeMin_;
    uint8_t time4Sek_;
    uint8_t nextChar_;
    uint8_t termChar_;
    bool stringReady_;
};