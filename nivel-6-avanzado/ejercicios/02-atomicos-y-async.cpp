// Miniproyecto 6.2 — Una cola para dos hilos
// ---------------------------------------------------------------
// Completa las funciones marcadas con TODO. No toques main().
// Vas a contar con un atómico, construir la cola del productor-consumidor
// (mutex + condition_variable) y repartir una suma con async y future.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++20 -Wall -pthread 02-atomicos-y-async.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste. Para comprobar además que no
// hay carreras de datos (si lo hiciste bien, no sale ningún WARNING):
//   g++ -std=c++20 -Wall -pthread -fsanitize=thread -g 02-atomicos-y-async.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <future>
#include <queue>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstdlib>
using namespace std;

// 1) Como sumarConHilos de la 6.1, pero sin mutex: con un atomic<int>.
//    Pista: atomic<int> contador = 0; y el resto igual que en la 6.1,
//    pero SIN mutex: contador++ ya es atómico. Al final, contador.load().
int contarConAtomico(int nHilos, int porHilo) {
    (void)nHilos; (void)porHilo;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return 0;
}

// 2) Una cola que varios hilos pueden usar a la vez.
//    Los productores meten() y, al terminar, alguien llama a cerrar().
//    Los consumidores sacan(): si no hay nada, ESPERAN dormidos.
class ColaSegura {
private:
    queue<int> datos;
    mutex m;
    condition_variable hayCambios;
    bool cerrada = false;

public:
    // Mete x y despierta a UN consumidor que esté esperando.
    //    Pista: un bloque { lock_guard<mutex> candado(m); datos.push(x); }
    //    y DESPUÉS, fuera del bloque, hayCambios.notify_one();
    void meter(int x) {
        (void)x;   // calla un aviso del compilador: bórrala al empezar
        // TODO
    }

    // Ya no llegará nada más: despierta a TODOS para que puedan terminar.
    //    Pista: igual que meter, pero pone cerrada = true y usa notify_all().
    void cerrar() {
        // TODO
    }

    // Espera hasta que haya un dato o la cola esté cerrada.
    // Si hay dato: lo copia en x, lo quita y devuelve true.
    // Si está cerrada y vacía: devuelve false (no hay más trabajo).
    //    Pista: unique_lock<mutex> candado(m);  (wait necesita unique_lock)
    //    hayCambios.wait(candado, [this] { return !datos.empty() || cerrada; });
    //    Al despertar: si datos está vacía, es que se cerró → false.
    bool sacar(int& x) {
        (void)x;   // calla un aviso del compilador: bórrala al empezar
        // TODO
        return false;
    }
};

// 3) Suma v repartiéndola en «partes» tareas con async.
//    Pista: vector<future<long long>> futuros; para cada parte,
//    futuros.push_back(async(launch::async, [&v, desde, hasta] { ... return s; }));
//    Los trozos, como en contarPares de la 6.1. Al final suma f.get() de cada una.
long long sumaParalela(const vector<int>& v, int partes) {
    (void)v; (void)partes;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return 0;
}

// Ya hecha: la raíz cuadrada entera. Con un negativo LANZA.
int raizEntera(int n) {
    if (n < 0) throw invalid_argument("raíz de un negativo");
    int r = 0;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

// 4) Calcula raizEntera(n) en segundo plano con async.
//    Devuelve el resultado como texto ("12"), o "error" si la tarea lanzó.
//    Pista: future<int> f = async(launch::async, raizEntera, n);
//    y luego f.get() dentro de un try; catch (const invalid_argument&).
string raizEnSegundoPlano(int n) {
    (void)n;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return "";
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// Corre una prueba con hilos con un tiempo máximo. Si un hilo se queda
// esperando para siempre (un wait que nadie despierta), avisa y sale.
template <typename F>
void conTiempoMaximo(F prueba, const char* que) {
    auto f = async(launch::async, prueba);
    if (f.wait_for(chrono::seconds(10)) == future_status::timeout) {
        cout << "  ✗ " << que << ": un hilo se quedó esperando para siempre\n" << flush;
        _Exit(1);   // salir ya: los hilos atascados no se pueden esperar
    }
    f.get();
}

int main() {
    cout << "contarConAtomico:\n";
    comprobar(contarConAtomico(1, 1000) == 1000, "1 hilo x 1000  ->  1000");
    comprobar(contarConAtomico(8, 20000) == 160000, "8 hilos x 20000  ->  160000 exacto");

    cout << "ColaSegura (un solo hilo):\n";
    int a = 0, b = 0, z = 0;
    bool r1 = false, r2 = false, r3 = true;
    conTiempoMaximo([&] {
        ColaSegura c;
        c.meter(1);
        c.meter(2);
        c.cerrar();
        r1 = c.sacar(a);
        r2 = c.sacar(b);
        r3 = c.sacar(z);     // cerrada y vacía: NO debe quedarse esperando
    }, "sacar de una cola cerrada");
    comprobar(r1 && r2 && a == 1 && b == 2, "meter 1, 2  ->  sale 1 y luego 2 (en orden)");
    comprobar(!r3, "cerrada y vacía  ->  sacar devuelve false sin quedarse esperando");

    cout << "ColaSegura (productor y consumidor):\n";
    long long suma1 = 0;
    conTiempoMaximo([&] {
        ColaSegura c;
        thread consumidor([&] { int x; while (c.sacar(x)) suma1 += x; });   // empieza ANTES que haya datos
        thread productor([&] { for (int i = 1; i <= 1000; i++) c.meter(i); c.cerrar(); });
        productor.join();
        consumidor.join();
    }, "productor y consumidor");
    comprobar(suma1 == 500500, "1 productor 1..1000, 1 consumidor  ->  suma 500500");

    long long suma2 = 0;
    int cuantos = 0;
    conTiempoMaximo([&] {
        ColaSegura c;
        mutex mSuma;
        vector<thread> consumidores;
        for (int k = 0; k < 3; k++)
            consumidores.push_back(thread([&] {
                int x;
                while (c.sacar(x)) { lock_guard<mutex> l(mSuma); suma2 += x; cuantos++; }
            }));
        thread p1([&] { for (int i = 1; i <= 500; i++) c.meter(i); });
        thread p2([&] { for (int i = 501; i <= 1000; i++) c.meter(i); });
        p1.join();
        p2.join();
        c.cerrar();                     // cerrar cuando los DOS productores acabaron
        for (thread& h : consumidores) h.join();
    }, "2 productores y 3 consumidores");
    comprobar(suma2 == 500500 && cuantos == 1000, "2 productores, 3 consumidores  ->  1000 datos, suma 500500");

    cout << "sumaParalela:\n";
    vector<int> v;
    for (int i = 1; i <= 100000; i++) v.push_back(i);
    comprobar(sumaParalela(v, 1) == 5000050000LL, "1..100000 en 1 parte  ->  5000050000");
    comprobar(sumaParalela(v, 7) == 5000050000LL, "1..100000 en 7 partes  ->  5000050000");
    comprobar(sumaParalela({5, 6}, 4) == 11, "más partes que números  ->  11");

    cout << "raizEnSegundoPlano:\n";
    comprobar(raizEnSegundoPlano(144) == "12", "raíz de 144  ->  \"12\"");
    comprobar(raizEnSegundoPlano(10) == "3", "raíz de 10  ->  \"3\"");
    comprobar(raizEnSegundoPlano(-4) == "error", "raíz de -4  ->  la excepción llega por get(): \"error\"");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.2 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
