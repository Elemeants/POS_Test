/**
    Project: Sistema de reparacion de equipos de computo
    File: Robotica.cpp
    Version: 1.0
    Date: 2018/11/20
*/
/// Librerias para el control de la aplicacion
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <vector>

#define SCREEN_STOP() cout << endl; system("pause");
#define SCREEN_CLEAR() system("cls");
#define ERROR     -1
#define OUT_INDEX -2
#define NOT_FOUND -3
#define INVALID   -4
#define FOUNDED    0
#define PROCESS_OK 0

#define IS_ADMIN   true
#define NON_ADMIN  false

using namespace std;

/// Estructura que contiene cosas decorativas
struct Decorations
{
    /// Constante WIDTH que determina el tamaño para las funciones
    static const int WIDTH = 40;
    /// Imprime un separador
    static void Separador();
};

/// Imprime un separador en la pestaña
void Decorations::Separador()
{
    cout << endl;
    for (int i = 0; i < WIDTH; i++)
        cout << (char)196;
    cout << endl;
}

/// Estructura para el manejo de los usuarios
struct User
{
private:
    /// Atributo de ID del usuario
    int id;
    /// Atributo que guarda el nombre del usuario
    string nombre;
    /// Atributo que guarda la contraseña temporal
    string password;
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
    User(int _id, string _nombre, bool _admin)
    {
        this->id = _id;
        this->password = "";
        this->nombre = _nombre;
        this->is_admin = _admin;
    }
    User(int _id, string _nombre, string _password)
    {
        this->id = _id;
        this->password = _password;
        this->nombre = _nombre;
        this->is_admin = false;
    }
    User(int _id, string _nombre, string _password, bool _admin)
    {
        this->id = _id;
        this->password = _password;
        this->nombre = _nombre;
        this->is_admin = _admin;
    }
    /// Get/Set Functions
    void setID(int _id) { this->id = _id; }
    void setNombre(string _nombre) { this->nombre = _nombre; }
    void setAdmin(bool _admin) { this->is_admin = _admin; }
    int getID() { return this->id; }
    string getNombre() { return this->nombre; }
    bool getPrivilege() { return this->is_admin; }
    string getPass() { return this->password; }

    bool isEqual(User);
    void ImpDatos();
};

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
    cout << " Datos del usuario" << endl;
    cout << " ID: " << this->id << endl;
    cout << " Nombre:      " << this->nombre << endl;
    cout << " Privilegios: " << (this->is_admin ? "Administrador" : "Cliente")
        << endl;
}

struct UserManager
{
private:
    std::vector<User> userRegistrated;
public:
    bool Login(User&);
    bool Register(User);
    bool checkUsername(string);
};

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

bool UserManager::checkUsername(string _username)
{
    for (int i = 0; i < this->userRegistrated.size(); i++)
    {
        if (!this->userRegistrated.at(i).getNombre().compare(_username))
            return false;
    }
    return true;
}

/// Estructura de modelado para el control de los productos
struct Producto
{
private:
    /// Atributos de la estructura PRODUCTO
    int id;
    string nombre;
    string descripcion;
    double precio;
    int descuento;
public:
    /// Producto() -> default values
    /// Default values are: (-1, "", "", 0.0f, 0)
    Producto()
    {
        this->id = INVALID;
        this->nombre = "";
        this->descripcion = "";
        this->precio = 0.0f;
        this->descuento = 0;
    }
    // Producto(int, string, string, double) -> Manual values
    Producto(int _id, string _nombre, string _descrip, double _precio)
    {
        this->id = _id;
        this->nombre = _nombre;
        this->descripcion = _descrip;
        this->precio = _precio;
        this->descuento = 0;
    }
    /// Get/Set Functions
    void setID(int _id) { this->id = _id; }
    void setNombre(string _id) { this->nombre = nombre; }
    void setDescripcion(string _descrip) { this->descripcion = _descrip; }
    void setPrecio(double _precio) { this->precio = _precio; }
    void setDescuento(int _descuento) { this->descuento = _descuento; }
    int getID() { return this->id; }
    string getNombre() { return this->nombre; }
    string getDescripcion() { return this->descripcion; }
    double getPrecio() { return this->precio; }
    int getDescuento() { return this->descuento; }

