#include <cstddef>
#include <iostream>
#include <vector>

#include "two_sum.hh"

int main() {
  std::vector<int> nums;
  nums.resize(10000);

  for (int i = 0; i < nums.size(); ++i)
    nums[i] = i;
  int target = nums[nums.size() - 1] + nums[nums.size() - 2];

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

  std::cout << "naive took " << naive_time << " ms to complete\n";
  std::cout << "final took " << final_time << " ms to complete\n";
}
