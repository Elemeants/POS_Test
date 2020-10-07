#include "inventario.h"

#include "codes.h"

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