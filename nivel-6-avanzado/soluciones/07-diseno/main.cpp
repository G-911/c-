// SOLUCIÓN del Miniproyecto 6.7 — Un carrito con estrategia, fábrica, observador y PIMPL
// ---------------------------------------------------------------
// Este proyecto tiene CUATRO archivos:
//   descuentos.h → las estrategias de descuento: completa los TODO 1 y 2
//   carrito.h    → la cara pública del Carrito (PIMPL): no tocar
//   carrito.cpp  → el interior del Carrito: completa los TODO 3 y 4
//   main.cpp     → pruebas automáticas (no tocar)
//
// Compilar y probar (en la terminal, dentro de ESTA carpeta):
//   g++ -std=c++17 -Wall -pthread main.cpp carrito.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <cmath>      // fabs
#include <iostream>
#include <memory>
#include <utility>
#include "carrito.h"
using namespace std;

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Los double no se comparan con ==: se mira si están muy cerca.
bool casiIgual(double a, double b) { return fabs(a - b) < 1e-9; }

int main() {
    cout << "PIMPL (ya viene hecho):\n";
    comprobar(sizeof(Carrito) == sizeof(unique_ptr<int>),
              "el Carrito solo guarda un apuntador");

    cout << "TODO 1 · estrategia Porcentaje:\n";
    comprobar(casiIgual(Porcentaje(10).aplicar(200), 180), "10 % de 200  ->  180");
    comprobar(casiIgual(Porcentaje(100).aplicar(50), 0), "100 % de 50  ->  0");
    comprobar(casiIgual(Porcentaje(0).aplicar(80), 80), "0 % de 80  ->  80");

    cout << "TODO 2 · fábrica crearDescuento:\n";
    {
        auto d1 = crearDescuento("porcentaje", 25);
        comprobar(d1 && casiIgual(d1->aplicar(100), 75), "\"porcentaje\", 25  ->  100 queda en 75");
        auto d2 = crearDescuento("ninguno", 0);
        comprobar(d2 && casiIgual(d2->aplicar(100), 100), "\"ninguno\"  ->  100 queda en 100");
        comprobar(crearDescuento("dos-por-uno", 0) == nullptr, "un tipo desconocido  ->  nullptr");
    }

    cout << "TODO 3 · total con la estrategia:\n";
    {
        Carrito c;
        c.agregar("cuaderno", 20);
        c.agregar("lápiz", 10);
        comprobar(c.cantidad() == 2 && casiIgual(c.subtotal(), 30), "2 productos, subtotal 30");
        comprobar(casiIgual(c.total(), 30), "sin descuento, total 30");
        c.cambiarDescuento(make_unique<Porcentaje>(10));
        comprobar(casiIgual(c.total(), 27), "con Porcentaje(10), total 27");
        c.cambiarDescuento(nullptr);
        comprobar(casiIgual(c.total(), 30), "con nullptr vuelve a SinDescuento: total 30");
    }

    cout << "TODO 4 · observadores:\n";
    {
        Carrito c;
        int avisosA = 0, avisosB = 0;
        double ultimoTotal = -1;
        c.alCambiar([&](double t) { avisosA++; ultimoTotal = t; });
        c.alCambiar([&](double) { avisosB++; });
        c.agregar("mochila", 40);
        comprobar(avisosA == 1 && casiIgual(ultimoTotal, 40), "agregar avisa con el total nuevo (40)");
        c.cambiarDescuento(make_unique<Porcentaje>(50));
        comprobar(avisosA == 2 && casiIgual(ultimoTotal, 20), "cambiar el descuento también avisa (20)");
        comprobar(avisosB == 2, "se avisa a TODOS los observadores");
    }

    cout << "Mover y liberar:\n";
    {
        Carrito a;
        a.agregar("regla", 5);
        Carrito b = std::move(a);   // b se queda con el Impl de a: no se copia nada
        comprobar(b.cantidad() == 1 && implVivos == 1, "mover pasa el Impl entero (sigue habiendo 1)");
    }
    comprobar(implVivos == 0, "no quedan Impl sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.7 terminado.\n"
                         : "\nAún hay fallos. Revisa los TODO de las pruebas con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
