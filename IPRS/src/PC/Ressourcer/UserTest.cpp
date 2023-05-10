#include "UserTest.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

UserTest::UserTest(std::string password)
{
    password_ = password;
    isLoggedIn_ = false;
}

void UserTest::login()
{

    while (!isLoggedIn())
    {
        std::string password;
        std::cout << "Login to the system" << std::endl;
        std::cout << "Password: ";
        std::cin >> password;

        if (password == password_)
        {
            std::cout << "Login successful" << std::endl;
            isLoggedIn_ = true;
        }
        else
        {
            std::cout << "Login failed try again" << std::endl;
        }
    }
}

void UserTest::logout()
{
    isLoggedIn_ = false;
}

bool UserTest::isLoggedIn()
{
    return isLoggedIn_;
}

void UserTest::changePassword(std::string newPassword)
{
    password_ = newPassword;
}