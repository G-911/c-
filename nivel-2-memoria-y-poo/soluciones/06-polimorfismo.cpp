// SOLUCIÓN del miniproyecto 2.6 — Un plano con figuras mezcladas
// ---------------------------------------------------------------
// Figura es una clase ABSTRACTA: tiene area() = 0, así que no se pueden
// crear figuras "a secas", solo círculos, rectángulos y triángulos.
// Todas se guardan juntas en un vector<Figura*> y se recorren sin
// preguntar de qué tipo es cada una: eso es el polimorfismo.
//
// Aquí están resueltos los OCHO puntos del ejercicio.
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 06-polimorfismo.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Lo usan las pruebas: cuántas figuras hay vivas ahora mismo.
// Cada clase HIJA suma 1 al nacer y resta 1 al morir.
int figurasVivas = 0;

// ----------------- Clase base abstracta -----------------
class Figura {
protected:
    string nombre;

public:
    Figura(string n) : nombre(n) {}

    // 1) Destructor VIRTUAL: imprescindible en una clase con métodos virtuales.
    virtual ~Figura() {}   // virtual: delete por Figura* ejecuta también el de la hija

    string getNombre() { return nombre; }

    // Virtual pura: cada hija DEBE escribir la suya. Por esto Figura es abstracta.
    virtual double area() = 0;
};

const double PI = 3.14159;

// ----------------- Las hijas -----------------
class Circulo : public Figura {
private:
    double radio;
public:
    Circulo(double r) : Figura("circulo"), radio(r) { figurasVivas++; }
    ~Circulo() { figurasVivas--; }

    // 2) Área del círculo: PI · radio · radio
    double area() override {
        return PI * radio * radio;
    }
};

class Rectangulo : public Figura {
private:
    double ancho, alto;
public:
    Rectangulo(double an, double al) : Figura("rectangulo"), ancho(an), alto(al) { figurasVivas++; }
    ~Rectangulo() { figurasVivas--; }

    // 3) Área del rectángulo: ancho · alto
    double area() override {
        return ancho * alto;
    }
};

class Triangulo : public Figura {
private:
    double base, altura;
public:
    // 4) El constructor pasa el nombre correcto a la clase base.
    Triangulo(double b, double h) : Figura("triangulo"), base(b), altura(h) { figurasVivas++; }
    ~Triangulo() { figurasVivas--; }

    // 5) Área del triángulo: base · altura / 2
    double area() override {
        return base * altura / 2;
    }
};

// ----------------- Funciones que trabajan con CUALQUIER figura -----------------

// 6) Suma el área de todas las figuras. Con el vector vacío, 0.
//    Pista: for (Figura* f : figuras)  y  f->area().
//    No preguntes el tipo: el virtual ya llama al area() correcto.
double areaTotal(const vector<Figura*>& figuras) {
    double total = 0;
    for (Figura* f : figuras) {
        total += f->area();   // virtual: cada figura usa SU area()
    }
    return total;
}

// 7) Devuelve el apuntador a la figura de MAYOR área.
//    Con el vector vacío, devuelve nullptr.
Figura* mayor(const vector<Figura*>& figuras) {
    Figura* mejor = nullptr;
    for (Figura* f : figuras) {
        if (mejor == nullptr || f->area() > mejor->area()) {
            mejor = f;
        }
    }
    return mejor;
}

// 8) Libera TODAS las figuras con delete y deja el vector vacío (clear()).
//    Las figuras se crearon con new en main(); si no las liberas, hay fuga.
void liberarTodas(vector<Figura*>& figuras) {
    for (Figura* f : figuras) {
        delete f;        // destructor virtual: corre ~Circulo, ~Rectangulo...
    }
    figuras.clear();     // los apuntadores ya no valen: fuera del vector
}

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
    cout << "Cada figura, por un Figura*:\n";
    Figura* c = new Circulo(1);
    Figura* r = new Rectangulo(3, 4);
    Figura* t = new Triangulo(6, 2);
    comprobar(cerca(c->area(), 3.14159), "circulo de radio 1: area 3.14159");
    comprobar(cerca(r->area(), 12), "rectangulo 3 x 4: area 12");
    comprobar(cerca(t->area(), 6), "triangulo base 6, altura 2: area 6");
    comprobar(t->getNombre() == "triangulo", "el triangulo se llama \"triangulo\"");

    cout << "Todas juntas en un vector<Figura*>:\n";
    vector<Figura*> vacio;
    comprobar(cerca(areaTotal(vacio), 0), "areaTotal de un vector vacio es 0");
    comprobar(mayor(vacio) == nullptr, "mayor de un vector vacio es nullptr");

    vector<Figura*> plano = {c, r, t};
    comprobar(cerca(areaTotal(plano), 21.14159), "areaTotal = 3.14159 + 12 + 6");
    comprobar(mayor(plano) == r, "la mayor es el rectangulo");
    plano.push_back(new Circulo(3));   // area 28.27
    comprobar(mayor(plano) != nullptr && mayor(plano)->getNombre() == "circulo",
              "tras meter un circulo de radio 3, el mayor es un circulo");

    cout << "Liberar la memoria:\n";
    comprobar(figurasVivas == 4, "antes de liberar hay 4 figuras vivas");
    liberarTodas(plano);
    comprobar(plano.empty(), "liberarTodas deja el vector vacio");
    comprobar(figurasVivas == 0, "no quedan figuras sin liberar (destructores de las hijas)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 2.6 terminado.\n"
                         : "\nAún hay fallos. Revisa los puntos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
