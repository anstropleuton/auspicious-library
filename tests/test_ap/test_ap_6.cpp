/**
 *  @file    test_ap.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test 6 of Argument Parser in Auspicious Library.
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
 *  @brief  AP Test 6: Subcommand parameter recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_ap_6() -> std::size_t
{
    T_BEGIN;

    // Actual size this time
    std::size_t names_count = 2;
    std::size_t overflow    = 1;

    if (extensive_test)
    {
        names_count = 4;
        overflow    = 4;
    }

    std::vector<const ap::subcommand_template *> subcommands = {};

    // Generate subcommands
    for (std::size_t i = 0; i < names_count; i++)
    {
        std::vector<std::string> parameters;
        for (std::size_t j = 0; j < i + 1; j++)
        {
            parameters.emplace_back(std::format("parameter-{}", j));
        }

        subcommands.emplace_back(new ap::subcommand_template {
            .description = std::format("Subcommand parameter recognition"
                " - {}", i),
            .names              = { std::format("name-{}", i) },
            .parameters         = parameters,
            .defaults_from_back = {},
            .subcommands        = {},
            .subcommand_options = {}
        });
    }

    try
    {
        std::size_t test_index = 0;
        std::vector<std::size_t> failed_tests = {};

        // Test each subcommand
        for (std::size_t i = 0; i < subcommands.size(); i++)
        {
            auto subcommand = subcommands[i];

            // For each parameter
            for (std::size_t j = 0;
                 j < subcommand->parameters.size() + overflow; j++)
            {
                test_index++;

                std::vector<std::string>         args     = {};
                std::vector<ap::parsed_argument> expected = {};

                auto arg = subcommand->names.front();
                args.emplace_back(arg);

                // Add n values per parameter requirements
                // Causes less parameters than required
                for (std::size_t k = 0; k < j; k++)
                {
                    args.emplace_back(std::format("value-{}", k));
                }

                vdt valid = j >= subcommand->parameters.size()
                            ? vdt::valid
                            : vdt::not_enough_values;

                ap::parsed_argument expect = {
                    .argument     = {
                        .original = arg,
                        .modified = arg,
                        .arg_type = at::regular_argument,
                        .org_pos  = 0,
                        .org_size = arg.size(),
                        .mod_pos  = 0,
                        .mod_size = arg.size()
                    },
                    .valid          = valid,
                    .is_parsed      = true,
                    .ref_option     = nullptr,
                    .ref_subcommand = subcommand,
                    .values         = {}
                };

                // Add values to expected
                for (std::size_t k = 0;
                     k < std::min(j, subcommand->parameters.size());
                     k++)
                {
                    expect.values.emplace_back(std::format("value-{}", k));
                }

                expected.emplace_back(expect);

                // Overflowed values are treated as subcommands, and is
                // unrecognized
                for (std::size_t k = subcommand->parameters.size();
                     k < j; k++)
                {
                    auto arg = std::format("value-{}", k);

                    ap::parsed_argument expect = {
                        .argument     = {
                            .original = arg,
                            .modified = arg,
                            .arg_type = at::regular_argument,
                            .org_pos  = 0,
                            .org_size = arg.size(),
                            .mod_pos  = 0,
                            .mod_size = arg.size()
                        },
                        .valid          = vdt::unrecognized_subcommand,
                        .is_parsed      = true,
                        .ref_option     = nullptr,
                        .ref_subcommand = nullptr,
                        .values         = {}
                    };

                    expected.emplace_back(expect);
                }

                logln("--- Test 6.{} ---", test_index);
                auto sub_errors = ap_tester(args, expected, {}, subcommands);
                logln("--- End of Test 6.{}, {} errors ---", test_index,
                    sub_errors);
                if (sub_errors != 0) failed_tests.emplace_back(test_index);
                errors += sub_errors;
            }
        }

        logln("Failed tests:\n{}\n", sm::to_string(failed_tests, ",\n"s,
            " Test 6."));
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_ap_6: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in test_ap_6");
    }

    for (auto &subcommand : subcommands)
    {
        delete subcommand;
    }

    T_END;
}