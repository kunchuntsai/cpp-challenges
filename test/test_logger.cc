#include "logger.h"
#include "unit_test.h"
#include <sstream>
#include <thread>

// Helper function to capture cout output
class CoutCapture {
    std::streambuf* old;
    std::ostringstream capture;

public:
    CoutCapture() : old(std::cout.rdbuf(capture.rdbuf())) {}
    ~CoutCapture() { std::cout.rdbuf(old); }
    std::string get() const { return capture.str(); }
};

TEST(LoggerSingletonBehavior) {
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    ASSERT_TRUE(&logger1 == &logger2);
}

TEST(LoggerSetAndGetLogLevel) {
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::DEBUG);
    ASSERT_EQUAL(Logger::DEBUG, logger.getLogLevel());
    
    logger.setLogLevel(Logger::ERROR);
    ASSERT_EQUAL(Logger::ERROR, logger.getLogLevel());
}

TEST(LoggerLogging) {
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::INFO);

    CoutCapture capture;
    std::string message = "Test log message";
    logger.log(message);
    
    std::string output = capture.get();
    ASSERT_TRUE(output.find("[INFO]") != std::string::npos);
    ASSERT_TRUE(output.find("Test log message") != std::string::npos);
}

TEST(LoggerThreadSafety) {
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::DEBUG);

    std::thread t1([]() {
        Logger::getInstance().setLogLevel(Logger::ERROR);
    });

    std::thread t2([]() {
        Logger::getInstance().setLogLevel(Logger::WARNING);
    });

    t1.join();
    t2.join();

    // The final log level could be either ERROR or WARNING depending on which thread finished last
    Logger::LogLevel finalLevel = logger.getLogLevel();
    ASSERT_TRUE(finalLevel == Logger::ERROR || finalLevel == Logger::WARNING);
}

void runLoggerTests() {
    UnitTest::runAllTests();
}