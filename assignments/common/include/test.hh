#pragma once

#include <functional>
#include <iomanip>
#include <iostream>

static int passing;
static int failing;
static int total;

static constexpr size_t TEST_NAME_WIDTH = 28;
static constexpr size_t TEST_DESC_WIDTH = 56;

static void test(const std::string name, const std::string description,
                 std::function<bool()> func) {
  if (func()) {
    std::cout << std::left << std::setw(TEST_NAME_WIDTH) << name
              << std::setw(TEST_DESC_WIDTH) << description << "Ok" << std::endl;
    ++passing;
  } else {
    std::cerr << std::left << std::setw(TEST_NAME_WIDTH) << name
              << std::setw(TEST_DESC_WIDTH) << description << "Err"
              << std::endl;
    ++failing;
  }
  ++total;
}

static void report() {
  std::cout << failing << " failed out of " << total << std::endl;
}
