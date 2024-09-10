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

#include <functional>
#include <initializer_list>
#include <map>
#include <numeric>
#include <utility>
#if !defined(AUSPICIOUS_LIBRARY_HPP_INCLUDED) \
 && !defined(AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN)
    #warning Its recommended to include auspicious_library.hpp instead.
#endif // ifndef AUSPICIOUS_LIBRARY_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

/**
 *  @brief  All Auspicious Library's contents in this namespace.
 *
 *  Do not `using namespace auspicious_library;`.  Instead, use this:
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
 *  @brief  All Container Utilities return this container.
 *  @tparam  Container  Compatible container type.
 */
template<cu_compatible Container>
using result_container = std::vector<value_type<Container>>;

/**
 *  @brief  All Container Utilities return this container if the result is
 *          nested.
 *  @tparam  Container  Compatible container type.
 */
template<cu_compatible Container>
using result_container_nested = std::vector<std::vector<value_type<Container>>>;

/**
 *  @brief  Nested container compatible for Container Utilities.
 *  @tparam  Container  Compatible container type with value type also being a
 *                      compatible container type.
 */
template<typename Container>
concept cu_compatible_nested = cu_compatible<value_type<Container>>;

/**
 *  @brief  Get the subset of the container's elements.
 *
 *  @tparam  Container       Compatible container type.
 *  @param   container       Container.
 *  @param   first_inclusive First index (inclusive).
 *  @param   last_exclusive  Last index (exclusive).
 *  @return  Subset of the container as @c result_container .
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
 *  @return  Combined container as @c result_container .
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
 *  @return  Value-appended container as @c result_container .
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
 *  @param   pattern     Sequence to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto filter_out_seq(
    const Container &container,
    const Container &pattern
)
{
    return stdv::split(container, pattern)
         | stdv::join
         | stdr::to<result_container<Container>>();
}

/**
 *  @brief  Filter out the occurrences of any of values from the container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   values     Elements to remove.
 *  @return  Filtered container as @c result_container .
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
 *  @brief  Filter out the occurrences of any of sequences from the container.
 *
 *  @tparam  Container        Compatible container type.
 *  @tparam  NestedContainer  Compatible nested container type.
 *  @param   container        Container.
 *  @param   patterns         Sequences to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible Container, cu_compatible_nested NestedContainer>
[[nodiscard]] inline constexpr auto filter_out_occ_seq(
    const Container       &container,
    const NestedContainer &patterns
)
{
    result_container<Container> result = container;
    for (auto &pattern : patterns)
    {
        result = filter_out_seq(result, pattern);
    }
    return result;
}

/**
 *  @brief  Filter out the occurrences of value from the container.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto filter_out(
    const Container             &container,
    const value_type<Container> &value
)
{
    return filter_out_seq(container, Container({ value }));
}

/**
 *  @brief  Repeat container @c n times.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   n          Repeat times.
 *  @return  Repeated container as @c result_container .
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
 *  @return  Repeated container as @c result_container .
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
 *  @return  Split container as @c result_container_nested .
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
 *  @brief  Split the container with occurrences of value.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   Values     Values to split with.
 *  @return  Split container as @c result_container_nested .
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
 *  @brief  Split the container with occurrences of any of pattern.
 *
 *  @tparam  Container        Compatible container type.
 *  @tparam  NestedContainer  Compatible nested container type.
 *  @param   container        Container.
 *  @param   patterns         Patterns to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible Container, cu_compatible_nested NestedContainer>
[[nodiscard]] inline constexpr auto split_occ_seq(
    const Container       &container,
    const NestedContainer &patterns
)
{
    result_container_nested<Container> result;
    for (auto &pattern : patterns)
    {
        result = cu::combine(result, split_seq(container, pattern));
    }
    return result;
}

/**
 *  @brief  Split the container with value.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   value      Value to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto split(
    const Container             &container,
    const value_type<Container> &value
)
{
    return split_seq(container, Container({ value }));
}

/**
 *  @brief  Return element at index, or a default-constructed instance of the
 *          value type if the index is invalid.
 *
 *  @tparam  Container  Compatible container type.
 *  @param   container  Container.
 *  @param   index      Value to split with.
 *  @return  Element at index or default constructed instance of type.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto boundless_access(
    const Container &container,
    std::size_t      index
)
{
    if (index >= container.size()) return value_type<Container>();
    return *(container.begin() + index);
}

/**
 *  @brief  A boundless vector.
 *
 *  Index-access of this vector always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  T      Type of element.
 *  @tparam  Alloc  Allocator type, defaults to @c std::allocator<T> .
 */
