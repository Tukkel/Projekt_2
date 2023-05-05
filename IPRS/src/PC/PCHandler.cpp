#include "PCHandler.h"
#include <iostream>

PCHandler::PCHandler()
{
}

void PCHandler::showMenu()
{
    int choice = 0;
    bool isLoggedIn = true;

    while (isLoggedIn)
    {
        std::cout << "Welcome to your program!" << std::endl;
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Print Data" << std::endl;
        std::cout << "2. Make change to system" << std::endl;
        std::cout << "3. Calibrate system" << std::endl;
        std::cout << "4. Log out" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "You chose to print data." << std::endl;
            // Code to print data
            break;
        case 2:
            std::cout << "You chose to make a change to the system." << std::endl;
            // Code to make a change to the system
            break;
        case 3:
            std::cout << "You chose to calibrate the system." << std::endl;
            // Code to calibrate the system
            break;
        case 4:
            std::cout << "You chose to log out." << std::endl;
            isLoggedIn = false;
            break;
        default:
            std::cout << "Invalid choice. Please choose again." << std::endl;
            break;
        }

        std::cout << std::endl;
    }
}