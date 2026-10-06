// agenda.h — la "carta de presentación" de la agenda.
// Aquí solo se DECLARA qué hay (struct y prototipos). El código va en agenda.cpp.
//
// Las tres líneas #ifndef / #define / #endif son el "include guard":
// si dos archivos incluyen agenda.h, el compilador solo lo lee una vez.
// (Equivale a poner #pragma once en la primera línea.)
#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <vector>

struct Contacto {
    std::string nombre;
    std::string telefono;
};

// En un .h NO se escribe "using namespace std;": se colaría en todos los
// archivos que lo incluyan. Por eso aquí va std:: delante.

// Guarda un número por línea. Devuelve false si no pudo abrir el archivo.
bool guardarNumeros(const std::vector<int>& numeros, const std::string& ruta);

// Lee un número por línea. Si el archivo no existe, devuelve un vector vacío.
std::vector<int> cargarNumeros(const std::string& ruta);

// Guarda un contacto por línea con el formato  nombre;telefono
bool guardarContactos(const std::vector<Contacto>& contactos, const std::string& ruta);

// Lee el formato de arriba. Ignora las líneas vacías o sin ';'.
std::vector<Contacto> cargarContactos(const std::string& ruta);

#endif
