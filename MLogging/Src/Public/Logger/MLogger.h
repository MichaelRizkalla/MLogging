#pragma once

#include <Common/MLogging.h>
#include <Enums/Enums.h>

namespace MLog {
	class MLoggerImpl;

	class MLogger {
		friend class MLoggerImpl;

	public:
		using CallbackType = void();
		using Callback = std::function<CallbackType>;

		/// <summary>
		/// Changes the output target, if MLogger is already started
		/// the new target is ignored
		/// </summary>
		MLOGGING(class) static void setOutputTarget(std::ostream& os) noexcept;

		/// <summary>
		/// Changes the launch mode, if MLogger is already started
		/// the new launch mode is ignored
		/// </summary>
		MLOGGING(class) static void setLaunchMode(launch&& mode) noexcept;

		/// <summary>
		/// Sets the callback for logs of Level::Information 
		/// </summary>
		MLOGGING(class) static void setInformationCallback(Callback&& callback) noexcept;

		/// <summary>
		/// Sets the callback for logs of Level::Warning 
		/// </summary>
		MLOGGING(class) static void setWarningCallback(Callback&& callback) noexcept;

		/// <summary>
		/// Sets the callback for logs of Level::Error 
		/// </summary>
		MLOGGING(class) static void setErrorCallback(Callback&& callback) noexcept;

		/// <summary>
		/// Sets the callback for logs of Level::Information 
		/// </summary>
		MLOGGING(class) static void setInformationCallback(const Callback& callback) noexcept;

		/// <summary>
		/// Sets the callback for logs of Level::Warning 
		/// </summary>
		MLOGGING(class) static void setWarningCallback(const Callback& callback) noexcept;

		/// <summary>
		/// Sets the callback for logs of Level::Error 
		/// </summary>
		MLOGGING(class) static void setErrorCallback(const Callback& callback) noexcept;

		/// <summary>
		/// Startes the logger if configuration is complete
		/// throws if: launch mode or target are not specified
		///				or the logger is already started
		/// </summary>
		MLOGGING(class) static void start();

		/// <summary>
		/// stops the logger
		/// throws if: the logger is already stopped
		/// </summary>
		MLOGGING(class) static void stop();

		/// <summary>
		/// Returns if the logger is running
		/// </summary>
		MLOGGING(class) static bool isRunning();

		static std::map<Level, std::function<void()>> getCallbacks();

		static std::ostream* getTarget();

	private:
		static std::ostream* out_;
		static launch mode_;
		static std::map<Level, std::function<void()>> callbacks_;
		static std::atomic_bool state_;
	};

}