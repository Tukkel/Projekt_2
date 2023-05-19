#include "Interrupts.h"

Interrupts I;

ISR(TIMER5_OVF_vect)
{
    if(I.getSek() >= 14)
    {
        I.setSek(I.getSek()-14);
        I.setTime(I.getTime()+1);
    }
    else
    {
        I.setSek(I.getSek()+1);
    }
}

ISR(USART0_RX_vect)
{
    I.string[I.getNextChar()] = UDR0;

    if(I.string[I.getNextChar()] == '\0')
    {
        I.setTermChar(I.getNextChar()+1);
        I.setStringReady(true);
    }

    I.setNextChar(I.getNextChar()+1);
}

ISR(USART1_RX_vect)
{
    char uart = UDR1;
    if(uart == 0)
    {
        I.setRoomToSend(0);
        I.setRoomReady(true);
    }
    else
    {
        for(size_t i = 0; i<8; ++i)
        {
            if(uart & 1<<i)
            {
                I.setRoomToSend(i+1);
                I.setRoomReady(true);
            }
        }
    }
}

Interrupts::Interrupts()
{
    timeMin_ = 0;
    time4Sek_ = 0;

    TCCR5A = 0b00000001;
    TCCR5B = 0b00010101;
    OCR5A = (4*15625) - 1;
    TIMSK5 = 0b00000001;
    sei();

    nextChar_ = 0;
    termChar_ = 0;
    roomToSend_ = 0;
    stringReady_ = false;
    roomReady_ = false;
    string[255] = '\0';
}

void Interrupts::setTime(size_t timeMin)
{
    timeMin_ = timeMin;
}

size_t Interrupts::getTime()
{
    return timeMin_;
}

void Interrupts::setSek(size_t time4Sek)
{
    time4Sek_ = time4Sek;
}

uint8_t Interrupts::getSek()
{
    return time4Sek_;
}

void Interrupts::setNextChar(uint8_t nextChar)
{
    nextChar_ = nextChar;
}

void Interrupts::setTermChar(uint8_t termChar)
{
    termChar_ = termChar;
}

void Interrupts::setStringReady(bool ready)
{
    stringReady_ = ready;
}

void Interrupts::setRoomToSend(uint8_t room)
{
    roomToSend_ = room;
}

void Interrupts::setRoomReady(bool ready)
{
    roomReady_ = ready;
}

uint8_t Interrupts::getNextChar()
{
    return nextChar_;
}

uint8_t Interrupts::getTermChar()
{
    return termChar_;
}

uint8_t Interrupts::getRoomToSend()
{
    return roomToSend_;
}

bool Interrupts::stringReady()
{
    return stringReady_;
}

bool Interrupts::roomReady()
{
    return roomReady_;
}

void Interrupts::stringRead()
{
    cli();

    for(size_t i = termChar_; i<256; ++i)
    {
        string[i-termChar_] = string[i];
    }
    for(size_t i = 255-termChar_; i<255; ++i)
    {
        string[i] = ' ';
    }

    string[255] = '\0';
    
    stringReady_ = false;

    nextChar_ -= termChar_;

    sei();
}