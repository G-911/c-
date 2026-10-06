// SOLUCIÓN — Miniproyecto 3.3 — Lista enlazada II (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Completa los TRES métodos marcados con TODO. No toques main(),
// ni el struct Nodo, ni los métodos que ya vienen hechos.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 03-lista-enlazada-2.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// Truco didáctico de la lección 3.2: cuántos nodos existen ahora en memoria.
int nodosVivos = 0;

// Lo que guarda cada nodo: un contacto con dos campos.
struct Contacto {
    string nombre;
    string telefono;
};

// Igual que en la lección 3.2, pero el dato ahora es un Contacto.
// Se accede así:  actual->dato.nombre   y   actual->dato.telefono
struct Nodo {
    Contacto dato;
    Nodo* siguiente;

    Nodo(Contacto d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class ListaEnlazada {
private:
    Nodo* cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    // ---------- Ya hecho (es la lección 3.2) ----------
    bool vacia() { return cabeza == nullptr; }

    int tamano() {
        int cuenta = 0;
        for (Nodo* actual = cabeza; actual != nullptr; actual = actual->siguiente) cuenta++;
        return cuenta;
    }

    void imprimir() {
        for (Nodo* actual = cabeza; actual != nullptr; actual = actual->siguiente)
            cout << actual->dato.nombre << " (" << actual->dato.telefono << ") -> ";
        cout << "nullptr\n";
    }

    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    // Ayuda para las pruebas: los nombres separados por comas, p. ej. "Ana,Beto".
    string nombres() {
        string texto;
        for (Nodo* actual = cabeza; actual != nullptr; actual = actual->siguiente) {
            if (!texto.empty()) texto += ",";
            texto += actual->dato.nombre;
        }
        return texto;
    }

    // ---------- Te toca a ti ----------

    // 1) Añade el contacto al FINAL de la lista.
    //    Caso especial: si la lista está vacía, el nodo nuevo ES la cabeza.
    //    Si no: avanza hasta el último nodo (el que tiene siguiente == nullptr)
    //    y engancha ahí el nuevo.
    //    Para crear el nodo:  Nodo* nuevo = new Nodo({nombre, telefono});
    void insertarAlFinal(string nombre, string telefono) {
        Nodo* nuevo = new Nodo({nombre, telefono});
        if (cabeza == nullptr) {          // caso especial: lista vacía
            cabeza = nuevo;
            return;
        }
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {   // parar EN el último, no después
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    // 2) Devuelve el teléfono del contacto con ese nombre.
    //    Si no existe (o la lista está vacía), devuelve "" (texto vacío).
    //    Pista: el recorrido de siempre; compara actual->dato.nombre == nombre.
    string buscar(string nombre) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato.nombre == nombre) return actual->dato.telefono;
            actual = actual->siguiente;
        }
        return "";
    }

    // 3) Borra el PRIMER contacto con ese nombre y libera su nodo.
    //    Devuelve true si lo borró y false si no estaba.
    //    Los cinco casos: lista vacía, borrar la cabeza, borrar en medio,
    //    borrar el último y nombre inexistente.
    //    Pista: la cabeza es un caso especial. Para los demás, usa dos
    //    apuntadores (anterior y actual) y REENGANCHA antes de hacer delete.
    bool eliminar(string nombre) {
        if (cabeza == nullptr) return false;          // caso 1: lista vacía

        if (cabeza->dato.nombre == nombre) {          // caso 2: borrar la cabeza
            Nodo* aBorrar = cabeza;
            cabeza = cabeza->siguiente;               // primero mover la cabeza...
            delete aBorrar;                           // ...después borrar
            return true;
        }

        Nodo* anterior = cabeza;                      // casos 3, 4 y 5
        Nodo* actual = cabeza->siguiente;
        while (actual != nullptr) {
            if (actual->dato.nombre == nombre) {
                anterior->siguiente = actual->siguiente;   // primero reenganchar...
                delete actual;                             // ...después borrar
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false;                                 // caso 5: no estaba
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Una agenda con Ana, Beto, Caro y Dani, en ese orden.
void llenar(ListaEnlazada& agenda) {
    agenda.insertarAlFinal("Ana",  "0412-111");
    agenda.insertarAlFinal("Beto", "0414-222");
    agenda.insertarAlFinal("Caro", "0416-333");
    agenda.insertarAlFinal("Dani", "0424-444");
}

int main() {
    cout << "insertarAlFinal:\n";
    {
        ListaEnlazada agenda;
        agenda.insertarAlFinal("Ana", "0412-111");
        comprobar(agenda.nombres() == "Ana", "en una agenda vacía, el primero queda de cabeza");
        agenda.insertarAlFinal("Beto", "0414-222");
        agenda.insertarAlFinal("Caro", "0416-333");
        comprobar(agenda.nombres() == "Ana,Beto,Caro", "se añaden en orden: Ana,Beto,Caro");
    }

    cout << "buscar:\n";
    {
        ListaEnlazada vacia;
        comprobar(vacia.buscar("Ana") == "", "buscar en una agenda vacía devuelve \"\"");
        ListaEnlazada agenda;
        llenar(agenda);
        comprobar(agenda.buscar("Ana") == "0412-111" && agenda.buscar("Dani") == "0424-444",
                  "encuentra al primero (Ana) y al último (Dani)");
        comprobar(agenda.buscar("Zoe") == "", "un nombre que no existe devuelve \"\"");
    }

    cout << "eliminar:\n";
    {
        ListaEnlazada vacia;
        comprobar(!vacia.eliminar("Ana"), "eliminar en una agenda vacía devuelve false");

        ListaEnlazada agenda;
        llenar(agenda);
        comprobar(!agenda.eliminar("Zoe") && agenda.tamano() == 4,
                  "eliminar un nombre inexistente devuelve false y no cambia nada");
        comprobar(agenda.eliminar("Ana") && agenda.nombres() == "Beto,Caro,Dani",
                  "borrar la cabeza (Ana) deja Beto,Caro,Dani");
        comprobar(agenda.eliminar("Caro") && agenda.nombres() == "Beto,Dani",
                  "borrar en medio (Caro) deja Beto,Dani");
        comprobar(agenda.eliminar("Dani") && agenda.nombres() == "Beto",
                  "borrar el último (Dani) deja Beto");
        agenda.insertarAlFinal("Eva", "0426-555");
        comprobar(agenda.nombres() == "Beto,Eva",
                  "tras borrar el último, insertarAlFinal sigue funcionando");
        comprobar(agenda.eliminar("Beto") && agenda.eliminar("Eva") && agenda.vacia(),
                  "borrar todos deja la agenda vacía");
        comprobar(nodosVivos == 0, "cada nodo eliminado se liberó con delete");
    }

    comprobar(nodosVivos == 0, "al final no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.3 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
