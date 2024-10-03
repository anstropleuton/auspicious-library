/**
 *  @file    test_aec.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of ANSI Escape Codes in Auspicious Library.
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

#include <iostream>
#include <print>

#include "tester.hpp"

using namespace aec_operators;

/**
 *  @brief  Test ANSI Escape Codes.
 *  @return  Zero.
 */
[[nodiscard]] auto test_aec() -> std::size_t
{
    logln("AEC test results cannot be displayed using files, see the terminal"
          "output to review the test results.");

    std::println("AEC test results are displayed on the terminal for review.");

    std::println("std::println'd:");
    std::println(" {}", aec::reset("reset"));
    std::println(" {}", aec::bold("bold"));
    std::println(" {}", aec::faint("faint"));
    std::println(" {}", aec::italic("italic"));
    std::println(" {}", aec::underline("underline"));
    std::println(" {}", aec::reverse_video("reverse_video"));
    std::println(" {}", aec::strike("strike"));
    std::println(" {}", aec::black("black"));
    std::println(" {}", aec::red("red"));
    std::println(" {}", aec::green("green"));
    std::println(" {}", aec::yellow("yellow"));
    std::println(" {}", aec::blue("blue"));
    std::println(" {}", aec::magenta("magenta"));
    std::println(" {}", aec::cyan("cyan"));
    std::println(" {}", aec::white("white"));
    std::println(" {}", aec::gray("gray"));
    std::println(" {}", aec::bright_red("bright_red"));
    std::println(" {}", aec::bright_green("bright_green"));
    std::println(" {}", aec::bright_yellow("bright_yellow"));
    std::println(" {}", aec::bright_blue("bright_blue"));
    std::println(" {}", aec::bright_magenta("bright_magenta"));
    std::println(" {}", aec::bright_cyan("bright_cyan"));
    std::println(" {}", aec::bright_white("bright_white"));
    std::println(" {}", aec::black_bg("black_bg"));
    std::println(" {}", aec::red_bg("red_bg"));
    std::println(" {}", aec::green_bg("green_bg"));
    std::println(" {}", aec::yellow_bg("yellow_bg"));
    std::println(" {}", aec::blue_bg("blue_bg"));
    std::println(" {}", aec::magenta_bg("magenta_bg"));
    std::println(" {}", aec::cyan_bg("cyan_bg"));
    std::println(" {}", aec::white_bg("white_bg"));
    std::println(" {}", aec::gray_bg("gray_bg"));
    std::println(" {}", aec::bright_red_bg("bright_red_bg"));
    std::println(" {}", aec::bright_green_bg("bright_green_bg"));
    std::println(" {}", aec::bright_yellow_bg("bright_yellow_bg"));
    std::println(" {}", aec::bright_blue_bg("bright_blue_bg"));
    std::println(" {}", aec::bright_magenta_bg("bright_magenta_bg"));
    std::println(" {}", aec::bright_cyan_bg("bright_cyan_bg"));
    std::println(" {}", aec::bright_white_bg("bright_white_bg"));
    std::println();

    std::println("std::cout'd:");
    std::cout << " " << aec::reset("reset") << std::endl;
    std::cout << " " << aec::bold("bold") << std::endl;
    std::cout << " " << aec::faint("faint") << std::endl;
    std::cout << " " << aec::italic("italic") << std::endl;
    std::cout << " " << aec::underline("underline") << std::endl;
    std::cout << " " << aec::reverse_video("reverse_video") << std::endl;
    std::cout << " " << aec::strike("strike") << std::endl;
    std::cout << " " << aec::black("black") << std::endl;
    std::cout << " " << aec::red("red") << std::endl;
    std::cout << " " << aec::green("green") << std::endl;
    std::cout << " " << aec::yellow("yellow") << std::endl;
    std::cout << " " << aec::blue("blue") << std::endl;
    std::cout << " " << aec::magenta("magenta") << std::endl;
    std::cout << " " << aec::cyan("cyan") << std::endl;
    std::cout << " " << aec::white("white") << std::endl;
    std::cout << " " << aec::gray("gray") << std::endl;
    std::cout << " " << aec::bright_red("bright_red") << std::endl;
    std::cout << " " << aec::bright_green("bright_green") << std::endl;
    std::cout << " " << aec::bright_yellow("bright_yellow") << std::endl;
    std::cout << " " << aec::bright_blue("bright_blue") << std::endl;
    std::cout << " " << aec::bright_magenta("bright_magenta") << std::endl;
    std::cout << " " << aec::bright_cyan("bright_cyan") << std::endl;
    std::cout << " " << aec::bright_white("bright_white") << std::endl;
    std::cout << " " << aec::black_bg("black_bg") << std::endl;
    std::cout << " " << aec::red_bg("red_bg") << std::endl;
    std::cout << " " << aec::green_bg("green_bg") << std::endl;
    std::cout << " " << aec::yellow_bg("yellow_bg") << std::endl;
    std::cout << " " << aec::blue_bg("blue_bg") << std::endl;
    std::cout << " " << aec::magenta_bg("magenta_bg") << std::endl;
    std::cout << " " << aec::cyan_bg("cyan_bg") << std::endl;
    std::cout << " " << aec::white_bg("white_bg") << std::endl;
    std::cout << " " << aec::gray_bg("gray_bg") << std::endl;
    std::cout << " " << aec::bright_red_bg("bright_red_bg") << std::endl;
    std::cout << " " << aec::bright_green_bg("bright_green_bg") << std::endl;
    std::cout << " " << aec::bright_yellow_bg("bright_yellow_bg") << std::endl;
    std::cout << " " << aec::bright_blue_bg("bright_blue_bg") << std::endl;
    std::cout << " " << aec::bright_magenta_bg("bright_magenta_bg") << std::endl;
    std::cout << " " << aec::bright_cyan_bg("bright_cyan_bg") << std::endl;
    std::cout << " " << aec::bright_white_bg("bright_white_bg") << std::endl;
    std::println();

    std::println(
        "Combined (bold, strike, bright red):"
    );

    aec::aec_t combined_1 = aec::bold + aec::strike + aec::bright_red;
    aec::aec_t combined_2 = aec::bold * aec::strike * aec::bright_red;
    aec::aec_t combined_3 = aec::bold & aec::strike & aec::bright_red;
    aec::aec_t combined_4 = aec::bold | aec::strike | aec::bright_red;
    aec::aec_t combined_5 = aec::bold && aec::strike && aec::bright_red;
    aec::aec_t combined_6 = aec::bold || aec::strike || aec::bright_red;

    std::println(" {}", combined_1("text"));
    std::println(" {}", combined_2("text"));
    std::println(" {}", combined_3("text"));
    std::println(" {}", combined_4("text"));
    std::println(" {}", combined_5("text"));
    std::println(" {}", combined_6("text"));

    return 0;
}
