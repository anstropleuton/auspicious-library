/**
 *  @file    al_string_manipulators.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Functionality to manipulate and format strings.
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

#pragma once

#if !defined(AUSPICIOUS_LIBRARY_HPP_INCLUDED) \
 && !defined(AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN)
    #warning Its recommended to include auspicious_library.hpp instead.
#endif // ifndef AUSPICIOUS_LIBRARY_HPP_INCLUDED

#include <cctype>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>

#include "al_container_utilities.hpp"

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

namespace stdr = std::ranges;
namespace stdv = stdr::views;

/**
 *  @brief  String Manipulators.
 */
namespace sm {

/**
 *  @brief  Convert a container to comma separated string.
 *
 *  @tparam  Container  Compatible container type.
 *  @tparam  Converter  Element conversion function type.
 *  @param   container  Container.
 *  @param   converter  Element conversion function.
 *  @param   separator  Separator between elements (optional).
 *  @param   prefix     Prefix to the element (optional).
 *  @param   suffix     Suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible Container, typename Converter>
[[nodiscard]] inline constexpr auto to_string(
    const Container &container,
    Converter        converter,
    std::string_view separator = ", ",
    std::string_view prefix    = "",
    std::string_view suffix    = ""
)
{
    auto transformer = [&](const cu::value_type<Container> &element)
    {
        ///  @todo  Remove this cast when C++26 comes out.
        return std::string(prefix) + converter(element) + std::string(suffix);
    };

    return stdv::transform(container, transformer)
         | stdv::join_with(std::string(separator))
         | stdr::to<std::string>();
}

/**
 *  @brief  Convert a container to comma separated string.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   separator  Separator between elements (optional).
 *  @param   prefix     Prefix to the element (optional).
 *  @param   suffix     Suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible Container>
[[nodiscard]] inline constexpr auto to_string(
    const Container &container,
    std::string_view separator = ", ",
    std::string_view prefix    = "",
    std::string_view suffix    = ""
)
{
    return to_string<Container, std::string (*)(cu::value_type<Container>)>(
        container, std::to_string, separator, prefix, suffix);
}

/**
 *  @brief  Convert a container of char to string with single-quoted elements
 *          separated by comma.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   separator  Separator between elements (optional).
 *  @param   prefix     Prefix to the element (optional).
 *  @param   suffix     Suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible Container>
requires std::is_same_v<cu::value_type<Container>, char>
[[nodiscard]] inline constexpr auto to_string(
    const Container &container,
    std::string_view separator = ", ",
    std::string_view prefix    = "\'",
    std::string_view suffix    = "\'"
)
{
    auto converter = [&](const cu::value_type<Container> &element)
    {
        return std::string(1, element);
    };

    return to_string(container, converter, separator, prefix, suffix);
}

/**
 *  @brief  Convert a container of @c std::string to string with double-quoted
 *          elements separated by comma.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   separator  Separator between elements (optional).
 *  @param   prefix     Prefix to the element (optional).
 *  @param   suffix     Suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible Container>
requires std::is_same_v<cu::value_type<Container>, std::string>
[[nodiscard]] inline constexpr auto to_string(
    const Container &container,
    std::string_view separator = ", ",
    std::string_view prefix    = "\"",
    std::string_view suffix    = "\""
)
{
    return to_string(container, std::identity {}, separator, prefix, suffix);
}

/**
 *  @brief  Convert a container of char to a regular string.
 *
 *  @tparam  Container  Compatible container type with char element type.
 *  @param   container  Container.
 *  @return  String of all chars.
 */
template<cu::cu_compatible Container>
requires std::is_same_v<cu::value_type<Container>, char>
[[nodiscard]] inline constexpr auto chars_to_string(const Container &container)
{
    return std::string(std::begin(container), std::end(container));
}

///  @todo  Add to_string for std::string and char for consistency.

/**
 *  @brief  Word-wrap a string at width or before width depending on the delim.
 *
 *  The string is tried to be split at the width if the character at the width
 *  is one of the delimiter.  If not, the split occurs at the character before
 *  the width that is one of the delimiter.  This process is repeated until the
 *  string is less than the size of width.  If a word is longer than the
 *  specified width, the word is kept as is.  If you use force, the word will be
 *  split.
 *
 *  @param  string  String to word-wrap.
 *  @param  width   Word-wrap width.
 *  @param  force   Force the string to always be less than or equal to width
 *                  (optional).
 *  @param  delims  Delimiters, usually whitespace (optional).
 *  @return  std::vector of word-wrapped lines.
 *
 *  @note  word-wrapped lines can be larger than width.
 */
[[nodiscard]] inline constexpr auto word_wrap(
    std::string_view string,
    std::size_t      width,
    bool             force = false,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    std::vector<std::string> lines = {};

    // Functions expect inclusive width, and also works as a measure to have at
    // least one as width (as a side effect)
    width++;

    while (string.size() > width)
    {
        // First non-delim character before or at width
        auto pos = string.substr(0, width).find_last_of(delims);
        if (pos == std::string_view::npos)
        {
            // Split without consuming character
            if (force)
            {
                pos       = string.substr(0, width).size() - 1;
                auto line = string.substr(0, pos);
                string    = string.substr(pos);
                lines.emplace_back(std::string(line));
                continue;
            }

            // If not, first non-delim character after width
            pos = string.substr(width + 1).find_first_of(delims);

            // If still not, eof reached? Prevent overflow
            if (pos == std::string_view::npos) pos--;
            else pos += width + 1;
        }

        auto line = string.substr(0, pos);
        string    = string.substr(pos + 1);
        lines.emplace_back(std::string(line));
    }

    if (!string.empty())
    {
        lines.emplace_back(std::string(string));
    }

    return lines;
}

/**
 *  @brief  Trim a string (only from left side) using delimiters (usually
 *          whitespace).
 *
 *  @param  string  String to trim from left.
 *  @param  delims  Delimiters, usually whitespace (optional).
 *  @return  Trimmed string.
 */
[[nodiscard]] inline constexpr auto trim_left(
    std::string_view string,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    auto pos = string.find_first_not_of(delims);
    if (pos == std::string_view::npos)
    {
        return string;
    }
    return string.substr(pos);
}

/**
 *  @brief  Trim a string (only from right side) using delimiters (usually
 *          whitespace).
 *
 *  @param  string  String to trim from right.
 *  @param  delims  Delimiters, usually whitespace (optional).
 *  @return  Trimmed string.
 */
[[nodiscard]] inline constexpr auto trim_right(
    std::string_view string,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    auto pos = string.find_last_not_of(delims);
    if (pos == std::string_view::npos)
    {
        return string;
    }
    return string.substr(0, pos + 1);
}

/**
 *  @brief  Trim a string using delimiters (usually whitespace).
 *
 *  @param  string  String to trim.
 *  @param  delims  Delimiters, usually whitespace (optional).
 *  @return  Trimmed string.
 */
[[nodiscard]] inline constexpr auto trim(
    std::string_view string,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    return trim_left(trim_right(string, delims), delims);
}

/**
 *  @brief  Convert string to uppercase.
 *
 *  @param  string  String to convert.
 *  @return  Uppercase string.
 */
[[nodiscard]] inline constexpr auto to_upper(std::string_view string)
{
    std::string str;
    stdr::transform(string, std::back_inserter(str), ::toupper);
    return str;
}

/**
 *  @brief  Convert string to lowercase.
 *
 *  @param  string  String to convert.
 *  @return  Lowercase string.
 */
[[nodiscard]] inline constexpr auto to_lower(std::string_view string)
{
    std::string str;
    stdr::transform(string, std::back_inserter(str), ::tolower);
    return str;
}

/**
 *  @brief  Convert character to uppercase (exists for consistency).
 *
 *  @param  character  Character to convert.
 *  @return  Uppercase character.
 */
[[nodiscard]] inline constexpr auto to_upper(char character)
{
    return ::toupper(character);
}

/**
 *  @brief  Convert character to lowercase (exists for consistency).
 *
 *  @param  character  Character to convert.
 *  @return  Lowercase character.
 */
[[nodiscard]] inline constexpr auto to_lower(char character)
{
    return ::tolower(character);
}

/**
 *  @brief  Compare string, case insensitivity.
 *
 *  @param  a  First string.
 *  @param  b  Second string.
 *  @return  True if they are equal, case insensitively.
 */
[[nodiscard]] inline constexpr auto is_equal_ins(
    std::string_view a,
    std::string_view b
)
{
    // Either of them will do...
    return to_lower(a) == to_lower(b);
}

/**
 *  @brief  Compare character, case insensitivity (exists for consistency).
 *
 *  @param  a  First character.
 *  @param  b  Second character.
 *  @return  True if they are equal, case insensitively.
 */
[[nodiscard]] inline constexpr auto is_equal_ins(char a, char b)
{
    // Either of them will do...
    return ::tolower(a) == ::tolower(b);
}

} // namespace sm

