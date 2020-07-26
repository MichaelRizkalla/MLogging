#include "UnitTestPCH.h"
#include <Logger/MLogger.h>
#include <Logger/Logger.h>  
#include <thread>
#include <fstream>

TEST(Log, directLog) {
    MLog::setLaunchMode(MLog::launch::seq);
    MLog::setOutputTarget(std::cout);
    MLog::setInformationCallback([]() {std::cout << "Information callback!\n"; });

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);

    MLog::start();

    int count = 1;
    EXPECT_NO_THROW(MLog::log(MLog::Level::Information, "This is log"));

    MLog::setInformationCallback(nullptr);
    EXPECT_NO_THROW(MLog::log(MLog::Level::Information, "Testing", " templates ", count));

    MLog::stop();

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);
}

TEST(Log, asyncLog) {
    MLog::setLaunchMode(MLog::launch::async);
    MLog::setOutputTarget(std::cout);
    MLog::setInformationCallback([]() {std::cout << "Information callback!\n"; });

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);

    MLog::start();

    int count = 1;
    MLog::log(MLog::Level::Information, "This is log");

    MLog::setInformationCallback(nullptr);
    MLog::log(MLog::Level::Information, "Testing", " templates ", count, " | ", count);

    MLog::stop();

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);
}

TEST(Log, asyncLogToFile) {
    MLog::setLaunchMode(MLog::launch::async);

    std::ofstream fs;
    fs.open("log.log", std::ios::out);

    MLog::setOutputTarget(fs);
    MLog::setInformationCallback(
        []() {
            std::cout << "Information callback called!\n"; 
        });

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);

    MLog::start();

    int count = 1;
    MLog::log(MLog::Level::Information, "This is log");

    MLog::setInformationCallback(nullptr);
    MLog::log(MLog::Level::Information, "Testing", " templates ", count, " | ", count);

    MLog::stop();

    EXPECT_THROW(MLog::log(MLog::Level::Information, "This is log"), MLog::MLoggerIsNotStarted);

    fs.close();
}