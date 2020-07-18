#pragma once

#include <Common/MLogging.h>
#include <Logger/LoggerImpl/Log.h>

namespace MLog {
	class MLoggerImpl {
	public:
		static void logNow(Log&& log_);

	private:
		std::queue<Log> log_;
		std::mutex lock_;
		std::condition_variable cv_;
	};
}