#pragma once

#include <Common/MLogging.h>
#include <Enums/Enums.h>

namespace MLog {
	using CallbackType = void() ;
	using Callback = void(*)();
}

extern "C" {

	namespace MLog {

		/// <summary>
		/// Changes the output target, if MLogger is already started
		/// the new target is ignored
		/// </summary>
		MLOGGING(class) void setOutputTarget(std::ostream& os);

		/// <summary>
		/// Changes the launch mode, if MLogger is already started
		/// the new launch mode is ignored
		/// </summary>
		MLOGGING(class) void setLaunchMode(launch&& mode);

		/// <summary>
		/// Sets the callback for logs of Level::Information 
		/// </summary>
		MLOGGING(class) void setInformationCallback(Callback callback);

		/// <summary>
		/// Sets the callback for logs of Level::Warning 
		/// </summary>
		MLOGGING(class) void setWarningCallback(Callback callback);

		/// <summary>
		/// Sets the callback for logs of Level::Error 
		/// </summary>
		MLOGGING(class) void setErrorCallback(Callback callback);

		/// <summary>
		/// Startes the logger if configuration is complete
		/// throws if: launch mode or target are not specified
		///				or the logger is already started
		/// </summary>
		MLOGGING(class) void start() noexcept(false);

		/// <summary>
		/// stops the logger
		/// throws if: the logger is already stopped
		/// </summary>
		MLOGGING(class) void stop() noexcept(false);

		/// <summary>
		/// Returns if the logger is running
		/// </summary>
		MLOGGING(class) bool isRunning();

		void* getCallbacks(Level lvl);

		std::ostream* getTarget();

		launch getMode();

		bool getState();
	}
}