#include "X10.h"

X10::X10(volatile uint8_t clock_pin, volatile uint8_t X10_read, volatile uint8_t X10_write, bool* address, char unit)
{
    clock_pin_ = clock_pin;
    X10_read_ = X10_read;
    X10_write_ = X10_write;

    if (unit == 'm' || unit == 'M')
    {
        int address_[8] = {0};
    }
    else
    {
        if (sizeof(address) == 8)
        {
            address_ = address;
        }
        else
        {
            int address_[8] = {0};
            if (sizeof(address) < 8)
            {
                for(size_t i=0;i<sizeof(address);i++)
                {
                    address_[i] = address[i];
                }
            }
            else
            {
                for(size_t i=0; i < 8;i++)
                {
                    address_[i] = address[i];
                }
            }
        }
    }
    
}