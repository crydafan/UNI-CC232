#include <cassert>
#include <vector>

#include "two_sum.hh"

int main() {
  std::vector<int> nums = {3, 3};
  auto result = two_sum_naive(nums, 6);
  assert(result.size() == 2);
  auto sum = nums[result[0]] + nums[result[1]];
  assert(sum == 6);
}
