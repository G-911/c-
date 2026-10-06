// SOLUCIÓN — Miniproyecto 1.6 — Funciones
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (dentro de la carpeta soluciones):
//   g++ -std=c++17 -Wall 06-funciones.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
using namespace std;

// Prototipos: le dicen al compilador que estas funciones existen.
bool esBisiesto(int anio);
int maximo(int a, int b);
int maximo(int a, int b, int c);
long long potencia(int base, int exponente = 2);
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

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

int maximo(int a, int b, int c) {
    return maximo(maximo(a, b), c);      // reutiliza la versión de dos
}

// El valor por defecto (= 2) va SOLO en el prototipo, no aquí.
long long potencia(int base, int exponente) {
    long long resultado = 1;
    for (int i = 0; i < exponente; i++) {
        resultado *= base;
    }
    return resultado;
}

double aFahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

int diasDelMes(int mes, int anio) {
    switch (mes) {
        case 2:
            return esBisiesto(anio) ? 29 : 28;   // una función que usa otra
        case 4: case 6: case 9: case 11:
            return 30;
        default:
            return 31;
    }
}
