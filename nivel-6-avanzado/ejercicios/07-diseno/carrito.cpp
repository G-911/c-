// carrito.cpp — el interior del Carrito
// ---------------------------------------------------------------
// Aquí completas el TODO 3 (total) y el TODO 4 (avisar a los observadores).
// ---------------------------------------------------------------
#include "carrito.h"
#include <utility>
#include <vector>
using namespace std;

int implVivos = 0;

// La implementación «escondida». Solo este archivo sabe qué hay dentro.
struct Carrito::Impl {
    vector<pair<string, double>> productos;
    unique_ptr<Descuento> descuento = make_unique<SinDescuento>();
    vector<function<void(double)>> observadores;

    Impl() { implVivos++; }
    ~Impl() { implVivos--; }

    // TODO 4 — el OBSERVADOR: llama a cada función de «observadores»
    // pasándole el total nuevo.
    // Pista: for (auto& f : observadores) f(...);
    void avisar(double totalNuevo) {
        (void)totalNuevo;   // calla un aviso del compilador: bórrala al empezar
        // TODO
    }
};

Carrito::Carrito() : impl(make_unique<Impl>()) {}
Carrito::~Carrito() = default;                    // aquí Impl ya es completa: unique_ptr sabe borrarla
Carrito::Carrito(Carrito&&) noexcept = default;
Carrito& Carrito::operator=(Carrito&&) noexcept = default;

void Carrito::agregar(const string& producto, double precio) {
    impl->productos.push_back({producto, precio});
    impl->avisar(total());
}

int Carrito::cantidad() const { return static_cast<int>(impl->productos.size()); }

double Carrito::subtotal() const {
    double suma = 0;
    for (const auto& p : impl->productos) suma += p.second;
    return suma;
}

// TODO 3 — la ESTRATEGIA en acción: devuelve el subtotal con el descuento
// actual aplicado. El Carrito no sabe QUÉ descuento es: solo lo usa.
// Pista: impl->descuento->aplicar(...)
double Carrito::total() const {
    // TODO (borra el return de abajo cuando lo escribas)
    return subtotal();
}

void Carrito::cambiarDescuento(unique_ptr<Descuento> nuevo) {
    if (!nuevo) nuevo = make_unique<SinDescuento>();   // nunca dejamos el descuento en nullptr
    impl->descuento = std::move(nuevo);
    impl->avisar(total());
}

void Carrito::alCambiar(function<void(double)> observador) {
    impl->observadores.push_back(std::move(observador));
}
