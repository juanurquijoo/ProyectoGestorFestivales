#include <iostream>
#include <limits>
#include "GestorFestival.hpp"
using namespace std;
/*
- El Proyecto es un gestor de festivales de musica, permite hacer lo siguiente:
    1. Resgistrar artistas, escenarios y asistentes.
    2. Programar conciertos asignando artista + escenario en un dia.
    3. Evitar incoherencias (un artista no puede tocar dos veces el mismo dia).
    4. Listar artistas/escenarios/agenda.
    5. Guardar los datos a disco y cargar despues.
    6. Interactuar desde un menu en consola con control basico de errores.
*/
int leerInt(const char* msg) {
    cout << msg;
    int x;
    while (!(cin >> x)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "valor invalido: "; }
    return x;
}
string leerStr(const char* msg) {
    cout << msg;
    string s; getline(cin >> ws, s); return s;
}

int main() {
    GestorFestival g("UniMusicFest", 3);
    g.inicializarEscenariosDefecto();
    g.inicializarAgenda();

    bool salir = false;
    while (!salir) {
        cout << "\n=== MENU ===\n"
            << "1) listar escenarios\n"
            << "2) anadir artista\n"
            << "3) listar artistas\n"
            << "4) asignar concierto\n"
            << "5) listar agenda dia\n"
            << "6) guardar (carpeta data)\n"
            << "7) cargar  (carpeta data)\n"
            << "8) salir\n";
        int op = leerInt("opcion: ");
        try {
            switch (op) {
            case 1: g.listarEscenarios(); break;
            case 2: {
                int id = leerInt("id artista: ");
                string nom = leerStr("nombre: ");
                string gen = leerStr("genero: ");
                double dur; cout << "duracion min: "; cin >> dur;
                int dem = leerInt("demanda: ");
                if (!g.anadirArtista(Artista(id, nom, gen, dur, dem)))
                    cout << "id duplicado\n";
                break;
            }
            case 3: g.listarArtistas(); break;
            case 4: {
                int d = leerInt("dia: ");
                int idEsc = leerInt("id escenario: ");
                int idArt = leerInt("id artista: ");
                if (!g.asignarConcierto(d, idEsc, idArt))
                    cout << "no se pudo asignar\n";
                break;
            }
            case 5: {
                int d = leerInt("dia: ");
                g.listarAgendaDia(d);
                break;
            }
            case 6: cout << (g.guardar("data") ? "guardado\n" : "error guardando\n"); break;
            case 7: cout << (g.cargar("data") ? "cargado\n" : "error cargando\n");  break;
            case 8: salir = true; break;
            default: cout << "opcion invalida\n";
            }
        }
        catch (const exception& e) {
            cout << "excepcion: " << e.what() << "\n";
        }
    }
    return 0;
}
