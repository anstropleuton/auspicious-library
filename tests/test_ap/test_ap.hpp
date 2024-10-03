/**
 *  @file    test_ap.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of Argument Parser in Auspicious Library.
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
 *  Never-nesters are advised to not take a look at this source file.
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

/**
 *  @brief  Default value for extensive tester.
 *  @see  extensive_test.
 */
#ifndef EXTENSIVE_TEST_VALUE
#define EXTENSIVE_TEST_VALUE false
#endif // EXTENSIVE_TEST_VALUE

/**
 *  @brief  Extensive test performs WAY TOO FUCKING MANY tests for each test.
 *          Be prepared to flood your terminal with test logs.  This is mostly
 *          redundant tests.
 */
[[maybe_unused]] static bool extensive_test = EXTENSIVE_TEST_VALUE;

/**
 *  @brief  Nothing... Just C-style array length expression that "just works".
 *          This is the peak of C-like code you will ever see in this library.
 *          ... maybe.
 */
#define lenof(array_expr) sizeof (array_expr) / sizeof (array_expr)[0]

#include <format>
#include <print>
#include <vector>

#include "tester.hpp"

using namespace sm_operators;

using at  = ap::argument_type;
using vdt = ap::validity;

/**
 *  @brief  Convert option template to string.
 *
 *  @param  option_template  Option template.
 *  @return  String representing option template.
 */
[[nodiscard]] static inline constexpr auto option_to_string(
    const ap::option_template &option_template
)
{
    return std::format(
        "  description: {}\n"
        "  long names: {}\n"
        "  short names: {}\n"
        "  parameters: {}\n"
        "  defaults: {}\n",
        option_template.description,
        sm::to_string(option_template.long_names),
        sm::to_string(option_template.short_names),
        sm::to_string(option_template.parameters),
        sm::to_string(option_template.defaults_from_back)
    );
}

/**
 *  @brief  Convert option template pointer to string.
 *
 *  @param  option_template  Option template pointer.
 *  @return  String representing option template.
 */
[[nodiscard]] static inline constexpr auto option_ptr_to_string(
    const ap::option_template *option_template
)
{
    return option_to_string(*option_template);
}

/**
 *  @brief  Convert parsed argument to string.
 *
 *  @param  parsed_argument  Parsed Argument.
 *  @return  String representing parsed argument.
 */
[[nodiscard]] static inline constexpr auto arg_to_string(
    const ap::parsed_argument &parsed_argument
)
{
    return std::format(
        "  arg: type: {}\n"
        "    original: {}\n"
        "              {}\n"
        "    modified: {}\n"
        "              {}\n"
        "  validity: {}\n"
        "  parsed? {}\n"
        "  option: {}\n"
        "  subcommand: {}\n"
        "  values: {}\n",
        ap::to_string(parsed_argument.argument.arg_type),
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
        ap::to_string(parsed_argument.valid),
        parsed_argument.is_parsed,
        parsed_argument.ref_option
            ? parsed_argument.ref_option->description
            : "(null)"s,
        parsed_argument.ref_subcommand
            ? parsed_argument.ref_subcommand->description
            : "(null)"s,
        sm::to_string(parsed_argument.values)
    );
}

/**
 *  @brief  Formatter for parsed argument.
 */
template<>
struct std::formatter<ap::parsed_argument> {

    /**
     *  @brief  Parse format specifier
     *
     *  @tparam  ParseContext  Parsing context type.
     *  @param   pc            Parsing context.
     *  @return  Iterator to end of format specifier.
     */
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
            throw std::format_error("Invalid format for ap::parsed_argument");
        }

        return it;
    }

    /**
     *  @brief  Format the object and convert to string.
     *
     *  @tparam  FormatContext    Formatting context type.
     *  @param   parsed_argument  Object to convert to string.
     *  @param   fc               Formatting context.
     *  @return  Formatted string representing the object.
     */
    template<typename FormatContext>
    [[nodiscard]] inline constexpr auto format(
        const ap::parsed_argument &parsed_argument, FormatContext &fc) const
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
[[nodiscard]] static inline constexpr auto compare(
    const ap::parsed_argument &a,
    const ap::parsed_argument &b
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
[[nodiscard]] static inline constexpr auto compare_no_values(
    const ap::parsed_argument &a,
    const ap::parsed_argument &b
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
[[nodiscard]] static inline constexpr auto compare_only_values(
    const ap::parsed_argument &a,
    const ap::parsed_argument &b
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
[[nodiscard]] static inline constexpr auto operator== (
    const ap::parsed_argument &a,
    const ap::parsed_argument &b
)
{
    return compare(a, b);
}

/**
 *  @brief  Generate combination of indices from @c min_index up to
 *          @c max_index, and run the function.
 *
 *  @tparam  Func       Type of function.
 *  @tparam  Args       Type of additional arguments to function.
 *  @param   combo      Current combination of indices.
 *  @param   min_index  Min size for indices (inclusive).
 *  @param   max_index  Max size for indices (exclusive).
 *  @param   depth      Current depth of recursion.
 *  @param   func       Function to call with combination.
 *  @param   args       Additional arguments for function call.
 */
template<typename Func, typename... Args>
static auto generate_combo(
    std::vector<std::size_t> &combo,
    std::size_t               min_index,
    std::size_t               max_index,
    std::size_t               depth,
    Func                      func,
    Args &&...                args
)
{
    if (depth == 0)
    {
        func(combo, args...);
        return;
    }

    for (std::size_t i = min_index; i < max_index; i++)
    {
        combo.emplace_back(i);
        generate_combo(combo, min_index, max_index, depth - 1, func, args...);
        combo.pop_back();
    }
}

/**
 *  @brief  Generate multiple combination up to @c max_combos of indices from
 *          @c min_index up to @c max_index, and run the function.
 *
 *  @tparam  Func        Type of function.
 *  @tparam  Args        Type of additional arguments to function.
 *  @param   min_index   Min size for indices (inclusive).
 *  @param   max_index   Max size for indices (exclusive).
 *  @param   max_combos  Min combination (size) of indices (inclusive).
 *  @param   max_combos  Max combination (size) of indices (exclusive).
 *  @param   func        Function to call with combination.
 *  @param   args        Additional arguments for function call.
 */
template<typename Func, typename... Args>
static auto run_combo(
    std::size_t min_index,
    std::size_t max_index,
    std::size_t min_combos,
    std::size_t max_combos,
    Func        func,
    Args &&...  args
)
{
    std::vector<std::size_t> combo = {};
    for (std::size_t i = min_combos; i < max_combos; i++)
    {
        generate_combo(combo, min_index, max_index, i, func, args...);
    }
}

/**
 *  @brief  Helper to test AP with args, options and subcommands.
 *
 *  @param  args      Arguments to test against.
 *  @param  expected  Expected parsed results to compare with.
 *  @return  Number of errors.
 */
[[nodiscard, maybe_unused]] static auto ap_tester(
    const std::vector<std::string>                    &args,
    const std::vector<ap::parsed_argument>            &expected,
    const std::vector<const ap::option_template *>     options,
    const std::vector<const ap::subcommand_template *> subcommands
) -> std::size_t
{
    T_BEGIN;

    auto parsed = ap::parse_arguments(args, options, subcommands);

    logln("args: {}",      sm::to_string(args));
    logln("parsed:\n{}\n", sm::to_string(parsed, arg_to_string, "\n"));
    logln("expected:\n{}\n",
        sm::to_string(expected, arg_to_string, "\n"));

    T_ASSERT_CTR(parsed, expected);

    T_END;
}
