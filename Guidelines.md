# Guidelines

**NEEDS UPDATING**

## Naming Conventions

### For all names
- Avoid using abbreviated or truncated names.
- But you can use acronyms.
- No single letter names unless dealing with mathematical formula or indexes.
- Namespace names is an exception.

### Structs
- Should be in `snake_case`.
    ```cpp
    struct my_struct;
    ```

### Variables
- Should be in `snake_case`.
    ```cpp
    int my_variable;
    ```

### Constants
- Should be in `snake_case`.
    ```cpp
    const int max_value = 100;
    ```

### Functions and Methods
- Should be in `snake_case`.
    ```cpp
    auto my_function() -> void;
    ```

### Enumerations
- **Enumeration names** should be in `snake_case`.
- **Enumeration values** should be in `snake_case`.
    ```cpp
    enum class my_enum {
        first_value,
        second_value
    };
    ```

### Namespaces
- Should be in `snake_case`.
    ```cpp
    namespace nsp;
    ```
- Here, you should use abbreviations.
- Should be between 2-5 letters.

### Template Parameter
- Should be in `PascalCase`.
    ```cpp
    template <typename Type>
    struct structure;
    ```

### Files
- **Header files** should have a `.hpp` extension.
- **Source files** should have a `.cpp` extension.
- File names should be in `snake_case`.
    ```txt
    my_module.hpp
    my_module.cpp
    ```

## Formatting

### Indentation
- Use 4 spaces for indentation. Do not use tabs.

### Braces
- Use Allman style for braces that involve control flow or function definition.
    ```cpp
    if (condition)
    {
        // code
    }
    ```
- Use K&R style for braces when defining structs, enums or namespaces.
    ```cpp
    struct my_struct {
        // members
    };
    ```

### Line Length
- Limit lines to 160 characters.

### Spaces
- Use spaces around operators.
    ```cpp
    int result = a + b;
    ```
- Do not use spaces inside parentheses.
    ```cpp
    if (a == b)
    ```
- Use a space after commas.
    ```cpp
    void do_something(int a, int b);
    ```

### Blank Lines
- Use blank lines to separate logical sections of the code.
    ```cpp
    int a = 10;

    if (a > 5)
    {
        // code
    }

    a++;
    ```

### Variable Declaration
- Use `auto` to deduce types of an expression involving function calls.
- Do not use `auto` to deduce types from constants.
    ```cpp
    auto value = do_something();
    ```

### Max width
- Max width is 80 characters. You can split up a long function declaration as so:
    ```cpp
    [[nodiscard]] inline constexpr auto get_value(
        a_very_long_parameter_type_1 a_very_long_parameter_1,
        a_long_parameter_type_2      a_very_long_parameter_2
    ) -> a_very_long_return_type
    {
        // relatively short code
        return a_very_long_return_value;
    }
    ```

## Comments

### Single-line Comments
- Use `//` for single-line comments. Place them above or on the line of the code they refer to.
    ```cpp
    int my_variable; // This is a single-line comment
    ```

### Multi-line Comments
- Use `/* */` for multi-line comments with each line starting from a `*` and two spaces.
    ```cpp
    /*
     *  This is a multi-line comment.
     *  It can span multiple lines.
     */
    int my_variable;
    ```

### Periods
- Use two space after a period in a comment.
    ```cpp
    /**
     *  This is a thing.  After that it does this.  So do that.
     */
    type thing;
    ```

### Documentation Comments
- Use doxygen formatted comments for documentation comments.
    ```cpp
    /**
     *  @brief  This function does something important.
     *
     *  @param   a  The first important parameter.
     *  @param   b  The second important parameter.
     *  @return  An important value.
     */
    int do_something(int a, int b);
    ```
- Use two spaces between the tag and the parameter/description.

## File Structure

### Header Files
- Use `#pragma once` to prevent multiple inclusions.
    ```cpp
    #pragma once
    // header content
    ```

### Source Files
- Source files should include their corresponding header files as the first include.
    ```cpp
    #include "my_module.hpp"
    ```

### Avoid Utils or Misc files
- Prefer creating a new file for each logical code instead of dumping all the utility related code in one file.

## (Member/) Functions and Lambdas

### (Member/) Function Declaration
- Use `auto` and trailing return type when declaring functions.
    ```cpp
    [[nodiscard]] auto do_something(int a, int b) -> int;
    ```

### (Member/) Function Declaration
- Use `auto` and don't use trailing return type when defining functions.
    ```cpp
    auto do_something(int a, int b)
    {
    }
    ```
- Use trailing return type when the function already has a declaration or when the return type cannot be deduced.

### Inline Functions
- Use `inline` keyword for small, performance-critical functions if they are not part of a struct.
    ```cpp
    [[nodiscard]] inline auto add(int a, int b)
    {
        return a + b;
    }
    ```

### Lambdas
- Use `auto` for lambda parameters.
- Always reference capture everything.
    ```cpp
    auto pos = std::ranges::find(my_instances, [&](const auto &my_instance) { return my_instance.value == my_value; });
    ```


### Attributes
- Always use `[[nodiscard]]` for function returning a value. Even the main().
    ```cpp
    [[nodiscard]] auto get_value()
    {
        return value;
    }
    ```

### Static
- Use static to make a function not visible outside a compilation unit.
    ```cpp
    static auto internal_helper_function() -> void
    {
        // ...
    }
    ```
