/**
 *  @file    test_to_string.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all the @c to_string functions from String Manipulator.
 *
 *  @copyright  Copyright (c) 2024 Anstro Pleuton
 *
 *  Auspicious Library is a collection of Utils for Anstro Pleuton's programs.
 *
 *  This software is licensed under the terms of MIT License.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

#include <cstddef>
#include <format>
#include <string>
#include <string_view>

#define AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN
#include "al_string_manipulators.hpp"
#include "tester.hpp"

namespace al {
using namespace auspicious_library::sm;
} // namespace al
using namespace auspicious_library::sm_operators;

using namespace std::string_literals;
using namespace std::string_view_literals;

/**
 *  @brief  Test SM's to_string function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_string_1() -> std::size_t
{
    T_BEGIN;

    std::vector vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto        converter = [](int i) { return std::format("#{}#", i); };
    std::string expected = "<#1#>... <#2#>... <#3#>... <#4#>... <#5#>... "
                           "<#6#>... <#7#>... <#8#>... <#9#>... <#10#>";

    auto string = al::to_string(vector, converter, "... ", "<", ">");

    std::println("string: {}",   string);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(string, expected);

    return errors;
}

/**
 *  @brief  Test SM's to_string function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_string_2() -> std::size_t
{
    T_BEGIN;

    std::vector vector   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::string expected = "1, 2, 3, 4, 5, 6, 7, 8, 9, 10";

    auto string = al::to_string(vector);

    std::println("string: {}",   string);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(string, expected);

    T_END;
}

/**
 *  @brief  Test SM's to_string function (overload 3).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_string_3() -> std::size_t
{
    T_BEGIN;

    std::vector vector   = { 'a', 'b', 'c', 'd', 'e' };
    std::string expected = "'a', 'b', 'c', 'd', 'e'";

    auto string = al::to_string(vector);

    std::println("string: {}",   string);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(string, expected);

    T_END;
}

/**
 *  @brief  Test SM's to_string function (overload 4).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_string_4() -> std::size_t
{
    T_BEGIN;

    std::vector vector = { "Well"s, "Hello"s, "There"s, "General"s,
        "Kenobi"s };
    std::string expected = "\"Well\", \"Hello\", \"There\", \"General\", "
                           "\"Kenobi\"";

    auto string = al::to_string(vector);

    std::println("string: {}",   string);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(string, expected);

    T_END;
}

/**
 *  @brief  Test SM's chars_to_string function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_chars_to_string() -> std::size_t
{
    T_BEGIN;

    std::vector vector = { 'H', 'e', 'l',
        'l',                    'o', ',',
        ' ',
        'W',                    'o', 'r',
        'l',                    'd', '!' };
    std::string expected = "Hello, World!";

    auto string = al::chars_to_string(vector);

    std::println("string: {}",   string);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(string, expected);

    T_END;
}

/**
 *  @brief  Test String Manipulators' to_string.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_sm_to_string() -> std::size_t
{
    test_suite suite;
    suite.pre_run    = default_pre_runner('=', 3);
    suite.post_run   = default_post_runner('=', 3);
    suite.run_failed = default_run_failed_quitter();

    // Scary memory management

    suite.tests.emplace_back(new test {
        "Test SM's to_string function (overload 1)",
        "test_sm_to_string_1",
        test_sm_to_string_1
    });

    suite.tests.emplace_back(new test {
        "Test SM's to_string function (overload 2)",
        "test_sm_to_string_2",
        test_sm_to_string_2
    });

    suite.tests.emplace_back(new test {
        "Test SM's to_string function (overload 3)",
        "test_sm_to_string_3",
        test_sm_to_string_3
    });

    suite.tests.emplace_back(new test {
        "Test SM's to_string function (overload 4)",
        "test_sm_to_string_4",
        test_sm_to_string_4
    });

    suite.tests.emplace_back(new test {
        "Test SM's chars_to_string function",
        "test_sm_chars_to_string",
        test_sm_chars_to_string
    });

    auto failed_tests = suite.run();

    print_failed_tests(failed_tests);
    auto errors = get_failed_tests_errors(failed_tests);

    for (auto &test : suite.tests)
    {
        delete test;
    }

    return errors;
}
