// SOLUCIÓN — Miniproyecto 1.1 — Tus primeras salidas con cout
// Ábrela solo después de intentarlo de verdad.
// ---------------------------------------------------------------
// Completa las TRES partes marcadas con TODO. No toques lo de abajo.
//
// Escribe SOLO dentro de las llaves { } de cada parte.
// Cada parte es una "función": un trozo de programa con nombre.
// Qué es una función de verdad lo verás en la lección 1.6; por ahora
// piensa en cada una como un mini-main().
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 01-primer-programa.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <sstream>   // solo lo usan las pruebas de abajo
#include <string>
using namespace std;

// 1) Muestra EXACTAMENTE esta línea (con salto de línea al final):
//        ¡Hola, mundo!
//    Pista: cout << "texto" << "\n";
void saludar() {
    cout << "¡Hola, mundo!" << "\n";
}

// 2) Muestra este cuadro de TRES líneas, exactamente igual
//    (sin espacios de más al final de cada línea):
//        +-------+
//        |  C++  |
//        +-------+
//    Pista: un cout por línea, cada uno terminado en "\n".
void cuadro() {
    cout << "+-------+" << "\n";
    cout << "|  C++  |" << "\n";
    cout << "+-------+" << "\n";
}

// 3) Muestra la suma de a y b con este formato:
//        2 + 3 = 5
//    La línea de abajo ya muestra "2 + 3 = ?". Cambia el ? por la suma.
//    Pista: cout puede mostrar una cuenta: cout << a + b;
void sumaEnPantalla(int a, int b) {
    cout << a << " + " << b << " = " << a + b << "\n";
}

// ----------------- Pruebas automáticas (no tocar) -----------------
// Truco: mientras corre cada prueba, lo que mandas a cout se guarda
// en un texto en lugar de salir en pantalla, y luego se compara.
ostringstream captura;
streambuf* pantalla = nullptr;
void empezarCaptura() { captura.str(""); pantalla = cout.rdbuf(captura.rdbuf()); }
string terminarCaptura() { cout.rdbuf(pantalla); return captura.str(); }

int fallos = 0;
void comprobar(bool ok, const string& que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    string salida;

    cout << "saludar:\n";
    empezarCaptura(); saludar(); salida = terminarCaptura();
    comprobar(salida.find("Hola, mundo") != string::npos, "dice «Hola, mundo»");
    comprobar(salida == "¡Hola, mundo!\n", "es exactamente «¡Hola, mundo!» y un salto de línea");

    cout << "cuadro:\n";
    empezarCaptura(); cuadro(); salida = terminarCaptura();
    comprobar(salida == "+-------+\n|  C++  |\n+-------+\n", "las tres líneas del cuadro, exactas");

    cout << "sumaEnPantalla:\n";
    empezarCaptura(); sumaEnPantalla(2, 3); salida = terminarCaptura();
    comprobar(salida == "2 + 3 = 5\n", "2 y 3     ->  «2 + 3 = 5»");
    empezarCaptura(); sumaEnPantalla(-4, 4); salida = terminarCaptura();
    comprobar(salida == "-4 + 4 = 0\n", "-4 y 4    ->  «-4 + 4 = 0»");
    empezarCaptura(); sumaEnPantalla(100, 250); salida = terminarCaptura();
    comprobar(salida == "100 + 250 = 350\n", "100 y 250 ->  «100 + 250 = 350»");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.1 terminado.\n"
                         : "\nAún hay fallos. Revisa las partes con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
