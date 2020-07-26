#pragma once

#include <Common/MLogging.h>
#include <Enums/Enums.h>

namespace MLog {
	extern "C" MLOGGING(api) void log(Level level, const char* message);

	template <class... Args, class TValid = std::enable_if_t < MLog::is_out_stream_friendly < std::stringstream, Args...>::value > >
	void log(Level level, Args... messageComponents) {
		std::stringstream ss;
		(ss << ... << messageComponents);
		log(level, ss.str().c_str());
	}
}