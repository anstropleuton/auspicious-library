/**
 *  @file    test_cu_containers.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test custom containers in Container Utilities.
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

#include <vector>

#include "tester.hpp"

/**
 *  @brief  Test CU containers' @c boundless_access function.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu_containers_boundless_access() -> std::size_t
{
    T_BEGIN;

    std::vector values { 1, 2, 3, 4, 5 };

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            al::boundless_access(values, i) = i;

            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cu_containers_boundless_access: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cu_containers_boundless_access");
    }

    T_END;
}

/**
 *  @brief  Test CU containers' @c boundless_vector struct.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu_containers_boundless_vector() -> std::size_t
{
    T_BEGIN;

    al::boundless_vector values = { 1, 2, 3, 4, 5 };

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            al::boundless_access(values, i) = i;

            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cu_containers_boundless_vector: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cu_containers_boundless_vector");
    }

    T_END;
}

/**
 *  @brief  Test CU containers' @c boundless_array struct.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu_containers_boundless_array() -> std::size_t
{
    T_BEGIN;

    al::boundless_array values = { 1, 2, 3, 4, 5 };

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            al::boundless_access(values, i) = i;

            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cu_containers_boundless_array: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cu_containers_boundless_array");
    }

    T_END;
}

/**
 *  @brief  Test CU containers' @c boundless_span struct.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu_containers_boundless_span() -> std::size_t
{
    T_BEGIN;

    al::boundless_vector    vec    = { 1, 2, 3, 4, 5 };
    al::boundless_span<int> values = vec;

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cu_containers_boundless_span: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cu_containers_boundless_span");
    }

    T_END;
}

/**
 *  @brief  Test CU containers' @c boundless_string struct.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu_containers_boundless_string() -> std::size_t
{
    T_BEGIN;

    al::boundless_string values = "String test #9999";

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            al::boundless_access(values, i) = i % ('z' - 'a') + 'a';

            auto value    = al::boundless_access(values, i);
            auto expected = '\0';

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cu_containers_boundless_string: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cu_containers_boundless_string");
    }

    T_END;
}

/**
 *  @brief  Test CU containers' @c boundless_string_view struct.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu_containers_boundless_string_view() -> std::size_t
{
    T_BEGIN;

    al::boundless_string_view values = "String test #9999";

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = al::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            T_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln(
            "Exception occurred in test_cu_containers_boundless_string_view: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cu_containers_boundless_string_view");
    }

    T_END;
}

/**
 *  @brief  Test CU containers' @c enumerated_array struct.
 *  @return  Number of errors.
 */
[[nodiscard]] auto test_cu_containers_enumerated_array() -> std::size_t
{
    T_BEGIN;

    enum class enumerator {
        zeroth,
        first,
        second,
        third,
        fourth,
        fifth,
        sixth,
        seventh,
        eighth,
        ninth,
        max
    };

    // Best name ever
    std::vector values = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    al::enumerated_array<int, enumerator> erray = { 0, 1, 2, 3, 4, 5, 6, 7, 8,
        9 };

    try
    {
        using enum enumerator;

        erray[zeroth]  += 10;
        erray[first]   += 10;
        erray[second]  += 10;
        erray[third]   += 10;
        erray[fourth]  += 10;
        erray[fifth]   += 10;
        erray[sixth]   += 10;
        erray[seventh] += 10;
        erray[eighth]  += 10;
        erray[ninth]   += 10;

        for (std::size_t i = 0; i < erray.size(); i++)
        {
            auto value    = erray[static_cast<enumerator>(i)];
            auto expected = values[i] + 10;

            T_ASSERT(value, expected, "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln(
            "Exception occurred in test_cu_containers_boundless_string_view: "
            "{}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cu_containers_boundless_string_view");
    }

    T_END;
}
