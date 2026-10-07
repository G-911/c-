// Miniproyecto 5.7 — Recorrer un grafo y buscar caminos
// ---------------------------------------------------------------
// Completa las CINCO funciones marcadas con TODO. No toques main(),
// los constructores ni agregarArista.
// El grafo de las pruebas es el de la lección (6 vértices): tenlo dibujado al lado.
// Los vecinos se recorren SIEMPRE en el orden de ady[u]; de eso depende el orden de visita.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 07-grafos.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste el miniproyecto y el Nivel 5.
// ---------------------------------------------------------------
#include <algorithm>   // reverse
#include <climits>     // INT_MAX
#include <functional>  // greater
#include <iostream>
#include <queue>       // queue, priority_queue
#include <utility>     // pair
#include <vector>
using namespace std;

// Grafo SIN pesos con lista de adyacencia. Vértices: 0 .. n-1.
class Grafo {
private:
    int n;
    bool dirigido;
    vector<vector<int>> ady;   // ady[u] = vecinos de u, en el orden en que se añadieron

    // 2) Ayudante recursivo de dfs: visita u y, desde él, todo lo alcanzable.
    //    Pista: marca u, mételo en orden, y para cada vecino v NO visitado,
    //    llama a dfsDesde(v, visitado, orden). La recursión hace de pila.
    void dfsDesde(int u, vector<bool>& visitado, vector<int>& orden) const {
        (void)u; (void)visitado; (void)orden;   // evita avisos; bórrala al empezar
        // TODO
    }

public:
    // Ya hecho.
    Grafo(int vertices, bool esDirigido = false)
        : n(vertices), dirigido(esDirigido), ady(vertices) {}

    void agregarArista(int u, int v) {
        ady[u].push_back(v);
        if (!dirigido) ady[v].push_back(u);   // no dirigido: la arista va en los dos sentidos
    }

    int numVertices() const { return n; }

    // 1) BFS desde origen: devuelve los vértices en el orden en que se visitan.
    //    Pista: vector<bool> visitado(n, false); queue<int> cola;
    //    marca y encola el origen. Mientras la cola no esté vacía: saca el del frente,
    //    añádelo a orden, y marca y encola cada vecino NO visitado.
    //    Marca al ENCOLAR, no al sacar: si no, un vértice entra dos veces.
    vector<int> bfs(int origen) const {
        (void)origen;   // evita un aviso; bórrala al empezar
        return {}; // TODO
    }

    // Ya hecho: DFS desde origen (usa tu dfsDesde).
    vector<int> dfs(int origen) const {
        vector<int> orden;
        vector<bool> visitado(n, false);
        dfsDesde(origen, visitado, orden);
        return orden;
    }

    // 3) Camino más corto (en número de aristas) de origen a destino, con BFS.
    //    Devuelve los vértices del camino, de origen a destino. Vacío si no hay camino.
    //    Pista: el mismo BFS, pero guardando padre[v] = u al descubrir v.
    //    Al final, si destino no se visitó: return {}. Si sí: sigue padre[] desde
    //    destino hasta -1 metiendo cada vértice, y dale la vuelta con reverse.
    vector<int> caminoMasCorto(int origen, int destino) const {
        (void)origen; (void)destino;   // evita avisos; bórrala al empezar
        return {}; // TODO
    }

    // 4) Cuántas componentes conexas tiene (grafo no dirigido): cuántas «islas».
    //    Pista: recorre u = 0..n-1; cada vez que encuentres uno NO visitado,
    //    cuenta una isla y llama a dfsDesde(u, ...) para marcarla entera.
    int componentes() const {
        return 0; // TODO
    }
};

// Grafo CON pesos: ady[u] = pares (vecino, peso).
class GrafoPonderado {
private:
    int n;
    vector<vector<pair<int, int>>> ady;

public:
    // Ya hecho.
    GrafoPonderado(int vertices) : n(vertices), ady(vertices) {}

