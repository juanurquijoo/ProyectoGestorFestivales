#pragma once
#include <string>

class Artista {
private:
    int id;
    std::string nombre;
    std::string genero;     
    double duracionMin;
    int demandaEstimada;

public:
    // Constructor
    Artista(int id, std::string nombre, std::string genero, double duracion, int demanda);

    // interface
    void mostrarInfo() const;

    // === GETTERS que usa GestorFestival ===
    int getId() const;
    std::string getNombre() const;
    std::string getGenero() const;
    double getDuracion() const;
    int getDemanda() const;
};
