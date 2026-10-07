// Miniproyecto 5.6 — Tu propia tabla hash con rehash
// ---------------------------------------------------------------
// Completa las SEIS funciones marcadas con TODO. No toques main(),
// hashCadena, indiceDe ni bienUbicada.
// La tabla es un vector de cubetas; cada cubeta es una list de pares
// (clave, valor). Las colisiones se resuelven por encadenamiento.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 06-tablas-hash.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <list>
#include <string>
#include <utility>     // pair
#include <vector>
using namespace std;

// Función hash de la lección: convierte una palabra en un número grande.
// size_t no tiene signo: nunca da un índice negativo.
size_t hashCadena(const string& clave) {
    size_t h = 0;
    for (char c : clave) h = h * 31 + (unsigned char)c;
    return h;
}

class TablaHash {
private:
    vector<list<pair<string, int>>> cubetas;   // cada cubeta: una lista de pares clave-valor
    size_t cantidad;                           // cuántos pares hay en total

    // Ya hecho: en qué cubeta va una clave con el número de cubetas ACTUAL.
    size_t indiceDe(const string& clave) const {
        return hashCadena(clave) % cubetas.size();
    }

public:
    // Ya hecho: nace con m cubetas vacías (al menos 1).
    TablaHash(size_t m = 8) : cubetas(m == 0 ? 1 : m), cantidad(0) {}

    size_t tamano() const { return cantidad; }
    size_t numCubetas() const { return cubetas.size(); }
    size_t largoCubeta(size_t i) const { return cubetas[i].size(); }

    // Ya hecho: true si cada par está en la cubeta que le toca.
    bool bienUbicada() const {
        for (size_t i = 0; i < cubetas.size(); i++)
            for (const auto& par : cubetas[i])
                if (indiceDe(par.first) != i) return false;
        return true;
    }

    // 1) Factor de carga = pares / cubetas, como double.
    //    Pista: (double)cantidad / cubetas.size()  — sin el (double) la división es entera.
    double factorDeCarga() const {
        return 0.0; // TODO
    }

    // 2) Si la clave existe, actualiza su valor. Si no, la añade al final de su cubeta,
    //    y si el factor de carga pasa de 1.0, duplica las cubetas.
    //    Pista: list<pair<string,int>>& cubeta = cubetas[indiceDe(clave)];
    //    recorre con for (auto& par : cubeta); si par.first == clave, cambia par.second
    //    y return. Si no estaba: push_back({clave, valor}), cantidad++ y comprueba el factor.
    void insertar(const string& clave, int valor) {
        (void)clave; (void)valor;   // evita avisos; bórrala al empezar
        // TODO
    }

    // 3) Si la encuentra, copia su valor en «valor» y devuelve true.
    //    Pista: solo hay que mirar UNA cubeta, la de indiceDe(clave).
    bool buscar(const string& clave, int& valor) const {
        (void)clave; (void)valor;   // evita avisos; bórrala al empezar
        return false; // TODO
    }

    // 4) Quita la clave. Devuelve true si estaba.
    //    Pista: recorre la cubeta con un iterador (auto it = cubeta.begin(); ...)
    //    y usa cubeta.erase(it). No olvides cantidad--.
    bool eliminar(const string& clave) {
        (void)clave;   // evita un aviso; bórrala al empezar
        return false; // TODO
    }

    // 5) Rehash: mudarse a «nuevas» cubetas, recalculando el índice de cada par.
    //    Pista: vector<list<pair<string,int>>> viejas(nuevas); viejas.swap(cubetas);
    //    Ahora «cubetas» tiene el tamaño nuevo y está vacía. Recorre «viejas» y mete
    //    cada par en cubetas[indiceDe(par.first)]. ¡NO copies las cubetas tal cual!
    //    (cantidad no cambia: son los mismos pares en otro sitio)
    void rehash(size_t nuevas) {
        (void)nuevas;   // evita un aviso; bórrala al empezar
        // TODO
    }
};

