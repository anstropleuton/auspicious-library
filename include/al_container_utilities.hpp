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
#include <array>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <map>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
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
 *  @c value_type typename member.
 *
 *  @tparam  Container  The container type.
 */
template<typename Container>
concept cu_compatible = requires {
    { Container().begin() } -> std::contiguous_iterator;
    { Container().end() } -> std::contiguous_iterator;
    { std::declval<typename Container::value_type>() };
};

/**
 *  @brief  Container's value_type member.
 *  @tparam  Container  A compatible container type.
 */
template<cu_compatible Container>
using value_type = Container::value_type;

/**
 *  @brief  All Container Utilities return this container.
 *  @tparam  Container  A compatible container type.
 */
template<cu_compatible Container>
using result_container = std::vector<value_type<Container>>;

/**
 *  @brief  All Container Utilities return this container if the result is
 *          nested.
 *  @tparam  Container  A compatible container type.
 */
template<cu_compatible Container>
using result_container_nested = std::vector<std::vector<value_type<Container>>>;

/**
 *  @brief  Nested container compatible for Container Utilities.
 *
 *  The container and it's value type must satisfy @c cu_compatible .
 *
 *  @tparam  Container  The container type.
 */
template<typename Container>
concept cu_compatible_nested =
    cu_compatible<Container>
 && cu_compatible<value_type<Container>>;

/**
 *  @brief  A compatible container for @c boundless_access.
 *
 *  The container must satisfy @c cu_compatible and it's value type should also
 *  assignable with default constructed value type.
 *
 *  @tparam  Container  The container type.
 */
template<typename Container>
concept boundless_accessible = cu_compatible<Container>
    && requires(value_type<Container> value) {
    { value = {} };
    { *(Container().begin()) } -> std::same_as<value_type<Container> &>;
};

/**
 *  @brief  Return element at index, or a default-constructed instance of the
 *          value type if the index is invalid.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   index      An index specifying element.
 *  @return  Element at index or default constructed instance of type.
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto boundless_access(
    const Container  &container,
    std::size_t index
)
{
    if (index >= container.size()) return value_type<Container>();
    return *(container.begin() + index);
}

/**
 *  @brief  Return element at index, or a default-constructed instance of the
 *          value type if the index is invalid.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   index      An index specifying element.
 *  @return  Element at index or default constructed instance of type.
 */
template<boundless_accessible Container>
[[nodiscard]] inline constexpr auto boundless_access(
    Container  &container,
    std::size_t index
) -> value_type<Container> &
{
    static value_type<Container> value;

    // Always initialize to default every time it is accessed
    value = {};
    if (index >= container.size()) return value;
    return *(container.begin() + index);
}

/**
 *  @brief  A boundless vector.
 *
 *  Index-access of this vector always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  T      The type of element.
 *  @tparam  Alloc  Allocator type, defaults to @c std::allocator<T> .
 */
