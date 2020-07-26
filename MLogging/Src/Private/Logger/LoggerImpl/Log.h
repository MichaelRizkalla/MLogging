#pragma once
#include <Common/MLogging.h>
#include <Enums/Enums.h>

namespace MLog {
	struct Log {
		Log() : message(nullptr), messageSize(0), level(Level::Information), callback(nullptr), target(nullptr) {}
		Log(Level&& level_, const char*&& message_, std::ostream* target_, std::function<void()>&& callback_) {
			level = std::move(level_);
			message = std::move(message_);
			messageSize = std::strlen(message_);
			target = std::move(target_);
			callback = std::move(callback_);
		}
		Log(const Level& level_, const char* message_, std::ostream* const target_, const std::function<void()>& callback_) {
			level = level_;
			messageSize = std::strlen(message_);
			char *m = new char[messageSize + 1];
			std::memcpy(m, message_, messageSize);
			m[messageSize] = '\0';
			message = m;
			target = target_;
			callback = callback_;
		}
		Log(const Log& rhs) {
			level = rhs.level;
			messageSize = rhs.messageSize;
			char* m = new char[messageSize];
			std::memcpy(m, rhs.message, messageSize);
			message = m;
			target = rhs.target;
			callback = rhs.callback;
		}
		Log(Log&& rhs) noexcept {
			level = rhs.level;
			messageSize = rhs.messageSize;
			message = std::move(rhs.message);
			rhs.message = nullptr;
			target = std::move(rhs.target);
			callback = std::move(rhs.callback);
		}
		Log& operator=(const Log& rhs) {
			level = rhs.level;
			messageSize = rhs.messageSize;
			char* m = new char[messageSize + 1];
			std::memcpy(m, rhs.message, messageSize);
			m[messageSize] = '\0';
			message = m;
			target = rhs.target;
			callback = rhs.callback;
			return *this;
		}
		Log& operator=(Log&& rhs) noexcept {
			level = rhs.level;
			messageSize = rhs.messageSize;
			message = std::move(rhs.message);
			rhs.message = nullptr;
			target = std::move(rhs.target);
			callback = std::move(rhs.callback);
			return *this;
		}
		~Log() {
			if(message != nullptr)
				delete[] message;
		}

		Level level;

		const char* message;

		std::function<void()> callback;

		std::ostream* target;

		size_t messageSize;
	};
}