// SOLUCIÓN — Miniproyecto 2.4 — Clases y objetos: CuentaBancaria (ábrela solo después de intentarlo)
// ---------------------------------------------------------------
// Completa los métodos marcados con TODO. No toques main().
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 04-clases.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
//
// Las líneas  (void)cantidad;  solo existen para que el archivo
// compile sin avisos mientras está vacío. Bórralas al completar
// cada método.
// ---------------------------------------------------------------
#include <iostream>
using namespace std;

// Contador didáctico: cuántas cuentas existen ahora mismo.
// El constructor suma 1 y el destructor debe restar 1.
// Si al final del programa no vuelve a 0, alguna cuenta no se destruyó.
int cuentasVivas = 0;

class CuentaBancaria {
private:
    double saldo;       // nadie de fuera puede tocarlo directamente
    int movimientos;    // cuántos depósitos y retiros SE HICIERON de verdad

public:
    // 1) Constructor. Usa la LISTA DE INICIALIZACIÓN para que el saldo
    //    empiece en saldoInicial y los movimientos en 0.
    //    Pista: ahora mismo pone saldo(0). Cámbialo.
    CuentaBancaria(double saldoInicial) : saldo(saldoInicial), movimientos(0) {
        cuentasVivas++;       // (ya hecho) una cuenta más existe
    }

    // 2) Destructor. Se llama solo cuando la cuenta muere
    //    (al acabar su bloque { } o al hacer delete).
    //    Pista: una cuenta menos existe.
    ~CuentaBancaria() {
        cuentasVivas--;
    }

    // 3) Suma cantidad al saldo y cuenta un movimiento.
    //    Si cantidad es 0 o negativa, NO hace nada (ni cuenta movimiento).
    void depositar(double cantidad) {
        if (cantidad <= 0) return;   // cantidad inválida: no se hace nada
        saldo += cantidad;
        movimientos++;
    }

    // 4) Resta cantidad del saldo SOLO si alcanza. Devuelve true si retiró.
    //    Si cantidad es 0 o negativa, o mayor que el saldo: no toca nada
    //    y devuelve false. Solo los retiros hechos cuentan como movimiento.
    bool retirar(double cantidad) {
        if (cantidad <= 0 || cantidad > saldo) return false;   // no alcanza o inválida
        saldo -= cantidad;
        movimientos++;
        return true;
    }

    // 5) Devuelve el saldo actual.
    double getSaldo() {
        return saldo;
    }

    // 6) Devuelve cuántos movimientos se hicieron.
    int getMovimientos() {
        return movimientos;
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "Constructor (cuenta creada con new, usada con ->):\n";
    CuentaBancaria* c = new CuentaBancaria(100);
    comprobar(c->getSaldo() == 100, "new CuentaBancaria(100) empieza con saldo 100");
    comprobar(c->getMovimientos() == 0, "una cuenta nueva tiene 0 movimientos");

    cout << "depositar:\n";
    c->depositar(50);
    comprobar(c->getSaldo() == 150 && c->getMovimientos() == 1,
              "depositar(50) -> saldo 150 y 1 movimiento");
    c->depositar(-20);
    comprobar(c->getSaldo() == 150 && c->getMovimientos() == 1,
              "depositar(-20) se ignora: ni saldo ni movimientos cambian");

    cout << "retirar:\n";
    bool r1 = c->retirar(30);
    comprobar(r1 && c->getSaldo() == 120 && c->getMovimientos() == 2,
              "retirar(30) devuelve true -> saldo 120 y 2 movimientos");
    bool r2 = c->retirar(500);
    comprobar(!r2 && c->getSaldo() == 120 && c->getMovimientos() == 2,
              "retirar(500) sin fondos devuelve false y no toca nada");
    bool r3 = c->retirar(120);
    comprobar(r3 && c->getSaldo() == 0, "retirar TODO el saldo (120) se permite: queda 0");

    cout << "Cada objeto tiene sus propios atributos:\n";
    {
        CuentaBancaria otra(10);   // objeto normal, sin new: se usa con punto
        otra.depositar(5);
        comprobar(otra.getSaldo() == 15 && c->getSaldo() == 0,
                  "depositar en 'otra' no cambia la cuenta 'c'");
        comprobar(cuentasVivas == 2, "ahora mismo existen 2 cuentas");
    }   // <- aquí muere 'otra': se llama su destructor solo
    comprobar(cuentasVivas == 1, "al cerrar el bloque { }, 'otra' se destruyó sola");

    cout << "Destructor con delete:\n";
    delete c;
    c = nullptr;
    comprobar(cuentasVivas == 0, "tras delete c no queda ninguna cuenta viva");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 2.4 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
