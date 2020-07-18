#include <MLoggingPCH.h>
#include <Logger/Logger.h>
#include <Logger/LoggerImpl/LoggerImpl.h>
#include <Logger/LoggerImpl/Log.h>

namespace MLog {

	void log(Level level, const char* message) {
		MLoggerImpl::logNow(Log(level, message));
	}

}