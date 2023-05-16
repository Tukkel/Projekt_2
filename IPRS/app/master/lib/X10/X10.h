#pragma once

#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>

class X10
{
    public:
        X10(volatile uint8_t clock_pin, volatile uint8_t X10_read, volatile uint8_t X10_write, uint8_t* address, size_t addressSize = 0, char unit = 's');
        void readData();
        void writeData(uint8_t* data, size_t dataSize, uint8_t* address = 0, size_t addressSize = 0) const;
        uint8_t getAddress() const;
        int getValue() const;
    private:
        bool readHalfBit() const;
        void writeBit(uint8_t bit) const;
        volatile uint8_t clock_pin_;
        volatile uint8_t X10_read_;
        volatile uint8_t X10_write_;
        uint8_t address_[8] = {0};
        char unit_;
        uint8_t data_[100] = {0};
};