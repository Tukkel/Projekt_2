#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

User::User(std::string password)
{
    password_ = password;
    isLoggedIn_ = false;
}

bool User::login(std::string password)
{
    // Check if the username and password is correct
    if (password == password_)
    {
        isLoggedIn_ = true;
        return true;
    }
    else
    {
        return false;
    }
}
void User::logout()
{
}

bool User::isLoggedIn()
{
    return isLoggedIn_;
}

void User::changePassword(std::string newPassword)
{
    password_ = newPassword;
}