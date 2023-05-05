#include <iostream>
#include <string>
#include "User.h"
#include "PCHandler.h"

int main()
{

    User admin;
    PCHandler PC;
    std::cout << "Welcome to the IPRS system" << std::endl;
    admin.login();

    PC.showMenu();

    return 0;
}