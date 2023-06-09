#pragma once

#include <avr/io.h>
#include <stdlib.h>
//#define F_CPU 16000000
#include <util/delay.h>

/*
    Klassen bruges til X10 kommunikation mellem master og slave.
    Klassen kan både læse og skrive data.
    Klassen bruger port A til at kommunikere med X10 enhederne.

    Klassen skal bruge parametrene:
    clock_pin: hvilket pin ben som x10 clocken er på
    X10_read: hvilket pin ben som x10 read er på
    X10_write: hvilket pin ben som x10 write er på
    address: en pointer til en bool array med længden 8, som er adressen på enheden, denne er 0 er det en master
    unit: en char som er enten 'm' eller 's', som fortæller om det er en master eller slave
*/
class X10
{
    public:
        X10();
        ~X10();
        X10(volatile uint8_t clock_pin, volatile uint8_t X10_read, volatile uint8_t X10_write, bool* address, char unit);
        bool readHalfBit() const;
        bool* readData();
        void writeBit(uint8_t bit) const;
        void writeData(bool* data, bool* address) const;
    private:
        volatile uint8_t clock_pin_;
        volatile uint8_t X10_read_;
        volatile uint8_t X10_write_;
        bool address_[8] = {false};
        char unit_;
        bool data_[100] = {false};
};