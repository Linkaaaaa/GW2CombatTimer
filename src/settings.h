#ifndef SETTINGS_H
#define SETTINGS_H

#include <mutex>

#include "submodules/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

extern const char* WINDOW_COMBAT_TIMER_KEY;
extern const char* WINDOW_PREVIOUS_TIMES_KEY;

extern const char* SHOW_WINDOW_COMBAT_TIMER;
extern const char* SHOW_WINDOW_PREVIOUS_TIMES;

extern const char* DISPLAY_COMBAT_STATUS;
extern const char* DISPLAY_FINAL_TIME;
extern const char* DISPLAY_MILLISECONDS;
extern const char* DISPLAY_MINUTES;
extern const char* DISPLAY_HOURS;
extern const char* DISPLAY_START_TIMESTAMP;
extern const char* DISPLAY_END_TIMESTAMP;
extern const char* DISPLAY_FULL_TIMESTAMP_DATE;
extern const char* USE_TIME_UNITS;

extern const char* MIN_COMBAT_TIMER_WINDOW_WIDTH;
extern const char* MIN_COMBAT_TIMER_WINDOW_HEIGHT;
extern const char* MAX_COMBAT_TIMER_WINDOW_WIDTH;
extern const char* MAX_COMBAT_TIMER_WINDOW_HEIGHT;
extern const char* MIN_PREVIOUS_TIMES_WINDOW_WIDTH;
extern const char* MIN_PREVIOUS_TIMES_WINDOW_HEIGHT;
extern const char* MAX_PREVIOUS_TIMES_WINDOW_WIDTH;
extern const char* MAX_PREVIOUS_TIMES_WINDOW_HEIGHT;

namespace Settings
{
	extern std::mutex Mutex;
	extern json	Settings;

	void Load(std::filesystem::path filePath);
	void Save(std::filesystem::path filePath);

	extern bool ShowWindowCombatTimer;
	extern bool ShowWindowPreviousTimes;

	extern bool DisplayCombatStatus;
	extern bool DisplayFinalTime;
	extern bool DisplayMilliseconds;
	extern bool DisplayMinutes;
	extern bool DisplayHours;
	extern bool DisplayStartTimestamp;
	extern bool DisplayEndTimestamp;
	extern bool DisplayFullTimestampDate;
	extern bool UseTimeUnits;

	extern float MinCombatTimerWindowWidth;
	extern float MinCombatTimerWindowHeight;
	extern float MaxCombatTimerWindowWidth;
	extern float MaxCombatTimerWindowHeight;
	extern float MinPreviousTimesWindowWidth;
	extern float MinPreviousTimesWindowHeight;
	extern float MaxPreviousTimesWindowWidth;
	extern float MaxPreviousTimesWindowHeight;
}

#endif