#include "GestorFestival.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
using namespace std;

// Funcion libre para componer rutas de ficheros
static string joinPath(const string& dir, const string& name) {
#ifdef _WIN32
    if (dir.empty() || dir == ".") return name;
    return dir + "\\" + name;
#else
    if (dir.empty() || dir == ".") return name;
    return dir + "/" + name;
#endif
}

// Constructor
GestorFestival::GestorFestival(string n, int d)
    : nombre(std::move(n)), dias(d > 0 ? d : DIAS_DEFECTO) {
}

// Getters
const string& GestorFestival::getNombre() const { return nombre; }
int  GestorFestival::getDias() const { return dias; }
int  GestorFestival::getNumEscenarios() const { return static_cast<int>(escenarios.size()); }
int  GestorFestival::getNumArtistas()   const { return static_cast<int>(artistas.size()); }
int  GestorFestival::getNumAsistentes() const { return static_cast<int>(asistentes.size()); }

// ---------- inicializacion ----------
void GestorFestival::inicializarEscenariosDefecto() {
    escenarios.clear();
    escenarios.push_back(make_unique<Escenario>(0, "Main", 4000));
    escenarios.push_back(make_unique<Escenario>(1, "Indie", 2000));
    escenarios.push_back(make_unique<Escenario>(2, "Electronica", 1500));
}

void GestorFestival::inicializarAgenda() {
    agenda.clear();
    agenda.resize(max(1, dias) * max(1, getNumEscenarios()));
    for (int d = 0; d < dias; ++d)
        for (int e = 0; e < getNumEscenarios(); ++e)
            agenda[idxAgenda(d, e)] = Concierto();
}

// ---------- Metodo añadir artistas ----------
bool GestorFestival::anadirArtista(const Artista& a) {
    for (auto& ptr : artistas) if (ptr->getId() == a.getId()) return false;
    artistas.push_back(make_unique<Artista>(a));
    return true;
}

// ---------- Metodo añadir escenario ----------
bool GestorFestival::anadirEscenario(const Escenario& e) {
    for (auto& ptr : escenarios) if (ptr->getId() == e.getId()) return false;
    escenarios.push_back(make_unique<Escenario>(e));
    return true;
}

// ---------- Metodo registrar asistente ----------
bool GestorFestival::registrarAsistente(const Asistente& a) {
    for (auto& ptr : asistentes) if (ptr->getId() == a.getId()) return false;
    asistentes.push_back(make_unique<Asistente>(a));
    return true;
}

// ---------- Metodo buscar artista por id (sobrecarga + wrappers) ----------
Artista* GestorFestival::buscarArtista(int id) {
    for (auto& p : artistas) if (p->getId() == id) return p.get();
    return nullptr;
}

// ---------- Metodo buscar artista por nombre (sobrecarga + wrappers) ----------
const Artista* GestorFestival::buscarArtista(const std::string& nombre) const {
    for (const auto& p : artistas) if (p->getNombre() == nombre) return p.get();
    return nullptr;
}

// Llamada al metodo
Artista* GestorFestival::buscarArtistaPorId(int id) {  // wrapper para codigo existente
    return buscarArtista(id);
}

// ---------- Metodo buscar escenario por id (sobrecarga + wrappers) ----------
Escenario* GestorFestival::buscarEscenario(int id) {
    for (auto& p : escenarios) if (p->getId() == id) return p.get();
    return nullptr;
}

// ---------- Metodo buscar escenario por nombre (sobrecarga + wrappers) ----------
const Escenario* GestorFestival::buscarEscenario(const std::string& nombre) const {
    for (const auto& p : escenarios) if (p->getNombre() == nombre) return p.get();
    return nullptr;
}

// Llamada al metodo
Escenario* GestorFestival::buscarEscenarioPorId(int id) { // wrapper
    return buscarEscenario(id);
}

// ---------- agenda ----------
int GestorFestival::idxAgenda(int d, int idEscenario) const {
    return d * getNumEscenarios() + idEscenario;
}

// Metodo encargado de comprobar si un artista ya tiene concierto ese dia
bool GestorFestival::artistaYaProgramadoEnDia(int idArtista, int d) const {
    if (d < 0 || d >= dias) return false;
    for (int e = 0; e < getNumEscenarios(); ++e) {
        const Concierto& c = agenda[idxAgenda(d, e)];
        if (c.esValido() && c.getArtista() && c.getArtista()->getId() == idArtista)
            return true;
    }
    return false;
}

