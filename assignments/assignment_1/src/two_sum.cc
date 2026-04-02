#include <unordered_map>

#include "two_sum.hh"

// https://leetcode.com/problems/two-sum/submissions/1965012909
std::vector<int> two_sum(const std::vector<int> &nums, int target) {
  std::unordered_map<int, int> indices;

  for (int i = 0; i < nums.size(); ++i) {
    int remainder = target - nums[i];

    if (indices.find(remainder) != indices.end())
      return {indices[remainder], i};

    indices[nums[i]] = i;
  }

  return {};
}

std::vector<int> two_sum_naive(const std::vector<int> &nums, int target) {
  for (int i = 0; i < nums.size(); ++i) {
    for (int j = 0; j < nums.size(); ++j) {
      if (nums[i] + nums[j] == target)
        return {i, j};
    }
  }

  return {};
}
