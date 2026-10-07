// SOLUCIÓN — descuentos.h: las ESTRATEGIAS de descuento y su FÁBRICA
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
// ---------------------------------------------------------------
#pragma once
#include <memory>
#include <string>

// La interfaz de la estrategia: una sola cosa que hacer.
class Descuento {
public:
    virtual ~Descuento() = default;
    virtual double aplicar(double subtotal) const = 0;
};

// Estrategia 1 (ya hecha): no descuenta nada.
class SinDescuento : public Descuento {
public:
    double aplicar(double subtotal) const override { return subtotal; }
};

// Estrategia 2 — TODO 1: quita el p por ciento del subtotal.
//   Porcentaje(10).aplicar(200)  ->  180
//   Porcentaje(100).aplicar(50)  ->  0
// Pista: subtotal * (1 - porcentaje / 100).
class Porcentaje : public Descuento {
public:
    explicit Porcentaje(double p) : porcentaje(p) {}
    double aplicar(double subtotal) const override {
        return subtotal * (1 - porcentaje / 100);
    }
private:
    double porcentaje;   // entre 0 y 100
};

// TODO 2 — la FÁBRICA: crea la estrategia a partir de un texto.
//   "ninguno"     ->  SinDescuento
//   "porcentaje"  ->  Porcentaje(valor)
//   cualquier otro texto  ->  nullptr (no se sabe crear)
// Pista: if (tipo == "...") return std::make_unique<...>(...);
// (Lleva «inline» porque su cuerpo está en un .h: así no choca al
//  incluirse desde varios .cpp. Lo viste en la lección 4.6.)
inline std::unique_ptr<Descuento> crearDescuento(const std::string& tipo, double valor) {
    if (tipo == "ninguno") return std::make_unique<SinDescuento>();
    if (tipo == "porcentaje") return std::make_unique<Porcentaje>(valor);
    return nullptr;   // quien llama decide qué hacer con un tipo desconocido
}
