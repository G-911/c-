// SOLUCIÓN del Miniproyecto 3.8 — Contar pasos
// Ábrela solo después de intentarlo de verdad.
// ---------------------------------------------------------------
// Completa las TRES funciones marcadas con TODO. No toques main().
//
// La variable global «pasos» es un contador: cada función le suma 1
// por cada comparación que hace. Así las pruebas comprueban la
// complejidad CONTANDO pasos, sin depender del reloj.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 08-complejidad.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
//
// Extra opcional (NO es parte de las pruebas): medir tiempos reales.
//   g++ -std=c++17 -Wall -O2 08-complejidad.cpp -o prog && ./prog --medir
// ---------------------------------------------------------------
#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

long long pasos = 0;   // súmale 1 en cada comparación

// 1) Búsqueda lineal: devuelve la posición de x en v, o -1 si no está.
//    Suma 1 a pasos por CADA elemento que comparas con x.
//    Pista: for (int i = 0; i < (int)v.size(); i++) { pasos++; if (...) return i; }
int busquedaLineal(const vector<int>& v, int x) {
    for (int i = 0; i < (int)v.size(); i++) {
        pasos++;                       // una comparación
        if (v[i] == x) return i;
    }
    return -1;                         // miré los n: no está
}

// 2) Búsqueda binaria: v está ORDENADO de menor a mayor.
//    Devuelve la posición de x, o -1 si no está.
//    Suma 1 a pasos en CADA vuelta del bucle (cada vez que miras v[medio]).
//    Pista:
//      int izq = 0, der = (int)v.size() - 1;
//      while (izq <= der) {
//          int medio = izq + (der - izq) / 2;   // como (izq+der)/2, sin desbordar
//          ... ¿es x? ¿está a la derecha (izq = medio + 1)?
//              ¿o a la izquierda (der = medio - 1)?
//      }
int busquedaBinaria(const vector<int>& v, int x) {
    int izq = 0, der = (int)v.size() - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        pasos++;                               // una mirada a v[medio]
        if (v[medio] == x) return medio;       // encontrado
        if (v[medio] < x) izq = medio + 1;     // está a la derecha: tiro la izquierda
        else              der = medio - 1;     // está a la izquierda: tiro la derecha
    }
    return -1;                                 // la zona quedó vacía: no está
}

// 3) Cuántas parejas de posiciones (i, j), con i < j, tienen el mismo valor.
//    {4, 4, 4, 1} tiene 3: (0,1), (0,2) y (1,2).
//    Compara todos con todos: es O(n²). Suma 1 a pasos por comparación.
//    Pista: dos for; el de dentro empieza en j = i + 1.
long long contarParesIguales(const vector<int>& v) {
    long long pares = 0;
    int n = (int)v.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {      // j > i: sin repetir parejas
            pasos++;
            if (v[i] == v[j]) pares++;
        }
    return pares;
}

// ----------------- Extra opcional: medir con <chrono> -----------------
// Ya está hecho. Solo corre con ./prog --medir. Los números cambian en
// cada ejecución: fíjate en las PROPORCIONES, no en los milisegundos.
double milisegundosDesde(chrono::steady_clock::time_point inicio) {
    auto fin = chrono::steady_clock::now();
    return chrono::duration<double, milli>(fin - inicio).count();
}

void extraMedirTiempos() {
    vector<int> grande;
    for (int i = 0; i < 1000000; i++) grande.push_back(2 * i);  // ordenado, solo pares

    auto t = chrono::steady_clock::now();
    for (int k = 0; k < 100; k++) busquedaLineal(grande, 1);     // 1 no está: peor caso
    cout << "100 búsquedas lineales en 1.000.000:  " << milisegundosDesde(t) << " ms\n";

    t = chrono::steady_clock::now();
    for (int k = 0; k < 100; k++) busquedaBinaria(grande, 1);
    cout << "100 búsquedas binarias en 1.000.000:  " << milisegundosDesde(t) << " ms\n\n";

    for (int n = 2000; n <= 8000; n *= 2) {
        vector<int> v;
        for (int i = 0; i < n; i++) v.push_back(i % 50);
        t = chrono::steady_clock::now();
        contarParesIguales(v);
        cout << "contarParesIguales con n = " << n << ":  " << milisegundosDesde(t) << " ms\n";
    }
    cout << "(si n se duplica y el tiempo se multiplica por ~4, es O(n²))\n";
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--medir") == 0) {
        extraMedirTiempos();
        return 0;
    }

    vector<int> v = {1, 3, 5, 7, 9, 11, 13};

    cout << "busquedaBinaria (corrección):\n";
    comprobar(busquedaBinaria(v, 1) == 0,  "encuentra el primero (1 en la posición 0)");
    comprobar(busquedaBinaria(v, 13) == 6, "encuentra el último (13 en la posición 6)");
    comprobar(busquedaBinaria(v, 7) == 3,  "encuentra el del medio (7 en la posición 3)");
    comprobar(busquedaBinaria(v, 0) == -1 && busquedaBinaria(v, 8) == -1 &&
              busquedaBinaria(v, 20) == -1, "ausentes (antes, entre y después) dan -1");
    vector<int> vacio;
    vector<int> uno = {5};
    comprobar(busquedaBinaria(vacio, 5) == -1 && busquedaBinaria(uno, 5) == 0,
              "vector vacío da -1; {5} encuentra el 5 en la posición 0");

    cout << "busquedaBinaria (pasos):\n";
    vector<int> grande;
    for (int i = 0; i < 1000000; i++) grande.push_back(2 * i);   // 0, 2, 4, ...
    pasos = 0;
    bool bien = busquedaBinaria(grande, 999999) == -1;           // impar: no está
    long long pasosAusente = pasos;
    pasos = 0;
    bien = bien && busquedaBinaria(grande, 1234566) == 617283;
    comprobar(bien && pasosAusente >= 1 && pasosAusente <= 20 && pasos >= 1 && pasos <= 20,
              "en 1.000.000 datos acierta con 20 pasos o menos: O(log n)");

    cout << "busquedaLineal:\n";
    pasos = 0;
    comprobar(busquedaLineal(v, 7) == 3 && pasos == 4,
              "encuentra el 7 en la posición 3 tras 4 comparaciones");
    vector<int> ceros(1000, 0);
    pasos = 0;
    comprobar(busquedaLineal(ceros, 5) == -1 && pasos == 1000,
              "un ausente en 1000 datos cuesta 1000 pasos: O(n)");

    cout << "contarParesIguales:\n";
    comprobar(contarParesIguales({4, 4, 4, 1}) == 3 && contarParesIguales({1, 2, 3}) == 0,
              "{4,4,4,1} tiene 3 pares iguales; {1,2,3}, ninguno");
    vector<int> cien(100, 7);
    pasos = 0;
    comprobar(contarParesIguales(cien) == 4950 && pasos == 4950,
              "100 datos: 4950 comparaciones = 100·99/2: O(n²)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.8 terminado.\n"
                           "Extra opcional: compila con -O2 y prueba ./prog --medir\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
