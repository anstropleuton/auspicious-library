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
#if !defined(AUSPICIOUS_LIBRARY_HPP_INCLUDED) \
 && !defined(AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN)
    #warning Its recommended to include auspicious_library.hpp instead.
#endif // ifndef AUSPICIOUS_LIBRARY_HPP_INCLUDED

#include <print>
#include <string>
#include <vector>

#include "ansi_escape_codes.hpp"
#include "container_utilities.hpp"

/**
 *  @brief  All Auspicious Library's contents in this namespace. Do not
 *          `using namespace auspicious_library;`.  Instead, use this:
    ```cpp
    namespace al {
    using namespace auspicious_library::aec;
    using namespace auspicious_library::ap;
    using namespace auspicious_library::cu;
    using namespace auspicious_library::sm;
    }
    using namespace auspicious_library::aec_operators;
    using namespace auspicious_library::cu_operators;
    using namespace auspicious_library::sm_operators;
    ```
 */
namespace auspicious_library {

using namespace std::string_literals;

/**
 *  @brief  Command line argument parser.
 *
 *  This supports both the new POSIX-style arguments and the old Microsoft-style
 *  arguments.  Each argument from the command line is parsed and is also
 *  modified internally for interpretation.
 *
 *  New POSIX-style arguments:
 *  - Long Argument: Each long argument starts with two hyphen (`--`) and
 *    consists of one or more characters for recognition.  Such as
 *    `--long-argument`.  The allowed characters are not an `=` sign or a `:`
 *    symbol.  If used, the behavior is undefined.
 *  - Short Argument: Each short argument starts with one hyphen (`-`) and
 *    consists of one character for recognition.  Such as
 *    `-a`.  If multiple characters are found, such as `-abc`, it internally
 *    splits each character as its own separate short arguments, such as
 *    `-a`, `-b`, `-c`.  The allowed characters are not an `=` sign or a `:`
 *    symbol.  If used, the behavior is undefined.
 *  - Use of a `--` with no additional characters indicates end of parsing and
 *    rest of the arguments are unparsed.
 *
 *  Old Microsoft-style arguments:
 *  - There is no dedicated section for the old Microsoft-style arguments, often
 *    known as "switches".
 *  - Instead, each switch is treated as a long option if the switch is more
 *    than one character for recognition, such as `/switch`.
 *  - If a switch is one character for recognition, such as `/s`, it is treated
 *    both as a long option and a short option (short name is matched first).
 *  - If a switch is not matched, you can optionally make it try to match case
 *    insensitively.
 *
 *  In both cases, arguments that contain an `=` sign or a `:` symbol, such as
 *  --option=value, -o:value, /switch=value or /s:value, are internally split
 *  from with the first found `=` sign or `:` symbol.
 *
 *  Each option or switch can have one or more value parameter.  Each argument
 *  after an option or switch that do contain value parameter will be treated as
 *  the value to associate with an option or a switch.  If an argument that is
 *  to be treated as a value looked like an option or a switch, it will not be
 *  treated as value associated to the previously appeared option or switch. In
 *  that case, if default argument is provided, it will use that.
 *  For example, let's say you have parameter as such:
    ```cpp
    password_add_option.parameters = {
        "id", "password", "encryption-key", "require-password-to-decrypt"
    };
    ```
 *  And you want to have default value for "encryption-key" and
 *  "require-password-to-decrypt" parameter.  You would define as such:
    ```cpp
    password_add_option.defaults_from_back = {
        "DEFAULT_ENCRYPTION_KEY", "false"
    };
    ```
 *  This will make ID and Password parameter as a mandatory parameter.
 *  @see  option_template.
 *
 *  You can use "..." as the last parameter if you want variadic parameters.
 *  i.e., all parameters not detected as option will be added to this vector.
 *  Use "parameter-name..." if you want to have at least one value.
 */
namespace ap {

/**
 *  @brief  Predefined option.
 */
struct option_template {

    /**
     *  @brief  Option usage description.
     */
    std::string description;