// 6) Cuenta cuántas veces aparece cada palabra del texto (separadas por espacios).
//    Pista: junta letras en un string «palabra» hasta encontrar ' ' o el final.
//    Para cada palabra: int veces = 0; t.buscar(palabra, veces); t.insertar(palabra, veces + 1);
void contarPalabras(const string& texto, TablaHash& t) {
    (void)texto; (void)t;   // evita avisos; bórrala al empezar
    // TODO
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "Insertar y buscar:\n";
    {
        TablaHash t(8);
        t.insertar("ana", 20);
        t.insertar("luis", 31);
        int v = -1;
        comprobar(t.buscar("ana", v) && v == 20, "buscar(\"ana\") encuentra 20");
        comprobar(t.buscar("luis", v) && v == 31, "buscar(\"luis\") encuentra 31");
        comprobar(!t.buscar("eva", v), "buscar una clave que no está devuelve false");
        t.insertar("ana", 21);
        comprobar(t.buscar("ana", v) && v == 21 && t.tamano() == 2,
                  "insertar una clave repetida actualiza, no duplica");
    }

    cout << "Colisiones:\n";
    {
        TablaHash t(1);   // una sola cubeta: todas las claves chocan
        t.insertar("ana", 1);
        t.insertar("eva", 2);
        int v = -1;
        comprobar(t.tamano() == 2, "empezando con una sola cubeta se guardan dos claves");
        comprobar(t.buscar("ana", v) && v == 1 && t.buscar("eva", v) && v == 2,
                  "con colisiones, cada clave conserva su valor");
    }

    cout << "Eliminar:\n";
    {
        TablaHash t(4);
        t.insertar("sol", 1);
        t.insertar("mar", 2);
        int v = -1;
        comprobar(t.eliminar("sol") && !t.buscar("sol", v) && t.tamano() == 1,
                  "eliminar(\"sol\") la quita y baja el tamaño");
        comprobar(!t.eliminar("sol"), "eliminar algo que ya no está devuelve false");
    }

    cout << "Factor de carga y rehash:\n";
    {
        TablaHash t(4);
        t.insertar("ana", 1);
        t.insertar("luis", 2);
        t.insertar("mar", 3);
        comprobar(t.factorDeCarga() == 0.75, "3 pares en 4 cubetas: factor 0.75");
        t.insertar("juan", 4);
        comprobar(t.numCubetas() == 4, "con factor 1.0 todavía no hay rehash");
        t.insertar("pan", 5);
        comprobar(t.numCubetas() == 8, "al pasar de 1.0, las cubetas se duplican (4 -> 8)");
        int v = -1;
        bool todas = t.buscar("ana", v) && v == 1 && t.buscar("luis", v) && v == 2 &&
                     t.buscar("mar", v) && v == 3 && t.buscar("juan", v) && v == 4 &&
                     t.buscar("pan", v) && v == 5;
        comprobar(todas && t.bienUbicada(),
                  "tras el rehash todo se encuentra y cada par está en su cubeta nueva");
        TablaHash g(2);
        for (int i = 0; i < 1000; i++) g.insertar("clave" + to_string(i), i);
        comprobar(g.tamano() == 1000 && g.factorDeCarga() <= 1.0 && g.bienUbicada(),
                  "1000 inserciones: factor de carga nunca pasa de 1.0");
    }

    cout << "Contar palabras:\n";
    {
        TablaHash t;
        contarPalabras("el gato y el perro y el raton", t);
        int el = 0, y = 0, gato = 0;
        t.buscar("el", el);
        t.buscar("y", y);
        t.buscar("gato", gato);
        comprobar(el == 3 && y == 2 && gato == 1 && t.tamano() == 5,
                  "«el» 3 veces, «y» 2, «gato» 1; 5 palabras distintas");
    }

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 5.6 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
