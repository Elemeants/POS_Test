#if !defined(APP_GUI_H)
#define APP_GUI_H

#include "pedido.h"
#include "user.h"
#include "inventario.h"
#include "user_manager.h"

extern void Login();
extern void Register(bool);
extern void Register();
extern bool MenuLog();
extern void initConfig();
extern UserManager userManager;
extern Inventario inventario;

struct GUI_APP
{
private:
    User usuario;
    Pedido carrito;

public:
    GUI_APP(User _user)
    {
        carrito = Pedido(_user);
        this->usuario = _user;
    }
    bool MenuPrincipal();
    bool BuscarProductos(bool);
    void MostrarProductos();

    struct Admin
    {
    private:
        bool isAdmin;

    public:
        Admin() : isAdmin(false) {}
        bool MenuModificarProducto(int);
        Admin(User _user) { this->isAdmin = _user.getPrivilege(); }
        bool MenuAdmin();
        void AddProducto();
        void ModifyProduct();
    };
};

#endif  // APP_GUI_H