    /**
     *  @brief  Long option names, such as "version" for argument "--version".
     *
     *  @see  Detauld Description of namespace @c ap.
     *
     *  @note  It is recommended that each name be at least 2 characters long.
     *         This is to prevent naming clashing for Microsoft-styled switches.
     */
    std::vector<std::string> long_names;

    /**
     *  @brief  Short option name, such as 'v' for argument '-v'.
     */
    std::vector<char> short_names;

    /**
     *  @brief  Name of parameters required by the option/switch, such as
     *          "filename".
     *
     *  @see  Detauld Description of namespace @c ap.
     *
     *  @note  When variadic parameter is used, @c defaults_from_back is ignored
     *         entirely.
     */
    std::vector<std::string> parameters;

    /**
     *  @brief  Default values for parameters from back, in forward
     *          order.
     *
     *  @note  Must be less than or equal to parameters.
     */
    std::vector<std::string> defaults_from_back;
};

/**
 *  @brief  Predefined subcommand.
 */
struct subcommand_template {

    /**
     *  @brief  Subcommand usage description.
     */
    std::string description;

    /**
     *  @brief  Command names, such as "get" for command "program-name get".
     *
     *  @see  option_template::names.
     */
    std::vector<std::string> names;

    /**
     *  @brief  Name of parameters required by the subcommand, such as
     *          "filename".
     *
     *  @see  option_template::parameters.
     */
    std::vector<std::string> parameters;

    /**
     *  @brief  Default values for parameters from back, in forward
     *          order.
     *
     *  @see  option_template::defaults_from_back.
     */
    std::vector<std::string> defaults_from_back;

    /**
     *  @brief  Subcommands for this subcommand (nesting).
     *
     *  @note  When this vector is not empty, @c parameters is ignored
     *         entirely.
     */
    std::vector<const subcommand_template *> subcommands;

    /**
     *  @brief  Subcommand specific options/switches.
     *
     *  @note  overrides global option/switch.
     */
    std::vector<const option_template *> subcommand_options;
};

/**
 *  @brief  Type for argument differentiation.
 */
enum class argument_type {
    unknown,
    empty,
    short_option,
    long_option,
    microsoft_switch,
    single_hyphen, // Not treaded specially, just as regular argument
    double_hyphen,
    regular_argument
};

/**
 *  @brief  Convert @c argument_type to string.
 *
 *  @param  arg_type  Argument type.
 *  @return  String representing @c argument_type enumeration.
 */
[[nodiscard]] inline constexpr auto to_string(argument_type arg_type)
{
    switch (arg_type)
    {
        case argument_type::unknown: return "unknown"s;
        case argument_type::empty: return "empty"s;
        case argument_type::short_option: return "short_option"s;
        case argument_type::long_option: return "long_option"s;
        case argument_type::microsoft_switch: return "microsoft_switch"s;
        case argument_type::single_hyphen: return "single_hyphen"s;
        case argument_type::double_hyphen: return "double_hyphen"s;
        case argument_type::regular_argument: return "regular_argument"s;
    }
}

/**
 *  @brief  Get the type of argument from command line argument.
 *
 *  @param  argument  Command line argument.
 *  @return  Argument type.
 */
[[nodiscard]] inline constexpr auto get_argument_type(std::string_view argument)
{
    // I should probably refactor this to make it more readable rather than
    // making it never-nester-friendly
    if (argument.size() == 0) return argument_type::regular_argument;
    if (argument[0] == '/') return argument_type::microsoft_switch;
    if (argument[0] != '-') return argument_type::regular_argument;
    if (argument.size() == 1) return argument_type::single_hyphen;
    if (argument[1] == '-')
    {
        if (argument.size() == 2) return argument_type::double_hyphen;
        return argument_type::long_option;
    }
    return argument_type::short_option;
}

/**
 *  @brief  What type of variadic is it?
 */
enum class variadicity {
    not_variadic,
    zero_or_more,
    one_or_more
};

/**
 *  @brief  Convert @c variadicity to string.
 *
 *  @param  variadic  Variadicity.
 *  @return  String representing @c variadicity enumeration.
 */
[[nodiscard]] inline constexpr auto to_string(variadicity variadic)
{
    switch (variadic)
    {
        case variadicity::not_variadic: return "not_variadic"s;
        case variadicity::zero_or_more: return "zero_or_more"s;
        case variadicity::one_or_more: return "one_or_more"s;
    }
}

/**
 *  @brief  Check if parameters is variadic.
 *
 *  @param  parameters  Parameters.
 *  @return  True if parameters is variadic.
 */
[[nodiscard]] inline constexpr auto is_parameters_variadic(
    const std::vector<std::string> &parameters
)
{
    if (parameters.empty())
        return variadicity::not_variadic;
    if (parameters.back() == "...")
        return variadicity::zero_or_more;
    if (parameters.back().ends_with("..."))
        return variadicity::one_or_more;
    return variadicity::not_variadic;
}

/**
 *  @brief  Internally modifies arguments but has original argument intact for
 *          reference.
 */
struct mod_argument {

