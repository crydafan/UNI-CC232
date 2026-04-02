#include "two_sum.hh"

std::vector<int> two_sum(const std::vector<int> &nums, int target) {
  // TODO: implement
  return {};
}

std::vector<int> two_sum_naive(const std::vector<int> &nums, int target) {
  for (size_t i = 0; i < nums.size(); i++) {
    for (size_t j = 0; j < nums.size(); j++) {
      if (nums[i] + nums[j] == target)
        return {static_cast<int>(i), static_cast<int>(j)};
    }
  }
  return {};
}
