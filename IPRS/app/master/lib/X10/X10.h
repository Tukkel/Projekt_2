#pragma once

#include <avr/io.h>
#include <stdlib.h>

class X10
{
    public:
        X10(volatile uint8_t clock_pin, volatile uint8_t X10_read, volatile uint8_t X10_write, bool* address, char unit);
        bool readBit() const;
        bool* readData();
        void writeBit(bool bit);
        void writeData(bool* data, bool* address = {false, false, false, false, false, false, flase, flase});
        
    private:
        volatile uint8_t clock_pin_;
        volatile uint8_t X10_read_;
        volatile uint8_t X10_write_;
        bool* address_;

};