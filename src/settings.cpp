#include <filesystem>
#include <fstream>

#include "settings.h"
#include "shared.h"

const char* WINDOW_COMBAT_TIMER_KEY = "WindowCombatTimer";
const char* WINDOW_PREVIOUS_TIMES_KEY = "WindowPreviousTimes";

const char* SHOW_WINDOW_COMBAT_TIMER = "ShowWindowCombatTimer";
const char* SHOW_WINDOW_PREVIOUS_TIMES = "ShowWindowPreviousTimes";

const char* DISPLAY_COMBAT_STATUS = "DisplayCombatStatus";
const char* DISPLAY_FINAL_TIME = "DisplayFinalTime";
const char* DISPLAY_MILLISECONDS = "DisplayMilliseconds";
const char* DISPLAY_MINUTES = "DisplayMinutes";
const char* DISPLAY_HOURS = "DisplayHours";
const char* DISPLAY_START_TIMESTAMP = "DisplayStartTimestamp";
const char* DISPLAY_END_TIMESTAMP = "DisplayEndTimestamp";
const char* DISPLAY_FULL_TIMESTAMP_DATE = "DisplayFullTimestampDate";
const char* USE_TIME_UNITS = "UseTimeUnits";

const char* MIN_COMBAT_TIMER_WINDOW_WIDTH = "MinCombatTimerWindowWidth";
const char* MIN_COMBAT_TIMER_WINDOW_HEIGHT = "MinCombatTimerWindowHeight";
const char* MAX_COMBAT_TIMER_WINDOW_WIDTH = "MaxCombatTimerWindowWidth";
const char* MAX_COMBAT_TIMER_WINDOW_HEIGHT = "MaxCombatTimerWindowHeight";
const char* MIN_PREVIOUS_TIMES_WINDOW_WIDTH = "MinPreviousTimesWindowWidth";
const char* MIN_PREVIOUS_TIMES_WINDOW_HEIGHT = "MinPreviousTimesWindowHeight";
const char* MAX_PREVIOUS_TIMES_WINDOW_WIDTH = "MaxPreviousTimesWindowWidth";
const char* MAX_PREVIOUS_TIMES_WINDOW_HEIGHT = "MaxPreviousTimesWindowHeight";

namespace Settings
{
	std::mutex Mutex;
	json Settings = json::object();

