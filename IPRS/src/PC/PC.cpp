#include <iostream>
#include "User.h"

int main()
{

    User admin;

    admin.login("admin", "admin");
    bool check = admin.isLoggedIn();
    std::cout << check << std::endl;

    return 0;
}