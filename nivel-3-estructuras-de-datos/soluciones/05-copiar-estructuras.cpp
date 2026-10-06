// SOLUCIÓN — Miniproyecto 3.5 — Copiar una lista: la regla de tres (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Completa los DOS métodos marcados con TODO: el constructor de copia
// y el operador de asignación (operator=). No toques main(), ni el
// struct Nodo, ni los métodos que ya vienen hechos.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 05-copiar-estructuras.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
//
// OJO: mientras no los escribas, vienen con un relleno que NO copia nada
// (para que el programa no se caiga). Si los BORRAS en vez de completarlos,
// C++ vuelve a la copia superficial y el programa se cae con
// "free(): double free detected". Eso es justo lo que arregla esta lección.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// Truco didáctico de la lección 3.2: cuántos nodos existen ahora en memoria.
// Una copia PROFUNDA de una lista de 3 nodos crea 3 nodos más.
int nodosVivos = 0;

struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class ListaEnlazada {
private:
    Nodo* cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    // ---------- Ya hecho (lecciones 3.2 y 3.3) ----------
    bool vacia() const { return cabeza == nullptr; }

    void insertarAlInicio(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    void insertarAlFinal(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (cabeza == nullptr) { cabeza = nuevo; return; }
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }

    // Borra todos los nodos y deja la lista vacía (cabeza = nullptr).
    void vaciar() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
        cabeza = nullptr;
    }

    // Regla de tres, pieza 1: el destructor.
    ~ListaEnlazada() { vaciar(); }

    // Los datos separados por comas, p. ej. "1,2,3". Lista vacía: "".
    string texto() const {
        string t;
        for (Nodo* actual = cabeza; actual != nullptr; actual = actual->siguiente) {
            if (!t.empty()) t += ",";
            t += to_string(actual->dato);
        }
        return t;
    }

    // Solo para las pruebas: la DIRECCIÓN del primer nodo. Dos listas
    // copiadas en profundidad nunca comparten esa dirección.
    const Nodo* primerNodo() const { return cabeza; }

    // ---------- Te toca a ti ----------

    // 2) Regla de tres, pieza 2: el CONSTRUCTOR DE COPIA.
    //    Se ejecuta en  ListaEnlazada b = a;   y al pasar una lista por valor.
    //    La lista nueva (this) acaba de nacer: aún no tiene nada.
    //    Recorre `otra` y crea un nodo NUEVO por cada nodo suyo, en el MISMO orden.
    //    Pista: la lista de inicialización ya deja cabeza en nullptr. Luego,
    //    el recorrido de siempre sobre otra.cabeza llamando a insertarAlFinal(...).
    //    (Ojo: insertarAlInicio las dejaría al revés.)
    ListaEnlazada(const ListaEnlazada& otra) : cabeza(nullptr) {
        for (Nodo* actual = otra.cabeza; actual != nullptr; actual = actual->siguiente) {
            insertarAlFinal(actual->dato);
        }
    }
    
    // 3) Regla de tres, pieza 3: el OPERADOR DE ASIGNACIÓN.
    //    Se ejecuta en  a = b;  cuando `a` YA EXISTÍA (y puede tener nodos).
    //    Tres pasos:
    //      a) Autoasignación: si this == &otra (a = a), no hagas nada.
    //      b) Libera los nodos viejos de esta lista (hay un método para eso).
    //      c) Copia los nodos de `otra`, igual que en el constructor de copia.
    //    Al final: return *this;  (permite encadenar a = b = c).
    ListaEnlazada& operator=(const ListaEnlazada& otra) {
        if (this == &otra) return *this;      // a) a = a: no hay nada que hacer
        vaciar();                             // b) fuera los nodos viejos
        for (Nodo* actual = otra.cabeza; actual != nullptr; actual = actual->siguiente) {
            insertarAlFinal(actual->dato);    // c) nodos nuevos, mismo orden
        }
        return *this;
    }
    };

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Recibe la lista POR VALOR: aquí dentro trabaja con una copia.
// Le mete un 99 a la copia; la lista original no debe enterarse.
string conNoventaYNueve(ListaEnlazada copia) {
    copia.insertarAlFinal(99);
    return copia.texto();
}

int main() {
    cout << "Constructor de copia:\n";
    {
        ListaEnlazada vacia;
        ListaEnlazada copiaVacia = vacia;
        comprobar(copiaVacia.vacia(), "copiar una lista vacía da una lista vacía");

        ListaEnlazada a;
        a.insertarAlFinal(1);
        a.insertarAlFinal(2);
        a.insertarAlFinal(3);
        ListaEnlazada b = a;                      // constructor de copia
        comprobar(b.texto() == "1,2,3", "la copia tiene los mismos datos en el mismo orden: 1,2,3");
        comprobar(nodosVivos == 6, "copiar 3 nodos crea 3 nodos NUEVOS (hay 6 vivos)");
        comprobar(b.primerNodo() != nullptr && b.primerNodo() != a.primerNodo(), "la copia no comparte nodos con el original");

        b.insertarAlInicio(0);
        a.insertarAlFinal(4);
        comprobar(a.texto() == "1,2,3,4" && b.texto() == "0,1,2,3",
                  "cambiar una no toca la otra: a=1,2,3,4 y b=0,1,2,3");

        comprobar(conNoventaYNueve(a) == "1,2,3,4,99" && a.texto() == "1,2,3,4",
                  "pasar por valor trabaja con una copia: a sigue 1,2,3,4");
    }
    comprobar(nodosVivos == 0, "al destruir original y copias no queda ningún nodo");

    cout << "Operador de asignación:\n";
    {
        ListaEnlazada a;
        a.insertarAlFinal(7);
        a.insertarAlFinal(8);
        ListaEnlazada b;
        b.insertarAlFinal(1);
        b.insertarAlFinal(2);
        b.insertarAlFinal(3);
        b = a;                                    // b YA EXISTÍA con 3 nodos
        comprobar(b.texto() == "7,8", "b = a deja en b una copia de a: 7,8");
        comprobar(nodosVivos == 4, "los 3 nodos viejos de b se liberaron (quedan 4 vivos)");
        comprobar(b.primerNodo() != nullptr && b.primerNodo() != a.primerNodo(), "tras b = a, no comparten nodos");

        b.insertarAlFinal(9);
        comprobar(a.texto() == "7,8" && b.texto() == "7,8,9", "cambiar b después no toca a");

        ListaEnlazada& mismo = a;                 // otro nombre para la MISMA lista
        a = mismo;                                // autoasignación: a = a
        comprobar(a.texto() == "7,8", "autoasignación (a = a) no rompe ni vacía la lista");

        ListaEnlazada c;
        c.insertarAlFinal(5);
        a = b = c;                                // encadenada: primero b = c, luego a = b
        comprobar(a.texto() == "5" && b.texto() == "5", "asignación encadenada a = b = c: las dos quedan 5");

        ListaEnlazada vacia;
        c = vacia;
        comprobar(c.vacia(), "asignar una lista vacía deja la otra vacía");
        comprobar(nodosVivos == 2, "nadie se quedó con nodos de más (2 vivos: a y b)");
    }
    comprobar(nodosVivos == 0, "al final no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.5 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
