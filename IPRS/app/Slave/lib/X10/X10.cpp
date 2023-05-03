#pragma once
#include <string>
#include "X10.h"
#include <vector>

X10::X10(std::string rx_pin, std::string tx_pin, std::string clock, int *address, char unit)
{
    rx_pin_ = rx_pin;
    tx_pin_ = tx_pin;
    clock_ = clock;
    address_ = address;
    unit_ = unit;
}

X10::~X10()
{
}

bool X10::readBit()
{
    while (true) // While reading
    {
        if (clock_ == "high")
        {
            for (int i = 0; i < 100; i++)
            {
                if (rx_pin_ == "high")
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool* X10::readData()
{
    bool* data[100];
    int i = 0;
    
    while (true)
    { // While reading

        data[i] = readBit(); // Reads the bit

        if (i > 2) // If the data contains stop bits then break
            if (data[i] == true && data[i - 1] == false && data[i - 2] == false)
            {
                break;
            }
        i++;
    }

    // Sends ack to the sender
    if (clock_ == "high")
    {
        writeBit(true);
        return data;
    }
}

void X10::writeBit(bool bit)
{
    while (true)
    {
        if (clock_ == "")
        { // If tx10 signal is high
            if (bit)
            { // If bit is high
                tx_pin_ = "1";
                return;
            }
            else
            { // If bit is low
                tx_pin_ = "0";
                return;
            }
        }
    }
}

void X10::writeData(std::vector<bool> data, bool *address)
{
    // Creates the data size to send
    int writeData[(sizeof(data)) + 4 + 4 + 16];

    // Creates the data to send
    if (unit_ == 'S')
    { // If the unit is a slave
        for (int i = 0; i < sizeof(writeData); i++)
        {
            if (i < 3)
            {
                writeData[i] = 1;
            }
            else if (i < 4)
            {
                writeData[i] = 0;
            }
            else if (i < 20)
            {
                writeData[i] = address_[i - 4];
            }
            else if (i < 20 + sizeof(data))
            {
                writeData[i] = data[i - 20];
            }
            else if (i < 21 + sizeof(data))
            {
                writeData[i] = 1;
            }
            else
            {
                writeData[i] = 0;
            }
        }
    }
    else
    { // If the unit is a master
        for (int i = 0; i < sizeof(writeData); i++)
        {
            if (i < 3)
            {
                writeData[i] = 1;
            }
            else if (i < 4)
            {
                writeData[i] = 0;
            }
            else if (i < 20)
            {
                writeData[i] = address[i - 4];
            }
            else if (i < 20 + sizeof(data))
            {
                writeData[i] = data[i - 20];
            }
            else if (i < 21 + sizeof(data))
            {
                writeData[i] = 1;
            }
            else
            {
                writeData[i] = 0;
            }
        }
    }

    bool ack = false;
    while (!ack)
    { // While not ack

      // Sends the data
        for (int i = 0; i < sizeof(writeData); i++)
        {
            writeBit(writeData[i]);
        }

        if (clock_ == "high")
        {
            ack = readBit();
        }
    }

    return;
}