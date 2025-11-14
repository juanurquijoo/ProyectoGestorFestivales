#include "Escenario.hpp"
using namespace std;

// Constructor
Escenario::Escenario(int id, string nombre, int aforo)
    : id(id), nombre(nombre), aforoMaximo(aforo) {
}

// Métodos
void Escenario::mostrarInfo() const {
    cout << "Escenario: " << nombre
        << " | Aforo maximo: " << aforoMaximo
        << " | ID: " << id << endl;
}

int Escenario::getId() const { return id; }
string Escenario::getNombre() const { return nombre; }
int Escenario::getAforoMaximo() const { return aforoMaximo; }
