#pragma once

#include <Common/MLogging.h>
#include <Enums/Enums.h>

namespace MLog {
	MLOGGING(api) void log(Level level, const char* message);
}