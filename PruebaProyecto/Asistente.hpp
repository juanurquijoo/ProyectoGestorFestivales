#pragma once
#include <string>

class Asistente {
private:
    int id;
    std::string nombre;
    int edad;
    std::string tipoEntrada; // Dia, Abono3 o VIP
    bool estudiante;
    bool pagada;

public:
    // Constructor
    Asistente(int id, std::string nombre, int edad, std::string tipoEntrada, bool estudiante, bool pagada);

    // Metodos
    void mostrarInfo() const;
    double calcularPrecio() const; // con descuento si es estudiante

    // Getters
    int getId() const;
    std::string getNombre() const;
    bool getPagada() const;
};
