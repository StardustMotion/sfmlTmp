#include "smLogger.hpp"

Logger::Logger() { ; }
Logger::~Logger() { ; } // file writing todo

uint8_t Logger::level = 0;

void Logger::log(const std::string_view message, uint8_t msgLevel) {
    if (message.empty() || !(level & msgLevel))
        return;

    std::string prefix;
    switch (msgLevel) {
        case LogLevel::debug: 
            std::cerr << "<DEBUG> " << message << std::endl; // cerr prints before a crash occurs
            return;
        case LogLevel::info: prefix = "~INFO~"; break;
        case LogLevel::warn: prefix = "* WARNING *"; break;
        case LogLevel::error: prefix = "# ERROR #"; break;
    }
    std::cout << prefix << " " << message << std::endl;
}

void Logger::debug(const std::string_view message) {
    log(message, LogLevel::debug);
}
void Logger::info(const std::string_view message) {
    log(message, LogLevel::info);
}
void Logger::warn(const std::string_view message) {
    log(message, LogLevel::warn);
}
void Logger::error(const std::string_view message) {
    log(message, LogLevel::error);
}
void Logger::setLevel(uint8_t msgLevel) {
    level = msgLevel;
}
