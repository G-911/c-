// SOLUCIÓN — Miniproyecto final 4.8 — Gestor de inventario
// Ábrela solo después de intentarlo de verdad.
// ---------------------------------------------------------------
// Junta casi todo el curso en un solo programa:
//   clases (2.4) · map y vector (4.2) · sort y accumulate con lambdas (4.3)
//   excepciones (4.4) · archivos (4.6)
//
// Ya están hechos: el constructor, agregar(), cantidadDe() y guardar().
// Completa las CUATRO funciones marcadas con TODO. No toques main().
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 08-panorama.cpp -o prog && ./prog
//
// El archivo de datos se crea en /tmp. Cuando todo salga con ✓, terminaste el curso.
// ---------------------------------------------------------------
#include <algorithm>   // sort
#include <cstdio>      // remove
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>     // accumulate
#include <stdexcept>   // invalid_argument, out_of_range, runtime_error
#include <string>
#include <vector>
using namespace std;

struct Producto {
    string nombre;
    int cantidad;
    double precio;     // precio de UNA unidad
};

// Ya hecha: parte "a;b;c" en {"a","b","c"} (la usarás en cargar).
vector<string> separar(const string& linea, char sep) {
    vector<string> partes;
    string actual;
    for (char c : linea) {
        if (c == sep) { partes.push_back(actual); actual = ""; }
        else actual += c;
    }
    partes.push_back(actual);
    return partes;
}

class Inventario {
    map<string, Producto> productos;   // clave: el nombre

public:
    // Ya hecha. Si el producto existe, suma la cantidad y actualiza el precio.
    void agregar(const string& nombre, int cantidad, double precio) {
        if (nombre.empty() || cantidad < 0 || precio < 0) {
            throw invalid_argument("datos de producto no válidos");
        }
        auto it = productos.find(nombre);
        if (it == productos.end()) {
            productos[nombre] = Producto{nombre, cantidad, precio};
        } else {
            it->second.cantidad += cantidad;
            it->second.precio = precio;
        }
    }

    // Ya hecha. 0 si no existe.
    int cantidadDe(const string& nombre) const {
        auto it = productos.find(nombre);
        return it == productos.end() ? 0 : it->second.cantidad;
    }

    int totalProductos() const { return static_cast<int>(productos.size()); }

    // 1) Resta 'cantidad' unidades del producto.
    //    - Si el producto no existe:            throw out_of_range("no existe: " + nombre);
    //    - Si no hay suficientes unidades:      throw runtime_error("stock insuficiente");
    //    - Si no, resta. (Si queda en 0, se queda en el inventario con 0.)
    void retirar(const string& nombre, int cantidad) {
        auto it = productos.find(nombre);
        if (it == productos.end()) throw out_of_range("no existe: " + nombre);
        if (it->second.cantidad < cantidad) throw runtime_error("stock insuficiente");
        it->second.cantidad -= cantidad;   // solo se toca DESPUÉS de comprobar todo
    }

    // 2) Valor total = suma de cantidad * precio de todos los productos.
    //    Pista: accumulate(productos.begin(), productos.end(), 0.0,
    //             [](double suma, const pair<const string, Producto>& par) { ... });
    double valorTotal() const {
        return accumulate(productos.begin(), productos.end(), 0.0,
            [](double suma, const pair<const string, Producto>& par) {
                return suma + par.second.cantidad * par.second.precio;
            });
    }

    // 3) Nombres de los productos con cantidad < limite, ORDENADOS de menor a
    //    mayor cantidad (si empatan, da igual el orden).
    //    Pista: junta los Producto en un vector, usa sort con una lambda que
    //    compare .cantidad, y luego copia los nombres.
    vector<string> bajoStock(int limite) const {
        vector<Producto> pocos;
        for (const auto& par : productos) {
            if (par.second.cantidad < limite) pocos.push_back(par.second);
        }
        sort(pocos.begin(), pocos.end(),
             [](const Producto& a, const Producto& b) { return a.cantidad < b.cantidad; });
        vector<string> nombres;
        for (const Producto& p : pocos) nombres.push_back(p.nombre);
        return nombres;   // devolver un vector por valor es barato (lección 4.7)
    }