// Metodo encargado de asignar un concierto
bool GestorFestival::asignarConcierto(int d, int idEsc, int idArt) {
    if (d < 0 || d >= dias) { cout << "dia invalido\n"; return false; }
    Escenario* esc = buscarEscenarioPorId(idEsc);
    Artista* art = buscarArtistaPorId(idArt);
    if (!esc || !art) { cout << "escenario o artista inexistente\n"; return false; }

    int k = idxAgenda(d, idEsc);
    if (k < 0 || k >= (int)agenda.size()) return false;

    if (agenda[k].esValido()) {
        cout << "ya hay concierto en ese dia/escenario\n";
        return false;
    }
    if (artistaYaProgramadoEnDia(idArt, d)) {
        cout << "el artista ya esta programado ese dia\n";
        return false;
    }
    if (art->getDemanda() > esc->getAforoMaximo()) {
        cout << "aviso: demanda (" << art->getDemanda()
            << ") supera aforo (" << esc->getAforoMaximo() << ")\n";
    }

    agenda[k].asignar(d, esc, art);
    return true;
}

// ---------- listados (muestra en pantalla la agenda de un dia ----------
void GestorFestival::listarAgendaDia(int d) const {
    if (d < 0 || d >= dias) { cout << "dia invalido\n"; return; }
    cout << "--- agenda dia " << d << " ---\n";
    for (int e = 0; e < getNumEscenarios(); ++e) {
        const Concierto& c = agenda[idxAgenda(d, e)];
        const string nombreEsc = (e < (int)escenarios.size() ? escenarios[e]->getNombre() : "?");
        if (c.esValido() && c.getArtista()) {
            cout << "[" << e << "] " << nombreEsc
                << " -> " << c.getArtista()->getNombre() << "\n";
        }
        else {
            cout << "[" << e << "] " << nombreEsc << " -> (libre)\n";
        }
    }
}

// LLamada al metodo
void GestorFestival::listarAgendaCompleta() const {
    for (int d = 0; d < dias; ++d) listarAgendaDia(d);
}

// Recorre los punteros de artista y llama al metodo mostrar informacion
void GestorFestival::listarArtistas() const {
    cout << "--- artistas ---\n";
    for (const auto& p : artistas) p->mostrarInfo();
}

// Recorre los punteros de escenario y llama al metodo mostrar informacion
void GestorFestival::listarEscenarios() const {
    cout << "--- escenarios ---\n";
    for (const auto& p : escenarios) p->mostrarInfo();
}

// Recorre los punteros de asistentes y llama al metodo mostrar informacion
void GestorFestival::listarAsistentes() const {
    cout << "--- asistentes ---\n";
    for (const auto& p : asistentes) {
        p->mostrarInfo();
        cout << "precio: " << p->calcularPrecio() << " EUR\n";
    }
}

// ---------- persistencia (metodo para guardar los datos) ----------
bool GestorFestival::guardar(const string& dir) const {
    ofstream fa(joinPath(dir, "artistas.txt"));
    ofstream fe(joinPath(dir, "escenarios.txt"));
    ofstream fs(joinPath(dir, "asistentes.txt"));
    ofstream fg(joinPath(dir, "agenda.txt"));
    if (!fa || !fe || !fs || !fg)
        throw runtime_error("No se pudieron abrir los archivos para escritura");

    // artistas: id;nombre;genero;duracion;demanda
    for (const auto& ptr : artistas) {
        const auto& a = *ptr;
        fa << a.getId() << ';' << a.getNombre() << ';'
            << a.getGenero() << ';' << a.getDuracion() << ';'
            << a.getDemanda() << '\n';
    }

    // escenarios: id;nombre;aforo
    for (const auto& ptr : escenarios) {
        const auto& e = *ptr;
        fe << e.getId() << ';' << e.getNombre() << ';'
            << e.getAforoMaximo() << '\n';
    }

    // asistentes: id;nombre;edad;tipo;estudiante;pagada
    for (const auto& ptr : asistentes) {
        const auto& s = *ptr;
        fs << s.getId() << ';' << s.getNombre() << ';'
            << 0 << ';'            // edad placeholder si no tienes getter
            << "Abono3" << ';'     // tipo placeholder
            << 0 << ';'            // estudiante placeholder
            << (s.getPagada() ? 1 : 0) << '\n';
    }

    // agenda: cabecera y filas
    fg << dias << ';' << getNumEscenarios() << '\n';
    for (int d = 0; d < dias; ++d) {
        for (int e = 0; e < getNumEscenarios(); ++e) {
            const Concierto& c = agenda[idxAgenda(d, e)];
            int idEsc = (e < (int)escenarios.size() ? escenarios[e]->getId() : e);
            int idArt = (c.esValido() && c.getArtista()) ? c.getArtista()->getId() : -1;
            fg << d << ';' << idEsc << ';' << idArt << ';' << (c.esValido() ? 1 : 0) << '\n';
        }
    }

    cout << "Datos guardados correctamente en carpeta: " << dir << endl;
    return true;
}

