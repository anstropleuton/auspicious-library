/**
 *  @file    arithmetics.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   How to use CU's string arithmetic functions.
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

#include "auspicious_library.hpp" // IWYU pragma: export

using namespace auspicious_library;

// This example is meant to be a kick-starter to start using string arithmetic
// from container utilities, but they do not teach everything.  Refer to the
// documentation for more details
int main()
{
    // I recommend you to check out examples/cu/arithmetic.cpp before this one

    std::string hello_world = "Hello, world! ";

    // No need for sm::combine because std::string has operator+

    // Filtering out occurrences the elements
    // Note: we are using c
    auto e = sm::filter_out_occ(hello_world, " "); // e is "Hello,world!"

    // Repeating the container
    // Note: we are using a
    auto f = sm::repeat(hello_world, 2); // f is "Hello, world! Hello, world! "

    // Splitting the container into sub containers
    // Note: we are using c
    auto g = sm::split_seq(hello_world, ", "); // g is { "Hello", "world! " }

    using namespace sm_operators;

    // Same examples using operators

    // Filtering out
    e = hello_world - " ";

    // Repeating
    f = hello_world * 2;

    // Splitting
    g = hello_world / ", ";
}