    // Ya hecha: una línea por producto,  nombre;cantidad;precio
    bool guardar(const string& ruta) const {
        ofstream archivo(ruta);
        if (!archivo) return false;
        for (const auto& par : productos) {
            const Producto& p = par.second;
            archivo << p.nombre << ";" << p.cantidad << ";" << p.precio << "\n";
        }
        return true;
    }

    // 4) Vacía el inventario (productos.clear()) y lo rellena desde el archivo.
    //    - Si no se puede abrir: devuelve false (y el inventario queda vacío).
    //    - Lee línea a línea con getline; sáltate las líneas vacías.
    //    - Cada línea: auto partes = separar(linea, ';');
    //      si partes.size() != 3, throw runtime_error("línea mal formada");
    //    - stoi(partes[1]) da el int y stod(partes[2]) el double.
    //      Usa agregar(...) para meterlo. Devuelve true al terminar.
    bool cargar(const string& ruta) {
        productos.clear();
        ifstream archivo(ruta);
        if (!archivo) return false;
        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            auto partes = separar(linea, ';');
            if (partes.size() != 3) throw runtime_error("línea mal formada");
            agregar(partes[0], stoi(partes[1]), stod(partes[2]));
        }
        return true;
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}
bool casiIgual(double a, double b) { return a - b < 1e-6 && b - a < 1e-6; }

int main() {
    const string ruta = "/tmp/curso-cpp-48-inventario.txt";
    remove(ruta.c_str());

    Inventario inv;
    inv.agregar("arroz", 10, 1.5);
    inv.agregar("aceite", 3, 4.0);
    inv.agregar("sal", 0, 0.5);
    inv.agregar("harina", 7, 2.0);

    cout << "retirar:\n";
    inv.retirar("arroz", 4);
    comprobar(inv.cantidadDe("arroz") == 6, "retirar 4 de 10 arroz deja 6");

    bool lanzoOut = false;
    try { inv.retirar("café", 1); } catch (const out_of_range&) { lanzoOut = true; } catch (...) {}
    comprobar(lanzoOut, "retirar un producto que no existe lanza out_of_range");

    bool lanzoRun = false;
    try { inv.retirar("aceite", 5); } catch (const runtime_error&) { lanzoRun = true; } catch (...) {}
    comprobar(lanzoRun && inv.cantidadDe("aceite") == 3,
              "retirar más de lo que hay lanza runtime_error y no cambia nada");

    cout << "valorTotal:\n";
    // arroz 6*1.5 = 9, aceite 3*4 = 12, sal 0, harina 7*2 = 14  → 35
    comprobar(casiIgual(inv.valorTotal(), 35.0), "valor total = 35");
    comprobar(casiIgual(Inventario().valorTotal(), 0.0) && inv.totalProductos() == 4,
              "un inventario vacío vale 0");

    cout << "bajoStock:\n";
    comprobar(inv.bajoStock(7) == vector<string>{"sal", "aceite", "arroz"},
              "bajoStock(7) = {sal, aceite, arroz}, de menor a mayor");
    comprobar(inv.bajoStock(0).empty(), "bajoStock(0) está vacío");

    cout << "guardar y cargar:\n";
    comprobar(inv.guardar(ruta), "guardar devuelve true");
    Inventario copia;
    copia.agregar("borrame", 1, 1.0);
    comprobar(copia.cargar(ruta) && copia.totalProductos() == 4 && copia.cantidadDe("harina") == 7
              && copia.cantidadDe("borrame") == 0 && casiIgual(copia.valorTotal(), 35.0),
              "cargar reconstruye el mismo inventario (y borra lo que había)");

    Inventario otro;
    comprobar(!otro.cargar("/tmp/curso-cpp-48-no-existe.txt") && otro.totalProductos() == 0,
              "cargar un archivo que no existe devuelve false");

    ofstream malo(ruta);
    malo << "pan;2;1.0\n\nesto no tiene formato\n";
    malo.close();
    bool lanzoMal = false;
    try { otro.cargar(ruta); } catch (const runtime_error&) { lanzoMal = true; } catch (...) {}
    comprobar(lanzoMal, "una línea mal formada lanza runtime_error");

    remove(ruta.c_str());
    cout << (fallos == 0 ? "\n¡Todo bien! Terminaste el miniproyecto final... y el curso.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
