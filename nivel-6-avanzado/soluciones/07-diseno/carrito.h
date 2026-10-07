// SOLUCIÓN — carrito.h: igual que en el ejercicio (no había nada que tocar)
// ---------------------------------------------------------------
// Fíjate en lo que NO hay: ni vector, ni la lista de productos, ni los
// observadores. Todo eso vive en Carrito::Impl, dentro de carrito.cpp.
// Eso es PIMPL: este .h casi nunca cambia, aunque cambie el interior.
// ---------------------------------------------------------------
#pragma once
#include <functional>
#include <memory>
#include <string>
#include "descuentos.h"

extern int implVivos;   // cuántos Impl existen ahora (para ver que no se fugan)

class Carrito {
public:
    Carrito();
    ~Carrito();                                  // definido en carrito.cpp, donde Impl ya se conoce
    Carrito(Carrito&&) noexcept;                 // se puede mover...
    Carrito& operator=(Carrito&&) noexcept;
    Carrito(const Carrito&) = delete;            // ...pero no copiar
    Carrito& operator=(const Carrito&) = delete;

    void agregar(const std::string& producto, double precio);
    int cantidad() const;
    double subtotal() const;                     // la suma, sin descuento
    double total() const;                        // con la estrategia de descuento aplicada
    void cambiarDescuento(std::unique_ptr<Descuento> nuevo);
    void alCambiar(std::function<void(double)> observador);   // se le avisa con el total nuevo

private:
    struct Impl;                    // declarada, NO definida: aquí es «una caja cerrada»
    std::unique_ptr<Impl> impl;     // lo único que guarda el Carrito: un apuntador
};
