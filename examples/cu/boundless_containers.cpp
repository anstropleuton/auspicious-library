/**
 *  @file    boundless_containers.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   How to use CU's @c cu::boundless_access and boundless containers.
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
#include <vector>

#include "auspicious_library.hpp" // IWYU pragma: export

using namespace auspicious_library;

// This example is meant to be a kick-starter to start using boundless
// containers from container utilities, but they do not teach everything.  Refer
// to the documentation for more details
int main()
{
    std::vector my_vector = { 1, 2, 3, 4, 5 };

    // Access and edit vector using cu::boundless_access :
    cu::boundless_access(my_vector, 2) = 6; // Now the vector is
                                            // { 1, 2, 6, 4, 5 }

    std::println("cu::boundless_access(my_vector, 2) after setting it to 6: {}",
        cu::boundless_access(my_vector, 2));

    // Print it, see examples/sm/to_string.cpp for more info on sm::to_string .
    std::println("my_vector: {}", sm::to_string(my_vector));

    // Accessing elements that are out of bound will always return 0 and does
    // not throw.  That's what "boundless" is.  This helps you ignore bounds by
    // proceeding to validate elements instead of having to care about bounds
    // and validating elements at the same time
    std::println("cu::boundless_access(my_vector, 6): {}",
        cu::boundless_access(my_vector, 6));

    // What happens when the index is out of range and when you try to write to
    // it?  Don't.  The data written goes to an internal static variable with
    // only purpose is to comply with C++ language design, i.e., returning a
    // reference to a temporary variable is illegal, hence the existence of this
    // static variable to allow returning reference to non-static container's
    // element and also using this static variable when the index is out of
    // bound. This static variable is immediately reset to {} (which will be 0
    // in this case) every time this function is called.  This is not undefined
    // behavior, it is defined to be erased.  Hence, the written data is not
    // accessible.  Effectively, **writing to a void**.
    //
    // TL;DR: Don't, and handle bounds checks when writing to it
    cu::boundless_access(my_vector, 7) = 9; // Don't

    std::println("cu::boundless_access(my_vector, 7) after setting it to 9: {}",
        cu::boundless_access(my_vector, 7)); // Prints 0

    std::println("my_vector: {}", sm::to_string(my_vector));



    // Tired of cu::boundless_access(my_vector, index) and just want to do
    // my_vector[index] and have it boundless?  You are in luck!
    cu::boundless_vector bound_broken = { 6, 7, 8, 9, 10 };

    bound_broken[3] = 12; // Now the vector is { 6, 7, 8, 12, 10 }

    std::println("bound_broken[3] after setting it to 12: {}", bound_broken[3]);
    std::println("bound_broken: {}", sm::to_string(bound_broken));

    // Same thing happens when the index is out of range and when you try to
    // write to it
    bound_broken[9] = 14;

    // Prints 0 as above
    std::println("bound_broken[9] after setting it to 14: {}", bound_broken[9]);
    std::println("bound_broken: {}", sm::to_string(bound_broken));



    // There is array, span, string and string_view variants too!
    cu::boundless_string infinite_string = "Lose";

    infinite_string[2] = 'v';

    std::println("infinite_string[2] after setting it to 'v': '{}'",
        infinite_string[2]);
    std::println("infinite_string: {}", infinite_string);

    infinite_string[4] = 'r';

    std::println("infinite_string[4] after setting it to 'r': '{}'",
        infinite_string[4]); // Note: prints a null character
    std::println("infinite_string: {}", infinite_string);



/*

    // One use case would be when parsing
    cu::boundless_string input =
        "#include <print>\nint main() { std::println(\"Input program\\n\"); }";
    std::vector<std::string> tokens = {};

    std::size_t current = 0;
    while (input[current] != '\0') // No need to care about bounds!
    {
        if (std::isdigit(input[current]))
        {
            // Parse integers?
        }
        // ...
        current++;
    }

*/
}
