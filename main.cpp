#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "codes.h"
#include "decorations.h"
#include "gui.h"
#include "inventario.h"
#include "pedido.h"
#include "user_manager.h"

using namespace std;

// Prototipos de funciones
void Login();
void Register(bool);
void Register();
bool MenuLog();
void initConfig();
UserManager userManager;
Inventario inventario;

int main(void)
{
    initConfig();
    while (MenuLog())
        ;
    SCREEN_STOP();
    return PROCESS_OK;
}

bool MenuLog()
{
    fflush(stdin);
    int selection;
    Menu principal({"Login", "Registrar", "Invitado", "Salir"}, "PUNTO DE VENTA");
    principal.ShowMenu();
    cout << " -> ";
    cin >> selection;
    switch (selection)
    {
    case 1:
        Login();
        break;
    case 2:
        Register();
        break;
    case 3:
    {
        GUI_APP app(User(0, "Invitado", false));
        while (app.MenuPrincipal())
            ;
        break;
    }
    case 4:
        cout << " Saliendo de la aplicacion " << endl;
        return false;
    default:
        cout << "\n Seleccion no valida" << endl;
    }
    return true;
}

void Login()
{
    SCREEN_CLEAR();
    Decorations::Separador();
    string username = "";
    string password = "";
    cout << "\t\tLOGIN";
    Decorations::Separador();
    cout << " Usuario:     ";
    cin >> username;
    cout << " Contrasenia: ";
    cin >> password;
    User usuario(0, username, password);
    if (userManager.Login(usuario))
    {
        cout << "\n Correcto bienvenido " << usuario.getNombre() << endl;
        GUI_APP app(usuario);
        while (app.MenuPrincipal())
            ;
    }
    else
    {
        char selection = 'n';
        cout << endl;
        cout << " Incorrecto no se pudo ingresar " << endl;
        cout << " Quiere volver a intentarlo? (y/n): ";
        cin >> selection;
        if (selection == 'y')
        {
            Login();
        }
    }
    SCREEN_CLEAR();
}

void Register()
{
    Register(NON_ADMIN);
}

void Register(bool Admin_mode)
{
    SCREEN_CLEAR();
    Decorations::Separador();
    int id = INVALID;
    string username = "";
    string password = "";
    cout << "\t\t REGISTRAR";
    Decorations::Separador();
    cout << " ID: ";
    cin >> id;
    cout << " Usuario:     ";
    cin >> username;
    cout << " Contrasenia: ";
    cin >> password;
    User usuario(id, username, password, Admin_mode);
    if (userManager.checkUsername(usuario.getNombre()))
    {
        if (userManager.Register(usuario))
            cout << "\n Correcto registrado " << usuario.getNombre() << endl;
        else
            cout << " Hubo un error al registrar el usuario" << endl;
        SCREEN_STOP();
    }
    else
    {
        char selection = 'n';
        cout << endl;
        cout << " Ya existe ese nombre de usuario " << endl;
        cout << " Quiere volver a intentarlo? (y/n): ";
        cin >> selection;
        if (selection == 'y')
            Register();
    }
    SCREEN_CLEAR();
}

void initConfig()
{
    /// Limpiando el inventario
    inventario.CleanInventario();
    /// Usuario administrador por defecto
    userManager.Register(User(0, "Admin", "1234", true));
    inventario.addProducto(Producto(4, "Caca", "ASDASD", 10.2));
    /// Inventario por defecto
    inventario.addProducto(Producto(0, "Leche 1lt", "1 litro de leche", 17.50));
    inventario.addProducto(Producto(1, "Galletas", "Paquete de galletas\nRicuras", 21.50));
    inventario.addProducto(Producto(2, "Test", "Yo que se algo", 5.00));
    inventario.addProducto(Producto(3, "Leche 1/2lt", "1/2 litro de leche", 10.50));
    /// Limpiamos la pestaña
    SCREEN_CLEAR();
}
