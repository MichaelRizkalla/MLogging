#pragma once

#include <Common/MLogging.h>
#include <Logger/LoggerImpl/Log.h>

namespace MLog {
	class MLoggerImpl {
		friend class MLogger;
	public:	

		static std::shared_ptr<MLoggerImpl> getInstance();

		void run();

		void stop();

		bool isRunning();

		void add(Log&& log_);

	private:

		void logNow(Log&& log_);

		void extract();

		bool waitAndPop(Log& log);

		struct enable_make_shared {
		protected:
			enable_make_shared() {}
			friend class MLoggerImpl;
		};

		// TODO: replace queue with a blocking queue implementation
		std::queue<Log>			logs_; 
		std::mutex				lock_;
		std::atomic_bool		state_;
		std::future<void>		this_;
		std::condition_variable cv_;

	public:

		MLoggerImpl(enable_make_shared);

		~MLoggerImpl();

	};
}