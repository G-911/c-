// SOLUCIÓN del Miniproyecto 5.4 — Un montículo de máximos y los k mayores
// Ábrela solo después de intentarlo de verdad.
// ---------------------------------------------------------------
// Completa las CINCO funciones marcadas con TODO. No toques main().
// El montículo guarda sus datos en un vector:
//   padre de i  = (i - 1) / 2
//   hijos de i  = 2*i + 1  y  2*i + 2
// y cumple: cada padre es >= que sus hijos (el máximo está en datos[0]).
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 04-monticulos-y-colas-de-prioridad.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <vector>
#include <queue>       // priority_queue
#include <functional>  // greater
#include <stdexcept>   // out_of_range
#include <utility>     // swap
using namespace std;

class Monticulo {
private:
    vector<int> datos;   // el árbol, guardado por niveles

    // 1) SUBIR: el elemento de la posición i acaba de llegar abajo.
    //    Mientras no sea la raíz (i > 0) y sea MAYOR que su padre,
    //    intercámbialo con el padre y sigue desde la posición del padre.
    //    Pista: int padre = (i - 1) / 2;  swap(datos[i], datos[padre]);  i = padre;
    void subir(int i) {
        while (i > 0) {
            int padre = (i - 1) / 2;
            if (datos[i] <= datos[padre]) break;   // ya está en su sitio
            swap(datos[i], datos[padre]);
            i = padre;                              // seguimos desde arriba
        }
    }

    // 2) HUNDIR: el elemento de la posición i puede ser más pequeño que
    //    sus hijos. Repite: busca el MAYOR entre i y sus hijos que existan
    //    (un hijo existe si su índice < tamano()). Si el mayor es i, para.
    //    Si no, intercambia i con ese hijo y sigue desde el hijo.
    //    Pista: int izq = 2*i + 1, der = 2*i + 2, mayor = i;
    void hundir(int i) {
        int n = tamano();
        while (true) {
            int izq = 2 * i + 1, der = 2 * i + 2, mayor = i;
            if (izq < n && datos[izq] > datos[mayor]) mayor = izq;
            if (der < n && datos[der] > datos[mayor]) mayor = der;
            if (mayor == i) break;                  // ningún hijo es mayor: para
            swap(datos[i], datos[mayor]);
            i = mayor;                              // seguimos desde abajo
        }
    }

public:
    bool vacia() const { return datos.empty(); }
    int tamano() const { return (int)datos.size(); }

    // Ya está hecha: si subir() funciona, insertar también.
    void insertar(int valor) {
        datos.push_back(valor);          // entra por el final (abajo)
        subir(tamano() - 1);             // y sube hasta su sitio
    }

    int verMax() const {
        if (vacia()) throw out_of_range("verMax: montículo vacío");
        return datos[0];
    }

    // 3) EXTRAER EL MÁXIMO: devuelve datos[0] y lo quita.
    //    - Si está vacío, lanza out_of_range (como en la lección 4.4).
    //    - Guarda la raíz, pon el ÚLTIMO en la raíz, haz pop_back()
    //      y hunde desde 0 (solo si queda algo).
    int extraerMax() {
        if (vacia()) throw out_of_range("extraerMax: montículo vacío");
        int maximo = datos[0];
        datos[0] = datos.back();     // el último pasa a la raíz
        datos.pop_back();
        if (!vacia()) hundir(0);     // y se hunde hasta su sitio
        return maximo;
    }

    // Para las pruebas: una copia del vector interno.
    vector<int> verDatos() const { return datos; }
};

// 4) ¿Este vector cumple la propiedad de montículo de máximos?
//    Para cada i desde 1, su padre (i - 1) / 2 debe ser >= v[i].
//    Un vector vacío o de un elemento sí es montículo.
bool esMonticulo(const vector<int>& v) {
    for (int i = 1; i < (int)v.size(); i++) {
        if (v[(i - 1) / 2] < v[i]) return false;   // un hijo supera a su padre
    }
    return true;
}

