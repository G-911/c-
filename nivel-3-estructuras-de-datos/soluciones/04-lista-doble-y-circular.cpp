// SOLUCIÓN — Miniproyecto 3.4 — Lista doble y lista circular (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Completa los CINCO métodos marcados con TODO. No toques main(),
// ni el struct Nodo, ni los métodos que ya vienen hechos.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 04-lista-doble-y-circular.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// Truco didáctico de la lección 3.2: cuántos nodos existen ahora en memoria.
// Cada new Nodo lo sube en 1 y cada delete lo baja en 1.
int nodosVivos = 0;

// Un nodo con DOS flechas: al anterior y al siguiente.
// (La lista circular de la parte B usa el mismo nodo, pero solo su siguiente.)
struct Nodo {
    int dato;
    Nodo* anterior;
    Nodo* siguiente;

    Nodo(int d) : dato(d), anterior(nullptr), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

// =================== PARTE A: lista doble ===================
class ListaDoble {
private:
    Nodo* cabeza;   // primer nodo (nullptr si está vacía)
    Nodo* ultimo;   // último nodo (nullptr si está vacía)

public:
    ListaDoble() : cabeza(nullptr), ultimo(nullptr) {}

    // ---------- Ya hecho ----------
    bool vacia() { return cabeza == nullptr; }

    void insertarAlInicio(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (cabeza == nullptr) {          // lista vacía: es el primero Y el último
            cabeza = nuevo;
            ultimo = nuevo;
            return;
        }
        nuevo->siguiente = cabeza;        // el nuevo mira hacia adelante, al viejo primero
        cabeza->anterior = nuevo;         // el viejo primero mira hacia atrás, al nuevo
        cabeza = nuevo;
    }

    // De la cabeza al último, p. ej. "1,2,3". Lista vacía: "".
    string alDerecho() {
        string texto;
        for (Nodo* actual = cabeza; actual != nullptr; actual = actual->siguiente) {
            if (!texto.empty()) texto += ",";
            texto += to_string(actual->dato);
        }
        return texto;
    }

    ~ListaDoble() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    // ---------- Te toca a ti ----------

    // 1) Añade al FINAL sin recorrer nada: para eso está `ultimo`.
    //    Caso especial: lista vacía (igual que en insertarAlInicio).
    //    Si no: tres flechas — nuevo->anterior, ultimo->siguiente y mover ultimo.
    void insertarAlFinal(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (ultimo == nullptr) {
            cabeza = nuevo;
            ultimo = nuevo;
            return;
        }
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    
    // 2) Del ÚLTIMO a la cabeza, siguiendo las flechas `anterior`.
    //    Mismo formato que alDerecho: "3,2,1". Lista vacía: "".
    //    Pista: copia alDerecho y cambia por dónde empiezas y hacia dónde avanzas.
    string alReves() {
        string texto;
        for (Nodo* actual = ultimo; actual != nullptr; actual = actual->anterior) {
            if (!texto.empty()) texto += ",";
            texto += to_string(actual->dato);
        }
        return texto;
    }
    
    // 3) Borra el PRIMER nodo con ese valor. Devuelve true si lo borró.
    //    Con lista doble NO hace falta el apuntador `anterior` del recorrido:
    //    el propio nodo sabe quién va antes. Busca el nodo y luego:
    //      - si tiene anterior, que el anterior salte al siguiente;
    //        si no, era la cabeza: mueve cabeza.
    //      - si tiene siguiente, que el siguiente mire atrás al anterior;
    //        si no, era el último: mueve ultimo.
    //    Reengancha ANTES de hacer delete.
    bool eliminar(int valor) {
        Nodo* actual = cabeza;
        while (actual != nullptr && actual->dato != valor) {
            actual = actual->siguiente;
        }
        if (actual == nullptr) return false;              // vacía o no estaba

        if (actual->anterior != nullptr) actual->anterior->siguiente = actual->siguiente;
        else                             cabeza = actual->siguiente;      // era la cabeza

        if (actual->siguiente != nullptr) actual->siguiente->anterior = actual->anterior;
        else                              ultimo = actual->anterior;      // era el último

        delete actual;                                    // ya nadie apunta a él
        return true;
    }
    };

// =================== PARTE B: lista circular ===================
// Lista simple en la que el último nodo apunta otra vez a la CABEZA.
// Si la lista está vacía, cabeza es nullptr. Si tiene un solo nodo,
// ese nodo se apunta a sí mismo.
class ListaCircular {
private:
    Nodo* cabeza;

public:
    ListaCircular() : cabeza(nullptr) {}

    // ---------- Ya hecho ----------
    void insertarAlFinal(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            nuevo->siguiente = nuevo;           // un solo nodo: se apunta a sí mismo
            return;
        }
        Nodo* actual = cabeza;
        while (actual->siguiente != cabeza) {   // el último es el que vuelve a la cabeza
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
        nuevo->siguiente = cabeza;              // cerrar el círculo
    }