template<typename T, typename Alloc = std::allocator<T>>
requires(std::is_default_constructible_v<T>)
struct boundless_vector : std::vector<T, Alloc> {
    using std::vector<T, Alloc>::vector;

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index) -> T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> const T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) -> T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) const -> const T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first element, or a default constructed instance of
     *          the value type when the vector is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> T &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the first element, or a default constructed instance of
     *          the value type when the vector is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> const T &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last element, or a default constructed instance of
     *          the value type when the vector is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> T &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief  Get the last element, or a default constructed instance of
     *          the value type when the vector is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> const T &
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  A boundless array.
 *
 *  Index-access of this array always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  T  Type of element.
 *  @tparam  N  Size of array.
 */
template<typename T, std::size_t N>
requires(std::is_default_constructible_v<T>)
struct boundless_array : std::array<T, N> {
    using std::array<T, N>::array;

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index) -> T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> const T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) -> T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) const -> const T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first element, or a default constructed instance of
     *          the value type when the array is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> T &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the first element, or a default constructed instance of
     *          the value type when the array is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> const T &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last element, or a default constructed instance of
     *          the value type when the array is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> T &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief  Get the last element, or a default constructed instance of
     *          the value type when the array is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> const T &
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  A boundless span.
 *
 *  Index-access of this span always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  T       Type of element.
 *  @tparam  Extent  The number of elements in the sequence, or
 *                   @c std::dynamic_extent if dynamic (default).
 */
template<typename T, std::size_t Extent = std::dynamic_extent>
requires(std::is_default_constructible_v<T>)
struct boundless_span : std::span<T, Extent> {
    using std::span<T, Extent>::span;

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index) -> T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> const T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) -> T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) const -> const T &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first element, or a default constructed instance of
     *          the value type when the span is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> T &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the first element, or a default constructed instance of
     *          the value type when the span is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> const T &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last element, or a default constructed instance of
     *          the value type when the span is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> T &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief  Get the last element, or a default constructed instance of
     *          the value type when the span is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> const T &
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  A boundless basic string.
 *
 *  Index-access of this string always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  CharT   Character type.
 *  @tparam  Traits  Character traits type.
 *  @tparam  Alloc   Allocator type, defaults to @c std::allocator<CharT> .
 */
template<typename CharT, typename Traits = std::char_traits<CharT>,
    typename Alloc = std::allocator<CharT>>
requires(std::is_default_constructible_v<CharT>)
struct boundless_basic_string : std::basic_string<CharT, Traits, Alloc> {
    using std::basic_string<CharT, Traits, Alloc>::basic_string;

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index) -> CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index) const -> const CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) -> CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index)
    const -> const CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first character, or a default constructed instance of
     *          the character type when the string is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> CharT &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the first character, or a default constructed instance of
     *          the character type when the string is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> const CharT &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last character, or a default constructed instance of
     *          the character type when the string is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> CharT &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief  Get the last character, or a default constructed instance of
     *          the character type when the string is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> const CharT &
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  A boundless basic string view.
 *
 *  Index-access of this string view always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  CharT   Character type.
 *  @tparam  Traits  Character traits type.
 */
