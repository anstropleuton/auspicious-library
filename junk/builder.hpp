/**
 *  @file    builder.hpp
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Custom simple build system.
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

#include <cstdlib>
#include <filesystem>
#include <format>
#include <memory>
#include <ranges>
#include <string>
#include <variant>
#include <vector>

/**
 *  @brief  Global variables are now available in header files!  Just #define
 *          @c gvar as empty in *one* source file.
 */
#ifndef gvar
#define gvar extern
#endif // gvar

/**
 *  @brief  Convert a vector of strings to a single string, each string
 *          surrounded by double quotation marks and separated by one space.
 *
 *  @param  strings  The strings.
 *  @return  A single string from strings.
 */
[[nodiscard]] inline constexpr auto strings_to_string(
    const std::vector<std::string> &strings
)
{
    return "\"" + (
        // Workaround to not utilize Auspicious Library for building
        // Auspicious Library
        strings
        | std::views::join_with(std::string("\" \""))
        | std::ranges::to<std::string>()
    ) + "\"";
}

/**
 *  @brief  Combine two vectors.
 *
 *  @tparam  T  The type of elements.
 *  @param   a  The first vector.
 *  @param   b  The second vector.
 *  @return  Vector with elements from @c a and @c b .
 */
template<typename T>
[[nodiscard]] inline constexpr auto operator+ (
    const std::vector<T> &a,
    const std::vector<T> &b
)
{
    return std::vector { a, b }
         | std::views::join
         | std::ranges::to<std::vector>();
}

/**
 *  @brief  Combine vectors with an element.
 *
 *  @tparam  T  The type of elements.
 *  @param   a  An element.
 *  @param   b  A vector.
 *  @return  Vector with element @c a and elements from @c b .
 */
template<typename T>
[[nodiscard]] inline constexpr auto operator+ (
    const T              &a,
    const std::vector<T> &b
)
{
    return std::vector { std::vector { a }, b }
         | std::views::join
         | std::ranges::to<std::vector>();
}

/**
 *  @brief  Combine vectors with an element.
 *
 *  @tparam  T  The type of elements.
 *  @param   a  A vector.
 *  @param   b  An element.
 *  @return  Vector with elements from @c a and element @c b .
 */
template<typename T>
[[nodiscard]] inline constexpr auto operator+ (
    const std::vector<T> &a,
    const T              &b
)
{
    return std::vector { a, std::vector { b } }
         | std::views::join
         | std::ranges::to<std::vector>();
}

/**
 *  @brief  The core is an individual command.
 */
struct command {

    /**
     *  @brief  Current working directory for command.
     */
    std::filesystem::path directory;

    /**
     *  @brief  All the arguments, including the first argument of program.
     */
    std::vector<std::string> arguments;

    /**
     *  @brief  Creates a command using arguments and current working directory.
     *
     *  @param  directory  The current working directory.
     *  @param  arguments  The arguments (including first argument of program).
     */
    inline command(
        const std::filesystem::path    &directory,
        const std::vector<std::string> &arguments
    ) : directory(directory), arguments(arguments) {}

    /**
     *  @brief  Virtual Destructor (does nothing).
     */
    virtual inline constexpr ~command() {}

    /**
     *  @brief  Get a single string representing the arguments.
     *  @return  String representing the command created using arguments.
     */
    [[nodiscard]] inline constexpr auto make_command()
    {
        return strings_to_string(arguments);
    }

    /**
     *  @brief  Run the command using command from @c make_command .
     *  @return  The return value of @c std::system with the command being run.
     */
    [[nodiscard]] inline auto run()
    {
        auto original_path = std::filesystem::current_path();
        std::filesystem::current_path(directory);
        int ret = std::system(make_command().c_str());
        std::filesystem::current_path(original_path);

        return ret;
    }
};

/**
 *  @brief  A compiling command, can also be used for @c compile_commands.json .
 */
struct compile_command : command {

    /**
     *  @brief  The ile this compile command applies to.
     */
    std::string file;

    /**
     *  @brief  The output this compile command is expected to produce.
     */
    std::string output;

    /**
     *  @brief  Creates a compile command using fields.
     *
     *  @param  directory  The current working directory.
     *  @param  arguments  The arguments (including first argument of program).
     *  @param  file       The file for the compile command.
     *  @param  output     The output of the compile command.
     */
    inline compile_command(
        const std::filesystem::path    &directory,
        const std::vector<std::string> &arguments,
        std::string_view                file,
        std::string_view                output
    ) : command(directory, arguments), file(file), output(output) {}

