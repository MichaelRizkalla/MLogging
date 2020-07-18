#pragma once
#include <Common/MLogging.h>
#include <Enums/Enums.h>

namespace MLog {
	struct Log {
		Log(Level level_, const char* message_) {
			level = level_;
			message = message_;
		}

		Level level;

		const char* message;
	};
}