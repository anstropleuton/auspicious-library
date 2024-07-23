/**
 *  @file    al_argument_parser.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Implementations for non-inline functions from
 *           al_argument_parser.hpp.
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

/**
 *  @brief  Prevent warning for directly including module header file.
 */
#define AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN
#include <algorithm>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

#include "al_argument_parser.hpp"
#include "al_string_manipulators.hpp"

namespace ap = auspicious_library::ap;
namespace sm = auspicious_library::sm;
namespace cu = auspicious_library::cu;

using namespace std::string_literals;
using namespace auspicious_library::sm_operators;

/**
 *  @brief  Throw if options/switches are null.
 *
 *  @param  options  Options.
 *  @throw  If options are null.
 */
static inline constexpr auto options_sanity_checker(
    const std::vector<const ap::option_template *> &options
)
{
    for (std::size_t i = 0; i < options.size(); i++)
    {
        auto &option = options[i];
        if (!option)
        {
            throw std::runtime_error(
                std::format("Option cannot be null (at index {})", i)
            );
        }
    }
}

/**
 *  @brief  Throw if subcommands or nested subcommands are null.
 *
 *  @param  subcommands  Subcommands.
 *  @param  level        Nesting level (optional).
 *  @throw  If subcommands or nested subcommands are null.
 */
static inline constexpr auto subcommands_sanity_checker(
    const std::vector<const ap::subcommand_template *> &subcommands,
    std::size_t                                         level = 0
) -> void
{
    for (std::size_t i = 0; i < subcommands.size(); i++)
    {
        auto &subcommand = subcommands[i];
        if (!subcommand)
        {
            throw std::runtime_error(std::format(
                "Subcommand cannot be null (nesting level {})",
                level
            ));
        }

        options_sanity_checker(subcommand->subcommand_options);
        subcommands_sanity_checker(subcommand->subcommands, level + 1);
    }
}

/**
 *  @brief  Check if argument matches the long names of the options/switches.
 *
 *  @param  options    Options.
 *  @param  long_name  Long name to match.
 *  @param  switch_ins  Match Microsoft-style switches case insensitively
 *                      (optional).
 *  @return  Nullable pointer to matched option/switch.
 */
[[nodiscard]] static inline constexpr auto match_long_names(
    const std::vector<const ap::option_template *> &options,
    std::string                                     long_name,
    bool                                            switch_ins = false
) -> const ap::option_template *
{
    for (auto &option : options)
    {
        for (auto &option_long_name : option->long_names)
        {
            if (option_long_name == long_name ||
                (switch_ins && sm::is_equal_ins(option_long_name, long_name)))
            {
                return option;
            }
        }
    }

    return nullptr;
}

/**
 *  @brief  Check if argument matches the short names of the options/switches.
 *
 *  @param  options     Options
 *  @param  short_name  Short name to match.
 *  @param  switch_ins  Match Microsoft-style switches case insensitively
 *                      (optional).
 *  @return  Nullable pointer to matched option/switch.
 */
[[nodiscard]] static inline constexpr auto match_short_names(
    const std::vector<const ap::option_template *> &options,
    char                                            short_name,
    bool                                            switch_ins = false
) -> const ap::option_template *
{
    for (auto &option : options)
    {
        for (auto &option_short_name : option->short_names)
        {
            if (option_short_name == short_name ||
                (switch_ins && sm::is_equal_ins(option_short_name, short_name)))
            {
                return option;
            }
        }
    }

    return nullptr;
}

/**
 *  @brief  Check if argument matches options/switches.
 *
 *  @param  arg         Argument to match options/switches.
 *  @param  arg_type    Argument type.
 *  @param  options     Options.
 *  @param  switch_ins  Match Microsoft-style switches case insensitively
 *                      (optional).
 *  @return  Nullable pointer to matched option/switch.
 */
