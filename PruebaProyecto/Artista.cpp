#include "Artista.hpp"
#include <iostream>
using namespace std;

// Constructor
Artista::Artista(int id, string nombre, string genero, double duracion, int demanda)
    : id(id), nombre(nombre), genero(genero), duracionMin(duracion), demandaEstimada(demanda) {
}

// Metodo que muestra la info de los artistas
void Artista::mostrarInfo() const {
    cout << "Artista: " << nombre
        << " | Genero: " << genero
        << " | Duracion: " << duracionMin << " min"
        << " | Demanda: " << demandaEstimada << endl;
}

// Getters
int Artista::getId() const { return id; }
std::string Artista::getNombre() const { return nombre; }
std::string Artista::getGenero() const { return genero; }
double Artista::getDuracion() const { return duracionMin; }
int Artista::getDemanda() const { return demandaEstimada; }
