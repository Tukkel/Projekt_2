
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