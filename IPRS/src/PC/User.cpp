#include "User.h"
#include <string>
#include <iostream>

User::User()
{
    username_ = "admin";
    password_ = "admin";
    isLoggedIn_ = false;
}

bool User::login(std::string username, std::string password)
{
    // Check if the username and password is correct
    if (username == username_ && password == password_)
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