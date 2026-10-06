// SOLUCIÓN — Miniproyecto 1.7 — Arreglos y strings
// ---------------------------------------------------------------
// Ábrela solo después de intentarlo de verdad.
//
// Compilar y probar (dentro de la carpeta soluciones):
//   g++ -std=c++17 -Wall 07-arreglos-y-strings.cpp -o prog && ./prog
// ---------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

// 1) Suma de todos los elementos.
int sumaArreglo(int arr[], int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma += arr[i];
    }
    return suma;
}

// 2) Posición de la PRIMERA aparición de buscado, o -1 si no está.
int indiceDe(int arr[], int n, int buscado) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == buscado) return i;   // en cuanto lo encuentra, sale
    }
    return -1;                             // dio la vuelta entera: no estaba
}

// 3) Da la vuelta al arreglo, en su sitio.
void invertir(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {      // solo hasta la mitad
        int aux = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = aux;
    }
}

// 4) Cuántas vocales (a e i o u, mayúsculas o minúsculas) tiene el texto.
int contarVocales(string texto) {
    string vocales = "aeiouAEIOU";
    int cuenta = 0;
    for (size_t i = 0; i < texto.size(); i++) {
        if (vocales.find(texto[i]) != string::npos) {
            cuenta++;
        }
    }
    return cuenta;
}

// 5) ¿Se lee igual al derecho y al revés?
bool esPalindromo(string texto) {
    int n = static_cast<int>(texto.size());
    for (int i = 0; i < n / 2; i++) {
        if (texto[i] != texto[n - 1 - i]) return false;
    }
    return true;
}

// 6) La primera palabra de una frase (hasta el primer espacio).
string primeraPalabra(string frase) {
    size_t espacio = frase.find(' ');
    if (espacio == string::npos) return frase;   // no hay espacio: es una sola palabra
    return frase.substr(0, espacio);
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
