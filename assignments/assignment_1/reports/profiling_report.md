## 📊 Reporte Experimental de Rendimiento y Complejidad

### 1. Análisis de Tiempo Real (Benchmark)
Se evaluó el comportamiento de dos enfoques para el problema "Two Sum" frente a un caso de prueba extremo ($N = 50,000$, con un objetivo inalcanzable para forzar el peor caso).

| Algoritmo | Estructura de Datos | Complejidad | Tiempo Empírico |
| :--- | :--- | :--- | :--- |
| **two_sum_naive** | Bucle Anidado (Fuerza Bruta) | $\mathcal{O}(n^2)$ | `11,025,876 us` (~11.0s) |
| **two_sum (Final)** | `std::unordered_map` (Hash Map) | $\mathcal{O}(n)$ | `12,914 us` (~0.01s) |

> 💡 **Conclusión Empírica:** La diferencia es abismal. Mientras la fuerza bruta colapsa con grandes volúmenes de datos, la eficiencia de acceso $\mathcal{O}(1)$ de las tablas Hash de la STL resolvió el problema **854 veces más rápido**. Ninguna bandera de compilación u optimización de código puede superar una mejora asintótica del algoritmo.

---

### 2. Análisis de Costo Computacional (`gprof`)
Utilizando la herramienta de profiling estadístico `gprof` sin inlining (`-fno-omit-frame-pointer`), pudimos abrir la "caja negra" del procesador y contabilizar las operaciones exactas.

```mermaid
graph TD
    A[Caso de Prueba Extremo<br>N = 50,000] --> B(Algoritmo Naive)
    A --> C(Algoritmo Optimizado)
    
    B -->|Bucle Anidado| D[2,500,050,000<br>Accesos al Vector]
    C -->|Hash Map| E[50,000<br>Búsquedas Promedio]
    
    D --> F((Cuello de Botella:<br>11.02 Segundos))
    E --> G((Eficiencia:<br>0.01 Segundos))
    
    style F fill:#e74c3c,stroke:#c0392b,color:#fff,stroke-width:2px
    style G fill:#2ecc71,stroke:#27ae60,color:#fff,stroke-width:2px