[[nodiscard]] static inline constexpr auto match_option(
    std::string                                    &arg,
    ap::argument_type                               arg_type,
    const std::vector<const ap::option_template *> &options,
    bool                                            switch_ins
) -> const ap::option_template *
{
    if (arg_type == ap::argument_type::long_option)
    {
        auto long_name = arg.substr(2);
        return match_long_names(options, long_name);
    }
    else if (arg_type == ap::argument_type::short_option)
    {
        auto short_name = arg[1];
        return match_short_names(options, short_name);
    }
    // Match both long names and short names for Microsoft style argument
    // depending on the size of the argument
    else if (arg_type == ap::argument_type::microsoft_switch)
    {
        if (arg.size() == 2)
        {
            auto short_name = arg[1];
            auto match      = match_short_names(options, short_name,
                switch_ins);
            if (match)
            {
                return match;
            }
        }

        auto long_name = arg.substr(1);
        auto match     = match_long_names(options, long_name, switch_ins);
        if (match)
        {
            return match;
        }
    }

    return nullptr;
}

/**
 *  @brief  Check if argument matches subordinate command.
 *
 *  @param  arg                  Argument.
 *  @param  current_subcommands  Currently handling nested subcommands.
 *  @return  Nullable pointer to matched subcommand.
 */
[[nodiscard]] static inline constexpr auto match_subcommand(
    std::string                                        arg,
    const std::vector<const ap::subcommand_template *> current_subcommands
) -> const ap::subcommand_template *
{
    for (auto &subs : current_subcommands)
    {
        for (auto &name : subs->names)
        {
            if (arg == name)
            {
                return subs;
            }
        }
    }

    return nullptr;
}

/**
 *  @brief  Get arguments that are not option or switch, to use as values.
 *
 *  @param  i              Current argument index.
 *  @param  mod_args       All arguments.
 *  @param  parameters     Parameters to collect.
 *  @param  default_args   Default arguments for unprovided arguments.
 *  @return  Collected values.
 */
[[nodiscard]] static inline constexpr auto collect_values(
    std::size_t                        &i,
    const std::vector<ap::mod_argument> mod_args,
    const std::vector<std::string>     &parameters,
    const std::vector<std::string>     &default_args
)
{
    std::vector<std::string> collected_values = {};

    auto is_variadic = ap::is_parameters_variadic(parameters);

    // Refactor this code? I added variadic feature after I made this
    std::size_t j = 0;
    if (is_variadic == ap::variadicity::not_variadic)
    {
        for (; j < parameters.size() && i + j + 1 < mod_args.size(); j++)
        {
            auto &mod_arg = mod_args[i + j + 1];
            if (mod_arg.arg_type != ap::argument_type::regular_argument
             && mod_arg.arg_type != ap::argument_type::single_hyphen)
            {
                break;
            }

            collected_values.emplace_back(mod_arg.original);
        }

        // Assumption: Default Arguments is less than or equal to Additional
        // Arguments
        auto defaults_provided = j - parameters.size() + default_args.size();
        auto first = defaults_provided;
        auto last  = default_args.size();
        if (first < last)
        {
            auto defaults    = cu::subordinate(default_args, first, last);
            collected_values = cu::combine(collected_values, defaults);
        }
    }
    else
    {
        for (; i + j + 1 < mod_args.size(); j++)
        {
            auto &mod_arg = mod_args[i + j + 1];
            if (mod_arg.arg_type != ap::argument_type::regular_argument
             && mod_arg.arg_type != ap::argument_type::single_hyphen)
            {
                break;
            }

            collected_values.emplace_back(mod_arg.original);
        }
    }

    i += j;
    return collected_values;
}

/**
 *  @brief  Parse command line arguments.
 *
 *  @see  Document written on top of this section's namespace.
 *
 *  @param  args         All excluding first (usually program name) command
 *                       line arguments.
 *  @param  options      Options.
 *  @param  subcommands  Subcommands.
 *  @return  Parsed argument information.
 *
 *  @note  Do not pass dynamically allocated memory directly as @c options or
 *         @c subcommands.  This should point to user managed memory.
 */