    /**
     *  @brief  Original intact argument.
     */
    std::string original;

    /**
     *  @brief  Internally modified.
     */
    std::string modified;

    /**
     *  @brief  Type of argument.
     */
    argument_type arg_type;

    /**
     *  @brief  Resemble position in original.
     */
    std::size_t org_pos;

    /**
     *  @brief  Resemble size in original.
     */
    std::size_t org_size;

    /**
     *  @brief  Resemble position in modified.
     */
    std::size_t mod_pos;

    /**
     *  @brief  Resemble size in modified.
     */
    std::size_t mod_size;
};

/**
 *  @brief  Parsed argument validity.
 */
enum class validity {
    valid = 0,
    unrecognized_option     = 1,
    unrecognized_subcommand = 2,
    not_enough_values       = 4
};

/**
 *  @brief  Convert @c validity to string.
 *
 *  @param  valid  Validity.
 *  @return  String representing @c validity enumeration.
 */
[[nodiscard]] inline constexpr auto to_string(validity valid)
{
    switch (valid)
    {
        case validity::valid: return "valid"s;
        case validity::unrecognized_option: return "unrecognized_option"s;
        case validity::unrecognized_subcommand: return "unrecognized_subcommand"s;
        case validity::not_enough_values: return "not_enough_values"s;
    }
}

/**
 *  @brief  Parsed argument.
 */
struct parsed_argument {

    /**
     *  @brief  Command line argument, intact and internally modified, as a
     *          reference.
     */
    mod_argument argument;

    /**
     *  @brief  Can contain invalid arguments.
     */
    validity valid;

    /**
     *  @brief  Can be raw if just "--" as argument was found.
     *
     *  @note  @c valid will be set to valid when the argument is not parsed.
     */
    bool is_parsed;

    /**
     *  @brief  Reference to option/switch if this parsed argument belongs to.
     */
    const option_template *ref_option;

    /**
     *  @brief  Reference to subcommand if this parsed argument belongs to.
     */
    const subcommand_template *ref_subcommand;

    /**
     *  @brief  Values for parameters.
     */
    std::vector<std::string> values;
};

/**
 *  @brief  Parse command line arguments.
 *
 *  @see  Detauld Description of namespace @c ap.
 *
 *  @param  args         All excluding first (usually program name) command
 *                       line arguments.
 *  @param  options      Options/Switches.
 *  @param  subcommands  Subcommands.
 *  @param  switch_ins   Match Microsoft-style switches case insensitively
 *                       (optional).
 *  @return  Parsed argument information.
 *
 *  @note  Do not pass dynamically allocated memory directly as @c options or
 *         @c subcommands.  This should point to user managed memory.
 */
[[nodiscard]] auto parse_arguments(
    const std::vector<std::string>                 &args,
    const std::vector<const option_template *>     &options,
    const std::vector<const subcommand_template *> &subcommands,
    bool                                            switch_ins = true
) -> std::vector<parsed_argument>;

/**
 *  @brief  Parse command line arguments.
 *
 *  @see  Detauld Description of namespace @c ap.
 *
 *  @param  argc         Arguments count from main().
 *  @param  argv         Argument values from main().
 *  @param  options      Options.
 *  @param  subcommands  Subcommands.
 *  @param  switch_ins   Match Microsoft-style switches case insensitively
 *                       (optional).
 *  @return  Parsed argument information.
 *
 *  @note  Do not pass dynamically allocated memory directly as @c options or
 *         @c subcommands.  This should point to user managed memory.
 */
[[nodiscard]] inline constexpr auto parse_arguments(
    int                                             argc,
    const char                                    **argv,
    const std::vector<const option_template *>     &options,
    const std::vector<const subcommand_template *> &subcommands,
    bool                                            switch_ins = true
) -> std::vector<parsed_argument>
{
    if (argc == 1) return {};

    return parse_arguments(std::vector<std::string>(argv + 1, argv + argc),
        options, subcommands, switch_ins);
}

/**
 *  @brief  Keep string and AEC separate for measurement purposes, for help
 *          message format.
 */
struct help_combo_t {