template<typename T, typename Alloc = std::allocator<T>>
requires(std::is_default_constructible_v<T>)
struct boundless_vector : std::vector<T, Alloc> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::vector<T, Alloc>;

    using base::vector;

    /**
     *  @brief  Creates a vector with no elements.
     */
    inline constexpr boundless_vector() = default;

    /**
     *  @brief  Creates a vector with no elements.
     *
     *  @param  allocator  An allocator.
     *  @see  @c std::vector 's constructor for more details.
     */
    explicit inline constexpr boundless_vector(
        const Alloc &allocator
    ) noexcept : base(allocator) {}

    /**
     *  @brief  Creates a vector with default constructed elements.
     *
     *  @param  size       The number of elements to initially create.
     *  @param  allocator  An allocator.
     *  @see  @c std::vector 's constructor for more details.
     */
    explicit inline constexpr boundless_vector(
        std::size_t  size,
        const Alloc &allocator = Alloc()
    ) : base(size, allocator) {}

    /**
     *  @brief  Creates a vector with copies of an exemplar element.
     *
     *  @param  size       The number of elements to initially create.
     *  @param  value      An element to copy.
     *  @param  allocator  An allocator.
     *  @see  @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        std::size_t  size,
        const T     &value,
        const Alloc &allocator = Alloc()
    ) : base(size, value, allocator) {}

    /**
     *  @brief  Vector copy constructor.
     *
     *  @param  vector  The other vector to copy from.
     *  @see  @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(const boundless_vector &vector) = default;

    /**
     *  @brief  Vector move constructor.
     *
     *  @param  vector  The other vector to move from.
     *  @see  @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(boundless_vector &&vector)
    noexcept = default;

    /**
     *  @brief  Copy constructor with alternative allocator.
     *
     *  @param  vector     The other vector to copy from.
     *  @param  allocator  An allocator.
     *  @see  @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        const boundless_vector &vector,
        const Alloc            &allocator
    ) : base((base)vector, allocator) {}

    /**
     *  @brief  Move constructor with alternative allocator.
     *
     *  @param  vector     The other vector to move from.
     *  @param  allocator  An allocator.
     *  @see  @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        boundless_vector &&vector,
        const Alloc       &allocator
    ) noexcept : base(std::move((base &) vector, allocator)) {}

    /**
     *  @brief  Creates a vector from an initializer list.
     *
     *  @param  list       An @c std::initializer_list .
     *  @param  allocator  An allocator.
     *  @see  @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        std::initializer_list<T> list,
        const Alloc             &allocator = Alloc()
    ) : base(list, allocator) {}

    /**
     *  @brief  Creates a vector from a range.
     *
     *  @tparam  InputIterator  The type of input iterators.
     *  @param   first          An input iterator.
     *  @param   last           An input iterator.
     *  @param   allocator      An allocator.
     *  @see  @c std::vector 's constructor for more details.
     */
    template<std::input_iterator InputIterator>
    inline constexpr boundless_vector(
        InputIterator first,
        InputIterator last,
        const Alloc  &allocator = Alloc()
    ) : base(first, last, allocator) {}

    /**
     *  @brief  Default destructor.
     *  @see  @c std::vector 's destructor for more details.
     */
    inline constexpr ~boundless_vector() = default;

    /**
     *  @brief  Vector assign operator.
     *
     *  @param  vector  A vector of identical element and allocator types.
     *  @return  Reference to self.
     *  @see  @c std::vector 's @c operator= for more details.
     */
    inline constexpr auto operator= (
        const boundless_vector &vector
    ) -> boundless_vector & = default;

    /**
     *  @brief  Vector move assign operator.
     *
     *  @param  vector  A vector of identical element and allocator types.
     *  @return  Reference to self.
     *  @see  @c std::vector 's @c operator= for more details.
     */
    inline constexpr auto operator= (
        boundless_vector &&vector
    ) -> boundless_vector & = default;

    /**
     *  @brief  Vector list assignment operator.
     *
     *  @param  list  An initializer list.
     *  @return  Reference to self.
     *  @see  @c std::vector 's @c operator= for more details.
     */
    inline constexpr auto operator= (
        std::initializer_list<T> list
    ) -> boundless_vector &
    {
        return base::operator= (list);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
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
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> T
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
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
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) const -> T
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
    [[nodiscard]] inline constexpr auto front() const -> T
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
    [[nodiscard]] inline constexpr auto back() const -> T
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  Template parameter deduction guide for @c boundless_vector .
 *
 *  Deduce types from initializer.
 *
 *  @tparam  InputIterator  The type of input iterator.
 *  @tparam  ValueType      The type of elements of vector.
 *  @tparam  AllocatorType  The type of an allocator object.
 */
template<std::input_iterator InputIterator,
    typename ValueType = std::iterator_traits<InputIterator>::value_type,
    typename AllocatorType = std::allocator<ValueType>>
boundless_vector(InputIterator, InputIterator, AllocatorType = AllocatorType())
-> boundless_vector<ValueType, AllocatorType>;

/**
 *  @brief  A boundless array.
 *
 *  Index-access of this array always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  T  The type of element.
 *  @tparam  N  The size of array.
 */
template<typename T, std::size_t N>
requires(std::is_default_constructible_v<T>)
struct boundless_array : std::array<T, N> {

    // Woah, std::array has no constructors!

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
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
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> T
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
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
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) const -> T
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
    [[nodiscard]] inline constexpr auto front() const -> T
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
    [[nodiscard]] inline constexpr auto back() const -> T
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  Template parameter deduction guide for @c boundless_array .
 *
 *  Deduce types from initializer.
 *
 *  @tparam  T  The type of elements.
 *  @tparam  U  The type of multiple elements in initializer.
 */
