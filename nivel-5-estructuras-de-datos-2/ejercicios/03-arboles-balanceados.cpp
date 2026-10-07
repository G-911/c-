// Miniproyecto 5.3 — Un AVL que no se tuerce
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO, en orden.
// Todo lo demás (alturas, insertar, la clase) ya está hecho:
// es el árbol de búsqueda de la 5.2 con un paso más al volver.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 03-arboles-balanceados.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Truco didáctico: cuenta cuántos nodos existen AHORA MISMO en memoria.
// Rotar solo cambia flechas: no debería crear ni perder ningún nodo.
int nodosVivos = 0;

// Es el NodoArbol de siempre con un campo más: la altura de su subárbol.
struct NodoAVL {
    int dato;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;     // una hoja mide 1

    NodoAVL(int d) : dato(d), izq(nullptr), der(nullptr), altura(1) { nodosVivos++; }
    ~NodoAVL() { nodosVivos--; }
};

// Ya hecho: la altura de un subárbol vacío es 0.
int altura(NodoAVL* n) {
    return n == nullptr ? 0 : n->altura;
}

// Ya hecho: recalcula la altura de n a partir de la de sus hijos.
void actualizarAltura(NodoAVL* n) {
    n->altura = 1 + max(altura(n->izq), altura(n->der));
}

// 1) Factor de balance = altura(n->izq) - altura(n->der).
//    Si n es nullptr, devuelve 0.
//    Pista: usa la función altura() de arriba, que ya acepta nullptr.
int factorBalance(NodoAVL* n) {
    (void)n;   // evita un aviso del compilador; bórrala al empezar
    return 0;  // TODO
}

// 2) Rotación a la DERECHA sobre y. Su hijo izquierdo x sube.
//    Devuelve la nueva raíz del subárbol (x).
//    Pista, la sección 3 de la lección:
//      x = y->izq;  t2 = x->der;
//      x->der = y;  y->izq = t2;
//      actualizarAltura(y);  actualizarAltura(x);   // en ESE orden
//      return x;
NodoAVL* rotarDerecha(NodoAVL* y) {
    return y;  // TODO
}

// 3) Rotación a la IZQUIERDA sobre x. Su hijo derecho y sube.
//    Pista: el espejo de rotarDerecha (cambia izq por der).
NodoAVL* rotarIzquierda(NodoAVL* x) {
    return x;  // TODO
}

// 4) Arregla n si está desbalanceado y devuelve la raíz del subárbol.
//    Pista, la tabla de la sección 7:
//      actualizarAltura(n); fb = factorBalance(n);
//      fb > 1:  si factorBalance(n->izq) < 0, primero
//               n->izq = rotarIzquierda(n->izq);   luego return rotarDerecha(n);
//      fb < -1: el espejo.
//      si no:   return n;
NodoAVL* balancear(NodoAVL* n) {
    return n;  // TODO
}

// Ya hecho: el insertar del BST (lección 5.2) + balancear al volver.
NodoAVL* insertarEn(NodoAVL* n, int valor) {
    if (n == nullptr) return new NodoAVL(valor);
    if (valor < n->dato) n->izq = insertarEn(n->izq, valor);
    else                 n->der = insertarEn(n->der, valor);
    return balancear(n);
}

// Ya hecho: postorden.
void liberar(NodoAVL* n) {
    if (n == nullptr) return;
    liberar(n->izq);
    liberar(n->der);
    delete n;
}

// Ya hecha: la clase. Todo el trabajo está en las funciones de arriba.
class ArbolAVL {
private:
    NodoAVL* raiz;

    int tamanoDe(NodoAVL* n) const {
        return n == nullptr ? 0 : 1 + tamanoDe(n->izq) + tamanoDe(n->der);
    }
    void inordenDe(NodoAVL* n, vector<int>& salida) const {
        if (n == nullptr) return;
        inordenDe(n->izq, salida);
        salida.push_back(n->dato);
        inordenDe(n->der, salida);
    }

public:
    ArbolAVL() : raiz(nullptr) {}
    ~ArbolAVL() { liberar(raiz); }
    ArbolAVL(const ArbolAVL&) = delete;              // prohibido copiar
    ArbolAVL& operator=(const ArbolAVL&) = delete;