template<typename CharT, typename Traits = std::char_traits<CharT>>
requires(std::is_default_constructible_v<CharT>)
struct boundless_basic_string_view : std::basic_string_view<CharT, Traits> {
    using std::basic_string_view<CharT, Traits>::basic_string_view;

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index) -> CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index) const -> const CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) -> CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index)
    const -> const CharT &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first character, or a default constructed instance of
     *          the character type when the view is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> CharT &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the first character, or a default constructed instance of
     *          the character type when the view is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> const CharT &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last character, or a default constructed instance of
     *          the character type when the view is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> CharT &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief  Get the last character, or a default constructed instance of
     *          the character type when the view is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> const CharT &
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  boundless_A string of @c char .
 */
using boundless_string = boundless_basic_string<char>;

/**
 *  @brief  boundless_A string of @c wchar_t .
 */
using boundless_wstring = boundless_basic_string<wchar_t>;

/**
 *  @brief  boundless_A string of @c char16_t .
 */
using boundless_u16string = boundless_basic_string<char16_t>;

/**
 *  @brief  boundless_A string of @c char32_t .
 */
using boundless_u32string = boundless_basic_string<char32_t>;

/**
 *  @brief  A non-owning @boundless_c string .
 */
using boundless_string_view = boundless_basic_string_view<char>;

/**
 *  @brief  A non-owning @c boundless_wstring .
 */
using boundless_wstring_view = boundless_basic_string_view<wchar_t>;

/**
 *  @brief  A non-owning @c boundless_u16string .
 */
using boundless_u16string_view = boundless_basic_string_view<char16_t>;

/**
 *  @brief  A non-owning @c boundless_u32string .
 */
using boundless_u32string_view = boundless_basic_string_view<char32_t>;

/**
 *  @brief  Container Utilities compatible enumerator for @c enumerated_array .
 *
 *  The type must be an enumerator with a @c max as a member.  The @c max member
 *  must be the largest member in the enumerator (Implementation pending).
 *
 *  @tparam  E  Enumerator type.
 *
 *  @todo  After reflection support is introduced, iterate over all the members
 *         and determine that the @c max member is the largest member.
 */
template<typename E>
concept cu_compatible_enum = std::is_enum_v<E> && requires { { E::max }; };

/**
 *  @brief  Integral constant for the enumerator's member.
 *  @tparam  E  Container Utilities compatible enumerator type.
 */
template<cu_compatible_enum E, E value>
struct enum_value : std::integral_constant<int, std::to_underlying (value)> {};

/**
 *  @brief  Helper to get the value of the enumerator's member.
 *  @tparam  E  Container Utilities compatible enumerator type.
 */
template<cu_compatible_enum E, E value>
inline constexpr auto enum_value_v = enum_value<E, value>::value;

/**
 *  @brief  Integral constant for the enumerator's @c max member.
 *  @tparam  E  Container Utilities compatible enumerator type.
 */
template<cu_compatible_enum E>
struct enum_max : enum_value<E, E::max> {};

/**
 *  @brief  Helper to get the value of the enumerator's @c max member.
 *  @tparam  E  Container Utilities compatible enumerator type.
 */
template<cu_compatible_enum E>
inline constexpr auto enum_max_v = enum_max<E>::value;

/**
 *  @brief  Array with enumerator as index.
 *
 *  @tparam  T  Type of element.
 *  @tparam  E  Container Utilities compatible enumerator type.
 */
template<typename T, cu_compatible_enum E>
struct enumerated_array : std::array<E, enum_max_v<E>> {
    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::array<E, enum_max_v<E>>;

    using base::array;

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (E enumerator) -> T &
    {
        return base::operator[] (enum_value (enumerator));
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (E enumerator)
    const -> const T &
    {
        return base::operator[] (enum_value (enumerator));
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(E enumerator) -> T &
    {
        return base::at(enum_value(enumerator));
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(E enumerator) const -> const T &
    {
        return base::at(enum_value(enumerator));
    }
};

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
 *  @return  Combined container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
 *  @return  Value-appended container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
 *  @return  Filtered container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
 *  @return  Filtered container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
 *  @return  Repeated container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
 *  @return  Repeated container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
 *  @return  Split container as @c result_container_nested .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
 *  @return  Split container as @c result_container_nested .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::string_view.
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
