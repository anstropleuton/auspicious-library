/*
 *  Auspicious Library is a collection of Utils for Anstro Pleuton's programs.
 *
 *  This software is licensed under the terms of MIT License.
 *
 *  Copyright (C) 2024 Anstro Pleuton
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

#pragma once

#include <algorithm>
#include <functional>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#define T_ERRORS      errors
#define T_ERRORS_TYPE std::size_t
#define T_BEGIN       T_ERRORS_TYPE T_ERRORS = {}; do {} while (false)
#define T_END         return T_ERRORS; do {} while (false)

#define T_ASSERT_CODE_FMT(value, expected, code, fmt, ...) \
if (value != expected)                                     \
{                                                          \
    std::println(fmt, __VA_ARGS__);                        \
    T_ERRORS++;                                            \
    code;                                                  \
}                                                          \
do {} while (false)

#define T_ASSERT_FMT(value, expected, fmt, ...) \
T_ASSERT_CODE_FMT(value, expected, {}, fmt, __VA_ARGS__)

#define T_ASSERT_CODE(value, expected, message, code)                        \
T_ASSERT_CODE_FMT(value, expected, code, "{}: {} != {} ({} != {})", message, \
    #value, #expected, value, expected)

#define T_ASSERT(value, expected, message)                                 \
T_ASSERT_CODE_FMT(value, expected, {}, "{}: {} != {} ({} != {})", message, \
    #value, #expected, value, expected)

#define T_ASSERT_SIZE(value, expected)                  \
T_ASSERT_CODE_FMT(value.size(), expected.size(), T_END, \
    "Invalid size: {}.size() != {}.size() ({} != {})",  \
    #value, #expected, value.size(), expected.size())

#define T_ASSERT_ELM(value, expected, i)                                     \
T_ASSERT_FMT(value[i], expected[i],                                          \
    "Invalid element: {}[{}] != {}[{}] ({} != {})", #value, i, #expected, i, \
    value[i], expected[i])

#define T_ASSERT_CTR(value, expected)             \
T_ASSERT_SIZE(value, expected);                   \
for (std::size_t i = 0; i < expected.size(); i++) \
{                                                 \
    T_ASSERT_ELM(value, expected, i);             \
}                                                 \
do {} while (false)

#define T_ASSERT_SUB_SIZE(value, expected, i)                  \
T_ASSERT_CODE_FMT(value[i].size(), expected[i].size(), T_END,  \
    "Invalid size: {}[{}].size() != {}[{}].size() ({} != {})", \
    #value, i, #expected, i, value[i].size(), expected[i].size())

#define T_ASSERT_SUB_ELM(value, expected, i1, i2)                           \
T_ASSERT_FMT(value[i1][i2], expected[i1][i2],                               \
    "Invalid element: {}[{}][{}] != {}[{}][{}] ({} != {})", #value, i1, i2, \
    #expected, i1, i2, value[i1][i2], expected[i2][i2])

#define T_ASSERT_SUB_CTR(value, expected, i)         \
T_ASSERT_SUB_SIZE(value, expected, i);               \
for (std::size_t j = 0; j < expected[i].size(); j++) \
{                                                    \
    T_ASSERT_SUB_ELM(value, expected, i, j);         \
}                                                    \

#define T_ASSERT_NEST_CTR(value, expected)        \
T_ASSERT_SIZE(value, expected);                   \
for (std::size_t i = 0; i < expected.size(); i++) \
{                                                 \
    T_ASSERT_SUB_CTR(value, expected, i)          \
}                                                 \
do {} while (false)

/**
 *  @brief  Test the function.
 */
struct test {

    /**
     *  @brief  Test title, useful to identify failed tests.
     */
    std::string title;

    /**
     *  @brief  Testing function's name.
     */
    std::string function_name;

    /**
     *  @brief  The function to test which returns the number of errors.
     */
    std::function<std::size_t()> function;

    /**
     *  @brief  Run the test.
     *  @return  the number of errors within the test.
     */
    [[nodiscard]] inline constexpr auto run() const { return function(); }
};

/**
 *  @brief  A category of tests.
 */
struct test_suite {

    /**
     *  @brief  All the tests.
     */
    std::vector<const test *> tests;

    /**
     *  @brief  Function to execute before a test.
     */
    std::function<void (const test *)> pre_run;

    /**
     *  @brief  Function to execute after a test.
     */
    std::function<void (const test *, std::size_t)> post_run;

    /**
     *  @brief  Function to execute after a failed test. Return true to stop
     *          further tests.
     *  @note  Also executes @c post_run
     */
    std::function<bool (const test *, std::size_t)> run_failed;

    /**
     *  @brief  Run all tests.
     *  @return  Titles and errors count of each failed test.
     */
    [[nodiscard]] inline constexpr auto run()
    {
        std::vector<std::pair<const test *, std::size_t>> failed_tests = {};
        for (auto &test : tests)
        {
            if (pre_run) pre_run(test);
            std::size_t errors   = test->run();
            bool        end_test = false;

            if (errors != 0)
            {
                failed_tests.emplace_back(test, errors);
                if (run_failed && run_failed(test, errors))
                {
                    end_test = true;
                }
            }

            if (post_run) post_run(test, errors);
            if (end_test) break;
        }
        return failed_tests;
    };
};

/**
 *  @brief  Get fancy default pre-run function for decorated title output.
 *  @param  decor_char   Decoration character for before and after title.
 *  @param  decor_count  Decoration character count.
 *  @return  Decorator function.
 */
[[nodiscard]] inline auto default_pre_runner(
    char        decor_char,
    std::size_t decor_count = 1
)
{
    std::string decor = std::ranges::views::repeat(decor_char, decor_count)
                        | std::ranges::to<std::string>();
    return [=](const test *test) {
        std::println("{} {} {}", decor, test->title, decor);
    };
}

/**
 *  @brief  Get fancy default post-run function for decorated title output.
 *  @param  decor_char   Decoration character for before and after title.
 *  @param  decor_count  Decoration character count.
 *  @return  Decorator function.
 */
[[nodiscard]] inline auto default_post_runner(
    char        decor_char,
    std::size_t decor_count = 1
)
{
    std::string decor = std::views::repeat(decor_char, decor_count)
                        | std::ranges::to<std::string>();
    return [=](const test *test, std::size_t errors) {
        std::println("{} End of {}, {} errors {}\n", decor, test->title, errors,
            decor);
    };
}

/**
 *  @brief  Terminate further tests after printing failed test title.
 *  @return  Quitter function.
 */
[[nodiscard]] inline auto default_run_failed_quitter()
{
    return [=](const test *test, std::size_t errors) {
        std::println("{} failed, cannot conduct further tests.", test->title);
        return true;
    };
}

/**
 *  @brief  Print all failed test's title and errors count.
 *  @param  failed_tests  Failed test results.
 */
inline auto print_failed_tests(
    const std::vector<std::pair<const test *,
        std::size_t>> &failed_tests
)
{
    if (failed_tests.empty()) return;

    std::println("Failed tests:");
    for (auto &failed_test : failed_tests)
    {
        std::println("  {}: {} errors", failed_test.first->title,
            failed_test.second);
    }
}

/**
 *  @brief  Get number of errors in total in all failed tests
 *  @param  failed_tests  Failed test results.
 *  @return  number of total errors.
 */
[[nodiscard]] inline constexpr auto get_failed_tests_errors(
    const std::vector<std::pair<const test *,
        std::size_t>> &failed_tests
)
{
    std::size_t errors = 0;
    std::ranges::for_each(failed_tests, [&](const auto &failed_test) {
        errors += failed_test.second;
    });
    return errors;
}
