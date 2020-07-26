#include <MLoggingPCH.h>
#include <Logger/MLogger.h>

#include <Logger/LoggerImpl/LoggerImpl.h>

namespace MLog {

	std::ostream* MLogger::out_ = nullptr;

	launch MLogger::mode_ = launch::invalid;

	std::map<Level, std::function<void()>> MLogger::callbacks_ = { {Level::Information, nullptr}, {Level::Warning, nullptr}, {Level::Error, nullptr} };

	std::atomic_bool MLogger::state_ = false;

	void MLogger::setOutputTarget(std::ostream& os) noexcept {
		if (state_ == true)
			return;
		out_ = &os;
	}

	void MLogger::setLaunchMode(launch&& mode) noexcept {
		if (state_ == true)
			return;
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
		if (mode_ == launch::invalid || out_ == nullptr) {
			throw MLoggerIsNotConfigured();
		}
		else if (state_ == true) {
			throw MLoggerIsAlreadyStarted();
		}
		state_ = true; 
		if (mode_ == launch::async) {
			MLog::MLoggerImpl::getInstance()->run();
		}
	}
	
	void MLogger::stop() {
		if (state_ == false) {
			throw MLoggerIsNotStarted();
		}
		if (mode_ == launch::async) {
			MLog::MLoggerImpl::getInstance()->stop();
		}
		state_ = false;
	}

	bool MLogger::isRunning() {
		return MLog::MLoggerImpl::getInstance()->isRunning();
	}

	std::map<Level, std::function<void()>> MLogger::getCallbacks() {
		return callbacks_;
	}

	std::ostream* MLogger::getTarget() {
		return out_;
	}
}