#include <iostream>
#include <string>
#include "User.h"
#include "PCHandler.h"

int main()
{

    PCHandler PC("admin");
    PC.clearScreen();
    std::cout << "Welcome to the IPRS system" << std::endl;
    PC.showMenu();

    return 0;
}

/*
# include<windows.h>
HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
DWORD consoleMode;
GetConsoleMode(console, &consoleMode);

//Remove echo from console
SetConsoleMode(console, consoleMode & ~ENABLE_ECHO_INPUT);

// Set console to default
SetConsoleMode(console, consoleMode);
*/