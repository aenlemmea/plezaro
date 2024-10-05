#pragma once

#ifndef LOG_HH // Header guards as ran into some portability issues.
#    define LOG_HH

#    include <iostream>
#    include <source_location>
enum class LOG_LEVEL : char {
    INFO = 'I',
    WARNING = 'W',
    ERROR = 'E',
};

class Logger {
public:
#    if defined(DEBUG)

    static void log(
        LOG_LEVEL const level,
        const std::string_view str,
        const std::source_location src = std::source_location::current()) {
        std::cout << static_cast<char>(level) << " | " << src.file_name() << ":" << src.function_name() << ":"
                  << src.line() << " | " << str << "\n";
    }
#    else
    static void log(
        LOG_LEVEL const level,
        const std::string_view str,
        const std::source_location src = std::source_location::current()) {}
#    endif
};

#endif
