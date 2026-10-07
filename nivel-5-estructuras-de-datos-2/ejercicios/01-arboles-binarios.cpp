// Miniproyecto 5.1 — Árboles binarios: medir un árbol
// ---------------------------------------------------------------
// Completa las SIETE funciones marcadas con TODO. No toques main()
// ni el struct NodoArbol. Todas son recursivas y todas empiezan igual:
//     if (n == nullptr) ...   (el caso base: árbol vacío)
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 01-arboles-binarios.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen AHORA MISMO en memoria.
// Cada new NodoArbol lo sube en 1 y cada delete lo baja en 1.
// Si al final no vuelve a 0, a liberar() se le escapó algún nodo.
int nodosVivos = 0;

// Un nodo del árbol: el dato y DOS apuntadores, uno por hijo.
struct NodoArbol {
    int dato;
    NodoArbol* izq;
    NodoArbol* der;

    NodoArbol(int d) : dato(d), izq(nullptr), der(nullptr) { nodosVivos++; }
    ~NodoArbol() { nodosVivos--; }
};

// 1) Preorden: añade a 'salida' la RAÍZ, luego el subárbol izquierdo
//    y luego el derecho.
//    Pista: si n es nullptr, return. Si no: push_back(n->dato) y dos llamadas.
void preorden(NodoArbol* n, vector<int>& salida) {
    (void)n; (void)salida;  // evita un aviso del compilador; bórrala al empezar
    // TODO
}

// 2) Inorden: izquierda, RAÍZ, derecha.
//    Pista: las mismas tres líneas que preorden, en otro orden.
void inorden(NodoArbol* n, vector<int>& salida) {
    (void)n; (void)salida;  // bórrala al empezar
    // TODO
}

// 3) Postorden: izquierda, derecha, RAÍZ.
void postorden(NodoArbol* n, vector<int>& salida) {
    (void)n; (void)salida;  // bórrala al empezar
    // TODO
}

// 4) Cuántos nodos tiene el árbol.
//    Pista: vacío -> 0. Si no: 1 + los de la izquierda + los de la derecha.
int contarNodos(NodoArbol* n) {
    (void)n;  // bórrala al empezar
    return 0; // TODO
}

// 5) Cuántas HOJAS tiene (nodos sin ningún hijo).
//    Pista: vacío -> 0. Si n->izq y n->der son nullptr, es una hoja -> 1.
//    Si no, suma las hojas de los dos subárboles.
int contarHojas(NodoArbol* n) {
    (void)n;  // bórrala al empezar
    return 0; // TODO
}

// 6) La altura: cuántos niveles tiene (vacío 0, un solo nodo 1).
//    Pista: 1 + max(altura(n->izq), altura(n->der)).
int altura(NodoArbol* n) {
    (void)n;  // bórrala al empezar
    return 0; // TODO
}

// 7) Libera TODOS los nodos con delete.
//    Pista: en POSTORDEN. Primero los dos hijos, el delete al final.
void liberar(NodoArbol* n) {
    (void)n;  // bórrala al empezar
    // TODO
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
