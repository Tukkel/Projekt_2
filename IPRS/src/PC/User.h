#include <string>

class User
{
private:
    std::string username_;
    std::string password_;
    bool isLoggedIn_;

public:
    User();
    ~User();

    bool login(std::string username, std::string password);
    void logout();
    bool isLoggedIn();
    void changePassword(std::string newPassword);
};
