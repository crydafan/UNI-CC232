# actividad1_semana1

Integrantes:

- Enrique Alejandro Paul Flores
- Leonardo Gabriel Estacio Huaricapcha

## Bloque 0

1. Un _problema_ es cuestion que se trata de aclarar. Un _algoritmo_ es un conjunto finito de operaciones que permite la solucion de un problema. Un _ADT_ es un modelo conceptual, una interfaz que define el comportamiento de un algoritmo: ya sea los datos en los que trabaja o las funciones que expone. Una _implementacion_ de una _intefaz_ es el codigo que respeta el comportamiento de la interfaz, es mas especifico porque puede hacer uso de instrucciones o funcionalidades especificas, por ejemplo `ArrayList` y `LinkedList` en Java.
2. La variable `changed` determina si es que hubo una permutacion o no, si es que no hubo un permutacion quiere decir que el arreglo ya esta ordenado, por lo tanto el bucle para en el momento que `changed` sea falso.
3. A diferencia de la version ingenua, la version optimizada divide la exponenciacion en suboperaciones que se encargar de aplicar la potencia con exponentes pares.
4. Por ejemplo, la version ingenua de fibonacci hace uso de la recursion que tiene una complejidad temporal mayor, ademas que en ciertos entornos puede incurrir en errores como un _stack overflow_.
5. `unsigned int` tiene un tamano de 32 bits pero el valor de `n` puede ser mucho menor. Por ejemplo para `n = 7` que tiene valor numero 7 pero ocupa 32 bits en memoria
6. Una interfaz actua como un contrato que define una lista de metodos y propiedades de una clase sin especificar como se implementa.

## Bloque 2

| Archivo | Salida / Observable | Idea algoritmica | Argumento costo |
| ------- | ------------------- | ---------------- | --------------- |
| `demo_bubblesort.cpp` | Arreglo ordenado | Intercambiar pares adyacentes del arreglo hasta llegar a un orden global | La complejidad temporal es de `O(n^2)` al haber `n` comparaciones para `n` elementos del arreglo. |
| `demo_power.cpp` | Potencia del numero en base al exponente | Dividir la potencia en suboperaciones donde el exponente sea un numero par | El costo de `powerBF` es `O(n)` donde `n` es el exponente, mientras que `power` reduce el costo a `O(log n)` al dividir el exponente a la mitad en cada iteracion. |
| `demo_fibonacci.cpp` | Numero de Fibonacci en la posicion `n` | La version iterativa `fibI` usa dos variables acumuladoras que avanzan de forma lineal, evitando la recomputacion que ocurre en la version recursiva ingenua | La version iterativa tiene complejidad `O(n)`, mientras que la version recursiva ingenua `fib` tiene complejidad `O(2^n)` por las llamadas redundantes. |
| `demo_countones.cpp` | Cantidad de bits en 1 de un entero sin signo | `countOnes1` elimina el bit 1 menos significativo con `n &= (n - 1)` en cada iteracion, `countOnes2` agrupa y suma bits por bloques usando mascaras | `countOnes1` tiene complejidad `O(k)` donde `k` es la cantidad de bits en 1, mientras que `countOnes2` tiene complejidad `O(log w)` donde `w` es el ancho de palabra (32 bits). |

1. La salida de comparaciones e intercambios sirve para defender costo, porque muestra cuantas operaciones reales se necesitaron para ordenar, no solo que el arreglo quedo ordenado.
2. La comparacion entre `powerBF` y `power` con el mismo exponente muestra la mejora algoritmica: ambas producen el mismo resultado pero `power` lo hace en menos pasos al aprovechar la division del exponente por 2.
3. El crecimiento lineal de `fibI` se vuelve defendible frente al crecimiento exponencial de `fib`, donde para valores cada vez mayores de `n` la version recursiva se vuelve practicamente inviable mientras la iterativa se mantiene rapida.
4. Por ejemplo para el valor numerico 7, es mucho menor al tamano de `unsigned int` (32 bits), sin embargo el numero de bits en 1 que contiene (3 bits) es lo que determina el costo de `countOnes1`, demostrando que el tamano de la entrada en bits no coincide con el valor numerico.

## Bloque 3

1. Estan verificando que las implementaciones de las funciones retornen un resultado conforme a lo esperado.
2. Una prueba publica demuestra que una implementacion respete el comportamiento que define una interfaz.
3. Una prueba publica no demuestra, por ejemplo, la complejidad temporal de un algoritmo, puesto que eso ya es especifico de cada implementacion.
4. Una especificacion o intefaz define el comportamiento de un algoritmo, mientras que una implementacion materializa la interfaz en codigo funcional, respetando el comportamiento definido por la interfaz.
5. Autoevaluacion:
   - Comprension conceptual: **En proceso** - reconocemos las diferencias entre problema, algoritmo, ADT e implementacion, pero aun nos cuesta articular con precision formal las definiciones.
   - Sustentacion de correctitud: **En proceso** - podemos dar intuiciones sobre por que funcionan los algoritmos (caso base, progreso, invariante), pero falta formalizarlas con mayor rigor.
   - Analisis de eficiencia: **En proceso** - identificamos que unas versiones son mas rapidas que otras y usamos notacion asintotica basica, pero aun nos falta justificar el costo con mayor detalle en algunos casos.

