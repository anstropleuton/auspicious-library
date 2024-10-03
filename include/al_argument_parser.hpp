/**
 *  @file    al_argument_parser.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Functionality to parse Command Line Arguments.
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

#pragma once

#include <print>
#include <string>
#include <vector>

#include "al_ansi_escape_codes.hpp"
#include "al_container_utilities.hpp"
#include "al_string_manipulators.hpp"

/**
 *  @brief  All Auspicious Library's contents in this namespace.  Just do
 *          `using namespace auspicious_library` to make your life easier.
 */
namespace auspicious_library {

/**
 *  @brief  Command line argument parser.
 *
 *  This supports both the new POSIX-style arguments and the old Microsoft-style
 *  arguments.  Each argument from the command line is parsed and is also
 *  modified internally for interpretation.
 *
 *  New POSIX-style arguments:
 *  - Long Argument: Each long argument starts with two hyphen ("--") and
 *    consists of one or more characters for recognition.  Such as
 *    "--long-argument".  The allowed characters are not an "=" sign or a ":"
 *    symbol.  If used, the behavior is undefined.
 *  - Short Argument: Each short argument starts with one hyphen ("-") and
 *    consists of one character for recognition.  Such as
 *    "-a".  If multiple characters are found, such as "-abc", it internally
 *    splits each character as its own separate short arguments, such as
 *    "-a", "-b", "-c".  The allowed characters are not an "=" sign or a ":"
 *    symbol.  If used, the behavior is undefined.
 *  - Use of a "--" with no additional characters indicates end of parsing and
 *    rest of the arguments are unparsed.
 *
 *  Old Microsoft-style arguments:
 *  - There is no dedicated section for the old Microsoft-style arguments, often
 *    known as "switches".
 *  - Instead, each switch is treated as a long option if the switch is more
 *    than one character for recognition, such as "/switch".
 *  - If a switch is one character for recognition, such as "/s", it is treated
 *    both as a long option and a short option (short name is matched first).
 *  - If a switch is not matched, you can optionally make it try to match case
 *    insensitively.
 *
 *  In both cases, arguments that contain an '=' sign or a ':' symbol, such as
 *  --option=value, -o:value, /switch=value or /s:value, are internally split
 *  with the first found '=' sign or ':' symbol.  This is only done when the
 *  option or switch is defined to have parameters.
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
 *
 *  @todo  Proper internationalization support?  Currently std::string is used,
 *         which is a string of char, char cannot hold any more than 1 byte.
 *         Hence internal counting characters will count the multi-byte
 *         character and international characters for short option is out of the
 *         window.
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
     *  @see  Detailed Description of namespace @c ap.
     *
     *  @note  It is recommended that each name be at least 2 characters long.
     *         This is to prevent name clashing for Microsoft-styled switches.
     *         If you do however have a long option of 1 character, it is not
     *         guaranteed whether the short name is matched first, or the long
     *         name.
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
     *  @see  Detailed Description of namespace @c ap.
     *
     *  @note  When variadic parameter is used, @c defaults_from_back is ignored
     *         entirely.
     */
    std::vector<std::string> parameters;

    /**
     *  @brief  Default values for parameters from back, in forward
     *          order.
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
     *  @see  option_template::names.
     */
    std::vector<std::string> names;

    /**
     *  @brief  Name of parameters required by the subcommand, such as
     *          "filename".
     *  @see  option_template::parameters.
     */
    std::vector<std::string> parameters;

    /**
     *  @brief  Default values for parameters from back, in forward
     *          order.
     *  @see  option_template::defaults_from_back.
     */
    std::vector<std::string> defaults_from_back;

    /**
     *  @brief  Subcommands for this subcommand (nesting).
     *  @note  When this vector is not empty, @c parameters is ignored
     *         entirely.
     */
    std::vector<const subcommand_template *> subcommands;

    /**
     *  @brief  Subcommand specific options/switches.
     *  @note  overrides global option/switch.
     */
    std::vector<const option_template *> subcommand_options;
};

/**
 *  @brief  Type for argument differentiation.
 */
enum class argument_type {

    /**
     *  @brief  Argument type cannot be determined.
     */
    unknown,

    /**
     *  @brief  Argument is empty.
     */
    empty,

    /**
     *  @brief  Argument is in form of "-a", "-abc=value", etc.
     */
    short_option,

    /**
     *  @brief  Argument is in form of "--argument", "--argument=value", etc.
     */
    long_option,

    /**
     *  @brief  Argument is in form of "/argument", "/argument:value", etc.
     */
    microsoft_switch,

    /**
     *  @brief  Argument is "-".  This is treated just as regular argument.
     */
    single_hyphen,

