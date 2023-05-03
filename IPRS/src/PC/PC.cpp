#include <iostream>
#include <string>
#include "User.h"

int main()
{

    User admin;
    while (true)
    {
        std::cout << "Welcome to the IPRS system" << std::endl;

        while (!admin.isLoggedIn())
        {
            std::string password;
            std::cout << "Login to the system" << std::endl;
            std::cout << "Password: ";
            std::cin >> password;

            if (admin.login(password))
            {
                std::cout << "Login successful" << std::endl;
                // Do stuff
            }
            else
            {
                std::cout << "Login failed try again" << std::endl;
            }
        }
    }
    return 0;
}

/*
#include <ncurses.h>
#include <string>
#include "User.h"

    int main()
{
    User admin;

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    start_color();
    curs_set(0);

    while (!admin.isLoggedIn())
    {
        std::string password;

        // Prompt for password
        printw("Password: ");
        refresh();

        // Get password input
        char input[256];
        getstr(input);

        // Convert input to std::string
        password = input;

        if (admin.login(password))
        {
            printw("Login successful\n");
            refresh();
        }
        else
        {
            printw("Login failed. Try again.\n");
            refresh();
        }
    }

    // Clean up ncurses
    endwin();

    return 0;
}
*/