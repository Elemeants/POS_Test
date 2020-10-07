#include "user_manager.h"
#include "codes.h"

bool UserManager::Login(User &_user)
{
    if (_user.getID() != INVALID)
    {
        for (int i = 0; i < this->userRegistrated.size(); i++)
        {
            if (this->userRegistrated.at(i).isEqual(_user))
            {
                _user = this->userRegistrated.at(i);
                return true;
            }
        }
    }
    return false;
}

bool UserManager::Register(User _user)
{
    try
    {
        this->userRegistrated.push_back(_user);
        return true;
    }
    catch (const std::bad_alloc& e)
    {
        return false;
    }
}

bool UserManager::checkUsername(std::string _username)
{
    for (int i = 0; i < this->userRegistrated.size(); i++)
    {
        if (!this->userRegistrated.at(i).getNombre().compare(_username))
            return false;
    }
    return true;
}