[[nodiscard]] auto ap::parse_arguments(
    const std::vector<std::string>                 &args,
    const std::vector<const option_template *>     &options,
    const std::vector<const subcommand_template *> &subcommands,
    bool                                            switch_ins
) -> std::vector<parsed_argument>
{
    options_sanity_checker(options);
    subcommands_sanity_checker(subcommands);

    // Split with '=' or ':' based on argument
    std::vector<mod_argument> mod_args_1 = {};
    std::size_t mod_i_1 = 0;
    for (; mod_i_1 < args.size(); mod_i_1++)
    {
        auto         &arg      = args[mod_i_1];
        argument_type arg_type = get_argument_type(arg);
        auto          pos      = std::string::npos;

        if (arg_type == argument_type::double_hyphen)
        {
            break;
        }

        if (arg_type == argument_type::long_option
         || arg_type == argument_type::short_option
         || arg_type == argument_type::microsoft_switch)
        {
            pos = std::min(arg.find_first_of('='), arg.find_first_of(':'));
        }

        if (pos == std::string::npos)
        {
            mod_args_1.emplace_back(
                arg, arg, arg_type, 0, arg.size(), 0, arg.size()
            );
            continue;
        }

        auto first  = arg.substr(0, pos);
        auto second = arg.substr(pos + 1);
        mod_args_1.emplace_back(arg, first, arg_type, 0, pos, 0,
            first.size());
        mod_args_1.emplace_back(arg, second, arg_type, pos + 1, second.size(),
            0, second.size());
    }

    // Unparsed
    for (; mod_i_1 < args.size(); mod_i_1++)
    {
        auto &arg = args[mod_i_1];
        mod_args_1.emplace_back(
            arg, arg, argument_type::unknown, 0, arg.size(), 0, arg.size()
        );
    }

    // Split short options of "-abc" to "-a", "-b", "-c"
    std::vector<mod_argument> mod_args_2 = {};
    std::size_t mod_i_2 = 0;
    for (; mod_i_2 < mod_args_1.size(); mod_i_2++)
    {
        auto &mod_arg = mod_args_1[mod_i_2];
        if (mod_arg.arg_type != argument_type::short_option)
        {
            mod_args_2.emplace_back(mod_arg);
            continue;
        }

        for (std::size_t i = 1; i < mod_arg.modified.size(); i++)
        {
            mod_args_2.emplace_back(mod_arg.original,
                "-"s + mod_arg.modified[i], mod_arg.arg_type,
                mod_arg.org_pos + i, 1, 1, 1);
        }
    }

    // Latest modification
    auto mod_args = mod_args_2;

    // Nesting subcommands is a thing
    const subcommand_template *current_subcommand = nullptr;

    // Finally, we parse! (with the 90% of parsing code made being above...)
    std::vector<parsed_argument> result = {};
    std::size_t i = 0;
    for (; i < mod_args.size(); i++)
    {
        auto &mod_arg = mod_args[i];

        if (mod_arg.arg_type == argument_type::double_hyphen)
        {
            break;
        }

        // First check for subcommand
        if (mod_arg.arg_type == argument_type::regular_argument)
        {
            auto matched_subcommand = match_subcommand(mod_arg.modified,
                subcommands);

            if (!matched_subcommand)
            {
                parsed_argument parsed_arg = {
                    mod_arg, validity::unrecognized_subcommand, true, nullptr,
                    nullptr, {}
                };

                result.emplace_back(parsed_arg);
                continue;
            }

            auto collected_args = collect_values(i, mod_args,
                matched_subcommand->parameters,
                matched_subcommand->defaults_from_back);

            validity valid = validity::valid;
            if (collected_args.size()
              < matched_subcommand->parameters.size())
            {
                valid = validity::not_enough_values;
            }

            parsed_argument parsed_arg = {
                mod_arg, valid, true, nullptr, matched_subcommand,
                collected_args
            };

            result.emplace_back(parsed_arg);
            current_subcommand = matched_subcommand;
            continue;
        }

        // Then for options/switches within a subcommand if subcommand is
        // available
        const option_template *matched_option = nullptr;
        if (current_subcommand)
        {
            matched_option = match_option(mod_arg.modified, mod_arg.arg_type,
                current_subcommand->subcommand_options, switch_ins);
        }

        // Then for options/switches that isn't part of any subcommand (global)
        if (!matched_option)
        {
            matched_option = match_option(mod_arg.modified, mod_arg.arg_type,
                options, switch_ins);
        }

        if (!matched_option)
        {
            parsed_argument parsed_arg = {
                mod_arg, validity::unrecognized_option, true, nullptr, nullptr,
                {}
            };

            result.emplace_back(parsed_arg);
            continue;
        }

        auto collected_args = collect_values(i, mod_args,
            matched_option->parameters,
            matched_option->defaults_from_back);

        validity valid = validity::valid;
        if (collected_args.size() < matched_option->parameters.size())
        {
            valid = validity::not_enough_values;
        }

        parsed_argument parsed_arg = {
            mod_arg, valid, true, matched_option, nullptr, collected_args
        };

        result.emplace_back(parsed_arg);
    }

    // Add all the unparsed arguments (as valid)
    for (; i < mod_args.size(); i++)
    {
        auto &mod_arg = mod_args[i];

        parsed_argument parsed_arg = {
            mod_arg, validity::valid, false, nullptr, nullptr, {}
        };

        result.emplace_back(parsed_arg);
    }
    return result;
}

