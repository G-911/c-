// Miniproyecto 1.5 — Bucles
// ---------------------------------------------------------------
// Completa las CINCO funciones marcadas con TODO. No toques main().
// Escribe solo dentro de las llaves de cada función: qué es una
// función exactamente lo verás en la lección 1.6. Por ahora piensa
// que "n" es un número que ya te dan y que "return" entrega el resultado.
//
// La línea (void)n; solo calla un aviso del compilador mientras no
// usas n. Bórrala cuando escribas tu código.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 05-bucles.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// 1) Suma 1 + 2 + ... + n. Si n es 0 o negativo, la suma es 0.
//    Ejemplo: sumaHasta(5) = 1+2+3+4+5 = 15.
//    Pista: un for de 1 a n y un acumulador que empieza en 0.
int sumaHasta(int n) {
    (void)n;
    // TODO
    return 0;
}

// 2) Factorial: n! = 1 * 2 * ... * n.  Por definición, 0! vale 1.
//    Pista: el acumulador de una multiplicación empieza en 1, no en 0.
long long factorial(int n) {
    (void)n;
    // TODO
    return 0;
}

// 3) Cuántas cifras tiene n. El 0 tiene UNA cifra. El signo no cuenta.
//    Pista: divide entre 10 hasta llegar a 0 y cuenta las vueltas.
//    Un do-while resuelve solo el caso del 0. Si n < 0, cámbiale el signo.
int contarDigitos(int n) {
    (void)n;
    // TODO
    return 0;
}

// 4) ¿n es primo? Es primo si es mayor que 1 y solo se divide
//    exactamente entre 1 y entre sí mismo. 2, 3, 5, 7, 11... lo son.
//    Pista: prueba divisores d = 2, 3, 4... mientras d * d <= n.
//    Si n % d == 0, ya sabes que no es primo: usa break (o return false).
bool esPrimo(int n) {
    (void)n;
    // TODO
    return false;
}

// 5) Devuelve un triángulo de asteriscos de n filas.
//    triangulo(3) devuelve "*\n**\n***\n", que al imprimirse se ve:
//        *
//        **
//        ***
//    Pista: bucle de filas; dentro, otro bucle que añade "*" tantas
//    veces como el número de la fila. Al final de cada fila, añade "\n".
string triangulo(int n) {
    (void)n;
    string dibujo = "";
    // TODO
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