    /**
     *  @brief  Argument is "--".  End of parsing.
     */
    double_hyphen,

    /**
     *  @brief  Argument is in form of "argument", etc.
     */
    regular_argument
};

/**
 *  @brief  Convert @c argument_type to string.
 *
 *  @param  arg_type  An argument type.
 *  @return  String representing @c argument_type enumeration.
 */
[[nodiscard]] inline constexpr auto to_string(argument_type arg_type)
{
    using namespace std::string_literals;
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
    return ""s;
}

/**
 *  @brief  Get the type of argument from command line argument.
 *
 *  @param  argument  A command line argument.
 *  @return  Argument type.
 */
[[nodiscard]] inline constexpr auto get_argument_type(std::string_view argument)
{
    if (argument.size() == 0) return argument_type::empty;

    if (argument.starts_with("--"))
    {
        if (argument.size() > 2) return argument_type::long_option;
        else return argument_type::double_hyphen;
    }

    if (argument.starts_with("-"))
    {
        if (argument.size() > 1) return argument_type::short_option;
        else return argument_type::single_hyphen;
    }

    if (argument.starts_with("/"))
    {
        return argument_type::microsoft_switch;
    }

    return argument_type::regular_argument;
}

/**
 *  @brief  What type of variadic is the parameter?
 */
enum class variadicity {

    /**
     *  @brief  Parameter is not variadic.
     */
    not_variadic,

    /**
     *  @brief  Parameter is "...".
     */
    zero_or_more,

    /**
     *  @brief  Parameter is in form "parameter...".
     */
    one_or_more
};

/**
 *  @brief  Convert @c variadicity to string.
 *
 *  @param  variadic  The variadicity enum.
 *  @return  String representing @c variadicity enumeration.
 */
[[nodiscard]] inline constexpr auto to_string(variadicity variadic)
{
    using namespace std::string_literals;
    switch (variadic)
    {
        case variadicity::not_variadic: return "not_variadic"s;
        case variadicity::zero_or_more: return "zero_or_more"s;
        case variadicity::one_or_more: return "one_or_more"s;
    }
    return ""s;
}

/**
 *  @brief  Check if a parameter is variadic.
 *
 *  @param  parameter  A parameter.
 *  @return  True if a parameter is variadic.
 */
[[nodiscard]] inline constexpr auto is_parameter_variadic(
    std::string_view parameter
)
{
    if (parameter == "...") return variadicity::zero_or_more;
    if (parameter.ends_with("...")) return variadicity::one_or_more;
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

    /**
     *  @brief  Something definitely has gone wrong.
     */
    unknown,

    /**
     *  @brief  Everything that can go right, gone right.
     */
    valid,

    /**
     *  @brief  Option is unrecognized.
     */
    unrecognized_option,

    /**
     *  @brief  Subcommand is unrecognized.
     */
    unrecognized_subcommand,

    /**
     *  @brief  Option or subcommand's parameters requirement is not met.
     */
    not_enough_values
};

/**
 *  @brief  Convert @c validity to string.
 *
 *  @param  valid  The validity enum.
 *  @return  String representing @c validity enumeration.
 */
