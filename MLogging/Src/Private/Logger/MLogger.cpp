#include <MLoggingPCH.h>
#include <Logger/MLogger.h>

namespace MLog {

	std::ostream* MLogger::out_ = nullptr;

	launch MLogger::mode_ = launch::invalid;

	std::map<Level, std::function<void()>> MLogger::callbacks_ = { {Level::Information, nullptr}, {Level::Warning, nullptr}, {Level::Error, nullptr} };

	std::atomic_bool MLogger::state_ = false;

	void MLogger::setOutputTarget(std::ostream& os) noexcept {
		out_ = &os;
	}

	void MLogger::setLaunchMode(launch&& mode) noexcept {
		mode_ = std::move(mode);
	}

	void MLogger::setInformationCallback(Callback&& callback) noexcept {
		callbacks_[Level::Information] = std::move(callback);
	}

	void MLogger::setWarningCallback(Callback&& callback) noexcept {
		callbacks_[Level::Warning] = std::move(callback);
	}

	void MLogger::setErrorCallback(Callback&& callback) noexcept {
		callbacks_[Level::Error] = std::move(callback);
	}

	void MLogger::setInformationCallback(const Callback& callback) noexcept {
		callbacks_[Level::Information] = callback;
	}

	void MLogger::setWarningCallback(const Callback& callback) noexcept {
		callbacks_[Level::Warning] = callback;
	}

	void MLogger::setErrorCallback(const Callback& callback) noexcept {
		callbacks_[Level::Error] = callback;
	}

	void MLogger::start() {
		state_ = true;
	}

	void MLogger::stop() {
		state_ = false;
	}
}