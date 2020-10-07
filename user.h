#if !defined(USER_H)
#define USER_H

#include <string.h>

#include <string>

#include "codes.h"

/// Estructura para el manejo de los usuarios
class User
{
private:
    /// Atributo de ID del usuario
    int id;
    /// Atributo que guarda el nombre del usuario
    std::string nombre;
    /// Atributo que guarda la contraseña temporal
    std::string password;
    /// Atributo que contiene si es administrador
    bool is_admin;

public:
    /// User() -> default values
    /// Default values are: (-1, "", false)
    User()
    {
        this->id = INVALID;
        this->nombre = "";
        this->password = "";
        this->is_admin = false;
    }

    /// User(int, string, bool) -> Manual values
    User(int _id, std::string _nombre, bool _admin)
    {
        this->id = _id;
        this->password = "";
        this->nombre = _nombre;
        this->is_admin = _admin;
    }
    User(int _id, std::string _nombre, std::string _password)
    {
        this->id = _id;
        this->password = _password;
        this->nombre = _nombre;
        this->is_admin = false;
    }
    User(int _id, std::string _nombre, std::string _password, bool _admin)
    {
        this->id = _id;
        this->password = _password;
        this->nombre = _nombre;
        this->is_admin = _admin;
    }

    /// Get/Set Functions
    void setID(int _id) { this->id = _id; }
    void setNombre(std::string _nombre) { this->nombre = _nombre; }
    void setAdmin(bool _admin) { this->is_admin = _admin; }
    int getID() { return this->id; }
    std::string getNombre() { return this->nombre; }
    bool getPrivilege() { return this->is_admin; }
    std::string getPass() { return this->password; }

    bool isEqual(User);
    void ImpDatos();
};

#endif  // USER_H
