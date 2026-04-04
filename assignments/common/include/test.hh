// test.hh - minimal testing suite, not safe for multi-threading
#pragma once

#include <functional>
#include <iostream>

static int passing;
static int failing;
static int total;

static void test(const std::string name, const std::string description,
                 std::function<bool()> func) {
  if (func()) {
    std::cout << name << "\t\t" << description << "\t\t" << "Ok" << std::endl;
    ++passing;
  } else {
    std::cerr << name << "\t\t" << description << "\t\t" << "Err" << std::endl;
    ++failing;
  }
  ++total;
}

static void report() {
  std::cout << failing << " failed out of " << total << std::endl;
}
