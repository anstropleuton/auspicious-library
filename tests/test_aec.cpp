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

#define AUSPICIOUS_LIBRARY_NO_INCLUSION_WARN
#include "al_ansi_escape_codes.hpp"
#include "tester.hpp"

namespace al {
using namespace auspicious_library::aec;
} // namespace al
using namespace auspicious_library::aec_operators;

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
    std::println(" {}", al::reset("reset"));
    std::println(" {}", al::bold("bold"));
    std::println(" {}", al::faint("faint"));
    std::println(" {}", al::italic("italic"));
    std::println(" {}", al::underline("underline"));
    std::println(" {}", al::reverse_video("reverse_video"));
    std::println(" {}", al::strike("strike"));
    std::println(" {}", al::black("black"));
    std::println(" {}", al::red("red"));
    std::println(" {}", al::green("green"));
    std::println(" {}", al::yellow("yellow"));
    std::println(" {}", al::blue("blue"));
    std::println(" {}", al::magenta("magenta"));
    std::println(" {}", al::cyan("cyan"));
    std::println(" {}", al::white("white"));
    std::println(" {}", al::gray("gray"));
    std::println(" {}", al::bright_red("bright_red"));
    std::println(" {}", al::bright_green("bright_green"));
    std::println(" {}", al::bright_yellow("bright_yellow"));
    std::println(" {}", al::bright_blue("bright_blue"));
    std::println(" {}", al::bright_magenta("bright_magenta"));
    std::println(" {}", al::bright_cyan("bright_cyan"));
    std::println(" {}", al::bright_white("bright_white"));
    std::println(" {}", al::black_bg("black_bg"));
    std::println(" {}", al::red_bg("red_bg"));
    std::println(" {}", al::green_bg("green_bg"));
    std::println(" {}", al::yellow_bg("yellow_bg"));
    std::println(" {}", al::blue_bg("blue_bg"));
    std::println(" {}", al::magenta_bg("magenta_bg"));
    std::println(" {}", al::cyan_bg("cyan_bg"));
    std::println(" {}", al::white_bg("white_bg"));
    std::println(" {}", al::gray_bg("gray_bg"));
    std::println(" {}", al::bright_red_bg("bright_red_bg"));
    std::println(" {}", al::bright_green_bg("bright_green_bg"));
    std::println(" {}", al::bright_yellow_bg("bright_yellow_bg"));
    std::println(" {}", al::bright_blue_bg("bright_blue_bg"));
    std::println(" {}", al::bright_magenta_bg("bright_magenta_bg"));
    std::println(" {}", al::bright_cyan_bg("bright_cyan_bg"));
    std::println(" {}", al::bright_white_bg("bright_white_bg"));
    std::println();

    std::println("std::cout'd:");
    std::cout << " " << al::reset("reset") << std::endl;
    std::cout << " " << al::bold("bold") << std::endl;
    std::cout << " " << al::faint("faint") << std::endl;
    std::cout << " " << al::italic("italic") << std::endl;
    std::cout << " " << al::underline("underline") << std::endl;
    std::cout << " " << al::reverse_video("reverse_video") << std::endl;
    std::cout << " " << al::strike("strike") << std::endl;
    std::cout << " " << al::black("black") << std::endl;
    std::cout << " " << al::red("red") << std::endl;
    std::cout << " " << al::green("green") << std::endl;
    std::cout << " " << al::yellow("yellow") << std::endl;
    std::cout << " " << al::blue("blue") << std::endl;
    std::cout << " " << al::magenta("magenta") << std::endl;
    std::cout << " " << al::cyan("cyan") << std::endl;
    std::cout << " " << al::white("white") << std::endl;
    std::cout << " " << al::gray("gray") << std::endl;
    std::cout << " " << al::bright_red("bright_red") << std::endl;
    std::cout << " " << al::bright_green("bright_green") << std::endl;
    std::cout << " " << al::bright_yellow("bright_yellow") << std::endl;
    std::cout << " " << al::bright_blue("bright_blue") << std::endl;
    std::cout << " " << al::bright_magenta("bright_magenta") << std::endl;
    std::cout << " " << al::bright_cyan("bright_cyan") << std::endl;
    std::cout << " " << al::bright_white("bright_white") << std::endl;
    std::cout << " " << al::black_bg("black_bg") << std::endl;
    std::cout << " " << al::red_bg("red_bg") << std::endl;
    std::cout << " " << al::green_bg("green_bg") << std::endl;
    std::cout << " " << al::yellow_bg("yellow_bg") << std::endl;
    std::cout << " " << al::blue_bg("blue_bg") << std::endl;
    std::cout << " " << al::magenta_bg("magenta_bg") << std::endl;
    std::cout << " " << al::cyan_bg("cyan_bg") << std::endl;
    std::cout << " " << al::white_bg("white_bg") << std::endl;
    std::cout << " " << al::gray_bg("gray_bg") << std::endl;
    std::cout << " " << al::bright_red_bg("bright_red_bg") << std::endl;
    std::cout << " " << al::bright_green_bg("bright_green_bg") << std::endl;
    std::cout << " " << al::bright_yellow_bg("bright_yellow_bg") << std::endl;
    std::cout << " " << al::bright_blue_bg("bright_blue_bg") << std::endl;
    std::cout << " " << al::bright_magenta_bg("bright_magenta_bg") << std::endl;
    std::cout << " " << al::bright_cyan_bg("bright_cyan_bg") << std::endl;
    std::cout << " " << al::bright_white_bg("bright_white_bg") << std::endl;
    std::println();

    std::println(
        "Combined (bold, strike, bright red):"
    );

    al::aec_t combined_1 = al::bold + al::strike + al::bright_red;
    al::aec_t combined_2 = al::bold * al::strike * al::bright_red;
    al::aec_t combined_3 = al::bold & al::strike & al::bright_red;
    al::aec_t combined_4 = al::bold | al::strike | al::bright_red;
    al::aec_t combined_5 = al::bold && al::strike && al::bright_red;
    al::aec_t combined_6 = al::bold || al::strike || al::bright_red;

    std::println(" {}", combined_1("text"));
    std::println(" {}", combined_2("text"));
    std::println(" {}", combined_3("text"));
    std::println(" {}", combined_4("text"));
    std::println(" {}", combined_5("text"));
    std::println(" {}", combined_6("text"));

    return 0;
}
