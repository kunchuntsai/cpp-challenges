// Challenge 3: Design a thread-safe singleton logger
// Implement a thread-safe singleton logger class that can be used across multiple threads.
// It should support the following:
// - getInstance(): Return the single instance of the logger
// - log(message): Add a message to the log
// - setLogLevel(level): Set the current log level
// - getLogLevel(): Get the current log level
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <stdexcept>

class Logger {
public:
    enum LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "[" << getLogLevelString(currentLevel_) << "] " << message << std::endl;
    }

    void setLogLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(mutex_);
        currentLevel_ = level;
    }

    LogLevel getLogLevel() const {
        return currentLevel_;
    }

    // Delete copy constructor and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Delete move constructor and assignment
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    Logger() : currentLevel_(LogLevel::INFO) {}

    //static const char* logLevelToString(LogLevel level) {
    std::string getLogLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

    LogLevel currentLevel_;
    mutable std::mutex mutex_;
};

// Convenience macros for logging
#define LOG_DEBUG(message) Logger::getInstance().log(message, Logger::LogLevel::DEBUG)
#define LOG_INFO(message) Logger::getInstance().log(message, Logger::LogLevel::INFO)
#define LOG_WARNING(message) Logger::getInstance().log(message, Logger::LogLevel::WARNING)
#define LOG_ERROR(message) Logger::getInstance().log(message, Logger::LogLevel::ERROR)

#endif // LOGGER_HPP