    bool buscar(int valor) const {
        NodoAVL* actual = raiz;
        while (actual != nullptr) {
            if (valor == actual->dato) return true;
            actual = (valor < actual->dato) ? actual->izq : actual->der;
        }
        return false;
    }
    bool insertar(int valor) {
        if (buscar(valor)) return false;
        raiz = insertarEn(raiz, valor);
        return true;
    }
    int altura() const { return ::altura(raiz); }   // la función de arriba
    int tamano() const { return tamanoDe(raiz); }
    void inorden(vector<int>& salida) const { inordenDe(raiz, salida); }
    const NodoAVL* verRaiz() const { return raiz; }   // solo para las pruebas
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Construye un nodo a mano con sus hijos y le pone la altura correcta.
NodoAVL* nodo(int d, NodoAVL* i = nullptr, NodoAVL* r = nullptr) {
    NodoAVL* n = new NodoAVL(d);
    n->izq = i;
    n->der = r;
    actualizarAltura(n);
    return n;
}
int datoDe(const NodoAVL* n) { return n == nullptr ? -1 : n->dato; }
// La altura contada nodo a nodo (sin fiarse del campo altura).
int alturaContada(const NodoAVL* n) {
    return n == nullptr ? 0 : 1 + max(alturaContada(n->izq), alturaContada(n->der));
}
vector<int> enOrden(NodoAVL* n) {
    vector<int> v;
    if (n == nullptr) return v;
    vector<int> a = enOrden(n->izq), b = enOrden(n->der);
    v.insert(v.end(), a.begin(), a.end());
    v.push_back(n->dato);
    v.insert(v.end(), b.begin(), b.end());
    return v;
}
// ¿Cumple las reglas del AVL en TODOS los nodos? (orden, altura guardada, |fb| <= 1)
bool esAVL(const NodoAVL* n, long minimo, long maximo, int& alturaReal) {
    if (n == nullptr) { alturaReal = 0; return true; }
    int hi = 0, hd = 0;
    if (n->dato <= minimo || n->dato >= maximo) return false;
    if (!esAVL(n->izq, minimo, n->dato, hi)) return false;
    if (!esAVL(n->der, n->dato, maximo, hd)) return false;
    alturaReal = 1 + max(hi, hd);
    return n->altura == alturaReal && abs(hi - hd) <= 1;
}
bool esAVL(const NodoAVL* raiz) {
    int h = 0;
    return esAVL(raiz, -1000000000L, 1000000000L, h);
}

int main() {
    cout << "factorBalance:\n";
    {
        NodoAVL* hoja = nodo(5);
        NodoAVL* torcido = nodo(30, nodo(20, nodo(10)));
        comprobar(factorBalance(nullptr) == 0 && factorBalance(hoja) == 0,
                  "vacío y hoja: factor 0");
        comprobar(factorBalance(torcido) == 2 && factorBalance(torcido->izq) == 1,
                  "30 -> 20 -> 10 por la izquierda: factores +2 y +1");
        liberar(hoja);
        liberar(torcido);
    }

    cout << "rotarDerecha:\n";
    {
        NodoAVL* r = rotarDerecha(nodo(30, nodo(20, nodo(10))));
        comprobar(datoDe(r) == 20 && r != nullptr && datoDe(r->izq) == 10 && datoDe(r->der) == 30,
                  "30-20-10: sube el 20, con 10 a la izquierda y 30 a la derecha");
        comprobar(r != nullptr && r->altura == 2 && r->der != nullptr && r->der->altura == 1,
                  "las alturas quedan bien: 20 mide 2 y 30 mide 1");
        liberar(r);
    }
    {
        // y=50 con x=30 (hijos 20 y 40) a la izquierda y 60 a la derecha.
        NodoAVL* r = rotarDerecha(nodo(50, nodo(30, nodo(20), nodo(40)), nodo(60)));
        comprobar(datoDe(r) == 30 && r != nullptr && datoDe(r->der) == 50
                  && r->der != nullptr && datoDe(r->der->izq) == 40,
                  "el subárbol del medio (40) cambia de padre: pasa a ser hijo izquierdo de 50");
        comprobar(enOrden(r) == vector<int>{20, 30, 40, 50, 60},
                  "rotar no cambia el inorden: 20 30 40 50 60");
        liberar(r);
    }

    cout << "rotarIzquierda:\n";
    {
        NodoAVL* r = rotarIzquierda(nodo(10, nullptr, nodo(20, nullptr, nodo(30))));
        comprobar(datoDe(r) == 20 && r != nullptr && datoDe(r->izq) == 10 && datoDe(r->der) == 30,
                  "10-20-30: sube el 20, con 10 a la izquierda y 30 a la derecha");
        comprobar(r != nullptr && r->altura == 2 && r->izq != nullptr && r->izq->altura == 1,
                  "las alturas quedan bien: 20 mide 2 y 10 mide 1");
        liberar(r);
    }

    cout << "balancear (los cuatro casos):\n";
    {
        NodoAVL* ii = balancear(nodo(30, nodo(20, nodo(10))));
        NodoAVL* dd = balancear(nodo(10, nullptr, nodo(20, nullptr, nodo(30))));
        NodoAVL* id = balancear(nodo(30, nodo(10, nullptr, nodo(20))));
        NodoAVL* di = balancear(nodo(10, nullptr, nodo(30, nodo(20))));
        comprobar(datoDe(ii) == 20 && esAVL(ii), "izquierda-izquierda: 20 queda arriba");
        comprobar(datoDe(dd) == 20 && esAVL(dd), "derecha-derecha: 20 queda arriba");
        comprobar(datoDe(id) == 20 && esAVL(id), "izquierda-derecha (doble): 20 queda arriba");
        comprobar(datoDe(di) == 20 && esAVL(di), "derecha-izquierda (doble): 20 queda arriba");
        NodoAVL* bien = nodo(20, nodo(10), nodo(30));
        comprobar(balancear(bien) == bien && datoDe(bien->izq) == 10,
                  "un nodo ya balanceado no se toca");
        liberar(ii); liberar(dd); liberar(id); liberar(di); liberar(bien);
    }

    cout << "ArbolAVL:\n";
    {
        ArbolAVL a;
        for (int i = 1; i <= 7; i++) a.insertar(i);
        vector<int> v;
        a.inorden(v);
        comprobar(datoDe(a.verRaiz()) == 4 && alturaContada(a.verRaiz()) == 3,
                  "insertar 1..7 en orden: raíz 4 y altura 3 (un árbol perfecto)");
        comprobar(v == vector<int>{1, 2, 3, 4, 5, 6, 7} && esAVL(a.verRaiz()),
                  "inorden 1..7 y todos los nodos cumplen la regla del AVL");
    }
    {
        ArbolAVL a;
        for (int i = 1; i <= 1000; i++) a.insertar(i);
        double tope = 1.44 * log2(1000.0) + 2;   // unos 16,35
        comprobar(a.tamano() == 1000 && alturaContada(a.verRaiz()) <= tope,
                  "insertar 1..1000 en orden: altura <= 1,44·log2(n) + 2 (un BST mediría 1000)");
        comprobar(esAVL(a.verRaiz()), "y todos los nodos cumplen la regla del AVL");
    }
    {
        ArbolAVL a;
        for (int i = 0; i < 500; i++) a.insertar((i * 37) % 500);   // 0..499 desordenados
        vector<int> v;
        a.inorden(v);
        bool ordenado = (int)v.size() == 500;
        for (int i = 0; ordenado && i < 500; i++) ordenado = (v[i] == i);
        comprobar(ordenado && esAVL(a.verRaiz()),
                  "500 valores desordenados: inorden 0..499 y sigue siendo AVL");
    }

    cout << "Memoria:\n";
    comprobar(nodosVivos == 0, "rotar no crea ni pierde nodos: al final no queda ninguno vivo");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 5.3 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