- Prefer static functions over lambda, unless there are too many local variables to share between the functions.

## Structs

### struct Organization
- Define member variables first.
- Followed by constructors.
- Followed by member functions.
- Followed by overloaded operators.
- Followed by conversion operators.
    ```cpp
    struct my_struct {
        // data members
        int a;
        float b;

        // constructors
        my_struct() = default;
        my_struct(int _a, float _b): a(_a), b(_b) {}
        my_struct(float ab): a(ab), b(ab) {}

        float do_something(int a, float b);

        float do_something_short(int a, float b)
        {
            return a + b;
        }

        // operators
        my_struct &operator+=(const my_struct& other)
        {
            a += other.a;
            b += other.b;
            return *this;
        }

        // conversion operators
        operator float()
        {
            return a + b;
        }
    };
    ```

### Access Specifiers
- Never use private or protected members.

### Member Variables
- Define each variable in a new line even if they are of same type.
    ```cpp
    struct my_struct {
        int x;
        int y;
        int z;
        int w;
    };
    ```

### Constructors
- Don't provide default or parameterized constructor.

### Member Functions
- Define member functions outside the struct declaration in the source file if they are not inline.
    ```cpp
    void my_struct::my_function()
    {
        // function implementation
    }
    ```
- No need to use the `inline` keyword to define a member function.

### Operator Overloading
- Use regular member functions for operators that modify the object.
- Use friend member functions for symmetric operators.
    ```cpp
    struct my_struct
    {
    public:
        my_struct& operator+=(const my_struct& rhs);

        friend my_struct operator+(my_struct lhs, const my_struct& rhs)
        {
            lhs += rhs;
            return lhs;
        }
    };
    ```

## Miscellaneous

### Include Order
- Main Module Header
- Local/Third-party Headers
- System #includes
    ```cpp
    #include "my_module.hpp"

    #include "raylib.h"

    #include <vector>
    ```

### Max Enum Member
- Have a member named max in every enum types intended to be used as index.

### Error Handling
- Use exceptions for error handling.
    ```cpp
    throw std::runtime_error("Error message");
    ```
- Do not use exceptions on performance-critical functions. Use returned error codes instead.

### Concepts
- Prefer using defined concept instead of `typename`.
- Prefer defining concept using standard library concepts instead of directly using standard library concepts.

### Standard Library
- Prefer C++ standard library features over C-style counterparts.
    ```cpp
    #include <string>
    std::string my_string = "Hello, World!";
    ```

### Pointer and Reference
- Prefer using smart pointers (`std::unique_ptr`, `std::shared_ptr`) over raw pointers.
    ```cpp
    std::unique_ptr<my_struct> ptr = std::make_unique<my_struct>();
    ```
- Use references when the ownership of the object does not need to be changed.
    ```cpp
    void my_function(const my_struct& my_value);
    ```

### Constants and Literals
- Use `constexpr` for compile-time constants.
    ```cpp
    constexpr int max_value = 100;
    ```

### Macros
- Avoid using macros; prefer inline functions, `constexpr`, and templates.
    ```cpp
    #define MAX(a, b) ((a) > (b) ? (a) : (b)) // Avoid
    inline constexpr int max(int a, int b)
    {
        return (a > b) ? a : b;
    }
    ```
- If you do use macros, name it `UPPER_SNAKE_CASE`.

### Lambdas
- Use lambdas defining functions inside of another function when this function is not intended to be used anywhere else.
    ```cpp
    auto add = [](int a, int b) { return a + b; };
    ```

### Initialization
- Use `=` for initializing type.
    ```cpp
    int value = 10;
    ```
- Always initialize to `{}` for user defined types.
    ```cpp
    Type value = {};
    ```

### Range-based For Loops
- Prefer range-based for loops over traditional loops.
- Always use `auto &` for range-based loop.
    ```cpp
    std::vector<int> values = { 1, 2, 3, 4, 5 };
    for (auto &value : values)
    {
        // use value
    }
    ```

### Passing Instance of Newly Constructed Type to Function Parameter

- Use the `Type {}` syntax for passing an instance of a newly created type which uses initializer_list.
    ```cpp
    void print_vector(std::vector<int> { 1, 2, 3, 4, 5 });
    ```

- Use the `Type()` syntax for passing an instance of a newly constructed type which uses constructor.
    ```cpp
    void print_string(std::string(5, 'a'));
    ```

- Use the `Type {}` syntax for default initializing a type.
    ```cpp
    void process_t_default(Type(parameters), Type {});
    ```

### Avoid Magic Numbers
- Use named constants instead of magic numbers.
    ```cpp
    constexpr int max_array_size = 100;
    int array[max_array_size];
    ```

### Prefer auto Keyword
- Use the `auto` keyword for variable declarations that are a result of an function.
    ```cpp
    auto my_variable = get_value();
    ```

### Use nullptr
- Use `nullptr` instead of `NULL` or `0` for pointer initialization.
    ```cpp
    int* ptr = nullptr;
    ```

### Prefix ::
- Always prefix :: to indicate that you are using a C standard function.
    ```cpp
    char lowered = ::tolower(my_letter);
    ```

### Long names
- Abbreviating long names such as `std::ranges` to `stdr` is okay if it is done in a source file.