## Bloque 4

1. `demo_const_refs.cpp` muestra que la lectura con referencia constante (`sum_readonly`) no modifica el vector original, la modificacion in-place (`append_in_place`) altera directamente el vector, y la copia (`appended_copy`) genera un vector nuevo sin afectar al original. La diferencia observable es que tras `append_in_place` el original cambia, pero tras `appended_copy` el original permanece igual.
2. Con `reserve` se elimina la necesidad de realocaciones durante el crecimiento del vector, lo que reduce el tiempo total de insercion. Sin `reserve`, el vector debe copiar todos sus elementos a una nueva region de memoria cada vez que se queda sin capacidad.
3. `push_back` al final es `O(1)` amortizado porque no necesita desplazar elementos. `insert(begin())` es `O(n)` porque debe desplazar todos los elementos existentes una posicion hacia la derecha. `insert(middle)` es `O(n/2)` en promedio porque desplaza la mitad de los elementos. El costo depende de cuantos elementos deben moverse para hacer espacio.
4. El recorrido secuencial de un vector es significativamente mas rapido que el acceso aleatorio o el recorrido de una `std::list`, porque los elementos contiguos en memoria aprovechan la cache del procesador. Cuando se accede a posiciones aleatorias o se recorre una lista enlazada (nodos dispersos en memoria), se producen mas fallos de cache, lo que incrementa el tiempo de acceso.

## Bloque 5

1. Segun `Ejercicios0.md`, el orden correcto antes de optimizar es: primero elegir bien el algoritmo, luego verificar que el programa sea correcto, despues medir rendimiento, y finalmente explorar optimizaciones mas avanzadas del compilador. Es decir, `-O3` no reemplaza a una buena eleccion algoritmica.
2. `stl_optimizacion_demostracion.cpp` quiere mostrar que elegir el algoritmo correcto de la STL produce mejoras mas significativas que las micro-optimizaciones. `reserve` reduce realocaciones, `nth_element` encuentra la mediana en `O(n)` sin necesidad de ordenar todo el arreglo, `partial_sort` ordena solo los primeros K elementos en vez del arreglo completo, y `lower_bound` realiza busqueda binaria en `O(log n)` sobre un vector ordenado en vez de busqueda lineal.
3. `resolver_ejercicios0_v4.2.sh` puede producir evidencia experimental: tiempos de ejecucion con distintos niveles de optimizacion, tamanos de ejecutables, reportes de sanitizers sobre errores de memoria, reportes de cobertura de codigo con `gcov`, y perfiles de rendimiento con `gprof`. Es evidencia cuantitativa y medible, no argumentos conceptuales.
4. `INSTRUCCIONES_Ejercicios0_v4.2.md` menciona que en Windows con Git Bash o MSYS2 pueden haber limitaciones: `ASan`, `UBSan` o `TSan` pueden no enlazar correctamente, `gcov` puede requerir ajustes extra, y `gprof` puede fallar o no generar perfiles utiles. Recomienda usar WSL Ubuntu o Linux nativo para sanitizers, cobertura y profiling.
5. Esta parte no reemplaza la discusion de correctitud de Semana1 porque se enfoca en evidencia experimental y optimizacion de rendimiento, mientras que Semana1 se centra en justificar por que un algoritmo es correcto (finitud, invariantes, casos base). Medir que un programa corre rapido no demuestra que produce el resultado correcto, y que pase pruebas no demuestra su correctitud formal.

## Bloque 6

Cuando pasamos de defender correctitud basica en Semana1 a comparar implementaciones con evidencia experimental, cambia el tipo de afirmacion que podemos hacer y la forma en que la sustentamos:

- **Especificacion**: la interfaz define que debe hacer el algoritmo (por ejemplo, ordenar un arreglo o calcular una potencia), y eso no cambia entre implementaciones. Lo que cambia es como se implementa.
- **Correctitud**: en Semana1 defendemos que el algoritmo termina y produce el resultado correcto usando argumentos como caso base, progreso e invariantes. Al comparar implementaciones, ambas deben ser correctas antes de poder compararlas.
- **Costo**: al pasar a evidencia experimental, podemos medir y comparar cuantas operaciones o cuanto tiempo consume cada implementacion. Por ejemplo, `power` en `O(log n)` frente a `powerBF` en `O(n)`, o `fibI` en `O(n)` frente a `fib` en `O(2^n)`.
- **Representacion o memoria**: la estructura de datos elegida afecta el rendimiento. Un vector con elementos contiguos aprovecha la cache del procesador, mientras que una lista enlazada dispersa los nodos en memoria. `reserve` evita realocaciones innecesarias que consumen tiempo y memoria.
- **Advertencia metodologica**: la evidencia experimental depende del entorno (compilador, sistema operativo, hardware, nivel de optimizacion). Los tiempos pueden variar entre ejecuciones, y medir mal puede llevar a conclusiones incorrectas. Un benchmark no reemplaza el analisis asintotico, y una prueba que pasa no demuestra correctitud formal.
