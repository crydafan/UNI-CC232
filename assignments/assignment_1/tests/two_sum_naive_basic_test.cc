#include <cassert>
#include <vector>

#include "two_sum.hh"

int main() {
  std::vector<int> nums = {2, 7, 11, 15};
  auto result = two_sum_naive(nums, 9);
  assert(result.size() == 2);
  assert(result[0] == 0);
  assert(result[1] == 1);
}
