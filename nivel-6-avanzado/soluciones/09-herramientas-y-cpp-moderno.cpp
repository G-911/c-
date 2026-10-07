// SOLUCIÓN del Miniproyecto 6.9 — Tu propio marco de pruebas
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar:
//   g++ -std=c++17 -Wall -pthread 09-herramientas-y-cpp-moderno.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <sstream>     // ostringstream: convertir cualquier valor en texto
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// ================================================================
// PARTE A — El marco de pruebas
// ================================================================

// Lo que el marco recuerda. Ya hecho.
int esperasHechas = 0;          // cuántas comprobaciones se ejecutaron
int esperasFallidas = 0;        // cuántas fallaron
vector<string> mensajes;        // el texto de cada fallo

// Ya hecha: apunta un resultado.
void anotar(bool ok, const string& mensaje) {
    esperasHechas++;
    if (!ok) {
        esperasFallidas++;
        mensajes.push_back(mensaje);
    }
}

// Ya hecha: deja el marco a cero (el corrector la usa entre rondas).
void reiniciar() {
    esperasHechas = 0;
    esperasFallidas = 0;
    mensajes.clear();
}

// Ya hecho: el ejemplo a imitar.
#define ESPERAR_VERDAD(cond) \
    anotar((cond), string(__FILE__) + ":" + to_string(__LINE__) + ": ESPERAR_VERDAD(" #cond ") falló")

// 1) esperarIgual: compara y, si no son iguales, anota un fallo con un mensaje así:
//      archivo:linea: ESPERAR_IGUAL(textoA, textoB) falló: vale X, se esperaba Y
template <typename A, typename B>
void esperarIgual(const A& a, const B& b, const char* textoA, const char* textoB,
                  const char* archivo, int linea) {
    ostringstream msg;
    msg << archivo << ":" << linea << ": ESPERAR_IGUAL(" << textoA << ", " << textoB
        << ") falló: vale " << a << ", se esperaba " << b;
    anotar(a == b, msg.str());
}

// 2) La macro: # convierte el argumento en texto; __FILE__ y __LINE__ dicen dónde está.
#define ESPERAR_IGUAL(a, b) esperarIgual((a), (b), #a, #b, __FILE__, __LINE__)

// 3) ESPERAR_LANZA: la expresión debe lanzar una excepción del tipo indicado.
//    do { ... } while (0) hace que la macro se comporte como UNA instrucción.
#define ESPERAR_LANZA(expr, Tipo)                                                    \
    do {                                                                             \
        bool lanzoBien = false;                                                      \
        try {                                                                        \
            expr;                                                                    \
        } catch (const Tipo&) {                                                      \
            lanzoBien = true;                                                        \
        } catch (...) {                                                              \
        }                                                                            \
        anotar(lanzoBien, string(__FILE__) + ":" + to_string(__LINE__) +            \
                              ": ESPERAR_LANZA(" #expr ", " #Tipo ") falló");        \
    } while (0)

// ================================================================
// PARTE B — La clase que vas a probar (no la toques)
// ================================================================

// El corrector estropea la Pila a propósito para ver si tus pruebas lo notan.
//   mutante 0 = la Pila correcta
//   mutante 1 = pop() sobre una pila vacía no lanza (como en el Nivel 3)
//   mutante 2 = top() devuelve el de ABAJO en vez del de arriba
//   mutante 3 = pop() olvida descontar el tamaño
int mutante = 0;

int nodosVivos = 0;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int d) : dato(d), siguiente(nullptr) { nodosVivos++; }
    ~Nodo() { nodosVivos--; }
};

class Pila {
private:
    Nodo* tope;
    int cuantos;

public:
    Pila() : tope(nullptr), cuantos(0) {}
    ~Pila() {
        while (tope != nullptr) {
            Nodo* sig = tope->siguiente;
            delete tope;
            tope = sig;
        }
    }
    Pila(const Pila&) = delete;              // no se copia (para no repetir la regla de tres)
    Pila& operator=(const Pila&) = delete;

    bool vacia() const { return tope == nullptr; }
    int tamano() const { return cuantos; }

    void push(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = tope;
        tope = nuevo;
        cuantos++;
    }

    int top() const {
        if (vacia()) throw out_of_range("top: la pila vacía no tiene tope");
        if (mutante == 2) {                  // error a propósito: baja hasta el fondo
            Nodo* p = tope;
            while (p->siguiente != nullptr) p = p->siguiente;
            return p->dato;
        }
        return tope->dato;
    }

    void pop() {
        if (vacia()) {
            if (mutante == 1) return;        // error a propósito: se calla
            throw out_of_range("pop: la pila vacía no tiene tope");
        }
        Nodo* viejo = tope;
        tope = tope->siguiente;
        delete viejo;
        if (mutante != 3) cuantos--;         // error a propósito en el mutante 3
    }
};

