// Miniproyecto 5.2 — Árbol binario de búsqueda completo
// ---------------------------------------------------------------
// Completa los SEIS métodos marcados con TODO (1 a 5; el 3 son dos).
// No toques main(), el struct NodoArbol ni los métodos que dicen
// «Ya hecho». Los números marcan el orden en que conviene hacerlos
// (en el archivo salen salteados porque los privados van arriba).
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 02-arbol-binario-de-busqueda.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen AHORA MISMO en memoria.
// Cada new NodoArbol lo sube en 1 y cada delete lo baja en 1.
int nodosVivos = 0;

struct NodoArbol {
    int dato;
    NodoArbol* izq;
    NodoArbol* der;

    NodoArbol(int d) : dato(d), izq(nullptr), der(nullptr) { nodosVivos++; }
    ~NodoArbol() { nodosVivos--; }
};

class ArbolBusqueda {
private:
    NodoArbol* raiz;   // nullptr si el árbol está vacío

    // 1) Mete 'valor' en el subárbol que empieza en n y DEVUELVE la raíz
    //    de ese subárbol. (insertar() ya comprobó que no está repetido.)
    //    Pista: si n es nullptr, aquí va: return new NodoArbol(valor);
    //    si no, baja por un lado:  n->izq = insertarEn(n->izq, valor);
    //    (o por la derecha) y al final return n;
    NodoArbol* insertarEn(NodoArbol* n, int valor) {
        (void)valor;  // evita un aviso del compilador; bórrala al empezar
        return n;     // TODO
    }

    // 4) Quita 'valor' del subárbol que empieza en n y DEVUELVE la raíz
    //    de ese subárbol. (eliminar() ya comprobó que el valor está.)
    //    Pista, los tres casos de la sección 6 de la lección:
    //      - menor o mayor: n->izq = eliminarEn(n->izq, valor); return n;
    //      - sin hijo izquierdo (hoja o solo derecho): guarda n->der,
    //        delete n, y devuelve lo guardado. Igual con el otro lado.
    //      - dos hijos: busca el mínimo de n->der (el sucesor), copia su
    //        dato en n, y elimínalo de n->der con una llamada recursiva.
    NodoArbol* eliminarEn(NodoArbol* n, int valor) {
        (void)valor;  // bórrala al empezar
        return n;     // TODO
    }

    // 5) Libera todos los nodos del subárbol (la usa el destructor).
    //    Pista: es el liberar() de la lección 5.1, en postorden.
    void liberar(NodoArbol* n) {
        (void)n;  // bórrala al empezar
        // TODO
    }

    // Ya hechos (son los de la lección 5.1).
    int alturaDe(NodoArbol* n) const {
        if (n == nullptr) return 0;
        return 1 + max(alturaDe(n->izq), alturaDe(n->der));
    }
    int tamanoDe(NodoArbol* n) const {
        if (n == nullptr) return 0;
        return 1 + tamanoDe(n->izq) + tamanoDe(n->der);
    }
    void inordenDe(NodoArbol* n, vector<int>& salida) const {
        if (n == nullptr) return;
        inordenDe(n->izq, salida);
        salida.push_back(n->dato);
        inordenDe(n->der, salida);
    }

public:
    ArbolBusqueda() : raiz(nullptr) {}
    ~ArbolBusqueda() { liberar(raiz); }

    // Prohibido copiar (lección 3.5): dos árboles con los mismos nodos
    // los liberarían dos veces.
    ArbolBusqueda(const ArbolBusqueda&) = delete;
    ArbolBusqueda& operator=(const ArbolBusqueda&) = delete;

    bool vacio() const { return raiz == nullptr; }

    // Ya hecho: no admite repetidos.
    bool insertar(int valor) {
        if (buscar(valor)) return false;
        raiz = insertarEn(raiz, valor);
        return true;
    }

    // 2) Devuelve true si 'valor' está en el árbol.
    //    Pista: NodoArbol* actual = raiz; y un while que baje a la
    //    izquierda si valor es menor y a la derecha si es mayor.
    bool buscar(int valor) const {
        (void)valor;   // bórrala al empezar
        return false;  // TODO
    }

    // 3) El valor más pequeño (el de más a la izquierda) y el más
    //    grande (el de más a la derecha).
    //    Si el árbol está vacío, lanza out_of_range (lección 4.4).
    //    Pista: comprueba raiz ANTES de bajar; luego baja mientras
    //    actual->izq != nullptr (o actual->der).
    int minimo() const {
        return 0;  // TODO
    }

    int maximo() const {
        return 0;  // TODO
    }

    // Ya hecho: devuelve false si el valor no estaba.
    bool eliminar(int valor) {
        if (!buscar(valor)) return false;
        raiz = eliminarEn(raiz, valor);
        return true;
    }

    int altura() const { return alturaDe(raiz); }
    int tamano() const { return tamanoDe(raiz); }
    void inorden(vector<int>& salida) const { inordenDe(raiz, salida); }

