// Miniproyecto 1.8 — vector
// ---------------------------------------------------------------
// Completa las SEIS funciones marcadas con TODO. No toques main().
// Es el último miniproyecto del Nivel 1.
//
// Las líneas (void)x; solo callan un aviso del compilador mientras
// no usas ese parámetro. Bórralas cuando escribas tu código.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 08-vector.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1) Promedio de los elementos. Si el vector está vacío, devuelve 0.
//    Pista: v.empty() primero. Luego un for de rango para sumar, y
//    static_cast<double>(suma) / v.size() para que no sea división entera.
double promedio(vector<int> v) {
    (void)v;
    // TODO
    return 0.0;
}

// 2) Un vector NUEVO solo con los elementos mayores que limite,
//    en el mismo orden.  {5,1,8,3,9} con limite 4 -> {5,8,9}
//    Pista: vector<int> resultado; ... resultado.push_back(x);
vector<int> mayoresQue(vector<int> v, int limite) {
    (void)v; (void)limite;
    vector<int> resultado;
    // TODO
    return resultado;
}

// 3) Un vector NUEVO con los elementos al revés. {1,2,3} -> {3,2,1}
//    Pista: recorre v desde el último índice hasta 0 con un for normal.
//    Empieza en static_cast<int>(v.size()) - 1 para no mezclar tipos.
vector<int> invertido(vector<int> v) {
    (void)v;
    vector<int> resultado;
    // TODO
    return resultado;
}

// 4) Cuántas veces aparece palabra en la lista.
//    Pista: for (string p : lista) y compara con ==.
int contarPalabra(vector<string> lista, string palabra) {
    (void)lista; (void)palabra;
    // TODO
    return 0;
}

// 5) Matriz identidad n x n: 1 en la diagonal, 0 en el resto.
//    identidad(3) = {{1,0,0},
//                    {0,1,0},
//                    {0,0,1}}
//    Pista: vector<vector<int>> m(n, vector<int>(n, 0)); crea n filas
//    de n ceros. Después pon m[i][i] = 1.
vector<vector<int>> identidad(int n) {
    (void)n;
    vector<vector<int>> m;
    // TODO
    return m;
}

// 6) La suma de cada fila de una matriz. Las filas pueden medir distinto
//    (incluso estar vacías).  {{1,2,3},{10},{}} -> {6,10,0}
//    Pista: dos for de rango anidados: uno para las filas, otro dentro.
vector<int> sumaPorFila(vector<vector<int>> m) {
    (void)m;
    vector<int> sumas;
    // TODO
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
