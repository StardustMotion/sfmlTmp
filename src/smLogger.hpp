#pragma once
#include <iostream>

namespace LogLevel {
    const uint8_t info = 0x01;
    const uint8_t debug = 0x02;
    const uint8_t warn = 0x04;
    const uint8_t error = 0x08;
    const uint8_t all = info | debug | warn | error;
}

class Logger
{
private:
    static uint8_t logLevel;
    Logger();
    ~Logger();
public:
    static void log(std::string _message, uint8_t level = LogLevel::all);
    static void debug(std::string _message);
    static void warn(std::string _message);
    static void error(std::string _message);
    static void setLogLevel(uint8_t level);
};