/**
 *  @brief  Get padding as string.
 *
 *  @param  pad       Padding.
 *  @param  subtract  Subtract from count (optional).
 *  @return  Padding as string.
 */
[[nodiscard]] static inline constexpr auto padding_string(
    ap::help_pad_t pad,
    std::size_t    subtract = 0
)
{
    if (subtract > pad.size)
    {
        return ""s;
    }

    std::size_t size = pad.size - subtract;
    if (size == 0)
    {
        return ""s;
    }
    if (size == 1)
    {
        return pad.mid.style(pad.mid.value);
    }
    if (size == 2)
    {
        return pad.first.style(pad.first.value)
             + pad.last.style(pad.last.value);
    }
    return pad.first.style(pad.first.value)
         + pad.mid.style(pad.mid.value * size)
         + pad.last.style(pad.last.value);
}

/**
 *  @brief  Get padding's size.
 *
 *  We use a separate function because @c std::string::size() returns characters
 *  including the ANSI Escape Code style.
 *
 *  @param  pad  Padding.
 *  @return  Padding's size.
 */
[[nodiscard]] static inline constexpr auto padding_size(ap::help_pad_t pad)
{
    if (pad.size == 0)
    {
        return 0zu;
    }
    if (pad.size == 1)
    {
        return pad.mid.value.size();
    }
    if (pad.size == 2)
    {
        return pad.first.value.size() + pad.last.value.size();
    }
    return pad.first.value.size()
         + pad.mid.value.size() * pad.size
         + pad.last.value.size();
}

/**
 *  @brief  Abstract helper to add name to the option_line.
 *
 *  @tparam  Container          Container of compatible type.
 *  @tparam  GetName            Function type to get the name from element.
 *  @tparam  GetNameSize        Function type to get the size of the name.
 *  @param   container          Container.
 *  @param   separator          Separator.
 *  @param   wrap_pad           Padding for wrapped line.
 *  @param   wrap_width         Max width to wrap at.
 *  @param   current_line       Current option line (local variable).
 *  @param   current_line_size  Current option line size (local variable).
 *  @param   option_lines       All option lines (local variable).
 *  @param   get_name           Function to get the name from element.
 *  @param   get_name_size      Function to get the size of the name.
 *  @return
 */
template<cu::cu_compatible Container, typename GetName, typename GetNameSize>
static inline constexpr auto add_names(
    const Container          &container,
    ap::help_combo_t          separator,
    ap::help_pad_t            wrap_pad,
    std::size_t               wrap_width,
    std::string              &current_line,
    std::size_t              &current_line_size,
    std::vector<std::string> &option_lines,
    GetName                   get_name,
    GetNameSize               get_name_size
)
{
    for (std::size_t i = 0; i < std::size(container); i++)
    {
        auto &element = *(std::begin(container) + i);

        std::string name_string = "";
        std::size_t name_size   = 0;

        // Separator
        if (i != 0)
        {
            name_string = separator.style(separator.value);
            name_size   = separator.value.size();
        }

        name_string = get_name(i, element);
        name_size   = get_name_size(i, element);

        // Wrap
        if (current_line_size + name_size > wrap_width)
        {
            option_lines.emplace_back(current_line);
            current_line      = padding_string(wrap_pad);
            current_line_size = padding_size(wrap_pad);
        }

        current_line      += name_string;
        current_line_size += name_size;
    }
}

