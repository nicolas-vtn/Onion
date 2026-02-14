# DateTime (UTC)

A lightweight C++20 `DateTime` class representing a precise UTC timestamp with millisecond precision.

* Always valid
* Year range: **[1, 9999]**
* Based on `std::chrono`
* ISO 8601 support
* Compatible with `std::format`

---

## Features

* Current UTC time (`UtcNow`)
* Accessors for date and time parts
* Comparison operators
* ISO 8601 string output
* Custom chrono-based formatting
* Unix timestamp conversion
* `std::format` integration via custom formatter

---

## Adding to Your CMake Project

If the library is included in your repository:
```cmake
add_subdirectory(libs/datetime)

target_link_libraries(your_target
    PRIVATE
        onion_datetime
)
```

---

## Example

```cpp
#include <format>
#include "DateTime.hpp"

using onion::DateTime;

int main()
{
    DateTime now = DateTime::UtcNow();

    // ISO 8601
    std::string iso = now.toString();

    // Custom format
    std::string formatted = now.toString("%Y-%m-%d %H:%M:%S");

    // std::format support
    std::string fmt = std::format("Current time: {}", now);
    std::string custom = std::format("{:%F %T}", now);

    return 0;
}
```

---

## Default Formatting

When used with `std::format` without a format specifier:

```cpp
std::format("{}", dt);
```

The default format is:

```
%d-%m-%Y %H:%M:%S
```

You can override it:

```cpp
std::format("{:%Y-%m-%d %H:%M}", dt);
```

Formatting follows C++20 `std::chrono` format rules.

---

## Requirements

* C++20 compatible compiler
* `<chrono>` with calendar and formatting support
* `<format>` support (MSVC / GCC 13+ / Clang 16+)

---
