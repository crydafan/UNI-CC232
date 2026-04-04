#include <cassert>
#include <vector>

#include "two_sum.hh"

int main() {
  std::vector<int> nums = {1, 2, 3};
  auto result = two_sum_naive(nums, 10);
  assert(result.empty());
}
