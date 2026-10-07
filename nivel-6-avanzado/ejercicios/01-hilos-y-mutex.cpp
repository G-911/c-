// Miniproyecto 6.1 — Hilos que no se pisan
// ---------------------------------------------------------------
// Completa las CUATRO funciones marcadas con TODO. No toques main().
// Vas a lanzar varios hilos, proteger un dato compartido con un mutex,
// repartir trabajo sin compartir nada, y transferir dinero entre dos
// cuentas sin que los hilos se queden esperándose para siempre.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++20 -Wall -pthread 01-hilos-y-mutex.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste. Para comprobar además que no
// hay carreras de datos (si lo hiciste bien, no sale ningún WARNING):
//   g++ -std=c++20 -Wall -pthread -fsanitize=thread -g 01-hilos-y-mutex.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <future>    // solo lo usan las pruebas (lo verás en la 6.2)
#include <chrono>
#include <cstdlib>
using namespace std;

// 1) Lanza nHilos hilos. Cada uno suma 1 al contador porHilo veces.
//    El contador es compartido: protégelo con un mutex.
//    Pista: un int contador y un mutex m locales; vector<thread> hilos;
//    hilos.push_back(thread([&] { ... }));  dentro del bucle del hilo,
//    lock_guard<mutex> candado(m); antes de contador++.
//    Al final, join() de TODOS antes de devolver el contador.
int sumarConHilos(int nHilos, int porHilo) {
    (void)nHilos; (void)porHilo;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return 0;
}

// 2) Cuenta los números pares de v repartiendo el trabajo entre nHilos.
//    Cada hilo cuenta SU trozo en SU casilla de parciales: no comparten nada,
//    así que no hace falta mutex.
//    Pista: vector<int> parciales(nHilos, 0). El hilo i recorre desde
//    i*n/nHilos hasta (i+1)*n/nHilos (sin incluir) y suma en parciales[i].
//    Captura i, desde y hasta POR COPIA: el bucle los cambia enseguida.
int contarPares(const vector<int>& v, int nHilos) {
    (void)v; (void)nHilos;   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return 0;
}

// 3) Cuenta bancaria con su propio mutex.
struct Cuenta {
    int saldo;
    mutex m;
    Cuenta(int s) : saldo(s) {}
};

//    Pasa monto de «de» a «a». Si «de» no tiene saldo suficiente,
//    no toca nada y devuelve false. Bloquea las DOS cuentas con
//    scoped_lock para no caer en un interbloqueo.
//    Pista: scoped_lock candado(de.m, a.m); y DESPUÉS comprueba el saldo.
bool transferir(Cuenta& de, Cuenta& a, int monto) {
    if (&de == &a) return false;   // misma cuenta: no tiene sentido (esta línea ya va bien)
    (void)monto;                   // calla un aviso del compilador: bórrala al empezar
    // TODO
    return false;
}

// 4) Cuántos hilos conviene usar en esta máquina.
//    hardware_concurrency() puede devolver 0 si no lo sabe: en ese caso, 2.
//    Pista: unsigned n = thread::hardware_concurrency();
int hilosParaUsar() {
    // TODO
    return 0;
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    cout << "sumarConHilos:\n";
    comprobar(sumarConHilos(1, 1000) == 1000, "1 hilo x 1000  ->  1000");
    comprobar(sumarConHilos(8, 20000) == 160000, "8 hilos x 20000  ->  160000 exacto");
    comprobar(sumarConHilos(0, 50) == 0, "0 hilos  ->  0");

    cout << "contarPares:\n";
    vector<int> v;
    for (int i = 1; i <= 10000; i++) v.push_back(i);
    comprobar(contarPares(v, 1) == 5000, "1..10000 con 1 hilo  ->  5000");
    comprobar(contarPares(v, 3) == 5000, "1..10000 con 3 hilos (no divide exacto)  ->  5000");
    comprobar(contarPares({2, 4, 5}, 8) == 2, "más hilos que números  ->  2");
    comprobar(contarPares({}, 4) == 0, "vector vacío  ->  0");

    cout << "transferir:\n";
    {
        Cuenta ana(100), beto(0);
        bool ok = transferir(ana, beto, 30);
        comprobar(ok && ana.saldo == 70 && beto.saldo == 30, "ana 100 -> beto 30  ->  70 y 30");
        bool mal = transferir(ana, beto, 500);
        comprobar(!mal && ana.saldo == 70 && beto.saldo == 30, "sin saldo  ->  false y no cambia nada");
    }
    {
        // Cuatro hilos transfieren en los DOS sentidos a la vez.
        // Si transferir se interbloquea, esta prueba no terminaría:
        // por eso corre con un tiempo máximo (async y future, lección 6.2).
        Cuenta ana(1000), beto(1000);
        auto prueba = async(launch::async, [&] {
            vector<thread> hilos;
            for (int i = 0; i < 2; i++) {
                hilos.push_back(thread([&] { for (int k = 0; k < 20000; k++) transferir(ana, beto, 1); }));
                hilos.push_back(thread([&] { for (int k = 0; k < 20000; k++) transferir(beto, ana, 1); }));
            }
            for (thread& h : hilos) h.join();
        });
        if (prueba.wait_for(chrono::seconds(10)) == future_status::timeout) {
            cout << "  ✗ los hilos se quedaron esperándose: interbloqueo\n" << flush;
            _Exit(1);   // salir ya: los hilos atascados no se pueden esperar
        }
        prueba.get();
        comprobar(ana.saldo + beto.saldo == 2000, "4 hilos en los dos sentidos  ->  el total sigue en 2000");
        comprobar(ana.saldo >= 0 && beto.saldo >= 0, "ningún saldo queda negativo");
    }
    {
        Cuenta ana(50);
        comprobar(!transferir(ana, ana, 10) && ana.saldo == 50, "a la misma cuenta  ->  false");
    }

    cout << "hilosParaUsar:\n";
    unsigned hc = thread::hardware_concurrency();
    int h = hilosParaUsar();
    comprobar(h >= 1, "al menos 1 hilo");
    comprobar(hc == 0 ? h == 2 : h == (int)hc, "usa hardware_concurrency (o 2 si devuelve 0)");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 6.1 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
