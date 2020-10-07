#if !defined(INVENTARIO_H)
#define INVENTARIO_H

#include <string>
#include <vector>

#include "producto.h"

/// Estructura de control para el inventario
class Inventario
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
typedef class Inventario Inventario;

#endif  // INVENTARIO_H
