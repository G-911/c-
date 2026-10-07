// SOLUCIÓN del Miniproyecto 6.5 — La caja de herramientas moderna
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (C++23 por ranges::to):
//   g++ -std=c++23 -Wall -pthread 05-biblioteca-moderna.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <optional>      // C++17
#include <variant>       // C++17
#include <string>
#include <string_view>   // C++17
#include <span>          // C++20
#include <format>        // C++20
#include <ranges>        // C++20 (ranges::to es C++23)
#include <vector>
using namespace std;

// ---------- Parte A: optional, string_view y span ----------

// 1) Convierte el texto en un int. Acepta un '-' opcional al principio
//    y luego SOLO dígitos (entre 1 y 9). Si no, devuelve nullopt.
optional<int> aEntero(string_view s) {
    bool negativo = false;
    if (!s.empty() && s[0] == '-') {
        negativo = true;
        s.remove_prefix(1);          // la vista avanza; el texto no se toca
    }
    if (s.empty() || s.size() > 9) return nullopt;
    int valor = 0;
    for (char c : s) {
        if (c < '0' || c > '9') return nullopt;
        valor = valor * 10 + (c - '0');
    }
    return negativo ? -valor : valor;
}

// 2) Devuelve la posición de la PRIMERA aparición de x, o nullopt.
optional<int> posicionDe(span<const int> datos, int x) {
    for (int i = 0; i < (int)datos.size(); i++)
        if (datos[i] == x) return i;
    return nullopt;
}

// 3) Devuelve una vista de la primera palabra (hasta el primer espacio).
//    Si no hay espacio, la vista entera. SIN copiar el texto.
string_view primeraPalabra(string_view s) {
    size_t espacio = s.find(' ');
    if (espacio == string_view::npos) return s;
    return s.substr(0, espacio);     // substr de una vista es otra vista
}

// ---------- Parte B: variant y visit ----------

struct Circulo    { double radio; };
struct Rectangulo { double ancho, alto; };
struct Triangulo  { double base, altura; };
using Figura = variant<Circulo, Rectangulo, Triangulo>;

const double PI = 3.14159;

// 4) Un operator() por cada tipo que puede guardar Figura.
struct CalculaArea {
    double operator()(const Circulo& c) const    { return PI * c.radio * c.radio; }
    double operator()(const Rectangulo& r) const { return r.ancho * r.alto; }
    double operator()(const Triangulo& t) const  { return t.base * t.altura / 2; }
};

// 5) El área de cualquier figura, con visit.
double area(const Figura& f) {
    return visit(CalculaArea{}, f);
}

// 6) Cuántas figuras del vector son círculos.
int contarCirculos(const vector<Figura>& figuras) {
    int n = 0;
    for (const Figura& f : figuras)
        if (holds_alternative<Circulo>(f)) n++;
    return n;
}

// ---------- Parte C: ranges y format ----------

// 7) Los cuadrados de los k primeros números PARES de v, en orden.
vector<int> cuadradosDePares(const vector<int>& v, int k) {
    return v | views::filter([](int x) { return x % 2 == 0; })
             | views::transform([](int x) { return x * x; })
             | views::take(k)
             | ranges::to<vector>();
}

// 8) "nombre: precio" con el precio a 2 decimales. Ej.: "pan: 1.50".
string etiqueta(string_view nombre, double precio) {
    return format("{}: {:.2f}", nombre, precio);
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

bool cerca(double a, double b) { return a - b < 1e-9 && b - a < 1e-9; }

int main() {
    cout << "Parte A · optional, string_view y span:\n";
    comprobar(aEntero("42") == 42 && aEntero("-17") == -17, "aEntero(\"42\") = 42 y aEntero(\"-17\") = -17");
    comprobar(!aEntero("") && !aEntero("-") && !aEntero("4a") && !aEntero(" 4"),
              "\"\", \"-\", \"4a\" y \" 4\" no son enteros: nullopt");
    comprobar(!aEntero("1234567890") && aEntero("123456789") == 123456789,
              "con más de 9 dígitos: nullopt");
    {
        int arr[] = {7, 3, 9, 3};
        vector<int> v = {5, 6};
        comprobar(posicionDe(arr, 3) == 1, "posicionDe([7,3,9,3], 3) = 1 (la primera)");
        comprobar(!posicionDe(v, 8) && posicionDe(v, 6) == 1,
                  "con un vector: 8 no está (nullopt) y 6 está en 1");
    }
    {
        string frase = "hola mundo";
        string_view p = primeraPalabra(frase);
        comprobar(p == "hola" && p.data() == frase.data(),
                  "primeraPalabra(\"hola mundo\") = \"hola\" y mira el MISMO texto (sin copiar)");
        comprobar(primeraPalabra("adios") == "adios", "sin espacios: la frase entera");
    }

    cout << "Parte B · variant y visit:\n";
    comprobar(cerca(area(Rectangulo{2, 3}), 6) && cerca(area(Triangulo{4, 5}), 10),
              "área del rectángulo 2x3 = 6 y del triángulo 4x5 = 10");
    comprobar(cerca(area(Circulo{1}), PI), "área del círculo de radio 1 = PI");
    {
        vector<Figura> figs = {Circulo{1}, Rectangulo{1, 1}, Circulo{2}, Triangulo{1, 1}};
        comprobar(contarCirculos(figs) == 2, "en [círculo, rectángulo, círculo, triángulo] hay 2 círculos");
    }

    cout << "Parte C · ranges y format:\n";
    comprobar(cuadradosDePares({1, 2, 3, 4, 5, 6, 8}, 3) == vector<int>{4, 16, 36},
              "cuadradosDePares([1,2,3,4,5,6,8], 3) = [4,16,36]");
    comprobar(cuadradosDePares({1, 3, 5}, 2).empty() && cuadradosDePares({2, 4}, 5) == vector<int>{4, 16},
              "sin pares: vacío; si piden más de los que hay: los que haya");
    comprobar(etiqueta("pan", 1.5) == "pan: 1.50" && etiqueta("leche", 0.999) == "leche: 1.00",
              "etiqueta(\"pan\", 1.5) = \"pan: 1.50\" (dos decimales, redondeado)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.5 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
