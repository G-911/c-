// SOLUCIÓN — Miniproyecto 1.8 — vector
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (dentro de la carpeta soluciones):
//   g++ -std=c++17 -Wall 08-vector.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1) Promedio de los elementos. Si el vector está vacío, 0.
double promedio(vector<int> v) {
    if (v.empty()) return 0.0;            // evita dividir entre 0
    int suma = 0;
    for (int x : v) suma += x;
    return static_cast<double>(suma) / v.size();
}

// 2) Un vector NUEVO con los elementos mayores que limite, en orden.
vector<int> mayoresQue(vector<int> v, int limite) {
    vector<int> resultado;
    for (int x : v) {
        if (x > limite) resultado.push_back(x);
    }
    return resultado;
}

// 3) Un vector NUEVO con los elementos al revés.
vector<int> invertido(vector<int> v) {
    vector<int> resultado;
    for (int i = static_cast<int>(v.size()) - 1; i >= 0; i--) {
        resultado.push_back(v[i]);
    }
    return resultado;
}

// 4) Cuántas veces aparece palabra en la lista.
int contarPalabra(vector<string> lista, string palabra) {
    int cuenta = 0;
    for (string p : lista) {
        if (p == palabra) cuenta++;
    }
    return cuenta;
}

// 5) Matriz identidad n x n: 1 en la diagonal, 0 en el resto.
vector<vector<int>> identidad(int n) {
    vector<vector<int>> m(n, vector<int>(n, 0));   // n filas de n ceros
    for (int i = 0; i < n; i++) {
        m[i][i] = 1;
    }
    return m;
}

// 6) Suma de cada fila de una matriz (las filas pueden medir distinto).
vector<int> sumaPorFila(vector<vector<int>> m) {
    vector<int> sumas;
    for (vector<int> fila : m) {
        int s = 0;
        for (int x : fila) s += x;
        sumas.push_back(s);
    }
    return sumas;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "promedio:\n";
    comprobar(promedio({2, 4, 9}) == 5.0, "promedio de {2,4,9} = 5");
    comprobar(promedio({1, 2}) == 1.5, "promedio de {1,2} = 1.5 (división real)");
    comprobar(promedio({}) == 0.0, "vector vacío -> 0");

    cout << "mayoresQue:\n";
    comprobar(mayoresQue({5, 1, 8, 3, 9}, 4) == vector<int>{5, 8, 9}, "{5,1,8,3,9} mayores que 4 -> {5,8,9}");
    comprobar(mayoresQue({1, 2}, 10).empty(), "si ninguno pasa, vector vacío");

    cout << "invertido:\n";
    comprobar(invertido({1, 2, 3}) == vector<int>{3, 2, 1}, "{1,2,3} -> {3,2,1}");
    comprobar(invertido({}).empty(), "vacío -> vacío");

    cout << "contarPalabra:\n";
    vector<string> lista = {"pila", "cola", "pila", "lista"};
    comprobar(contarPalabra(lista, "pila") == 2, "\"pila\" aparece 2 veces");
    comprobar(contarPalabra(lista, "arbol") == 0, "\"arbol\" no aparece");

    cout << "identidad:\n";
    vector<vector<int>> esperada = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    comprobar(identidad(3) == esperada, "identidad(3) = {{1,0,0},{0,1,0},{0,0,1}}");
    comprobar(identidad(0).empty(), "identidad(0) no tiene filas");

    cout << "sumaPorFila:\n";
    comprobar(sumaPorFila({{1, 2, 3}, {10}, {}}) == vector<int>{6, 10, 0}, "{{1,2,3},{10},{}} -> {6,10,0}");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.8 terminado. ¡Nivel 1 completo!\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
