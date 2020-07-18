#include "UnitTestPCH.h"
#include <Logger/Logger.h>
#include <Logger/MLogger.h>

TEST(Log, directLog) {
    MLog::MLogger::setLaunchMode(MLog::launch::seq);
    MLog::MLogger::setOutputTarget(std::cout);
    MLog::MLogger::setInformationCallback([&]() {std::cout << "Entered a callback!\n"; });

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::LoggerIsNotStarted);

    MLog::MLogger::start();

    EXPECT_NO_THROW(MLog::log(MLog::Level::Information, "This is log"));

    MLog::MLogger::stop();

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::LoggerIsNotStarted);
}