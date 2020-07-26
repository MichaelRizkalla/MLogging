#pragma once

namespace MLog {

	struct MLoggerIsNotStarted : public std::exception {
		const char* what() const throw () {
			return "MLogger is not started!";
		}
	};

	struct MLoggerIsNotConfigured : public std::exception {
		const char* what() const throw () {
			return "MLogger is not configured!";
		}
	};

	struct MLoggerIsAlreadyStarted : public std::exception {
		const char* what() const throw () {
			return "MLogger is already started!";
		}
	};

}