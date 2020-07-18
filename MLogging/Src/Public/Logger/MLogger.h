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

		MLOGGING(class) static void setOutputTarget(std::ostream& os) noexcept;

		MLOGGING(class) static void setInformationCallback(Callback&& callback) noexcept;

		MLOGGING(class) static void setWarningCallback(Callback&& callback) noexcept;

		MLOGGING(class) static void setErrorCallback(Callback&& callback) noexcept;

		MLOGGING(class) static void setInformationCallback(const Callback& callback) noexcept;

		MLOGGING(class) static void setWarningCallback(const Callback& callback) noexcept;

		MLOGGING(class) static void setErrorCallback(const Callback& callback) noexcept;

		MLOGGING(class) static void setLaunchMode(launch&& mode) noexcept;

		MLOGGING(class) static void start();

		MLOGGING(class) static void stop();

	private:
		static std::ostream* out_;
		static launch mode_;
		static std::map<Level, std::function<void()>> callbacks_;
		static std::atomic_bool state_;
	};

}