#include <MLoggingPCH.h>
#include <Logger/LoggerImpl/LoggerImpl.h>
#include <Logger/MLogger.h>

namespace MLog {

	void MLoggerImpl::logNow(Log&& log) {
		if (!MLogger::state_) {
			throw MLog::LoggerIsNotStarted();
		}
		*MLogger::out_ << log.level << ":: " << log.message << '\n';
		if (MLogger::callbacks_[log.level] != nullptr) {
			MLogger::callbacks_[log.level]();
		}
	}

}