    void agregarArista(int u, int v, int peso) {   // no dirigido
        ady[u].push_back({v, peso});
        ady[v].push_back({u, peso});
    }

    // 5) Dijkstra desde origen: distancia mínima a cada vértice.
    //    -1 para los vértices a los que no se puede llegar. Pesos >= 0.
    //    Pista: dist(n, INT_MAX); dist[origen] = 0;
    //    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    //    con pares (distancia, vértice). Saca el menor; si d > dist[u], sáltalo (es viejo).
    //    Para cada (v, peso): si dist[u] + peso < dist[v], mejora dist[v] y empuja.
    //    Al final cambia los INT_MAX por -1.
    vector<int> dijkstra(int origen) const {
        (void)origen;   // evita un aviso; bórrala al empezar
        return {}; // TODO
    }
};

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

// El grafo de la lección: 6 vértices y 6 aristas.
Grafo grafoDeLaLeccion() {
    Grafo g(6);
    g.agregarArista(0, 2);
    g.agregarArista(0, 1);
    g.agregarArista(1, 3);
    g.agregarArista(2, 4);
    g.agregarArista(3, 4);
    g.agregarArista(3, 5);
    return g;
}

int main() {
    Grafo g = grafoDeLaLeccion();

    cout << "BFS:\n";
    comprobar(g.bfs(0) == vector<int>{0, 2, 1, 4, 3, 5}, "bfs(0) visita 0 2 1 4 3 5 (por capas)");
    comprobar(g.bfs(5) == vector<int>{5, 3, 1, 4, 0, 2}, "bfs(5) visita 5 3 1 4 0 2");

    cout << "DFS:\n";
    comprobar(g.dfs(0) == vector<int>{0, 2, 4, 3, 1, 5}, "dfs(0) visita 0 2 4 3 1 5 (en profundidad)");
    {
        Grafo solo(1);
        comprobar(solo.dfs(0) == vector<int>{0} && solo.bfs(0) == vector<int>{0},
                  "un grafo de un vértice: bfs y dfs devuelven solo {0}");
    }

    cout << "Camino más corto:\n";
    comprobar(g.caminoMasCorto(0, 5) == vector<int>{0, 1, 3, 5}, "de 0 a 5: 0 1 3 5 (3 aristas)");
    comprobar(g.caminoMasCorto(4, 4) == vector<int>{4}, "de 4 a 4: el camino es solo {4}");
    {
        Grafo dos(4);
        dos.agregarArista(0, 1);
        dos.agregarArista(2, 3);
        comprobar(dos.caminoMasCorto(0, 3).empty(), "si no hay camino, devuelve un vector vacío");
        comprobar(dos.componentes() == 2 && g.componentes() == 1,
                  "componentes: 2 islas en {0-1, 2-3}; 1 en el grafo de la lección");
    }
    {
        Grafo d(3, true);   // dirigido: 0 -> 1 -> 2
        d.agregarArista(0, 1);
        d.agregarArista(1, 2);
        comprobar(d.caminoMasCorto(0, 2) == vector<int>{0, 1, 2} && d.caminoMasCorto(2, 0).empty(),
                  "dirigido: de 0 a 2 sí hay camino; de 2 a 0 no");
    }

    cout << "Dijkstra:\n";
    {
        GrafoPonderado p(5);
        p.agregarArista(0, 1, 4);
        p.agregarArista(0, 2, 1);
        p.agregarArista(2, 1, 2);
        p.agregarArista(1, 3, 1);
        p.agregarArista(2, 3, 5);
        p.agregarArista(3, 4, 3);
        comprobar(p.dijkstra(0) == vector<int>{0, 3, 1, 4, 7},
                  "dijkstra(0) = 0 3 1 4 7 (a 1 se llega mejor por 2: 1+2 < 4)");
        GrafoPonderado q(3);
        q.agregarArista(0, 1, 5);
        comprobar(q.dijkstra(0) == vector<int>{0, 5, -1}, "un vértice inalcanzable da -1");
    }

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 5.7 terminado. ¡Nivel 5 completo!\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