/**
 *  @brief  String Manipulators, operators version.
 */
namespace sm_operators {

/**
 *  @brief  Filter out the occurrences of sequence from the string.
 *
 *  @param  string  String.
 *  @param  values  Sequence to remove.
 *  @return  Filtered string as std::string.
 *
 *  @see  cu::filter_out_seq.
 */
[[nodiscard]] inline constexpr auto operator- (
    std::string_view string,
    std::string_view values
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<char> values_vec(values.begin(), values.end());
    return sm::chars_to_string(cu::filter_out_seq(string_vec, values_vec));
}

/**
 *  @brief  Filter out the occurrences of value from the string.
 *
 *  @param  string  String.
 *  @param  value   Value to remove.
 *  @return  Filtered string as std::string.
 *
 *  @see  cu::filter_out.
 */
[[nodiscard]] inline constexpr auto operator- (
    std::string_view string,
    char             value
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::filter_out(string_vec, value));
}

/**
 *  @brief  Repeat string using operator.
 *
 *  @param  string  String.
 *  @param  n       Repeat times.
 *  @return  Repeated string as std::string.
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    std::size_t      n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  String.
 *  @param  n       Repeat times.
 *  @return  Repeated string as std::string.
 *
 *  @see   cu::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    long double      n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Split the string with pattern.
 *
 *  @param  string  String.
 *  @param  pattern Pattern to split with.
 *  @return  Split string as std::vector of std::string.
 *
 *  @see  cu::split.
 */
[[nodiscard]] inline constexpr auto operator/ (
    std::string_view string,
    std::string_view pattern
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<char> pattern_vec(pattern.begin(), pattern.end());
    auto result = cu::split_seq(string_vec, pattern_vec);
    return stdv::transform(result, sm::chars_to_string<std::vector<char>>)
         | stdr::to<std::vector<std::string>>();
}

/**
 *  @brief  Split the string with value.
 *
 *  @param  string  String.
 *  @param  value   Value to split with.
 *  @return  Split string as std::vector of std::string.
 *
 *  @see  cu::split.
 */
[[nodiscard]] inline constexpr auto operator/ (
    std::string_view string,
    char             value
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    auto result = cu::split(string_vec, value);
    return stdv::transform(result, sm::chars_to_string<std::vector<char>>)
         | stdr::to<std::vector<std::string>>();
}

} // namespace sm_operators

} // namespace auspicious_library
