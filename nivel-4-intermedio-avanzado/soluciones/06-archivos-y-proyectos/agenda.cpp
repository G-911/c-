// agenda.cpp — SOLUCIÓN del miniproyecto 4.6.
// Ábrela solo después de intentarlo de verdad.
#include "agenda.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool guardarNumeros(const vector<int>& numeros, const string& ruta) {
    ofstream archivo(ruta);          // abre (y vacía) el archivo para escribir
    if (!archivo) return false;      // no se pudo abrir: carpeta inexistente, sin permiso...
    for (int n : numeros) {
        archivo << n << "\n";
    }
    return true;                     // al salir, el destructor de ofstream cierra el archivo (RAII)
}

vector<int> cargarNumeros(const string& ruta) {
    vector<int> resultado;
    ifstream archivo(ruta);
    if (!archivo) return resultado;  // no existe: vector vacío
    int n;
    while (archivo >> n) {           // se detiene al llegar al final (o a algo que no es número)
        resultado.push_back(n);
    }
    return resultado;
}

bool guardarContactos(const vector<Contacto>& contactos, const string& ruta) {
    ofstream archivo(ruta);
    if (!archivo) return false;
    for (const Contacto& c : contactos) {
        archivo << c.nombre << ";" << c.telefono << "\n";
    }
    return true;
}

vector<Contacto> cargarContactos(const string& ruta) {
    vector<Contacto> resultado;
    ifstream archivo(ruta);
    if (!archivo) return resultado;
    string linea;
    while (getline(archivo, linea)) {          // getline: la línea ENTERA, con espacios
        size_t pos = linea.find(';');
        if (pos == string::npos) continue;     // vacía o sin ';': se ignora
        Contacto c;
        c.nombre = linea.substr(0, pos);
        c.telefono = linea.substr(pos + 1);    // "Sol;" → teléfono vacío
        resultado.push_back(c);
    }
    return resultado;
}
