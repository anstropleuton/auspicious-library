/*
 *  @file    test_ap.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of Argument Parser in Auspicious Library.
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

#include <format>
#include <print>
#include <vector>

#define AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN
#include "argument_parser.hpp"
#include "string_manipulators.hpp"
#include "tester.hpp"

namespace al {
using namespace auspicious_library::ap;
using namespace auspicious_library::sm;
} // namespace al
using namespace auspicious_library::sm_operators;

using namespace std::string_literals;
namespace stdr = std::ranges;

/**
 *  @brief  Nothing... Just C-style array length expression that "just works".
 *          This is the peak of C-like code you will ever see in this library.
 *          ... maybe.
 */
#define lenof(array_expr) sizeof ((array_expr)) / sizeof ((array_expr)[0])

/**
 *  @brief  Convert parsed argument to string.
 *
 *  @param  parsed_argument  Parsed Argument.
 *  @return  String representing parsed argument.
 */
[[nodiscard]] inline constexpr auto to_string(
    const al::parsed_argument &parsed_argument
)
{
    return std::format(
        "├── arg:\n"
        "│   ├── original: {}\n"
        "│   │             {}\n"
        "│   └── modified: {}\n"
        "│                 {}\n"
        "├── validity: {}\n"
        "├── parsed? {}\n"
        "├── reference option description: {}\n"
        "├── reference subcommand description: {}\n"
        "└── values: {}\n",
        parsed_argument.argument.original,
        " "s * parsed_argument.argument.org_pos + "^"s
        + "~"s * (parsed_argument.argument.org_size == 0
                  ? 0
                  : parsed_argument.argument.org_size - 1),
        parsed_argument.argument.modified,
        " "s * parsed_argument.argument.mod_pos + "^"s
        + "~"s * (parsed_argument.argument.mod_size == 0
                  ? 0
                  : parsed_argument.argument.mod_size - 1),
        al::to_string(parsed_argument.valid),
        parsed_argument.is_parsed,
        parsed_argument.ref_option
            ? parsed_argument.ref_option->description
            : "(null)"s,
        parsed_argument.ref_subcommand
            ? parsed_argument.ref_option->description
            : "(null)"s,
        al::to_string(parsed_argument.values)
    );
}

/**
 *  @brief  Formatter for parsed argument.
 */
template<>
struct std::formatter<al::parsed_argument> {
    template<typename ParseContext>
    [[nodiscard]] inline constexpr auto parse(ParseContext &pc)
    {
        auto it = pc.begin();
        if (it == pc.end())
        {
            return it;
        }

        // Add format specifiers?

        if (it != pc.end() && *it != '}')
        {
            throw std::format_error("Invalid format for al::parsed_argument");
        }

        return it;
    }

    template<typename FormatContext>
    [[nodiscard]] inline constexpr auto format(
        const al::parsed_argument &parsed_argument, FormatContext &fc) const
    {
        return std::format_to(fc.out(), "\"{}\" (\"{}\")",
            parsed_argument.argument.original,
            parsed_argument.argument.modified);
    }
};

/**
 *  @brief  Compare all values of two parsed arguments.
 *
 *  @param  a  First parsed argument.
 *  @param  b  Second parsed argument.
 *  @return  True if they are equal.
 */
[[nodiscard]] inline constexpr auto compare(
    const al::parsed_argument &a,
    const al::parsed_argument &b
)
{
    return a.argument.original == b.argument.original
        && a.argument.modified == b.argument.modified
        && a.argument.arg_type == b.argument.arg_type
        && a.argument.org_pos == b.argument.org_pos
        && a.argument.org_size == b.argument.org_size
        && a.argument.mod_pos == b.argument.mod_pos
        && a.argument.mod_size == b.argument.mod_size
        && a.valid == b.valid
        && a.is_parsed == b.is_parsed
        && a.ref_option == b.ref_option
        && a.ref_subcommand == b.ref_subcommand
        && a.values == b.values;
}

/**
 *  @brief  Compare all values of two parsed arguments, ignoring the values
 *          member.
 *
 *  @param  a  First parsed argument.
 *  @param  b  Second parsed argument.
 *  @return  True if they are equal, except the values member.
 */
