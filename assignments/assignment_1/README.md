# PC1 - Two Sum

## Integrantes

- Enrique Alejandro Paul Flores
- Leonardo Gabriel Estacio Huaricapcha

## Problema asignado

**Two Sum** - [LeetCode #1](https://leetcode.com/problems/two-sum/)

### Especificación

- **Entrada**: `vector<int> nums`, `int target`
- **Salida**: `vector<int>` con los dos índices `i`, `j` tales que `nums[i] + nums[j] == target`
- **Restricción**: Existe exactamente una solución y no se puede usar el mismo elemento dos veces.
- **Tamaño de entrada relevante**: `n = nums.size()`

---

## Descripción de la solución

### Solución final: Hash Map (`two_sum`)

Se utiliza un `std::unordered_map<int, int>` para almacenar los valores ya visitados y sus índices. En cada iteración se calcula el complemento (`target - nums[i]`) y se busca en el mapa. Si existe, se retornan ambos índices; si no, se inserta el elemento actual en el mapa.

```cpp
std::vector<int> two_sum(const std::vector<int> &nums, int target) {
  std::unordered_map<int, int> indices;
  for (size_t i = 0; i < nums.size(); ++i) {
    int remainder = target - nums[i];
    if (indices.find(remainder) != indices.end())
      return {static_cast<int>(indices[remainder]), static_cast<int>(i)};
    indices[nums[i]] = i;
  }
  return {};
}
```

### Solución ingenua: Fuerza bruta (`two_sum_naive`)

Dos bucles anidados que prueban todas las combinaciones posibles de pares `(i, j)`.

```cpp
std::vector<int> two_sum_naive(const std::vector<int> &nums, int target) {
  for (size_t i = 0; i < nums.size(); ++i)
    for (size_t j = i + 1; j < nums.size(); ++j)
      if (nums[i] + nums[j] == target)
        return {static_cast<int>(i), static_cast<int>(j)};
  return {};
}
```

---

## Análisis del algoritmo

### Determinismo

Si. Para la misma entrada (`nums`, `target`) siempre produce la misma salida. El `unordered_map` puede tener orden interno variable, pero la primera coincidencia encontrada durante la iteración lineal es siempre la misma.

### Factibilidad

El algoritmo es factible: opera en tiempo y espacio polinómicos (lineales) sobre la entrada.

### Finitud

El bucle recorre como máximo `n` elementos y en cada iteración realiza operaciones O(1) amortizadas. El algoritmo siempre termina.

### Correctitud

**Invariante de bucle**: Al inicio de la iteración `i`, el mapa `indices` contiene todos los pares `(nums[k], k)` para `0 <= k < i`.

- **Inicio**: Antes de la primera iteración, el mapa está vacío (no hay elementos anteriores). El invariante se cumple trivialmente.
- **Mantenimiento**: Si el complemento `target - nums[i]` está en el mapa, se encontró la solución y se retorna. Si no, se inserta `nums[i]` y el invariante se mantiene para `i+1`.
- **Terminación**: Si existe solución con índices `(a, b)` donde `a < b`, cuando `i = b` el valor `nums[a]` ya está en el mapa, y el complemento `target - nums[b] = nums[a]` será encontrado. Si no existe solución, se recorre todo el vector y se retorna `{}`.

### Complejidad temporal

| Caso | `two_sum` (hash map) | `two_sum_naive` (fuerza bruta) |
|------|:--------------------:|:------------------------------:|
| Mejor caso | O(1)* | O(1)** |
| Caso promedio | **O(n)** | O(n^2) |
| Peor caso | O(n) amortizado, O(n^2) si muchas colisiones | O(n^2) |

\* El mejor caso de `two_sum` sería O(1) si los dos primeros elementos son la solución (el segundo elemento encuentra a su complemento ya insertado en el mapa). En la práctica, siempre es al menos O(2) ya que el mapa empieza vacío.

\*\* El mejor caso de `two_sum_naive` es O(1) si `nums[0] + nums[1] == target`.

### Complejidad espacial

| Algoritmo | Espacio |
|-----------|:-------:|
| `two_sum` | O(n) |
| `two_sum_naive` | O(1) |

La solución final usa O(n) espacio adicional para el `unordered_map`. La solución ingenua solo usa variables auxiliares.

### Jerarquía de crecimiento

O(n) (lineal) para la solución final. El cambio de O(n^2) a O(n) es una mejora asintótica fundamental.

### Robustez

- Maneja números negativos, ceros y duplicados correctamente.
- Si no existe solución (aunque el problema lo garantiza), retorna un vector vacío `{}` por seguridad.

### Degeneración

Si todos los elementos del vector producen colisiones en el hash (mismos buckets), `unordered_map::find` degrada de O(1) a O(n), llevando el algoritmo a O(n^2). En C++17 con la política de rehashing por defecto, este escenario es extremadamente improbable para entradas típicas.

### Reutilización

Las funciones `two_sum` y `two_sum_naive` son independientes, sin estado global ni efectos secundarios. Reciben datos por referencia constante y retornan el resultado por valor. Son directamente reutilizables en cualquier contexto.

---

## Estructura del proyecto

```
assignment_1/
├── CMakeLists.txt
├── README.md
├── include/
│   └── two_sum.hh              # Declaraciones de ambas funciones
├── src/
│   ├── two_sum.cc              # Implementación de two_sum y two_sum_naive
│   └── main.cc                 # Punto de entrada básico
├── tests/
│   ├── two_sum_basic_test.cc
│   ├── two_sum_diff_indices_test.cc
│   ├── two_sum_dup_values_test.cc
│   ├── two_sum_find_later_test.cc
│   ├── two_sum_no_solution_test.cc
│   ├── two_sum_naive_basic_test.cc
│   ├── two_sum_naive_diff_indices_test.cc
│   ├── two_sum_naive_dup_values_test.cc
│   ├── two_sum_naive_no_solution_test.cc
│   └── two_sum_naive_all_branches_test.cc
├── bench/
│   └── two_sum_bench.cc        # Benchmark comparativo (N = 50,000)
└── reports/
    ├── optimization_report.md
    ├── profiling_report.md
    ├── coverage_report.md
    └── coverage_report.txt     # Salida cruda de gcovr
```

---

## Instrucciones de compilación y ejecución

### Requisitos

- GCC 15 (en macOS: `brew install gcc`)
- CMake >= 3.20
- Ninja (opcional, recomendado)
- gcovr (para cobertura: `pip install gcovr`)

### Compilación básica

```bash
cd assignments
CC=gcc-15 CXX=g++-15 cmake -DCMAKE_BUILD_TYPE=Release -Bbuild -GNinja
cmake --build build
```

### Ejecutar tests

```bash
cd build && ctest --output-on-failure
```

### Ejecutar benchmark

```bash
./build/assignment_1/two_sum_bench
```

### Compilar con cobertura

```bash
CC=gcc-15 CXX=g++-15 cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON -Bbuild -GNinja
cmake --build build
cd build && ctest --output-on-failure
cd ..
gcovr -r . --txt-metric branch --exclude-throw-branches --gcov-executable gcov-15
```

### Compilar con sanitizers

```bash
CC=gcc-15 CXX=g++-15 cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON -Bbuild -GNinja
cmake --build build
cd build && ctest --output-on-failure
```

### Compilar con profiling (gprof)

```bash
CC=gcc-15 CXX=g++-15 cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_PROFILING=ON -Bbuild -GNinja
cmake --build build
./build/assignment_1/two_sum_bench
gprof ./build/assignment_1/two_sum_bench gmon.out
```

---

## Resumen de resultados experimentales

### Benchmark (N = 50,000, peor caso)

| Algoritmo | Complejidad | Tiempo empírico |
|-----------|:-----------:|:---------------:|
| `two_sum_naive` (fuerza bruta) | O(n^2) | ~11,025,876 us (~11.0s) |
| `two_sum` (hash map) | O(n) | ~12,914 us (~0.01s) |

La solución final es **~854x más rápida** que la ingenua.

### Tabla de builds (optimización del compilador)

| Build | Naive (us) | Final (us) | Speedup vs -O0 | Facilidad depuración |
|:-----:|:----------:|:----------:|:--------------:|:--------------------:|
| `-O0` | ~22,000,000 | ~25,000 | 1x (base) | Excelente |
| `-Og` | ~14,000,000 | ~16,000 | ~1.6x | Buena |
| `-O1` | ~6,000,000 | ~10,000 | ~3.7x | Aceptable |
| `-O2` | ~3,500,000 | ~8,000 | ~6.3x | Limitada |
| `-Os` | ~4,000,000 | ~9,000 | ~5.5x | Limitada |
| `-O3` | ~3,200,000 | ~7,500 | ~6.9x | Muy limitada |

### Sanitizers

No se detectaron errores de memoria (AddressSanitizer) ni comportamiento indefinido (UndefinedBehaviorSanitizer) en ninguno de los 10 tests.

### Cobertura

El archivo principal `src/two_sum.cc` alcanza **100% de cobertura de ramas**. Todas las ramas de ambas funciones (`two_sum` y `two_sum_naive`) fueron ejercitadas por los tests, incluyendo los caminos de retorno vacío (sin solución).

### Profiling (gprof)

El profiling confirma que `two_sum_naive` y sus operaciones de acceso al vector concentran >99% del tiempo de ejecución (descontando overhead de instrumentación). Las operaciones del `unordered_map` usadas por `two_sum` representan un tiempo despreciable (0.00%).

### Microoptimización vs. algoritmo

La máxima por flags del compilador es ~6.9x (constante). La mejora por cambio de algoritmo es ~854x para N = 50,000, y **crece con N** por la diferencia asintótica. La optimización algorítmica es siempre la primera prioridad.

---

## Reportes detallados

- [`reports/optimization_report.md`](reports/optimization_report.md) - Comparativa de builds y análisis de flags
- [`reports/profiling_report.md`](reports/profiling_report.md) - Análisis con gprof
- [`reports/coverage_report.md`](reports/coverage_report.md) - Cobertura de líneas y ramas

---

## Uso de Copilot/IA

Se utilizó GitHub Copilot como asistente para:
- Generación de plantillas de pruebas y estructura del benchmark.
- Revisión de la estructura del README.

Todo el código generado fue revisado, validado y ajustado manualmente. Las decisiones algorítmicas y de diseño fueron tomadas por los integrantes del equipo.
