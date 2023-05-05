#include "PCHandler.h"
#include <iostream>

PCHandler::PCHandler()
{
}

void PCHandler::showMenu() const
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

void PCHandler::printData() const
{
    std::cout << "Printing data..." << std::endl;

    int choice = 0;
    bool goBack = false;

    while (!goBack)
    {
        std::cout << "Welcome to your program!" << std::endl;
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Print Newest Data" << std::endl;
        std::cout << "2. Print Oldest Log" << std::endl;
        std::cout << "3. Print Nothing" << std::endl;
        std::cout << "4. Go Back" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "You chose to print Newest Data." << std::endl;
            // Code to print data
            break;
        case 2:
            std::cout << "You chose to Print Oldest Log" << std::endl;
            // Code to make a change to the system
            break;
        case 3:
            std::cout << "You chose to Print Nothing." << std::endl;
            // Code to calibrate the system
            break;
        case 4:
            std::cout << "You chose to Go Back." << std::endl;
            goBack = true;
            break;
        default:
            std::cout << "Invalid choice. Please choose again." << std::endl;
            break;
        }

        std::cout << std::endl;
    }
}