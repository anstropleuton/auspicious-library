/**
 *  @file    test_sm.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of String Manipulators in Auspicious Library.
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
#include <limits>
#include <string>
#include <string_view>

#define AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN
#include "string_manipulators.hpp"
#include "tester.hpp"

namespace al {
using namespace auspicious_library::sm;
} // namespace al
using namespace auspicious_library::sm_operators;

using namespace std::string_literals;
using namespace std::string_view_literals;

/**
 *  @brief  Test SM's word_wrap function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_word_wrap() -> std::size_t
{
    T_BEGIN;

    std::string long_string = "Never gonna give you up, "
                              "Never gonna let you down, "
                              "Never gonna run around and desert you. "
                              "Never gonna make you cry, "
                              "Never gonna say Lopadotemachoselachogaleokranioleipsanodrimhypotrimmatosilphioparaomelitokatakechymenokichlepikossyphophattoperisteralektryonoptekephalliokigklopeleiolagoiosiraiobaphetraganopterygon, "
                              "Never gonna tell a lie and hurt you.";

    std::vector expected_1 = {
// ..... 1       10        20        30        40
// ..... V        V         V         V         V
        "Never gonna give you up, Never gonna let"s,
        "you down, Never gonna run around and"s,
        "desert you. Never gonna make you cry,"s,
        "Never gonna say"s,
        "Lopadotemachoselachogaleokranioleipsanodrimhypotrimmatosilphioparaomelitokatakechymenokichlepikossyphophattoperisteralektryonoptekephalliokigklopeleiolagoiosiraiobaphetraganopterygon,"s,
        "Never gonna tell a lie and hurt you."s
    };

    std::vector expected_2 = {
// ..... 1       10        20        30        40
// ..... V        V         V         V         V
        "Never gonna give you up, Never gonna let"s,
        "you down, Never gonna run around and"s,
        "desert you. Never gonna make you cry,"s,
        "Never gonna say"s,
        "Lopadotemachoselachogaleokranioleipsanod"s,
        "rimhypotrimmatosilphioparaomelitokatakec"s,
        "hymenokichlepikossyphophattoperisteralek"s,
        "tryonoptekephalliokigklopeleiolagoiosira"s,
        "iobaphetraganopterygon, Never gonna tell"s,
        "a lie and hurt you."s
    };

    auto wrapped_1 = al::word_wrap(long_string, 40);
    auto wrapped_2 = al::word_wrap(long_string, 40, true);

    std::println("long_string:\n{}", long_string);

    T_ASSERT_SIZE(wrapped_1, wrapped_1);
    T_ASSERT_SIZE(wrapped_2, wrapped_2);

    std::println("wrapped_1:\n{}",  al::to_string(wrapped_1, "\n"sv, "  \""));
    std::println("expected_1:\n{}", al::to_string(expected_1, "\n"sv, "  \""));
    std::println("wrapped_2:\n{}",  al::to_string(wrapped_2, "\n"sv, "  \""));
    std::println("expected_2:\n{}", al::to_string(expected_2, "\n"sv, "  \""));

    T_ASSERT_SIZE(wrapped_1, expected_1);

    T_ASSERT_SIZE(wrapped_2, expected_2);

    T_END;
}

/**
 *  @brief  Test SM's trim_left function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_trim_left() -> std::size_t
{
    T_BEGIN;

    std::string string   = " \tAyo word \t";
    std::string expected = "Ayo word \t";

    auto trimmed = al::trim_left(string);

    std::println("string: {}",   string);
    std::println("trimmed: {}",  trimmed);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(trimmed, expected);

    T_END;
}

/**
 *  @brief  Test SM's trim_right function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_trim_right() -> std::size_t
{
    T_BEGIN;

    std::string string   = " \tAyo word \t";
    std::string expected = " \tAyo word";

    auto trimmed = al::trim_right(string);

    std::println("string: {}",   string);
    std::println("trimmed: {}",  trimmed);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(trimmed, expected);

    T_END;
}

/**
 *  @brief  Test SM's trim function.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_trim() -> std::size_t
{
    T_BEGIN;

    std::string string   = " \tAyo word \t";
    std::string expected = "Ayo word";

    auto trimmed = al::trim(string);

    std::println("string: {}",   string);
    std::println("trimmed: {}",  trimmed);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(trimmed, expected);

    T_END;
}

/**
 *  @brief  Test SM's to_upper function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_upper_1() -> std::size_t
{
    T_BEGIN;

    std::string string   = "LaTeX";
    std::string expected = "LATEX";

    auto upper = al::to_upper(string);

    std::println("string: {}",   string);
    std::println("upper: {}",    upper);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(upper, expected);

    T_END;
}

/**
 *  @brief  Test SM's to_lower function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_lower_1() -> std::size_t
{
    T_BEGIN;

    std::string string   = "LaTeX";
    std::string expected = "latex";

    auto lower = al::to_lower(string);

    std::println("string: {}",   string);
    std::println("lower: {}",    lower);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(lower, expected);

    T_END;
}

/**
 *  @brief  Test SM's to_upper function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_upper_2() -> std::size_t
{
    T_BEGIN;

    char character = 'a';
    char expected  = 'A';

    auto upper = al::to_upper(character);

    std::println("character: {}", character);
    std::println("upper: {}",     upper);
    std::println("expected: {}",  expected);

    T_ASSERT(upper, expected, "Invalid result");

    T_END;
}

/**
 *  @brief  Test SM's to_lower function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_to_lower_2() -> std::size_t
{
    T_BEGIN;

    char character = 'A';
    char expected  = 'a';

    auto lower = al::to_lower(character);

    std::println("character: {}", character);
    std::println("lower: {}",     lower);
    std::println("expected: {}",  expected);

    T_ASSERT(lower, expected, "Invalid result");

    T_END;
}

/**
 *  @brief  Test SM's is_equal_ins function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_is_equal_ins_1() -> std::size_t
{
    T_BEGIN;

    std::string a_1        = "LaTeX";
    std::string b_1        = "lAtEx";
    bool        expected_1 = true;
    std::string a_2        = "HeLlO";
    std::string b_2        = "wOrLd";
    bool        expected_2 = false;

    auto value_1 = al::is_equal_ins(a_1, b_1);
    auto value_2 = al::is_equal_ins(a_2, b_2);

    std::println("a_1: {}, b_1: {}", a_1, b_1);
    std::println("a_2: {}, b_2: {}", a_2, b_2);
    std::println("value_1: {}, expected_1: {}", value_1, expected_1);
    std::println("value_2: {}, expected_2: {}", value_2, expected_2);

    T_ASSERT(value_1, expected_1, "Invalid result");
    T_ASSERT(value_2, expected_2, "Invalid result");

    T_END;
}

/**
 *  @brief  Test SM's is_equal_ins function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_is_equal_ins_2() -> std::size_t
{
    T_BEGIN;

    char a_1        = 'a';
    char b_1        = 'A';
    bool expected_1 = true;
    char a_2        = 'b';
    char b_2        = 'C';
    bool expected_2 = false;

    auto value_1 = al::is_equal_ins(a_1, b_1);
    auto value_2 = al::is_equal_ins(a_2, b_2);

    std::println("a_1: {}, b_1: {}", a_1, b_1);
    std::println("a_2: {}, b_2: {}", a_2, b_2);
    std::println("value_1: {}, expected_1: {}", value_1, expected_1);
    std::println("value_2: {}, expected_2: {}", value_2, expected_2);

    T_ASSERT(value_1, expected_1, "Invalid result");
    T_ASSERT(value_2, expected_2, "Invalid result");

    T_END;
}

/**
 *  @brief  Test SM operators' operator- (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_operator_minus_1() -> std::size_t
{
    T_BEGIN;

    std::string string = "This is the text with a lot of \"the\" words in the "
                         "text as of the day I am writing the text as this is "
                         "the way to test the text";
    std::string filter   = "the ";
    std::string expected = "This is text with a lot of \"the\" words in text "
                           "as of day I am writing text as this is way to test "
                           "text";

    auto filtered = string - filter;

    std::println("string: {}",   string);
    std::println("filter: {}",   filter);
    std::println("filtered: {}", filtered);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(filtered, expected);

    T_END;
}

/**
 *  @brief  Test SM operators' operator- (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_operator_minus_2() -> std::size_t
{
    T_BEGIN;

    std::string string   = "This is a very unreadable text because";
    char        filter   = ' ';
    std::string expected = "Thisisaveryunreadabletextbecause";

    auto filtered = string - filter;

    std::println("string: {}",   string);
    std::println("filter: '{}'", filter);
    std::println("filtered: {}", filtered);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(filtered, expected);

    T_END;
}

/**
 *  @brief  Test SM operators' operator* (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_operator_star_1() -> std::size_t
{
    T_BEGIN;

    std::string string   = "Spam. ";
    std::size_t repeat   = 10;
    std::string expected = "Spam. Spam. Spam. Spam. Spam. "
                           "Spam. Spam. Spam. Spam. Spam. ";

    auto repeated = string * repeat;

    std::println("string: {}",   string);
    std::println("repeat: {}",   repeat);
    std::println("repeated: {}", repeated);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(repeated, expected);

    T_END;
}

/**
 *  @brief  Test SM operators' operator* (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_operator_star_2() -> std::size_t
{
    T_BEGIN;

    std::string string = "Spam. ";
    long double repeat = 10.0 - 1.0 / 6.0 // 9.83333333333333
                       + std::numeric_limits<float>::epsilon();
    std::string expected = "Spam. Spam. Spam. Spam. Spam. "
                           "Spam. Spam. Spam. Spam. Spam.";

    auto repeated = string * repeat;

    std::println("string: {}",   string);
    std::println("repeat: {}",   repeat);
    std::println("repeated: {}", repeated);
    std::println("expected: {}", expected);

    T_ASSERT_CTR(repeated, expected);

    T_END;
}

/**
 *  @brief  Test SM operators' operator/ (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_operator_slash_1() -> std::size_t
{
    T_BEGIN;

    std::string string = "This is the text with the once again a lot of the "
                         "words in the text as of the day I am writing the "
                         "text as this is the way to test the text";
    std::string pattern  = "the ";
    std::vector expected = {
        "This is "s,         "text with "s,   "once again a lot of "s,
        "words in "s,        "text as of "s,  "day I am writing "s,
        "text as this is "s, "way to test "s, "text"s
    };

    auto splitted = string / pattern;

    std::println("string: {}",  string);
    std::println("pattern: {}", pattern);

    T_ASSERT_SIZE(splitted, expected);

    for (std::size_t i = 0; i < splitted.size(); i++)
    {
        std::println("splitted[{}]: {}", i, splitted[i]);
    }

    for (std::size_t i = 0; i < expected.size(); i++)
    {
        std::println("expected[{}]: {}", i, expected[i]);
    }

    T_ASSERT_NEST_CTR(splitted, expected);

    T_END;
}

/**
 *  @brief  Test SM operators' operator/ (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_sm_operator_slash_2() -> std::size_t
{
    T_BEGIN;

    std::string string = "This is the text with the once again a lot of the "
                         "words in the text as of the day I am writing the "
                         "text as this is the way to test the text";
    char        splitter = ' ';
    std::vector expected = {
        "This"s,  "is"s,      "the"s, "text"s, "with"s, "the"s,   "once"s,
        "again"s, "a"s,       "lot"s, "of"s,   "the"s,  "words"s, "in"s,
        "the"s,   "text"s,    "as"s,  "of"s,   "the"s,  "day"s,   "I"s,
        "am"s,    "writing"s, "the"s, "text"s, "as"s,   "this"s,  "is"s,
        "the"s,   "way"s,     "to"s,  "test"s, "the"s,  "text"s
    };

    auto splitted = string / splitter;

    std::println("string: {}",   string);
    std::println("splitter: {}", splitter);

    T_ASSERT_SIZE(splitted, expected);

    for (std::size_t i = 0; i < splitted.size(); i++)
    {
        std::println("splitted[{}]: {}", i, splitted[i]);
    }

    for (std::size_t i = 0; i < expected.size(); i++)
    {
        std::println("expected[{}]: {}", i, expected[i]);
    }

    T_ASSERT_NEST_CTR(splitted, expected);

    T_END;
}

/**
 *  @brief  Test String Manipulators.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_sm() -> std::size_t
{
    test_suite suite;
    suite.pre_run  = default_pre_runner('=', 3);
    suite.post_run = default_post_runner('=', 3);
    // suite.run_failed = default_run_failed_quitter();

    // Scary memory management

    suite.tests.emplace_back(new test {
        "Test SM's word_wrap function",
        "test_sm_word_wrap",
        test_sm_word_wrap
    });

    suite.tests.emplace_back(new test {
        "Test SM's trim_left function",
        "test_sm_trim_left",
        test_sm_trim_left
    });

    suite.tests.emplace_back(new test {
        "Test SM's trim_right function",
        "test_sm_trim_right",
        test_sm_trim_right
    });

    suite.tests.emplace_back(new test {
        "Test SM's trim function",
        "test_sm_trim",
        test_sm_trim
    });

    suite.tests.emplace_back(new test {
        "Test SM's trim_to_upper function (overload 1)",
        "test_sm_to_upper_1",
        test_sm_to_upper_1
    });

    suite.tests.emplace_back(new test {
        "Test SM's trim_to_lower function (overload 1)",
        "test_sm_to_lower_1",
        test_sm_to_lower_1
    });

    suite.tests.emplace_back(new test {
        "Test SM's trim_to_upper function (overload 2)",
        "test_sm_to_upper_2",
        test_sm_to_upper_2
    });

    suite.tests.emplace_back(new test {
        "Test SM's trim_to_lower function (overload 2)",
        "test_sm_to_lower_2",
        test_sm_to_lower_2
    });

    suite.tests.emplace_back(new test {
        "Test SM's is_equal_ins function (overload 1)",
        "test_sm_is_equal_ins_1",
        test_sm_is_equal_ins_1
    });

    suite.tests.emplace_back(new test {
        "Test SM's is_equal_ins function (overload 2)",
        "test_sm_is_equal_ins_2",
        test_sm_is_equal_ins_2
    });

    suite.tests.emplace_back(new test {
        "Test SM operators' operator- (overload 1)",
        "test_sm_operator_minus_1",
        test_sm_operator_minus_1
    });

    suite.tests.emplace_back(new test {
        "Test SM operators' operator- (overload 2)",
        "test_sm_operator_minus_2",
        test_sm_operator_minus_2
    });

    suite.tests.emplace_back(new test {
        "Test SM operators' operator- (overload 1)",
        "test_sm_operator_star_1",
        test_sm_operator_star_1
    });

    suite.tests.emplace_back(new test {
        "Test SM operators' operator- (overload 2)",
        "test_sm_operator_star_2",
        test_sm_operator_star_2
    });

    suite.tests.emplace_back(new test {
        "Test SM operators' operator- (overload 1)",
        "test_sm_operator_slash_1",
        test_sm_operator_slash_1
    });

    suite.tests.emplace_back(new test {
        "Test SM operators' operator- (overload 2)",
        "test_sm_operator_slash_2",
        test_sm_operator_slash_2
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