    double getPrecioDescuento()
    {
        double precioDescuento = precio * ((double)(100 - descuento) / 100);
        return precioDescuento;
    }
    bool isEqual(Producto);
    void ImpDatos();
};

void Producto::ImpDatos()
{
    cout << std::setprecision(2) << std::fixed;
    cout << "\n ID:   " << this->id << endl;
    cout << " Producto:    " << this->nombre << endl;
    cout << " Descripcion: " << this->descripcion << endl;
    cout << " Precio:     $" << this->getPrecioDescuento() << "MXM" << endl;
    if (this->descuento > 0)
        cout << " Descuento:   " << this->descuento << "%" << endl;
}

bool Producto::isEqual(Producto _producto)
{
    if (this->nombre.compare(_producto.getNombre()))
        return false;
    if (this->descripcion.compare(_producto.getDescripcion()))
        return false;
    if (this->precio != _producto.getPrecio())
        return false;
    return true;
}

/// Estructura de control para el inventario
struct Inventario
{
private:
    std::vector<Producto> productos;
public:
    void CleanInventario() { this->productos.clear(); }
    int searchIndex(int);
    Producto searchProducto(Producto);
    void setProductos(std::vector<Producto> _product) { this->productos = _product; }
    std::vector<Producto> getAllProductos();
    Producto getProducto(int index);
    int updateProducto(Producto, int);
    int addProducto(Producto);
    int deleteProducto(Producto);
};

Producto Inventario::getProducto(int index)
{
    if (index < this->productos.size())
    {
        return this->productos.at(index);
    }
    return Producto();
}

int Inventario::searchIndex(int ID)
{
    for (int i = 0; i < this->productos.size(); i++)
    {
        if (this->productos.at(i).getID() == ID)
            return i;
    }
    return NOT_FOUND;
}

Producto Inventario::searchProducto(Producto _producto)
{
    if (!this->productos.empty())
    {
        int index = this->searchIndex(_producto.getID());
        if (index != NOT_FOUND)
        {
            return this->productos.at(index);
        }
    }
    return Producto();
}

std::vector<Producto> Inventario::getAllProductos()
{
    return this->productos;
}

int Inventario::updateProducto(Producto _producto, int index)
{
    if (index < this->productos.size())
    {
        this->productos.at(index) = _producto;
        return PROCESS_OK;
    }
    return OUT_INDEX;
}

int Inventario::addProducto(Producto _producto)
{
    try
    {
        this->productos.push_back(_producto);
        return PROCESS_OK;
    }
    catch (const std::bad_alloc& e)
    {
        return ERROR;
    }
}

int Inventario::deleteProducto(Producto _producto)
{
    if (!this->productos.empty())
    {
        int index = this->searchIndex(_producto.getID());
        if (index != NOT_FOUND)
        {
            this->productos.erase(this->productos.begin() + index);
            return PROCESS_OK;
        }
        return NOT_FOUND;
    }
    return OUT_INDEX;
}

/// Estrucutra de control de la interfaz
struct Menu
{
private:
    std::vector<string> opciones;
    string nameMenu;
public:
    Menu()
    {
        this->nameMenu = "";
        this->opciones.clear();
    }
    Menu(std::vector<string> _options, string _name)
    {
        this->nameMenu = _name;
        this->opciones.resize(_options.size());
        for (int i = 0; i < _options.size(); i++)
        {
            this->opciones.at(i) = _options.at(i);
        }
    }
    Menu(string _options[], int len, string _name)
    {
        this->nameMenu = _name;
        this->opciones.resize(len);
        for (int i = 0; i < len; i++)
        {
            this->opciones.at(i) = _options[i];
        }
    }
    void ShowMenu();
    void ShowMenu(bool);
    int addOpcion(string);
    int addOpcion(string[], int);
    int addOpcion(std::vector<string>);
    int deleteOpciones(int);
};

