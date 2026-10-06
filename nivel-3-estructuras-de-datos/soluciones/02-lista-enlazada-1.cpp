// SOLUCIÓN — Miniproyecto 3.2 — Lista enlazada I (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 02-lista-enlazada-1.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen AHORA MISMO en memoria.
int nodosVivos = 0;

struct Nodo {
    string dato;
    Nodo* siguiente;

    Nodo(string d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class ListaEnlazada {
private:
    Nodo* cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    // 1) Vacía = cabeza no apunta a nada.
    bool vacia() {
        return cabeza == nullptr;
    }

    // 2) Crear, enganchar delante, mover la cabeza. El orden importa:
    //    si movieras cabeza primero, perderías el resto de la lista.
    void insertarAlInicio(string tarea) {
        Nodo* nuevo = new Nodo(tarea);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    // 3) Recorrido con un apuntador auxiliar; cabeza no se mueve.
    void imprimir() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato << " -> ";
            actual = actual->siguiente;
        }
        cout << "nullptr\n";
    }

    // 4) El mismo recorrido, contando.
    int tamano() {
        int cuenta = 0;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cuenta++;
            actual = actual->siguiente;
        }
        return cuenta;
    }

    // 5) Guardar el siguiente ANTES de borrar el actual.
    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

string capturarImpresion(ListaEnlazada& lista) {
    ostringstream salida;
    streambuf* original = cout.rdbuf(salida.rdbuf());
    lista.imprimir();
    cout.rdbuf(original);
    return salida.str();
}

int main() {
    cout << "Lista vacía:\n";
    {
        ListaEnlazada tareas;
        comprobar(tareas.vacia(), "una lista nueva está vacía");
        comprobar(tareas.tamano() == 0, "una lista nueva tiene tamaño 0");
        comprobar(capturarImpresion(tareas) == "nullptr\n",
                  "imprimir una lista vacía muestra solo: nullptr");
    }

    cout << "insertarAlInicio:\n";
    {
        ListaEnlazada tareas;
        tareas.insertarAlInicio("Estudiar");
        comprobar(!tareas.vacia() && tareas.tamano() == 1,
                  "con una tarea: no está vacía y tamaño 1");
        tareas.insertarAlInicio("Lavar");
        tareas.insertarAlInicio("Comprar");
        comprobar(tareas.tamano() == 3, "con tres tareas: tamaño 3");
        comprobar(capturarImpresion(tareas) == "Comprar -> Lavar -> Estudiar -> nullptr\n",
                  "la última insertada sale primero: Comprar -> Lavar -> Estudiar -> nullptr");
    }

    cout << "Muchas tareas:\n";
    {
        ListaEnlazada tareas;
        for (int i = 0; i < 100; i++) tareas.insertarAlInicio("tarea");
        comprobar(tareas.tamano() == 100, "100 inserciones: tamaño 100");
    }

    cout << "Destructor:\n";
    int vivosDentro = -1;
    {
        ListaEnlazada tareas;
        tareas.insertarAlInicio("A");
        tareas.insertarAlInicio("B");
        tareas.insertarAlInicio("C");
        vivosDentro = nodosVivos;
    }
    comprobar(vivosDentro == 3, "con 3 tareas hay 3 nodos vivos en memoria");
    comprobar(nodosVivos == 0, "al destruir las listas no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.2 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
