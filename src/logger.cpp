// Challenge 3: Design a thread-safe singleton logger
// Implement a thread-safe singleton logger class that can be used across multiple threads.
// It should support the following:
// - getInstance(): Return the single instance of the logger
// - log(message): Add a message to the log
// - setLogLevel(level): Set the current log level
// - getLogLevel(): Get the current log level
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

    void log(std::string message) {
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

int main() {
    Logger& log = Logger::getInstance();
    log.log("Check log level");

    log.setLogLevel(Logger::WARNING);
    log.log("Check log level");

    return 0;
}