#include "X10.h"

X10::X10(volatile uint8_t clock_pin, volatile uint8_t X10_read, volatile uint8_t X10_write, uint8_t* address, size_t addressSize, char unit)
{
    clock_pin_ = clock_pin;
    X10_read_ = X10_read;
    X10_write_ = X10_write;

    DDRL &= ~clock_pin_;    //Set pin asignments
    DDRL &= ~X10_read_;
    DDRL &= ~X10_write_;

    if (unit == 'm' || unit == 'M') //If master make address empty
    {
        unit_ = 'm';
    }
    else                            //If not master then make a slave
    {
        unit_ = 's';
        if (addressSize < 8)
        {
            for(size_t i=8-addressSize;i<8;i++)
            {
                address_[i] = address[i+addressSize-8];
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

bool X10::readHalfBit() const
{
    bool bit = false;
    while (true) // While reading
    {
        if (PINL & clock_pin_)
        {
            while (PINL & clock_pin_)   //While clock pin is high set bit true if true is send on X10
            {
                if (PINL & X10_read_)
                {
                    bit = true;
                }
            }
            return bit;                 //When clock pin goes low return the bit
        }
    }
}

void X10::readData()
{
    size_t i;
    size_t pair;
    bool ack;
    while(true)
    {
        i = 0;
        pair = 0;
        ack = true;
        while (true)    //Find start bit
        {
            data_[0] = data_[1];
            data_[1] = data_[2];
            data_[2] = data_[3];
            data_[3] = readHalfBit();
            
            if(i > 2 && data_[0] == true && data_[1] == true && data_[2] == true && data_[3] == false)
            {
                break;
            }

            ++i;
        }
        i = 4;
        while (true)
        { // While reading

            data_[i] = readHalfBit(); // Reads the half bit

            if(i%2)             //If there is a pair of half bits convert to full bit
            {
                if(data_[i-1] == true && data_[i] == false)
                {
                    ++pair;     //If it is a 1 increment pair
                }
            }

            if (i > 6) // If the data contains stop bits then break
            {
                if (data_[i-3] == false && data_[i-2] == false && data_[i-1] == false && data_[i] == true)
                {
                    break;
                }
            }

            ++i;
        }

        if(unit_ == 'm')
        {
            if(pair%2)
            {
                ack = false;
            }
            else
            {
                ack = true;
            }
        }
        else
        {
            for(size_t i = 2; i<10; ++i)
            {
                //PORTB |= data_[i*2]<<(9-i);
                if(address_[i-2] != data_[2*i])
                {
                    ack = false;
                }
            }
            if(pair%2)
            {
                ack = false;
            }
        }
        if(unit_ == 'm' || ack)
        {
            while(true) //Check for pairity
            {
                if (PINL & clock_pin_)
                {
                    DDRL |= X10_write_;
                    if(ack)  // if sending ack
                    {
                        writeBit(1);
                        DDRL &= ~X10_write_;
                        return;
                    }
                    else        //Else don't send ack
                    {
                        writeBit(0);
                        DDRL &= ~X10_write_;
                        break;
                    }
                }
            }
        }
    }
}

void X10::writeBit(uint8_t bit) const
{
    while (true)
    {
        if (PINL & clock_pin_)      //Wait for pulse on clock_pin
        {
            if (bit == 1)            //If sending a 1 write 10 half bits
            {
                PORTL |= X10_write_;
                while(PINL & clock_pin_)
                {
                }
                PORTL &= ~X10_write_;
                while((PINL & clock_pin_) == 0)
                {
                }
                while(PINL & clock_pin_)
                {
                }
                return;
            }
            else if (bit == 2)            //If sending a 2 write 00 half bits
            {
                PORTL &= ~X10_write_;
                while(PINL & clock_pin_)
                {
                }
                while((PINL & clock_pin_) == 0)
                {
                }
                while(PINL & clock_pin_)
                {
                }
                return;
            }
            else if (bit == 3)            //If sending a 3 write 11 half bits
            {
                PORTL |= X10_write_;
                while(PINL & clock_pin_)
                {
                }
                PORTL &= ~X10_write_;
                while((PINL & clock_pin_) == 0)
                {
                }
                PORTL |= X10_write_;
                while(PINL & clock_pin_)
                {
                }
                PORTL &= ~X10_write_;
                return;
            }
            else                //Else send a 0 with 01 half bits
            {
                PORTL &= ~X10_write_;
                while(PINL & clock_pin_)
                {
                }
                while((PINL & clock_pin_) == 0)
                {
                }
                PORTL |= X10_write_;
                while(PINL & clock_pin_)
                {
                }
                PORTL &= ~X10_write_;
                return;
            }
        }
    }
}

bool X10::writeData(uint8_t* data, size_t dataSize, uint8_t* address, size_t addressSize) const
{
    bool read[6] = {false};
    uint8_t send[8+dataSize+1] = {0};
    size_t pair = 0;

    if (unit_ == 'm')       //If it is master sending the inputted address is used but needs to be checked for correct size
    {
        if(addressSize < 8)
        {
            for(size_t i = 8-addressSize; i<8; ++i)
            {
                send[i] = address[i+addressSize-8];
            }
        }
        else
        {
            for(size_t i = 0; i<8; ++i)
            {
                send[i] = address[i];
            }
        }
    }
    else                    //If it is not a master sending it is a slave that needs to send its own address
    {
        for(size_t i = 0; i<8; ++i)
        {
            send[i] = address_[i];
        }
    }

    for(size_t i = 8; i<8+dataSize; ++i)  //The data is inserted into the array to send
    {
        send[i] = data[i-8];
    }

    for(size_t i = 0; i<8+dataSize; ++i)    //Pairity bit is set to 1 of there is an uneven number of 1's
    {
        if(send[i])
        {
            pair++;
        }
    }
    if(pair%2)
    {
        send[8+dataSize] = 1;
    }

    size_t i = 0;
    while(true)     //Check that nothing is beeing send on X10 before starting
    {
        read[0] = read[1];
        read[1] = read[2];
        read[2] = read[3];
        read[3] = read[4];
        read[4] = read[5];
        read[5] = readHalfBit();
        
        if(i > 2 && read[2] == false && read[3] == false && read[4] == false && read[5] == false)
        {
            break;
        }

        if(i > 4 && read[0] == false && read[1] == false && read[2] == false && read[3] == true && read[4] == true && read[5] == false)
        {
            break;
        }

        ++i;
    }
    
    //First send start bit
    DDRL |= X10_write_;
    writeBit(3);
    writeBit(1);

    for(size_t j = 0; j < sizeof(send); j++)    //Address and data with pairity bit is send here
    {
        writeBit(send[j]);
    }

    writeBit(2);
    writeBit(0);
    DDRL &= ~X10_write_;

    if(readHalfBit())       //Check for ack. If no ack is recived try again
    {
        if(readHalfBit() == 0)
        {
            return true;
        }
    }

    return false;
}

uint8_t X10::getAddress() const
{
    uint8_t address = 0;
    for(size_t i = 2; i<10; ++i)
    {
        address += data_[2*i]<<(i-2);
    }
    return address;
}

int X10::getValue() const
{
    size_t value = 0;
    size_t count = 0;
    for(size_t i = 10; i<50; ++i)
    {
        if((data_[i*2] == false) && (data_[i*2+1] == false))
        {
            break;
        }
        ++count;
    }
    --count;
    for(size_t i = 10; i<(10+count); ++i)
    {
        value += data_[2*i]<<(count+9-i);
    }
    return value;
}