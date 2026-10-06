// Miniproyecto 4.1 — Una Pila<T> que sirve para todo
// ---------------------------------------------------------------
// Completa las partes marcadas con TODO. No toques main().
// La Pila es la de la lección 3.6, ya convertida en plantilla:
// vacia(), tamano() y el destructor vienen hechos.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 01-plantillas.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1) Función plantilla: el mayor de dos valores del MISMO tipo T.
//    Pista: una línea con if o con el operador ternario ? :
template <typename T>
T maximo(T a, T b) {
    (void)b;    // TODO: borra esta línea
    return a;   // TODO: devuelve el mayor de a y b
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
    //    Pista: copia el push de la 3.6 y cambia Nodo por Nodo<T>.
    void push(const T& valor) {
        (void)valor;   // TODO: borra esta línea y escribe el método
    }

    // 3) pop: sobre una pila vacía no hace nada.
    //    Pista: guarda el nodo viejo, mueve el tope, y después delete.
    void pop() {
        // TODO
    }

    // 4) top: precondición, la pila NO está vacía (quien llama comprueba vacia()).
    //    Pista: ¿dónde está el dato del nodo de arriba?
    T top() const {
        return T{};   // TODO: T{} es «el valor vacío de T» (0, "", ...). Cámbialo.
    }
};

// 5) Función plantilla que USA la clase plantilla: invierte un vector
//    metiendo todo en una Pila<T> y sacándolo después.
//    Pista: crea una Pila<T>, haz push de cada elemento, y luego
//    mientras no esté vacía: push_back(top()) al resultado y pop().
template <typename T>
vector<T> invertir(const vector<T>& v) {
    (void)v;       // TODO: borra esta línea
    return {};     // TODO: devuelve el vector al revés
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
