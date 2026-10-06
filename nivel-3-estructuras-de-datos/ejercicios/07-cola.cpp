// Miniproyecto 3.7 — Cola y turnos de banco
// ---------------------------------------------------------------
// Completa los TRES trozos marcados con TODO: encolar, desencolar
// y procesarEventos. Lo demás ya está hecho. No toques main().
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 07-cola.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
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

class Cola {
private:
    Nodo* frente;   // el primero de la fila (el que sale)
    Nodo* final;    // el último de la fila (detrás de él entra el nuevo)

public:
    Cola() : frente(nullptr), final(nullptr) {}

    ~Cola() {
        Nodo* actual = frente;
        while (actual != nullptr) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    bool vacia() const { return frente == nullptr; }

    int tamano() const {
        int n = 0;
        for (Nodo* p = frente; p != nullptr; p = p->siguiente) n++;
        return n;
    }

    // Precondición: la cola NO está vacía. Quien llama comprueba vacia() antes.
    int verFrente() const { return frente->dato; }

    // Para las pruebas: frente y final son nullptr A LA VEZ, o ninguno lo es.
    bool bienFormada() const { return (frente == nullptr) == (final == nullptr); }

    // 1) encolar: el nuevo entra por el FINAL de la fila.
    //    Dos casos:
    //      - cola vacía: el nuevo es a la vez frente y final.
    //      - si no: el final actual apunta al nuevo, y el nuevo pasa a ser final.
    void encolar(int valor) {
        (void)valor;   // esta línea solo calla un aviso del compilador: bórrala al empezar
        // TODO
    }

    // 2) desencolar: sale el del FRENTE y se libera su nodo con delete.
    //    Si la cola está vacía, no hace nada.
    //    ¡OJO! Si sacas al último, final también debe volver a nullptr.
    void desencolar() {
        // TODO
    }
};

// Simulador del banco.
// eventos: un número > 0 es un cliente que llega con ese número de turno;
//          un 0 es la cajera que llama al siguiente.
// Guarda en «atendidos» los turnos en el orden en que pasan a caja
// y devuelve cuántos se atendieron. Un 0 con la fila vacía se ignora.
//
// 3) Pista: un for sobre los eventos. Con > 0, encola. Con 0, si la fila
//    no está vacía: guarda verFrente() en atendidos[cuantos], suma 1 y desencola.
//    Recuerda: «fila» es un apuntador a la Cola, así que se usa fila->encolar(...).
int procesarEventos(Cola* fila, int eventos[], int n, int atendidos[]) {
    (void)fila; (void)eventos; (void)n; (void)atendidos;   // bórrala al empezar
    return 0;   // TODO
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "Cola:\n";
    {
        Cola c;
        comprobar(c.vacia() && c.tamano() == 0, "una cola nueva está vacía");
        c.encolar(4);
        c.encolar(7);
        c.encolar(9);
        comprobar(!c.vacia() && c.verFrente() == 4 && c.tamano() == 3,
                  "encolar 4, 7, 9  ->  verFrente = 4 y tamano = 3");
        c.desencolar();
        comprobar(!c.vacia() && c.verFrente() == 7 && c.tamano() == 2 && nodosVivos == 2,
                  "desencolar  ->  verFrente = 7, tamano = 2 y libera el nodo");
        c.desencolar();
        c.desencolar();
        comprobar(c.vacia() && c.bienFormada() && nodosVivos == 0,
                  "al desencolar el ÚLTIMO, frente Y final vuelven a nullptr");
        c.desencolar();   // una de más: sobre vacía no debe hacer nada
        c.encolar(5);
        c.encolar(6);
        comprobar(!c.vacia() && c.verFrente() == 5 && c.tamano() == 2,
                  "se puede volver a usar después de vaciarla");
    }   // aquí se destruye la cola
    comprobar(nodosVivos == 0, "no quedan nodos sin liberar");

    cout << "Banco:\n";
    {
        Cola fila;
        int eventos[] = {5, 8, 0, 3, 0, 0, 0};
        int atendidos[7] = {0};
        int n = procesarEventos(&fila, eventos, 7, atendidos);
        comprobar(n == 3 && atendidos[0] == 5 && atendidos[1] == 8 && atendidos[2] == 3,
                  "llegan 5, 8, 3  ->  se atienden en orden 5, 8, 3");
        comprobar(fila.vacia(), "el 0 con la fila vacía no hace nada");
    }
    {
        Cola fila;
        int eventos[] = {1, 2, 0, 4};
        int atendidos[4] = {0};
        int n = procesarEventos(&fila, eventos, 4, atendidos);
        comprobar(n == 1 && atendidos[0] == 1 && fila.tamano() == 2 &&
                  !fila.vacia() && fila.verFrente() == 2,
                  "llegan 1, 2, 4 y solo se atiende uno  ->  esperan 2 y 4");
    }
    comprobar(nodosVivos == 0, "el banco no deja nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.7 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
