#pragma once
#include <string>
#include <vector>

class TX10
{
private:
    std::string rx_pin_;
    std::string tx_pin_;
    std::string clock_;
    bool *address_;
    char unit_;

    bool readBit();
    void writeBit(bool bit);

public:
    TX10(std::string rx_pin, std::string tx_pin, std::string clock, bool *address, char unit);
    ~TX10();
    std::vector<int> readData();
    void writeData(bool *data, bool *address);
};