/**
 *  @brief  Helper to add long names to option_line.
 *
 *  @param  option             Option.
 *  @param  format             POSIX-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_long_names(
    const ap::option_template   &option,
    const ap::posix_help_format &format,
    std::string                 &current_line,
    std::size_t                 &current_line_size,
    std::vector<std::string>    &option_lines
)
{
    add_names(option.long_names, format.long_name_separator,
        format.pad_long_names, format.option_n_subcommand_width, current_line,
        current_line_size, option_lines,
        [&](std::size_t, const std::string &long_name)
    {
        return format.long_name_prefix_style("--")
             + format.long_name_style(long_name);
    },
        [&](std::size_t, const std::string &long_name)
    {
        return 2 + long_name.size();
    });
}

/**
 *  @brief  Helper to add short names to option_line.
 *
 *  @param  option             Option.
 *  @param  format             POSIX-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_short_names(
    const ap::option_template   &option,
    const ap::posix_help_format &format,
    std::string                 &current_line,
    std::size_t                 &current_line_size,
    std::vector<std::string>    &option_lines
)
{
    add_names(option.short_names, format.short_name_separator,
        format.pad_short_names, format.option_n_subcommand_width, current_line,
        current_line_size, option_lines,
        [&](std::size_t, char short_name)
    {
        return format.short_name_prefix_style("-")
             + format.short_name_style(std::string(1, short_name));
    },
        [&](std::size_t, char short_name)
    {
        return 2;
    });
}

/**
 *  @brief  Helper to add Microsoft-style switch names (long and short option
 *          names) to option_line.
 *
 *  @param  option             Option.
 *  @param  format             Microsoft-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_microsoft_switches(
    const ap::option_template       &option,
    const ap::microsoft_help_format &format,
    std::string                     &current_line,
    std::size_t                     &current_line_size,
    std::vector<std::string>        &option_lines
)
{
    auto add_microsoft_switch_long_names = [&]()
    {
        add_names(option.long_names, format.switch_separator,
            format.pad_switch, format.switch_n_subcommand_width, current_line,
            current_line_size, option_lines,
            [&](std::size_t, const std::string &long_name)
        {
            return format.switch_prefix_style("/")
                 + format.switch_style(long_name);
        },
            [&](std::size_t, const std::string &long_name)
        {
            return 1 + long_name.size();
        });
    };

    auto add_microsoft_switch_short_names = [&]()
    {
        add_names(option.short_names, format.switch_separator,
            format.pad_switch, format.switch_n_subcommand_width, current_line,
            current_line_size, option_lines,
            [&](std::size_t, char short_name)
        {
            return format.switch_prefix_style("/")
                 + format.switch_style(std::string(1, short_name));
        },
            [&](std::size_t, char short_name)
        {
            return 2;
        });
    };

    // Whichever first
    if (format.long_names_first)
    {
        add_microsoft_switch_long_names();

        current_line += format.switch_separator.style(
            format.switch_separator.value);
        current_line_size += format.switch_separator.value.size();

        add_microsoft_switch_short_names();
    }
    else
    {
        add_microsoft_switch_short_names();

        current_line += format.switch_separator.style(
            format.switch_separator.value);
        current_line_size += format.switch_separator.value.size();

        add_microsoft_switch_long_names();
    }
}

/**
 *  @brief  Helper to add subcommand names to option_line.
 *
 *  @param  subcommand         Subcommand.
 *  @param  format             POSIX-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_subcommand_names(
    const ap::subcommand_template &subcommand,
    const ap::posix_help_format   &format,
    std::string                   &current_line,
    std::size_t                   &current_line_size,
    std::vector<std::string>      &option_lines
)
{
    add_names(subcommand.names, format.subcommand_separator,
        format.pad_subcommand, format.option_n_subcommand_width, current_line,
        current_line_size, option_lines,
        [&](std::size_t, const std::string &name)
    {
        return format.subcommand_style(name);
    },
        [&](std::size_t, const std::string &name)
    {
        return name.size();
    });
}

/**
 *  @brief  Helper to add subcommand names to option_line.
 *
 *  @param  subcommand         Subcommand.
 *  @param  format             Microsoft-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_subcommand_names(
    const ap::subcommand_template   &subcommand,
    const ap::microsoft_help_format &format,
    std::string                     &current_line,
    std::size_t                     &current_line_size,
    std::vector<std::string>        &option_lines
)
{
    add_names(subcommand.names, format.subcommand_separator,
        format.pad_subcommand, format.switch_n_subcommand_width, current_line,
        current_line_size, option_lines,
        [&](std::size_t, const std::string &name)
    {
        return format.subcommand_style(name);
    },
        [&](std::size_t, const std::string &name)
    {
        return name.size();
    });
}

/**
 *  @brief  Abstract helper to get formatted parameter name.
 *
 *  @param  i                            Current element index.
 *  @param  parameter                    Current element.
 *  @param  parameters_size              All parameters size.
 *  @param  defaults_size                Default values size.
 *  @param  optional_parameter_enclose   Encloser for optional parameter.
 *  @param  mandatory_parameter_enclose  Encloser for mandatory parameter.
 *  @param  parameter_prefix_first       Prefix for first parameter.
 *  @param  parameter_prefix             Prefix for rest of the parameters.
 *  @param  enclose_before_prefix        Enclose before appending prefix.
 *  @return  Formatted parameter name.
 */
