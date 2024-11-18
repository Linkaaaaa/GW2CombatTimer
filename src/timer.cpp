#include <chrono>
#include <string>
#include <vector>
#include <time.h>

#include "timer.h"
#include "settings.h"

TimeInfo current;
std::vector<TimeInfo> previous;
bool running = false;

namespace timer {
	void Start() {
		if (!running) {
			current = {};
			running = true;
			current.start = std::chrono::system_clock::now();
		}
	}

	void Stop() {
		if (running) {
			previous.push_back(current);
			running = false;
			current = {};
		}
	}

	void Update() {
		current.end = std::chrono::system_clock::now();
	}

	void ClearPrevious() {
		previous.clear();
	}

	std::string GetCombatTime(const std::chrono::system_clock::duration& delta) {
		int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count() % 1000;
		int seconds = Settings::DisplayMinutes
			? std::chrono::duration_cast<std::chrono::seconds>(delta).count() % 60  // For personal usecase, 100s 000ms needs to be a possibility
			: std::chrono::duration_cast<std::chrono::seconds>(delta).count();
		int minutes = std::chrono::duration_cast<std::chrono::minutes>(delta).count() % 60;
		int hours = std::chrono::duration_cast<std::chrono::hours>(delta).count() % 24;

		std::string result = "";

		if (Settings::UseTimeUnits) {
			result += Settings::DisplayHours ? std::format("{:02}h ", hours) : "";
			result += Settings::DisplayMinutes ? std::format("{:02}m ", minutes) : "";
			result += Settings::DisplayMilliseconds ? std::format("{:02}s ", seconds) : std::format("{:02}s", seconds);
			result += Settings::DisplayMilliseconds ? std::format("{:03}ms ", milliseconds) : "";
		}
		else {
			result += Settings::DisplayHours ? std::format("{:02}:", hours) : "";
			result += Settings::DisplayMinutes ? std::format("{:02}:", minutes) : "";
			result += Settings::DisplayMilliseconds ? std::format("{:02}.", seconds) : std::format("{:02}", seconds);
			result += Settings::DisplayMilliseconds ? std::format("{:03}", milliseconds) : "";
		}
		return result;
	}

	std::string GetTotalCombatTime(const std::vector <TimeInfo>& ci) {
		std::chrono::system_clock::duration delta{};

		for (const TimeInfo& info : ci) {
			delta += info.end - info.start;
		}
		return GetCombatTime(delta);
	}

	std::string GetDate(const std::chrono::system_clock::time_point& tp) {
		if (tp == std::chrono::system_clock::time_point{}) {
			return "";
		}

		struct tm lt;
		std::stringstream ss;
		std::time_t time = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
		int ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count() % 1000;

		if (localtime_s(&lt, &time) == 0) {
			if (Settings::DisplayFullTimestampDate) {
				ss << std::put_time(&lt, "%Y-%m-%d %H:%M:%S")
					<< '.' << std::setw(3) << std::setfill('0') << ms;
			}
			else {
				ss << std::put_time(&lt, "%H:%M:%S")
					<< '.' << std::setw(3) << std::setfill('0') << ms;
			}
		}

		return ss.str();
	}
}