// 5) Los k mayores de v, de MAYOR a MENOR, usando std::priority_queue.
//    Idea: una cola de prioridad de MÍNIMOS con como mucho k elementos.
//    Por cada x de v: push(x); si pasa de k elementos, pop() (sale el más chico).
//    Al final, sácalos todos (salen de menor a mayor) y dales la vuelta.
//    Si k <= 0 devuelve un vector vacío. Si k > v.size(), devuelve todos.
//    Pista: priority_queue<int, vector<int>, greater<int>> pq;
vector<int> kMayores(const vector<int>& v, int k) {
    if (k <= 0) return {};
    priority_queue<int, vector<int>, greater<int>> pq;   // arriba, el MENOR
    for (int x : v) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();                // sobra uno: fuera el más chico
    }
    vector<int> r;
    while (!pq.empty()) { r.push_back(pq.top()); pq.pop(); }   // salen de menor a mayor
    return vector<int>(r.rbegin(), r.rend());                 // al revés: de mayor a menor
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "insertar y subir:\n";
    {
        Monticulo m;
        for (int x : {30, 20, 25, 5, 10, 12}) m.insertar(x);
        comprobar(m.verDatos() == vector<int>{30, 20, 25, 5, 10, 12},
                  "insertar 30 20 25 5 10 12  ->  datos = 30 20 25 5 10 12");
        m.insertar(28);
        comprobar(m.verDatos() == vector<int>{30, 20, 28, 5, 10, 12, 25},
                  "insertar 28  ->  sube al índice 2: 30 20 28 5 10 12 25");
        m.insertar(99);
        comprobar(m.verMax() == 99 && esMonticulo(m.verDatos()),
                  "insertar 99  ->  sube hasta la raíz");
    }

    cout << "extraerMax y hundir:\n";
    {
        Monticulo m;
        for (int x : {30, 20, 25, 5, 10, 12}) m.insertar(x);
        int a = m.extraerMax();
        comprobar(a == 30 && m.verDatos() == vector<int>{25, 20, 12, 5, 10},
                  "extraer de 30 20 25 5 10 12  ->  30, y quedan 25 20 12 5 10");

        Monticulo m2;
        for (int x : {4, 10, 3, 5, 1, 10, 7}) m2.insertar(x);
        vector<int> salida;
        int vueltas = 0;
        while (!m2.vacia() && vueltas < 20) { salida.push_back(m2.extraerMax()); vueltas++; }
        comprobar(salida == vector<int>{10, 10, 7, 5, 4, 3, 1},
                  "4 10 3 5 1 10 7  ->  salen 10 10 7 5 4 3 1 (con repetidos)");

        bool lanzo = false;
        try { m2.extraerMax(); } catch (const out_of_range&) { lanzo = true; }
        comprobar(lanzo, "extraerMax sobre vacío lanza out_of_range");
    }

    cout << "muchos datos:\n";
    {
        Monticulo m;
        bool siempre = true;
        for (int i = 0; i < 1000; i++) {
            m.insertar((i * 37) % 101);
            if (!esMonticulo(m.verDatos())) siempre = false;
        }
        int anterior = 1000000, vueltas = 0;
        bool ordenado = true;
        while (!m.vacia() && vueltas < 2000) {
            int x = m.extraerMax();
            if (x > anterior) ordenado = false;
            anterior = x;
            vueltas++;
        }
        comprobar(siempre && ordenado && vueltas == 1000,
                  "1000 inserciones: siempre es montículo y sale de mayor a menor");
    }

    cout << "esMonticulo:\n";
    comprobar(esMonticulo({}) && esMonticulo({7}), "vacío y de un elemento: sí");
    comprobar(esMonticulo({9, 5, 8, 1, 4}), "9 5 8 1 4: sí");
    comprobar(!esMonticulo({9, 5, 8, 6, 1}), "9 5 8 6 1: no (el 6 supera a su padre 5)");

    cout << "kMayores:\n";
    comprobar(kMayores({4, 1, 9, 7, 3, 8}, 3) == vector<int>{9, 8, 7},
              "k = 3 de 4 1 9 7 3 8  ->  9 8 7");
    comprobar(kMayores({5, 5, 2}, 2) == vector<int>{5, 5}, "con repetidos: 5 5");
    comprobar(kMayores({2, 1}, 5) == vector<int>{2, 1} && kMayores({2, 1}, 0).empty(),
              "k mayor que el tamaño: todos; k = 0: ninguno");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 5.4 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
