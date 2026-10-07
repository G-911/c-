// SOLUCIÓN del Miniproyecto 5.5 — Tres algoritmos de ordenamiento que cuentan
// Ábrela solo después de intentarlo de verdad.
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO. No toques main().
//
// REGLA: toda comparación entre dos elementos se hace con menor(a, b),
// nunca con < directamente. Así el programa CUENTA las comparaciones
// (la variable global «comparaciones») y las pruebas pueden ver si tu
// algoritmo hace el trabajo que debe. No medimos tiempos: cambian de
// una máquina a otra; las comparaciones no.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 05-ordenamiento.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   // sort, stable_sort, is_sorted
#include <utility>     // swap
using namespace std;

long long comparaciones = 0;

// ¿a va antes que b? Cuenta una comparación cada vez.
bool menor(int a, int b) {
    comparaciones++;
    return a < b;
}

// 1) INSERCIÓN. Para cada i desde 1: guarda x = v[i] y desplaza a la
//    derecha los de su izquierda MAYORES que x; luego deja x en el hueco.
//    Pista:
//      int x = v[i]; int j = i - 1;
//      while (j >= 0 && menor(x, v[j])) { v[j + 1] = v[j]; j--; }
//      v[j + 1] = x;
//    (Fíjate: con el && se deja de comparar en cuanto j < 0.)
void insercion(vector<int>& v) {
    for (int i = 1; i < (int)v.size(); i++) {
        int x = v[i];                     // la carta que vamos a colocar
        int j = i - 1;
        while (j >= 0 && menor(x, v[j])) {
            v[j + 1] = v[j];              // el mayor se corre a la derecha
            j--;
        }
        v[j + 1] = x;                     // x cae en el hueco
    }
}

// 2) MEZCLAR (el corazón de mergesort).
//    v[ini..medio-1] y v[medio..fin-1] ya están ordenados cada uno.
//    Júntalos en un vector temporal, eligiendo cada vez el menor de
//    los dos primeros, y cópialo de vuelta a v desde ini.
//    Para que sea ESTABLE: toma el de la derecha solo si
//    menor(derecho, izquierdo); si empatan, gana el de la izquierda.
//    Cuando uno de los dos trozos se acaba, copia el resto del otro
//    SIN comparar.
void mezclar(vector<int>& v, int ini, int medio, int fin) {
    vector<int> temp;                     // la memoria extra de mergesort
    temp.reserve(fin - ini);
    int i = ini, j = medio;
    while (i < medio && j < fin) {
        if (menor(v[j], v[i])) temp.push_back(v[j++]);   // derecha solo si es MENOR
        else                   temp.push_back(v[i++]);   // empate: gana la izquierda
    }
    while (i < medio) temp.push_back(v[i++]);   // lo que sobre, sin comparar
    while (j < fin)   temp.push_back(v[j++]);
    for (int k = 0; k < (int)temp.size(); k++) v[ini + k] = temp[k];
}

// Ya está hecha: ordena v[ini..fin-1] partiendo por la mitad.
void mergesort(vector<int>& v, int ini, int fin) {
    if (fin - ini <= 1) return;          // 0 o 1 elementos: ya ordenado
    int medio = ini + (fin - ini) / 2;
    mergesort(v, ini, medio);
    mergesort(v, medio, fin);
    mezclar(v, ini, medio, fin);
}
void mergesort(vector<int>& v) { mergesort(v, 0, (int)v.size()); }

