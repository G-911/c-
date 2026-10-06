// SOLUCIÓN del Miniproyecto 4.4 — Una pila que avisa con excepciones
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 04-excepciones.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <stdexcept>   // out_of_range, invalid_argument
#include <string>
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen ahora mismo.
// Si al final no vale 0, hay una fuga de memoria.
int nodosVivos = 0;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class Pila {
private:
    Nodo* tope;   // el de arriba; nullptr si la pila está vacía

public:
    Pila() : tope(nullptr) {}

    ~Pila() {
        Nodo* actual = tope;
        while (actual != nullptr) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    bool vacia() const { return tope == nullptr; }

    int tamano() const {
        int n = 0;
        for (Nodo* p = tope; p != nullptr; p = p->siguiente) n++;
        return n;
    }

    void push(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = tope;
        tope = nuevo;
    }

    // 1) Sobre una pila vacía ya no hay «precondición»: avisa lanzando.
    int top() const {
        if (vacia()) throw out_of_range("top: la pila vacía no tiene tope");
        return tope->dato;
    }

    // 2) Lo mismo para pop: comprueba ANTES de tocar nada.
    void pop() {
        if (vacia()) throw out_of_range("pop: la pila vacía no tiene tope");
        Nodo* viejo = tope;
        tope = tope->siguiente;
        delete viejo;
    }
};

// 3) Atrapa el error de la pila y lo convierte en un valor por defecto.
int sacarOValor(Pila& p, int porDefecto) {
    try {
        int valor = p.top();   // si está vacía, salta directo al catch
        p.pop();
        return valor;
    } catch (const out_of_range&) {
        return porDefecto;
    }
}

// 4) Lanza tu propia excepción con un mensaje claro.
int dividir(int a, int b) {
    if (b == 0) throw invalid_argument("dividir: división entre cero");
    return a / b;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "top y pop:\n";
    {
        Pila p;
        p.push(1);
        p.push(2);
        p.push(3);
        comprobar(p.top() == 3, "push 1, 2, 3  ->  top = 3");
        p.pop();
        comprobar(p.top() == 2 && nodosVivos == 2, "pop  ->  top = 2 y quedan 2 nodos vivos");
    }
    comprobar(nodosVivos == 0, "la pila libera sus nodos al destruirse");

    cout << "pila vacía:\n";
    {
        Pila p;
        bool lanzo = false;
        string mensaje;
        try {
            p.pop();
        } catch (const out_of_range& e) {
            lanzo = true;
            mensaje = e.what();
        }
        comprobar(lanzo, "pop sobre vacía lanza out_of_range");
        comprobar(mensaje.find("pila vacía") != string::npos,
                  "el mensaje de pop dice \"pila vacía\"");

        lanzo = false;
        try {
            p.top();
        } catch (const out_of_range&) {
            lanzo = true;
        }
        comprobar(lanzo, "top sobre vacía lanza out_of_range");

        p.push(7);
        comprobar(p.top() == 7, "después del error la pila sigue funcionando");
    }

    cout << "sacarOValor:\n";
    {
        Pila p;
        p.push(5);
        int primero = sacarOValor(p, -1);
        int segundo = sacarOValor(p, -1);
        comprobar(primero == 5 && segundo == -1, "[5]  ->  5, y luego -1 porque quedó vacía");
    }

    cout << "dividir:\n";
    comprobar(dividir(10, 2) == 5, "dividir(10, 2) = 5");
    bool lanzo = false;
    try {
        dividir(1, 0);
    } catch (const invalid_argument&) {
        lanzo = true;
    }
    comprobar(lanzo, "dividir(1, 0) lanza invalid_argument");

    comprobar(nodosVivos == 0, "no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 4.4 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
