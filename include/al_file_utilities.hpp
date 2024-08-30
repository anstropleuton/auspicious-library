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
#include <cstring>
#include <fstream>
#include <ios>
#include <stdexcept>
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
 *  @brief  File Utilities.  Not what you are thinking.
 */
namespace fu {

/**
 *  @brief  Read all the file's content at once and return @c std::string
 *          representing the file's content.
 *
 *  @param  filename  Filename.
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

} // namespace fu

} // namespace auspicious_library
