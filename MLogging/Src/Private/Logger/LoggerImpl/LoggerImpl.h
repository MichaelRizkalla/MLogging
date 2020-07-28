#pragma once

#include <Common/MLogging.h>
#include <Logger/LoggerImpl/Log.h>

namespace MLog {
	class MLoggerImpl {
		friend class MLogger;

	public:	
		static MLoggerImpl* getInstance();

		void run();

		void stop();

		bool isRunning();

		void add(Log&& log_);

	private:
		void logNow(Log&& log_);

		void extract();

		bool waitAndPop(Log& log);

	protected:
		// TODO: replace queue with a blocking queue implementation
		std::queue<Log>				logs_; 
		std::mutex				lock_;
		std::atomic_bool			state_;
		std::future<void>			this_;
		std::condition_variable			cv_;
		std::unique_ptr<MLoggerImpl>		instance;

		struct make_enabler {};

	public:
		MLoggerImpl(make_enabler);
		~MLoggerImpl();

		MLoggerImpl(const MLoggerImpl&) = delete;
		MLoggerImpl(MLoggerImpl&&) = delete;
		MLoggerImpl& operator=(const MLoggerImpl&) = delete;
		MLoggerImpl& operator=(MLoggerImpl&&) = delete;
	};
}
