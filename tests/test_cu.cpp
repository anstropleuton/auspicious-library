/**
 *  @file    test_cu.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test everything in Container Utilities.
 *
 *  @copyright  Copyright (c) 2024 Anstro Pleuton
 *
 *      _                   _      _
 *     / \  _   _ ___ _ __ (_) ___(_) ___  _   _ ___
 *    / _ \| | | / __| '_ \| |/ __| |/ _ \| | | / __|
 *   / ___ \ |_| \__ \ |_) | | (__| | (_) | |_| \__ \
 *  /_/   \_\__,_|___/ .__/|_|\___|_|\___/ \__,_|___/
 *                   |_|  _    ___ ___ ___    _   _____   __
 *                       | |  |_ _| _ ) _ \  /_\ | _ \ \ / /
 *                       | |__ | || _ \   / / _ \|   /\ V /
 *                       |____|___|___/_|_\/_/ \_\_|_\ |_|
 *
 *  Auspicious Library is a collection of utils for Anstro Pleuton's programs.
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
 *
 *  Credits where credit's due:
 *  - ASCII Art generated using https://www.patorjk.com/software/taag with font
 *    "Standard" (for "Auspicious") and "Small" (for "LIBRARY").
 */

#include <cstddef>
#include <functional>

#include "tester.hpp"

