#include <iostream>
#include "User.h"

int main()
{

    User admin;

    while (!admin.isLoggedIn())
    {
        std::string username;
        std::string password;

        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        if (admin.login(username, password))
        {
            std::cout << "Login successful" << std::endl;
        }
        else
        {
            std::cout << "Login failed try again" << std::endl;
        }
    }

    return 0;
}