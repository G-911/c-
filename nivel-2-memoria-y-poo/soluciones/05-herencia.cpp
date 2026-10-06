// SOLUCIÓN del miniproyecto 2.5 — La nómina de una tienda, con herencia
// ---------------------------------------------------------------
// La clase base Empleado ya está hecha: guarda el nombre y el sueldo base.
// Tú completas las dos clases hijas, Gerente y Vendedor, en los SEIS
// puntos que en el ejercicio estaban marcados con TODO. Ábrela solo después de intentarlo.
//
//   - Un Gerente cobra su sueldo base + un bono fijo.
//   - Un Vendedor cobra su sueldo base + el 10 % de lo que vendió.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 05-herencia.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

int empleadosCreados = 0;   // lo usan las pruebas: cuenta cuántas veces nace un Empleado

// ----------------- Clase base (YA HECHA, no tocar) -----------------
class Empleado {
protected:                 // las hijas SÍ pueden tocarlos; desde fuera, no
    string nombre;
    double sueldoBase;

public:
    Empleado(string n, double s) : nombre(n), sueldoBase(s) {
        empleadosCreados++;
    }
    string getNombre() { return nombre; }
    double getSueldoBase() { return sueldoBase; }
};

// ----------------- Clase hija 1: Gerente -----------------
class Gerente : public Empleado {
private:
    double bono;

public:
    // 1) Constructor. Ahora pasa datos falsos a la base y deja el bono en 0.
    //    Arréglalo: la base recibe n y s; bono recibe b.
    //    Pista: todo va en la lista de inicialización, la base PRIMERO.
    Gerente(string n, double s, double b) : Empleado(n, s), bono(b) {}

    // 2) Sueldo total = sueldo base + bono.
    //    Pista: sueldoBase es protected, así que aquí lo puedes leer directamente.
    double sueldoTotal() {
        return sueldoBase + bono;   // sueldoBase es protected: la hija lo ve
    }

    // 3) Una línea para la nómina: "Ana (gerente)".
    //    Pista: el nombre es de la base. getNombre() o nombre, los dos valen aquí.
    string describir() {
        return nombre + " (gerente)";
    }
};

// ----------------- Clase hija 2: Vendedor -----------------
class Vendedor : public Empleado {
private:
    double ventas;   // total vendido en el mes

public:
    // 4) Constructor: la base recibe n y s; las ventas empiezan en 0.
    Vendedor(string n, double s) : Empleado(n, s), ventas(0) {}

    // 5) Suma una venta al total. Si el monto es 0 o negativo, no hace nada.
    void registrarVenta(double monto) {
        if (monto <= 0) return;
        ventas += monto;
    }

    double getVentas() { return ventas; }

    // 6) Sueldo total = sueldo base + el 10 % de las ventas.
    double sueldoTotal() {
        return sueldoBase + ventas * 0.10;
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Los double se comparan "casi iguales", nunca con == exacto.
bool cerca(double a, double b) {
    double d = a - b;
    return d < 0.001 && d > -0.001;
}

int main() {
    cout << "Gerente:\n";
    Gerente ana("Ana", 1000, 300);
    comprobar(ana.getNombre() == "Ana", "la base guarda el nombre (getNombre heredado)");
    comprobar(cerca(ana.getSueldoBase(), 1000), "la base guarda el sueldo base: 1000");
    comprobar(cerca(ana.sueldoTotal(), 1300), "sueldoTotal = 1000 + 300 = 1300");
    comprobar(ana.describir() == "Ana (gerente)", "describir() da \"Ana (gerente)\"");
    Gerente sinBono("Leo", 800, 0);
    comprobar(cerca(sinBono.sueldoTotal(), 800), "gerente con bono 0 cobra solo el base");

    cout << "Vendedor:\n";
    Vendedor beto("Beto", 600);
    comprobar(beto.getNombre() == "Beto" && cerca(beto.getSueldoBase(), 600),
              "la base guarda nombre y sueldo de Beto");
    comprobar(cerca(beto.getVentas(), 0), "un vendedor nuevo empieza con 0 en ventas");
    comprobar(cerca(beto.sueldoTotal(), 600), "sin ventas cobra solo el base: 600");
    beto.registrarVenta(1000);
    beto.registrarVenta(500);
    comprobar(cerca(beto.getVentas(), 1500), "dos ventas suman 1500");
    comprobar(cerca(beto.sueldoTotal(), 750), "sueldoTotal = 600 + 10% de 1500 = 750");
    beto.registrarVenta(-200);
    beto.registrarVenta(0);
    comprobar(cerca(beto.getVentas(), 1500), "una venta de 0 o negativa no cuenta");

    cout << "Constructores:\n";
    comprobar(empleadosCreados == 3, "cada hijo construyó UNA vez su parte Empleado (3 en total)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 2.5 terminado.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
