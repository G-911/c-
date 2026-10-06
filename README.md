# Curso de C++: desde cero hasta intermedio-avanzado

32 lecciones cortas, en español, organizadas en 4 niveles. Cada lección trae:

- teoría breve con ejemplos y diagramas,
- una sección **«¿Qué pasa en la memoria?»** que enlaza al [mapa de la memoria](reference/memoria.html),
- un quiz que se corrige al pulsar,
- un **miniproyecto** en C++ que se corrige solo al compilarlo (✓ / ✗), con su solución aparte.

## Cómo empezar

Abre `index.html` en el navegador. Ahí está el temario completo, en orden.

Para hacer un miniproyecto:

```bash
cd nivel-1-fundamentos/ejercicios
g++ -std=c++17 -Wall 01-primer-programa.cpp -o prog && ./prog
```

Terminaste cuando todas las pruebas salen con ✓. Si te atascas, la solución está en la carpeta
`soluciones/` del mismo nivel. Ábrela solo después de intentarlo de verdad.

## Estructura

| Carpeta | Contenido |
|---|---|
| `nivel-1-fundamentos/` | primer programa, variables, operadores, condicionales, bucles, funciones, arreglos, vector |
| `nivel-2-memoria-y-poo/` | referencias, apuntadores, memoria dinámica, clases, herencia, polimorfismo, operadores |
| `nivel-3-estructuras-de-datos/` | recursión, listas enlazadas (simple, doble, circular), copia, pila, cola, complejidad, STL |
| `nivel-4-intermedio-avanzado/` | plantillas, contenedores, algoritmos y lambdas, excepciones, apuntadores inteligentes, archivos y proyectos, movimiento, panorama |
| `reference/` | hojas de consulta rápida |
| `assets/` | estilo y quiz compartidos |

Cada nivel tiene `NN-tema.html` (la lección), `ejercicios/` y `soluciones/`.

**Ruta corta para el examen** (apuntadores, listas, pilas y colas): 2.2 → 2.3 → 2.4 → 3.2 → 3.3 → 3.6 → 3.7.

## Requisitos

Un compilador de C++17: `g++` en Linux (`sudo apt install g++`). En Windows, MSYS2 o WSL
(se explica en la lección 1.1).

## Fuentes

[LearnCpp.com](https://www.learncpp.com/) y [cppreference.com](https://en.cppreference.com/),
citadas lección por lección.
