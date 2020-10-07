#if !defined(DECORATIONS_H)
#define DECORATIONS_H

#include <string>
#include <vector>

#define SCREEN_STOP()       \
    std::cout << std::endl; \
    system("pause");
#define SCREEN_CLEAR() system("clear");

/// Estructura que contiene cosas decorativas
struct Decorations
{
    /// Constante WIDTH que determina el tamaño para las funciones
    static const int WIDTH = 40;
    /// Imprime un separador
    static void Separador();
};

/// Estrucutra de control de la interfaz
struct Menu
{
private:
    std::vector<std::string> opciones;
    std::string nameMenu;

public:
    Menu()
    {
        this->nameMenu = "";
        this->opciones.clear();
    }
    Menu(std::vector<std::string> _options, std::string _name)
    {
        this->nameMenu = _name;
        this->opciones.resize(_options.size());
        for (int i = 0; i < _options.size(); i++)
        {
            this->opciones.at(i) = _options.at(i);
        }
    }
    Menu(std::string _options[], int len, std::string _name)
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
    int addOpcion(std::string);
    int addOpcion(std::string[], int);
    int addOpcion(std::vector<std::string>);
    int deleteOpciones(int);
};

#endif  // DECORATIONS_H
