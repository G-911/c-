// Miniproyecto 1.2 — Elegir el tipo correcto
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO. No toques main().
//
// Escribe SOLO dentro de las llaves { } de cada función. Qué es una
// función lo verás en la lección 1.6. Por ahora te basta con esto:
//   - lo que va entre paréntesis (por ejemplo "double precio") es un
//     dato que ya te llega con valor;
//   - "return algo;" entrega el resultado.
// Cada función trae una línea de RELLENO para que compile desde el
// principio. Bórrala o cámbiala por tu solución.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 02-variables-y-tipos.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// 1) Devuelve el precio con el IVA del 16 % ya sumado.
//    Ejemplo: 100.0 -> 116.0
//    Pista: double total{precio * 1.16}; return total;
double precioConIva(double precio) {
    return precio;   // RELLENO: cambia esta línea
}

// 2) Devuelve un saludo con el nombre: "Ana" -> "Hola, Ana!"
//    Pista: con string, el + PEGA textos: "Hola, " + nombre
string saludo(string nombre) {
    return nombre;   // RELLENO: cambia esta línea
}

// 3) Devuelve cuántos segundos hay en esa cantidad de años
//    (años de 365 días). 1 año -> 31536000 segundos.
//    OJO: 100 años son más de 3 mil millones de segundos y eso
//    NO cabe en un int. Guarda la cuenta en un long long.
//    Pista: long long total{anios}; y luego multiplica total.
long long segundosEnAnios(int anios) {
    return anios;    // RELLENO: cambia esta línea
}

// 4) Devuelve el área de un círculo: PI * radio * radio.
//    Declara PI como constante: const double PI{3.14159};
double areaCirculo(double radio) {
    return radio;    // RELLENO: cambia esta línea
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const string& que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Los double no siempre son exactos (0.1 + 0.2 da 0.30000000000000004),
// así que se comparan con un margen pequeño.
bool casiIgual(double a, double b) {
    double diferencia = a - b;
    if (diferencia < 0) diferencia = -diferencia;
    return diferencia < 0.0001;
}

int main() {
    cout << "precioConIva:\n";
    comprobar(casiIgual(precioConIva(100.0), 116.0), "100     -> 116");
    comprobar(casiIgual(precioConIva(19.99), 23.1884), "19.99   -> 23.1884 (con decimales)");

    cout << "saludo:\n";
    comprobar(saludo("Ana") == "Hola, Ana!", "\"Ana\"   -> \"Hola, Ana!\"");
    comprobar(saludo("Luis Miguel") == "Hola, Luis Miguel!", "\"Luis Miguel\" -> \"Hola, Luis Miguel!\"");

    cout << "segundosEnAnios:\n";
    comprobar(segundosEnAnios(1) == 31536000LL, "1 año    -> 31536000");
    comprobar(segundosEnAnios(0) == 0LL, "0 años   -> 0");
    comprobar(segundosEnAnios(100) == 3153600000LL, "100 años -> 3153600000 (no cabe en int)");

    cout << "areaCirculo:\n";
    comprobar(casiIgual(areaCirculo(1.0), 3.14159), "radio 1   -> 3.14159");
    comprobar(casiIgual(areaCirculo(2.5), 19.6349375), "radio 2.5 -> 19.6349375");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.2 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
