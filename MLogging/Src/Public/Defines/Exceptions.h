#pragma once

namespace MLog {

	struct LoggerIsNotStarted : public std::exception {
		const char* what() const throw () {
			return "Logger is not started!";
		}
	};

}