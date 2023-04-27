#include <string>

class User
{
private:
    // Variables
    std::string password_;
    bool isLoggedIn_;

public:
    User(std::string password = "admin");

    // Function to login to the system, checks if the username and password are correct, Return if the login is true og not
    bool login(std::string password);

    // Function to logout of the system
    void logout();

    // Function to check if the user is logged in
    bool isLoggedIn();

    // Function to change the password of the user, username
    void changePassword(std::string newPassword);
};
