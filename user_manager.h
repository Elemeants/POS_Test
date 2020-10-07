#if !defined(USER_MANAGER_H)
#define USER_MANAGER_H

#include <vector>

#include "user.h"

class UserManager
{
private:
    std::vector<User> userRegistrated;

public:
    bool Login(User&);
    bool Register(User);
    bool checkUsername(std::string);
};

#endif  // USER_MANAGER_H