// 4) Tus pruebas de la Pila: al menos 6 comprobaciones con las macros.
void probarPila() {
    // Una pila nueva está vacía.
    {
        Pila p;
        ESPERAR_VERDAD(p.vacia());
        ESPERAR_IGUAL(p.tamano(), 0);
    }
    // top devuelve el ÚLTIMO que entró (atrapa al mutante 2).
    {
        Pila p;
        p.push(1);
        p.push(2);
        p.push(3);
        ESPERAR_IGUAL(p.top(), 3);
        ESPERAR_IGUAL(p.tamano(), 3);
        p.pop();
        ESPERAR_IGUAL(p.top(), 2);
        ESPERAR_IGUAL(p.tamano(), 2);        // atrapa al mutante 3
    }
    // Vaciar del todo.
    {
        Pila p;
        p.push(7);
        p.pop();
        ESPERAR_VERDAD(p.vacia());
        ESPERAR_IGUAL(p.tamano(), 0);
    }
    // Casos borde: la pila vacía lanza (atrapa al mutante 1).
    {
        Pila p;
        ESPERAR_LANZA(p.pop(), out_of_range);
        ESPERAR_LANZA(p.top(), out_of_range);
    }
}

// ================================================================
// Pruebas automáticas del miniproyecto (no tocar)
// ================================================================
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

bool contiene(const string& texto, const string& trozo) {
    return texto.find(trozo) != string::npos;
}

// Ayudantes para probar ESPERAR_LANZA.
void lanzaRango() { throw out_of_range("x"); }
void lanzaOtro() { throw runtime_error("x"); }
void noLanza() {}

// Ejecuta tus pruebas contra un mutante. Si alguna excepción se escapa
// de tus pruebas, cuenta como fallo detectado (como haría GoogleTest).
void ejecutarContra(int cual) {
    reiniciar();
    mutante = cual;
    try {
        probarPila();
    } catch (...) {
        anotar(false, "una excepción se escapó de probarPila");
    }
    mutante = 0;
}

int main() {
    cout << "Parte A · ESPERAR_IGUAL:\n";
    reiniciar();
    ESPERAR_IGUAL(2 + 2, 4);
    comprobar(esperasHechas == 1 && esperasFallidas == 0, "2 + 2 == 4 se anota como acierto");

    reiniciar();
    int lineaDelFallo = __LINE__ + 1;
    ESPERAR_IGUAL(2 + 2, 5);
    comprobar(esperasHechas == 1 && esperasFallidas == 1, "2 + 2 == 5 se anota como fallo");
    string m = mensajes.empty() ? "" : mensajes[0];
    comprobar(contiene(m, "vale 4") && contiene(m, "se esperaba 5"),
              "el mensaje dice cuánto valía y qué se esperaba");
    comprobar(contiene(m, "2 + 2"), "el mensaje muestra el TEXTO de la expresión (#a)");
    comprobar(contiene(m, ":" + to_string(lineaDelFallo) + ":"),
              "el mensaje dice la línea del fallo (__LINE__)");

    reiniciar();
    ESPERAR_IGUAL(string("hola"), string("hola"));
    comprobar(esperasHechas == 1 && esperasFallidas == 0, "también compara strings");

    cout << "Parte A · ESPERAR_LANZA:\n";
    reiniciar();
    ESPERAR_LANZA(lanzaRango(), out_of_range);
    comprobar(esperasHechas == 1 && esperasFallidas == 0, "lanza out_of_range  ->  acierto");
    reiniciar();
    ESPERAR_LANZA(noLanza(), out_of_range);
    comprobar(esperasHechas == 1 && esperasFallidas == 1, "no lanza nada  ->  fallo");
    reiniciar();
    ESPERAR_LANZA(lanzaOtro(), out_of_range);
    comprobar(esperasHechas == 1 && esperasFallidas == 1,
              "lanza otro tipo  ->  fallo (y la excepción no se escapa)");

    cout << "Parte B · tus pruebas de la Pila:\n";
    ejecutarContra(0);
    comprobar(esperasHechas >= 6, "probarPila hace al menos 6 comprobaciones");
    comprobar(esperasHechas > 0 && esperasFallidas == 0, "con la Pila correcta, todas pasan");
    ejecutarContra(1);
    comprobar(esperasFallidas > 0, "atrapan al mutante 1 (pop sobre vacía no lanza)");
    ejecutarContra(2);
    comprobar(esperasFallidas > 0, "atrapan al mutante 2 (top devuelve el de abajo)");
    ejecutarContra(3);
    comprobar(esperasFallidas > 0, "atrapan al mutante 3 (pop no descuenta el tamaño)");
    comprobar(nodosVivos == 0, "no quedan nodos sin liberar");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.9 terminado. ¡Y el curso!\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