[[nodiscard]] static inline constexpr auto parameter_name_adder(
    std::size_t        i,
    const std::string &parameter,
    std::size_t        parameters_size,
    std::size_t        defaults_size,
    ap::help_enclose_t optional_parameter_enclose,
    ap::help_enclose_t mandatory_parameter_enclose,
    ap::help_combo_t   parameter_prefix_first,
    ap::help_combo_t   parameter_prefix,
    bool               enclose_before_prefix
)
{
    bool is_optional = parameters_size - defaults_size < i + 1;

    ap::help_enclose_t encloser = {};
    if (is_optional) encloser = optional_parameter_enclose;
    else encloser = mandatory_parameter_enclose;

    ap::help_combo_t prefix = {};
    if (i == 0) prefix = parameter_prefix_first;
    else prefix = parameter_prefix;

    if (enclose_before_prefix)
    {
        return prefix.style(prefix.value)
             + encloser.prefix.style(encloser.prefix.value)
             + encloser.value_style(parameter)
             + encloser.suffix.style(encloser.suffix.value);
    }
    else
    {
        return encloser.prefix.style(encloser.prefix.value)
             + prefix.style(prefix.value)
             + encloser.value_style(parameter)
             + encloser.suffix.style(encloser.suffix.value);
    }
}

/**
 *  @brief  Abstract helper to get size of formatted parameter name.
 *
 *  @param  i                            Current element index.
 *  @param  parameter                    Current element.
 *  @param  parameters_size              All parameters size.
 *  @param  defaults_size                Default values size.
 *  @param  optional_parameter_enclose   Encloser for optional parameter.
 *  @param  mandatory_parameter_enclose  Encloser for mandatory parameter.
 *  @param  parameter_prefix_first       Prefix for first parameter.
 *  @param  parameter_prefix             Prefix for rest of the parameters.
 *  @return  Size of formatted parameter name.
 */
static inline constexpr auto parameter_name_adder_size(
    std::size_t        i,
    const std::string &parameter,
    std::size_t        parameters_size,
    std::size_t        defaults_size,
    ap::help_enclose_t optional_parameter_enclose,
    ap::help_enclose_t mandatory_parameter_enclose,
    ap::help_combo_t   parameter_prefix_first,
    ap::help_combo_t   parameter_prefix
)
{
    bool is_optional = parameters_size - defaults_size < i + 1;

    ap::help_enclose_t encloser = {};
    if (is_optional) encloser = optional_parameter_enclose;
    else encloser = mandatory_parameter_enclose;

    ap::help_combo_t prefix = {};
    if (i == 0) prefix = parameter_prefix_first;
    else prefix = parameter_prefix;

    return prefix.value.size()
         + encloser.prefix.value.size()
         + parameter.size()
         + encloser.suffix.value.size();
}