// Metodo encargado de cargar los datos
bool GestorFestival::cargar(const string& dir) {
    ifstream fa(joinPath(dir, "artistas.txt"));
    ifstream fe(joinPath(dir, "escenarios.txt"));
    ifstream fs(joinPath(dir, "asistentes.txt"));
    ifstream fg(joinPath(dir, "agenda.txt"));
    if (!fa || !fe || !fs || !fg)
        throw runtime_error("No se pudieron abrir los archivos para lectura");

    artistas.clear();
    escenarios.clear();
    asistentes.clear();
    agenda.clear();

    string lin, tok;

    // escenarios
    while (getline(fe, lin)) {
        if (lin.empty()) continue;
        stringstream ss(lin);
        string nom; int id, af;
        getline(ss, tok, ';'); id = stoi(tok);
        getline(ss, nom, ';');
        getline(ss, tok, ';'); af = stoi(tok);
        escenarios.push_back(make_unique<Escenario>(id, nom, af));
    }

    // artistas
    while (getline(fa, lin)) {
        if (lin.empty()) continue;
        stringstream ss(lin);
        string nom, gen; int id, dem; double dur;
        getline(ss, tok, ';'); id = stoi(tok);
        getline(ss, nom, ';');
        getline(ss, gen, ';');
        getline(ss, tok, ';'); dur = stod(tok);
        getline(ss, tok, ';'); dem = stoi(tok);
        artistas.push_back(make_unique<Artista>(id, nom, gen, dur, dem));
    }

    // asistentes
    while (getline(fs, lin)) {
        if (lin.empty()) continue;
        stringstream ss(lin);
        string nom, tipo; int id, edad, est, pag;
        getline(ss, tok, ';'); id = stoi(tok);
        getline(ss, nom, ';');
        getline(ss, tok, ';'); edad = stoi(tok);
        getline(ss, tipo, ';');
        getline(ss, tok, ';'); est = stoi(tok);
        getline(ss, tok, ';'); pag = stoi(tok);
        asistentes.push_back(make_unique<Asistente>(id, nom, edad, tipo, est != 0, pag != 0));
    }

    // agenda
    getline(fg, lin); // cabecera
    stringstream hs(lin); int nd, ne;
    getline(hs, tok, ';'); nd = stoi(tok);
    getline(hs, tok, ';'); ne = stoi(tok);
    dias = nd;
    inicializarAgenda();

    while (getline(fg, lin)) {
        if (lin.empty()) continue;
        stringstream ss(lin);
        int d, idEsc, idArt, v;
        getline(ss, tok, ';'); d = stoi(tok);
        getline(ss, tok, ';'); idEsc = stoi(tok);
        getline(ss, tok, ';'); idArt = stoi(tok);
        getline(ss, tok, ';'); v = stoi(tok);
        if (v != 0) {
            Escenario* esc = nullptr;
            Artista* art = nullptr;
            for (auto& p : escenarios) if (p->getId() == idEsc) { esc = p.get(); break; }
            for (auto& p : artistas)  if (p->getId() == idArt) { art = p.get(); break; }
            if (esc && art) agenda[idxAgenda(d, idEsc)].asignar(d, esc, art);
        }
    }

    cout << "Datos cargados correctamente desde carpeta: " << dir << endl;
    return true;
}