void Menu::ShowMenu(bool clean_screen)
{
    if(clean_screen)
        SCREEN_CLEAR();
    Decorations::Separador();
    cout << "\t\t" << this->nameMenu << endl;
    if (!this->opciones.empty())
    {
        for (int i = 0; i < this->opciones.size(); i++)
        {
            cout << "  " << (i + 1) << ".- " << this->opciones.at(i) << endl;
        }
        cout << endl;
    }
    else
        cout << " No hay opciones disponibles" << endl;
}

void Menu::ShowMenu()
{
    this->ShowMenu(true);
}

int Menu::addOpcion(string _opcion)
{
    try
    {
        this->opciones.push_back(_opcion);
        return PROCESS_OK;
    }
    catch (const std::bad_alloc& e)
    {
        return ERROR;
    }
}

int Menu::addOpcion(std::vector<string> _newOptions)
{
    for (int i = 0; i < _newOptions.size(); i++)
    {
        if (this->addOpcion(_newOptions.at(i)) == ERROR)
        {
            return ERROR;
        }
    }
    return PROCESS_OK;
}

int Menu::addOpcion(string _newOptions[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (this->addOpcion(_newOptions[i]) == ERROR)
        {
            return ERROR;
        }
    }
    return PROCESS_OK;
}

int Menu::deleteOpciones(int nOpcion)
{
    if (!this->opciones.empty())
    {
        if (nOpcion < this->opciones.size())
        {
            this->opciones.erase(this->opciones.begin() + nOpcion);
            return PROCESS_OK;
        }
        return NOT_FOUND;
    }
    return OUT_INDEX;
}

struct Pedido
{
private:
    User usuario;
    Inventario productos;
    double costo = 0;
public:
    Pedido(){}
    Pedido(User _user)
    {
        this->usuario = _user;
    }
    Pedido(User _user, std::vector<Producto> _product)
    {
        this->usuario = _user;
        this->productos.setProductos(_product);
        this->costo = 0;
        for(int i = 0; i < this->productos.getAllProductos().size(); i++)
            this->costo += this->productos.getAllProductos().at(i).getPrecioDescuento();
    }
    Pedido(User _user, Producto _product)
    {
        this->usuario = _user;
        this->productos.setProductos({_product});
        this->costo = _product.getPrecioDescuento();
    }
    void setUsuario(User _user) { this->usuario = _user; }
    void addProducto(Producto _product)
    {
        this->productos.addProducto(_product);
        this->costo += _product.getPrecioDescuento();
    }
    void ImpTicket();
};

void Pedido::ImpTicket()
{
    SCREEN_CLEAR();
    Decorations::Separador();
    this->usuario.ImpDatos();
    Decorations::Separador();
    if(!this->productos.getAllProductos().empty())
    {
        for (int i = 0; i < this->productos.getAllProductos().size(); i++)
        {
            Producto producto = this->productos.getProducto(i);
            producto.ImpDatos();
            Decorations::Separador();
        }
        cout << " Costo total: $" << this->costo << "MXM" << endl;
    }
    else
    {
        cout << "\n No hay productos actualmente" << endl;
    }
}

// Prototipos de funciones
void Login();
void Register(bool);
void Register();
bool MenuLog();
void initConfig();
UserManager userManager;
Inventario inventario;

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
        bool isAdmin = false;
    public:
        bool MenuModificarProducto(int);
        Admin(User _user) { this->isAdmin = _user.getPrivilege(); }
        bool MenuAdmin();
        void AddProducto();
        void ModifyProduct();
    };
};

