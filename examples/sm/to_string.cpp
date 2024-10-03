/**
 *  @file    boundless_containers.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   How to use SM's @c sm::to_string as I use in other examples.
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

#include <print>
#include <string>
#include <vector>

#include "al_string_manipulators.hpp"

using namespace auspicious_library;
using namespace std::string_literals;

int main()
{
    // Know these conversion tricks before checking out other examples
    std::vector vector = { 1, 2, 3, 4, 5 };

    // Default parameters
    std::println("Converted using default sm::to_string parameters: {}",
        sm::to_string(vector));

    // Customized parameters
    std::println("Converted by customizing basic sm::to_string parameters: {}",
        sm::to_string(vector, " -- "s, "<", ">"));

    // Customizing conversion function
    std::println("Converted by custom conversion for sm::to_string: {}",
        sm::to_string(vector, [&](int value) {
        // Square the number and then convert to string
        return std::to_string(value * value);
    }));

    // More defaults
    std::vector strings = { "Hello"s, "world"s };
    std::vector chars   = {
        'Y', 'o', 'u', ' ', 'a', 'r', 'e', ' ',
        'a', 'w', 'e', 's', 'o', 'm', 'e', '!' };

    std::println("Converted strings container using default sm::to_sting "
        "parameters: {}", sm::to_string(strings));

    std::println("Converted characters container using default sm::to_string "
        "parameters: {}", sm::to_string(chars));

    // Convert characters container to a string
    std::string string_from_chars = sm::chars_to_string(chars);

    std::println("Converted characters to an actual string: {}",
        string_from_chars);
}
