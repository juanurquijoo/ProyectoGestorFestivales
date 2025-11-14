#include <cassert>
#include <iostream>
#include "GestorFestival.hpp"
using namespace std;

int main() {
    GestorFestival g("TestFest", 2);
    g.inicializarEscenariosDefecto();
    g.inicializarAgenda();

    // alta artistas
    bool ok1 = g.anadirArtista(Artista(1, "Coldplay", "Pop-Rock", 120.0, 4000));
    bool ok2 = g.anadirArtista(Artista(2, "The Killers", "Indie", 90.0, 2500));
    assert(ok1 && ok2);

    // sobrecarga de busqueda
    assert(g.buscarArtista(1) != nullptr);
    assert(g.buscarArtista("The Killers") != nullptr);
    assert(g.buscarEscenario(0) != nullptr);
    assert(g.buscarEscenario("Main") != nullptr);

    // asignacion agenda
    bool asignado = g.asignarConcierto(0, 0, 1); // dia 0, escenario 0, artista 1
    assert(asignado);

    // duplicado mismo dia debe fallar
    bool otraVez = g.asignarConcierto(0, 1, 1);
    assert(!otraVez);

    cout << "OK - tests basicos superados\n";
    return 0;
}
