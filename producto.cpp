#include "producto.h"

#include <iostream>
#include <iomanip>

void Producto::ImpDatos()
{
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "\n ID:   " << this->id << std::endl;
    std::cout << " Producto:    " << this->nombre << std::endl;
    std::cout << " Descripcion: " << this->descripcion << std::endl;
    std::cout << " Precio:     $" << this->getPrecioDescuento() << "MXM" << std::endl;
    if (this->descuento > 0)
        std::cout << " Descuento:   " << this->descuento << "%" << std::endl;
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