template<typename T, typename... U>
requires(std::is_same_v<T, U> && ...)
boundless_array(T, U...) -> boundless_array<T, 1 + sizeof... (U)>;

/**
 *  @brief  A boundless span.
 *
 *  Index-access of this span always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  T       The type of element.
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
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> T
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) const -> T
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first element, or a default constructed instance of
     *          the value type when the span is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> T
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last element, or a default constructed instance of
     *          the value type when the span is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> T
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from raw array.
 *
 *  @tparam  T  The type of array elements.
 *  @tparam  N  The number of array elements.
 */
template<typename T, size_t N>
boundless_span(T(&)[N]) -> boundless_span<T, N>;

/**
 *  @brief  Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from @c std::array .
 *
 *  @tparam  T  The type of array elements.
 *  @tparam  N  The number of array elements.
 */
template<typename T, size_t N>
boundless_span(std::array<T, N> &) -> boundless_span<T, N>;

/**
 *  @brief  Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from constant @c std::array.
 *
 *  @tparam  T  The type of array elements.
 *  @tparam  N  The number of array elements.
 */
template<typename T, size_t N>
boundless_span(const std::array<T, N> &)
-> boundless_span<const T, N>;

/**
 *  @brief  Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from iterators.
 *
 *  @tparam  I    The type of iterator.
 *  @tparam  End  The type of end of the iterator.
 */
template<std::contiguous_iterator I, typename End>
boundless_span(I, End)
-> boundless_span<std::remove_reference_t<std::iter_reference_t<I>>>;

/**
 *  @brief  Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from range.
 *
 *  @tparam  Range  A range type.
 */
template<stdr::contiguous_range Range>
boundless_span(Range &&)
-> boundless_span<std::remove_reference_t<stdr::range_reference_t<Range &>>>;

/**
 *  @brief  A boundless basic string.
 *
 *  Index-access of this string always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  CharT   The character type.
 *  @tparam  Traits  The character traits type.
 *  @tparam  Alloc   The allocator type, defaults to @c std::allocator<CharT> .
 */
template<typename CharT, typename Traits = std::char_traits<CharT>,
    typename Alloc = std::allocator<CharT>>
