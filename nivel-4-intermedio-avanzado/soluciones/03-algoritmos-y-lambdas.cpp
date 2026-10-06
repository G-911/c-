// SOLUCIÓN del Miniproyecto 4.3 — Las notas del curso, sin bucles a mano
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 03-algoritmos-y-lambdas.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <algorithm>   // sort, find_if, count_if, for_each, transform
#include <iostream>
#include <iterator>    // back_inserter
#include <numeric>     // accumulate  (¡no está en <algorithm>!)
#include <string>
#include <vector>
using namespace std;

struct Alumno {
    string nombre;
    double nota;   // de 0 a 20
};

// 1) Ordena de MAYOR a menor nota. Si dos tienen la misma nota,
//    va primero el nombre que va antes en el alfabeto.
void ordenarPorNota(vector<Alumno>& v) {
    sort(v.begin(), v.end(), [](const Alumno& a, const Alumno& b) {
        if (a.nota != b.nota) return a.nota > b.nota;   // ¿a va ANTES que b?
        return a.nombre < b.nombre;
    });
}

// 2) Cuántos tienen nota >= minimo.
int contarAprobados(const vector<Alumno>& v, double minimo) {
    return count_if(v.begin(), v.end(), [minimo](const Alumno& a) {
        return a.nota >= minimo;   // minimo viene de fuera: hay que capturarlo
    });
}

// 3) La nota media. Con el vector vacío devuelve 0.
double promedio(const vector<Alumno>& v) {
    if (v.empty()) return 0.0;
    double suma = accumulate(v.begin(), v.end(), 0.0,   // 0.0, NO 0
        [](double acumulado, const Alumno& a) { return acumulado + a.nota; });
    return suma / v.size();
}

// 4) Solo los nombres, en el mismo orden.
vector<string> nombres(const vector<Alumno>& v) {
    vector<string> resultado;
    transform(v.begin(), v.end(), back_inserter(resultado),
              [](const Alumno& a) { return a.nombre; });
    return resultado;
}

// 5) ¿Hay alguien con ese nombre?
bool existe(const vector<Alumno>& v, const string& nombre) {
    auto it = find_if(v.begin(), v.end(), [&nombre](const Alumno& a) {
        return a.nombre == nombre;
    });
    return it != v.end();
}

// 6) Suma «puntos» a todas las notas, sin pasar de 20.
void subirNotas(vector<Alumno>& v, double puntos) {
    for_each(v.begin(), v.end(), [puntos](Alumno& a) {   // Alumno& para poder cambiarlo
        a.nota = min(20.0, a.nota + puntos);
    });
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

vector<Alumno> curso() {
    return {{"Luis", 12}, {"Ana", 18}, {"Beto", 9.5}, {"Carla", 18}, {"Dani", 15}};
}

int main() {
    cout << "ordenarPorNota:\n";
    vector<Alumno> v = curso();
    ordenarPorNota(v);
    comprobar(v[0].nombre == "Ana" && v[1].nombre == "Carla",
              "primero Ana y Carla (18), empatadas en orden alfabético");
    comprobar(v[4].nombre == "Beto", "el último es Beto (9.5)");

    cout << "contarAprobados:\n";
    comprobar(contarAprobados(curso(), 10) == 4, "con mínimo 10 aprueban 4");
    comprobar(contarAprobados(curso(), 18) == 2, "con mínimo 18 aprueban 2 (el >= cuenta)");

    cout << "promedio:\n";
    comprobar(promedio(curso()) == 14.5, "la media de 12, 18, 9.5, 18 y 15 es 14.5");
    comprobar(promedio({}) == 0.0, "sin alumnos, la media es 0");

    cout << "nombres:\n";
    comprobar(nombres(curso()) == vector<string>{"Luis", "Ana", "Beto", "Carla", "Dani"},
              "devuelve los 5 nombres en el mismo orden");

    cout << "existe:\n";
    comprobar(existe(curso(), "Carla"), "Carla está");
    comprobar(!existe(curso(), "Zoe") && !existe({}, "Ana"), "Zoe no está; en un curso vacío nadie");

    cout << "subirNotas:\n";
    vector<Alumno> w = curso();
    subirNotas(w, 3);
    comprobar(w[0].nota == 15 && w[2].nota == 12.5, "Luis 12 -> 15 y Beto 9.5 -> 12.5");
    comprobar(w[1].nota == 20 && w[3].nota == 20, "Ana y Carla 18 -> 20 (tope, no 21)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 4.3 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
