// Miniproyecto 1.6 — Funciones
// ---------------------------------------------------------------
// Completa las SEIS funciones marcadas con TODO (están al final del
// archivo, DESPUÉS de main). No toques main() ni los prototipos.
//
// Fíjate en el orden: main() usa las funciones antes de que aparezcan
// escritas. Funciona gracias a los PROTOTIPOS de arriba.
//
// Las líneas (void)x; solo callan un aviso del compilador mientras
// no usas ese parámetro. Bórralas cuando escribas tu código.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 06-funciones.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
using namespace std;

// Prototipos: le dicen al compilador que estas funciones existen.
bool esBisiesto(int anio);
int maximo(int a, int b);
int maximo(int a, int b, int c);                 // sobrecarga: mismo nombre, 3 parámetros
long long potencia(int base, int exponente = 2); // parámetro por defecto
double aFahrenheit(double celsius);
int diasDelMes(int mes, int anio);

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "esBisiesto:\n";
    comprobar(esBisiesto(2024), "2024 es bisiesto (divisible entre 4)");
    comprobar(!esBisiesto(2023), "2023 no es bisiesto");
    comprobar(!esBisiesto(1900), "1900 no es bisiesto (divisible entre 100)");
    comprobar(esBisiesto(2000), "2000 sí es bisiesto (divisible entre 400)");

    cout << "maximo (sobrecargada):\n";
    comprobar(maximo(3, 8) == 8 && maximo(8, 3) == 8, "maximo(3, 8) = 8 en cualquier orden");
    comprobar(maximo(-5, -2) == -2, "maximo(-5, -2) = -2");
    comprobar(maximo(4, 9, 7) == 9, "maximo(4, 9, 7) = 9");

    cout << "potencia (exponente por defecto = 2):\n";
    comprobar(potencia(5) == 25, "potencia(5) = 25 (usa el 2 por defecto)");
    comprobar(potencia(2, 10) == 1024, "potencia(2, 10) = 1024");
    comprobar(potencia(7, 0) == 1, "potencia(7, 0) = 1");

    cout << "aFahrenheit:\n";
    comprobar(aFahrenheit(100.0) == 212.0, "100 °C = 212 °F");
    comprobar(aFahrenheit(-40.0) == -40.0, "-40 °C = -40 °F");

    cout << "diasDelMes:\n";
    comprobar(diasDelMes(1, 2023) == 31 && diasDelMes(4, 2023) == 30, "enero 31, abril 30");
    comprobar(diasDelMes(2, 2023) == 28 && diasDelMes(2, 2024) == 29, "febrero 28, o 29 en bisiesto");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.6 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}

// ----------------- Tus funciones -----------------

// 1) Un año es bisiesto si es divisible entre 4 pero NO entre 100,
//    o si es divisible entre 400.  2024 sí, 1900 no, 2000 sí.
//    Pista: se puede hacer en un solo return con && y ||.
bool esBisiesto(int anio) {
    (void)anio;
    // TODO
    return false;
}

// 2) El mayor de dos números.
int maximo(int a, int b) {
    (void)a; (void)b;
    // TODO
    return 0;
}

// 3) El mayor de tres. Es una SOBRECARGA: mismo nombre, otros parámetros.
//    Pista: no repitas trabajo, llama a la versión de dos.
int maximo(int a, int b, int c) {
    (void)a; (void)b; (void)c;
    // TODO
    return 0;
}

// 4) base elevado a exponente (exponente >= 0). potencia(2, 10) = 1024.
//    Si llaman potencia(5), exponente vale 2 por defecto.
//    El "= 2" va SOLO en el prototipo de arriba, no aquí.
//    Pista: un for que multiplique "exponente" veces; empieza en 1.
long long potencia(int base, int exponente) {
    (void)base; (void)exponente;
    // TODO
    return 0;
}

// 5) Grados Celsius a Fahrenheit:  F = C * 9 / 5 + 32
//    Pista: usa 9.0 y 5.0 para que la división sea real, no entera.
double aFahrenheit(double celsius) {
    (void)celsius;
    // TODO
    return 0.0;
}

// 6) Días que tiene un mes (1 = enero ... 12 = diciembre).
//    Abril, junio, septiembre y noviembre: 30. Febrero: 28, o 29
//    si el año es bisiesto. El resto: 31.
//    Pista: un switch, y para febrero LLAMA a esBisiesto(anio).
int diasDelMes(int mes, int anio) {
    (void)mes; (void)anio;
    // TODO
    return 0;
}