    /**
     *  @brief  Value to use.
     */
    std::string value;

    /**
     *  @brief  Style applied for value.
     */
    aec::aec_t style;
};

/**
 *  @brief  Padding before the content, for help message format.
 */
struct help_pad_t {

    /**
     *  @brief  Use this for first padding value.
     */
    help_combo_t first;

    /**
     *  @brief  Use this for padding value.
     */
    help_combo_t mid;

    /**
     *  @brief  Use this for last padding value.
     */
    help_combo_t last;

    /**
     *  @brief  Number of times to pad with value.
     *
     *  1  -> Use only the mid.
     *  2  -> Use first and then last.
     *  2+ -> Use first, n-2 times mid and then last.
     */
    std::size_t size;
};

/**
 *  @brief  Surround the content with values, for help message format.
 */
struct help_enclose_t {

    /**
     *  @brief  Prefix value before content.
     */
    help_combo_t prefix;

    /**
     *  @brief  Suffix value after content.
     */
    help_combo_t suffix;

    /**
     *  @brief  Style for enclosed value.
     */
    aec::aec_t value_style;
};

/**
 *  @brief  POSIX-style format specifier for help message.
 */
struct posix_help_format {

    /**
     *  @brief  Padding before short names.
     */
    help_pad_t pad_short_names = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 2
    };

    /**
     *  @brief  Padding before long names.
     */
    help_pad_t pad_long_names = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 6
    };

