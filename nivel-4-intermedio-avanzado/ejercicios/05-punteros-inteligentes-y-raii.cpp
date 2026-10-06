// Miniproyecto 4.5 — Lista enlazada con unique_ptr
// ---------------------------------------------------------------
// Completa los CUATRO métodos marcados con TODO. No toques main().
// Regla del juego: en este archivo NO se escribe ni un new ni un delete.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 05-punteros-inteligentes-y-raii.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
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

    // 1) Pone «valor» delante de todo.
    //    Pista: crea el nodo con make_unique<Nodo>(valor); que su
    //    siguiente se quede con la cabeza (move); luego la cabeza es el nuevo (move).
    void insertarAlInicio(int valor) {
        (void)valor;   // calla un aviso del compilador: bórrala al empezar
        // TODO
    }

    // 2) Pone «valor» al final.
    //    Pista: si no hay cabeza, la cabeza es el nuevo. Si no, camina con
    //    un Nodo* p = cabeza.get() mientras p->siguiente exista
    //    (p = p->siguiente.get()) y cuelga ahí el nuevo.
    void insertarAlFinal(int valor) {
        (void)valor;   // calla un aviso del compilador: bórrala al empezar
        // TODO
    }

    // 3) Quita el primero. Devuelve false si la lista estaba vacía.
    //    Pista: una sola línea con move hace que el primero se libere solo.
    bool eliminarPrimero() {
        // TODO (borra el return false cuando lo escribas)
        return false;
    }

    // 4) Deja la lista vacía liberando los nodos UNO A UNO con un bucle
    //    while. Es la misma línea del método 3, repetida.
    void vaciar() {
        // TODO
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