requires(std::is_default_constructible_v<CharT>)
struct boundless_basic_string : std::basic_string<CharT, Traits, Alloc> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::basic_string<CharT, Traits, Alloc>;

    using base::basic_string;

    /**
     *  @brief  Default constructor creates an empty string.
     */
    inline constexpr boundless_basic_string()
    noexcept (std::is_default_constructible_v<Alloc>) = default;

    /**
     *  @brief  Create an empty string using allocator.
     *
     *  @param  allocator  An allocator.
     *  @see  @c std::basic_string 's constructor for more details.
     */
    inline constexpr boundless_basic_string(
        const Alloc &allocator
    ) noexcept : base(allocator) {}

    /**
     *  @brief  String copy constructor.
     *
     *  @param  string  The other string to copy from.
     *  @see  @c std::basic_string 's constructor for more details.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string
    ) = default;

    /**
     *  @brief  Creates a string as a copy of a substring.
     *
     *  @param  string     A string to copy from.
     *  @param  pos        The index of first character to copy from.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string,
        std::size_t                   pos,
        const Alloc                  &allocator = Alloc()
    ) : base(string, pos, allocator) {}

    /**
     *  @brief  Creates a string as a copy of a substring.
     *
     *  @param  string     A string to copy from.
     *  @param  pos        The index of first character to copy from.
     *  @param  n          The number of characters to copy.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string,
        std::size_t                   pos,
        std::size_t                   n,
        const Alloc                  &allocator = Alloc()
    ) : base(string, pos, n, allocator) {}

    /**
     *  @brief  Creates a string initialized by a character array.
     *
     *  @param  string     A character array.
     *  @param  n          The number of characters to copy.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        const CharT *string,
        std::size_t  n,
        const Alloc &allocator = Alloc()
    ) : base(string, n, allocator) {}

    /**
     *  @brief  Creates a string initialized by a character array.
     *
     *  @param  string     A null-terminated character array.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        const CharT *string,
        const Alloc &allocator = Alloc()
    ) : base(string, allocator) {}

    /**
     *  @brief  Creates a string with multiple characters.
     *
     *  @param  n          The number of characters.
     *  @param  c          The character to use.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        std::size_t  n,
        CharT        c,
        const Alloc &allocator
    ) : base(n, c, allocator) {}

    /**
     *  @brief  String move constructor.
     */
    inline constexpr boundless_basic_string(
        boundless_basic_string &&string
    ) noexcept = default;

    /**
     *  @brief  Creates a string from an initializer list.
     *
     *  @param  list       An @c std::initializer_list of characters.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        std::initializer_list<CharT> list,
        const Alloc                 &allocator = Alloc()
    ) : base(list, allocator) {}

    /**
     *  @brief  Copy constructor with alternative allocator.
     *
     *  @param  string     The other string to copy from.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string,
        const Alloc                  &allocator
    ) : base(string, allocator) {}

    /**
     *  @brief  Move constructor with alternative allocator.
     *
     *  @param  string     The other string to move from.
     *  @param  allocator  An allocator.
     */
    inline constexpr boundless_basic_string(
        boundless_basic_string &&string,
        const Alloc             &allocator
    ) : base(std::move(string), allocator) {}

    /**
     *  @brief  Creates a string from a range.
     *
     *  @tparam  InputIterator  The type of input iterator.
     *  @param   first          An input iterator.
     *  @param   last           An input iterator.
     *  @param   allocator      An allocator.
     */
    template<std::input_iterator InputIterator>
    inline constexpr boundless_basic_string(
        InputIterator first,
        InputIterator last,
        const Alloc  &allocator = Alloc()
    ) : base(first, last, allocator) {}

    /**
     *  @brief  Creates a string from a substring of a @c std::basic_string_view .
     *
     *  @tparam  T          A type convertible to @c std::basic_string_view .
     *  @param   t          A string to copy from.
     *  @param   pos        The index of the first character to copy from.
     *  @param   n          The number of characters to copy.
     *  @param   allocator  An allocator.
     */
    template<std::convertible_to<std::basic_string_view<CharT>> T>
    inline constexpr boundless_basic_string(
        const T     &t,
        std::size_t  pos,
        std::size_t  n,
        const Alloc &allocator = Alloc()
    ) : base(t, pos, n, allocator) {}

    /**
     *  @brief  Creates a string from a @c std::basic_string_view .
     *
     *  @tparam  T          A type convertible to @c std::basic_string_view .
     *  @param   t          A string to copy from.
     *  @param   allocator  An allocator.
     */
    template<std::convertible_to<std::basic_string_view<CharT>> T>
    inline constexpr boundless_basic_string(
        const T     &t,
        const Alloc &allocator = Alloc()
    ) : base(t, allocator) {}

    /**
     *  @brief  Default destructor.
     */
    inline constexpr ~boundless_basic_string() = default;

    /**
     *  @brief  String assign operator.
     *
     *  @param  string  A string of identical char type and allocator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        const boundless_basic_string &string
    ) -> boundless_basic_string & = default;

    /**
     *  @brief  Copy contents of @c string to this string.
     *
     *  @param  string  A string of identical char type and allocator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        const CharT *string
    ) -> boundless_basic_string &
    {
        base::operator= (string);
        return *this;
    }

    /**
     *  @brief  Set value of string to one character.
     *
     *  @param  c  A character.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (CharT c) -> boundless_basic_string &
    {
        base::operator= (c);
        return *this;
    }

    /**
     *  @brief  String move assign operator.
     *
     *  @param  string  A string of identical char type and allocator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        boundless_basic_string &&string
    ) -> boundless_basic_string & = default;

    /**
     *  @brief  Set value of string using an @c std::initializer_list.
     *
     *  @param  list  An @c std::initializer_list of char type.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        std::initializer_list<CharT> list
    ) -> boundless_basic_string &
    {
        base::operator= (list);
        return *this;
    }

    /**
     *  @brief  Set value of string from a @c std::basic_string_view .
     *
     *  @tparam  T          A type convertible to @c std::basic_string_view .
     *  @param   t          A string to copy from.
     *  @return  Reference to self.
     */
    template<std::convertible_to<std::basic_string_view<CharT>> T>
    inline constexpr auto operator= (
        const T &t
    ) -> boundless_basic_string &
    {
        base::operator= (t);
        return *this;
    }

    /**
     *  @brief  Convert to a @c std::basic_string_view .
     *  @return  @c std::basic_string_view of this string.
     */
    [[nodiscard]] inline constexpr operator std::basic_string_view<CharT>()
    const noexcept
    {
        return std::basic_string_view((base) * this);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index
    ) const -> CharT
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index)
    const -> CharT
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first character, or a default constructed instance of
     *          the character type when the string is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> CharT
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last character, or a default constructed instance of
     *          the character type when the string is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> CharT
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
 *  @tparam  CharT   The character type.
 *  @tparam  Traits  The character traits type.
 */
