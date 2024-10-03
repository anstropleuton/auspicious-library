/**
 *  @file    test_ap.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test 11 of Argument Parser in Auspicious Library.
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

#include <stdexcept>

#include "test_ap.hpp"

/**
 *  @brief  AP Test 11: Throw tests.
 *  @return  Number of errors.
 *
 *  @todo  Split these tests into even smaller functions.
 */
[[nodiscard]] auto test_ap_11() -> std::size_t
{
    T_BEGIN;

    std::vector<const ap::option_template *>     options     = {};
    std::vector<const ap::subcommand_template *> subcommands = {};

    std::size_t test_index = 0;
    std::vector<std::size_t> failed_tests = {};

    // Test throw when an option is null
    options.emplace_back(new ap::option_template {
        .description        = "Test throw null option - 1",
        .long_names         = {},
        .short_names        = {},
        .parameters         = {},
        .defaults_from_back = {}
    });
    options.emplace_back(nullptr);
    options.emplace_back(new ap::option_template {
        .description        = "Test throw null option - 3",
        .long_names         = {},
        .short_names        = {},
        .parameters         = {},
        .defaults_from_back = {}
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Option cannot be null (at index: 1)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test throw when a subcommand is null
    subcommands.emplace_back(new ap::subcommand_template {
        .description        = "Test throw null subcommand - 1",
        .names              = {},
        .parameters         = {},
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });
    subcommands.emplace_back(nullptr);
    subcommands.emplace_back(new ap::subcommand_template {
        .description        = "Test throw null subcommand - 3",
        .names              = {},
        .parameters         = {},
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Subcommand cannot be null (nesting indices: 1)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test throw when option's defaults are more than parameters
    options.emplace_back(new ap::option_template {
        .description        = "Option with wore defaults than parameters",
        .long_names         = {},
        .short_names        = {},
        .parameters         = { "parameter-1" },
        .defaults_from_back = { "default-value-1", "default-value-2" }
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Option cannot have more default values than parameters"
            " (defaults: 2, parameters: 1, at index: 0)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test throw when subcommand's defaults are more than parameters
    subcommands.emplace_back(new ap::subcommand_template {
        .description        = "Subcommand with more defaults than parameters",
        .names              = {},
        .parameters         = { "parameter-1" },
        .defaults_from_back = { "default-value-1", "default-value-2" },
        .subcommands        = {},
        .subcommand_options = {}
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Subcommand cannot have more default values than "
            "parameters (defaults: 2, parameters: 1, nesting indices: 0)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test throw when option's last parameter is variadic but has defaults
    options.emplace_back(new ap::option_template {
        .description        = "Option has variadic parameter and defaults",
        .long_names         = {},
        .short_names        = {},
        .parameters         = { "parameters..." },
        .defaults_from_back = { "default-value" }
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Option cannot have default values when last "
            "parameter is variadic (at index: 0)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test throw when subcommand's last parameter is variadic but has defaults
    subcommands.emplace_back(new ap::subcommand_template {
        .description        = "Subcommand has variadic parameters and defaults",
        .names              = {},
        .parameters         = { "parameters..." },
        .defaults_from_back = { "default-value" },
        .subcommands        = {},
        .subcommand_options = {}
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Subcommand cannot have default values when last "
            "parameter is variadic (nesting indices: 0)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    ap::subcommand_template nested_subcommand = {
        .description        = "Nested subcommand",
        .names              = {},
        .parameters         = {},
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    };

    // Test throw when subcommand's last parameter is variadic but nested
    // subcommands are specified
    subcommands.emplace_back(new ap::subcommand_template {
        .description = "Subcommand has variadic parameters and nested "
                       "subcommand",
        .names              = {},
        .parameters         = { "parameters..." },
        .defaults_from_back = {},
        .subcommands        = { &nested_subcommand },
        .subcommand_options = {}
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Subcommands cannot have nested subcommands when "
            "last parameter is variadic (nesting indices: 0)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test throw when option's non-last parameters are variadic
    options.emplace_back(new ap::option_template {
        .description        = "Option's non-last parameter is variadic",
        .long_names         = {},
        .short_names        = {},
        .parameters         = { "parameter-1...", "parameter-2" },
        .defaults_from_back = {}
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Option's non-last parameter cannot be "
            "variadic (at index: 0, parameter index: 0)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    // Test throw when subcommand's non-last parameters are variadic
    subcommands.emplace_back(new ap::subcommand_template {
        .description        = "Subcommand's non-last parameter is variadic",
        .names              = {},
        .parameters         = { "parameter-1...", "parameter-2" },
        .defaults_from_back = {},
        .subcommands        = {},
        .subcommand_options = {}
    });

    try
    {
        test_index++;
        logln("--- Test 11.{} ---", test_index);
        auto parsed = ap::parse_arguments({}, options, subcommands);
        failed_tests.emplace_back(test_index);
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
    }
    catch (const std::invalid_argument &e)
    {
        logln("\"Invalid argument\" exception caught: {}", e.what());
        if (e.what() == "Subcommand's non-last parameter cannot be variadic "
            "(nesting indices: 0, parameter index: 0)"s)
        {
            logln("--- End of Test 11.{}: Successfully caught valid exception "
                "---", test_index);
        }
        else
        {
            logln("--- End of Test 11.{}: Exception string does not match ---",
                test_index);
            failed_tests.emplace_back(test_index);
        }
    }
    catch (const std::exception &e)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Invalid exception occurred in test_ap_11: {}", e.what());
        failed_tests.emplace_back(test_index);
    }
    catch (...)
    {
        logln("--- End of Test 11.{}: Failure to catch valid exception ---",
            test_index);
        logln("Unknown and invalid exception occurred in test_ap_11");
        failed_tests.emplace_back(test_index);
    }

    for (auto &option : options)
    {
        if (option) delete option;
    }

    for (auto &subcommand : subcommands)
    {
        if (subcommand) delete subcommand;
    }

    options.clear();
    subcommands.clear();

    logln("Failed tests:\n{}\n", sm::to_string(failed_tests, ",\n"s,
        " Test 11."));

    T_END;
}