	void Load(std::filesystem::path filePath) {
		if (!std::filesystem::exists(filePath)) return;

		try {
			std::scoped_lock lck(Mutex);
			std::ifstream file(filePath);
			Settings = json::parse(file);
			file.close();
		}
		catch (json::parse_error& ex) {
			APIDefs->Log(ELogLevel_CRITICAL, ADDON_NAME, std::format("failed to parse settings.json file. exception details: {}", ex.what()).c_str());
		}

		/* Window Visibility */
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][SHOW_WINDOW_COMBAT_TIMER].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][SHOW_WINDOW_COMBAT_TIMER].get_to<bool>(ShowWindowCombatTimer);
		}
		if (!Settings[WINDOW_PREVIOUS_TIMES_KEY][SHOW_WINDOW_PREVIOUS_TIMES].is_null()) {
			Settings[WINDOW_PREVIOUS_TIMES_KEY][SHOW_WINDOW_PREVIOUS_TIMES].get_to<bool>(ShowWindowPreviousTimes);
		}

		/* Display Combat Status */
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_COMBAT_STATUS].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_COMBAT_STATUS].get_to<bool>(DisplayCombatStatus);
		}

		/* Display Final Time */
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_FINAL_TIME].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_FINAL_TIME].get_to<bool>(DisplayFinalTime);
		}

		/* Display Start/End Timestamp */
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_START_TIMESTAMP].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_START_TIMESTAMP].get_to<bool>(DisplayStartTimestamp);
		}
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_END_TIMESTAMP].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_END_TIMESTAMP].get_to<bool>(DisplayEndTimestamp);
		}
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_FULL_TIMESTAMP_DATE].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_FULL_TIMESTAMP_DATE].get_to<bool>(DisplayFullTimestampDate);
		}

		/* Display Time */
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_MILLISECONDS].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_MILLISECONDS].get_to<bool>(DisplayMilliseconds);
		}
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_HOURS].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_HOURS].get_to<bool>(DisplayHours);
		}
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_MINUTES].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_MINUTES].get_to<bool>(DisplayMinutes);
		}

		/* Time Units */
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][USE_TIME_UNITS].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][USE_TIME_UNITS].get_to<bool>(UseTimeUnits);
		}

		/* Window Sizing */
		/* Combat Timer */
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][MIN_COMBAT_TIMER_WINDOW_WIDTH].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][MIN_COMBAT_TIMER_WINDOW_WIDTH].get_to<float>(MinCombatTimerWindowWidth);
		}
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][MIN_COMBAT_TIMER_WINDOW_HEIGHT].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][MIN_COMBAT_TIMER_WINDOW_HEIGHT].get_to<float>(MinCombatTimerWindowHeight);
		}
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][MAX_COMBAT_TIMER_WINDOW_WIDTH].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][MAX_COMBAT_TIMER_WINDOW_WIDTH].get_to<float>(MaxCombatTimerWindowWidth);
		}
		if (!Settings[WINDOW_COMBAT_TIMER_KEY][MAX_COMBAT_TIMER_WINDOW_HEIGHT].is_null()) {
			Settings[WINDOW_COMBAT_TIMER_KEY][MAX_COMBAT_TIMER_WINDOW_HEIGHT].get_to<float>(MaxCombatTimerWindowHeight);
		}
		/* Previous Times */
		if (!Settings[WINDOW_PREVIOUS_TIMES_KEY][MIN_PREVIOUS_TIMES_WINDOW_WIDTH].is_null()) {
			Settings[WINDOW_PREVIOUS_TIMES_KEY][MIN_PREVIOUS_TIMES_WINDOW_WIDTH].get_to<float>(MinPreviousTimesWindowWidth);
		}
		if (!Settings[WINDOW_PREVIOUS_TIMES_KEY][MIN_PREVIOUS_TIMES_WINDOW_HEIGHT].is_null()) {
			Settings[WINDOW_PREVIOUS_TIMES_KEY][MIN_PREVIOUS_TIMES_WINDOW_HEIGHT].get_to<float>(MinPreviousTimesWindowHeight);
		}
		if (!Settings[WINDOW_PREVIOUS_TIMES_KEY][MAX_PREVIOUS_TIMES_WINDOW_WIDTH].is_null()) {
			Settings[WINDOW_PREVIOUS_TIMES_KEY][MAX_PREVIOUS_TIMES_WINDOW_WIDTH].get_to<float>(MaxPreviousTimesWindowWidth);
		}
		if (!Settings[WINDOW_PREVIOUS_TIMES_KEY][MAX_PREVIOUS_TIMES_WINDOW_HEIGHT].is_null()) {
			Settings[WINDOW_PREVIOUS_TIMES_KEY][MAX_PREVIOUS_TIMES_WINDOW_HEIGHT].get_to<float>(MaxPreviousTimesWindowHeight);
		}
	}
	void Save(std::filesystem::path filePath) {
		std::scoped_lock lck(Mutex);
		std::ofstream file(filePath);
		file << Settings.dump(4, ' ') << std::endl;
		file.close();
	}

	bool ShowWindowCombatTimer = false;
	bool ShowWindowPreviousTimes = false;

	bool DisplayCombatStatus = true;
	bool DisplayFinalTime = true;
	bool DisplayMilliseconds = true;
	bool DisplayMinutes = false;
	bool DisplayHours = false;
	bool DisplayStartTimestamp = true;
	bool DisplayEndTimestamp = true;
	bool DisplayFullTimestampDate = true;
	bool UseTimeUnits = false;

	float MinCombatTimerWindowWidth = 300.0f;
	float MinCombatTimerWindowHeight = 100.0f;
	float MaxCombatTimerWindowWidth = 800.0f;
	float MaxCombatTimerWindowHeight = 800.0f;
	float MinPreviousTimesWindowWidth = 300.0f;
	float MinPreviousTimesWindowHeight = 100.0f;
	float MaxPreviousTimesWindowWidth = 800.0f;
	float MaxPreviousTimesWindowHeight = 800.0f;
}