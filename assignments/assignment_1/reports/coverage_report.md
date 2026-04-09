# Reporte de Cobertura de Código

## 1. Compilación con cobertura

En macOS se requiere usar GCC explícitamente (ya que `clang` no es compatible con `gcov`). Se utilizó CMake con la opción `ENABLE_COVERAGE` activada, especificando `gcc-15`/`g++-15` y el generador Ninja:

```bash
CC=gcc-15 CXX=g++-15 cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON -Bbuild -GNinja
cmake --build build
```

Esto agrega las flags `--coverage -fprofile-arcs -ftest-coverage` al compilador. Durante la compilación se generan archivos `.gcno`, y al ejecutar los tests se generan archivos `.gcda` con los datos de ejecución.

## 2. Ejecución de pruebas

```bash
cd build && ctest --output-on-failure
```

Se ejecutaron 10 tests en total:

| Test | Función evaluada | Caso |
|------|-----------------|------|
| `two_sum_basic_test` | `two_sum` | Caso base: `{2,7,11,15}`, target=9 |
| `two_sum_diff_indices_test` | `two_sum` | Índices no consecutivos |
| `two_sum_dup_values_test` | `two_sum` | Valores duplicados |
| `two_sum_find_later_test` | `two_sum` | Complemento encontrado al final |
| `two_sum_no_solution_test` | `two_sum` | Sin solución (retorna `{}`) |
| `two_sum_naive_basic_test` | `two_sum_naive` | Caso base |
| `two_sum_naive_diff_indices_test` | `two_sum_naive` | Índices no consecutivos |
| `two_sum_naive_dup_values_test` | `two_sum_naive` | Valores duplicados |
| `two_sum_naive_no_solution_test` | `two_sum_naive` | Sin solución (retorna `{}`) |
| `two_sum_naive_all_branches_test` | `two_sum_naive` | Cobertura de ramas adicional |

## 3. Generación del reporte

Se utilizó `gcovr` con la métrica de branches, excluyendo ramas generadas por excepciones (throw branches) y especificando el ejecutable `gcov-15` para compatibilidad con GCC 15 en macOS:

```bash
gcovr -r . --txt-metric branch --exclude-throw-branches --gcov-executable gcov-15
```

La flag `--exclude-throw-branches` es clave: excluye las ramas que el compilador genera internamente para el manejo de excepciones (destructores, unwinding de stack, etc.), que no son parte de la lógica del programa y distorsionan la métrica de cobertura.

## 4. Resultados de cobertura

### Cobertura de ramas (branch coverage) del código fuente

| Archivo | Cobertura de ramas |
|---------|:------------------:|
| `src/two_sum.cc` | **100%** |

Se alcanzó **100% de cobertura de ramas** en el archivo principal `two_sum.cc`. Esto significa que todas las ramas de la lógica algorítmica fueron ejercitadas por los tests:

- **`two_sum`**: Se cubrió el camino donde se encuentra el complemento en el `unordered_map` (retorno temprano con los índices) y el camino donde se recorre el vector completo sin encontrar solución (retorno de vector vacío `{}`).
- **`two_sum_naive`**: Se cubrió el camino donde `nums[i] + nums[j] == target` (retorno temprano) y el camino donde se agotan ambos bucles sin encontrar solución (retorno de `{}`).

### Detalle de ramas cubiertas en `two_sum.cc`

| Función | Rama | Cubierta |
|---------|------|:--------:|
| `two_sum` | `i < nums.size()` (true: itera, false: sale del for) | Sí |
| `two_sum` | `indices.find(remainder) != indices.end()` (true: encontrado) | Sí |
| `two_sum` | `indices.find(remainder) != indices.end()` (false: no encontrado) | Sí |
| `two_sum` | `return {}` (sin solución) | Sí |
| `two_sum_naive` | `i < nums.size()` (true/false) | Sí |
| `two_sum_naive` | `j < nums.size()` (true/false) | Sí |
| `two_sum_naive` | `nums[i] + nums[j] == target` (true: encontrado) | Sí |
| `two_sum_naive` | `nums[i] + nums[j] == target` (false: continúa) | Sí |
| `two_sum_naive` | `return {}` (sin solución) | Sí |

## 5. Por qué inicialmente se reportaba menos del 100%

Sin la flag `--exclude-throw-branches`, `gcovr` reportaba coberturas de 62-75% en los archivos de test. Esto se debía a:

1. **Ramas de fallo de `assert()`**: El compilador genera una rama para el caso `true` (continúa) y otra para `false` (aborta). Como los tests pasan, la rama de fallo nunca se ejecuta.
2. **Ramas de excepciones (throw branches)**: GCC genera ramas implícitas para el manejo de excepciones en destructores y operaciones de la STL. Estas ramas no representan lógica del programa.

Ambas son ramas artificiales del compilador, no de la lógica del programador. La flag `--exclude-throw-branches` las filtra correctamente.

## 6. Reflexión

- El código bajo prueba (`two_sum.cc`) alcanza el **100% de cobertura de ramas**, lo cual confirma que los tests ejercitan todos los caminos posibles del algoritmo.
- El test `two_sum_no_solution_test` y `two_sum_naive_no_solution_test` son fundamentales para cubrir las ramas del `return {}` al final de cada función, que representan el caso donde no existe solución.
- En macOS es necesario usar `gcc-15`/`g++-15` explícitamente y `gcov-15` como ejecutable de gcov, ya que el `gcc` por defecto es un alias de `clang` que no genera archivos `.gcno`/`.gcda` compatibles.
- La exclusión de throw branches (`--exclude-throw-branches`) es una práctica recomendada para obtener métricas de cobertura que reflejen la lógica real del programa y no artefactos del compilador.