/**
 *  @brief  Helper to add parameter names to option_line.
 *
 *  @param  option             Option.
 *  @param  format             POSIX-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_parameter_names(
    const ap::option_template   &option,
    const ap::posix_help_format &format,
    std::string                 &current_line,
    std::size_t                 &current_line_size,
    std::vector<std::string>    &option_lines
)
{
    add_names(option.parameters, format.parameter_separator,
        format.pad_parameters_wrapped, format.option_n_subcommand_width,
        current_line, current_line_size, option_lines,
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder(i, parameter, option.parameters.size(),
            option.defaults_from_back.size(), format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix, format.enclose_before_prefix);
    },
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder_size(i, parameter, option.parameters.size(),
            option.defaults_from_back.size(), format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix);
    });
}

/**
 *  @brief  Helper to add parameter names to option_line.
 *
 *  @param  option             Option.
 *  @param  format             Microsoft-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_parameter_names(
    const ap::option_template       &option,
    const ap::microsoft_help_format &format,
    std::string                     &current_line,
    std::size_t                     &current_line_size,
    std::vector<std::string>        &option_lines
)
{
    add_names(option.parameters, format.parameter_separator,
        format.pad_parameters_wrapped, format.switch_n_subcommand_width,
        current_line, current_line_size, option_lines,
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder(i, parameter, option.parameters.size(),
            option.defaults_from_back.size(), format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix, format.enclose_before_prefix);
    },
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder_size(i, parameter, option.parameters.size(),
            option.defaults_from_back.size(), format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix);
    });
}

/**
 *  @brief  Helper to add parameter names to option_line.
 *
 *  @param  subcommand         Subcommand.
 *  @param  format             POSIX-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_parameter_names(
    const ap::subcommand_template &subcommand,
    const ap::posix_help_format   &format,
    std::string                   &current_line,
    std::size_t                   &current_line_size,
    std::vector<std::string>      &option_lines
)
{
    add_names(subcommand.parameters, format.parameter_separator,
        format.pad_parameters_wrapped, format.option_n_subcommand_width,
        current_line, current_line_size, option_lines,
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder(i, parameter, subcommand.parameters.size(),
            subcommand.defaults_from_back.size(),
            format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix, format.enclose_before_prefix);
    },
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder_size(i, parameter,
            subcommand.parameters.size(), subcommand.defaults_from_back.size(),
            format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix);
    });
}

/**
 *  @brief  Helper to add parameter names to option_line.
 *
 *  @param  subcommand         Subcommand.
 *  @param  format             Microsoft-style format.
 *  @param  current_line       Current option line (local variable).
 *  @param  current_line_size  Current option line size (local variable).
 *  @param  option_lines       All option lines (local variable).
 */
static inline constexpr auto add_parameter_names(
    const ap::subcommand_template   &subcommand,
    const ap::microsoft_help_format &format,
    std::string                     &current_line,
    std::size_t                     &current_line_size,
    std::vector<std::string>        &option_lines
)
{
    add_names(subcommand.parameters, format.parameter_separator,
        format.pad_parameters_wrapped, format.switch_n_subcommand_width,
        current_line, current_line_size, option_lines,
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder(i, parameter, subcommand.parameters.size(),
            subcommand.defaults_from_back.size(),
            format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix, format.enclose_before_prefix);
    },
        [&](std::size_t i, const std::string &parameter)
    {
        return parameter_name_adder_size(i, parameter,
            subcommand.parameters.size(), subcommand.defaults_from_back.size(),
            format.optional_parameter_enclose,
            format.mandatory_parameter_enclose, format.parameter_prefix_first,
            format.parameter_prefix);
    });
}

/**
 *  @brief  Helper to combine option_line and description text.
 *
 *  @param  description              Description text.
 *  @param  description_width        Wrap description at width.
 *  @param  n_subcommand_width       Option/Switch and Subcommand's total width.
 *  @param  pad_description          Description first line padding.
 *  @param  pad_description_wrapped  Wrapped description padding.
 *  @param  option_lines             Option lines (local variable).
 *  @param  result                   Overall result (local variable).
 */
