// Miniproyecto 2.1 — Referencias y const
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO. No toques main().
// Fíjate en los parámetros: unos llevan &, otros const &. Esa es la lección.
// Las líneas  (void)algo;  solo callan un aviso del compilador mientras la
// función está vacía: bórralas cuando escribas la tuya.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 01-referencias-y-const.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;

// 1) Deja en a el MENOR de los dos y en b el MAYOR.
//    Ejemplo: si x = 8 y y = 3, después de ordenarDos(x, y)
//    queda x = 3 y y = 8. Si ya estaban en orden, no cambia nada.
//    Pista: si a > b, intercámbialos con una variable auxiliar.
void ordenarDos(int& a, int& b) {
    // TODO
    (void)a; (void)b;   // calla un aviso del compilador: bórrala al empezar
}

// 2) Multiplica por 2 CADA elemento del vector de quien llama.
//    Pista: un for de rango con int& (con int a secas cambiarías copias).
void duplicarTodos(vector<int>& v) {
    // TODO
    (void)v;   // bórrala al empezar
}

// 3) Cuenta cuántos elementos son MAYORES que limite.
//    El vector llega por const &: no se copia y no se puede cambiar.
//    Pista: un contador que empieza en 0 y un if dentro del for.
int contarMayores(const vector<int>& v, int limite) {
    // TODO
    (void)v; (void)limite;   // bórrala al empezar
    return 0;
}

// 4) Deja en positivos cuántos elementos son > 0
//    y en negativos cuántos son < 0. El cero no cuenta en ninguno.
//    Así una función "devuelve" DOS resultados a la vez.
//    Pista: pon los dos a 0 al empezar; quien llama puede traer basura.
void contarSignos(const vector<int>& v, int& positivos, int& negativos) {
    // TODO
    (void)v; (void)positivos; (void)negativos;   // bórrala al empezar
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "ordenarDos:\n";
    int x = 8, y = 3;
    ordenarDos(x, y);
    comprobar(x == 3 && y == 8, "x=8, y=3  ->  x=3, y=8");
    int p = 1, q = 5;
    ordenarDos(p, q);
    comprobar(p == 1 && q == 5, "si ya estaban en orden, no cambian");
    int m = -2, n = -7;
    ordenarDos(m, n);
    comprobar(m == -7 && n == -2, "también con negativos: -2, -7  ->  -7, -2");

    cout << "duplicarTodos:\n";
    vector<int> v = {1, -3, 10};
    duplicarTodos(v);
    comprobar(v == vector<int>({2, -6, 20}), "{1,-3,10}  ->  {2,-6,20}");
    vector<int> vacio;
    duplicarTodos(vacio);
    comprobar(vacio.empty(), "un vector vacío sigue vacío");

    cout << "contarMayores:\n";
    vector<int> notas = {12, 7, 15, 10, 20};
    comprobar(contarMayores(notas, 10) == 3, "en {12,7,15,10,20} hay 3 mayores que 10");
    comprobar(contarMayores(notas, 100) == 0, "ninguno es mayor que 100");
    comprobar(contarMayores(notas, -1) == 5, "todos son mayores que -1");

    cout << "contarSignos:\n";
    vector<int> mezcla = {4, -1, 0, 9, -8, 0, 3};
    int pos = 99, neg = 99;   // basura a propósito
    contarSignos(mezcla, pos, neg);
    comprobar(pos == 3, "en {4,-1,0,9,-8,0,3} hay 3 positivos");
    comprobar(neg == 2, "y 2 negativos (los ceros no cuentan)");
    contarSignos(vacio, pos, neg);
    comprobar(pos == 0 && neg == 0, "con un vector vacío, los dos quedan en 0");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 2.1 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