// 3) PARTICIONAR (el corazón de quicksort), esquema de Lomuto.
//    Pivote = v[fin] (el ÚLTIMO, como en la lección).
//    i marca dónde va el siguiente «pequeño». Para j de ini a fin-1:
//    si v[j] <= pivote, es decir, si !menor(pivote, v[j]),
//    intercambia v[i] y v[j] e incrementa i.
//    Al final pon el pivote en su sitio: swap(v[i], v[fin]); return i;
int particionar(vector<int>& v, int ini, int fin) {
    int pivote = v[fin];
    int i = ini;                          // aquí irá el siguiente «pequeño»
    for (int j = ini; j < fin; j++) {
        if (!menor(pivote, v[j])) {       // v[j] <= pivote
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[fin]);                   // el pivote, a su sitio definitivo
    return i;
}

// Ya está hecha: ordena v[ini..fin] (¡fin incluido!).
void quicksort(vector<int>& v, int ini, int fin) {
    if (ini >= fin) return;
    int p = particionar(v, ini, fin);    // el pivote ya está en su sitio final
    quicksort(v, ini, p - 1);
    quicksort(v, p + 1, fin);
}
void quicksort(vector<int>& v) { quicksort(v, 0, (int)v.size() - 1); }

// 4) ESTABILIDAD. Ordena por nota de menor a mayor. Si dos alumnos
//    empatan, deben quedar en el MISMO orden en que venían.
//    Usa std::stable_sort con una lambda que compare solo la nota.
struct Alumno {
    string nombre;
    int nota;
};
void ordenarPorNota(vector<Alumno>& alumnos) {
    stable_sort(alumnos.begin(), alumnos.end(),
                [](const Alumno& a, const Alumno& b) { return a.nota < b.nota; });
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Números «al azar» pero siempre los mismos (para que la prueba se repita igual).
vector<int> pseudoAzar(int n) {
    vector<int> v;
    unsigned x = 12345;
    for (int i = 0; i < n; i++) {
        x = x * 1103515245u + 12345u;
        v.push_back((int)((x / 65536) % 1000));
    }
    return v;
}
vector<int> creciente(int n) { vector<int> v; for (int i = 0; i < n; i++) v.push_back(i); return v; }
vector<int> decreciente(int n) { vector<int> v; for (int i = n; i > 0; i--) v.push_back(i); return v; }

// ¿El algoritmo f deja v igual que std::sort?
bool ordenaBien(void (*f)(vector<int>&), vector<int> v) {
    vector<int> esperado = v;
    sort(esperado.begin(), esperado.end());
    f(v);
    return v == esperado;
}
bool ordenaTodo(void (*f)(vector<int>&)) {
    return ordenaBien(f, {5, 2, 4, 1, 3}) && ordenaBien(f, {}) && ordenaBien(f, {7})
        && ordenaBien(f, {3, 1, 3, 1, 2}) && ordenaBien(f, {-4, 10, 0, -9})
        && ordenaBien(f, pseudoAzar(500));
}
long long contar(void (*f)(vector<int>&), vector<int> v) {
    comparaciones = 0;
    f(v);
    return comparaciones;
}

int main() {
    cout << "inserción:\n";
    comprobar(ordenaTodo(insercion), "ordena (vacío, uno, repetidos, negativos, 500 al azar)");
    comprobar(contar(insercion, creciente(100)) == 99,
              "ya ordenado de 100: 99 comparaciones (su mejor caso, O(n))");
    comprobar(contar(insercion, decreciente(100)) == 4950,
              "al revés de 100: 4950 comparaciones (su peor caso, O(n²))");

    cout << "mergesort:\n";
    comprobar(ordenaTodo(mergesort), "ordena (vacío, uno, repetidos, negativos, 500 al azar)");
    long long cm = contar(mergesort, pseudoAzar(1024));
    long long ci = contar(insercion, pseudoAzar(1024));
    comprobar(cm > 0 && cm <= 10240, "1024 al azar: como mucho 1024·log2(1024) = 10240 comparaciones");
    comprobar(cm > 0 && ci > 10 * cm, "en esos 1024, inserción compara más de 10 veces más");

    cout << "quicksort:\n";
    comprobar(ordenaTodo(quicksort), "ordena (vacío, uno, repetidos, negativos, 500 al azar)");
    long long cq = contar(quicksort, pseudoAzar(1000));
    comprobar(cq > 0 && cq <= 30000, "1000 al azar: menos de 30000 comparaciones (caso promedio)");
    comprobar(contar(quicksort, creciente(100)) == 4950,
              "ya ordenado de 100 con pivote = último: 4950 (¡su PEOR caso!)");

    cout << "estabilidad:\n";
    {
        vector<Alumno> a = {{"Ana", 8}, {"Beto", 6}, {"Caro", 8}, {"Dani", 6}, {"Eva", 9}};
        ordenarPorNota(a);
        string orden;
        for (const Alumno& x : a) orden += x.nombre + " ";
        comprobar(orden == "Beto Dani Ana Caro Eva ",
                  "por nota: Beto Dani Ana Caro Eva (los empates conservan su orden)");
    }

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 5.5 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
