// SOLUCIÓN — idéntico al de ejercicios/: las respuestas están en agenda.cpp.
// Miniproyecto 4.6 — Agenda en archivos (proyecto de 3 archivos)
// ---------------------------------------------------------------
// Este proyecto tiene TRES archivos de código:
//   agenda.h    → declaraciones (no tocar)
//   agenda.cpp  → AQUÍ completas las 4 funciones con TODO
//   main.cpp    → pruebas automáticas (no tocar)
//
// Compilar y probar (en la terminal, dentro de ESTA carpeta), de una de tres formas:
//   a) a mano:   g++ -std=c++17 -Wall main.cpp agenda.cpp -o prog && ./prog
//   b) con make: make && ./prog
//   c) con CMake (opcional): cmake -S . -B build && cmake --build build && ./build/prog
//
// Los archivos de datos se crean en /tmp, así no ensucian tu carpeta.
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <cstdio>     // remove(): borra un archivo
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "agenda.h"
using namespace std;

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    const string rutaNum = "/tmp/curso-cpp-46-numeros.txt";
    const string rutaCon = "/tmp/curso-cpp-46-contactos.txt";
    remove(rutaNum.c_str());
    remove(rutaCon.c_str());

    cout << "numeros:\n";
    comprobar(guardarNumeros({4, -2, 15}, rutaNum), "guardarNumeros devuelve true");
    vector<int> leidos = cargarNumeros(rutaNum);
    comprobar(leidos == vector<int>{4, -2, 15}, "guardar {4,-2,15} y cargar da lo mismo");
    comprobar(guardarNumeros({}, rutaNum) && cargarNumeros(rutaNum).empty(),
              "guardar un vector vacío deja el archivo vacío");
    comprobar(cargarNumeros("/tmp/curso-cpp-46-no-existe.txt").empty(),
              "cargar un archivo que no existe da vector vacío");
    comprobar(!guardarNumeros({1}, "/tmp/carpeta-que-no-existe-46/x.txt"),
              "guardar en una carpeta que no existe devuelve false");

    cout << "contactos:\n";
    vector<Contacto> agenda = {{"Ana Pérez", "0414-555"}, {"Luis", "0212-777"}};
    comprobar(guardarContactos(agenda, rutaCon), "guardarContactos devuelve true");

    ifstream crudo(rutaCon);
    string primera;
    getline(crudo, primera);
    crudo.close();
    comprobar(primera == "Ana Pérez;0414-555", "la primera línea es  Ana Pérez;0414-555");

    vector<Contacto> c = cargarContactos(rutaCon);
    comprobar(c.size() == 2 && c[0].nombre == "Ana Pérez" && c[1].telefono == "0212-777",
              "cargar devuelve los 2 contactos (nombre con espacio incluido)");

    ofstream sucio(rutaCon);   // escribimos un archivo "a mano" con líneas raras
    sucio << "Eva;111\n\nlinea sin punto y coma\nSol;\n";
    sucio.close();
    vector<Contacto> s = cargarContactos(rutaCon);
    comprobar(s.size() == 2 && s[0].nombre == "Eva" && s[1].nombre == "Sol" && s[1].telefono.empty(),
              "ignora líneas vacías o sin ';' (y acepta teléfono vacío)");

    remove(rutaNum.c_str());
    remove(rutaCon.c_str());
    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 4.6 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗ en agenda.cpp.\n");
    return fallos == 0 ? 0 : 1;
}
