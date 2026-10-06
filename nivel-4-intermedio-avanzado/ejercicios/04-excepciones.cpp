// Miniproyecto 4.4 — Una pila que avisa con excepciones
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO. No toques main().
// En el Nivel 3, pop() sobre una pila vacía «no hacía nada» y top()
// tenía una precondición. Ahora las dos van a AVISAR lanzando una excepción.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 04-excepciones.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
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

    // 1) Devuelve el dato de arriba.
    //    Si la pila está vacía, LANZA out_of_range con un mensaje que
    //    contenga "pila vacía", por ejemplo "top: la pila vacía no tiene tope".
    //    Pista: if (vacia()) throw out_of_range("...");
    int top() const {
        // TODO (borra el return 0 cuando lo escribas)
        return 0;
    }

    // 2) Quita el de arriba y libera su nodo (como en la lección 3.6).
    //    Si la pila está vacía, LANZA out_of_range; el mensaje debe
    //    contener "pila vacía".
    //    Pista: comprueba ANTES de tocar el tope.
    void pop() {
        // TODO
    }
};

// 3) Saca el de arriba y devuélvelo. Si la pila está vacía, devuelve
//    porDefecto. NO preguntes vacia(): usa try/catch.
//    Pista: dentro del try, top() y luego pop(); en
//    catch (const out_of_range&) devuelve porDefecto.
int sacarOValor(Pila& p, int porDefecto) {
    (void)p; (void)porDefecto;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return 0;
}

// 4) Devuelve a / b. Si b es 0, lanza invalid_argument
//    con el mensaje que quieras.
int dividir(int a, int b) {
    (void)a; (void)b;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return 0;
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
