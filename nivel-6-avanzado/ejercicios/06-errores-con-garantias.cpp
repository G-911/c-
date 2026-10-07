// Miniproyecto 6.6 — Un vector que no se rompe
// ---------------------------------------------------------------
// Completa las SIETE partes marcadas con TODO. No toques main().
// Vas a construir un vector pequeño (VectorPiezas) que, aunque una
// copia falle a mitad, nunca queda roto ni pierde memoria. Las pruebas
// hacen fallar copias a propósito (fallarProximaCopia) para comprobarlo.
//
// Compilar y probar (en la terminal, dentro de esta carpeta).
// C++23 hace falta por <expected>:
//   g++ -std=c++23 -Wall -pthread 06-errores-con-garantias.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <stdexcept>     // runtime_error
#include <string>
#include <utility>       // move, move_if_noexcept, swap
#include <type_traits>   // is_nothrow_move_constructible_v (lo usan las pruebas)
#include <expected>      // C++23
#include <format>        // C++20 (lección 6.5)
using namespace std;

// ---------- La Pieza: cuenta todo lo que le pasa ----------
int piezasVivas = 0;              // si al final no vale 0, hay fuga
int copias = 0;                   // copias hechas desde el último reinicio
bool fallarProximaCopia = false;  // si es true, la PRÓXIMA copia lanza

void contarCopia() {
    if (fallarProximaCopia) {
        fallarProximaCopia = false;
        throw runtime_error("copia fallida (simulada)");
    }
    copias++;
}

struct Pieza {
    int valor;
    Pieza(int v = 0) : valor(v) { piezasVivas++; }
    ~Pieza() { piezasVivas--; }

    // Copiar PUEDE fallar (aquí, cuando las pruebas lo piden).
    Pieza(const Pieza& o) : valor(o.valor) { contarCopia(); piezasVivas++; }
    Pieza& operator=(const Pieza& o) { contarCopia(); valor = o.valor; return *this; }

    // 1) Mover solo copia un int: no puede fallar. Prométeselo al compilador.
    //    TODO: añade una palabra a cada una de estas dos líneas (antes del ':' y del '{').
    Pieza(Pieza&& o) : valor(o.valor) { o.valor = -1; piezasVivas++; }
    Pieza& operator=(Pieza&& o) { valor = o.valor; o.valor = -1; return *this; }
};

// ---------- VectorPiezas: un vector pequeño hecho a mano ----------
// std::vector construye los elementos en memoria sin inicializar; aquí,
// para no complicarlo, creamos piezas vacías con new Pieza[] y luego les
// ASIGNAMOS. La idea de las garantías es exactamente la misma.
class VectorPiezas {
    Pieza* datos = nullptr;
    int n = 0;     // cuántas hay
    int cap = 0;   // cuántas caben

    // 2) Duplica la capacidad (o la pone en 1 si era 0) con GARANTÍA FUERTE.
    //    Pasos: pide el bloque nuevo con new Pieza[nuevaCap]; dentro de un
    //    try, pasa cada pieza con nuevo[i] = move_if_noexcept(datos[i]);
    //    en catch (...): delete[] nuevo; y throw; (relanza el mismo error).
    //    Solo al final, cuando ya nada puede fallar: delete[] datos y
    //    actualizar datos y cap.
    void crecer() {
        // TODO
    }

public:
    VectorPiezas() {}
    ~VectorPiezas() { delete[] datos; }

    // Constructor de copia (hecho). Si una copia falla a mitad, el
    // destructor NO se llamará (el objeto nunca terminó de nacer):
    // por eso liberamos aquí lo que ya habíamos pedido.
    VectorPiezas(const VectorPiezas& o) : datos(new Pieza[o.cap]), n(o.n), cap(o.cap) {
        try {
            for (int i = 0; i < n; i++) datos[i] = o.datos[i];
        } catch (...) {
            delete[] datos;
            throw;
        }
    }

    // Constructor de movimiento (hecho): roba y deja al otro vacío.
    VectorPiezas(VectorPiezas&& o) noexcept : datos(o.datos), n(o.n), cap(o.cap) {
        o.datos = nullptr;
        o.n = o.cap = 0;
    }

    int tamano() const { return n; }
    int capacidad() const { return cap; }
    const Pieza& operator[](int i) const { return datos[i]; }
    int valorEn(int i) const { return (i >= 0 && i < n) ? datos[i].valor : -999; }

    // 3) Añade una copia de x al final con GARANTÍA FUERTE: si algo lanza,
    //    el vector queda EXACTAMENTE como estaba (tamaño, capacidad, valores).
    //    Pista: el ORDEN lo es todo. Primero lo que puede fallar (hacer una
    //    copia local de x), luego crecer si hace falta, y al final lo que
    //    no falla (mover la copia a datos[n] y sumar 1 a n).
    //    Cuidado: x puede ser uno de TUS elementos (w.push_back(w[0])).
    void push_back(const Pieza& x) {
        (void)x;   // calla un aviso del compilador: bórrala al empezar
        // TODO
    }

    // 4) Intercambia el contenido con otro vector. No puede fallar.
    //    Pista: swap de cada uno de los tres atributos.
    void intercambiar(VectorPiezas& otro) noexcept {
        (void)otro;   // calla un aviso del compilador: bórrala al empezar
        // TODO
    }