    // Solo para las pruebas: mirar la forma del árbol sin poder cambiarla.
    const NodoArbol* verRaiz() const { return raiz; }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

vector<int> enOrden(const ArbolBusqueda& a) { vector<int> v; a.inorden(v); return v; }
int datoDe(const NodoArbol* n) { return n == nullptr ? -1 : n->dato; }

// El árbol de la lección: 8, 3, 10, 1, 6, 14, 4, 7.
void llenar(ArbolBusqueda& a) {
    for (int x : {8, 3, 10, 1, 6, 14, 4, 7}) a.insertar(x);
}

int main() {
    cout << "Árbol vacío:\n";
    {
        ArbolBusqueda a;
        comprobar(a.vacio() && a.tamano() == 0 && a.altura() == 0,
                  "un árbol nuevo está vacío: tamaño 0 y altura 0");
        comprobar(!a.buscar(5), "buscar en un árbol vacío devuelve false");
        bool lanzaMin = false, lanzaMax = false;
        try { a.minimo(); } catch (const out_of_range&) { lanzaMin = true; }
        try { a.maximo(); } catch (const out_of_range&) { lanzaMax = true; }
        comprobar(lanzaMin && lanzaMax, "minimo() y maximo() lanzan out_of_range si está vacío");
    }

    cout << "insertar y buscar:\n";
    {
        ArbolBusqueda a;
        llenar(a);
        comprobar(a.tamano() == 8, "tras insertar 8 valores, tamaño 8");
        comprobar(enOrden(a) == vector<int>{1, 3, 4, 6, 7, 8, 10, 14},
                  "el inorden sale ordenado: 1 3 4 6 7 8 10 14");
        const NodoArbol* r = a.verRaiz();
        comprobar(datoDe(r) == 8 && r != nullptr && datoDe(r->izq) == 3 && datoDe(r->der) == 10,
                  "el primero insertado (8) es la raíz; 3 a su izquierda, 10 a su derecha");
        comprobar(!a.insertar(6) && a.tamano() == 8,
                  "insertar un repetido devuelve false y no cambia nada");
        comprobar(a.buscar(8) && a.buscar(1) && a.buscar(7) && a.buscar(14),
                  "encuentra 8 (la raíz), 1, 7 y 14 (hojas)");
        comprobar(!a.buscar(0) && !a.buscar(5) && !a.buscar(99),
                  "no encuentra 0, 5 ni 99");
    }

    cout << "minimo y maximo:\n";
    {
        ArbolBusqueda a;
        llenar(a);
        int mn = -1, mx = -1;
        try { mn = a.minimo(); mx = a.maximo(); } catch (const exception&) {}
        comprobar(mn == 1 && mx == 14, "minimo 1 y maximo 14");
    }

    cout << "eliminar (los tres casos):\n";
    {
        ArbolBusqueda a;
        llenar(a);
        int antes = nodosVivos;
        comprobar(a.eliminar(7) && enOrden(a) == vector<int>{1, 3, 4, 6, 8, 10, 14}
                  && nodosVivos == antes - 1,
                  "hoja: eliminar 7 lo quita y libera su nodo");
        bool ok = a.eliminar(10);
        const NodoArbol* r = a.verRaiz();
        comprobar(ok && r != nullptr && datoDe(r->der) == 14
                  && enOrden(a) == vector<int>{1, 3, 4, 6, 8, 14},
                  "un hijo: eliminar 10 deja a 14 en su sitio");
        ok = a.eliminar(3);
        r = a.verRaiz();
        comprobar(ok && r != nullptr && datoDe(r->izq) == 4
                  && enOrden(a) == vector<int>{1, 4, 6, 8, 14},
                  "dos hijos: eliminar 3 pone en su sitio al sucesor (4)");
        comprobar(!a.eliminar(3) && !a.eliminar(99) && a.tamano() == 5,
                  "eliminar algo que no está devuelve false");
        comprobar(nodosVivos == antes - 3, "cada eliminar liberó exactamente un nodo");
    }
    {
        ArbolBusqueda a;
        llenar(a);
        comprobar(a.eliminar(8) && datoDe(a.verRaiz()) == 10
                  && enOrden(a) == vector<int>{1, 3, 4, 6, 7, 10, 14},
                  "eliminar la raíz (8, dos hijos) deja como raíz a su sucesor, 10");
        for (int x : {1, 3, 4, 6, 7, 10, 14}) a.eliminar(x);
        comprobar(a.vacio() && a.tamano() == 0, "eliminar todo deja el árbol vacío");
    }

    cout << "Árbol degenerado:\n";
    {
        ArbolBusqueda a;
        for (int i = 1; i <= 10; i++) a.insertar(i);
        comprobar(a.altura() == 10, "insertar 1..10 en orden da altura 10: es una lista");
    }

    cout << "Destructor:\n";
    comprobar(nodosVivos == 0, "al destruir los árboles no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 5.2 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
