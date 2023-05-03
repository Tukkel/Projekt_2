#pragma once
#include <string>
#include <vector>

class X10
{
private:
    std::string rx_pin_;
    std::string tx_pin_;
    std::string clock_;
    int *address_;
    char unit_;

    bool readBit();
    void writeBit(bool bit);

public:
    X10(std::string rx_pin, std::string tx_pin, std::string clock, int *address, char unit);
    ~X10();
    bool* readData();
    void writeData(bool *data, bool *address);
};
