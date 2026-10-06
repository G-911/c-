// SOLUCIÓN — Miniproyecto 1.5 — Bucles
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (dentro de la carpeta soluciones):
//   g++ -std=c++17 -Wall 05-bucles.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// 1) Suma 1 + 2 + ... + n. Si n es 0 o negativo, la suma es 0.
int sumaHasta(int n) {
    int suma = 0;
    for (int i = 1; i <= n; i++) {     // si n <= 0, el bucle no da ni una vuelta
        suma += i;
    }
    return suma;
}

// 2) n! = 1 * 2 * ... * n.  0! vale 1.
long long factorial(int n) {
    long long resultado = 1;           // empieza en 1, no en 0: es una multiplicación
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

// 3) Cuántas cifras tiene n. El 0 tiene una cifra. El signo no cuenta.
int contarDigitos(int n) {
    if (n < 0) n = -n;
    int cifras = 0;
    do {                               // do-while: el 0 da UNA vuelta y cuenta 1
        cifras++;
        n /= 10;
    } while (n != 0);
    return cifras;
}

// 4) ¿n es primo? (mayor que 1 y solo divisible entre 1 y él mismo)
bool esPrimo(int n) {
    if (n < 2) return false;
    bool primo = true;
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            primo = false;
            break;                     // ya lo sabemos: no hace falta seguir
        }
    }
    return primo;
}

// 5) Triángulo de asteriscos con bucles anidados.
string triangulo(int n) {
    string dibujo = "";
    for (int fila = 1; fila <= n; fila++) {
        for (int col = 1; col <= fila; col++) {
            dibujo += "*";
        }
        dibujo += "\n";
    }
    return dibujo;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "sumaHasta:\n";
    comprobar(sumaHasta(5) == 15, "sumaHasta(5) = 15");
    comprobar(sumaHasta(1) == 1, "sumaHasta(1) = 1");
    comprobar(sumaHasta(0) == 0 && sumaHasta(-3) == 0, "con 0 o negativos la suma es 0");

    cout << "factorial:\n";
    comprobar(factorial(5) == 120, "factorial(5) = 120");
    comprobar(factorial(0) == 1, "factorial(0) = 1");

    cout << "contarDigitos:\n";
    comprobar(contarDigitos(12345) == 5, "12345 tiene 5 cifras");
    comprobar(contarDigitos(0) == 1, "0 tiene 1 cifra");
    comprobar(contarDigitos(-907) == 3, "-907 tiene 3 cifras");

    cout << "esPrimo:\n";
    comprobar(esPrimo(2) && esPrimo(13) && esPrimo(97), "2, 13 y 97 son primos");
    comprobar(!esPrimo(1) && !esPrimo(9) && !esPrimo(91), "1, 9 y 91 no son primos");

    cout << "triangulo:\n";
    comprobar(triangulo(3) == "*\n**\n***\n", "triangulo(3) tiene 3 filas: *, **, ***");
    comprobar(triangulo(0) == "", "triangulo(0) está vacío");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.5 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
