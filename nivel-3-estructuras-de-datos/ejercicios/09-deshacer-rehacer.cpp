// Miniproyecto 3.9 — Deshacer y rehacer con dos pilas
// ---------------------------------------------------------------
// Completa los TRES métodos marcados con TODO: escribir, deshacer y
// rehacer. No toques main() ni el resto de la clase.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 09-deshacer-rehacer.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
// La idea: antes de CADA cambio, guarda el texto como estaba.
//   pilaDeshacer: textos anteriores (el más reciente arriba).
//   pilaRehacer:  textos que deshiciste (para poder volver a ellos).
// Recuerda: con std::stack, top() LEE el de arriba y pop() lo QUITA
// (pop no devuelve nada). Nunca llames top() ni pop() con la pila vacía.
// ---------------------------------------------------------------
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Editor {
private:
    string texto;               // lo que se ve en pantalla
    stack<string> pilaDeshacer; // versiones anteriores de texto
    stack<string> pilaRehacer;  // versiones que se deshicieron

public:
    Editor() : texto("") {}

    string getTexto() const { return texto; }
    bool puedeDeshacer() const { return !pilaDeshacer.empty(); }
    bool puedeRehacer() const { return !pilaRehacer.empty(); }

    // 1) Añade una palabra al final del texto.
    //    Si el texto está vacío queda solo la palabra ("hola");
    //    si no, se añade con un espacio delante ("hola" -> "hola mundo").
    //    Antes de cambiar el texto, guarda el texto actual en pilaDeshacer.
    //    Escribir algo nuevo invalida lo que habías deshecho: vacía pilaRehacer.
    //    Pista: std::stack no tiene clear(). Vacíala con
    //           while (!pilaRehacer.empty()) pilaRehacer.pop();
    void escribir(const string& palabra) {
        (void)palabra;   // borra esta línea cuando empieces
        // TODO
    }

    // 2) Vuelve al texto anterior.
    //    Si pilaDeshacer está vacía, no hace NADA.
    //    Si no: guarda el texto actual en pilaRehacer, toma el de arriba
    //    de pilaDeshacer como nuevo texto y quítalo de esa pila.
    //    Pista: son 3 líneas: push, top, pop (en ese orden).
    void deshacer() {
        // TODO
    }

    // 3) Lo contrario de deshacer.
    //    Si pilaRehacer está vacía, no hace NADA.
    //    Si no: guarda el texto actual en pilaDeshacer, toma el de arriba
    //    de pilaRehacer como nuevo texto y quítalo de esa pila.
    //    Pista: es deshacer() con las dos pilas intercambiadas.
    void rehacer() {
        // TODO
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "escribir:\n";
    Editor e;
    e.escribir("hola");
    comprobar(e.getTexto() == "hola", "escribir \"hola\" en vacío deja \"hola\" (sin espacio)");
    e.escribir("mundo");
    comprobar(e.getTexto() == "hola mundo", "escribir \"mundo\" deja \"hola mundo\"");

    cout << "deshacer:\n";
    e.deshacer();
    comprobar(e.getTexto() == "hola", "deshacer una vez vuelve a \"hola\"");
    e.deshacer();
    e.deshacer();   // ya no queda historial: este no debe hacer nada
    comprobar(e.getTexto() == "" && !e.puedeDeshacer(),
              "deshacer de más vuelve al texto vacío y no se cae");

    cout << "rehacer:\n";
    e.rehacer();
    comprobar(e.getTexto() == "hola", "rehacer recupera \"hola\"");
    e.rehacer();
    e.rehacer();    // ya no queda nada deshecho: este no debe hacer nada
    comprobar(e.getTexto() == "hola mundo" && !e.puedeRehacer(),
              "rehacer de más llega a \"hola mundo\" y no se cae");

    cout << "escribir después de deshacer:\n";
    e.deshacer();                     // "hola"
    e.escribir("gente");              // "hola gente" y se pierde "hola mundo"
    comprobar(e.getTexto() == "hola gente", "deshacer y escribir \"gente\" deja \"hola gente\"");
    comprobar(!e.puedeRehacer(), "escribir vacía la pila de rehacer");
    e.rehacer();
    comprobar(e.getTexto() == "hola gente", "por eso rehacer ya no cambia nada");
    e.deshacer();
    comprobar(e.getTexto() == "hola", "deshacer sigue funcionando: vuelve a \"hola\"");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 3.9 terminado. Terminaste el Nivel 3.\n"
                         : "\nAún hay fallos. Revisa los métodos con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
