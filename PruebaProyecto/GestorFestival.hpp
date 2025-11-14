#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Artista.hpp"
#include "Escenario.hpp"
#include "Asistente.hpp"
#include "Concierto.hpp"

class GestorFestival {
private:
    std::string nombre;
    int dias;

    // almacenamos objetos; expondremos punteros no duenos a los mismos
    std::vector<std::unique_ptr<Artista>>   artistas;
    std::vector<std::unique_ptr<Escenario>> escenarios;
    std::vector<std::unique_ptr<Asistente>> asistentes;


    // agenda de tamano dias * escenarios.size()
    std::vector<Concierto> agenda;

public:
    // constantes utiles
    static constexpr int DIAS_DEFECTO = 3;
    static constexpr double DESCUENTO_ESTUDIANTE = 0.80; // 20%


    // ctor
    explicit GestorFestival(std::string nombre, int dias = DIAS_DEFECTO);

    // info basica
    const std::string& getNombre() const;
    int  getDias() const;
    int  getNumEscenarios() const;
    int  getNumArtistas() const;
    int  getNumAsistentes() const;

    // init
    void inicializarEscenariosDefecto(); // crea Main/Indie/Electronica
    void inicializarAgenda();            // limpia y redimensiona agenda

    // altas
    bool anadirArtista(const Artista& a);
    bool anadirEscenario(const Escenario& e);
    bool registrarAsistente(const Asistente& a);

    // busquedas por id
    Artista* buscarArtistaPorId(int id);
    Escenario* buscarEscenarioPorId(int id);

    // sobrecarga: buscar por id o por nombre
    Artista* buscarArtista(int id);
    const Artista* buscarArtista(const std::string& nombre) const;

    Escenario* buscarEscenario(int id);
    const Escenario* buscarEscenario(const std::string& nombre) const;


    // agenda
    bool asignarConcierto(int dia, int idEscenario, int idArtista); // valida hueco y duplicados
    void listarAgendaDia(int dia) const;
    void listarAgendaCompleta() const;

    // listados
    void listarArtistas() const;
    void listarEscenarios() const;
    void listarAsistentes() const;

    // persistencia simple en carpeta (csv basico)
    bool guardar(const std::string& carpeta) const;
    bool cargar(const std::string& carpeta);

private:
    // util
    int idxAgenda(int dia, int idEscenario) const;   // posicion lineal en agenda
    bool artistaYaProgramadoEnDia(int idArtista, int dia) const;
};
