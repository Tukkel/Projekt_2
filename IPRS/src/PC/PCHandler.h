#pragma once
#include "User.h"

class PCHandler
{
public:
    PCHandler();
    // PCHandler(User* user_);

    void showMenu();
    void printData();
    void clearScreen() const;
    void changeSystem() const;
    void changeSlaves() const;

private:
    User user;
};