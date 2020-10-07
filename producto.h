#if !defined(PRODUCTO_H)
#define PRODUCTO_H

#include <string>

#include "codes.h"

/// Estructura de modelado para el control de los productos
struct Producto
{
private:
    /// Atributos de la estructura PRODUCTO
    int id;
    std::string nombre;
    std::string descripcion;
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
    // Producto(int, std::string, std::string, double) -> Manual values
    Producto(int _id, std::string _nombre, std::string _descrip, double _precio)
    {
        this->id = _id;
        this->nombre = _nombre;
        this->descripcion = _descrip;
        this->precio = _precio;
        this->descuento = 0;
    }
    /// Get/Set Functions
    void setID(int _id) { this->id = _id; }
    void setNombre(std::string _id) { this->nombre = nombre; }
    void setDescripcion(std::string _descrip) { this->descripcion = _descrip; }
    void setPrecio(double _precio) { this->precio = _precio; }
    void setDescuento(int _descuento) { this->descuento = _descuento; }
    int getID() { return this->id; }
    std::string getNombre() { return this->nombre; }
    std::string getDescripcion() { return this->descripcion; }
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

#endif  // PRODUCTO_H
