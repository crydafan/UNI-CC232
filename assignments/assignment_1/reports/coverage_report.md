# Reporte de Cobertura de Codigo

## 1. Compilacion con cobertura

En macOS se requiere usar GCC explicitamente (ya que `clang` no es compatible con `gcov`). Se utilizo CMake con la opcion `ENABLE_COVERAGE` activada, especificando `gcc-15`/`g++-15` y el generador Ninja:

```bash
CC=gcc-15 CXX=g++-15 cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON -Bbuild -GNinja
cmake --build build
```

Esto agrega las flags `--coverage -fprofile-arcs -ftest-coverage` al compilador. Durante la compilacion se generan archivos `.gcno`, y al ejecutar los tests se generan archivos `.gcda` con los datos de ejecucion.

## 2. Ejecucion de pruebas

```bash
cd build && ctest --output-on-failure
```

Se ejecutaron 10 tests en total:

| Test | Funcion evaluada | Caso |
|------|-----------------|------|
| `two_sum_basic_test` | `two_sum` | Caso base: `{2,7,11,15}`, target=9 |
| `two_sum_diff_indices_test` | `two_sum` | Indices no consecutivos |
| `two_sum_dup_values_test` | `two_sum` | Valores duplicados |
| `two_sum_find_later_test` | `two_sum` | Complemento encontrado al final |
| `two_sum_no_solution_test` | `two_sum` | Sin solucion (retorna `{}`) |
| `two_sum_naive_basic_test` | `two_sum_naive` | Caso base |
| `two_sum_naive_diff_indices_test` | `two_sum_naive` | Indices no consecutivos |
| `two_sum_naive_dup_values_test` | `two_sum_naive` | Valores duplicados |
| `two_sum_naive_no_solution_test` | `two_sum_naive` | Sin solucion (retorna `{}`) |
| `two_sum_naive_all_branches_test` | `two_sum_naive` | Cobertura de ramas adicional |

## 3. Generacion del reporte

Se utilizo `gcovr` con la metrica de branches, excluyendo ramas generadas por excepciones (throw branches) y especificando el ejecutable `gcov-15` para compatibilidad con GCC 15 en macOS:

```bash
gcovr -r . --txt-metric branch --exclude-throw-branches --gcov-executable gcov-15
```

La flag `--exclude-throw-branches` es clave: excluye las ramas que el compilador genera internamente para el manejo de excepciones (destructores, unwinding de stack, etc.), que no son parte de la logica del programa y distorsionan la metrica de cobertura.

## 4. Resultados de cobertura

### Cobertura de ramas (branch coverage) del codigo fuente

| Archivo | Cobertura de ramas |
|---------|:------------------:|
| `src/two_sum.cc` | **100%** |

Se alcanzo **100% de cobertura de ramas** en el archivo principal `two_sum.cc`. Esto significa que todas las ramas de la logica algoritmica fueron ejercitadas por los tests:

- **`two_sum`**: Se cubrio el camino donde se encuentra el complemento en el `unordered_map` (retorno temprano con los indices) y el camino donde se recorre el vector completo sin encontrar solucion (retorno de vector vacio `{}`).
- **`two_sum_naive`**: Se cubrio el camino donde `nums[i] + nums[j] == target` (retorno temprano) y el camino donde se agotan ambos bucles sin encontrar solucion (retorno de `{}`).

### Detalle de ramas cubiertas en `two_sum.cc`

| Funcion | Rama | Cubierta |
|---------|------|:--------:|
| `two_sum` | `i < nums.size()` (true: itera, false: sale del for) | Si |
| `two_sum` | `indices.find(remainder) != indices.end()` (true: encontrado) | Si |
| `two_sum` | `indices.find(remainder) != indices.end()` (false: no encontrado) | Si |
| `two_sum` | `return {}` (sin solucion) | Si |
| `two_sum_naive` | `i < nums.size()` (true/false) | Si |
| `two_sum_naive` | `j < nums.size()` (true/false) | Si |
| `two_sum_naive` | `nums[i] + nums[j] == target` (true: encontrado) | Si |
| `two_sum_naive` | `nums[i] + nums[j] == target` (false: continua) | Si |
| `two_sum_naive` | `return {}` (sin solucion) | Si |

## 5. Por que inicialmente se reportaba menos del 100%

Sin la flag `--exclude-throw-branches`, `gcovr` reportaba coberturas de 62-75% en los archivos de test. Esto se debia a:

1. **Ramas de fallo de `assert()`**: El compilador genera una rama para el caso `true` (continua) y otra para `false` (aborta). Como los tests pasan, la rama de fallo nunca se ejecuta.
2. **Ramas de excepciones (throw branches)**: GCC genera ramas implicitas para el manejo de excepciones en destructores y operaciones de la STL. Estas ramas no representan logica del programa.

Ambas son ramas artificiales del compilador, no de la logica del programador. La flag `--exclude-throw-branches` las filtra correctamente.

## 6. Reflexion

- El codigo bajo prueba (`two_sum.cc`) alcanza el **100% de cobertura de ramas**, lo cual confirma que los tests ejercitan todos los caminos posibles del algoritmo.
- El test `two_sum_no_solution_test` y `two_sum_naive_no_solution_test` son fundamentales para cubrir las ramas del `return {}` al final de cada funcion, que representan el caso donde no existe solucion.
- En macOS es necesario usar `gcc-15`/`g++-15` explicitamente y `gcov-15` como ejecutable de gcov, ya que el `gcc` por defecto es un alias de `clang` que no genera archivos `.gcno`/`.gcda` compatibles.
- La exclusion de throw branches (`--exclude-throw-branches`) es una practica recomendada para obtener metricas de cobertura que reflejen la logica real del programa y no artefactos del compilador.
