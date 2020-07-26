#include <MLoggingPCH.h>
#include <Logger/MLogger.h>

#include <Logger/LoggerImpl/LoggerImpl.h>

namespace MLog {

	static std::ostream* out_ = nullptr;

	static launch mode_ = launch::invalid;

	static std::map<Level, void(*)()> callbacks_ = { {Level::Information, nullptr}, {Level::Warning, nullptr}, {Level::Error, nullptr} };

	static std::atomic_bool state_ = false;

	void setOutputTarget(std::ostream& os) {
		if (state_ == true)
			return;
		out_ = &os;
	}

	void setLaunchMode(launch&& mode) {
		if (state_ == true)
			return;
		mode_ = std::move(mode);
	}

	void setInformationCallback(Callback callback) {
		callbacks_[Level::Information] = std::move(callback);
	}

	void setWarningCallback(Callback callback) {
		callbacks_[Level::Warning] = std::move(callback);
	}

	void setErrorCallback(Callback callback) {
		callbacks_[Level::Error] = std::move(callback);
	}

	void start() noexcept(false) {
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
	
	void stop() noexcept(false) {
		if (state_ == false) {
			throw MLoggerIsNotStarted();
		}
		if (mode_ == launch::async) {
			MLog::MLoggerImpl::getInstance()->stop();
		}
		state_ = false;
	}

	bool isRunning() {
		return MLog::MLoggerImpl::getInstance()->isRunning();
	}

	void* getCallbacks(Level lvl) {
		return callbacks_[lvl];
	}

	std::ostream* getTarget() {
		return out_;
	}

	launch getMode() {
		return mode_;
	}

	bool getState() {
		return state_;
	}
}