bool GUI_APP::Admin::MenuAdmin()
{
    SCREEN_CLEAR();
    Menu adminMenu(
        {"Agregar usuario",
         "Agregar producto",
         "Modificar producto",
         "Salir"}
        , "Panel admin");
    Decorations::Separador();
    cout << "   Bienvenido Administrador!";
    adminMenu.ShowMenu(false);
    int selection = 0;
    cout << " -> ";
    cin >> selection;
    switch(selection)
    {
    case 1:
    {
        Register(IS_ADMIN);
        break;
    }
    case 2:
    {
        this->AddProducto();
        break;
    }
    case 3:
    {
        this->ModifyProduct();
        break;
    }
    case 4:
    {
        return false;
        break;
    }
    default:
        break;
    }
    return true;
}

bool GUI_APP::Admin::MenuModificarProducto(int index)
{
    int selectMenu = -1;
    SCREEN_CLEAR();
    cout << " Producto encontrado:";
    Producto producto = inventario.getProducto(index);
    producto.ImpDatos();
    Decorations::Separador();
    Menu modificar(
        { "Cambiar ID", "Cambiar nombre", "Cambiar descripcion",
         "Cambiar precio", "Cambiar descuento", "Salir" }
    , "Modificar producto");
    modificar.ShowMenu(false);
    cout << " -> ";
    cin >> selectMenu;
    fflush(stdin);
    cin.ignore();
    switch (selectMenu)
    {
    case 1:
    {
        int newId = -1;
        cout << "\n Ingresa la nueva ID: ";
        cin >> newId;
        producto.setID(newId);
        break;
    }
    case 2:
    {
        string newNombre;
        cout << "\n Ingresa el nuevo nombre:      ";
        getline(cin, newNombre);
        producto.setNombre(newNombre);
        break;
    }
    case 3:
    {
        string newDescrip;
        cout << "\n Ingresa la nueva descripcion: ";
        getline(cin, newDescrip);
        producto.setDescripcion(newDescrip);
        break;
    }
    case 4:
    {
        double newPrice;
        cout << "\n Ingresa el nuevo precio:      ";
        cin >> newPrice;
        producto.setPrecio(newPrice);
        break;
    }
    case 5:
    {
        int newDesc = -1;
        cout << "\n Ingresa el descuento(100-0): ";
        cin >> newDesc;
        producto.setDescuento(newDesc);
        break;
    }
    case 6:
    {
        return false;
    }
    default:
    {
        cout << " Opcion no valida..." << endl;
    }
    }
    inventario.updateProducto(producto, index);
    return true;
}

void GUI_APP::Admin::ModifyProduct()
{
    int id_producto = -1;
    SCREEN_CLEAR();
    Decorations::Separador();
    cout << " Modificar producto";
    Decorations::Separador();
    cout << " Ingrese la ID del producto: ";
    cin >> id_producto;
    int index = inventario.searchIndex(id_producto);
    if (index != NOT_FOUND)
    {
        while(this->MenuModificarProducto(index));
    }
    else
    {
        cout << " No se encontro el producto" << endl;
    }
}

void GUI_APP::Admin::AddProducto()
{
    SCREEN_CLEAR();
    Decorations::Separador();
    cout << " Agregar producto";
    Decorations::Separador();
    int ID = -1;
    string nombre;
    string descripcion;
    double precio = 0.0f;
    cout << " Ingrese la ID: "; cin >> ID;
    fflush(stdin);
    cin.ignore();
    cout << " Ingrese el nombre:      "; getline(cin, nombre);
    cout << " Ingrese la descripcion: "; getline(cin, descripcion);
    cout << " Ingrese el precio:     $"; cin >> precio;
    Decorations::Separador();
    Producto product(ID, nombre, descripcion, precio);
    cout << " Guardando el producto: ";
    product.ImpDatos();
    if(inventario.addProducto(product) == PROCESS_OK)
    {
        cout << " Producto guardado..." << endl;
    }
    else
    {
        cout << " Hubo un error al guardar el producto";
    }
}

