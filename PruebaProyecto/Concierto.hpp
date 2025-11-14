#pragma once

// forward declarations para evitar dependencias circulares
class Artista;
class Escenario;

class Concierto {
private:
    int dia;                     // dia del festival (0..N-1)
    const Escenario* escenario;  // puntero al escenario (no dueno)
    const Artista* artista;      // puntero al artista (no dueno)
    bool valido;                 // indica si hay concierto asignado

public:
    // Constructores
    Concierto();                                                     // por defecto (libre)
    Concierto(int dia, const Escenario* escenario, const Artista* artista); // asignado

    // Metodos
    void asignar(int nuevoDia, const Escenario* escenario, const Artista* artista);
    void limpiar();
    void mostrarInfo() const;

    // Getters
    int getDia() const;
    const Escenario* getEscenario() const;
    const Artista* getArtista() const;
    bool esValido() const;
};
