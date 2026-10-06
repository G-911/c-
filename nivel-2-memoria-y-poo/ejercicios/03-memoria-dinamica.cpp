// Miniproyecto 2.3 — Memoria dinámica: un arreglo que crece solo
// ---------------------------------------------------------------
// Completa las TRES funciones marcadas con TODO. No toques lo de abajo.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 03-memoria-dinamica.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
//
// Las pruebas cuentan cuántos arreglos pediste con new[] y cuántos
// devolviste con delete[]. Si se te olvida un delete[], lo verás en ✗.
// ---------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

// 1) Pide con new[] un arreglo de n enteros, pon valorInicial en
//    todas las casillas y devuelve su dirección.
//    Ejemplo: crearArreglo(3, 7) devuelve un arreglo con {7, 7, 7}.
//    Pista: int* a = new int[n];  y luego un for.
int* crearArreglo(int n, int valorInicial) {
    (void)n; (void)valorInicial;   // borra esta línea al empezar (solo evita avisos)
    return nullptr;                // TODO
}

// 2) Crea un arreglo NUEVO de nuevaCapacidad enteros, copia en él los
//    tam primeros elementos de datos, LIBERA el arreglo viejo y
//    devuelve la dirección del nuevo.
//    Pista: los tres pasos en este orden: pedir nuevo, copiar, delete[] viejo.
int* crecer(int* datos, int tam, int nuevaCapacidad) {
    (void)datos; (void)tam; (void)nuevaCapacidad;   // borra esta línea al empezar
    return nullptr;                                  // TODO
}

// 3) Añade valor al final del arreglo y devuelve la dirección del arreglo
//    (que puede haber cambiado si hubo que crecer).
//    *tam = cuántos elementos hay; *cap = cuántos caben.
//    - Si está lleno (*tam == *cap): la nueva capacidad es el DOBLE
//      (o 1 si *cap es 0). Usa crecer() y actualiza *cap.
//    - Luego guarda valor en la casilla *tam y suma 1 a *tam.
//    Se usa así:  datos = agregar(datos, &tam, &cap, 42);
//    Pista: (*tam)++ con paréntesis; sin ellos sumas 1 a la dirección.
int* agregar(int* datos, int* tam, int* cap, int valor) {
    (void)tam; (void)cap; (void)valor;   // borra esta línea al empezar
    return datos;                        // TODO
}

// ----------------- Pruebas automáticas (no tocar) -----------------
// Truco didáctico: reemplazamos new[] y delete[] por versiones que,
// además de hacer su trabajo, llevan la cuenta de arreglos vivos.
int arreglosVivos = 0;
void* operator new[](size_t n) {
    void* p = malloc(n == 0 ? 1 : n);
    if (p == nullptr) throw bad_alloc();
    arreglosVivos++;
    return p;
}
void operator delete[](void* p) noexcept {
    if (p != nullptr) { arreglosVivos--; free(p); }
}
void operator delete[](void* p, size_t) noexcept { operator delete[](p); }

int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "crearArreglo:\n";
    int antes = arreglosVivos;
    int* a = crearArreglo(4, 7);
    bool sieteEnTodas = (a != nullptr);
    for (int i = 0; i < 4 && a != nullptr; i++) if (a[i] != 7) sieteEnTodas = false;
    bool pidioUno = (arreglosVivos - antes == 1);
    delete[] a;
    a = nullptr;
    comprobar(sieteEnTodas, "crearArreglo(4, 7) devuelve {7, 7, 7, 7}");
    comprobar(pidioUno, "pide exactamente un arreglo con new[]");

    cout << "crecer:\n";
    antes = arreglosVivos;
    int* viejo = new int[3];
    viejo[0] = 10; viejo[1] = 20; viejo[2] = 30;
    int* nuevo = crecer(viejo, 3, 6);
    bool distinto = (nuevo != nullptr && nuevo != viejo);
    bool copiado = distinto && nuevo[0] == 10 && nuevo[1] == 20 && nuevo[2] == 30;
    if (distinto) delete[] nuevo;   // el viejo lo tenía que liberar crecer()
    nuevo = nullptr;
    viejo = nullptr;
    comprobar(distinto, "devuelve un arreglo nuevo (otra dirección)");
    comprobar(copiado, "copia {10, 20, 30} al arreglo nuevo");
    comprobar(arreglosVivos == antes, "libera el arreglo viejo (sin fuga de memoria)");

    cout << "agregar:\n";
    antes = arreglosVivos;
    int* datos = nullptr;
    int tam = 0, cap = 0;
    for (int v = 1; v <= 5; v++) datos = agregar(datos, &tam, &cap, v);
    comprobar(tam == 5, "tras agregar 1..5, tam vale 5");
    comprobar(cap == 8, "la capacidad se duplica: 1, 2, 4, 8");
    bool enOrden = (datos != nullptr && tam == 5);
    for (int i = 0; i < 5 && enOrden; i++) if (datos[i] != i + 1) enOrden = false;
    comprobar(enOrden, "los valores quedan en orden {1, 2, 3, 4, 5}");
    int* dondeEstaba = datos;
    datos = agregar(datos, &tam, &cap, 6);
    comprobar(tam == 6 && cap == 8 && datos == dondeEstaba && datos != nullptr,
              "si aún hay sitio, NO crece (mismo arreglo, cap sigue en 8)");
    delete[] datos;
    datos = nullptr;
    comprobar(arreglosVivos == antes, "al final no quedan arreglos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 2.3 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
