// SOLUCIÓN — Miniproyecto 5.1 — Árboles binarios: medir un árbol
// (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 01-arboles-binarios.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
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

// 1) Preorden: raíz, izquierda, derecha.
void preorden(NodoArbol* n, vector<int>& salida) {
    if (n == nullptr) return;          // caso base: árbol vacío
    salida.push_back(n->dato);
    preorden(n->izq, salida);
    preorden(n->der, salida);
}

// 2) Inorden: izquierda, raíz, derecha.
void inorden(NodoArbol* n, vector<int>& salida) {
    if (n == nullptr) return;
    inorden(n->izq, salida);
    salida.push_back(n->dato);
    inorden(n->der, salida);
}

// 3) Postorden: izquierda, derecha, raíz.
void postorden(NodoArbol* n, vector<int>& salida) {
    if (n == nullptr) return;
    postorden(n->izq, salida);
    postorden(n->der, salida);
    salida.push_back(n->dato);
}

// 4) Este nodo + los de la izquierda + los de la derecha.
int contarNodos(NodoArbol* n) {
    if (n == nullptr) return 0;
    return 1 + contarNodos(n->izq) + contarNodos(n->der);
}

// 5) Una hoja no tiene hijos; si no es hoja, suma las hojas de los dos lados.
int contarHojas(NodoArbol* n) {
    if (n == nullptr) return 0;
    if (n->izq == nullptr && n->der == nullptr) return 1;
    return contarHojas(n->izq) + contarHojas(n->der);
}

// 6) Este nivel + el más alto de los dos subárboles.
int altura(NodoArbol* n) {
    if (n == nullptr) return 0;
    return 1 + max(altura(n->izq), altura(n->der));
}

// 7) Postorden: primero los hijos, el padre al final.
void liberar(NodoArbol* n) {
    if (n == nullptr) return;
    liberar(n->izq);
    liberar(n->der);
    delete n;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// El árbol de la lección (raíz 8):
//   8 tiene a 3 a la izquierda y a 10 a la derecha;
//   3 tiene a 1 y a 6; 10 solo tiene a 14, a la derecha.
NodoArbol* arbolEjemplo() {
    NodoArbol* raiz = new NodoArbol(8);
    raiz->izq = new NodoArbol(3);
    raiz->der = new NodoArbol(10);
    raiz->izq->izq = new NodoArbol(1);
    raiz->izq->der = new NodoArbol(6);
    raiz->der->der = new NodoArbol(14);
    return raiz;
}

// Una «cadena»: 1 -> 2 -> ... -> n, siempre por la derecha.
NodoArbol* cadena(int n) {
    NodoArbol* raiz = nullptr;
    for (int i = n; i >= 1; i--) {
        NodoArbol* nuevo = new NodoArbol(i);
        nuevo->der = raiz;
        raiz = nuevo;
    }
    return raiz;
}

vector<int> pre(NodoArbol* n)  { vector<int> v; preorden(n, v);  return v; }
vector<int> in(NodoArbol* n)   { vector<int> v; inorden(n, v);   return v; }
vector<int> post(NodoArbol* n) { vector<int> v; postorden(n, v); return v; }

int main() {
    cout << "Árbol vacío (nullptr):\n";
    comprobar(pre(nullptr).empty() && in(nullptr).empty() && post(nullptr).empty(),
              "los tres recorridos de un árbol vacío no añaden nada");
    comprobar(contarNodos(nullptr) == 0 && contarHojas(nullptr) == 0,
              "un árbol vacío tiene 0 nodos y 0 hojas");
    comprobar(altura(nullptr) == 0, "un árbol vacío tiene altura 0");

    cout << "Un solo nodo:\n";
    {
        NodoArbol* solo = new NodoArbol(5);
        comprobar(pre(solo) == vector<int>{5} && in(solo) == vector<int>{5},
                  "recorrer un solo nodo da {5}");
        comprobar(contarNodos(solo) == 1 && contarHojas(solo) == 1 && altura(solo) == 1,
                  "un solo nodo: 1 nodo, 1 hoja, altura 1");
        liberar(solo);
    }

    cout << "El árbol de la lección:\n";
    NodoArbol* a = arbolEjemplo();
    comprobar(pre(a) == vector<int>{8, 3, 1, 6, 10, 14}, "preorden: 8 3 1 6 10 14");
    comprobar(in(a) == vector<int>{1, 3, 6, 8, 10, 14}, "inorden: 1 3 6 8 10 14");
    comprobar(post(a) == vector<int>{1, 6, 3, 14, 10, 8}, "postorden: 1 6 3 14 10 8");
    comprobar(contarNodos(a) == 6, "tiene 6 nodos");
    comprobar(contarHojas(a) == 3, "tiene 3 hojas (1, 6 y 14)");
    comprobar(altura(a) == 3, "tiene altura 3");

    cout << "Una cadena de 5 nodos:\n";
    NodoArbol* c = cadena(5);
    comprobar(altura(c) == 5 && contarHojas(c) == 1,
              "altura 5 y una sola hoja: es una lista disfrazada");
    comprobar(in(c) == vector<int>{1, 2, 3, 4, 5}, "inorden: 1 2 3 4 5");

    cout << "Liberar:\n";
    comprobar(nodosVivos == 11, "antes de liberar hay 11 nodos vivos (6 + 5)");
    liberar(a);
    liberar(c);
    liberar(nullptr);   // no debe hacer nada ni caerse
    comprobar(nodosVivos == 0, "al liberar los dos árboles no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 5.1 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
