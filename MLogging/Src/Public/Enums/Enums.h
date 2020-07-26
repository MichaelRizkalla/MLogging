#pragma once
#include <Common/MLogging.h>

namespace MLog {

	enum class launch : uint8_t {

		seq,

		async,

		invalid = std::numeric_limits<std::underlying_type<MLog::launch>::type>::max(),
	};

	enum class Level : uint8_t {
		Information,

		Warning,

		Error
	};
}

extern "C" MLOGGING(enum) std::ostream& operator<<(std::ostream& os, MLog::Level lvl); 