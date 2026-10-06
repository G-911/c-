// SOLUCIÓN — Miniproyecto 1.3 — Cuentas que no engañan
// Ábrela solo después de intentarlo de verdad.
// ---------------------------------------------------------------
// Completa las CINCO funciones marcadas con TODO. No toques main().
//
// Escribe SOLO dentro de las llaves { } de cada función (qué es una
// función lo verás en la 1.6). Cada una trae una línea de RELLENO para
// que compile desde el principio: cámbiala por tu solución.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 03-operadores.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// 1) ¿Cuántas horas COMPLETAS caben en esos minutos?  135 -> 2
//    Pista: entre dos int, / descarta los decimales.
int horasCompletas(int minutos) {
    return minutos / 60;
}

// 2) ¿Cuántos minutos SOBRAN después de quitar las horas?  135 -> 15
//    Pista: el operador % da el resto de la división.
int minutosSobrantes(int minutos) {
    return minutos % 60;
}

// 3) Promedio de dos enteros, CON decimales:  3 y 4 -> 3.5
//    OJO: (a + b) / 2 con int da 3, no 3.5.
//    Pista: static_cast<double>(a + b) / 2
double promedio(int a, int b) {
    return static_cast<double>(a + b) / 2;
}

// 4) ¿Es impar n?  7 -> true,  10 -> false,  -3 -> true
//    OJO: en C++, -3 % 2 vale -1, no 1. Compara con 0.
bool esImpar(int n) {
    return n % 2 != 0;   // con "== 1" fallaría para -3
}

// 5) Puede entrar al concierto quien tenga 18 años o más
//    Y además tenga entrada.
//    Pista: dos condiciones a la vez se unen con &&
bool puedeEntrar(int edad, bool tieneEntrada) {
    return edad >= 18 && tieneEntrada;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const string& que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

bool casiIgual(double a, double b) {
    double diferencia = a - b;
    if (diferencia < 0) diferencia = -diferencia;
    return diferencia < 0.0001;
}

int main() {
    cout << "horasCompletas y minutosSobrantes:\n";
    comprobar(horasCompletas(135) == 2 && minutosSobrantes(135) == 15, "135 min -> 2 h y 15 min");
    comprobar(horasCompletas(59) == 0 && minutosSobrantes(59) == 59, "59 min  -> 0 h y 59 min");
    comprobar(horasCompletas(60) == 1 && minutosSobrantes(60) == 0, "60 min  -> 1 h y 0 min");

    cout << "promedio:\n";
    comprobar(casiIgual(promedio(3, 4), 3.5), "3 y 4  -> 3.5 (no 3)");
    comprobar(casiIgual(promedio(-1, 0), -0.5), "-1 y 0 -> -0.5");

    cout << "esImpar:\n";
    comprobar(esImpar(7) && !esImpar(10), "7 es impar, 10 no");
    comprobar(esImpar(-3), "-3 es impar (aunque -3 % 2 sea -1)");

    cout << "puedeEntrar:\n";
    comprobar(puedeEntrar(18, true), "18 años con entrada: entra");
    comprobar(!puedeEntrar(17, true) && !puedeEntrar(30, false), "17 con entrada o 30 sin entrada: no entra");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.3 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