    // El dato que queda tras avanzar `pasos` veces desde la cabeza.
    // Como es un círculo, se puede avanzar más veces que nodos hay.
    // Lista vacía: -1.
    int datoTras(int pasos) {
        if (cabeza == nullptr) return -1;
        Nodo* actual = cabeza;
        for (int i = 0; i < pasos; i++) actual = actual->siguiente;
        return actual->dato;
    }

    // ---------- Te toca a ti ----------

    // 4) Cuántos nodos hay. Aquí NO existe el nullptr del final:
    //    `while (actual != nullptr)` daría vueltas para siempre.
    //    Pista: lista vacía → 0. Si no, avanza hasta VOLVER a la cabeza
    //    (un do-while encaja muy bien).
    int tamano() {
        if (cabeza == nullptr) return 0;
        int cuenta = 0;
        Nodo* actual = cabeza;
        do {
            cuenta++;
            actual = actual->siguiente;
        } while (actual != cabeza);
        return cuenta;
    }
    
    // 5) Libera todos los nodos.
    //    Pista: si la lista no está vacía, primero ROMPE el círculo
    //    (busca el último y pon su siguiente en nullptr). A partir de ahí
    //    es el destructor de siempre: guardar el siguiente, borrar, avanzar.
    ~ListaCircular() {
        if (cabeza == nullptr) return;
        Nodo* ultimo = cabeza;
        while (ultimo->siguiente != cabeza) ultimo = ultimo->siguiente;
        ultimo->siguiente = nullptr;            // ahora es una lista simple normal

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

int main() {
    cout << "Parte A · insertarAlFinal:\n";
    {
        ListaDoble lista;
        lista.insertarAlFinal(1);
        comprobar(lista.alDerecho() == "1", "en una lista vacía, el primero queda solo: 1");
        lista.insertarAlFinal(2);
        lista.insertarAlFinal(3);
        comprobar(lista.alDerecho() == "1,2,3", "se añaden en orden: 1,2,3");
        lista.insertarAlInicio(0);
        comprobar(lista.alDerecho() == "0,1,2,3", "se combina con insertarAlInicio: 0,1,2,3");
    }

    cout << "Parte A · alReves:\n";
    {
        ListaDoble vacia;
        comprobar(vacia.alReves() == "", "una lista vacía al revés está vacía también");
        ListaDoble lista;
        lista.insertarAlInicio(2);
        lista.insertarAlInicio(1);
        lista.insertarAlFinal(3);
        comprobar(lista.alReves() == "3,2,1", "1,2,3 al revés es 3,2,1 (flechas anterior bien puestas)");
    }

    cout << "Parte A · eliminar:\n";
    {
        ListaDoble vacia;
        comprobar(!vacia.eliminar(5), "eliminar en una lista vacía devuelve false");

        ListaDoble lista;
        for (int i = 1; i <= 5; i++) lista.insertarAlFinal(i);   // 1,2,3,4,5
        comprobar(!lista.eliminar(9) && lista.alDerecho() == "1,2,3,4,5",
                  "un valor inexistente devuelve false y no cambia nada");
        comprobar(lista.eliminar(3) && lista.alDerecho() == "1,2,4,5" && lista.alReves() == "5,4,2,1",
                  "borrar en medio (3): 1,2,4,5 y al revés 5,4,2,1");
        comprobar(lista.eliminar(1) && lista.alDerecho() == "2,4,5" && lista.alReves() == "5,4,2",
                  "borrar la cabeza (1): 2,4,5 y al revés 5,4,2");
        comprobar(lista.eliminar(5) && lista.alDerecho() == "2,4" && lista.alReves() == "4,2",
                  "borrar el último (5): 2,4 y al revés 4,2");
        lista.insertarAlFinal(6);
        comprobar(lista.alDerecho() == "2,4,6", "tras borrar el último, insertarAlFinal sigue bien");
        comprobar(lista.eliminar(2) && lista.eliminar(4) && lista.eliminar(6) && lista.vacia()
                  && lista.alReves() == "",
                  "borrar todos deja la lista vacía en los dos sentidos");
        comprobar(nodosVivos == 0, "cada nodo eliminado se liberó con delete");
    }

    cout << "Parte B · lista circular:\n";
    {
        ListaCircular vacia;
        comprobar(vacia.tamano() == 0, "una lista circular vacía tiene tamaño 0");

        ListaCircular uno;
        uno.insertarAlFinal(7);
        comprobar(uno.tamano() == 1, "con un nodo que se apunta a sí mismo: tamaño 1");

        ListaCircular turnos;
        turnos.insertarAlFinal(10);
        turnos.insertarAlFinal(20);
        turnos.insertarAlFinal(30);
        comprobar(turnos.tamano() == 3, "con tres nodos: tamaño 3");
        comprobar(turnos.datoTras(3) == 10 && turnos.datoTras(5) == 30,
                  "es un círculo: 3 pasos vuelve al 10 y 5 pasos llega al 30");
    }
    comprobar(nodosVivos == 0, "al final no quedan nodos sin liberar (también los circulares)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.4 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
