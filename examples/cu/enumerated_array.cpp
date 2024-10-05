/**
 *  @file    boundless_containers.cpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   How to use CU's @c cu::enumerated_array .
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

// This example is meant to be a kick-starter to start using enumerated array
// from container utilities, but they do not teach everything.  Refer to the
// documentation for more details
int main()
{
    // Let's consider an RPG game example where each character is an enum member
    // and has different stats
    struct character_stats {
        std::string name;
        int health;
        int mana; // Resources to cast spell
        int attack_power;

        void print()
        {
            std::println("{}:",                 name);
            std::println("  Health: {}:",       health);
            std::println("  Mana: {}:",         mana);
            std::println("  Attack Power: {}:", attack_power);
        }
    };

    // The scoped enumerator must be casted to an integer type in order to be
    // used as index, this is where enumerated array comes in which does *not*
    // require you to cast it to an integer type!
    enum class character_type {
        warrior,
        mage,
        archer,
        max
    };

    // All the stats in the enumerated array
    cu::enumerated_array<character_stats, character_type> characters = {
        character_stats { "Warrior", 150, 50,  30 },
        character_stats { "Mage",    80,  200, 15 },
        character_stats { "Archer",  100, 75,  45 }
    };

    // Access specific character stats
    auto warrior_stats = characters[character_type::warrior]; // Just access
                                                              // from the enum!
    warrior_stats.print();

    // Access using instance of enumerator
    character_type current_character = character_type::mage;
    auto           current_stats     = characters[current_character];
    current_stats.print();

    // Buff the character after advancement?
    characters[current_character].health += 20;



    // The use case is beyond the described example, you can use it wherever
    // index is an enumerator and you hate ugly cast operators
}
