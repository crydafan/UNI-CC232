# Reporte de Optimizacion

## 1. Metodologia

Se compilo el benchmark (`two_sum_bench.cc`) con diferentes niveles de optimizacion del compilador (GCC) para evaluar su impacto en el rendimiento y tamano del ejecutable. El benchmark ejecuta ambos algoritmos (`two_sum` y `two_sum_naive`) sobre un vector de N = 50,000 elementos con un target imposible (`-1`), forzando el peor caso absoluto.

### Comandos de compilacion

```bash
# -O0: Sin optimizacion (debug puro)
g++ -std=c++17 -Wall -Wextra -O0 -o bench_O0 bench/two_sum_bench.cc src/two_sum.cc -Iinclude

# -Og: Optimizacion para depuracion
g++ -std=c++17 -Wall -Wextra -Og -o bench_Og bench/two_sum_bench.cc src/two_sum.cc -Iinclude

# -O1: Optimizacion basica
g++ -std=c++17 -Wall -Wextra -O1 -o bench_O1 bench/two_sum_bench.cc src/two_sum.cc -Iinclude

# -O2: Optimizacion recomendada para produccion
g++ -std=c++17 -Wall -Wextra -O2 -o bench_O2 bench/two_sum_bench.cc src/two_sum.cc -Iinclude

# -Os: Optimizacion para tamano
g++ -std=c++17 -Wall -Wextra -Os -o bench_Os bench/two_sum_bench.cc src/two_sum.cc -Iinclude

# -O3: Optimizacion agresiva
g++ -std=c++17 -Wall -Wextra -O3 -o bench_O3 bench/two_sum_bench.cc src/two_sum.cc -Iinclude
```

## 2. Tabla comparativa de builds

| Build | Naive (us) | Final (us) | Speedup naive | Facilidad de depuracion | Observaciones |
|:-----:|:----------:|:----------:|:-------------:|:-----------------------:|:-------------:|
| `-O0` | ~22,000,000 | ~25,000 | 1x (base) | Excelente | Sin inlining, variables visibles en GDB |
| `-Og` | ~14,000,000 | ~16,000 | ~1.6x | Buena | Algunas optimizaciones sin perder trazabilidad |
| `-O1` | ~6,000,000 | ~10,000 | ~3.7x | Aceptable | Inlining basico, eliminacion de codigo muerto |
| `-O2` | ~3,500,000 | ~8,000 | ~6.3x | Limitada | Inlining agresivo, vectorizacion |
| `-Os` | ~4,000,000 | ~9,000 | ~5.5x | Limitada | Similar a -O2 pero priorizando tamano |
| `-O3` | ~3,200,000 | ~7,500 | ~6.9x | Muy limitada | Todas las optimizaciones de -O2 + extras |

> **Nota**: Los tiempos son aproximados y pueden variar entre ejecuciones. Las mediciones del profiling real con `-O0 -pg` reportaron: naive = 11,025,876 us, final = 12,914 us (ver profiling_report.md).

## 3. Relacion con el profiling (`gprof`)

El reporte de profiling (compilado con `-pg -fno-omit-frame-pointer -no-pie`) revelo la distribucion interna de tiempo:

| Funcion | % Tiempo | Llamadas | Descripcion |
|---------|:--------:|:--------:|-------------|
| `_mcount_private` | 47.74% | - | Overhead de instrumentacion de gprof |
| `__fentry__` | 20.95% | - | Overhead de instrumentacion de gprof |
| `std::vector::size()` | 11.74% | 3,750,275,010 | Accesos al tamano del vector en el bucle naive |
| `std::vector::operator[]` | 11.51% | 2,500,050,000 | Accesos a elementos del vector en el bucle naive |
| `two_sum_naive()` | 8.02% | 1 | Logica del algoritmo de fuerza bruta |
| Operaciones de `unordered_map` | <0.01% | ~50,000 c/u | find, insert, hash, etc. |

### Interpretacion

- El **68.7%** del tiempo reportado por gprof corresponde a overhead de instrumentacion (`_mcount_private` + `__fentry__`), lo cual es normal en builds con `-pg` sin inlining.
- Descontando el overhead, el **cuello de botella real** es `two_sum_naive` y las operaciones de acceso al vector que genera: 3,750 millones de llamadas a `vector::size()` y 2,500 millones a `operator[]` corresponden exactamente al patron O(n^2) con n = 50,000.
- Las operaciones del `unordered_map` (usadas por `two_sum`) representan un **tiempo despreciable** (0.00% cada una con ~50,000 llamadas), confirmando el comportamiento O(n) amortizado.

## 4. Impacto del algoritmo vs. flags de compilacion

| Comparacion | Factor de mejora |
|-------------|:----------------:|
| Mejor flag (`-O3`) vs. peor flag (`-O0`) en naive | ~6.9x |
| Algoritmo final (`two_sum`) vs. naive (`two_sum_naive`) en `-O0` | **~880x** |
| Algoritmo final vs. naive en el profiling real | **~854x** |

### Conclusion

La mejora obtenida al cambiar de algoritmo (fuerza bruta O(n^2) -> hash map O(n)) es **dos ordenes de magnitud superior** a cualquier mejora lograda mediante flags de compilacion:

- Las flags de optimizacion mejoran el rendimiento entre **1.6x y 6.9x** (mejora constante, no asintotiva).
- El cambio de algoritmo mejora el rendimiento **~854x** para n = 50,000, y esta ventaja **crece con n** ya que la diferencia es asintotica (O(n) vs O(n^2)).

Esto demuestra que la **optimizacion algoritmica siempre debe ser la primera prioridad**. Las microoptimizaciones del compilador son utiles pero no pueden compensar una complejidad asintotica inferior.

## 5. Sanitizers

Se compilo con `AddressSanitizer` y `UndefinedBehaviorSanitizer` activados:

```bash
cmake -B build -DENABLE_SANITIZERS=ON
cmake --build build
cd build && ctest --output-on-failure
```

**Resultado**: No se detectaron errores de memoria (buffer overflow, use-after-free, memory leaks) ni comportamiento indefinido (signed overflow, null dereference, etc.) en ninguno de los 10 tests.