    // 5) Asignación con copy-and-swap: el parámetro llega POR VALOR
    //    (ya copiado; si la copia falla, *this ni se entera).
    //    Son dos líneas. No hace falta comprobar a = a.
    VectorPiezas& operator=(VectorPiezas otro) noexcept {
        (void)otro;   // calla un aviso del compilador: bórrala al empezar
        // TODO
        return *this;
    }
};

// ---------- expected (C++23) ----------

// 6) a / b. Si b es 0, devuelve el error "división entre cero".
//    Pista: return unexpected("..."); para el error; return a / b; si va bien.
expected<int, string> dividir(int a, int b) {
    (void)a; (void)b;   // calla un aviso del compilador: bórrala al empezar
    // TODO (borra el return 0 cuando lo escribas)
    return 0;
}

// 7) "a / b = r" si se puede; si no, "error: " + el mensaje del error.
//    Usa dividir. Si r tiene valor, *r es el resultado; si no, r.error()
//    es el mensaje. format("{} / {} = {}", ...) arma el texto (lección 6.5).
string describir(int a, int b) {
    (void)a; (void)b;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return "";
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

bool valoresSon(const VectorPiezas& v, initializer_list<int> esperados) {
    if (v.tamano() != (int)esperados.size()) return false;
    int i = 0;
    for (int e : esperados)
        if (v.valorEn(i++) != e) return false;
    return true;
}

int main() {
    cout << "Pieza:\n";
    comprobar(is_nothrow_move_constructible_v<Pieza> && is_nothrow_move_assignable_v<Pieza>,
              "mover una Pieza es noexcept (constructor y asignación)");

    cout << "push_back y crecer:\n";
    {
        VectorPiezas v;
        copias = 0;
        for (int i = 1; i <= 5; i++) {
            Pieza p(i);
            v.push_back(p);
        }
        comprobar(valoresSon(v, {1, 2, 3, 4, 5}) && v.capacidad() == 8,
                  "push_back de 1..5  ->  [1,2,3,4,5] con capacidad 8");
        comprobar(copias == 5,
                  "5 push_back = 5 copias: al crecer MUEVE, no copia (¿noexcept?)");
    }
    comprobar(piezasVivas == 0, "el vector libera sus piezas al destruirse");

    cout << "garantía fuerte de push_back:\n";
    {
        VectorPiezas v;
        for (int i = 1; i <= 4; i++) v.push_back(Pieza(i));   // lleno: 4 de 4
        bool lanzo = false;
        fallarProximaCopia = true;
        try {
            v.push_back(Pieza(9));
        } catch (const runtime_error&) {
            lanzo = true;
        }
        fallarProximaCopia = false;
        comprobar(lanzo, "si la copia falla, push_back deja pasar el error");
        comprobar(valoresSon(v, {1, 2, 3, 4}) && v.capacidad() == 4,
                  "...y el vector queda EXACTAMENTE igual: [1,2,3,4], capacidad 4");

    }
    {
        VectorPiezas w;
        for (int i = 1; i <= 4; i++) w.push_back(Pieza(i));   // lleno: 4 de 4
        if (w.tamano() == 4) {
            w.push_back(w[0]);   // copiar uno suyo justo cuando tiene que crecer
            comprobar(valoresSon(w, {1, 2, 3, 4, 1}),
                      "w.push_back(w[0]) con el vector lleno  ->  [1,2,3,4,1]");
        } else {
            comprobar(false, "w.push_back(w[0]) con el vector lleno  ->  [1,2,3,4,1]");
        }
    }

    cout << "intercambiar y copy-and-swap:\n";
    {
        VectorPiezas a, b;
        a.push_back(Pieza(1));
        b.push_back(Pieza(7));
        b.push_back(Pieza(8));
        a.intercambiar(b);
        comprobar(valoresSon(a, {7, 8}) && valoresSon(b, {1}), "intercambiar([1], [7,8])  ->  [7,8] y [1]");

        a = b;
        b.push_back(Pieza(5));
        comprobar(valoresSon(a, {1}) && valoresSon(b, {1, 5}), "a = b copia: luego cambiar b no toca a");

        a = a;
        comprobar(valoresSon(a, {1}), "a = a no rompe nada");

        b.push_back(Pieza(6));   // b = [1,5,6]
        bool lanzo = false;
        fallarProximaCopia = true;
        try {
            a = b;
        } catch (const runtime_error&) {
            lanzo = true;
        }
        fallarProximaCopia = false;
        comprobar(lanzo && valoresSon(a, {1}),
                  "si copiar b falla en a = b, a sigue siendo [1] (garantía fuerte)");
    }
    comprobar(piezasVivas == 0, "no quedan piezas sin liberar (tampoco tras los errores)");

    cout << "expected:\n";
    comprobar(dividir(10, 3).value_or(-1) == 3, "dividir(10, 3) tiene valor 3");
    {
        auto r = dividir(1, 0);
        comprobar(!r.has_value() && r.error() == "división entre cero",
                  "dividir(1, 0) no tiene valor; su error es \"división entre cero\"");
    }
    comprobar(describir(10, 2) == "10 / 2 = 5", "describir(10, 2) = \"10 / 2 = 5\"");
    comprobar(describir(1, 0) == "error: división entre cero",
              "describir(1, 0) = \"error: división entre cero\"");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.6 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
