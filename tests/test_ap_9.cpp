/**
 *  @file    test_ap.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test 9 of Argument Parser in Auspicious Library.
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
 *  Never-nesters are advised to not take a look at this source file.
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

#include "test_ap.hpp"

/**
 *  @brief  AP Test 9: Argument split tests.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_ap_9() -> std::size_t
{
    T_BEGIN;

    std::vector<const al::option_template *> options = {};

    options.emplace_back(new al::option_template {
        .description        = "Option split test",
        .long_names         = { "name" },
        .short_names        = { 'a' },
        .parameters         = { "parameter" },
        .defaults_from_back = {}
    });

    std::vector<std::string>         args     = {};
    std::vector<al::parsed_argument> expected = {};

    std::size_t test_index = 0;
    std::vector<std::size_t> failed_tests = {};

    args.emplace_back("--name=value");
    expected.emplace_back(al::parsed_argument {
        .argument     = {
            .original = "--name=value",
            .modified = "--name",
            .arg_type = at::long_option,
            .org_pos  = 2,
            .org_size = 4,
            .mod_pos  = 2,
            .mod_size = 4
        },
        .valid          = vdt::valid,
        .is_parsed      = true,
        .ref_option     = options.front(),
        .ref_subcommand = nullptr,
        .values         = { "value" }
    });

    try
    {
        test_index++;
        logln("--- Test 9.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, {});
        logln("--- End of Test 9.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_9: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_9");
    }

    args.clear();
    expected.clear();

    args.emplace_back("-a=value");
    expected.emplace_back(al::parsed_argument {
        .argument     = {
            .original = "-a=value",
            .modified = "-a",
            .arg_type = at::short_option,
            .org_pos  = 1,
            .org_size = 1,
            .mod_pos  = 1,
            .mod_size = 1
        },
        .valid          = vdt::valid,
        .is_parsed      = true,
        .ref_option     = options.front(),
        .ref_subcommand = nullptr,
        .values         = { "value" }
    });

    try
    {
        test_index++;
        logln("--- Test 9.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, {});
        logln("--- End of Test 9.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_9: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_9");
    }

    args.clear();
    expected.clear();

    args.emplace_back("/name:value");
    expected.emplace_back(al::parsed_argument {
        .argument     = {
            .original = "/name:value",
            .modified = "/name",
            .arg_type = at::microsoft_switch,
            .org_pos  = 1,
            .org_size = 4,
            .mod_pos  = 1,
            .mod_size = 4
        },
        .valid          = vdt::valid,
        .is_parsed      = true,
        .ref_option     = options.front(),
        .ref_subcommand = nullptr,
        .values         = { "value" }
    });

    try
    {
        test_index++;
        logln("--- Test 9.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, {});
        logln("--- End of Test 9.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_9: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_9");
    }

    args.clear();
    expected.clear();

    args.emplace_back("/a:value");
    expected.emplace_back(al::parsed_argument {
        .argument     = {
            .original = "/a:value",
            .modified = "/a",
            .arg_type = at::microsoft_switch,
            .org_pos  = 1,
            .org_size = 1,
            .mod_pos  = 1,
            .mod_size = 1
        },
        .valid          = vdt::valid,
        .is_parsed      = true,
        .ref_option     = options.front(),
        .ref_subcommand = nullptr,
        .values         = { "value" }
    });

    try
    {
        test_index++;
        logln("--- Test 9.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, {});
        logln("--- End of Test 9.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_9: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_9");
    }

    args.clear();
    expected.clear();

    args.emplace_back("--name:value");
    expected.emplace_back(al::parsed_argument {
        .argument     = {
            .original = "--name:value",
            .modified = "--name:value",
            .arg_type = at::long_option,
            .org_pos  = 2,
            .org_size = 10,
            .mod_pos  = 2,
            .mod_size = 10
        },
        .valid          = vdt::unrecognized_option,
        .is_parsed      = true,
        .ref_option     = nullptr,
        .ref_subcommand = nullptr,
        .values         = {}
    });

    try
    {
        test_index++;
        logln("--- Test 9.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, {});
        logln("--- End of Test 9.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_9: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_9");
    }

    args.clear();
    expected.clear();

    args.emplace_back("/name=value");
    expected.emplace_back(al::parsed_argument {
        .argument     = {
            .original = "/name=value",
            .modified = "/name=value",
            .arg_type = at::microsoft_switch,
            .org_pos  = 1,
            .org_size = 10,
            .mod_pos  = 1,
            .mod_size = 10
        },
        .valid          = vdt::unrecognized_option,
        .is_parsed      = true,
        .ref_option     = nullptr,
        .ref_subcommand = nullptr,
        .values         = {}
    });

    try
    {
        test_index++;
        logln("--- Test 9.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, {});
        logln("--- End of Test 9.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_9: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_9");
    }

    args.clear();
    expected.clear();

    for (auto &option : options)
    {
        delete option;
    }

    T_END;
}
