#include <MLoggingPCH.h>
#include <Logger/Logger.h>
#include <Logger/LoggerImpl/LoggerImpl.h>
#include <Logger/LoggerImpl/Log.h>
#include <Logger/MLogger.h>

namespace MLog {

	void log(Level level, const char* message) {
		auto logger_ = MLoggerImpl::getInstance();
		logger_->add(Log(level, message, MLogger::getTarget(), MLogger::getCallbacks()[level]));
	}

}