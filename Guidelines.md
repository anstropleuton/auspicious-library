I'll be honest with you, I took this straight from ChatGPT and did some tweaks to it. But the guidelines is mine tho.

---

# Auspicious Library Coding Guidelines

## Naming Conventions

### General
- Don't abbreviate names, acronyms are allowed. And namespace abbreviations are allowed (see [Namespace Names](#namespace-names)).
- Don't use single letter names, except when it is a mathematical formulas or names of indices.

### Variable Names
Use `snake_case` and keep the variable names descriptive.
```cpp
int users_count;
```

### Constant Names
Use `snake_case`, and keep the constant names descriptive.
```cpp
const int max_users = 10;
```

### Structure Names
Use `snake_case` and don't append any `_t` at the end. Prefer keeping it simple than descriptive.
```cpp
struct user {
    // ...
};
```

### Enumerator Names
Use `snake_case` and prefer keeping it simple than descriptive.
```cpp
enum user_type {
    // ...
};
```

### Function Names
Use `snake_case` and name the function based on what it does.
```cpp
auto create_user(std::string_view username) -> user;
```

### Namespace Names
When the namespace is internal use or is not in global space, abbreviate namespaces to 2-5 letters. We don't care about descriptiveness when not in global space.
```cpp
namespace nsp {
    // ...
};
```
In global space, prefer more descriptive name since one can just do `namespace a = a_long_namespace_name;`.

### Template Parameters
Use `PascalCase` for template parameters.
```cpp
template <typename Type>
struct structure;
```
This may change to `snake_case` for consistency, but is `PascalCase` for the time being.

### File Names
Use `snake_case` for file names.
```txt
my_module.hpp
my_module.cpp
```
Use specificity-first style, e.g., `animated_icon_texture.gif` over `texture_icon_animated.gif`.

## Formatting

### Indentation
Use 4 spaces for indentation, no tabs.

### Braces
Allman style for control flow or function definitions.
```cpp
if (condition)
{
    // code
}
```
K&R style for structures, enumerators, or namespaces.
```cpp
struct my_struct {
    // members
};
```

### Line Length
Limit lines to 80 characters. I use 1920x1080 screen and I use split view, side by side, to work with multiple files, and word wrap or having to scroll horizontally is less convenient.

### Spacing
Use spaces around operators and after commas, but not inside parentheses.
```cpp
int result = a + b;
if (a == b) { /* ... */ }

void do_something(int a, int b);
```

### Variable Declaration
Use `auto` for function expressions but not for constants or when the result is a fundamental type (`int`, `float`, etc., including aliases like `std::size_t`).
```cpp
auto value = get_value();
```

### Function Declarations
Split long function declarations for readability.
```cpp
[[nodiscard]] inline constexpr auto get_value(
    param_type_1 param_1,
    param_type_2 param_2
) -> return_type;
```

## Comments

### Single-Line Comments
Use `//` for single-line comments, placed above or on the code line.
```cpp
int my_variable; // This is a comment
```

### Multi-Line Comments
Use `/* */` with asterisks and two spaces at the start of each line.
```cpp
/*
 *  Multi-line comment.
 */
```

### Documentation Comments
Use Doxygen-style comments for documentation.
```cpp
/**
 *  @brief  Function description.
 *  @param  a  First parameter.
 *  @param  b  Second parameter.
 *  @return  Return description.
 */
```

### Punctuations
Use periods to end the sentence in a document comment, and not in regular comment
```cpp
/*
 *  This comment ends with a period.
 */

// This comment does not end with a period
```
Use two space in comment after `.`, `!` and `?` punctuations.
```cpp
/*
 *  This is a sentence.  This is another sentence after period!  Is this a
 *  life-long question?  And the end.
 */
```

### File Comment
Have a documentation comment on the first line of the file describing the file.
`header.hpp`:
```cpp
/**
 *  @file    header.hpp
 *  @author  Your Name (your.mail@email.provider)
 *  @brief   This is a header file.
 *
 *  @copyright  Copyright (C) 2024 I own this code to death
 *
 *  SUPER FANCY ART (OPTIONAL).
 *
 *  Detailed description.
 *
 *  License info.
 *
 *  Credits.
 */
```

## Code Structure

### Header Files
Use `#pragma once` for include guards.
```cpp
#pragma once
```
As oppose to `#ifndef` guards.

### Source Files
Include the corresponding header file first.
```cpp
#include "my_module.hpp"
```

## Functions and Lambdas

