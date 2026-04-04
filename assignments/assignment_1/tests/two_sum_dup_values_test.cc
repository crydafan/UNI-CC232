#include <cassert>
#include <vector>

#include "two_sum.hh"

int main() {
  std::vector<int> nums = {3, 3};
  auto result = two_sum(nums, 6);
  assert(result.size() == 2);
  assert(result[0] == 0);
  assert(result[1] == 1);
}
