// SOLUCIÓN del Miniproyecto 6.4 — Plantillas que saben lo que piden
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (en la terminal, dentro de esta carpeta).
// Hace falta C++20 por los concepts:
//   g++ -std=c++20 -Wall -pthread 04-plantillas-avanzadas-y-concepts.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <sstream>       // ostringstream
#include <string>
#include <type_traits>   // is_integral_v, is_floating_point_v, is_same_v
#include <vector>
using namespace std;

// 1) ESPECIALIZACIÓN TOTAL.
//    nombreDeTipo<T>() devuelve "desconocido" para cualquier T.
//    Añade DEBAJO dos especializaciones totales:
//      nombreDeTipo<int>()    -> "int"
//      nombreDeTipo<double>() -> "double"
//    Pista: template <>
//           string nombreDeTipo<int>() { return "int"; }
template <typename T>
string nombreDeTipo() {
    return "desconocido";
}
// template <> = «esta es la versión para un tipo CONCRETO de la plantilla de arriba».
template <>
string nombreDeTipo<int>() {
    return "int";
}

template <>
string nombreDeTipo<double>() {
    return "double";
}


// 2) PLANTILLA VARIÁDICA + FOLD.
//    Devuelve un texto con cada argumento seguido de UN espacio.
//    unirConEspacios(1, "hola", 2.5)  ->  "1 hola 2.5 "
//    unirConEspacios()                ->  ""
//    Pista: ostringstream os;  ((os << args << ' '), ...);  return os.str();
template <typename... Args>
string unirConEspacios(const Args&... args) {
    ostringstream os;
    // Fold con la coma: se repite (os << arg << ' ') para cada argumento, en orden.
    // Con cero argumentos no se ejecuta nada y queda "".
    ((os << args << ' '), ...);
    return os.str();
}

// 3) FOLD CON VALOR INICIAL.
//    Suma todos los argumentos. Con CERO argumentos debe dar 0.
//    sumaTodo(1, 2, 3) -> 6     sumaTodo() -> 0
//    Pista: (args + ...) no compila con cero argumentos; empieza en 0.
template <typename... Args>
auto sumaTodo(const Args&... args) {
    // Fold binario por la izquierda: (((0 + a1) + a2) + a3).
    // Con cero argumentos queda solo el 0.
    return (0 + ... + args);
}

// 4) CONCEPT.
//    Numerico<T> debe ser verdadero si T es entero (int, long, char...)
//    o de coma flotante (double, float), y falso para todo lo demás.
//    Ahora mismo dice "true" para todo: cámbialo.
//    Pista: is_integral_v<T> || is_floating_point_v<T>
template <typename T>
concept Numerico = is_integral_v<T> || is_floating_point_v<T>;

// doble() ya está hecha y usa tu concept: solo acepta tipos Numerico.
template <Numerico T>
T doble(T x) {
    return x * 2;
}

// 5) IF CONSTEXPR + TYPE TRAITS.
//    describir(x) devuelve:
//      "entero"  si T es entero        (is_integral_v<T>)
//      "decimal" si T es de coma flotante (is_floating_point_v<T>)
//      "texto"   si T es string        (is_same_v<T, string>)
//      "otro"    en cualquier otro caso
//    Pista: if constexpr (...) return "..."; else if constexpr (...) ...
template <typename T>
string describir(const T& x) {
    (void)x;   // aquí el valor no hace falta: decide el TIPO
    // Solo se compila la rama elegida para cada T.
    if constexpr (is_integral_v<T>) return "entero";
    else if constexpr (is_floating_point_v<T>) return "decimal";
    else if constexpr (is_same_v<T, string>) return "texto";
    else return "otro";
}

// 6) CONSTEXPR.
//    factorial(n) = 1 * 2 * ... * n, y factorial(0) = 1.
//    Tiene que poder calcularse AL COMPILAR (la prueba usa una
//    variable constexpr: si no se puede, no compila).
//    Pista: un bucle for normal sirve dentro de una función constexpr.
constexpr long long factorial(int n) {
    long long r = 1;
    for (int i = 2; i <= n; i++) r *= i;
    return r;
}

// Extra: se comprueba AL COMPILAR. Si no diera 120, no compilaría.
static_assert(factorial(5) == 120);

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "especialización:\n";
    comprobar(nombreDeTipo<int>() == "int", "nombreDeTipo<int>() = \"int\"");
    comprobar(nombreDeTipo<double>() == "double", "nombreDeTipo<double>() = \"double\"");
    comprobar(nombreDeTipo<char>() == "desconocido", "nombreDeTipo<char>() = \"desconocido\"");

    cout << "variádicas y fold:\n";
    comprobar(unirConEspacios(1, "hola", 2.5) == "1 hola 2.5 ",
              "unirConEspacios(1, \"hola\", 2.5) = \"1 hola 2.5 \"");
    comprobar(unirConEspacios() == "", "unirConEspacios() = \"\"");
    comprobar(sumaTodo(1, 2, 3) == 6, "sumaTodo(1, 2, 3) = 6");
    comprobar(sumaTodo(1, 2.5) == 3.5, "sumaTodo(1, 2.5) = 3.5");
    comprobar(sumaTodo() == 0, "sumaTodo() = 0");

    cout << "concept Numerico:\n";
    comprobar(Numerico<int> && Numerico<double> && Numerico<char>,
              "int, double y char son Numerico");
    comprobar(!Numerico<string> && !Numerico<vector<int>>,
              "string y vector<int> NO son Numerico");
    comprobar(doble(21) == 42 && doble(1.5) == 3.0, "doble(21) = 42 y doble(1.5) = 3");

    cout << "if constexpr:\n";
    comprobar(describir(7) == "entero", "describir(7) = \"entero\"");
    comprobar(describir(2.5) == "decimal", "describir(2.5) = \"decimal\"");
    comprobar(describir(string("hola")) == "texto", "describir(string(\"hola\")) = \"texto\"");
    comprobar(describir(vector<int>{1, 2}) == "otro", "describir(vector) = \"otro\"");

    cout << "constexpr:\n";
    constexpr long long f5 = factorial(5);    // se calcula AL COMPILAR
    constexpr long long f0 = factorial(0);
    comprobar(f5 == 120, "factorial(5) = 120, calculado al compilar");
    comprobar(f0 == 1, "factorial(0) = 1");
    comprobar(factorial(20) == 2432902008176640000LL, "factorial(20) cabe en long long");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.4 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