### Function Return Type
Use `auto` and trailing return types.
```cpp
[[nodiscard]] inline constexpr auto add(int a, int b) -> int;
```
If you are defining the function in the header file, let the compiler figure out the return type for you.
```cpp
[[nodiscard]] inline constexpr auto add(int a, int b)
{
    return a + b;
}
```

### `[[nodiscard]]`, `inline` and `constexpr` Functions
Use `[[nodiscard]]` to indicate the caller should not discard the value (almost always), use `inline` for small or performance-critical functions, and use `constexpr` (if applicable) to let compiler run the code at compile time.
```cpp
[[nodiscard]] inline constexpr auto add(int a, int b) -> int
{
    return a + b;
}
```

### Lambdas
Always use reference capture for lambda.
```cpp
auto lambda = [&]() { /* code */ };
```

### Static Functions
Use `static` for internal functions.
```cpp
static inline constexpr auto helper() -> void;
```

## Structures

### Structure Organization
Order members as:
- Data members
- Constructors
- Member functions
- Operators
- Conversion operators
```cpp
struct my_struct {

    // Data members
    int a;
    float b;

    // Constructors
    my_struct() = default;
    my_struct(int a, float b) : a(a), b(b) {};

    // Member functions
    [[nodiscard]] inline constexpr auto do_something(int a, float b)
    {
        return a + b;
    }

    [[nodiscard]] inline constexpr auto do_another_thing(int a, float b)
    {
        return a - b;
    }

    auto do_way_more_stuff(int a, float b) -> float;

    // Operators
    inline constexpr auto operator+=(const my_struct &other) -> my_struct &
    {
        a += other.a;
        b += other.b;
        return *this;
    }

    [[nodiscard]] friend inline constexpr auto operator-(
        const my_struct &a,
        const my_struct &b
    )
    {
        return my_struct(a.a + a.b, b.a + b.b);
    }

    // Conversion operators
    [[nodiscard]] inline constexpr operator int()
    {
        return a;
    }

    [[nodiscard]] inline constexpr operator float()
    {
        return b;
    }
};
```

### Constructors
Prefer making a type aggregate unless you really need constructors.

### Member Functions
Define non-inline member functions outside the struct in source files.
```cpp
auto my_struct::do_way_more_stuff(int a, float b) -> float
{
    return a + b - a - b + a + b - a - b;
}
```

### Operator Overloading
Use regular member functions for modifying operators, friend functions non-modifying operators.
```cpp
struct my_struct {
    inline constexpr auto operator+=(const my_struct& other) -> my_struct &
    { /* ... */ }

    [[nodiscard]] friend inline constexpr auto operator+(
        const my_struct &lhs,
        const my_struct& rhs
    ) -> my_struct
    { /* ... */ }
};
```

## Miscellaneous

### Enumerators
Include a `max` member in enumerators intended for use as indexes.

### Error Handling
Use exceptions for error handling, but return error codes in performance-critical functions.
```cpp
throw std::runtime_error("A very descriptive message with some debug info");
```

### Concepts
Prefer using defined concepts over `typename` for template parameters.

### Standard Library
Prefer C++ standard library features.
```cpp
#include <string>
std::string my_string = "Hello";
```

### Pointers and References
Use smart pointers over raw pointers, and references when ownership isn't changing.
```cpp
std::unique_ptr<my_struct> ptr = std::make_unique<my_struct>();
void my_function(const my_struct& obj);
```
Use raw pointers if you intend the API to accept address of local variables (still not worth it).

### Macros
Avoid macros; use `inline constexpr` or templated functions instead.
```cpp
#define MAX(a, b) ((a) > (b) ? (a) : (b)) // Avoid
```

### Initialization
Use `=` or `{}` for initializing values and `()` for constructing objects.
```cpp
int value = 10;
std::vector vec = {1, 2, 3};
Type object(param1, param2);
```

### Range-Based Loops
Prefer range-based loops and use `auto &` for all.
```cpp
for (auto &value : values) { /* code */ }
```

### Avoid Magic Numbers
Use named constants instead of magic numbers.
```cpp
const int max_size = 100;
```

### Use `nullptr`
Use `nullptr` instead of `NULL`.
```cpp
int *ptr = nullptr;
```

### Prefix `::`
Use `::` for calling C standard functions.
```cpp
char lowered = ::tolower(c);
```

### Abbreviations
Don't use abbreviated thing in API, but you can abbreviate long names like `std::ranges` to shorter names (e.g., `stdr`) within source files.