/**
 *  @brief  Test CU's subordinate function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_subordinate() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::size_t first     = 2;
    std::size_t last      = 7;
    std::vector expected  = { 3, 4, 5, 6, 7 };

    auto subbed = al::subordinate(container, first, last);

    logln("container: {}", al::to_string(container));
    logln("first: {}",     first);
    logln("last: {}",      last);
    logln("subbed: {}",    al::to_string(subbed));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(subbed, expected);

    T_END;
}

/**
 *  @brief  Test CU's combine function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_combine_1() -> std::size_t
{
    T_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    std::vector b        = { 6, 7, 8, 9, 10 };
    std::vector expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto combined = al::combine(a, b);

    logln("a: {}",        al::to_string(a));
    logln("b: {}",        al::to_string(b));
    logln("combined: {}", al::to_string(combined));
    logln("expected: {}", al::to_string(expected));

    T_ASSERT_CTR(combined, expected);

    T_END;
}

/**
 *  @brief  Test CU's combine function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_combine_2() -> std::size_t
{
    T_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    int         b        = 6;
    std::vector expected = { 1, 2, 3, 4, 5, 6 };

    auto combined = al::combine(a, b);

    logln("a: {}",        al::to_string(a));
    logln("b: {}",        b);
    logln("combined: {}", al::to_string(combined));
    logln("expected: {}", al::to_string(expected));

    T_ASSERT_CTR(combined, expected);

    T_END;
}

/**
 *  @brief  Test CU's filter_out_seq function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_filter_out_seq() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector filter    = { 4, 5, 6 };
    std::vector expected  = { 1, 2, 3, 7, 8, 9, 10 };

    auto filtered = al::filter_out_seq(container, filter);

    logln("container: {}", al::to_string(container));
    logln("filter: {}",    al::to_string(filter));
    logln("filtered: {}",  al::to_string(filtered));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(filtered, expected);

    T_END;
}

/**
 *  @brief  Test CU's filter_out_occ function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_filter_out_occ() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector filter    = { 1, 3, 5, 7, 9 };
    std::vector expected  = { 2, 4, 6, 8, 10 };

    auto filtered = al::filter_out_occ(container, filter);

    logln("container: {}", al::to_string(container));
    logln("filter: {}",    al::to_string(filter));
    logln("filtered: {}",  al::to_string(filtered));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(filtered, expected);

    T_END;
}

/**
 *  @brief  Test CU's filter_out function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_filter_out() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         filter    = 3;
    std::vector expected  = { 1, 2, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered = al::filter_out(container, filter);

    logln("container: {}", al::to_string(container));
    logln("filter: {}",    filter);
    logln("filtered: {}",  al::to_string(filtered));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(filtered, expected);

    T_END;
}

/**
 *  @brief  Test CU's repeat function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_repeat_1() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    std::size_t times     = 3;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };

    auto repeated = al::repeat(container, times);

    logln("container: {}", al::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  al::to_string(repeated));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(repeated, expected);

    T_END;
}

/**
 *  @brief  Test CU's repeat function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_repeat_2() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    long double times     = 3.6;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
        3 };

    auto repeated = al::repeat(container, times);

    logln("container: {}", al::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  al::to_string(repeated));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(repeated, expected);

    T_END;
}

/**
 *  @brief  Test CU's split_seq function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_split_seq() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector splitter  = { 5, 6, 7 };
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4 },
        { 8, 9, 10 }
    };

    auto splitted = al::split_seq(container, splitter);

    logln("container: {}", al::to_string(container));
    logln("splitter: {}",  al::to_string(splitter));

    T_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", al::to_string(splitted[0]));
    logln("splitted[1]: {}", al::to_string(splitted[1]));
    logln("expected[0]: {}", al::to_string(expected[0]));
    logln("expected[1]: {}", al::to_string(expected[1]));

    T_ASSERT_SUB_SIZE(splitted, expected, 0);

    T_ASSERT_SUB_SIZE(splitted, expected, 1);

    T_END;
}

/**
 *  @brief  Test CU's split_occ function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_split_occ() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector splitter  = { 4, 8 };
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3 },
        { 5, 6, 7 },
        { 9, 10 }
    };

    auto splitted = al::split_occ(container, splitter);

    logln("container: {}", al::to_string(container));
    logln("splitter: {}",  al::to_string(splitter));

    T_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", al::to_string(splitted[0]));
    logln("splitted[1]: {}", al::to_string(splitted[1]));
    logln("splitted[2]: {}", al::to_string(splitted[2]));
    logln("expected[0]: {}", al::to_string(expected[0]));
    logln("expected[1]: {}", al::to_string(expected[1]));
    logln("expected[2]: {}", al::to_string(expected[2]));

    T_ASSERT_SUB_SIZE(splitted, expected, 0);

    T_ASSERT_SUB_SIZE(splitted, expected, 1);

    T_ASSERT_SUB_SIZE(splitted, expected, 2);

    T_END;
}

/**
 *  @brief  Test CU's split function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_split() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         splitter  = 7;
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4, 5, 6 },
        { 8, 9, 10 }
    };

    auto splitted = al::split(container, splitter);

    logln("container: {}", al::to_string(container));
    logln("splitter: {}",  splitter);

    T_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", al::to_string(splitted[0]));
    logln("splitted[1]: {}", al::to_string(splitted[1]));
    logln("expected[0]: {}", al::to_string(expected[0]));
    logln("expected[1]: {}", al::to_string(expected[1]));

    T_ASSERT_SUB_SIZE(splitted, expected, 0);

    T_ASSERT_SUB_SIZE(splitted, expected, 1);

    T_END;
}

/**
 *  @brief  Test CU operators' operator+ (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_plus_1() -> std::size_t
{
    T_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    std::vector b        = { 6, 7, 8, 9, 10 };
    std::vector expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto combined = a + b;

    logln("a: {}",        al::to_string(a));
    logln("b: {}",        al::to_string(b));
    logln("combined: {}", al::to_string(combined));
    logln("expected: {}", al::to_string(expected));

    T_ASSERT_CTR(combined, expected);

    T_END;
}

/**
 *  @brief  Test CU operators' operator+ (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_plus_2() -> std::size_t
{
    T_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    int         b        = 6;
    std::vector expected = { 1, 2, 3, 4, 5, 6 };

    auto combined = a + b;

    logln("a: {}",        al::to_string(a));
    logln("b: {}",        b);
    logln("combined: {}", al::to_string(combined));
    logln("expected: {}", al::to_string(expected));

    T_ASSERT_CTR(combined, expected);

    T_END;
}

/**
 *  @brief  Test CU operators' operator- (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_minus_1() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector filter    = { 4, 5, 6 };
    std::vector expected  = { 1, 2, 3, 7, 8, 9, 10 };

    auto filtered = container - filter;

    logln("container: {}", al::to_string(container));
    logln("filter: {}",    al::to_string(filter));
    logln("filtered: {}",  al::to_string(filtered));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(filtered, expected);

    T_END;
}

/**
 *  @brief  Test CU operators' operator- (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_minus_2() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         filter    = 3;
    std::vector expected  = { 1, 2, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered = container - filter;

    logln("container: {}", al::to_string(container));
    logln("filter: {}",    filter);
    logln("filtered: {}",  al::to_string(filtered));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(filtered, expected);

    T_END;
}

/**
 *  @brief  Test CU operators' operator* (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_star_1() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    std::size_t times     = 3;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };

    auto repeated = container * times;

    logln("container: {}", al::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  al::to_string(repeated));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(repeated, expected);

    T_END;
}

/**
 *  @brief  Test CU operators' operator* (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_star_2() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    long double times     = 3.6;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
        3 };

    auto repeated = container * times;

    logln("container: {}", al::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  al::to_string(repeated));
    logln("expected: {}",  al::to_string(expected));

    T_ASSERT_CTR(repeated, expected);

    T_END;
}

/**
 *  @brief  Test CU operators' operator/ (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_slash_1() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector splitter  = { 5, 6, 7 };
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4 },
        { 8, 9, 10 }
    };

    auto splitted = container / splitter;

    logln("container: {}", al::to_string(container));
    logln("splitter: {}",  al::to_string(splitter));

    T_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", al::to_string(splitted[0]));
    logln("splitted[1]: {}", al::to_string(splitted[1]));
    logln("expected[0]: {}", al::to_string(expected[0]));
    logln("expected[1]: {}", al::to_string(expected[1]));

    T_ASSERT_SUB_SIZE(splitted, expected, 0);

    T_ASSERT_SUB_SIZE(splitted, expected, 1);

    T_END;
}

/**
 *  @brief  Test CU operators' operator/ (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_cu_operator_slash_2() -> std::size_t
{
    T_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         splitter  = 7;
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4, 5, 6 },
        { 8, 9, 10 }
    };

    auto splitted = container / splitter;

    logln("container: {}", al::to_string(container));
    logln("splitter: {}",  splitter);

    T_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", al::to_string(splitted[0]));
    logln("splitted[1]: {}", al::to_string(splitted[1]));
    logln("expected[0]: {}", al::to_string(expected[0]));
    logln("expected[1]: {}", al::to_string(expected[1]));

    T_ASSERT_SUB_SIZE(splitted, expected, 0);

    T_ASSERT_SUB_SIZE(splitted, expected, 1);

    T_END;
}

/**
 *  @brief  Test... copper?  No wait, test Container Utilities.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu() -> std::size_t
{
    test_suite suite = {};
    suite.pre_run    = default_pre_runner('=', 3);
    suite.post_run   = default_post_runner('=', 3);
    // suite.run_failed = default_run_failed_quitter();

    // Scary memory management

    suite.tests.emplace_back(new test {
        "Test CU's subordinate function",
        "test_cu_subordinate",
        test_cu_subordinate
    });

    suite.tests.emplace_back(new test {
        "Test CU's combine function (overload 1)",
        "test_cu_combine_1",
        test_cu_combine_1
    });

    suite.tests.emplace_back(new test {
        "Test CU's combine function (overload 1)",
        "test_cu_combine_1",
        test_cu_combine_1
    });

    suite.tests.emplace_back(new test {
        "Test CU's combine function (overload 2)",
        "test_cu_combine_2",
        test_cu_combine_2
    });

    suite.tests.emplace_back(new test {
        "Test CU's filter_out_seq function",
        "test_cu_filter_out_seq",
        test_cu_filter_out_seq
    });

    suite.tests.emplace_back(new test {
        "Test CU's filter_out_occ function",
        "test_cu_filter_out_occ",
        test_cu_filter_out_occ
    });

    suite.tests.emplace_back(new test {
        "Test CU's filter_out function",
        "test_cu_filter_out",
        test_cu_filter_out
    });

    suite.tests.emplace_back(new test {
        "Test CU's repeat function (overload 1)",
        "test_cu_repeat_1",
        test_cu_repeat_1
    });

    suite.tests.emplace_back(new test {
        "Test CU's repeat function (overload 2)",
        "test_cu_repeat_2",
        test_cu_repeat_2
    });

    suite.tests.emplace_back(new test {
        "Test CU's split_seq function",
        "test_cu_split_seq",
        test_cu_split_seq
    });

    suite.tests.emplace_back(new test {
        "Test CU's split_occ function",
        "test_cu_split_occ",
        test_cu_split_occ
    });

    suite.tests.emplace_back(new test {
        "Test CU's split function",
        "test_cu_split",
        test_cu_split
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator+ (overload 1)",
        "test_cu_operator_plus_1",
        test_cu_operator_plus_1
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator+ (overload 2)",
        "test_cu_operator_plus_2",
        test_cu_operator_plus_2
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator- (overload 1)",
        "test_cu_operator_minus_1",
        test_cu_operator_minus_1
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator- (overload 2)",
        "test_cu_operator_minus_2",
        test_cu_operator_minus_2
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator* (overload 1)",
        "test_cu_operator_star_1",
        test_cu_operator_star_1
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator* (overload 2)",
        "test_cu_operator_star_2",
        test_cu_operator_star_2
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator/ (overload 1)",
        "test_cu_operator_slash_1",
        test_cu_operator_slash_1
    });

    suite.tests.emplace_back(new test {
        "Test CU operators' operator/ (overload 2)",
        "test_cu_operator_slash_2",
        test_cu_operator_slash_2
    });

    std::size_t errors = (std::size_t)-1;
    try
    {
        auto failed_tests = suite.run();

        print_failed_tests(failed_tests);
        errors = get_failed_tests_errors(failed_tests);
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred during test: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred during test");
    }

    for (auto &test : suite.tests)
    {
        delete test;
    }

    return errors;
}
