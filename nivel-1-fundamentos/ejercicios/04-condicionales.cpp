// Miniproyecto 1.4 — El programa decide
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO. No toques main().
//
// Escribe SOLO dentro de las llaves { } de cada función (qué es una
// función lo verás en la 1.6). Cada una trae RELLENO para que compile
// desde el principio: bórralo y escribe tu solución.
//
// La línea  (void)nota;  solo le dice al compilador «ya sé que todavía
// no uso nota»; así no te avisa. Bórrala cuando escribas tu código.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 04-condicionales.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// 1) Clasifica una nota en la escala del 0 al 20:
//      menor que 0 o mayor que 20  -> "invalida"
//      de 0 a 9                    -> "reprobado"
//      de 10 a 15                  -> "aprobado"
//      de 16 a 20                  -> "excelente"
//    Pista: if / else if / else. Revisa primero los casos inválidos.
string clasificarNota(int nota) {
    (void)nota;       // RELLENO: bórralo
    return "";        // RELLENO: bórralo
}

// 2) Nombre del día de la semana con switch:
//      1 -> "lunes", 2 -> "martes", ..., 7 -> "domingo"
//      cualquier otro número -> "invalido"
//    Pista: cada case termina en return (o en break). Usa default.
string nombreDia(int dia) {
    (void)dia;        // RELLENO: bórralo
    return "";        // RELLENO: bórralo
}

// 3) Valor absoluto con el operador ternario, en UNA línea:
//      -5 -> 5,  7 -> 7,  0 -> 0
//    Pista: condición ? valor_si_true : valor_si_false
int valorAbsoluto(int n) {
    return n;         // RELLENO: cambia esta línea
}

// 4) ¿Es bisiesto el año? La regla del calendario:
//      divisible entre 4 -> bisiesto,
//      PERO si es divisible entre 100 -> no lo es,
//      SALVO que sea divisible entre 400 -> sí lo es.
//    Ejemplos: 2024 sí, 2023 no, 1900 no, 2000 sí.
//    Pista: "divisible entre 4" es  anio % 4 == 0
bool esBisiesto(int anio) {
    return anio < 0;  // RELLENO: cambia esta línea
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const string& que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "clasificarNota:\n";
    comprobar(clasificarNota(0) == "reprobado" && clasificarNota(9) == "reprobado", "0 y 9   -> reprobado");
    comprobar(clasificarNota(10) == "aprobado" && clasificarNota(15) == "aprobado", "10 y 15 -> aprobado (los bordes cuentan)");
    comprobar(clasificarNota(16) == "excelente" && clasificarNota(20) == "excelente", "16 y 20 -> excelente");
    comprobar(clasificarNota(-1) == "invalida" && clasificarNota(21) == "invalida", "-1 y 21 -> invalida");

    cout << "nombreDia:\n";
    comprobar(nombreDia(1) == "lunes" && nombreDia(3) == "miercoles", "1 -> lunes, 3 -> miercoles");
    comprobar(nombreDia(7) == "domingo", "7 -> domingo");
    comprobar(nombreDia(0) == "invalido" && nombreDia(8) == "invalido", "0 y 8 -> invalido (default)");

    cout << "valorAbsoluto:\n";
    comprobar(valorAbsoluto(-5) == 5 && valorAbsoluto(7) == 7 && valorAbsoluto(0) == 0, "-5 -> 5, 7 -> 7, 0 -> 0");

    cout << "esBisiesto:\n";
    comprobar(esBisiesto(2024) && !esBisiesto(2023), "2024 sí, 2023 no");
    comprobar(!esBisiesto(1900) && esBisiesto(2000), "1900 no (÷100), 2000 sí (÷400)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.4 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
