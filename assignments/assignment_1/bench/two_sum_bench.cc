#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>

#include "two_sum.hh"

// 1. Aumentamos el tamaño a 50,000 para que el algoritmo demore lo suficiente
static constexpr size_t BENCH_VECTOR_ELEMENTS = 50000;

int main() {
  std::vector<int> nums;
  nums.resize(BENCH_VECTOR_ELEMENTS);

  for (size_t i = 0; i < nums.size(); ++i)
    nums[i] = static_cast<int>(i);

  // 2. Un objetivo imposible garantiza el ABSOLUTO peor caso matemático
  int target = -1;

  std::size_t naive_time, final_time;

  {
    auto start = std::chrono::high_resolution_clock::now();
    auto res = two_sum_naive(nums, target);
    auto end = std::chrono::high_resolution_clock::now();
    naive_time =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    auto res2 = two_sum(nums, target);
    auto end = std::chrono::high_resolution_clock::now();
    final_time =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
  }

  // 3. Corregimos el texto a "us" (microsegundos) para ser precisos
  std::cout << "naive took " << naive_time << " us to complete\n";
  std::cout << "final took " << final_time << " us to complete\n";
}
