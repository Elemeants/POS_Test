#include "decorations.h"

#include <iostream>

#include "codes.h"

/// Imprime un separador en la pestaña
void Decorations::Separador()
{
    std::cout << std::endl;
    for (int i = 0; i < Decorations::WIDTH; i++)
        std::cout << (char)196;
    std::cout << std::endl;
}

void Menu::ShowMenu(bool clean_screen)
{
    if (clean_screen)
        SCREEN_CLEAR();
    Decorations::Separador();
    std::cout << "\t\t" << this->nameMenu << std::endl;
    if (!this->opciones.empty())
    {
        for (int i = 0; i < this->opciones.size(); i++)
        {
            std::cout << "  " << (i + 1) << ".- " << this->opciones.at(i) << std::endl;
        }
        std::cout << std::endl;
    }
    else
        std::cout << " No hay opciones disponibles" << std::endl;
}

void Menu::ShowMenu()
{
    this->ShowMenu(true);
}

int Menu::addOpcion(std::string _opcion)
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

int Menu::addOpcion(std::vector<std::string> _newOptions)
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

int Menu::addOpcion(std::string _newOptions[], int len)
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