template<typename CharT, typename Traits = std::char_traits<CharT>>
requires(std::is_default_constructible_v<CharT>)
struct boundless_basic_string_view : std::basic_string_view<CharT, Traits> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::basic_string_view<CharT, Traits>;

    using base::basic_string_view;

    /**
     *  @brief  Default constructor.
     */
    inline constexpr boundless_basic_string_view() noexcept = default;

    /**
     *  @brief  String view copy constructor.
     *  @param  string  The other string view to copy from.
     */
    inline constexpr boundless_basic_string_view(
        const boundless_basic_string_view &string
    ) noexcept = default;

    /**
     *  @brief  Creates a string view from a null-terminated character array.
     *  @param  string  A null-terminated character array.
     */
    inline constexpr boundless_basic_string_view(
        const CharT *string
    ) : base(string) {}

    /**
     *  @brief  Creates a string from a character array.
     *
     *  @param  string  A character array of at least @c n length.
     *  @param  n       The number of characters to create a view.
     */
    inline constexpr boundless_basic_string_view(
        const CharT *string,
        std::size_t  n
    ) : base(string, n) {}

    /**
     *  @brief  Creates a string view from a range.
     *
     *  @tparam  InputIterator  An input iterator type.
     *  @param   first          An input iterator.
     *  @param   last           An input iterator.
     */
    template<std::input_iterator InputIterator>
    inline constexpr boundless_basic_string_view(
        InputIterator first,
        InputIterator last
    ) noexcept (noexcept (last - first)) : base(first, last) {}

    /**
     *  @brief  Creates a string view from a C++20 range.
     *
     *  @tparam  Range  A range type.
     *  @param   range  A range of char type.
     */
    template<stdr::range Range>
    explicit inline constexpr boundless_basic_string_view(
        Range range
    ) : base(range) {}

    /**
     *  @brief  String view assign operator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (const boundless_basic_string_view &)
    noexcept -> boundless_basic_string_view & = default;

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index
    ) const -> CharT
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get a character at index, or a default constructed instance of
     *          the character type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index)
    const -> CharT
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief  Get the first character, or a default constructed instance of
     *          the character type when the string view is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> CharT
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief  Get the last character, or a default constructed instance of
     *          the character type when the string view is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> CharT
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
 *  @tparam  T  The type of element.
 *  @tparam  E  A Container Utilities compatible enumerator type.
 */
