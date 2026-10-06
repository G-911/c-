// agenda.cpp — aquí van las DEFINICIONES de lo que agenda.h promete.
// Completa las cuatro funciones marcadas con TODO.
#include "agenda.h"   // comillas: archivo NUESTRO. <...>: de la biblioteca.
#include <fstream>
#include <string>
#include <vector>
using namespace std;  // en un .cpp sí está bien: no se contagia a nadie

// 1) Abre un ofstream con la ruta. Si no se abrió (!archivo), devuelve false.
//    Escribe cada número seguido de "\n". Devuelve true.
bool guardarNumeros(const vector<int>& numeros, const string& ruta) {
    (void)numeros; (void)ruta;  // borra esta línea al empezar (solo evita un aviso)
    // TODO
    return false;
}

// 2) Abre un ifstream. Si no se abrió, devuelve el vector vacío.
//    Pista: while (archivo >> n) { ... }  lee números hasta que se acaben.
vector<int> cargarNumeros(const string& ruta) {
    vector<int> resultado;
    (void)ruta;  // borra esta línea al empezar
    // TODO
    return resultado;
}

// 3) Igual que guardarNumeros, pero cada línea es:  nombre;telefono
bool guardarContactos(const vector<Contacto>& contactos, const string& ruta) {
    (void)contactos; (void)ruta;  // borra esta línea al empezar
    // TODO
    return false;
}

// 4) Lee LÍNEA A LÍNEA con getline(archivo, linea).
//    En cada línea busca el ';' con linea.find(';').
//    Si no lo hay (string::npos), sáltate la línea (continue).
//    Si lo hay: nombre = linea.substr(0, pos), telefono = linea.substr(pos + 1).
vector<Contacto> cargarContactos(const string& ruta) {
    vector<Contacto> resultado;
    (void)ruta;  // borra esta línea al empezar
    // TODO
    return resultado;
}
