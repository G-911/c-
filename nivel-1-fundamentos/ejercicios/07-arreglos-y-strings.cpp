// Miniproyecto 1.7 — Arreglos y strings
// ---------------------------------------------------------------
// Completa las SEIS funciones marcadas con TODO. No toques main().
//
// Las líneas (void)x; solo callan un aviso del compilador mientras
// no usas ese parámetro. Bórralas cuando escribas tu código.
//
// Compilar y probar (en la terminal, dentro de esta carpeta):
//   g++ -std=c++17 -Wall 07-arreglos-y-strings.cpp -o prog && ./prog
//
// Cuando todo salga con ✓, terminaste.
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// 1) Suma de todos los elementos del arreglo (tiene n elementos).
//    Pista: for (int i = 0; i < n; i++) y un acumulador.
int sumaArreglo(int arr[], int n) {
    (void)arr; (void)n;
    // TODO
    return 0;
}

// 2) Posición de la PRIMERA vez que aparece buscado, o -1 si no está.
//    Pista: en cuanto lo encuentres, return i. Si el bucle termina
//    sin encontrarlo, entonces sí: return -1.
int indiceDe(int arr[], int n, int buscado) {
    (void)arr; (void)n; (void)buscado;
    // TODO
    return 0;
}

// 3) Da la vuelta al arreglo, en su sitio: {1,2,3} queda {3,2,1}.
//    Los cambios se ven fuera de la función (los arreglos no se copian).
//    Pista: intercambia arr[i] con arr[n - 1 - i], pero solo hasta
//    la mitad (i < n / 2). Si llegas al final, lo vuelves a dejar igual.
void invertir(int arr[], int n) {
    (void)arr; (void)n;
    // TODO
}

// 4) Cuántas vocales (a e i o u, mayúsculas o minúsculas) tiene el texto.
//    Sin tildes, para no complicarnos.
//    Pista: string vocales = "aeiouAEIOU"; y para cada letra pregunta
//    vocales.find(texto[i]) != string::npos  (o sea: "¿la encontró?").
int contarVocales(string texto) {
    (void)texto;
    // TODO
    return 0;
}

// 5) ¿Se lee igual al derecho y al revés?  "reconocer" sí, "casa" no.
//    Pista: compara texto[i] con texto[n - 1 - i] hasta la mitad.
//    Para no mezclar tipos: int n = static_cast<int>(texto.size());
bool esPalindromo(string texto) {
    (void)texto;
    // TODO
    return false;
}

// 6) La primera palabra de una frase: todo lo que hay antes del
//    primer espacio. Si no hay espacio, la frase entera.
//    Pista: frase.find(' ') te da la posición del espacio (o
//    string::npos si no hay); luego frase.substr(0, posicion).
string primeraPalabra(string frase) {
    (void)frase;
    // TODO
    return "";
}

// ----------------- Pruebas automáticas (no tocar) -----------------
int fallos = 0;
void comprobar(bool ok, const char* que) {
    cout << (ok ? "  ✓ " : "  ✗ ") << que << "\n";
    if (!ok) fallos++;
}

int main() {
    int datos[] = {4, 8, 15, 16, 23, 42};
    int n = 6;

    cout << "sumaArreglo:\n";
    comprobar(sumaArreglo(datos, n) == 108, "4+8+15+16+23+42 = 108");
    comprobar(sumaArreglo(datos, 0) == 0, "con n = 0 la suma es 0");

    cout << "indiceDe:\n";
    comprobar(indiceDe(datos, n, 4) == 0, "el 4 está en la posición 0");
    comprobar(indiceDe(datos, n, 42) == 5, "el 42 está en la última posición (5)");
    comprobar(indiceDe(datos, n, 7) == -1, "el 7 no está: devuelve -1");
    int repetidos[] = {3, 9, 3};
    comprobar(indiceDe(repetidos, 3, 3) == 0, "si se repite, devuelve la PRIMERA posición");

    cout << "invertir:\n";
    int a[] = {1, 2, 3, 4, 5};
    invertir(a, 5);
    comprobar(a[0] == 5 && a[1] == 4 && a[2] == 3 && a[3] == 2 && a[4] == 1, "{1,2,3,4,5} -> {5,4,3,2,1}");
    int b[] = {7, 9};
    invertir(b, 2);
    comprobar(b[0] == 9 && b[1] == 7, "{7,9} -> {9,7} (cantidad par)");

    cout << "contarVocales:\n";
    comprobar(contarVocales("murcielago") == 5, "\"murcielago\" tiene 5 vocales");
    comprobar(contarVocales("HOLA mundo") == 4, "cuenta mayúsculas: \"HOLA mundo\" tiene 4");
    comprobar(contarVocales("") == 0, "el texto vacío tiene 0");

    cout << "esPalindromo:\n";
    comprobar(esPalindromo("reconocer") && esPalindromo("anna"), "\"reconocer\" y \"anna\" sí lo son");
    comprobar(!esPalindromo("casa"), "\"casa\" no lo es");
    comprobar(esPalindromo(""), "el texto vacío cuenta como palíndromo");

    cout << "primeraPalabra:\n";
    comprobar(primeraPalabra("hola mundo cruel") == "hola", "\"hola mundo cruel\" -> \"hola\"");
    comprobar(primeraPalabra("solita") == "solita", "sin espacios devuelve la frase entera");

    cout << (fallos == 0 ? "\n¡Todo bien! Miniproyecto 1.7 terminado.\n"
                         : "\nAún hay fallos. Revisa las funciones con ✗.\n");
    return fallos == 0 ? 0 : 1;
}
