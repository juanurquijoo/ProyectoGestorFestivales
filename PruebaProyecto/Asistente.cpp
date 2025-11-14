#include "Asistente.hpp"
#include <iostream>
using namespace std;

Asistente::Asistente(int id, string nombre, int edad, string tipoEntrada, bool estudiante, bool pagada)
    : id(id), nombre(nombre), edad(edad), tipoEntrada(tipoEntrada), estudiante(estudiante), pagada(pagada) {
}

void Asistente::mostrarInfo() const {
    cout << "Asistente: " << nombre
        << " | Edad: " << edad
        << " | Tipo entrada: " << tipoEntrada
        << " | Estudiante: " << (estudiante ? "Si" : "No")
        << " | Pagada: " << (pagada ? "Si" : "No")
        << endl;
}

double Asistente::calcularPrecio() const {
    double precio = 0.0;
    if (tipoEntrada == "Dia") precio = 50.0;
    else if (tipoEntrada == "Abono3") precio = 110.0;
    else if (tipoEntrada == "VIP") precio = 200.0;

    if (estudiante) precio *= 0.8; // 20% descuento
    return precio;
}

int Asistente::getId() const { return id; }
string Asistente::getNombre() const { return nombre; }
bool Asistente::getPagada() const { return pagada; }
