#pragma once
#include <iostream>
#include <string>

namespace LogLevel {
    const uint8_t error = 0x01;
    const uint8_t warn = 0x02;
    const uint8_t info = 0x04;
    const uint8_t debug = 0x08;
    const uint8_t all = error | warn | info | debug;
}

class Logger
{
private:
    Logger();
    ~Logger();
    static uint8_t level;
    static void log(const std::string_view message, uint8_t level);
public:
    static void debug(const std::string_view message);
    static void info(const std::string_view message);
    static void warn(const std::string_view message);
    static void error(const std::string_view message);
    static void setLevel(uint8_t msgLevel);
};

/// quick "to_string" alias for 
template <typename T>
std::string tos(T element) {
    return std::to_string(element);
}