    /**
     *  @brief  Get the json representation of a compile command.
     *  @return  Json representation of a compile command.
     */
    [[nodiscard]] inline constexpr auto json()
    {
        return std::format(
            "    {{\n"
            "        \"directory\": \"{}\",\n"
            "        \"arguments\": [\"{}\"],\n"
            "        \"file\": \"{}\",\n"
            "        \"output\": \"{}\",\n"
            "    }}",
            directory.string(),
            make_command(),
            file,
            output
        );
    }
};

/**
 *  @brief  A source file for compilation.
 */
struct source_file {

    /**
     *  @brief  The source file path.
     */
    std::filesystem::path file;

    /**
     *  @brief  File's last modification time.
     */
    std::filesystem::file_time_type last_write_time;

    /**
     *  @brief  Creates a source file and automatically sets file's last
     *          modification time.
     *  @param  file  The file.
     */
    inline source_file(const std::filesystem::path &file) : file(file)
    {
        if (!std::filesystem::exists(file))
        {
            return;
        }

        last_write_time = std::filesystem::last_write_time(file);
    }
};

/**
 *  @brief  Define a variable.
 */
struct variable {

    /**
     *  @brief  Name of the variable.
     */
    std::string name;

    /**
     *  @brief  Variable value as a string, or a list of values as strings.
     */
    std::vector<std::string> value;
};

/**
 *  @brief  Global variables.
 */
gvar std::vector<variable> variables;

/**
 *  @brief  The compiler configuration.
 */
struct environment {

    /**
     *  @brief  The include search directories.
     */
    std::vector<std::filesystem::path> include_directories;

    /**
     *  @brief  The library search directories.
     */
    std::vector<std::filesystem::path> library_directories;

    /**
     *  @brief  The include search directories to export for dependents.
     */
    std::vector<std::filesystem::path> export_include_directories;

    /**
     *  @brief  The library search directories to export for dependents.
     */
    std::vector<std::filesystem::path> export_library_directories;

    /**
     *  @brief  The current working directory for compiling.
     */
    std::filesystem::path directory = std::filesystem::current_path();
};

/**
 *  @brief  The base for executable and library.
 */
struct target {

    /**
     *  @brief  The name of the target exe/lib.
     */
    std::string target_name;

    /**
     *  @brief  Creates a target with an exe/lib name.
     *  @param  target_name  The target exe/lib name.
     */
    inline constexpr target(std::string_view target_name)
        : target_name(target_name) {}

    /**
     *  @brief  Virtual destructor (does nothing).
     */
    virtual inline constexpr ~target() {}

    /**
     *  @brief  Get commands for compiling the executable.
     *
     *  @param  env  The compiler settings.
     *  @return  Compile commands for compiling the executable.
     */
    [[nodiscard]] virtual inline auto get_commands(const environment *env)
    -> std::vector<std::unique_ptr<command>> = 0;
};

/**
 *  @brief  The executable command, creates an executable from sources.
 */
struct executable : target {

    /**
     *  @brief  The source files to use to create executable.
     */
    std::vector<std::string> sources;

    /**
     *  @brief  Creates an executable with exe name and sources.
     *
     *  @param  exe_name  The target executable name.
     *  @param  sources   The source files to use.
     */
    inline constexpr executable(
        std::string_view               exe_name,
        const std::vector<std::string> sources
    ) : target(exe_name), sources(sources) {}

    /**
     *  @brief  Get commands for compiling the executable.
     *
     *  @param  env  The compiler settings.
     *  @return  Compile commands for compiling the executable.
     */
    [[nodiscard]] inline auto get_commands(const environment *env)
    -> std::vector<std::unique_ptr<command>> override
    {}
};

struct library : target {};

/**
 *  @brief  Define a single project with commands.
 */
struct project {

    /**
     *  @brief  All the variables for a project.
     */
    std::vector<variable> variables;

    /**
     *  @brief  Compiler settings throughout this project.
     */
    environment env;

    /**
     *  @brief  All the commands to be executed, in order.
     */
    std::vector<std::variant<command, executable>> commands;

    /**
     *  @brief  Add an executable file using source files.
     */
    [[nodiscard]] inline constexpr auto add_executable(
        std::string_view exe_name, std::vector<std::string> sources)
    {
        commands.emplace_back(executable { std::string(exe_name), sources });
    }
};