[[nodiscard]] inline constexpr auto compare_no_values(
    const al::parsed_argument &a,
    const al::parsed_argument &b
)
{
    return a.argument.original == b.argument.original
        && a.argument.modified == b.argument.modified
        && a.argument.arg_type == b.argument.arg_type
        && a.argument.org_pos == b.argument.org_pos
        && a.argument.org_size == b.argument.org_size
        && a.argument.mod_pos == b.argument.mod_pos
        && a.argument.mod_size == b.argument.mod_size
        && a.valid == b.valid
        && a.is_parsed == b.is_parsed
        && a.ref_option == b.ref_option
        && a.ref_subcommand == b.ref_subcommand;
}

/**
 *  @brief  Compare the values member of two parsed arguments.
 *
 *  @param  a  First parsed argument.
 *  @param  b  Second parsed argument.
 *  @return  True if values member of them are equal.
 */
[[nodiscard]] inline constexpr auto compare_only_values(
    const al::parsed_argument &a,
    const al::parsed_argument &b
)
{
    return a.values == b.values;
}

/**
 *  @brief  Compare all values of two parsed argument.
 *
 *  @param  a  First parsed argument.
 *  @param  b  Second parsed argument.
 *  @return  True if they are equal.
 */
[[nodiscard]] inline constexpr auto operator== (
    const al::parsed_argument &a,
    const al::parsed_argument &b
)
{
    return compare(a, b);
}

/**
 *  @brief  Option recognition test - Option 1.
 */
al::option_template ot_long_1 = {
    .description        = "OT Long Name 1",
    .long_names         = { "long-name-1" },
    .short_names        = {},
    .parameters         = {},
    .defaults_from_back = {}
};

/**
 *  @brief  Option recognition test - Option 2.
 */
al::option_template ot_long_2 = {
    .description        = "OT Long Name 2",
    .long_names         = { "long-name-2" },
    .short_names        = {},
    .parameters         = {},
    .defaults_from_back = {}
};

/**
 *  @brief  Option recognition test - Option 3.
 */
al::option_template ot_long_3 = {
    .description        = "OT Long Name 3",
    .long_names         = { "long-name-3" },
    .short_names        = {},
    .parameters         = {},
    .defaults_from_back = {}
};

/**
 *  @brief  All test options.
 */
std::vector<const al::option_template *> options = {
    &ot_long_1, &ot_long_2, &ot_long_3
};

/**
 *  @brief  All test subcommands.
 */
std::vector<const al::subcommand_template *> subcommands = {};

/**
 *  @brief  AP Test 0: No arguments test.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_ap_0() -> std::size_t
{
    T_BEGIN;

    const char *argv[] = { "./program" };
    int         argc   = lenof(argv);

    std::vector<std::string>         args(argv + 1, argv + argc);
    std::vector<al::parsed_argument> expected = {};

    auto parsed_1 = al::parse_arguments(argc, argv, options, subcommands);
    auto parsed_2 = al::parse_arguments(args, options, subcommands);

    std::println("args: {}",        al::to_string(args));
    std::println("parsed_1:\n{}\n", al::to_string(parsed_1, to_string, "\n"));
    std::println("parsed_2:\n{}\n", al::to_string(parsed_2, to_string, "\n"));
    std::println("expected:\n{}\n", al::to_string(expected, to_string, "\n"));

    T_ASSERT_CTR(parsed_1, expected);
    T_ASSERT_CTR(parsed_2, expected);

    T_END;
}

/**
 *  @brief  AP Test 1.1: Option recognition test: Long name 1.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_ap_1_1() -> std::size_t
{
    T_BEGIN;

    std::vector args     = { "--long-name-1"s };
    std::vector expected = {
        al::parsed_argument {
            .argument     = {
                .original = "--long-name-1",
                .modified = "--long-name-1",
                .arg_type = al::argument_type::long_option,
                .org_pos  =                              0,
                .org_size = "--long-name-1"s.size(),
                .mod_pos  =                              0,
                .mod_size = "--long-name-1"s.size()
            },
            .valid          = al::validity::valid,
            .is_parsed      = true,
            .ref_option     = &ot_long_1,
            .ref_subcommand = nullptr,
            .values         = {}
        }
    };

    auto parsed = al::parse_arguments(args, options, subcommands);

    std::println("args: {}",        al::to_string(args));
    std::println("parsed_2:\n{}\n", al::to_string(parsed, to_string, "\n"));
    std::println("expected:\n{}\n", al::to_string(expected, to_string, "\n"));

    T_ASSERT_CTR(parsed, expected);

    T_END;
}

/**
 *  @brief  AP Test 1.2: Option recognition test: Long name 2.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_ap_1_2() -> std::size_t
{
    T_BEGIN;

    std::vector args     = { "--long-name-2"s };
    std::vector expected = {
        al::parsed_argument {
            .argument     = {
                .original = "--long-name-2",
                .modified = "--long-name-2",
                .arg_type = al::argument_type::long_option,
                .org_pos  =                              0,
                .org_size = "--long-name-2"s.size(),
                .mod_pos  =                              0,
                .mod_size = "--long-name-2"s.size()
            },
            .valid          = al::validity::valid,
            .is_parsed      = true,
            .ref_option     = &ot_long_2,
            .ref_subcommand = nullptr,
            .values         = {}
        }
    };

    auto parsed = al::parse_arguments(args, options, subcommands);

    std::println("args: {}",        al::to_string(args));
    std::println("parsed_2:\n{}\n", al::to_string(parsed, to_string, "\n"));
    std::println("expected:\n{}\n", al::to_string(expected, to_string, "\n"));

    T_ASSERT_CTR(parsed, expected);

    T_END;
}

/**
 *  @brief  AP Test 1.3: Option recognition test: Long name 2 and 3.
 *  @return  Number of errors.
 */
