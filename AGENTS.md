# AGENTS.md - Development Guidelines

This is a C++ university assignment project using CMake.

## Build Commands

### Build Project
```bash
cd assignments/build
cmake ..
make
```

### Run All Tests
```bash
cd assignments/build
ctest --output-on-failure
```

### Run Single Test
```bash
# Run a specific test executable directly
./assignment_1/two_sum_basic_test

# Or use ctest with specific test name
cd assignments/build
ctest -R two_sum_basic_test --output-on-failure
```

### Clean Build
```bash
rm -rf assignments/build/*
cd assignments/build
cmake ..
make
```

## Project Structure

```
assignments/
├── CMakeLists.txt           # Root CMake config
├── build/                   # Build output directory
├── assignment_1/
│   ├── CMakeLists.txt
│   ├── src/                 # Implementation (.cc)
│   ├── include/             # Headers (.hh)
│   └── tests/               # Test files (.cc)
```

## Code Style Guidelines

### General
- **C++ Standard**: C++17
- **Header extension**: `.hh` (not `.hpp` or `.h`)
- **Implementation extension**: `.cc`
- **No comments** in code unless referencing external sources (e.g., LeetCode URL)

### Naming Conventions
- Functions: `snake_case` (e.g., `two_sum`, `two_sum_naive`)
- Variables: `snake_case` (e.g., `nums`, `target`, `indices`)
- Classes/Types: Not used in this project currently

### Imports and Includes
- System headers first, then blank line, then project headers
- Use `#pragma once` for header guards
- Example:
```cpp
#include <unordered_map>

#include "two_sum.hh"
```

### Formatting
- Use 2 spaces for indentation
- Curly braces on same line for control statements
- Use early returns when appropriate

### Header File Structure
```cpp
//
// Brief description of the problem/functionality
//
#pragma once

#include <vector>

// Function declarations only - no implementation
```

### Error Handling
- Return empty containers (`{}`) for "no solution" cases
- No exceptions
- Use `assert` for testing

### Testing
- Each test is a separate executable using `<cassert>`
- Test naming: `{module}_{test_case}_test.cc`
- Tests are registered via `add_test()` in CMakeLists.txt

## Key Files

- Root CMake: `assignments/CMakeLists.txt`
- Assignment CMake: `assignments/assignment_1/CMakeLists.txt`
- Header: `assignments/assignment_1/include/two_sum.hh`
- Implementation: `assignments/assignment_1/src/two_sum.cc`
