#include "UnitTestPCH.h"
#include <Logger/MLogger.h>
#include <Logger/Logger.h>  
#include <thread>

TEST(Log, directLog) {
    MLog::MLogger::setLaunchMode(MLog::launch::seq);
    MLog::MLogger::setOutputTarget(std::cout);
    MLog::MLogger::setInformationCallback([&]() {std::cout << "Information callback!\n"; });

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);

    MLog::MLogger::start();

    int count = 1;
    EXPECT_NO_THROW(MLog::log(MLog::Level::Information, "This is log"));

    MLog::MLogger::setInformationCallback(nullptr);
    EXPECT_NO_THROW(MLog::log(MLog::Level::Information, "Testing", " templates ", count));

    MLog::MLogger::stop();

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);

}

TEST(Log, asyncLog) {
    MLog::MLogger::setLaunchMode(MLog::launch::async);
    MLog::MLogger::setOutputTarget(std::cout);
    MLog::MLogger::setInformationCallback([&]() {std::cout << "Information callback!\n"; });

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);

    MLog::MLogger::start();

    int count = 1;
    MLog::log(MLog::Level::Information, "This is log");

    MLog::MLogger::setInformationCallback(nullptr);
    MLog::log(MLog::Level::Information, "Testing", " templates ", count, " | ", count);

    MLog::MLogger::stop();

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);
}