// Miniproyecto 4.2 — Contar, buscar y quitar repetidos
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO. No toques main().
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 02-stl-contenedores.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
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
    // Pista: recorre con for de rango y usa conteo[p]++ (el [] crea la clave con 0).
    map<string, int> conteo;
    (void)palabras;   // TODO: borra esta línea y llena el mapa
    return conteo;
}

// 2) La palabra que más se repite y cuántas veces, como un pair.
//    Empate: gana la primera en orden alfabético (la que aparece antes al recorrer).
//    Mapa vacío: devuelve {"", 0}.
pair<string, int> masFrecuente(const map<string, int>& conteo) {
    // Pista: for (const auto& [palabra, veces] : conteo) y quédate con el mayor.
    // Usa > (no >=) para que en un empate se quede la primera.
    (void)conteo;     // TODO: borra esta línea
    return {"", 0};   // TODO
}

// 3) Los valores sin repetir y ordenados de menor a mayor.
//    {5,1,5,3,1}  ->  {1,3,5}
vector<int> unicosOrdenados(const vector<int>& v) {
    // Pista: mete todo en un set<int> (ordena y quita repetidos solo)
    // y luego pásalo a un vector.
    (void)v;     // TODO: borra esta línea
    return {};   // TODO
}

// 4) La edad de alguien en la agenda, o -1 si no está.
//    OJO: agenda es const, así que agenda[nombre] NO compila. Usa find.
int buscarEdad(const unordered_map<string, int>& agenda, const string& nombre) {
    // Pista: auto it = agenda.find(nombre); compáralo con agenda.end().
    (void)agenda; (void)nombre;   // TODO: borra esta línea
    return 0;                     // TODO
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
