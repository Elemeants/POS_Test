#include "user.h"

#include <iostream>

bool User::isEqual(User _user)
{
    if (this->nombre.compare(_user.getNombre()))
        return false;
    if (this->password.compare(_user.getPass()))
        return false;
    return true;
}

void User::ImpDatos()
{
    std::cout << " Datos del usuario" << std::endl;
    std::cout << " ID: " << this->id << std::endl;
    std::cout << " Nombre:      " << this->nombre << std::endl;
    std::cout << " Privilegios: " << (this->is_admin ? "Administrador" : "Cliente")
              << std::endl;
}