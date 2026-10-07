// SOLUCIÓN del Miniproyecto 6.8 — Caza de comportamiento indefinido (y una matriz)
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// PARTE A. Las cuatro funciones de abajo YA están escritas, pero cada una
// tiene comportamiento indefinido (UB) escondido. Encuéntralo y arréglalo
// sin cambiar lo que la función promete hacer (lee su comentario).
// PARTE B. Completa sumaPorFilas y sumaPorColumnas.
// No toques main() ni las pruebas.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall -pthread 08-comportamiento-indefinido-y-rendimiento.cpp -o prog && ./prog
//
// OJO: NO le pongas -O2 mientras quede UB. Con optimización, el UB puede
// hacer cualquier cosa (en la máquina donde se escribió esto, el programa
// repetía las pruebas sin fin). Ese es justo el tema de la lección.
//
// Para que las herramientas te señalen los fallos (UBSan avisa y sigue;
// ASan se detiene en el primero que encuentra):
//   g++ -std=c++17 -Wall -pthread -g -fsanitize=address,undefined 08-comportamiento-indefinido-y-rendimiento.cpp -o prog && ./prog
//
// Extra opcional (NO es parte de las pruebas), cuando ya esté todo en ✓:
//   g++ -std=c++17 -Wall -pthread -O2 08-comportamiento-indefinido-y-rendimiento.cpp -o prog && ./prog --medir
// mide con <chrono> tus dos sumas sobre una matriz grande. Se mide con -O2.
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <chrono>
#include <climits>     // INT_MAX, INT_MIN
#include <cstring>     // strcmp
#include <iostream>
#include <vector>
using namespace std;

// ======================= PARTE A: arregla el UB =======================

// 1) Devuelve el promedio de a y b, redondeado hacia cero (como la división
//    entera). Debe funcionar con CUALQUIER par de int, también los enormes.
//    Pista: ¿qué pasa con a + b si los dos rondan INT_MAX? Calcula en
//    long long y vuelve a int al final.
int promedio(int a, int b) {
    // a + b en int puede desbordar (UB). En long long cabe siempre,
    // y la mitad de dos int siempre vuelve a caber en un int.
    long long suma = static_cast<long long>(a) + b;
    return static_cast<int>(suma / 2);
}

// 2) Dice si a + b cabe en un int (true) o se desbordaría (false).
//    La idea es buena: sumar en long long, que tiene sitio de sobra, y mirar
//    si el resultado está entre INT_MIN e INT_MAX. Pero hay un fallo sutil.
//    Pista: ¿en qué tipo se calcula a + b? ¿ANTES o DESPUÉS de guardarlo
//    en s? Convierte uno de los dos a long long antes de sumar.
bool sumaCabe(int a, int b) {
    // Antes: a + b se calculaba en int (UB si desborda) y DESPUÉS se
    // guardaba en long long. Ahora se convierte a ANTES de sumar.
    long long s = static_cast<long long>(a) + b;
    return s >= INT_MIN && s <= INT_MAX;
}

// 3) Suma las n notas del alumno.
//    Pista: mira la condición del for. Si hay n notas, ¿cuál es el último
//    índice válido?
struct Alumno {
    int notas[3];
    int edad;
};

int sumaNotas(const Alumno& a, int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) suma += a.notas[i];   // < y no <=: el último índice es n - 1
    return suma;
}

// 4) Añade x al final de v y devuelve el que era el PRIMER elemento.
//    (v nunca llega vacío.)
//    Pista: push_back puede mudar los datos a otro sitio del montón.
//    ¿Qué le pasa entonces a la referencia «primero»? Copia el valor antes.
int agregarYDarPrimero(vector<int>& v, int x) {
    int primero = v[0];   // una COPIA del valor, no una referencia al hueco viejo
    v.push_back(x);       // si se muda, a la copia no le pasa nada
    return primero;
}

// ===================== PARTE B: recorrer una matriz =====================
// m es una matriz rectangular (todas las filas del mismo largo); puede
// estar vacía. Las dos devuelven la suma de todos sus elementos.

