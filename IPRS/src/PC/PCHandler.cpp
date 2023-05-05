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
        clearScreen();
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
            printData();
            break;
        case 2:
            std::cout << "You chose to make a change to the system." << std::endl;
            changeSystem();
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
        clearScreen();
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

void PCHandler::changeSlaves() const
{
    bool validChoice = false;

    while (!validChoice)
    {
        int Slavechoice;
        std::cin >> Slavechoice;
        if (Slavechoice > 0)
        {
            std::cout << "You chose to change the number of slaves to " << Slavechoice << std::endl;
            validChoice = true;
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please choose again." << std::endl;
        }
    }
}

void PCHandler::changeSystem() const
{
    std::cout << "Printing data..." << std::endl;

    int choice = 0;
    bool goBack = false;

    while (!goBack)
    {
        clearScreen();
        std::cout << "Welcome to your program!" << std::endl;
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Change Number of slaves" << std::endl;
        std::cout << "2. Print Oldest Log" << std::endl;
        std::cout << "3. Print Nothing" << std::endl;
        std::cout << "4. Go Back" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "How many slaves?" << std::endl;
            changeSlaves();
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

void PCHandler::clearScreen() const
{
    system("cls"); // Code to clear the screen
}
