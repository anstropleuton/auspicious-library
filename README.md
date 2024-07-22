# Auspicious Library
Auspicious Library is a collection of Utils for Anstro Pleuton's programs. This library contains several commonly used program artifacts in a simplified functions for ease of use.

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

# Usage
If you are not Anstro Pleuton, which you probably are, here is a quick guide to use my library:

 1. Setup:
    - Clone this repository.
    - Set up include path to the [include](include/) folder.
 2. Include the library to include all functionality:
```cpp
#include "auspicious_library.hpp"
```
 3. Go through [documentation](docs/html/index.html) (or [header files](include/auspicious_library.hpp)) to get a grasp on what you can do using my library.

# Documentations
Refer to the [documentation](docs/html/index.html) (or [header files](include/auspicious_library.hpp)) to get a grasp on what you can do using my library.

# Contributing
Check out [guidelines](guidelines.md) before you submit your code! Make sure to create a branch with one task with the name of the category of your task (i.e., "features/" or "fixes/") your task before you change the code.

# Credits
Thanks to [jothepro](https://github.com/jothepro) for the stylesheet [Doxygen Awesome](https://github.com/jothepro/doxygen-awesome-css) for Doxygen.

# License
This project is licensed under the terms of MIT License, see [LICENSE](LICENSE).
