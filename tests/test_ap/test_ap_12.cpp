/**
 *  @file    test_ap.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test 12 of Argument Parser in Auspicious Library.
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

#include <vector>

#include "test_ap.hpp"

/**
 *  @brief  AP Test 12: Misc. edge case tests.
 *  @return  Number of errors.
 *
 *  @todo  Split these tests into even smaller functions.
 */
[[nodiscard]] auto test_ap_12() -> std::size_t
{
    T_BEGIN;

    std::vector<const ap::option_template *>     options     = {};
    std::vector<const ap::subcommand_template *> subcommands = {};

    std::size_t test_index = 0;
    std::vector<std::size_t> failed_tests = {};

    std::vector<std::string>         args     = {};
    std::vector<ap::parsed_argument> expected = {};

    // Test `--arg value subcommand`
    options.emplace_back(new ap::option_template {
        .description        = "Option test `--arg value subcommand`",
        .long_names         = { "arg" },
        .short_names        = {},
        .parameters         = { "parameter" },
        .defaults_from_back = {}
    });

    subcommands.emplace_back(new ap::subcommand_template {
        .description        = "Subcommand test `--arg value subcommand`",
        .names              = { "subcommand" },
        .parameters         = {},
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });

    args     = { "--arg", "value", "subcommand" };
    expected = {
        ap::parsed_argument {
            .argument     = {
                .original = "--arg",
                .modified = "--arg",
                .arg_type = at::long_option,
                .org_pos  = 2,
                .org_size = 3,
                .mod_pos  = 2,
                .mod_size = 3
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = options.front(),
            .ref_subcommand = nullptr,
            .values         = { "value" }
        },
        ap::parsed_argument {
            .argument     = {
                .original = "subcommand",
                .modified = "subcommand",
                .arg_type = at::regular_argument,
                .org_pos  = 0,
                .org_size = 10,
                .mod_pos  = 0,
                .mod_size = 10
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = nullptr,
            .ref_subcommand = subcommands.front(),
            .values         = {         }
        }
    };

    try
    {
        test_index++;
        logln("--- Test 12.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, subcommands);
        logln("--- End of Test 12.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_12: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_12");
    }

    for (auto &option : options)
    {
        delete option;
    }

    for (auto &subcommand : subcommands)
    {
        delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test `subcommand-1 value subcommand-2`
    subcommands.emplace_back(new ap::subcommand_template {
        .description = "Subcommand test - 1 `subcommand-1 value "
                       "subcommand-2`",
        .names              = { "subcommand-1" },
        .parameters         = { "parameter" },
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });
    subcommands.emplace_back(new ap::subcommand_template {
        .description = "Subcommand test - 2 `subcommand-1 value "
                       "subcommand-2`",
        .names              = { "subcommand-2" },
        .parameters         = {},
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });

    args     = { "subcommand-1", "value", "subcommand-2" };
    expected = {
        ap::parsed_argument {
            .argument     = {
                .original = "subcommand-1",
                .modified = "subcommand-1",
                .arg_type = at::regular_argument,
                .org_pos  = 0,
                .org_size = 12,
                .mod_pos  = 0,
                .mod_size = 12
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = nullptr,
            .ref_subcommand = subcommands[0],
            .values         = { "value" }
        },
        ap::parsed_argument {
            .argument     = {
                .original = "subcommand-2",
                .modified = "subcommand-2",
                .arg_type = at::regular_argument,
                .org_pos  = 0,
                .org_size = 12,
                .mod_pos  = 0,
                .mod_size = 12
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = nullptr,
            .ref_subcommand = subcommands[1],
            .values         = {         }
        }
    };

    try
    {
        test_index++;
        logln("--- Test 12.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, subcommands);
        logln("--- End of Test 12.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_12: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_12");
    }

    for (auto &option : options)
    {
        delete option;
    }

    for (auto &subcommand : subcommands)
    {
        delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test argument starting with `=`
    args     = { "=" };
    expected = {
        ap::parsed_argument {
            .argument     = {
                .original = "=",
                .modified = "=",
                .arg_type = at::regular_argument,
                .org_pos  = 0,
                .org_size = 1,
                .mod_pos  = 0,
                .mod_size = 1
            },
            .valid          = vdt::unrecognized_subcommand,
            .is_parsed      = true,
            .ref_option     = nullptr,
            .ref_subcommand = nullptr,
            .values         = {}
        }
    };

    try
    {
        test_index++;
        logln("--- Test 12.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, subcommands);
        logln("--- End of Test 12.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_12: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_12");
    }

    for (auto &option : options)
    {
        delete option;
    }

    for (auto &subcommand : subcommands)
    {
        delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test `--arg value-1=value-2`
    options.emplace_back(new ap::option_template {
        .description        = "Option test `--arg value-1=value-2`",
        .long_names         = { "arg" },
        .short_names        = {},
        .parameters         = { "parameter" },
        .defaults_from_back = {}
    });

    args     = { "--arg", "value-1=value-2" };
    expected = {
        ap::parsed_argument {
            .argument     = {
                .original = "--arg",
                .modified = "--arg",
                .arg_type = at::long_option,
                .org_pos  = 2,
                .org_size = 3,
                .mod_pos  = 2,
                .mod_size = 3
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = options.front(),
            .ref_subcommand = nullptr,
            .values         = { "value-1=value-2" }
        }
    };

    try
    {
        test_index++;
        logln("--- Test 12.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, subcommands);
        logln("--- End of Test 12.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_12: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_12");
    }

    for (auto &option : options)
    {
        delete option;
    }

    for (auto &subcommand : subcommands)
    {
        delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test `global-subcommand-1 global-subcommand-2` even when
    // `global-subcommand-1` has subcommand of its own
    subcommands.emplace_back(new ap::subcommand_template {
        .description = "Subcommand test - 1 `global-subcommand-1 "
                       "global-subcommand-2`",
        .names              = { "global-subcommand-1" },
        .parameters         = {},
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });
    subcommands.emplace_back(new ap::subcommand_template {
        .description = "Subcommand test - 2 `global-subcommand-1 "
                       "global-subcommand-2`",
        .names              = { "global-subcommand-2" },
        .parameters         = {},
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });

    args     = { "global-subcommand-1", "global-subcommand-2" };
    expected = {
        ap::parsed_argument {
            .argument     = {
                .original = "global-subcommand-1",
                .modified = "global-subcommand-1",
                .arg_type = at::regular_argument,
                .org_pos  = 0,
                .org_size = 19,
                .mod_pos  = 0,
                .mod_size = 19
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = nullptr,
            .ref_subcommand = subcommands[0],
            .values         = {}
        },
        ap::parsed_argument {
            .argument     = {
                .original = "global-subcommand-2",
                .modified = "global-subcommand-2",
                .arg_type = at::regular_argument,
                .org_pos  = 0,
                .org_size = 19,
                .mod_pos  = 0,
                .mod_size = 19
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = nullptr,
            .ref_subcommand = subcommands[1],
            .values         = {}
        }
    };

    try
    {
        test_index++;
        logln("--- Test 12.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, subcommands);
        logln("--- End of Test 12.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_12: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_12");
    }

    for (auto &option : options)
    {
        delete option;
    }

    for (auto &subcommand : subcommands)
    {
        delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test `--arg-1 value --arg-2` even when `--arg-1` has two parameters
    options.emplace_back(new ap::option_template {
        .description        = "Option test `--arg-1 value --arg-2`",
        .long_names         = { "arg-1" },
        .short_names        = {},
        .parameters         = { "parameter-1", "parameter-2" },
        .defaults_from_back = {}
    });

    options.emplace_back(new ap::option_template {
        .description        = "Option test `--arg-1 value --arg-2`",
        .long_names         = { "arg-2" },
        .short_names        = {},
        .parameters         = {},
        .defaults_from_back = {}
    });

    args     = { "--arg-1", "value", "--arg-2" };
    expected = {
        ap::parsed_argument {
            .argument     = {
                .original = "--arg-1",
                .modified = "--arg-1",
                .arg_type = at::long_option,
                .org_pos  = 2,
                .org_size = 5,
                .mod_pos  = 2,
                .mod_size = 5
            },
            .valid          = vdt::not_enough_values,
            .is_parsed      = true,
            .ref_option     = options[0],
            .ref_subcommand = nullptr,
            .values         = { "value" }
        },
        ap::parsed_argument {
            .argument     = {
                .original = "--arg-2",
                .modified = "--arg-2",
                .arg_type = at::long_option,
                .org_pos  = 2,
                .org_size = 5,
                .mod_pos  = 2,
                .mod_size = 5
            },
            .valid          = vdt::valid,
            .is_parsed      = true,
            .ref_option     = options[1],
            .ref_subcommand = nullptr,
            .values         = {         }
        }
    };

    try
    {
        test_index++;
        logln("--- Test 12.{} ---", test_index);
        auto sub_errors = ap_tester(args, expected, options, subcommands);
        logln("--- End of Test 12.{}, {} errors ---", test_index,
            sub_errors);
        if (sub_errors != 0) failed_tests.emplace_back(test_index);
        errors += sub_errors;
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_12: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_12");
    }

    for (auto &option : options)
    {
        delete option;
    }

    for (auto &subcommand : subcommands)
    {
        delete subcommand;
    }

    options.clear();
    subcommands.clear();

    logln("Failed tests:\n{}\n", sm::to_string(failed_tests, ",\n"s,
        " Test 12."));

    T_END;
}
