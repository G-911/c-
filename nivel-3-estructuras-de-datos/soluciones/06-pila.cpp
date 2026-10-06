// SOLUCIÓN del Miniproyecto 3.6 — Pila y paréntesis balanceados
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 06-pila.cpp -o prog && ./prog
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

    // push = apilar: igual que insertarAlInicio de la lista.
    void push(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = tope;   // el nuevo apunta al que estaba arriba
        tope = nuevo;              // y ahora el de arriba es el nuevo
    }

    // pop = desapilar: quita el de arriba. Sobre una pila vacía no hace nada.
    void pop() {
        if (vacia()) return;
        Nodo* viejo = tope;        // guardo el que voy a borrar
        tope = tope->siguiente;    // muevo el tope ANTES de borrar
        delete viejo;
    }
};

// Ya hecha: ¿cierra «cierra» al que abrió «abre»?
// (La pila guarda int; un char cabe en un int sin problema.)
bool esPareja(int abre, char cierra) {
    return (abre == '(' && cierra == ')') ||
           (abre == '[' && cierra == ']') ||
           (abre == '{' && cierra == '}');
}

bool balanceado(string texto) {
    Pila p;
    for (int i = 0; i < (int)texto.size(); i++) {
        char c = texto[i];
        if (c == '(' || c == '[' || c == '{') {
            p.push(c);                                    // abre: lo apilo
        } else if (c == ')' || c == ']' || c == '}') {
            if (p.vacia()) return false;                  // cierra algo que nadie abrió
            if (!esPareja(p.top(), c)) return false;      // cierra el que no toca
            p.pop();                                      // pareja correcta: la quito
        }
        // cualquier otro carácter se ignora
    }
    return p.vacia();   // si sobra alguno abierto, no está balanceado
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