static inline constexpr auto combine_option_description(
    std::string               description,
    std::size_t               description_width,
    std::size_t               n_subcommand_width,
    ap::help_pad_t            pad_description,
    ap::help_pad_t            pad_description_wrapped,
    std::vector<std::string> &option_lines,
    std::vector<std::string> &result
)
{
    auto wrapped_description = sm::word_wrap(description,
        description_width);

    std::size_t description_line_offset = 0;
    if (n_subcommand_width > pad_description.size && !option_lines.empty())
    {
        description_line_offset = option_lines.size()
            - option_lines.back().size() <= pad_description.size;
    }

    // Add description and option lines
    // Will continue to add option even if description lines are ended
    std::size_t i = 0;
    for (; i < option_lines.size(); i++)
    {
        std::string line = option_lines[i];

        std::size_t j = i - description_line_offset;
        if (j == 0)
        {
            line += padding_string(pad_description, line.size());
            line += wrapped_description.front();
        }
        else if (j < wrapped_description.size())
        {
            line += padding_string(pad_description_wrapped, line.size());
            line += wrapped_description[j];
        }
        result.emplace_back(line);
    }

    // Add description if option lines ended before description lines
    for (std::size_t j = i - description_line_offset;
         j < wrapped_description.size(); i++, j++)
    {
        std::string line = "";
        line += padding_string(pad_description_wrapped, line.size());
        line += wrapped_description[j];
        result.emplace_back(line);
    }
}

/**
 *  @brief  Generate help message string from option and POSIX-style format.
 *
 *  @param  option  Option.
 *  @param  format  POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] auto ap::get_help_message(
    const option_template &option,
    posix_help_format      format
) -> std::vector<std::string>
{
    std::vector<std::string> result       = {};
    std::vector<std::string> option_lines = {};

    std::string current_line      = "";
    std::size_t current_line_size = 0;

    // Whichever first
    if (format.long_names_first)
    {
        add_long_names(option, format, current_line, current_line_size,
            option_lines);

        current_line += format.short_n_long_name_separator.style(
            format.short_n_long_name_separator.value);
        current_line_size += format.short_n_long_name_separator.value.size();

        add_short_names(option, format, current_line, current_line_size,
            option_lines);
    }
    else
    {
        add_short_names(option, format, current_line, current_line_size,
            option_lines);

        current_line += format.short_n_long_name_separator.style(
            format.short_n_long_name_separator.value);
        current_line_size += format.short_n_long_name_separator.value.size();

        add_long_names(option, format, current_line, current_line_size,
            option_lines);
    }

    add_parameter_names(option, format, current_line, current_line_size,
        option_lines);

    combine_option_description(option.description, format.description_width,
        format.option_n_subcommand_width, format.pad_description,
        format.pad_description_wrapped, option_lines, result);

    return result;
}

/**
 *  @brief  Generate help message string from subcommand and POSIX-style format.
 *
 *  @param  subcommand  Subcommand.
 *  @param  format      POSIX-style format.
 *  @return  Vector of string for each line.
 */
[[nodiscard]] auto ap::get_help_message(
    const subcommand_template &subcommand,
    posix_help_format          format
) -> std::vector<std::string>
{
    std::vector<std::string> result       = {};
    std::vector<std::string> option_lines = {};

    std::string current_line      = "";
    std::size_t current_line_size = 0;

    add_subcommand_names(subcommand, format, current_line, current_line_size,
        option_lines);

    add_parameter_names(subcommand, format, current_line, current_line_size,
        option_lines);

    combine_option_description(subcommand.description, format.description_width,
        format.option_n_subcommand_width, format.pad_description,
        format.pad_description_wrapped, option_lines, result);

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
[[nodiscard]] auto ap::get_help_message(
    const option_template &option,
    microsoft_help_format  format
) -> std::vector<std::string>
{
    std::vector<std::string> result       = {};
    std::vector<std::string> option_lines = {};

    std::string current_line      = "";
    std::size_t current_line_size = 0;

    add_microsoft_switches(option, format, current_line, current_line_size,
        option_lines);

    add_parameter_names(option, format, current_line, current_line_size,
        option_lines);

    combine_option_description(option.description, format.description_width,
        format.switch_n_subcommand_width, format.pad_description,
        format.pad_description_wrapped, option_lines, result);

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
[[nodiscard]] auto ap::get_help_message(
    const subcommand_template &subcommand,
    microsoft_help_format      format
) -> std::vector<std::string>
{
    std::vector<std::string> result       = {};
    std::vector<std::string> option_lines = {};

    std::string current_line      = "";
    std::size_t current_line_size = 0;

    add_subcommand_names(subcommand, format, current_line, current_line_size,
        option_lines);

    add_parameter_names(subcommand, format, current_line, current_line_size,
        option_lines);

    combine_option_description(subcommand.description, format.description_width,
        format.switch_n_subcommand_width, format.pad_description,
        format.pad_description_wrapped, option_lines, result);

    return result;
}
