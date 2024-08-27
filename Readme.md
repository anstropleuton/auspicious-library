# Auspicious Library
Auspicious Library is a collection of utils for Anstro Pleuton's programs. This library contains several commonly used program artifacts in a simplified functions for ease of use.

# Sections
This library is subdivided into sections:
- **Container Utilities** contains several utilities for container types (i.e., **std::vector**, **std::array**, etc. or custom compatible container types) which includes **appending elements** (combining), **filtering elements out**, etc. And several **operators** for these operations.
- **String Manipulators** contains several utilities for **std::string** (or **std::string_view** as parameters) which includes **converting containers to string**, **word-wrap**, **trimming string**, converting **to lower case**, etc. And several **operators** from Container Utilities applied to string types.
- **ANSI Escape Codes** contains easy handlers for manipulation output using decorator [ANSI Escape Codes](https://en.wikipedia.org/wiki/ANSI_escape_code).
- **Argument Parser** contains functionality to parse **Command Line Arguments** and structures to **define options** (or **switches** if you are old and use Microsoft Windows) to easily validate arguments.

# Planned Sections
There are several Utilities I am planning add to this library, notably:
- **Binary Files** to contain several utilities for managing binary files to store and retrieve raw data.
- **Security** to contain encryption and decryption functions (yeah that's it).

# Prerequisite
- Know to program in C++
- Know to program in C++23 (optional, recommended)
- Know to use third party C++ libraries
- Know to use CMake

# Usage
If you are not Anstro Pleuton, which you probably are, here is a quick and rough guide to use my library:

 1. Setup:
    - Clone this repository.
```
git clone https://github.com/anstropleuton/auspicious-library
cd auspicious-library
```
 2. Build the library:
    - Make build folder:
```bash
mkdir build
cd build
```
    - Build the project:
```bash
cmake ..
cmake --build .
```
 3. Set up include path and C++ flags:
    - Depends on your development environment, generally include the [include](include/) folder as include search path. Additionally, select C++23 as the C++ standard. In Clang++/G++, you can do as so:
```
g++ -Iinclude -std=c++23
```
 4. Include the library to include all functionality:
```cpp
#include "auspicious_library.hpp"
```
 5. Go through [documentation](https://anstropleuton.github.io/auspicious-library) (or [header files](include/auspicious_library.hpp)[*](#Doxygen)) to get a grasp on what you can do using my library. You can check out [examples source files](examples/) for more usage information.

# Documentations
Refer to the [documentation](https://anstropleuton.github.io/auspicious-library) (or [header files](include/auspicious_library.hpp)[*](#Doxygen)) to get a grasp on what you can do using my library.

# Changelog
Refer to the [Changelog](Changelog.md) for info about changes in each version.

# Contributing
Check out [Guidelines](Guidelines.md) before you submit your code! Make sure to create a branch with one task with the name of the category of your task (i.e., "features/", "bugfix/", etc.) your task before you change the code.

# Credits
Thanks to [jothepro](https://github.com/jothepro) for the stylesheet [Doxygen Awesome](https://github.com/jothepro/doxygen-awesome-css) for Doxygen.

# License
This project is licensed under the terms of MIT License, see [License](License.md).

# Doxygen
\*: Due to some limitations on how files link in Markdown, not all hyperlinks from this file link properly, so refer to:
- [header files](https://anstropleuton.github.io/auspicious-library/docs/html/auspicious__library_8hpp_source.html)
- [include](https://anstropleuton.github.io/auspicious-library/docs/html/dir_d44c64559bbebec7f509842c48db8b23.html)
