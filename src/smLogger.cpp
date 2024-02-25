#include "smLogger.hpp"

uint8_t Logger::logLevel = LogLevel::all;

void Logger::log(std::string _message, uint8_t level = LogLevel::info) {
    if (_message.empty() || !(level & logLevel))
        return;

    if (level == LogLevel::error) _message = "[ERROR] " + _message;
    else if (level == LogLevel::debug) _message = "[DEBUG] " + _message;
    else if (level == LogLevel::warn) _message = "[WARN] " + _message;
    else  _message = "[INFO] " + _message;

    std::cout << _message << std::endl;
}

void Logger::debug(std::string _message) {
    log(_message, LogLevel::debug);
}

void Logger::warn(std::string _message) {
    log(_message, LogLevel::warn);
}

void Logger::error(std::string _message) {
    log(_message, LogLevel::error);
}

void Logger::setLogLevel(uint8_t level) {
    logLevel = level;
}