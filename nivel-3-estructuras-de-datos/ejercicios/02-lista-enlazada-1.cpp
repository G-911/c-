// Miniproyecto 3.2 — Lista enlazada I: lista de tareas pendientes
// ---------------------------------------------------------------
// Completa los CINCO métodos marcados con TODO. No toques main()
// ni el struct Nodo.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 02-lista-enlazada-1.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen AHORA MISMO en memoria.
// Cada new Nodo lo sube en 1 y cada delete lo baja en 1.
// Si al final no vuelve a 0, a tu lista se le olvidó liberar algún nodo.
int nodosVivos = 0;

// Una caja de la lista: la tarea y la dirección de la siguiente caja.
struct Nodo {
    string dato;
    Nodo* siguiente;

    Nodo(string d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class ListaEnlazada {
private:
    Nodo* cabeza;   // apunta al PRIMER nodo; nullptr si la lista está vacía

public:
    // Ya hecho: una lista nueva está vacía.
    ListaEnlazada() : cabeza(nullptr) {}

    // 1) Devuelve true si la lista no tiene ningún nodo.
    //    Pista: una sola línea. ¿Qué vale cabeza en una lista vacía?
    bool vacia() {
        return false; // TODO
    }

    // 2) Mete la tarea al PRINCIPIO de la lista.
    //    Pista, en este orden: crea el nodo con new,
    //    engánchalo delante (nuevo->siguiente = cabeza)
    //    y por último mueve cabeza al nodo nuevo.
    void insertarAlInicio(string tarea) {
        (void)tarea;  // evita un aviso del compilador; bórrala al empezar
        // TODO
    }

    // 3) Muestra las tareas en orden, cada una seguida de " -> ",
    //    y al final "nullptr" y un salto de línea. Ejemplos:
    //      lista con Estudiar y Lavar:   Estudiar -> Lavar -> nullptr
    //      lista vacía:                  nullptr
    //    Pista: Nodo* actual = cabeza; while (actual != nullptr) { ... }
    void imprimir() {
        // TODO
    }

    // 4) Devuelve cuántos nodos hay en la lista.
    //    Pista: el mismo recorrido de imprimir, pero contando.
    int tamano() {
        return 0; // TODO
    }

    // 5) Destructor: libera TODOS los nodos con delete.
    //    Pista: guarda actual->siguiente ANTES de hacer delete actual.
    ~ListaEnlazada() {
        // TODO
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Ejecuta lista.imprimir() y devuelve lo que habría salido en pantalla.
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
    }   // aquí se destruye la lista
    comprobar(vivosDentro == 3, "con 3 tareas hay 3 nodos vivos en memoria");
    comprobar(nodosVivos == 0, "al destruir las listas no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.2 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
