#include "Concierto.hpp"
#include "Escenario.hpp"
#include "Artista.hpp"
#include <iostream>
using namespace std;

// Constructor por defecto (sin datos)
Concierto::Concierto()
    : dia(-1), escenario(nullptr), artista(nullptr), valido(false) {
}

// Constructor con parametros (asignado)
Concierto::Concierto(int d, const Escenario* esc, const Artista* art)
    : dia(d), escenario(esc), artista(art), valido(false) {
    if (esc != nullptr && art != nullptr && d >= 0) {
        valido = true;
    }
}

// Metodo asignar datos a un concierto existente
void Concierto::asignar(int nuevoDia, const Escenario* esc, const Artista* art) {
    dia = nuevoDia;
    escenario = esc;
    artista = art;
    valido = (esc != nullptr && art != nullptr && nuevoDia >= 0);
}

// Metodo limpiar el concierto (deja libre)
void Concierto::limpiar() {
    dia = -1;
    escenario = nullptr;
    artista = nullptr;
    valido = false;
}

// Metodo mostrar informacion por consola
void Concierto::mostrarInfo() const {
    cout << "Concierto: ";
    if (!valido) {
        cout << "(libre)";
    }
    else {
        cout << "dia " << dia;
        cout << " | escenario asignado";
        cout << " | artista asignado";
    }
    cout << endl;
}

// Getters
int Concierto::getDia() const { return dia; }
const Escenario* Concierto::getEscenario() const { return escenario; }
const Artista* Concierto::getArtista() const { return artista; }
bool Concierto::esValido() const { return valido; }
