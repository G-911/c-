// SOLUCIÓN — Miniproyecto 5.2 — Árbol binario de búsqueda completo
// (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 02-arbol-binario-de-busqueda.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

// Truco didáctico: cuántos nodos existen AHORA MISMO en memoria.
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

    // 1) Devuelve la raíz del subárbol ya con el valor dentro.
    NodoArbol* insertarEn(NodoArbol* n, int valor) {
        if (n == nullptr) return new NodoArbol(valor);   // hueco libre: aquí va
        if (valor < n->dato) n->izq = insertarEn(n->izq, valor);
        else                 n->der = insertarEn(n->der, valor);
        return n;                                         // la raíz no cambia
    }

    // 4) Devuelve la raíz del subárbol ya sin el valor.
    NodoArbol* eliminarEn(NodoArbol* n, int valor) {
        if (n == nullptr) return nullptr;
        if (valor < n->dato) { n->izq = eliminarEn(n->izq, valor); return n; }
        if (valor > n->dato) { n->der = eliminarEn(n->der, valor); return n; }

        // Lo encontramos: n es el nodo a borrar.
        if (n->izq == nullptr) {             // hoja, o solo hijo derecho
            NodoArbol* hijo = n->der;
            delete n;
            return hijo;                     // el hijo (o nullptr) sube a su sitio
        }
        if (n->der == nullptr) {             // solo hijo izquierdo
            NodoArbol* hijo = n->izq;
            delete n;
            return hijo;
        }
        // Dos hijos: el sucesor inorden es el MÍNIMO del subárbol derecho.
        NodoArbol* sucesor = n->der;
        while (sucesor->izq != nullptr) sucesor = sucesor->izq;
        n->dato = sucesor->dato;                       // copiar su valor aquí
        n->der = eliminarEn(n->der, sucesor->dato);    // y borrar el original
        return n;
    }

    // 5) Postorden: primero los hijos, el padre al final.
    void liberar(NodoArbol* n) {
        if (n == nullptr) return;
        liberar(n->izq);
        liberar(n->der);
        delete n;
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

    // 2) Bajar comparando: menor a la izquierda, mayor a la derecha.
    bool buscar(int valor) const {
        NodoArbol* actual = raiz;
        while (actual != nullptr) {
            if (valor == actual->dato) return true;
            actual = (valor < actual->dato) ? actual->izq : actual->der;
        }
        return false;
    }

    // 3) El mínimo es el de más a la izquierda; el máximo, el de más a la derecha.
    int minimo() const {
        if (raiz == nullptr) throw out_of_range("minimo: el árbol está vacío");
        NodoArbol* actual = raiz;
        while (actual->izq != nullptr) actual = actual->izq;
        return actual->dato;
    }

    int maximo() const {
        if (raiz == nullptr) throw out_of_range("maximo: el árbol está vacío");
        NodoArbol* actual = raiz;
        while (actual->der != nullptr) actual = actual->der;
        return actual->dato;
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
