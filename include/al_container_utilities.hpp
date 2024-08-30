/**
 *  @file    al_container_utilities.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   General functionality for container types with operators.
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

#if !defined(AUSPICIOUS_LIBRARY_HPP_INCLUDED) \
 && !defined(AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN)
    #warning Its recommended to include auspicious_library.hpp instead.
#endif // ifndef AUSPICIOUS_LIBRARY_HPP_INCLUDED

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <vector>

/**
 *  @brief  All Auspicious Library's contents in this namespace. Do not
 *          `using namespace auspicious_library;`.  Instead, use this:
    ```cpp
    namespace al {
    using namespace auspicious_library::cu;
    using namespace auspicious_library::sm;
    using namespace auspicious_library::aec;
    using namespace auspicious_library::ap;
    using namespace auspicious_library::fu;
    }
    using namespace auspicious_library::cu_operators;
    using namespace auspicious_library::sm_operators;
    using namespace auspicious_library::aec_operators;
    ```
 */
namespace auspicious_library {

namespace stdr = std::ranges;
namespace stdv = stdr::views;

/**
 *  @brief  Copper...?  No wait, Container Utilities.
 */
namespace cu {

/**
 *  @brief  Container compatible for Container Utilities.
 *
 *  Container type must have @c begin() and @c end() in either member or
 *  free-standing function which return contiguous iterators, and a
 *  @c value_type typename member.  The container must also be constructable
 *  using iterators and an @c initializer_list of value type.
 *
 *  @tparam  Container  The container type.
 */
template<typename Container>
concept cu_compatible = requires {
    { std::begin(std::declval<Container>()) } -> std::contiguous_iterator;
    { std::end(std::declval<Container>()) } -> std::contiguous_iterator;
    { std::declval<typename Container::value_type>() };
    { Container(std::begin(std::declval<Container>()),
        std::end(std::declval<Container>())) };
    { Container({ std::declval<typename Container::value_type>() }) };
};

/**
 *  @brief  Container's value_type member.
 *  @tparam  Container  Compatible container type.
 */
template<cu_compatible Container>
using value_type = Container::value_type;

/**
 *  @brief  All container utilities return this container.
 *  @tparam  Container  Compatible container type.
 */
template<cu_compatible Container>
using result_container = std::vector<value_type<Container>>;

/**
 *  @brief  All container utilities return this container if the result is
 *          nested.
 *
 *  @tparam  Container  Compatible container type.
 */
template<cu_compatible Container>
using result_container_nested = std::vector<std::vector<value_type<Container>>>;

/**
 *  @brief  Get the subset of the container's elements.
 *
 *  @tparam  Container       Compatible container type.
 *  @param   container       Container.
 *  @param   first_inclusive First index (inclusive).
 *  @param   last_exclusive  Last index (exclusive).
 *  @return  Subset of the container as result_container.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto subordinate(
    const Container &container,
    std::size_t      first_inclusive,
    std::size_t      last_exclusive
)
{
    return result_container<Container>(
        std::begin(container) + first_inclusive,
        std::begin(container) + last_exclusive);
}

/**
 *  @brief  Copy containers into one container.
 *
 *  @tparam  Container    Compatible container type.
 *  @param   container_a  First container.
 *  @param   container_b  Second container.
 *  @return  Combined container as result_container.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto combine(
    const Container &container_a,
    const Container &container_b
)
{
    return result_container_nested<Container> { container_a, container_b }
         | stdv::join
         | stdr::to<result_container<Container>>();
}

/**
 *  @brief  Copy container and value into one container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value.
 *  @return  Value-appended container as result_container.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto combine(
    const Container             &container,
    const value_type<Container> &value
)
{
    return combine(container, Container({ value }));
}

/**
 *  @brief  Filter out the occurrences of sequence from the container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   values     Sequence to remove.
 *  @return  Filtered container as result_container.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto filter_out_seq(
    const Container &container,
    const Container &values
)
{
    return stdv::split(container, values)
         | stdv::join
         | stdr::to<result_container<Container>>();
}

/**
 *  @brief  Filter out the occurrences of any of values from the container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   values     Sequence to remove.
 *  @return  Filtered container as result_container.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto filter_out_occ(
    const Container &container,
    const Container &values
)
{
    auto filterer = [&](const cu::value_type<Container> &element)
    {
        return stdr::find(values, element) == values.end();
    };

    return stdv::filter(container, filterer)
         | stdr::to<result_container<Container>>();
}

/**
 *  @brief  Filter out the occurrences of value from the container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value to remove.
 *  @return  Filtered container as result_container.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto filter_out(
    const Container             &container,
    const value_type<Container> &value
)
{
    // Either of them will do...
    return filter_out_seq(container, Container({ value }));
}

/**
 *  @brief  Repeat container @c n times.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   n          Repeat times.
 *  @return  Repeated container as result_container.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto repeat(
    const Container &container,
    std::size_t      n
)
{
    return stdv::repeat(container, n)
         | stdv::join
         | stdr::to<result_container<Container>>();
}

/**
 *  @brief  Repeat container @c n times.
 *
 *  Considering integer part of the number @c n as @c i, and fraction part as
 *  @c f, the container is repeated @c i.0 times, and then the container is
 *  added with subordinate container with `round(0.f * container.size())`
 *  elements from the beginning.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   n          Repeat times.
 *  @return  Repeated container as result_container.
 *
 *  @note  This is scuffed.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto repeat(
    const Container &container,
    long double      n
)
{
    long double i_part         = 0;
    long double f_part         = std::modf(n, &i_part);
    std::size_t regular_repeat = i_part;
    std::size_t sub_size       = std::floor(f_part * container.size());
    Container   sub = subordinate(container, 0, sub_size);

    return combine(repeat(container, regular_repeat), sub);
}

/**
 *  @brief  Split the container with pattern.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   pattern    Pattern to split with.
 *  @return  Split container as result_container_nested.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto split_seq(
    const Container &container,
    const Container &pattern
)
{
    return stdv::split(container, pattern)
         | stdr::to<result_container_nested<Container>>();
}

/**
 *  @brief  Split the container with occurrences.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   Values     Values to split with.
 *  @return  Split container as result_container_nested.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto split_occ(
    const Container &container,
    const Container &values
)
{
    // Couldn't find standard library to do this heavy job, so...
    result_container_nested<Container> result;
    auto it = container.begin();

    while (it != container.end())
    {
        auto next_it = std::find_first_of(it, container.end(), values.begin(),
            values.end());
        result.emplace_back(result_container<Container>(it, next_it));
        it = next_it;
        if (it != container.end()) ++it;
    }

    return result;
}

/**
 *  @brief  Split the container with value.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value to split with.
 *  @return  Split container as result_container_nested.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto split(
    const Container             &container,
    const value_type<Container> &value
)
{
    // Either of them will do...
    return split_seq(container, Container({ value }));
}

} // namespace cu

/**
 *  @brief  Container Utilities, operators version.
 */
namespace cu_operators {

/**
 *  @brief  Combine containers using operator.
 *
 *  @tparam  Container    Compatible container type.
 *  @param   container_a  First container.
 *  @param   container_b  Second container.
 *  @return  Combined container as result_container.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see  cu::combine.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator+ (
    const Container &container_a,
    const Container &container_b
)
{
    return cu::combine(container_a, container_b);
}

/**
 *  @brief  Copy container and value into one container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value.
 *  @return  Value-appended container as result_container.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see  cu::combine.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator+ (
    const Container                 &container_a,
    const cu::value_type<Container> &value
)
{
    return cu::combine(container_a, value);
}

/**
 *  @brief  Filter out the occurrences of sequence from the container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   values     Sequence to remove.
 *  @return  Filtered container as result_container.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see  cu::filter_out_seq.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator- (
    const Container &container,
    const Container &values
)
{
    return cu::filter_out_seq(container, values);
}

/**
 *  @brief  Filter out the occurrences of value from the container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value to remove.
 *  @return  Filtered container as result_container.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see  cu::filter_out.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator- (
    const Container                 &container,
    const cu::value_type<Container> &value
)
{
    return cu::filter_out(container, value);
}

/**
 *  @brief  Repeat container using operator.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   n          Repeat times.
 *  @return  Repeated container as result_container.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see  cu::repeat.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator* (
    const Container &container,
    std::size_t      n
)
{
    return cu::repeat(container, n);
}

/**
 *  @brief  Repeat container @c n times.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   n          Repeat times.
 *  @return  Repeated container as result_container.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see   cu::repeat.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator* (
    const Container &container,
    long double      n
)
{
    return cu::repeat(container, n);
}

/**
 *  @brief  Split the container with pattern.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   pattern    Pattern to split with.
 *  @return  Split container as result_container_nested.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see  cu::split.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator/ (
    const Container &container,
    const Container &pattern
)
{
    return cu::split_seq(container, pattern);
}

/**
 *  @brief  Split the container with value.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value to split with.
 *  @return  Split container as result_container_nested.
 *
 *  @note  Use String Manipulators' operators for std::string or
 *         std::string_view.
 *
 *  @see  cu::split.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator/ (
    const Container                 &container,
    const cu::value_type<Container> &value
)
{
    return cu::split(container, value);
}

} // namespace cu_operators

} // namespace auspicious_library
