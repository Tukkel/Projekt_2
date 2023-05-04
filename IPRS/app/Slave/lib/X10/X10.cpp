#include "X10.h"

X10::X10(volatile uint8_t clock_pin, volatile uint8_t X10_read, volatile uint8_t X10_write, bool* address, char unit = 's')
{
    clock_pin_ = clock_pin;
    X10_read_ = X10_read;
    X10_write_ = X10_write;

    DDRA &= ~clock_pin_;    //Set pin asignments
    DDRA &= ~X10_read_;
    DDRA |= X10_write_;

    if (unit == 'm' || unit == 'M') //If master make address empty
    {
        unit_ = 'm';
        bool address_[8] = {false};
    }
    else                            //If not master then make a slave
    {
        unit_ = 's';
        if (sizeof(address) == 8)   //If size matches make it the saved address
        {
            address_ = address;
        }
        else                        //Else try to fit the given address into expected size
        {
            bool address_[8] = {false};
            if (sizeof(address) < 8)
            {
                for(size_t i=8-sizeof(address);i<8;i++)
                {
                    address_[i] = address[i+sizeof(address)-8];
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

bool X10::readBit() const
{
    bool bit = false;
    while (true) // While reading
    {
        if (PINA & clock_pin_)
        {
            while (PINA & clock_pin_)   //While clock pin is high set bit true if true is send on X10
            {
                if (PINA & X10_read_)
                {
                    bit = true;
                }
            }
            return bit;                 //When clock pin goes low return the bit
        }
    }
}

bool* X10::readData()
{
    bool data[100];         //Setup array for half bits
    bool result_long[50];   //Setup array for full bits
    size_t i;
    size_t j;
    size_t pair;
    while(true)
    {
        i = 0;
        j = 0;
        pair = 0;
        while (true)    //Find start bit
        {
            data[0] = data[1];
            data[1] = data[2];
            data[2] = data[3];
            data[3] = readBit();
            
            if(i > 2 && data[0] == true && data[1] == true && data[2] == true && data[3] == false)
            {
                break;
            }

            i++;
        }
        i = 4;
        while (true)
        { // While reading

            data[i] = readBit(); // Reads the half bit

            if(i%2)             //If there is a pair of half bits convert to full bit
            {
                if(data[i-1] == true && data[i] == false)
                {
                    result_long[j] = true;
                    j++;
                    pair++;     //If it is a 1 increment pair
                }
                else if(data[i-1] == false && data[i] == true)
                {
                    result_long[j] = false;
                    j++;
                }
            }

            if (i > 6) // If the data contains stop bits then break
            {
                if (data[i-3] == false && data[i - 2] == false && data[i - 1] == false && data[i] == true)
                {
                    break;
                }
            }

            i++;
        }

        while(true) //Check for pairity
        {
            if (PINA & clock_pin_)
            {
                if(pair%2)  // If not even try to read again and don't send ack
                {
                    writeBit(false);
                    break;
                }
                else        //Else convert result to an array with correct size and return it
                {
                    writeBit(true);
                    bool result[j+1];
                    for (size_t k = 0; k < j; k++)
                    {
                        result[k] = result_long[k];
                    }
                    return result;
                }
            }
        }
        
    }
}

void X10::writeBit(bool bit)
{
    while (true)
    {
        if (PINA & clock_pin_) //Wait for pulse on clock_pin
        {
            if (bit)            //If sending a 1 write 10 half bits
            {
                PORTA |= X10_write_;
                while(PINA & clock_pin_)
                {
                }
                PORTA &= ~X10_write_;
                while((PINA & clock_pin_) == 0)
                {
                }
                while(PINA & clock_pin_)
                {
                }
                return;
            }
            else                //Else send a 0 with 01 half bits
            {
                PORTA &= ~X10_write_;
                while(PINA & clock_pin_)
                {
                }
                while((PINA & clock_pin_) == 0)
                {
                }
                PORTA |= X10_write_;
                while(PINA & clock_pin_)
                {
                }
                PORTA &= ~X10_write_;
                return;
            }
        }
    }
}

void X10::writeData(bool* data, bool* address = 0)
{
    bool read[6] = {false};
    bool send[8+sizeof(data)+1] = {false};
    size_t pair = 0;

    if (unit_ == 'm')       //If it is master sending the inputted address is used but needs to be checked for correct size
    {
        if(sizeof(address) < 8)
        {
            for(size_t i = 8-sizeof(address); i<8; i++)
            {
                send[i] = address[i+sizeof(address)-8];
            }
        }
        else
        {
            for(size_t i = 0; i<8; i++)
            {
                send[i] = address[i];
            }
        }
    }
    else                    //If it is not a master sending it is a slave that needs to send its own address
    {
        for(size_t i = 0; i<8; i++)
        {
            send[i] = address_[i];
        }
    }

    for(size_t i = 8; i<(8+sizeof(data)); i++)  //The data is inserted into the array to send
    {
        send[i] = data[i-8];
    }

    for(size_t i = 0; i<8+sizeof(data); i++)    //Pairity bit is set to 1 of there is an uneven number of 1's
    {
        if(send[i])
        {
            pair++;
        }
    }
    if(pair%2)
    {
        send[8+sizeof(data)] = true;
    }

    size_t i = 0;
    while(true)     //Check that nothing is beeing send on X10 before starting
    {
        read[0] = read[1];
        read[1] = read[2];
        read[2] = read[3];
        read[3] = read[4];
        read[4] = read[5];
        read[5] = readBit();

        
        if(i > 2 && read[2] == false && read[3] == false && read[4] == false && read[5] == false)
        {
            break;
        }

        if(i > 4 && read[0] == false && read[1] == false && read[2] == false && read[3] == true && read[4] == true && read[5] == false)
        {
            break;
        }

        i++;
    }
    
    while(true)
    {       //First send start bit
        while((PINA & clock_pin_) == 0)
        {
        }
        PORTA |= X10_write_;
        while(PINA & clock_pin_)
        {
        }
        PORTA &= ~X10_write_;
        while((PINA & clock_pin_) == 0)
        {
        }
        PORTA |= X10_write_;
        while(PINA & clock_pin_)
        {
        }
        PORTA &= ~X10_write_;

        writeBit(true);

        for(size_t j = 0; j < sizeof(send); j++)    //Address and data with pairity bit is send here
        {
            writeBit(send[j]);
        }

        PORTA &= ~X10_write_;
        while((PINA & clock_pin_) == 0)
        {
        }
        while(PINA & clock_pin_)                //Stopbit starts here
        {
        }
        while((PINA & clock_pin_) == 0)
        {
        }
        while(PINA & clock_pin_)
        {
        }
        
        writeBit(false);

        if(readBit())       //Check for ack. If no ack is recived try again
        {
            break;
        }
    }

    return;
}