// SOLUCIÓN — Miniproyecto 2.7 — Una Fraccion que se suma, se compara y se imprime
// ---------------------------------------------------------------
// La clase Fraccion ya sabe nacer simplificada: Fraccion(2, 4) guarda 1/2,
// y el signo siempre queda arriba: Fraccion(1, -3) guarda -1/3.
// Los seis operadores ya resueltos. main() es igual que en el ejercicio.
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 07-sobrecarga-de-operadores.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <numeric>   // gcd: máximo común divisor (C++17)
#include <sstream>   // ostringstream: un "cout" que escribe en un string
using namespace std;

class Fraccion {
private:
    int num;   // numerador
    int den;   // denominador (siempre > 0 después del constructor)

public:
    // YA HECHO: crea la fracción y la deja simplificada.
    // Fraccion(3) es 3/1. Fraccion() es 0/1. No pases den = 0.
    Fraccion(int n = 0, int d = 1) : num(n), den(d) {
        if (den < 0) { num = -num; den = -den; }   // el signo, arriba
        int g = gcd(num, den);                      // gcd(0, d) vale d
        if (g != 0) { num /= g; den /= g; }
    }

    int getNum() const { return num; }
    int getDen() const { return den; }

    // 1) ¿Son iguales? Como siempre están simplificadas,
    //    basta comparar num con num y den con den.
    bool operator==(const Fraccion& otra) const {
        return num == otra.num && den == otra.den;
    }

    // 2) ¿Son distintas? Pista: reutiliza el == en una sola línea.
    bool operator!=(const Fraccion& otra) const {
        return !(*this == otra);   // *this es "yo mismo"; reutiliza el ==
    }

    // 3) Suma: a/b + c/d = (a·d + c·b) / (b·d).
    //    Devuelve una Fraccion NUEVA; no cambies *this ni otra.
    //    Pista: return Fraccion(..., ...); el constructor simplifica solo.
    Fraccion operator+(const Fraccion& otra) const {
        return Fraccion(num * otra.den + otra.num * den, den * otra.den);
    }

    // 4) Multiplicación: a/b · c/d = (a·c) / (b·d).
    Fraccion operator*(const Fraccion& otra) const {
        return Fraccion(num * otra.num, den * otra.den);
    }

    // 5) ¿Es menor? a/b < c/d  equivale a  a·d < c·b
    //    (vale porque los dos denominadores son positivos).
    bool operator<(const Fraccion& otra) const {
        return num * otra.den < otra.num * den;
    }

    // 6) Imprimir: 3/4 se escribe "3/4". Si den es 1, solo el número: "5".
    //    Es friend porque a la izquierda del << está el ostream, no la Fraccion.
    //    Pista: escribe en os (no en cout) y termina con return os;
    friend ostream& operator<<(ostream& os, const Fraccion& f) {
        os << f.num;                         // friend: puede leer num y den
        if (f.den != 1) os << "/" << f.den;
        return os;                           // devolver os permite encadenar
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Ayuda de las pruebas: ¿f vale exactamente n/d?
bool vale(const Fraccion& f, int n, int d) {
    return f.getNum() == n && f.getDen() == d;
}

// Ayuda de las pruebas: lo que imprime f, como string.
string comoTexto(const Fraccion& f) {
    ostringstream salida;
    salida << f;
    return salida.str();
}

int main() {
    Fraccion medio(1, 2), tercio(1, 3), dosCuartos(2, 4);

    cout << "== y !=:\n";
    comprobar(medio == dosCuartos, "1/2 == 2/4");
    comprobar(!(medio == tercio), "1/2 no es == 1/3");
    comprobar(medio != tercio, "1/2 != 1/3");
    comprobar(!(medio != dosCuartos), "1/2 no es != 2/4");

    cout << "+ y *:\n";
    comprobar(vale(medio + tercio, 5, 6), "1/2 + 1/3 = 5/6");
    comprobar(vale(medio + medio, 1, 1), "1/2 + 1/2 = 1 (simplificada)");
    comprobar(vale(medio + Fraccion(-1, 2), 0, 1), "1/2 + (-1/2) = 0");
    comprobar(vale(Fraccion(2, 3) * Fraccion(3, 4), 1, 2), "2/3 * 3/4 = 1/2");
    Fraccion a(1, 4);
    Fraccion b = a + a;
    comprobar(vale(a, 1, 4) && vale(b, 1, 2), "a + a no cambia a (sigue en 1/4)");

    cout << "<:\n";
    comprobar(tercio < medio, "1/3 < 1/2");
    comprobar(!(medio < tercio), "1/2 no es < 1/3");
    comprobar(Fraccion(-1, 2) < Fraccion(1, 3), "-1/2 < 1/3");

    cout << "<<:\n";
    comprobar(comoTexto(Fraccion(3, 4)) == "3/4", "imprime 3/4 como \"3/4\"");
    comprobar(comoTexto(Fraccion(10, 2)) == "5", "imprime 10/2 como \"5\"");
    comprobar(comoTexto(Fraccion(1, -3)) == "-1/3", "imprime 1/-3 como \"-1/3\"");
    ostringstream encadenado;
    encadenado << medio << " + " << tercio << " = " << medio + tercio;
    comprobar(encadenado.str() == "1/2 + 1/3 = 5/6", "se puede encadenar: 1/2 + 1/3 = 5/6");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 2.7 terminado.\n"
                         : "\nAún hay fallos. Revisa los operadores con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
