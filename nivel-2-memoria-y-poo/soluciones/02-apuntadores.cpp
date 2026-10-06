// SOLUCIÓN — Miniproyecto 2.2 — Apuntadores (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Completa las DOS funciones marcadas con TODO. No toques main().
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 02-apuntadores.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
using namespace std;

// 1) Intercambia los valores de las dos variables a las que apuntan a y b.
//    Ejemplo: si x = 3 y y = 8, después de intercambiar(&x, &y)
//    queda x = 8 y y = 3.
//    Pista: necesitas una variable auxiliar.
void intercambiar(int* a, int* b) {
    int aux = *a; *a = *b; *b = aux;
}

// 2) Recorre el arreglo y deja el menor valor en *menor y el mayor en *mayor.
//    Así una función "devuelve" DOS resultados a la vez.
//    Pista: empieza con *menor = arr[0] y *mayor = arr[0].
void minMax(int arr[], int n, int* menor, int* mayor) {
    *menor = arr[0]; *mayor = arr[0];
    for (int i = 1; i < n; i++) { if (arr[i] < *menor) *menor = arr[i]; if (arr[i] > *mayor) *mayor = arr[i]; }
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "intercambiar:\n";
    int x = 3, y = 8;
    intercambiar(&x, &y);
    comprobar(x == 8 && y == 3, "x=3, y=8  ->  x=8, y=3");
    int p = -5, q = -5;
    intercambiar(&p, &q);
    comprobar(p == -5 && q == -5, "dos valores iguales siguen iguales");

    cout << "minMax:\n";
    int datos[] = {7, 2, 9, -4, 5};
    int menor = 0, mayor = 0;
    minMax(datos, 5, &menor, &mayor);
    comprobar(menor == -4, "el menor de {7,2,9,-4,5} es -4");
    comprobar(mayor == 9,  "el mayor de {7,2,9,-4,5} es 9");
    int uno[] = {42};
    minMax(uno, 1, &menor, &mayor);
    comprobar(menor == 42 && mayor == 42, "con un solo elemento, menor = mayor = 42");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 2.2 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
