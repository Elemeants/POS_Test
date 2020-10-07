#if !defined(PEDIDO_H)
#define PEDIDO_H

#include "producto.h"
#include "user.h"
#include "inventario.h"

struct Pedido
{
private:
    User usuario;
    Inventario productos;
    double costo;

public:
    Pedido() {}
    Pedido(User _user)
    {
        this->usuario = _user;
    }
    Pedido(User _user, std::vector<Producto> _product)
    {
        this->usuario = _user;
        this->productos.setProductos(_product);
        this->costo = 0;
        for (int i = 0; i < this->productos.getAllProductos().size(); i++)
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

#endif  // PEDIDO_H