[[nodiscard]] static auto test_ap_1_3() -> std::size_t
{
    T_BEGIN;

    std::vector args     = { "--long-name-2"s, "--long-name-3"s };
    std::vector expected = {
        al::parsed_argument {
            .argument     = {
                .original = "--long-name-2",
                .modified = "--long-name-2",
                .arg_type = al::argument_type::long_option,
                .org_pos  =                              0,
                .org_size = "--long-name-2"s.size(),
                .mod_pos  =                              0,
                .mod_size = "--long-name-2"s.size()
            },
            .valid          = al::validity::valid,
            .is_parsed      = true,
            .ref_option     = &ot_long_2,
            .ref_subcommand = nullptr,
            .values         = {}
        },
        al::parsed_argument {
            .argument     = {
                .original = "--long-name-3",
                .modified = "--long-name-3",
                .arg_type = al::argument_type::long_option,
                .org_pos  =                              0,
                .org_size = "--long-name-3"s.size(),
                .mod_pos  =                              0,
                .mod_size = "--long-name-3"s.size()
            },
            .valid          = al::validity::valid,
            .is_parsed      = true,
            .ref_option     = &ot_long_3,
            .ref_subcommand = nullptr,
            .values         = {}
        }
    };

    auto parsed = al::parse_arguments(args, options, subcommands);

    std::println("args: {}",        al::to_string(args));
    std::println("parsed_2:\n{}\n", al::to_string(parsed, to_string, "\n"));
    std::println("expected:\n{}\n", al::to_string(expected, to_string, "\n"));

    T_ASSERT_CTR(parsed, expected);

    T_END;
}

/**
 *  @brief  Test Argument Parser.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_ap() -> std::size_t
{
    test_suite suite;
    suite.pre_run  = default_pre_runner('=', 3);
    suite.post_run = default_post_runner('=', 3);
    // suite.run_failed = default_run_failed_quitter();

    // Scary memory management

    suite.tests.emplace_back(new test {
        "AP Test 0: No arguments test",
        "test_ap_0",
        test_ap_0
    });

    suite.tests.emplace_back(new test {
        "AP Test 1.1: Option recognition test: Long name 1",
        "test_ap_1_1",
        test_ap_1_1
    });

    suite.tests.emplace_back(new test {
        "AP Test 1.2: Option recognition test: Long name 2",
        "test_ap_1_2",
        test_ap_1_2
    });

    suite.tests.emplace_back(new test {
        "AP Test 1.3: Option recognition test: Long name 2 and 3",
        "test_ap_1_3",
        test_ap_1_3
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
