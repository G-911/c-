// SOLUCIÓN del Miniproyecto 4.2 — Contar, buscar y quitar repetidos
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar:
//   g++ -std=c++17 -Wall 02-stl-contenedores.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>   // pair
#include <vector>
using namespace std;

// 1) Cuenta cuántas veces aparece cada palabra.
//    {"sol","luna","sol"}  ->  {"luna":1, "sol":2}
map<string, int> contarPalabras(const vector<string>& palabras) {
    map<string, int> conteo;
    for (const string& p : palabras) {
        conteo[p]++;   // si p no estaba, [] la crea con 0 y luego suma 1
    }
    return conteo;
}

// 2) La palabra que más se repite y cuántas veces, como un pair.
//    Empate: gana la primera en orden alfabético (la que aparece antes al recorrer).
//    Mapa vacío: devuelve {"", 0}.
pair<string, int> masFrecuente(const map<string, int>& conteo) {
    pair<string, int> mejor = {"", 0};
    for (const auto& [palabra, veces] : conteo) {
        if (veces > mejor.second) {   // > estricto: en empate se queda la primera
            mejor = {palabra, veces};
        }
    }
    return mejor;
}

// 3) Los valores sin repetir y ordenados de menor a mayor.
//    {5,1,5,3,1}  ->  {1,3,5}
vector<int> unicosOrdenados(const vector<int>& v) {
    set<int> s(v.begin(), v.end());   // el set descarta repetidos y ordena solo
    return vector<int>(s.begin(), s.end());
}

// 4) La edad de alguien en la agenda, o -1 si no está.
//    OJO: agenda es const, así que agenda[nombre] NO compila. Usa find.
int buscarEdad(const unordered_map<string, int>& agenda, const string& nombre) {
    auto it = agenda.find(nombre);
    if (it == agenda.end()) return -1;
    return it->second;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "contarPalabras:\n";
    map<string, int> c = contarPalabras({"sol", "luna", "sol", "mar", "sol", "luna"});
    comprobar(c.size() == 3, "hay 3 palabras distintas");
    comprobar(c.count("sol") == 1 && c.at("sol") == 3, "\"sol\" aparece 3 veces");
    comprobar(c.count("mar") == 1 && c.at("mar") == 1, "\"mar\" aparece 1 vez");
    comprobar(contarPalabras({}).empty(), "sin palabras, el mapa queda vacío");

    cout << "masFrecuente:\n";
    comprobar(masFrecuente(c) == pair<string, int>{"sol", 3}, "la más frecuente es {\"sol\", 3}");
    comprobar(masFrecuente({{"b", 2}, {"a", 2}}) == pair<string, int>{"a", 2},
              "empate: gana la primera alfabéticamente {\"a\", 2}");
    comprobar(masFrecuente({}) == pair<string, int>{"", 0}, "mapa vacío -> {\"\", 0}");

    cout << "unicosOrdenados:\n";
    comprobar(unicosOrdenados({5, 1, 5, 3, 1}) == vector<int>{1, 3, 5}, "{5,1,5,3,1} -> {1,3,5}");
    comprobar(unicosOrdenados({7, 7, 7}) == vector<int>{7}, "{7,7,7} -> {7}");

    cout << "buscarEdad:\n";
    unordered_map<string, int> agenda = {{"Ana", 20}, {"Luis", 31}};
    comprobar(buscarEdad(agenda, "Luis") == 31, "Luis tiene 31");
    comprobar(buscarEdad(agenda, "Pedro") == -1, "Pedro no está -> -1");
    comprobar(agenda.size() == 2, "buscar no añade a nadie a la agenda");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 4.2 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
