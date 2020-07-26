#include <MLoggingPCH.h>
#include <Logger/LoggerImpl/LoggerImpl.h>
#include <Logger/MLogger.h>

namespace MLog {

	MLoggerImpl::MLoggerImpl(enable_make_shared) {
		state_ = false;
	}

	MLoggerImpl::~MLoggerImpl() = default;

	void MLoggerImpl::logNow(Log&& log) {
		*log.target << log.level << ":: " << log.message << '\n';
		if (log.callback != nullptr) {
			log.callback();
		}
	}

	std::shared_ptr<MLoggerImpl> MLoggerImpl::getInstance() {
		static std::shared_ptr<MLoggerImpl> instance = nullptr;

		if (instance == nullptr) {
			instance = std::make_shared<MLoggerImpl>(enable_make_shared{});
		}
		return instance;
	}

	void MLoggerImpl::run() {
		state_ = true;
		this_ = std::async(std::launch::async, &MLoggerImpl::extract, this);
	}

	void MLoggerImpl::extract() {
		bool toLog;
		do {
			Log aLog;
			toLog = waitAndPop(aLog);
			if (toLog) logNow(std::move(aLog));
			// Exit when the logger is stopped 
			// And no elements left in the queue
		} while (toLog || state_);
	}

	bool MLoggerImpl::waitAndPop(Log& log) {
		std::unique_lock guard(lock_);
		cv_.wait(guard, [&]() {return !logs_.empty() || !state_; });
		if ((logs_.empty() && !state_) || logs_.empty())
			return false;

		log = std::move(logs_.front());
		logs_.pop();
		return true;
	}

	void MLoggerImpl::stop() {
		state_ = false;
		this_.wait();
	}

	bool MLoggerImpl::isRunning() {
		return state_;
	}

	void MLoggerImpl::add(Log&& log_) {
		if (!MLog::getState()) {
			throw MLog::MLoggerIsNotStarted();
		}

		if (MLog::getMode() == launch::seq)
			logNow(std::move(log_));
		else {
			std::lock_guard<std::mutex> guard(lock_);
			logs_.push(std::move(log_));
			cv_.notify_one();
		}
	}
}