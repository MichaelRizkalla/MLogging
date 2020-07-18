#include "UnitTestPCH.h"
#include <Logger/MLogger.h>
#include <Logger/Logger.h>

TEST(Log, directLog) {
    MLog::MLogger::setLaunchMode(MLog::launch::seq);
    MLog::MLogger::setOutputTarget(std::cout);
    MLog::MLogger::setInformationCallback([&]() {std::cout << "Information callback!\n"; });

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::LoggerIsNotStarted);

    MLog::MLogger::start();

    int count = 1;
    EXPECT_NO_THROW(MLog::log(MLog::Level::Information, "This is log"));

    MLog::MLogger::setInformationCallback(nullptr);
    EXPECT_NO_THROW(MLog::log(MLog::Level::Information, "Testing", " templates ", count));

    MLog::MLogger::stop();

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::LoggerIsNotStarted);

}