[[nodiscard]] inline constexpr auto to_string(validity valid)
{
    using namespace std::string_literals;
    switch (valid)
    {
        case validity::unknown: return "unknown"s;
        case validity::valid: return "valid"s;
        case validity::unrecognized_option: return "unrecognized_option"s;
        case validity::unrecognized_subcommand: return
                "unrecognized_subcommand"s;
        case validity::not_enough_values: return "not_enough_values"s;
    }
    return ""s;
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
 *  @see  Detailed Description of namespace @c ap.
 *
 *  @param  args         All excluding the first (usually program name) command
 *                       line arguments.
 *  @param  options      All options/switches.
 *  @param  subcommands  All subcommands.
 *  @param  switch_ins   Whether to match Microsoft-style switches case
 *                       insensitively (optional).
 *  @return  Parsed argument information.
 *
 *  @exception  std::invalid_argument  Thrown in the following cases:
 *   - When a pointer is null.
 *   - When there are more @c defaults_from_back than @c parameters.
 *   - When @c parameters is variadic, and default values are provided.
 *   - When @c parameters is variadic, and subcommands are provided.
 *   - When a non-last parameter is variadic.
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
 *  @see  Detailed Description of namespace @c ap.
 *
 *  @param  argc         The arguments count from main().
 *  @param  argv         The argument values from main().
 *  @param  options      All options/switches.
 *  @param  subcommands  All subcommands.
 *  @param  switch_ins   Whether to match Microsoft-style switches case
 *                       insensitively (optional).
 *  @return  Parsed argument information.
 *
 *  @exception  std::invalid_argument  Thrown in the following cases:
 *   - When a pointer is null.
 *   - When there are more @c defaults_from_back than @c parameters.
 *   - When @c parameters is variadic, and default values are provided.
 *   - When @c parameters is variadic, and subcommands are provided.
 *   - When a non-last parameter is variadic.
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
 *  @brief  String where it's size is independent from the style.  Useful to
 *          avoid counting ANSI Escape Code characters when calculating length.
 */
struct measured_string {

    /**
     *  @brief  String content with ANSI Escape Code.
     */
    std::string string;

    /**
     *  @brief  Size of the string without calculating ANSI Escape Code.
     */
    std::size_t size;

    /**
     *  @brief  Default constructor.
     */
    inline constexpr measured_string() = default;

    /**
     *  @brief  Create measured string with string and size.
     *
     *  @param  string  A string.
     *  @param  size    The size of string without accounting ANSI Escape Codes.
     */
    inline constexpr measured_string(std::string_view string, std::size_t size)
        : string(string), size(size) {}

    /**
     *  @brief  Create measured string by applying ANSI Escape Code.
     *
     *  @param  code    The ANSI Escape Code to apply.
     *  @param  string  THe content to apply ANSI Escape Code.
     */
    inline constexpr measured_string(aec::aec_t code, std::string_view string)
        : string(code(string)), size(string.size()) {}

    /**
     *  @brief  Add two measured string.
     *
     *  @param  other  The other measured string.
     *  @return  A reference to self.
     */
    inline constexpr auto operator+= (
        const measured_string &other
    ) -> measured_string &
    {
        string += other.string;
        size   += other.size;
        return *this;
    }

    /**
     *  @brief  Add two measured string.
     *
     *  @param  a  The first measured string.
     *  @param  b  The first measured string.
     *  @return  New measured string representing added measured string.
     */
    [[nodiscard]] friend inline constexpr auto operator+ (
        const measured_string &a,
        const measured_string &b
    )
    {
        return measured_string(a.string + b.string, a.size + b.size);
    }
};

/**
 *  @brief  Keep string and AEC separate for measurement purposes, for help
 *          message format.
 */
struct styled_text {

    /**
     *  @brief  Value to use.
     */
    std::string value;

    /**
     *  @brief  Style applied for value.
     */
    aec::aec_t style;

    /**
     *  @brief  Get the string that is enclosed by the style.
     *  @return  String enclosed by style.
     */
    [[nodiscard]] inline constexpr auto str() const
    {
        return style(value);
    }

    /**
     *  @brief  Get the number of characters in value field, without counting
     *          any ANSI Escape Code characters.
     *  @return  The number of characters in value field.
     */
    [[nodiscard]] inline constexpr auto size() const
    {
        return value.size();
    }

    /**
     *  @brief  Get a measured string representing styled text.
     *  @return  Measured string representing styled text.
     */
    [[nodiscard]] inline constexpr auto m_str() const
    {
        return measured_string(str(), size());
    }
};

/**
 *  @brief  Padding before the content, for help message format.
 */
struct styled_padding {

    /**
     *  @brief  Use this for first padding value.
     */
    styled_text first;

    /**
     *  @brief  Use this for padding value.
     */
    styled_text mid;

    /**
     *  @brief  Use this for last padding value.
     */
    styled_text last;

    /**
     *  @brief  Number of times to pad with value.
     *
     *  1  -> Use only the mid.
     *  2  -> Use first and then last.
     *  3+ -> Use first, n-2 times mid and then last.
     */
    std::size_t width;

    /**
     *  @brief  Get the string that represents the padding.
     *
     *  @param  subtract  Modify the width by subtracting (optional).
     *  @return  The string that represents the padding.
     */
    [[nodiscard]] inline constexpr auto str(std::size_t subtract = 0) const
    {
        using namespace std::string_literals;
        if (subtract > width)
        {
            return ""s;
        }

        std::size_t actual_size = width - subtract;
        if (actual_size == 0)
        {
            return ""s;
        }
        if (actual_size == 1)
        {
            return mid.style(mid.value);
        }
        if (actual_size == 2)
        {
            return first.style(first.value)
                 + last.style(last.value);
        }
        return first.style(first.value)
             + mid.style(sm::repeat(mid.value, actual_size))
             + last.style(last.value);
    }

    /**
     *  @brief  Get the number of characters that are used for padding.
     *
     *  @param  subtract  Modify the width by subtracting (optional).
     *  @return  Number of characters that are used for padding.
     */
    [[nodiscard]] inline constexpr auto size(std::size_t subtract = 0) const
    {
        if (subtract > width)
        {
            return 0zu;
        }

        std::size_t actual_size = width - subtract;
        if (actual_size == 0)
        {
            return 0zu;
        }
        if (actual_size == 1)
        {
            return mid.value.size();
        }
        if (actual_size == 2)
        {
            return first.value.size()
                 + last.value.size();
        }
        return first.value.size()
             + mid.value.size() * actual_size
             + last.value.size();
    }

    /**
     *  @brief  Get a measured string representing padding.
     *
     *  @param  subtract  Modify the width by subtracting (optional).
     *  @return  Measured string representing padding.
     */
    [[nodiscard]] inline constexpr auto m_str(std::size_t subtract = 0) const
    {
        return measured_string(str(subtract), size(subtract));
    }
};

/**
 *  @brief  Surround the content with prefix/suffix, for help message format.
 */
struct styled_enclosure {

    /**
     *  @brief  Prefix value before content.
     */
    styled_text prefix;

    /**
     *  @brief  Suffix value after content.
     */
    styled_text suffix;

    /**
     *  @brief  Style for enclosed value.
     */
    aec::aec_t value_style;

    /**
     *  @brief  Apply enclosure to content.
     *
     *  @param  content  The content to apply enclosure to.
     *  @return  A string with enclosure applied.
     */
    [[nodiscard]] inline constexpr auto str(std::string_view content) const
    {
        return prefix.str() + value_style(content) + suffix.str();
    }

    /**
     *  @brief  Get the number of characters for enclosure.
     *
     *  @param  content  The content to calculate size for enclosure.
     *  @return  Number of characters for enclosure.
     */
    [[nodiscard]] inline constexpr auto size(std::string_view content) const
    {
        return prefix.size() + content.size() + suffix.size();
    }

    /**
     *  @brief  Get a measured string representing enclosed text.
     *
     *  @param  content  The content to apply enclosure to.
     *  @return  Measured string representing enclosed text.
     */
    [[nodiscard]] inline constexpr auto m_str(std::string_view content) const
    {
        return measured_string(str(content), size(content));
    }
};

/**
 *  @brief  POSIX-style format specifier for help message.
 */
struct posix_help_format {

    /**
     *  @brief  Padding before short names.
     */
    styled_padding pad_short_names = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 2
    };

    /**
     *  @brief  Padding before long names.
     */
    styled_padding pad_long_names = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 6
    };

    /**
     *  @brief  Padding before subcommand names.
     */
    styled_padding pad_subcommand = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 4
    };

    /**
     *  @brief  Padding before wrapped parameters.
     */
    styled_padding pad_parameters_wrapped = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 6
    };

    /**
     *  @brief  Padding before description.
     */
    styled_padding pad_description = {

        .first = { " ", aec::reset },
        .mid   = { ".", aec::reset },
        .last  = { " ", aec::reset },
        .width = 40
    };

    /**
     *  @brief  Description padding when the description is wrapped around.
     */
    styled_padding pad_description_wrapped = {

        .first = { " ",  aec::reset  },
        .mid   = { " ",  aec::reset  },
        .last  = { ". ", aec::reset  },
        .width = 39 // Note the two characters in the `last` field
    };

    /**
     *  @brief  Style for the "-" prefix before the short name.
     */
    aec::aec_t short_name_prefix_style = aec::reset;

    /**
     *  @brief  Style for the short name.
     */
    aec::aec_t short_name_style = aec::reset;

    /**
     *  @brief  Style for the "--" prefix before the long name.
     */
    aec::aec_t long_name_prefix_style = aec::reset;

    /**
     *  @brief  Style for the long name.
     */
    aec::aec_t long_name_style = aec::reset;

    /**
     *  @brief  Separation between each short names.
     */
    styled_text short_name_separator = { ", ", aec::reset };

    /**
     *  @brief  Separation between each long names.
     */
    styled_text long_name_separator = { ", ", aec::reset };

    /**
     *  @brief  Separation between short names and long names.
     */
    styled_text short_n_long_name_separator = { ", ", aec::reset };

    /**
     *  @brief  Style for the subcommand name.
     */
    aec::aec_t subcommand_style = aec::reset;

    /**
     *  @brief  Separation between each subcommand names.
     */
    styled_text subcommand_separator = { "|", aec::reset };

    /**
     *  @brief  Prefix before the first parameter name.
     */
    styled_text parameter_prefix_first = { "=", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    styled_text parameter_prefix = { "", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    aec::aec_t parameter_style = aec::reset;

    /**
     *  @brief  Separation between each parameter name.
     */
    styled_text parameter_separator = { " ", aec::reset };

    /**
     *  @brief  Enclose with this for parameter name with no corresponding
     *          default parameter.
     */
    styled_enclosure mandatory_parameter_enclose = {

        .prefix      = { "", aec::reset },
        .suffix      = { "", aec::reset },
        .value_style = aec::reset
    };

    /**
     *  @brief  Enclose with this for parameter name with a corresponding
     *          default parameter.
     */
    styled_enclosure optional_parameter_enclose = {

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
    styled_padding pad_switch = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 0
    };

    /**
     *  @brief  Padding before subcommand names.
     */
    styled_padding pad_subcommand = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 4
    };

    /**
     *  @brief  Padding before wrapped parameters.
     */
    styled_padding pad_parameters_wrapped = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 6
    };

    /**
     *  @brief  Padding before description.
     */
    styled_padding pad_description = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 8
    };

    /**
     *  @brief  Description padding when the description is wrapped around.
     */
    styled_padding pad_description_wrapped = {

        .first = { " ", aec::reset },
        .mid   = { " ", aec::reset },
        .last  = { " ", aec::reset },
        .width = 8
    };

    /**
     *  @brief  Style for the "/" prefix before the switch name.
     */
    aec::aec_t switch_prefix_style = aec::reset;

    /**
     *  @brief  Style for the switch name.
     */
    aec::aec_t switch_style = aec::reset;

    /**
     *  @brief  Separation between each switch names.
     */
    styled_text switch_separator = { ", ", aec::reset };

    /**
     *  @brief  Style for the subcommand name.
     */
    aec::aec_t subcommand_style = aec::reset;

    /**
     *  @brief  Separation between each subcommand names.
     */
    styled_text subcommand_separator = { "|", aec::reset };

    /**
     *  @brief  Prefix before the first parameter name.
     */
    styled_text parameter_prefix_first = { ":", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    styled_text parameter_prefix = { "", aec::reset };

    /**
     *  @brief  Prefix before the rest of the parameter name.
     */
    aec::aec_t parameter_style = aec::reset;

    /**
     *  @brief  Separation between each parameter name.
     */
    styled_text parameter_separator = { " ", aec::reset };

    /**
     *  @brief  Enclose with this for parameter name with no corresponding
     *          default parameter.
     */
    styled_enclosure mandatory_parameter_enclose = {

        .prefix      = { "", aec::reset },
        .suffix      = { "", aec::reset },
        .value_style = aec::reset
    };

    /**
     *  @brief  Enclose with this for parameter name with a corresponding
     *          default parameter.
     */
    styled_enclosure optional_parameter_enclose = {

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
 *  @param  option  An option (not switch).
 *  @param  format  A POSIX-style format.
 *  @return  @c std::vector<std::string> for each line.
 */
[[nodiscard]] auto get_help_message(
    const option_template &option,
    posix_help_format      format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from options and POSIX-style format.
 *
 *  @param  options  The options (not switches).
 *  @param  format   A POSIX-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  options  The options (not switches).
 *  @param  format   A POSIX-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  subcommand  A Subcommand.
 *  @param  format      A POSIX-style format.
 *  @return  @c std::vector<std::string> for each line.
 */
[[nodiscard]] auto get_help_message(
    const subcommand_template &subcommand,
    posix_help_format          format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from subcommands and POSIX-style
 *          format.
 *
 *  @param  subcommands  The subcommands.
 *  @param  format       A POSIX-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  subcommands  The subcommands.
 *  @param  format       A POSIX-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  option  A switch (not option).
 *  @param  format  The Microsoft-style format.
 *  @return  @c std::vector<std::string> for each line.
 */
[[nodiscard]] auto get_help_message(
    const option_template &option,
    microsoft_help_format  format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from options (switches) and
 *          Microsoft-style format.
 *
 *  @param  options  The switches (not options).
 *  @param  format   The Microsoft-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  options  The switches (not options).
 *  @param  format   The Microsoft-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  subcommand  A subcommand.
 *  @param  format      The Microsoft-style format.
 *  @return  @c std::vector<std::string> for each line.
 */
[[nodiscard]] auto get_help_message(
    const subcommand_template &subcommand,
    microsoft_help_format      format
) -> std::vector<std::string>;

/**
 *  @brief  Generate help message string from subcommands and Microsoft-style
 *          format.
 *
 *  @param  subcommands  The subcommands.
 *  @param  format       The Microsoft-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  subcommands  The subcommands.
 *  @param  format       The Microsoft-style format.
 *  @return  @c std::vector<std::string> for each line.
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
 *  @param  lines  The lines obtained by @c get_help_message .
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
