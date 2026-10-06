// Miniproyecto 3.1 — Cinco funciones recursivas
// ---------------------------------------------------------------
// Completa las CINCO funciones marcadas con TODO. No toques main().
// Regla: SIN bucles (ni for ni while). Cada función se resuelve con
// un caso base y un caso recursivo que se llama a sí misma.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 01-recursion.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
using namespace std;

// 1) n! = n · (n-1) · ... · 1.   0! = 1 y 1! = 1.
//    Pista: caso base n <= 1; caso recursivo n * factorial(n - 1).
long long factorial(int n) {
    (void)n;  // evita un aviso del compilador; bórrala al empezar
    return 0; // TODO
}

// 2) Suma de los n primeros elementos de arr. Con n == 0 la suma es 0.
//    Pista: el último (arr[n - 1]) + la suma de los n - 1 primeros.
int sumarArreglo(const int arr[], int n) {
    (void)arr; (void)n;  // bórrala al empezar
    return 0; // TODO
}

// 3) base elevado a exp, con exp >= 0.  potencia(2, 10) = 1024.
//    Pista: cualquier número elevado a 0 vale 1;
//           base^exp = base * base^(exp - 1).
int potencia(int base, int exp) {
    (void)base; (void)exp;  // bórrala al empezar
    return 0; // TODO
}

// 4) Cuántas cifras tiene n (n >= 0).  0 tiene 1 cifra; 12345 tiene 5.
//    Pista: si n < 10, tiene 1 cifra. Si no, n / 10 le quita la última:
//           cifras de n = 1 + cifras de n / 10.
int contarDigitos(int n) {
    (void)n;  // bórrala al empezar
    return 0; // TODO
}

// 5) El mayor elemento de arr (n >= 1: el arreglo nunca está vacío).
//    Pista: con un solo elemento, el mayor es arr[0].
//           Si no: calcula el mayor de los n - 1 primeros y compáralo
//           con el último, arr[n - 1].
int maximo(const int arr[], int n) {
    (void)arr; (void)n;  // bórrala al empezar
    return 0; // TODO
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "factorial:\n";
    comprobar(factorial(0) == 1,        "0! = 1 (caso base)");
    comprobar(factorial(15) == 1307674368000LL, "15! = 1307674368000 (no cabe en int)");

    cout << "sumarArreglo:\n";
    int datos[] = {4, 1, 7, -2, 10};
    comprobar(sumarArreglo(datos, 0) == 0,  "arreglo vacío suma 0");
    comprobar(sumarArreglo(datos, 5) == 20, "{4,1,7,-2,10} suma 20");

    cout << "potencia:\n";
    comprobar(potencia(2, 10) == 1024, "2^10 = 1024");
    comprobar(potencia(7, 0) == 1,     "7^0 = 1 (caso base)");

    cout << "contarDigitos:\n";
    comprobar(contarDigitos(0) == 1,      "0 tiene 1 cifra");
    comprobar(contarDigitos(12345) == 5,  "12345 tiene 5 cifras");

    cout << "maximo:\n";
    int negativos[] = {-5, -2, -9};
    int alFinal[] = {3, 8, 1, 15};
    comprobar(maximo(negativos, 3) == -2,  "{-5,-2,-9}: el mayor es -2");
    comprobar(maximo(alFinal, 4) == 15,    "{3,8,1,15}: el mayor está al final");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.1 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
