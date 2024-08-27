/**
 *  @file    tester.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of Auspicious Library.
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

/**
 *  @brief  Define global variables for this translation unit.
 */
#define gvar
#include "tester.hpp"

#include <cstddef>

/**
 *  @brief  Test String Manipulators' to_string.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_sm_to_string() -> std::size_t;

/**
 *  @brief  Test Argument Parser.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_ap() -> std::size_t;

/**
 *  @brief  Test String Manipulators.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_sm() -> std::size_t;

/**
 *  @brief  Test ANSI Escape Codes.
 *  @return  Zero.
 */
[[nodiscard]] auto test_aec() -> std::size_t;

/**
 *  @brief  Test... copper?  No wait, test Container Utilities.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu() -> std::size_t;

/**
 *  @brief  Test Argument Parser.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_ap() -> std::size_t;

/**
 *  @brief  The biggie.
 *  @return  zero on success.
 */
auto main() -> int try
{
    // Test String Manipulators' to_string function before anything else.
    log_file.open("test_sm_to_string.log");
    if (auto errors = test_sm_to_string(); errors != 0)
    {
        std::println("String Manipulators' to_string functions failed, "
            "cannot continue further tests.");
        return errors;
    }
    log_file.close();

    test_suite suite = {};
    suite.pre_run    = [&](const test *test)
    {
        log_file.open(test->function_name + ".log");
        default_pre_runner('=', 5)(test);
    };
    suite.post_run = [&](const test *test, std::size_t errors)
    {
        default_post_runner('=', 5)(test, errors);
        log_file.close();
    };
    // suite.run_failed = default_run_failed_quitter();

    test cu_test = {
        "Test Container Utilities",
        "test_cu",
        test_cu
    };

    test sm_test = {
        "Test String Manipulators",
        "test_sm",
        test_sm
    };

    test aec_test = {
        "Test ANSI Escape Codes",
        "test_aec",
        test_aec
    };

    test ap_test = {
        "Test Argument Parser",
        "test_ap",
        test_ap
    };

    suite.tests.emplace_back(&cu_test);
    suite.tests.emplace_back(&sm_test);
    suite.tests.emplace_back(&aec_test);
    suite.tests.emplace_back(&ap_test);

    auto failed_tests = suite.run();
    log_file.open("tester.log");

    print_failed_tests(failed_tests);

    return get_failed_tests_errors(failed_tests);
}
catch (const std::exception &e)
{
    log_file.open("tester.log");
    std::println("Exception occurred during testing: {}", e.what());
    return 1;
}
catch (...)
{
    log_file.open("tester.log");
    std::println("Unknown exception occurred during testing");
    return 1;
}
