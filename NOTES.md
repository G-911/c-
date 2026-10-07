# Notas del profesor

- Idioma: español. Explicar simple, frases cortas, conclusión primero.
- Poco tiempo: lecciones cortas, un solo logro por lección, miniproyecto que se autocorrige al compilar.
- Temas de la universidad: apuntadores, listas, pilas, colas — con POO (clases).
- SUPUESTO (sin confirmar): ya sabe lo básico de C++ (variables, if, for, funciones, arreglos).
  Si no, añadir una lección 0 de repaso.
- Pendiente preguntar: fecha del examen y si el profesor exige `struct` o `class`, o plantillas.
- Compilador disponible: g++ 15. Compilar con: g++ -std=c++17 -Wall archivo.cpp -o prog && ./prog
## 2026-10-06
- Pidió TODAS las lecciones de una vez para estudiar a su ritmo, sin esperar a terminar cada una.
  Por eso cada lección es autosuficiente: calentamiento con el quiz anterior (repaso espaciado),
  y solución en `soluciones/` para cuando estudia solo y se atasca.
- Convenciones de nombres fijadas para todo el curso (Nodo/dato/siguiente, ListaEnlazada/cabeza,
  Pila/tope/push/pop/top, Cola/frente/final/encolar/desencolar/verFrente). Respetarlas en lo que se añada.

## 2026-10-07
- Pidió llegar a nivel AVANZADO: se añadieron el Nivel 5 (estructuras de datos II, 7 lecciones) y el
  Nivel 6 (avanzado, 9 lecciones). Curso total: 48 lecciones, 25 hojas de referencia.
- Pidió explícitamente usar la extensión /teach para esto (solo la puede activar él).
- Convenciones nuevas: NodoArbol/ArbolBusqueda/raiz (altura cuenta NODOS: vacío 0, hoja 1),
  NodoAVL/ArbolAVL, Monticulo, TablaHash, Grafo. «Montículo» (estructura) ≠ «montón» (memoria).
- El Nivel 6 compila con el estándar MÍNIMO que necesita cada lección (C++17/20/23, -pthread);
  el comando está en la cabecera de cada ejercicio. El ejercicio 6.8 vacío NO se compila con -O2
  (el UB lo hace entrar en bucle; está documentado a propósito).
- Herramientas en esta máquina: g++ 15.2, cmake, gdb, gprof. NO: valgrind, clang-tidy, perf (sin permisos).
- Sigue sin haber evidencia de lo aprendido: cuando haga ejercicios o pregunte, escribir learning-records.
- Primer intento propio (2026-10-06, proyectos-practica/01_iniciar/hola.cpp): `#include` sin
  `<iostream>` y `cout >> "..."` en vez de `<<`. Son los dos errores de la lección 1.1: reforzar
  «<< empuja hacia cout» y leer el error del compilador. Aún no hay evidencia de que lo corrigiera.
