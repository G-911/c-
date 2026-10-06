// SOLUCIÓN del Miniproyecto 4.1 — Una Pila<T> que sirve para todo
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 01-plantillas.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1) Función plantilla: el mayor de dos valores del MISMO tipo T.
template <typename T>
T maximo(T a, T b) {
    return (a > b) ? a : b;
}

// Truco didáctico: cuenta cuántos nodos existen ahora mismo,
// sean del tipo que sean. Si al final no vale 0, hay una fuga de memoria.
int nodosVivos = 0;

// El Nodo de siempre, pero el dato es de tipo T.
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;   // dentro de la plantilla, «Nodo» ya significa Nodo<T>
    Nodo(const T& d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

template <typename T>
class Pila {
private:
    Nodo<T>* tope;   // el de arriba; nullptr si la pila está vacía

public:
    Pila() : tope(nullptr) {}

    // No se copia: así nadie hace dos delete del mismo nodo (regla de tres, 3.5).
    Pila(const Pila&) = delete;
    Pila& operator=(const Pila&) = delete;

    ~Pila() {
        Nodo<T>* actual = tope;
        while (actual != nullptr) {
            Nodo<T>* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    bool vacia() const { return tope == nullptr; }

    int tamano() const {
        int n = 0;
        for (Nodo<T>* p = tope; p != nullptr; p = p->siguiente) n++;
        return n;
    }

    // 2) push: igual que con int, cambiando int por T.
    void push(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        nuevo->siguiente = tope;
        tope = nuevo;
    }

    // 3) pop: sobre una pila vacía no hace nada.
    void pop() {
        if (vacia()) return;
        Nodo<T>* viejo = tope;
        tope = tope->siguiente;   // muevo el tope ANTES de borrar
        delete viejo;
    }

    // 4) top: precondición, la pila NO está vacía (quien llama comprueba vacia()).
    T top() const { return tope->dato; }
};

// 5) Función plantilla que USA la clase plantilla: invierte un vector
//    metiendo todo en una Pila<T> y sacándolo después.
template <typename T>
vector<T> invertir(const vector<T>& v) {
    Pila<T> p;
    for (const T& x : v) p.push(x);
    vector<T> resultado;
    while (!p.vacia()) {
        resultado.push_back(p.top());
        p.pop();
    }
    return resultado;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "maximo:\n";
    comprobar(maximo(3, 8) == 8, "maximo(3, 8) es 8");
    comprobar(maximo(2.5, -1.0) == 2.5, "maximo(2.5, -1.0) es 2.5");
    comprobar(maximo(string("ana"), string("beto")) == "beto",
              "maximo(\"ana\", \"beto\") es \"beto\" (orden alfabético)");

    cout << "Pila<int>:\n";
    {
        Pila<int> p;
        p.push(1); p.push(2); p.push(3);
        comprobar(!p.vacia() && p.tamano() == 3, "tras 3 push, tamano es 3");
        comprobar(!p.vacia() && p.top() == 3, "el tope es el último que entró (3)");
        p.pop();
        comprobar(!p.vacia() && p.top() == 2 && p.tamano() == 2, "tras un pop, el tope es 2");
        p.pop(); p.pop(); p.pop();   // el último pop es sobre una pila vacía
        comprobar(p.vacia() && p.tamano() == 0, "pop de más sobre pila vacía no rompe nada");
    }

    cout << "Pila<string>:\n";
    {
        Pila<string> p;
        p.push("hola");
        p.push("mundo");
        comprobar(!p.vacia() && p.top() == "mundo", "con string también funciona: tope \"mundo\"");
    }

    cout << "invertir:\n";
    comprobar(invertir(vector<int>{1, 2, 3}) == vector<int>{3, 2, 1}, "{1,2,3} -> {3,2,1}");
    comprobar(invertir(vector<char>{'a', 'b'}) == vector<char>{'b', 'a'}, "{'a','b'} -> {'b','a'}");
    comprobar(invertir(vector<int>{}).empty(), "un vector vacío sigue vacío");

    comprobar(nodosVivos == 0, "no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 4.1 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
