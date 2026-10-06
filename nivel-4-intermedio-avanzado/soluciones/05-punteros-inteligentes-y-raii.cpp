// SOLUCIÓN del Miniproyecto 4.5 — Lista enlazada con unique_ptr
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 05-punteros-inteligentes-y-raii.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <memory>    // unique_ptr, make_unique
#include <string>
#include <utility>   // move
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen ahora mismo.
// Si al final no vale 0, hay una fuga de memoria.
int nodosVivos = 0;

struct Nodo {
    int dato;
    unique_ptr<Nodo> siguiente;   // el nodo es DUEÑO del siguiente
    Nodo(int d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class ListaEnlazada {
private:
    unique_ptr<Nodo> cabeza;   // la lista es dueña del primero

public:
    // Sin destructor «a mano» que haga delete: cada unique_ptr libera lo suyo.
    // Solo llamamos a vaciar() para que una lista MUY larga no se libere
    // de forma recursiva (ver la lección, sección 6).
    ~ListaEnlazada() { vaciar(); }

    bool vacia() const { return cabeza == nullptr; }

    // Para RECORRER se usa un apuntador normal que solo mira: .get()
    int tamano() const {
        int n = 0;
        for (Nodo* p = cabeza.get(); p != nullptr; p = p->siguiente.get()) n++;
        return n;
    }

    string aTexto() const {
        string s;
        for (Nodo* p = cabeza.get(); p != nullptr; p = p->siguiente.get()) {
            s += to_string(p->dato);
            if (p->siguiente) s += " -> ";
        }
        return s;
    }

    // 1) El nuevo se queda con la cabeza vieja; luego el nuevo ES la cabeza.
    void insertarAlInicio(int valor) {
        unique_ptr<Nodo> nuevo = make_unique<Nodo>(valor);
        nuevo->siguiente = move(cabeza);
        cabeza = move(nuevo);
    }

    // 2) Camina con un Nodo* que solo mira hasta el último.
    void insertarAlFinal(int valor) {
        if (!cabeza) {
            cabeza = make_unique<Nodo>(valor);
            return;
        }
        Nodo* p = cabeza.get();
        while (p->siguiente) p = p->siguiente.get();
        p->siguiente = make_unique<Nodo>(valor);
    }

    // 3) Mover el segundo a la cabeza libera el primero solo. Sin delete.
    bool eliminarPrimero() {
        if (!cabeza) return false;
        cabeza = move(cabeza->siguiente);
        return true;
    }

    // 4) Libera nodo a nodo con un bucle (nunca en cadena recursiva).
    void vaciar() {
        while (cabeza) {
            cabeza = move(cabeza->siguiente);
        }
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "insertarAlInicio:\n";
    {
        ListaEnlazada l;
        comprobar(l.vacia() && l.tamano() == 0, "una lista nueva está vacía");
        l.insertarAlInicio(3);
        l.insertarAlInicio(2);
        l.insertarAlInicio(1);
        comprobar(l.aTexto() == "1 -> 2 -> 3", "inicio 3, 2, 1  ->  1 -> 2 -> 3");
    }
    comprobar(nodosVivos == 0, "al salir del bloque se liberan TODOS los nodos (sin delete)");

    cout << "insertarAlFinal:\n";
    {
        ListaEnlazada l;
        l.insertarAlFinal(7);
        comprobar(l.aTexto() == "7", "en una lista vacía, el primero es la cabeza");
        l.insertarAlFinal(8);
        l.insertarAlInicio(6);
        comprobar(l.aTexto() == "6 -> 7 -> 8", "final 7, final 8, inicio 6  ->  6 -> 7 -> 8");
    }

    cout << "eliminarPrimero:\n";
    {
        ListaEnlazada l;
        l.insertarAlFinal(1);
        l.insertarAlFinal(2);
        bool ok = l.eliminarPrimero();
        comprobar(ok && l.aTexto() == "2" && nodosVivos == 1,
                  "1 -> 2  ->  queda 2 y se liberó un nodo");
        l.eliminarPrimero();
        comprobar(!l.eliminarPrimero() && l.vacia(), "sobre una lista vacía devuelve false");
    }

    cout << "vaciar:\n";
    bool vaciarFunciona = false;
    {
        ListaEnlazada l;
        for (int i = 0; i < 5; i++) l.insertarAlInicio(i);
        bool teniaCinco = l.tamano() == 5;
        l.vaciar();
        vaciarFunciona = teniaCinco && l.vacia() && nodosVivos == 0;
        comprobar(vaciarFunciona, "vaciar() deja la lista vacía y libera los 5 nodos");
        l.insertarAlFinal(9);
        comprobar(l.aTexto() == "9", "después de vaciar se puede volver a usar");
    }

    if (vaciarFunciona) {
        {
            ListaEnlazada larga;
            for (int i = 0; i < 1000000; i++) larga.insertarAlInicio(i);
        }   // aquí se destruye: un millón de nodos
        comprobar(nodosVivos == 0, "una lista de un millón de nodos se libera sin caerse");
    } else {
        comprobar(false, "lista de un millón de nodos (primero haz que vaciar() funcione)");
    }

    comprobar(nodosVivos == 0, "no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 4.5 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
