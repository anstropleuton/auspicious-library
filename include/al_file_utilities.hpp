/**
 *  @file    al_file_utilities.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   General functionality to work with files.
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

#include <bit>
#include <concepts>
#include <cstring>
#include <fstream>
#include <ios>
#include <stdexcept>
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
 *  @brief  File Utilities.  Not what you are thinking.
 *
 *  Contains utilities regarding file handling, and functionality to handle
 *  binary files of SD format.
 *
 *  SD Format is a binary format which consists of chunks.  Each chunk is a pair
 *  of *Size* and *Data*.  The Size is the number of bytes of the raw data.  The
 *  Data is the raw data, i.e., the memory map of an object.
 *
 *  @note  The SD Format does not specify the endianness of the data, neither
 *         does the code to handle this format.  This implies that the binary
 *         file may not be portable for systems with different endianness.
 *  @todo  When C++ introduces a good reflection support, implement automatic
 *         endianness conversion to make the binary file actually be portable.
 *
 *  @todo  The biggest todo: implement stuff.
 */
namespace fu {

/**
 *  @brief  Read all the file's content at once and return @c std::string
 *          representing the file's content.
 *
 *  @param  filename  The filename.
 *  @return  @c std::string representing all the file's contents.
 *
 *  @note  Large files causes problems.
 */
[[nodiscard]] inline auto read_all(std::string_view filename)
{
    std::ifstream infile((std::string(filename)));
    if (!infile)
    {
        throw std::runtime_error(std::format("Failed to open file {}",
            filename));
    }

    return std::string(std::istreambuf_iterator(infile), {});
}

/**
 *  @brief  A chunk in the SD file format.
 *  @see  Detailed Description of namespace @c fu.
 */
struct sd_chunk {

    /**
     *  @brief  The number of bytes of @c data .
     */
    std::size_t size;

    /**
     *  @brief  The raw data of @c size bytes.
     *
     *  @note  The values pointed by the pointer are not changed.  It is user's
     *         responsibility to manage the memory.
     *  @todo  If nobody finds a use for `void *` data type for pointer for
     *         chunks or finds it tedious to manage memory (like we do), replace
     *         it with @c std::shared_ptr<void> .
     */
    void *data;
};

/**
 *  @brief  Convert an object to a chunk.
 *  
 *  @tparam  T  A trivially copyable type.
 *  @param   t  A trivially copyable value.
 *  @return  A newly allocated chunk.  Memory allocation failure may occur.
 *
 *  @note  Use @c delete_sd_chunk to free the allocated memory.
 */
template<typename T>
requires(std::is_trivially_copyable_v<T>)
[[nodiscard]] inline constexpr auto to_new_sd_chunk(const T &t) -> sd_chunk;

/**
 *  @brief  Convert a chunk to an object.
 *  
 *  @tparam  T      A trivially copyable chunk.
 *  @param   chunk  A chunk with memory layout of type @c T .
 *  @return  An object of T with memory layout of the chunk.
 */
template<typename T>
requires(std::is_trivially_copyable_v<T>)
[[nodiscard]] inline constexpr auto from_sd_chunk(sd_chunk chunk) -> T;

/**
 *  @brief  Delete the memory of a chunk.
 *
 *  After creating a chunk using @c to_new_sd_chunk , using it and being done
 *  with it, be sure to call this function to delete the memory of the created
 *  chunk.
 *
 *  @param  chunk  The chunk to delete.
 */
inline constexpr auto delete_sd_chunk(sd_chunk chunk) -> void;

} // namespace fu

} // namespace auspicious_library