template<typename T, cu_compatible_enum E>
struct enumerated_array : std::array<T, enum_max_v<E>> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::array<E, enum_max_v<E>>;

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline auto operator[] (E enumerator) -> T &
    {
        return base::operator[] (enum_value_v<E, enumerator>);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline auto operator[] (E enumerator)
    const -> T
    {
        return base::operator[] (enum_value_v<E, enumerator>);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline auto at(E enumerator) -> T &
    {
        return base::at(enum_value_v<E, enumerator>);
    }

    /**
     *  @brief  Get an element at index, or a default constructed instance of
     *          the value type when index is invalid.
     *
     *  @param  index  An index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline auto at(E enumerator) const -> T
    {
        return base::at(enum_value_v<E, enumerator>);
    }
};

/**
 *  @brief  Get the subset of the container's elements.
 *
 *  @tparam  Container        A compatible container type.
 *  @param   container        A container.
 *  @param   first_inclusive  The first index (inclusive).
 *  @param   last_exclusive   The last index (exclusive).
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
        container.begin() + first_inclusive,
        container.begin() + last_exclusive);
}

/**
 *  @brief  Copy containers into one container.
 *
 *  @tparam  Container    A compatible container type.
 *  @param   container_a  The first container.
 *  @param   container_b  The second container.
 *  @return  Combined container as @c result_container .
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto combine(
    const Container &container_a,
    const Container &container_b
)
{
    return result_container_nested<Container> {
        result_container<Container>(container_a.begin(), container_a.end()),
        result_container<Container>(container_b.begin(), container_b.end())
    } | stdv::join
      | stdr::to<result_container<Container>>();
}

/**
 *  @brief  Copy container and value into one container.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   value      A value of container's value type.
 *  @return  Value-appended container as @c result_container .
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto combine(
    const Container             &container,
    const value_type<Container> &value
)
{
    return combine(container, result_container<Container> { value });
}

/**
 *  @brief  Filter out the occurrences of sequence from the container.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   pattern    A sequence to remove.
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   values     The elements to remove.
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
 *  @tparam  Container        A compatible container type.
 *  @tparam  NestedContainer  A compatible container type nested container type.
 *  @param   container        A container.
 *  @param   patterns         The sequences to remove.
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   value      A value to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto filter_out(
    const Container             &container,
    const value_type<Container> &value
)
{
    return filter_out_seq(container, result_container<Container> { value });
}

/**
 *  @brief  Repeat container @c n times.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   n          The number of times to repeat.
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   n          The number of times to repeat.
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   pattern    A pattern to split with.
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   values     The values to split with.
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
 *  @tparam  Container        A compatible container type.
 *  @tparam  NestedContainer  A compatible container type nested container type.
 *  @param   container        A container.
 *  @param   patterns         The patterns to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible Container, cu_compatible_nested NestedContainer>
[[nodiscard]] inline constexpr auto split_occ_seq(
    const Container       &container,
    const NestedContainer &patterns
)
{
    // Again couldn't find standard library to do this heavy job, so...
    result_container_nested<Container> result;
    auto it = container.begin();

    while (it != container.end())
    {
        auto        next_it      = container.end();
        std::size_t pattern_size = (std::size_t)-1;
        for (auto &pattern : patterns)
        {
            // Use std::search instead of std::find_first_of to find sequence
            auto tmp = std::search(it, container.end(), pattern.begin(),
                pattern.end());

            if (next_it > tmp)
            {
                next_it      = tmp;
                pattern_size = pattern.size();
            }
        }

        result.emplace_back(result_container<Container>(it, next_it));
        it = next_it;
        if (it != container.end()) it += pattern_size;
    }

    return result;
}

/**
 *  @brief  Split the container with value.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   value      A value to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible Container>
[[nodiscard]] inline constexpr auto split(
    const Container             &container,
    const value_type<Container> &value
)
{
    return split_seq(container, result_container<Container> { value });
}

} // namespace cu

/**
 *  @brief  Container Utilities, operators version.
 */
namespace cu_operators {

/**
 *  @brief  Copy containers into one container.
 *
 *  @tparam  Container    A compatible container type.
 *  @param   container_a  The first container.
 *  @param   container_b  The second container.
 *  @return  Combined container as @c result_container .
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   value      A value of container's value type.
 *  @return  Value-appended container as @c result_container .
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   pattern    A sequence to remove.
 *  @return  Filtered container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::basic_string_view .
 *
 *  @see  cu::filter_out_seq.
 */
template<cu::cu_compatible Container>
requires(!std::is_same_v<Container, std::string>
      && !std::is_same_v<Container, std::string_view>)
[[nodiscard]] inline constexpr auto operator- (
    const Container &container,
    const Container &pattern
)
{
    return cu::filter_out_seq(container, pattern);
}

/**
 *  @brief  Filter out the occurrences of value from the container.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   value      A value to remove.
 *  @return  Filtered container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::basic_string_view .
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
 *  @brief  Repeat container @c n times.
 *
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   n          The number of times to repeat.
 *  @return  Repeated container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::basic_string_view .
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   n          The number of times to repeat.
 *  @return  Repeated container as @c result_container .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::basic_string_view .
 *
 *  @see  cu::repeat.
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   pattern    A pattern to split with.
 *  @return  Split container as @c result_container_nested .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::basic_string_view .
 *
 *  @see  cu::split_seq.
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
 *  @tparam  Container  A compatible container type.
 *  @param   container  A container.
 *  @param   value      A value to split with.
 *  @return  Split container as @c result_container_nested .
 *
 *  @note  Use String Manipulators' operators for @c std::string or
 *         @c std::basic_string_view .
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
