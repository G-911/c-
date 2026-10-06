// Miniproyecto 4.7 — Una Pila que se MUEVE en vez de copiarse
// ---------------------------------------------------------------
// La Pila ya trae la regla de tres de la lección 3.5 (destructor, constructor
// de copia y operator= de copia). Tú le añades las dos piezas que faltan para
// la regla de cinco, y una función que use std::move.
//
// Completa las TRES partes marcadas con TODO. No toques main().
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 07-semantica-de-movimiento.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <utility>   // std::move
#include <vector>
using namespace std;

int nodosVivos = 0;      // cuántos nodos existen ahora mismo
int nodosCopiados = 0;   // cuántos nodos se han COPIADO desde el principio

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class Pila {
    Nodo* tope = nullptr;
    int n = 0;

    void liberar() {                        // borra todos los nodos
        while (tope != nullptr) {
            Nodo* viejo = tope;
            tope = tope->siguiente;
            delete viejo;
        }
        n = 0;
    }

    void copiarDe(const Pila& otra) {       // copia PROFUNDA, en el mismo orden
        Nodo* ultimo = nullptr;
        for (Nodo* p = otra.tope; p != nullptr; p = p->siguiente) {
            Nodo* nuevo = new Nodo(p->dato);
            nodosCopiados++;
            if (ultimo == nullptr) tope = nuevo; else ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        n = otra.n;
    }

public:
    Pila() {}
    ~Pila() { liberar(); }

    // --- Regla de tres (ya hecha, lección 3.5) ---
    Pila(const Pila& otra) { copiarDe(otra); }
    Pila& operator=(const Pila& otra) {
        if (this != &otra) { liberar(); copiarDe(otra); }
        return *this;
    }

    // --- Lo que añades tú: las dos piezas de MOVIMIENTO ---

    // 1) Constructor de movimiento: "róbale" los nodos a 'otra'.
    //    - Toma su tope y su n.
    //    - Deja a 'otra' VACÍA y válida: tope = nullptr, n = 0.
    //    No crees ni un nodo nuevo.
    Pila(Pila&& otra) noexcept {
        (void)otra;  // borra esta línea al empezar (solo evita un aviso)
        // TODO
    }

    // 2) Asignación por movimiento:  a = std::move(b);
    //    - Si this == &otra, no hagas nada.
    //    - Si no: libera TUS nodos (liberar()), roba los de 'otra'
    //      y déjala vacía, igual que en el 1).
    Pila& operator=(Pila&& otra) noexcept {
        (void)otra;  // borra esta línea al empezar
        // TODO
        return *this;
    }

    void push(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = tope;
        tope = nuevo;
        n++;
    }
    int top() const { return tope->dato; }   // solo si !vacia()
    bool vacia() const { return tope == nullptr; }
    int tamano() const { return n; }
};

// 3) Mete la pila 'p' en el vector SIN copiar sus nodos.
//    Pista: push_back recibe lo que le des; si le das std::move(p),
//    usa el constructor de movimiento. Una sola línea.
void guardarEnLista(vector<Pila>& lista, Pila& p) {
    (void)lista; (void)p;  // borra esta línea al empezar
    // TODO
}

// Crea una pila con 1..cuantos. Se devuelve POR VALOR: ¿cuesta copiarla?
Pila crearPila(int cuantos) {
    Pila p;
    for (int i = 1; i <= cuantos; i++) p.push(i);
    return p;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    {
        cout << "copiar (ya funciona):\n";
        Pila a;
        a.push(1); a.push(2); a.push(3);
        nodosCopiados = 0;
        Pila b = a;
        comprobar(b.tamano() == 3 && a.tamano() == 3 && nodosCopiados == 3,
                  "Pila b = a;  copia los 3 nodos y a sigue llena");

        cout << "constructor de movimiento:\n";
        nodosCopiados = 0;
        Pila c = std::move(a);
        comprobar(c.tamano() == 3 && c.top() == 3, "Pila c = std::move(a);  c tiene los 3, tope 3");
        comprobar(a.vacia() && a.tamano() == 0, "a queda vacía (tope nullptr, n 0)");
        comprobar(nodosCopiados == 0 && nodosVivos == 6, "no se copió ningún nodo (siguen 6 vivos)");

        cout << "asignación por movimiento:\n";
        Pila d;
        d.push(70); d.push(80);
        nodosCopiados = 0;
        d = std::move(c);
        comprobar(d.tamano() == 3 && d.top() == 3 && c.vacia(), "d = std::move(c);  d recibe los 3, c vacía");
        comprobar(nodosVivos == 6 && nodosCopiados == 0, "los 2 nodos viejos de d se liberaron, sin copias");
        Pila& mismaD = d;            // otro nombre para d
        d = std::move(mismaD);       // auto-asignación: a = std::move(a)
        comprobar(d.tamano() == 3 && d.top() == 3, "d = std::move(d);  no rompe nada");

        cout << "std::move en la vida real:\n";
        vector<Pila> lista;
        Pila e;
        e.push(5); e.push(6); e.push(7);
        nodosCopiados = 0;
        guardarEnLista(lista, e);
        comprobar(lista.size() == 1 && lista[0].tamano() == 3 && e.vacia() && nodosCopiados == 0,
                  "guardarEnLista mete la pila en el vector sin copiar nodos");

        nodosCopiados = 0;
        Pila grande = crearPila(1000);
        comprobar(grande.tamano() == 1000 && nodosCopiados == 0,
                  "devolver una pila de 1000 por valor no copia nodos");
    }
    comprobar(nodosVivos == 0, "al final no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 4.7 terminado.\n"
                         : "\nAún hay fallos. Revisa las partes con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
