#include "pedido.h"

#include <iostream>

#include "codes.h"
#include "decorations.h"

void Pedido::ImpTicket()
{
    SCREEN_CLEAR();
    Decorations::Separador();
    this->usuario.ImpDatos();
    Decorations::Separador();
    if (!this->productos.getAllProductos().empty())
    {
        for (int i = 0; i < this->productos.getAllProductos().size(); i++)
        {
            Producto producto = this->productos.getProducto(i);
            producto.ImpDatos();
            Decorations::Separador();
        }
        std::cout << " Costo total: $" << this->costo << "MXM" << std::endl;
    }
    else
    {
        std::cout << "\n No hay productos actualmente" << std::endl;
    }
}