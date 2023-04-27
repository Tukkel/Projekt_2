#include <iostream>
#include "User.h"

int main()
{

    User admin("admin");

    while (!admin.isLoggedIn())
    {
        std::string password;

        std::cout << "Password: ";
        std::cin >> password;

        if (admin.login(password))
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