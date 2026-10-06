// Miniproyecto 3.6 — Pila y paréntesis balanceados
// ---------------------------------------------------------------
// Completa los TRES trozos marcados con TODO: push, pop y balanceado.
// Lo demás de la clase Pila ya está hecho. No toques main().
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 06-pila.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen ahora mismo.
// Sube al crear un nodo (new) y baja al borrarlo (delete).
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

    // Precondición: la pila NO está vacía. Quien llama comprueba vacia() antes.
    int top() const { return tope->dato; }

    // 1) push = apilar: pone «valor» arriba del todo.
    //    Es lo mismo que insertarAlInicio de la lista (lección 3.2).
    //    Pista: crea el nodo con new, que apunte al tope actual, y mueve el tope.
    void push(int valor) {
        (void)valor;   // esta línea solo calla un aviso del compilador: bórrala al empezar
        // TODO
    }

    // 2) pop = desapilar: quita el de arriba y LIBERA su nodo con delete.
    //    Si la pila está vacía, no hace nada.
    //    Pista: guarda el tope en un apuntador auxiliar ANTES de moverlo.
    void pop() {
        // TODO
    }
};

// Ya hecha: ¿cierra «cierra» al que abrió «abre»?
// (La pila guarda int; un char cabe en un int sin problema.)
bool esPareja(int abre, char cierra) {
    return (abre == '(' && cierra == ')') ||
           (abre == '[' && cierra == ']') ||
           (abre == '{' && cierra == '}');
}

// 3) Devuelve true si los ( ) [ ] { } del texto están bien cerrados.
//    Recorre el texto carácter a carácter (texto[i]):
//      - si abre ( [ {         -> push
//      - si cierra ) ] }       -> si la pila está vacía, o el top no es su
//                                 pareja (usa esPareja), devuelve false;
//                                 si es su pareja, pop
//      - cualquier otra letra  -> ignórala
//    Al terminar, está balanceado solo si la pila quedó vacía.
bool balanceado(string texto) {
    (void)texto;   // bórrala al empezar
    return false;  // TODO
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "Pila:\n";
    {
        Pila p;
        comprobar(p.vacia() && p.tamano() == 0, "una pila nueva está vacía");
        p.push(1);
        p.push(2);
        p.push(3);
        comprobar(!p.vacia() && p.top() == 3 && p.tamano() == 3,
                  "push 1, 2, 3  ->  top = 3 y tamano = 3");
        p.pop();
        comprobar(!p.vacia() && p.top() == 2 && p.tamano() == 2,
                  "pop  ->  top = 2 y tamano = 2");
        comprobar(nodosVivos == 2, "pop libera el nodo que quita (quedan 2 vivos)");
        p.pop();
        p.pop();
        p.pop();   // una de más: sobre vacía no debe hacer nada
        comprobar(p.vacia() && nodosVivos == 0, "pop hasta vaciar (y uno de más) no se cae");
        p.push(5);
        p.push(6);
    }   // aquí se destruye la pila
    comprobar(nodosVivos == 0, "no quedan nodos sin liberar");

    cout << "balanceado:\n";
    comprobar(balanceado("([]{})") == true,         "\"([]{})\" está balanceado");
    comprobar(balanceado("f(a[i]) + {x}") == true,  "\"f(a[i]) + {x}\" está balanceado (ignora letras)");
    comprobar(balanceado("([)]") == false,          "\"([)]\" NO: se cruzan");
    comprobar(balanceado("((") == false,            "\"((\" NO: sobran abiertos");
    comprobar(balanceado("())") == false,           "\"())\" NO: cierra uno que nadie abrió");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.6 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