bool GUI_APP::MenuPrincipal()
{
    SCREEN_CLEAR();
    Menu menu({ "Ver productos", "Buscar producto", "Ver carrito" }, "Opciones");
    if(this->usuario.getPrivilege() == IS_ADMIN)
        menu.addOpcion("Admin panel");
    menu.addOpcion("Salir");
    Decorations::Separador();
    cout << "   Bienvenido " << this->usuario.getNombre() << "!";
    menu.ShowMenu(false);
    int selection = 0;
    cout << " -> ";
    cin >> selection;
    /// See all productos
    if(selection == 1)
    {
        MostrarProductos();
    }
    /// Search producto
    if (selection == 2)
    {
        while (BuscarProductos(true));
    }
    if (selection == 3)
    {
        this->carrito.ImpTicket();
    }
    /// Admin mode
    if (selection == 4 && this->usuario.getPrivilege())
    {
        Admin panelAdmin(this->usuario);
        while (panelAdmin.MenuAdmin());
    }
    /// Go out session
    if ((selection == 5 && this->usuario.getPrivilege())
        || (selection == 4 && !this->usuario.getPrivilege()))
    {
        cout << "\n Saliendo de la sesion... " << endl;
        cout << " Adios " << this->usuario.getNombre() << endl;
        SCREEN_STOP();
        return false;
    }
    SCREEN_STOP();
    return true;
}

bool GUI_APP::BuscarProductos(bool _interface)
{
    if(_interface)
    {
        SCREEN_CLEAR();
        Decorations::Separador();
        cout << "\t  BUSCAR PRODUCTO ";
        Decorations::Separador();
    }

    int ID_producto = -1;
    cout << "\n Ingrese la ID del producto: ";
    cin >> ID_producto;
    int index = inventario.searchIndex(ID_producto);
    if (index != NOT_FOUND)
    {
        Producto producto = inventario.getProducto(index);
        cout << " Producto encontrado: ";
        producto.ImpDatos();
        cout << " Desea añadirlo al carrito? (y/n): ";
        char addCart = 'n';
        cin >> addCart;
        if(addCart == 'y')
        {
            this->carrito.addProducto(producto);
            cout << " ... Producto guardado ...";
            Decorations::Separador();
        }
        return false;
    }
    else
    {
        char repetir = 'n';
        cout << " No existe ese producto " << endl;
        cout << " Desea volver a buscar? (y/n): ";
        cin >> repetir;
        return (repetir == 'y');
    }
}

void GUI_APP::MostrarProductos()
{
    SCREEN_CLEAR();
    Decorations::Separador();
    cout << "\t\t PRODUCTOS ";
    Decorations::Separador();
    for (int i = 0; i < inventario.getAllProductos().size(); i++)
    {
        Producto producto = inventario.getProducto(i);
        producto.ImpDatos();
        Decorations::Separador();
    }
    char seleccion;
    cout << " Desea añadir algo a su carrito? (y/n): ";
    cin >> seleccion;
    if (seleccion == 'y')
    {
        int ID_producto = -1;
        cout << "\n Ingrese la ID del producto: ";
        cin >> ID_producto;
        int index = inventario.searchIndex(ID_producto);
        if(index != NOT_FOUND)
        {
            Producto newCarrito = inventario.getProducto(index);
            this->carrito.addProducto(newCarrito);
            cout << " Producto agregado..." << endl << endl;
            cout << " Datos del producto: ";
            newCarrito.ImpDatos();
        }
        else
        {
            cout << " No existe ese producto " << endl;
        }
    }
}

int main(void)
{
    initConfig();
    while (MenuLog());
    SCREEN_STOP();
    return PROCESS_OK;
}

bool MenuLog()
{
    fflush(stdin);
    int selection;
    Menu principal({ "Login", "Registrar", "Invitado", "Salir" }, "PUNTO DE VENTA");
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
        while (app.MenuPrincipal());
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
        while(app.MenuPrincipal());
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
