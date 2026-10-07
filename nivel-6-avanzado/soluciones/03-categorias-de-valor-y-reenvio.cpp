// SOLUCIÓN del Miniproyecto 6.3 — Reenviar sin copiar de más
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Rastreado es un objeto que CUENTA cuántas veces lo copian y cuántas
// lo mueven. Tú escribes funciones que lo pasan de un sitio a otro y
// las pruebas miran los contadores: si copias donde había que mover,
// lo notan.
//
// Compilar y probar (en la terminal, dentro de esta carpeta).
// Basta C++17; usamos el comando del Nivel 6:
//   g++ -std=c++17 -Wall -pthread 03-categorias-de-valor-y-reenvio.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <utility>   // std::move, std::forward
#include <vector>
using namespace std;

int copias = 0;        // cuántas veces se ha COPIADO un Rastreado
int movimientos = 0;   // cuántas veces se ha MOVIDO un Rastreado

void reiniciar() { copias = 0; movimientos = 0; }

struct Rastreado {
    string nombre;

    Rastreado(const string& n) : nombre(n) {}

    Rastreado(const Rastreado& otro) : nombre(otro.nombre) { copias++; }
    Rastreado(Rastreado&& otro) noexcept : nombre(std::move(otro.nombre)) { movimientos++; }

    Rastreado& operator=(const Rastreado& otro) {
        nombre = otro.nombre;
        copias++;
        return *this;
    }
    Rastreado& operator=(Rastreado&& otro) noexcept {
        nombre = std::move(otro.nombre);
        movimientos++;
        return *this;
    }
};

// 1) Mete 'obj' al final de 'v' con REENVÍO PERFECTO:
//    - si te pasan un lvalue (una variable), push_back debe COPIARLO;
//    - si te pasan un rvalue (un temporal o std::move(x)), debe MOVERLO.
//    Una sola línea.
//    Pista: v.push_back(std::forward<T>(obj));
template <typename T>
void guardar(vector<Rastreado>& v, T&& obj) {
    // forward devuelve a obj la categoría con la que llegó:
    // T = Rastreado&  (variable)  -> sigue siendo lvalue -> push_back copia
    // T = Rastreado   (temporal)  -> vuelve a ser rvalue -> push_back mueve
    v.push_back(std::forward<T>(obj));
}

// 2) Un Envoltorio guarda un Rastreado dentro.
//    El primer constructor (copia) ya está bien.
//    El SEGUNDO tiene un error: recibe un rvalue pero lo COPIA.
//    Arréglalo para que mueva.
//    Pista: dentro del constructor, 'r' tiene nombre... ¿qué categoría es?
struct Envoltorio {
    Rastreado dentro;

    Envoltorio(const Rastreado& r) : dentro(r) {}

    // r es de tipo Rastreado&&, pero TIENE NOMBRE: como expresión es un lvalue.
    // Sin std::move se elegiría el constructor de copia de Rastreado.
    Envoltorio(Rastreado&& r) : dentro(std::move(r)) {}
};

// 3) Una fábrica: construye un T pasándole 'arg' con reenvío perfecto,
//    y lo devuelve por valor.
//    Ejemplo: fabricar<Envoltorio>(r) debe llamar a Envoltorio(const Rastreado&)
//    si r es una variable, y a Envoltorio(Rastreado&&) si es un temporal.
//    Pista: return T(std::forward<A>(arg));
template <typename T, typename A>
T fabricar(A&& arg) {
    // Se devuelve un temporal: la elisión de copia está garantizada (C++17),
    // así que no se añade ningún movimiento al devolver.
    return T(std::forward<A>(arg));
}

// 4) Añade al final de 'v' un Rastreado con ese nombre SIN copiarlo
//    ni moverlo: que se construya directamente dentro del vector.
//    Pista: emplace_back recibe los argumentos del CONSTRUCTOR.
void agregarEnSitio(vector<Rastreado>& v, const string& nombre) {
    // emplace_back reenvía 'nombre' al constructor Rastreado(const string&)
    // y construye el objeto directamente en su hueco del vector.
    v.emplace_back(nombre);
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "guardar (reenvío perfecto):\n";
    {
        vector<Rastreado> v;
        v.reserve(10);   // así el vector no se muda y no ensucia los contadores
        Rastreado r("ana");

        reiniciar();
        guardar(v, r);
        comprobar(v.size() == 1 && copias == 1 && movimientos == 0,
                  "con una variable: 1 copia, 0 movimientos");
        comprobar(r.nombre == "ana", "la variable original no se toca");

        reiniciar();
        guardar(v, Rastreado("beto"));
        comprobar(v.size() == 2 && copias == 0 && movimientos == 1 && v[1].nombre == "beto",
                  "con un temporal: 0 copias, 1 movimiento");

        reiniciar();
        guardar(v, std::move(r));
        comprobar(v.size() == 3 && copias == 0 && movimientos == 1 && v[2].nombre == "ana",
                  "con std::move(r): 0 copias, 1 movimiento");
    }

    cout << "Envoltorio:\n";
    {
        reiniciar();
        Envoltorio e(Rastreado("caja"));
        comprobar(copias == 0 && movimientos == 1 && e.dentro.nombre == "caja",
                  "desde un temporal: mueve, no copia");
    }

    cout << "fabricar:\n";
    {
        Rastreado r("dani");
        reiniciar();
        Envoltorio e1 = fabricar<Envoltorio>(r);
        comprobar(copias == 1 && movimientos == 0 && e1.dentro.nombre == "dani",
                  "fabricar con una variable: 1 copia");
        comprobar(r.nombre == "dani", "y la variable sigue intacta");

        reiniciar();
        Envoltorio e2 = fabricar<Envoltorio>(Rastreado("eva"));
        comprobar(copias == 0 && movimientos == 1 && e2.dentro.nombre == "eva",
                  "fabricar con un temporal: 0 copias, 1 movimiento");
    }

    cout << "agregarEnSitio (emplace_back):\n";
    {
        vector<Rastreado> v;
        v.reserve(10);
        reiniciar();
        agregarEnSitio(v, "fede");
        comprobar(v.size() == 1 && v[0].nombre == "fede", "el vector tiene a fede");
        comprobar(copias == 0 && movimientos == 0, "sin copias ni movimientos");
    }

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.3 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
