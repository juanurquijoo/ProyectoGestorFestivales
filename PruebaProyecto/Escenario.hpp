#pragma once
#include <string>
#include <iostream>

class Escenario {
private:
    int id;
    std::string nombre;
    int aforoMaximo;

public:
    // Constructor
    Escenario(int id, std::string nombre, int aforo);

    // Métodos para mostrar y consultar datos
    void mostrarInfo() const;
    int getId() const;
    std::string getNombre() const;
    int getAforoMaximo() const;
};
