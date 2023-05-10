#pragma once

#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>

class X10
{
    public:
        X10(volatile uint8_t clock_pin, volatile uint8_t X10_read, volatile uint8_t X10_write, bool* address, char unit = 's');
        void readData();
        void writeData(bool* data, bool* address = 0) const;
        uint8_t readAddress() const;
        int readValue() const;
    private:
        bool readHalfBit() const;
        void writeBit(uint8_t bit) const;
        volatile uint8_t clock_pin_;
        volatile uint8_t X10_read_;
        volatile uint8_t X10_write_;
        bool address_[8] = {false};
        char unit_;
        bool data_[100] = {false};
};