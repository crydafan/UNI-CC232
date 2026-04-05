#include <cassert>
#include <vector>

#include "two_sum.hh"

int main() {
  std::vector<int> nums = {3, 2, 4};
  auto result = two_sum_naive(nums, 6);
  assert(result.size() == 2);
  assert(result[0] != result[1]);
  auto sum = nums[result[0]] + nums[result[1]];
  assert(sum == 6);
}
