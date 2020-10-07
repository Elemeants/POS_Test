#include "gui.h"

#include <iostream>

#include "decorations.h"
#include "user_manager.h"
#include "inventario.h"

bool GUI_APP::Admin::MenuAdmin()
{
    SCREEN_CLEAR();
    Menu adminMenu(
        {"Agregar usuario",
         "Agregar producto",
         "Modificar producto",
         "Salir"},
        "Panel admin");
    Decorations::Separador();
    std::cout << "   Bienvenido Administrador!";
    adminMenu.ShowMenu(false);
    int selection = 0;
    std::cout << " -> ";
    std::cin >> selection;
    switch (selection)
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
    std::cout << " Producto encontrado:";
    Producto producto = inventario.getProducto(index);
    producto.ImpDatos();
    Decorations::Separador();
    Menu modificar(
        {"Cambiar ID", "Cambiar nombre", "Cambiar descripcion",
         "Cambiar precio", "Cambiar descuento", "Salir"},
        "Modificar producto");
    modificar.ShowMenu(false);
    std::cout << " -> ";
    std::cin >> selectMenu;
    fflush(stdin);
    std::cin.ignore();
    switch (selectMenu)
    {
    case 1:
    {
        int newId = -1;
        std::cout << "\n Ingresa la nueva ID: ";
        std::cin >> newId;
        producto.setID(newId);
        break;
    }
    case 2:
    {
        std::string newNombre;
        std::cout << "\n Ingresa el nuevo nombre:      ";
        getline(std::cin, newNombre);
        producto.setNombre(newNombre);
        break;
    }
    case 3:
    {
        std::string newDescrip;
        std::cout << "\n Ingresa la nueva descripcion: ";
        getline(std::cin, newDescrip);
        producto.setDescripcion(newDescrip);
        break;
    }
    case 4:
    {
        double newPrice;
        std::cout << "\n Ingresa el nuevo precio:      ";
        std::cin >> newPrice;
        producto.setPrecio(newPrice);
        break;
    }
    case 5:
    {
        int newDesc = -1;
        std::cout << "\n Ingresa el descuento(100-0): ";
        std::cin >> newDesc;
        producto.setDescuento(newDesc);
        break;
    }
    case 6:
    {
        return false;
    }
    default:
    {
        std::cout << " Opcion no valida..." << std::endl;
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
    std::cout << " Modificar producto";
    Decorations::Separador();
    std::cout << " Ingrese la ID del producto: ";
    std::cin >> id_producto;
    int index = inventario.searchIndex(id_producto);
    if (index != NOT_FOUND)
    {
        while (this->MenuModificarProducto(index))
            ;
    }
    else
    {
        std::cout << " No se encontro el producto" << std::endl;
    }
}

void GUI_APP::Admin::AddProducto()
{
    SCREEN_CLEAR();
    Decorations::Separador();
    std::cout << " Agregar producto";
    Decorations::Separador();
    int ID = -1;
    std::string nombre;
    std::string descripcion;
    double precio = 0.0f;
    std::cout << " Ingrese la ID: ";
    std::cin >> ID;
    fflush(stdin);
    std::cin.ignore();
    std::cout << " Ingrese el nombre:      ";
    getline(std::cin, nombre);
    std::cout << " Ingrese la descripcion: ";
    getline(std::cin, descripcion);
    std::cout << " Ingrese el precio:     $";
    std::cin >> precio;
    Decorations::Separador();
    Producto product(ID, nombre, descripcion, precio);
    std::cout << " Guardando el producto: ";
    product.ImpDatos();
    if (inventario.addProducto(product) == PROCESS_OK)
    {
        std::cout << " Producto guardado..." << std::endl;
    }
    else
    {
        std::cout << " Hubo un error al guardar el producto";
    }
}

bool GUI_APP::MenuPrincipal()
{
    SCREEN_CLEAR();
    Menu menu({"Ver productos", "Buscar producto", "Ver carrito"}, "Opciones");
    if (this->usuario.getPrivilege() == IS_ADMIN)
        menu.addOpcion("Admin panel");
    menu.addOpcion("Salir");
    Decorations::Separador();
    std::cout << "   Bienvenido " << this->usuario.getNombre() << "!";
    menu.ShowMenu(false);
    int selection = 0;
    std::cout << " -> ";
    std::cin >> selection;
    /// See all productos
    if (selection == 1)
    {
        MostrarProductos();
    }
    /// Search producto
    if (selection == 2)
    {
        while (BuscarProductos(true))
            ;
    }
    if (selection == 3)
    {
        this->carrito.ImpTicket();
    }
    /// Admin mode
    if (selection == 4 && this->usuario.getPrivilege())
    {
        Admin panelAdmin(this->usuario);
        while (panelAdmin.MenuAdmin())
            ;
    }
    /// Go out session
    if ((selection == 5 && this->usuario.getPrivilege()) || (selection == 4 && !this->usuario.getPrivilege()))
    {
        std::cout << "\n Saliendo de la sesion... " << std::endl;
        std::cout << " Adios " << this->usuario.getNombre() << std::endl;
        SCREEN_STOP();
        return false;
    }
    SCREEN_STOP();
    return true;
}

bool GUI_APP::BuscarProductos(bool _interface)
{
    if (_interface)
    {
        SCREEN_CLEAR();
        Decorations::Separador();
        std::cout << "\t  BUSCAR PRODUCTO ";
        Decorations::Separador();
    }

    int ID_producto = -1;
    std::cout << "\n Ingrese la ID del producto: ";
    std::cin >> ID_producto;
    int index = inventario.searchIndex(ID_producto);
    if (index != NOT_FOUND)
    {
        Producto producto = inventario.getProducto(index);
        std::cout << " Producto encontrado: ";
        producto.ImpDatos();
        std::cout << " Desea añadirlo al carrito? (y/n): ";
        char addCart = 'n';
        std::cin >> addCart;
        if (addCart == 'y')
        {
            this->carrito.addProducto(producto);
            std::cout << " ... Producto guardado ...";
            Decorations::Separador();
        }
        return false;
    }
    else
    {
        char repetir = 'n';
        std::cout << " No existe ese producto " << std::endl;
        std::cout << " Desea volver a buscar? (y/n): ";
        std::cin >> repetir;
        return (repetir == 'y');
    }
}

void GUI_APP::MostrarProductos()
{
    SCREEN_CLEAR();
    Decorations::Separador();
    std::cout << "\t\t PRODUCTOS ";
    Decorations::Separador();
    for (int i = 0; i < inventario.getAllProductos().size(); i++)
    {
        Producto producto = inventario.getProducto(i);
        producto.ImpDatos();
        Decorations::Separador();
    }
    char seleccion;
    std::cout << " Desea añadir algo a su carrito? (y/n): ";
    std::cin >> seleccion;
    if (seleccion == 'y')
    {
        int ID_producto = -1;
        std::cout << "\n Ingrese la ID del producto: ";
        std::cin >> ID_producto;
        int index = inventario.searchIndex(ID_producto);
        if (index != NOT_FOUND)
        {
            Producto newCarrito = inventario.getProducto(index);
            this->carrito.addProducto(newCarrito);
            std::cout << " Producto agregado..." << std::endl
                      << std::endl;
            std::cout << " Datos del producto: ";
            newCarrito.ImpDatos();
        }
        else
        {
            std::cout << " No existe ese producto " << std::endl;
        }
    }
}