    /**
     *  @brief  Padding before subcommand names.
     */
    help_pad_t pad_subcommand = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 4
    };

    /**
     *  @brief  Padding before wrapped parameters.
     */
    help_pad_t pad_parameters_wrapped = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 6
    };

    /**
     *  @brief  Padding before description.
     */
    help_pad_t pad_description = {

        .first = { " ", aec::reset },
        .mid   = { ".", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 40
    };

    /**
     *  @brief  Description padding when the description is wrapped around.
     */
    help_pad_t pad_description_wrapped = {

        .first = { " ",  aec::reset },
        .mid   = { " ",  aec::reset },
        .last  = { ". ", aec::reset },
        .size  = 39 // Note the two characters in the `last` field
    };

    /**
     *  @brief  Style for the `-` prefix before the short name.
     */
    aec::aec_t short_name_prefix_style = aec::reset;

    /**
     *  @brief  Style for the short name.
     */
    aec::aec_t short_name_style = aec::reset;

    /**
     *  @brief  Style for the `--` prefix before the long name.
     */
    aec::aec_t long_name_prefix_style = aec::reset;

    /**
     *  @brief  Style for the long name.
     */
    aec::aec_t long_name_style = aec::reset;

    /**
     *  @brief  Separation between each short names.
     */
    help_combo_t short_name_separator = { ", ", aec::reset };

    /**
     *  @brief  Separation between each long names.
     */
    help_combo_t long_name_separator = { ", ", aec::reset };

    /**
     *  @brief  Separation between short names and long names.
     */
    help_combo_t short_n_long_name_separator = { ", ", aec::reset };

    /**
     *  @brief  Style for the subcommand name.
     */
    aec::aec_t subcommand_style = aec::reset;

    /**
     *  @brief  Separation between each subcommand names.
     */
    help_combo_t subcommand_separator = { "|", aec::reset };

    /**
     *  @brief  Prefix before the first parameter name.
     */
    help_combo_t parameter_prefix_first = { "=", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    help_combo_t parameter_prefix = { "", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    aec::aec_t parameter_style = aec::reset;

    /**
     *  @brief  Separation between each parameter name.
     */
    help_combo_t parameter_separator = { " ", aec::reset };

    /**
     *  @brief  Enclose with this for parameter name with no corresponding
     *          default parameter.
     */
    help_enclose_t mandatory_parameter_enclose = {

        .prefix      = { "", aec::reset },
        .suffix      = { "", aec::reset },
        .value_style = aec::reset
    };

    /**
     *  @brief  Enclose with this for parameter name with a corresponding
     *          default parameter.
     */
    help_enclose_t optional_parameter_enclose = {

        .prefix      = { "[", aec::reset },
        .suffix      = { "]", aec::reset },
        .value_style = aec::reset
    };

    /**
     *  @brief  Enclose parameter name before appending prefix.
     */
    bool enclose_before_prefix = false;

    /**
     *  @brief  List long names first.
     */
    bool long_names_first = false;

    /**
     *  @brief  Wrap around for option (long and short) or subcommand names at
     *          width.
     */
    std::size_t option_n_subcommand_width = 80;

    /**
     *  @brief  Wrap around description at width.
     */
    std::size_t description_width = 40;
};

/**
 *  @brief  Microsoft-style format specifier for help message.
 */
struct microsoft_help_format {

    /**
     *  @brief  Padding before Microsoft-style switch.
     */
    help_pad_t pad_switch = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 0
    };

    /**
     *  @brief  Padding before subcommand names.
     */
    help_pad_t pad_subcommand = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 4
    };

    /**
     *  @brief  Padding before wrapped parameters.
     */
    help_pad_t pad_parameters_wrapped = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 6
    };

    /**
     *  @brief  Padding before description.
     */
    help_pad_t pad_description = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 8
    };

    /**
     *  @brief  Description padding when the description is wrapped around.
     */
    help_pad_t pad_description_wrapped = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .size  = 8
    };

    /**
     *  @brief  Style for the `/` prefix before the switch name.
     */
    aec::aec_t switch_prefix_style = aec::reset;

    /**
     *  @brief  Style for the switch name.
     */
    aec::aec_t switch_style = aec::reset;

    /**
     *  @brief  Separation between each switch names.
     */
    help_combo_t switch_separator = { ", ", aec::reset };

    /**
     *  @brief  Style for the subcommand name.
     */
    aec::aec_t subcommand_style = aec::reset;

    /**
     *  @brief  Separation between each subcommand names.
     */
    help_combo_t subcommand_separator = { "|", aec::reset };

    /**
     *  @brief  Prefix before the first parameter name.
     */
    help_combo_t parameter_prefix_first = { ":", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    help_combo_t parameter_prefix = { "", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    aec::aec_t parameter_style = aec::reset;

    /**
     *  @brief  Separation between each parameter name.
     */
    help_combo_t parameter_separator = { " ", aec::reset };

    /**
     *  @brief  Enclose with this for parameter name with no corresponding
     *          default parameter.
     */
    help_enclose_t mandatory_parameter_enclose = {

        .prefix      = { "", aec::reset },
        .suffix      = { "", aec::reset },
        .value_style = aec::reset
    };

    /**
     *  @brief  Enclose with this for parameter name with a corresponding
     *          default parameter.
     */
    help_enclose_t optional_parameter_enclose = {

        .prefix      = { "[", aec::reset },
        .suffix      = { "]", aec::reset },
        .value_style = aec::reset
    };

    /**
     *  @brief  Enclose parameter name before appending prefix.
     */
    bool enclose_before_prefix = false;

    /**
     *  @brief  List long names as switch first.
     */
    bool long_names_first = false;

    /**
     *  @brief  Make all switch names uppercase.
     */
    bool uppercase_switch_names = true;

    /**
     *  @brief  Wrap around for switch or subcommand names at width.
     */
    std::size_t switch_n_subcommand_width = 80;

    /**
     *  @brief  Wrap around description at width.
     */
    std::size_t description_width = 76;
};

/**
 *  @brief  Generate help message string from option and POSIX-style format.
 *
 *  @param  option  Option.
 *  @param  format  POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] auto get_help_message(
    const option_template &option,
    posix_help_format      format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from options and POSIX-style format.
 *
 *  @param  options  Options.
 *  @param  format   POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<option_template> &options,
    posix_help_format                   format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &option : options)
    {
        result = cu::combine(result, get_help_message(option, format));
    }
    return result;
}

/**
 *  @brief  Generate help message string from options and POSIX-style format.
 *
 *  @param  options  Options.
 *  @param  format   POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<const option_template *> &options,
    posix_help_format                           format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &option : options)
    {
        result = cu::combine(result, get_help_message(*option, format));
    }
    return result;
}

/**
 *  @brief  Generate help message string from subcommand and POSIX-style format.
 *
 *  @param  subcommand  Subcommand.
 *  @param  format      POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] auto get_help_message(
    const subcommand_template &subcommand,
    posix_help_format          format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from subcommands and POSIX-style
 *          format.
 *
 *  @param  subcommands  Subcommands.
 *  @param  format       POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<subcommand_template> &subcommands,
    posix_help_format                       format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &subcommand : subcommands)
    {
        result = cu::combine(result, get_help_message(subcommand, format));
    }
    return result;
}

/**
 *  @brief  Generate help message string from subcommands and POSIX-style
 *          format.
 *
 *  @param  subcommands  Subcommands.
 *  @param  format       POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<const subcommand_template *> &subcommands,
    posix_help_format                               format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &subcommand : subcommands)
    {
        result = cu::combine(result, get_help_message(*subcommand, format));
    }
    return result;
}

/**
 *  @brief  Generate help message string from option (switch) and
 *          Microsoft-style format.
 *
 *  @param  option  Option.
 *  @param  format  Microsoft-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] auto get_help_message(
    const option_template &option,
    microsoft_help_format  format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from options (switches) and
 *          Microsoft-style format.
 *
 *  @param  options  Options.
 *  @param  format   Microsoft-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<option_template> &options,
    microsoft_help_format               format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &option : options)
    {
        result = cu::combine(result, get_help_message(option, format));
    }
    return result;
}

/**
 *  @brief  Generate help message string from options (switches) and
 *          Microsoft-style format.
 *
 *  @param  options  Options.
 *  @param  format   Microsoft-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<const option_template *> &options,
    microsoft_help_format                       format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &option : options)
    {
        result = cu::combine(result, get_help_message(*option, format));
    }
    return result;
}

/**
 *  @brief  Generate help message string from subcommand and Microsoft-style
 *          format.
 *
 *  @param  subcommand  Subcommand.
 *  @param  format      Microsoft-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] auto get_help_message(
    const subcommand_template &subcommand,
    microsoft_help_format      format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from subcommands and Microsoft-style
 *          format.
 *
 *  @param  subcommands  Subcommands.
 *  @param  format       Microsoft-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<subcommand_template> &subcommands,
    microsoft_help_format                   format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &subcommand : subcommands)
    {
        result = cu::combine(result, get_help_message(subcommand, format));
    }
    return result;
}

/**
 *  @brief  Generate help message string from subcommands and Microsoft-style
 *          format.
 *
 *  @param  subcommands  Subcommands.
 *  @param  format       Microsoft-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] inline constexpr auto get_help_message(
    const std::vector<const subcommand_template *> &subcommands,
    microsoft_help_format                           format
) -> std::vector<std::string>
{
    std::vector<std::string> result = {};
    for (auto &subcommand : subcommands)
    {
        result = cu::combine(result, get_help_message(*subcommand, format));
    }
    return result;
}

/**
 *  @brief  Helper to print all the help message lines.
 *  @param  lines  Lines returned by @c get_help_message.
 */
[[nodiscard]] inline constexpr auto print_help_message(
    const std::vector<std::string> &lines
)
{
    for (auto &line : lines)
    {
        std::println("{}", line);
    }
}

} // namespace ap

} // namespace auspicious_library