// 5) Recorre fila a fila: para cada fila f, para cada columna c, suma m[f][c].
long long sumaPorFilas(const vector<vector<int>>& m) {
    long long suma = 0;
    for (size_t f = 0; f < m.size(); f++)
        for (size_t c = 0; c < m[f].size(); c++)
            suma += m[f][c];   // recorre la fila seguida: memoria contigua
    return suma;
}

// 6) Recorre columna a columna: para cada columna c, para cada fila f.
//    Pista: el número de columnas es m[0].size(), pero solo si m no está vacía.
long long sumaPorColumnas(const vector<vector<int>>& m) {
    if (m.empty()) return 0;   // sin filas no hay m[0]
    long long suma = 0;
    for (size_t c = 0; c < m[0].size(); c++)
        for (size_t f = 0; f < m.size(); f++)
            suma += m[f][c];   // cada paso salta a otra fila (otro bloque del montón)
    return suma;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Extra opcional: mide las dos sumas. No forma parte de las pruebas.
void medir() {
    const int N = 4000;
    vector<vector<int>> m(N, vector<int>(N, 1));
    for (int vez = 1; vez <= 3; vez++) {
        auto t0 = chrono::steady_clock::now();
        long long a = sumaPorFilas(m);
        auto t1 = chrono::steady_clock::now();
        long long b = sumaPorColumnas(m);
        auto t2 = chrono::steady_clock::now();
        cout << "vez " << vez
             << ": por filas " << chrono::duration<double, milli>(t1 - t0).count() << " ms"
             << ", por columnas " << chrono::duration<double, milli>(t2 - t1).count() << " ms"
             << "  (sumas: " << a << ", " << b << ")\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--medir") == 0) {
        medir();
        return 0;
    }

    cout << "1) promedio:\n";
    comprobar(promedio(2, 4) == 3, "promedio(2, 4) = 3");
    comprobar(promedio(INT_MAX, INT_MAX - 2) == INT_MAX - 1,
              "promedio(INT_MAX, INT_MAX - 2) = INT_MAX - 1 (sin desbordar)");
    comprobar(promedio(INT_MIN, INT_MIN) == INT_MIN, "promedio(INT_MIN, INT_MIN) = INT_MIN");

    cout << "2) sumaCabe:\n";
    comprobar(sumaCabe(1, 2), "1 + 2 cabe");
    comprobar(!sumaCabe(INT_MAX, 1), "INT_MAX + 1 NO cabe");
    comprobar(!sumaCabe(INT_MIN, -1), "INT_MIN + (-1) NO cabe");
    comprobar(sumaCabe(INT_MAX, INT_MIN), "INT_MAX + INT_MIN cabe");

    cout << "3) sumaNotas:\n";
    {
        Alumno ana = {{15, 18, 12}, 20};
        comprobar(sumaNotas(ana, 3) == 45, "notas 15 + 18 + 12 = 45 (sin sumar la edad)");
        comprobar(sumaNotas(ana, 2) == 33, "solo las 2 primeras: 15 + 18 = 33");
    }

    cout << "4) agregarYDarPrimero:\n";
    {
        vector<int> v = {7};
        v.shrink_to_fit();   // sin sitio libre: el push_back TIENE que mudarse
        int p = agregarYDarPrimero(v, 8);
        comprobar(p == 7, "{7} + 8 devuelve 7");
        comprobar(v.size() == 2 && v[1] == 8, "y el 8 quedó al final");
    }

    cout << "5 y 6) recorrer una matriz:\n";
    {
        vector<vector<int>> m = {{1, 2, 3, 4},
                                 {5, 6, 7, 8},
                                 {9, 10, 11, 12}};   // 3 filas x 4 columnas
        comprobar(sumaPorFilas(m) == 78, "por filas: 3x4 suma 78");
        comprobar(sumaPorColumnas(m) == 78, "por columnas: 3x4 suma 78");
        vector<vector<int>> alta = {{1}, {2}, {3}, {4}, {5}};   // 5 x 1
        comprobar(sumaPorFilas(alta) == 15 && sumaPorColumnas(alta) == 15,
                  "5x1: las dos suman 15");
        vector<vector<int>> vacia;
        comprobar(sumaPorFilas(vacia) == 0 && sumaPorColumnas(vacia) == 0,
                  "matriz vacía: las dos suman 0");
    }

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.8 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
