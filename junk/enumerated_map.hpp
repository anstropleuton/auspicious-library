/**
 *  @file    enumerated_map.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   A junk-ish experiment of @c enumerated_map .
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

#include "al_container_utilities.hpp"

#include <map>

/**
 *  @brief  All Auspicious Library's contents in this namespace.  Just do
 *          `using namespace auspicious_library` to make your life easier.
 */
namespace auspicious_library {

namespace cu {

/**
 *  @brief  Fixed-size map that has enumerator as key.
 *
 *  @tparam Key      Enumerator key.
 *  @tparam T        Type of mapped objects.
 *  @tparam Compare  Comparison function, defaults to @c std::less<Key> .
 *  @tparam Alloc    Allocator type, defaults to
 *                   `std::allocator<std::pair<const Key, T>>`.
 *
 *  @note  The subscript operator ( @c [] ) does not create new element.
 *
 *  @deprecated  This class is deprecated due to no found value due to an
 *               @c auspicious_library::cu::enumerated_array already exists.
 */
template<cu_compatible_enum Key, typename T,
    typename Compare = std::less<std::underlying_type_t<Key>>,
    typename Alloc = std::allocator<std::pair<Key, T>>>
struct [[deprecated("Use @c auspicious_library::cu::enumerated_array instead")]]
enumerated_map {

    /**
     *  @brief  Key type.
     */
    using key_type = Key;

    /**
     *  @brief  Mapped type.
     */
    using mapped_type = T;

    /**
     *  @brief  Value type (paired).
     */
    using value_type = std::pair<const key_type, mapped_type>;

    /**
     *  @brief  Comparator function type.
     */
    using key_compare = Compare;

    /**
     *  @brief  Allocator type.
     */
    using allocator_type = Alloc;

    /**
     *  @brief  The map type.
     */
    using map_t = std::map<key_type, mapped_type, key_compare, allocator_type>;

    /**
     *  @brief  Map's value compare type.
     */
    using value_compare = typename map_t::value_compare;

    /**
     *  @brief  Map's pointer type.
     */
    using pointer = typename map_t::pointer;

    /**
     *  @brief  Map's constant pointer type.
     */
    using const_pointer = typename map_t::const_pointer;

    /**
     *  @brief  Map's reference type.
     */
    using reference = typename map_t::reference;

    /**
     *  @brief  Map's constant reference type.
     */
    using const_reference = typename map_t::const_reference;

    /**
     *  @brief  Map's iterator type.
     */
    using iterator = typename map_t::iterator;

    /**
     *  @brief  Map's constant iterator type.
     */
    using const_iterator = typename map_t::const_iterator;

    /**
     *  @brief  Map's size type.
     */
    using size_type = typename map_t::size_type;

    /**
     *  @brief  Map's difference type.
     */
    using difference_type = typename map_t::difference_type;

    /**
     *  @brief  Map's reverse iterator type.
     */
    using reverse_iterator = typename map_t::reverse_iterator;

    /**
     *  @brief  Map's constant reverse iterator type.
     */
    using const_reverse_iterator = typename map_t::const_reverse_iterator;

    /**
     *  @brief  Map's node type.
     */
    using node_type = typename map_t::node_type;

    /**
     *  @brief  Map's insert return type.
     */
    using insert_return_type = typename map_t::insert_return_type;

    /**
     *  @brief  The map.
     */
    map_t map;

    /**
     *  @brief  Default constructor creates no elements.
     */
    inline constexpr enumerated_map()
    {
        refresh_enumerated_map();
    }

    /**
     *  @brief  Creates a map using allocator.
     */
    inline constexpr enumerated_map(
        const allocator_type &allocator = allocator_type()
    ) : map(allocator)
    {
        refresh_enumerated_map();
    }

    /**
     *  @brief  Copy constructor.
     */
    inline constexpr enumerated_map(const enumerated_map &map) = default;

    /**
     *  @brief  Move constructor.
     */
    inline constexpr enumerated_map(enumerated_map &&map) = default;

    /**
     *  @brief  Copy constructor using a @c std::map .
     *
     *  @param  map        A @c std::map .
     *  @param  allocator  An allocator object (optional).
     */
    inline constexpr enumerated_map(
        const map_t          &map,
        const allocator_type &allocator = allocator_type()
    ) : map(map, allocator) {}

    /**
     *  @brief  Move constructor using a @c std::map .
     *
     *  @param  map        A @c std::map .
     *  @param  allocator  An allocator object (optional).
     */
    inline constexpr enumerated_map(
        map_t               &&map,
        const allocator_type &allocator = allocator_type()
    ) : map(std::move(map), allocator) {}

    /**
     *  @brief  Creates a map with no elements.
     *
     *  @param  compare    A comparison object.
     *  @param  allocator  An allocator object (optional).
     */
    explicit inline constexpr enumerated_map(
        const key_compare    &compare,
        const allocator_type &allocator = allocator_type()
    ) : map(compare, allocator)
    {
        refresh_enumerated_map();
    }

    /**
     *  @brief  Refresh the map to contain only enumerator members as keys and
     *          values.
     */
    inline constexpr auto refresh_enumerated_map()
    {
        map.clear();
        auto hint = map.begin();

        for (auto i : std::ranges::iota(0zu, enum_max_v<key_type>))
        {
            hint = map.emplace_hint(hint, static_cast<key_type>(i),
                mapped_type());
        }
    }

    /**
     *  @brief  Get an iterator pointing to the first pair in the map.
     *  @return  Iterator pointing to the first pair in the map.
     */
    [[nodiscard]] inline constexpr auto begin() noexcept
    {
        return map.begin();
    }

    /**
     *  @brief  Get a read-only iterator pointing to the first pair in the map.
     *  @return  Read-only iterator pointing to the first pair in the map.
     */
    [[nodiscard]] inline constexpr auto begin() const noexcept
    {
        return map.begin();
    }

    /**
     *  @brief  Get an iterator pointing to the last pair in the map.
     *  @return  Iterator pointing to the last pair in the map.
     */
    [[nodiscard]] inline constexpr auto end() noexcept
    {
        return map.end();
    }

    /**
     *  @brief  Get a read-only iterator pointing to the last pair in the map.
     *  @return  Read-only iterator pointing to the last pair in the map.
     */
    [[nodiscard]] inline constexpr auto end() const noexcept
    {
        return map.end();
    }

    /**
     *  @brief  Get a reverse iterator pointing to the last pair in the map.
     *  @return  Reverse iterator pointing to the last pair in the map.
     */
    [[nodiscard]] inline constexpr auto rbegin() noexcept
    {
        return map.rbegin();
    }

    /**
     *  @brief  Get a read-only reverse iterator pointing to the last pair in
     *          the map.
     *  @return  Read-only reverse iterator pointing to the last pair in the
     *           map.
     */
    [[nodiscard]] inline constexpr auto rbegin() const noexcept
    {
        return map.rbegin();
    }

    /**
     *  @brief  Get a reverse iterator pointing to one before the first pair in
     *          the map.
     *  @return  Reverse iterator pointing to one before the first pair in the
     *           map.
     */
    [[nodiscard]] inline constexpr auto rend() noexcept
    {
        return map.rend();
    }

    /**
     *  @brief  Get a read-only reverse iterator pointing to one before the
     *          first pair in the map.
     *  @return  Read-only reverse iterator pointing to one before the first
     *           pair in the map.
     */
    [[nodiscard]] inline constexpr auto rend() const noexcept
    {
        return map.rend();
    }

    /**
     *  @brief  Get a read-only iterator pointing to the first pair in the map.
     *  @return  Read-only iterator pointing to the first pair in the map.
     */
    [[nodiscard]] inline constexpr auto cbegin() const noexcept
    {
        return map.cbegin();
    }

    /**
     *  @brief  Get a read-only iterator pointing to the last pair in the map.
     *  @return  Read-only iterator pointing to the last pair in the map.
     */
    [[nodiscard]] inline constexpr auto cend() const noexcept
    {
        return map.cend();
    }

    /**
     *  @brief  Get a read-only reverse iterator pointing to the last pair in
     *          the map.
     *  @return  Read-only reverse iterator pointing to the last pair in the
     *           map.
     */
    [[nodiscard]] inline constexpr auto crbegin() const noexcept
    {
        return map.crbegin();
    }

    /**
     *  @brief  Get a read-only reverse iterator pointing to one before the
     *          first pair in the map.
     *  @return  Read-only reverse iterator pointing to one before the first
     *           pair in the map.
     */
    [[nodiscard]] inline constexpr auto crend() const noexcept
    {
        return map.crend();
    }

    /**
     *  @brief  Access element at key.
     *
     *  @param  key                   Key from which data should be retrieved.
     *  @throw  @c std::out_of_range  If no such data is present.
     *  @return  A reference to the data.
     *
     *  @note  A new element cannot be created with invalid key.
     */
    inline constexpr auto operator[] (const key_type &key)
    -> mapped_type &
    {
        return map.at(key);
    }

    /**
     *  @brief  Access element at key.
     *
     *  @param  key                   Key from which data should be retrieved.
     *  @throw  @c std::out_of_range  If no such data is present.
     *  @return  A constant reference to the data.
     *
     *  @note  A new element cannot be created with invalid key.
     */
    inline constexpr auto operator[] (const key_type &key) const
    -> const mapped_type &
    {
        return map.at(key);
    }

    /**
     *  @brief  Access element at key.
     *
     *  @param  key                   Key from which data should be retrieved.
     *  @throw  @c std::out_of_range  If no such data is present.
     *  @return  A reference to the data.
     */
    [[nodiscard]] inline constexpr auto at(const key_type &key)
    -> mapped_type &
    {
        return map.at(key);
    }

    /**
     *  @brief  Access element at key.
     *
     *  @param  key                   Key from which data should be retrieved.
     *  @throw  @c std::out_of_range  If no such data is present.
     *  @return  A constant reference to the data.
     */
    [[nodiscard]] inline constexpr auto at(const key_type &key) const
    -> const mapped_type &
    {
        return map.at(key);
    }

    /**
     *  @brief  Swaps data with another map.
     *  @param  other  The map of same element and allocator type.
     */
    inline constexpr auto swap(enumerated_map &other)
    noexcept (std::is_nothrow_swappable_v<Compare>)
    {
        map.swap(other.map);
    }

    /**
     *  @brief  Swaps data with another map.
     *  @param  other  The map of same element and allocator type.
     */
    inline constexpr auto swap(map_t &other)
    noexcept (std::is_nothrow_swappable_v<Compare>)
    {
        map.swap(other);
    }

    /**
     *  @brief  Returns the key comparison object out of which the map was
     *          constructed.
     *  @return  The key comparison object out of which the map was constructed.
     */
    [[nodiscard]] inline constexpr auto key_comp() const
    {
        return map.key_comp();
    }

    /**
     *  @brief  Returns a value comparison object, built from the key comparison
     *          object out of which the %map was constructed.
     *  @return  A value comparison object, built from the key comparison object
     *           out of which the %map was constructed.
     */
    [[nodiscard]] inline constexpr auto value_comp() const
    {
        return map.value_comp();
    }

    /**
     *  @brief  Check if two maps are equal.
     *
     *  @param  a  First map.
     *  @param  b  Second map.
     *  @return  True if both maps are equal.
     */
    [[nodiscard]] friend inline constexpr auto operator== (
        const enumerated_map &a,
        const enumerated_map &b
    )
    {
        return a.map == b.map;
    }

    /**
     *  @brief  Compare two maps's orders.
     *
     *  @param  a  First map.
     *  @param  b  Second map.
     *  @return  A value indicating whether @c a is less than, equal to,
     *           greater than, or incomparable with @c b .
     */
    [[nodiscard]] friend inline constexpr auto operator<=> (
        const enumerated_map &a,
        const enumerated_map &b
    )
    {
        return a.map <=> b.map;
    }
};

} // namespace cu

} // namespace auspicious_library
