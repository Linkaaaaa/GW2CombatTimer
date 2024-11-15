#include "submodules/nexus/Nexus.h"
#include "submodules/mumble/Mumble.h"
#include "submodules/imgui/imgui.h"
#include "shared.h"
#include "settings.h"
#include "version.h"
#include "timer.h"
#include "gui.h"

void RenderWindowCombatTimer() {
	ImGuiIO& io = ImGui::GetIO();
	bool isInCombat = false;

	if (nullptr != MumbleLink && MumbleLink->Context.IsInCombat == 1) {
		isInCombat = true;
		timer::Start();
		timer::Update();
	}
	else {
		timer::Stop();
	}

	if (!Settings::ShowWindowCombatTimer) {
		return;
	}

	ImGui::SetNextWindowSizeConstraints(
		ImVec2(Settings::MinCombatTimerWindowWidth, Settings::MinCombatTimerWindowHeight),
		ImVec2(Settings::MaxCombatTimerWindowWidth, Settings::MaxCombatTimerWindowHeight)
	);

	if (ImGui::Begin(ADDON_NAME, &Settings::ShowWindowCombatTimer, gui::windowFlags))
	{
		TimeInfo emptyTI{};
		TimeInfo& latest = previous.size() > 0 ? previous[previous.size() - 1] : emptyTI;

		if (Settings::DisplayCombatStatus) {
			ImGui::Text("Status: %s", isInCombat ? "In Combat" : "Out of Combat");
		}

		ImGui::Text("Combat Time: %s", timer::GetCombatTime(current.end - current.start).c_str());

		if (Settings::DisplayFinalTime) {
			ImGui::Text("Final Time: %s", timer::GetCombatTime(latest.end - latest.start).c_str());
		}

		if (Settings::DisplayStartTimestamp) {
			if (isInCombat) {
				ImGui::Text("Start: %s", timer::GetDate(current.start).c_str());
			}
			else {
				ImGui::Text("Start: %s", timer::GetDate(latest.start).c_str());
			}
		}
		if (Settings::DisplayEndTimestamp) {
			if (isInCombat) {
				ImGui::Text("End: %s", timer::GetDate(current.end).c_str());
			}
			else {
				ImGui::Text("End: %s", timer::GetDate(latest.end).c_str());
			}
		}

	}
	ImGui::End();

	// X button clicked, saves only on last frame
	if (!Settings::ShowWindowCombatTimer) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][SHOW_WINDOW_COMBAT_TIMER] = Settings::ShowWindowCombatTimer;
		Settings::Save(SettingsPath);
	}
}

void RenderWindowPreviousTimes() {
	ImGuiIO& io = ImGui::GetIO();

	if (!Settings::ShowWindowPreviousTimes) {
		return;
	}

	ImGui::SetNextWindowSizeConstraints(
		ImVec2(Settings::MinPreviousTimesWindowWidth, Settings::MinPreviousTimesWindowHeight),
		ImVec2(Settings::MaxPreviousTimesWindowWidth, Settings::MaxPreviousTimesWindowHeight)
	);

	if (ImGui::Begin("Previous Times", &Settings::ShowWindowPreviousTimes, gui::windowFlags))
	{
		ImVec2 region = ImGui::GetContentRegionAvail();
		float textY = ImGui::GetTextLineHeightWithSpacing();
		if (ImGui::BeginChild("##ChildTable", ImVec2(region.x, region.y - textY), gui::windowFlags)) {
			if (ImGui::BeginTable("Times", 3, gui::tableFlags)) {
				ImGui::TableSetupColumn("Start", gui::columnFlags);
				ImGui::TableSetupColumn("End", gui::columnFlags);
				ImGui::TableSetupColumn("Time", gui::columnFlags);
				ImGui::TableHeadersRow();
				for (int row = 0; row < previous.size(); row++) {
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text(timer::GetDate(previous[row].start).c_str());
					ImGui::TableSetColumnIndex(1);
					ImGui::Text(timer::GetDate(previous[row].end).c_str());
					ImGui::TableSetColumnIndex(2);
					ImGui::Text(timer::GetCombatTime(previous[row].end - previous[row].start).c_str());
				}
				ImGui::EndTable();
			}
		}
		ImGui::EndChild();
		ImGui::Text("Total Combat Time: %s", timer::GetTotalCombatTime(previous).c_str());
	}
	ImGui::End();

	// X button clicked, saves only on last frame
	if (!Settings::ShowWindowPreviousTimes) {
		Settings::Settings[WINDOW_PREVIOUS_TIMES_KEY][SHOW_WINDOW_PREVIOUS_TIMES] = Settings::ShowWindowPreviousTimes;
		Settings::Save(SettingsPath);
	}
}

void RenderWindowSizingSettings() {
	/* Combat Timer */
	ImGui::Text("Combat Timer Window Sizing");
	if (ImGui::SliderFloat("Min Width##CombatTimerMaxWidth", &Settings::MinCombatTimerWindowWidth, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][MIN_COMBAT_TIMER_WINDOW_WIDTH] = Settings::MinCombatTimerWindowWidth;
		Settings::Save(SettingsPath);
	}
	if (ImGui::SliderFloat("Max Width##CombatTimerMinWidth", &Settings::MaxCombatTimerWindowWidth, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][MAX_COMBAT_TIMER_WINDOW_WIDTH] = Settings::MaxCombatTimerWindowWidth;
		Settings::Save(SettingsPath);
	}
	if (ImGui::SliderFloat("Min Height##CombatTimerMinHeight", &Settings::MinCombatTimerWindowHeight, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][MIN_COMBAT_TIMER_WINDOW_HEIGHT] = Settings::MinCombatTimerWindowHeight;
		Settings::Save(SettingsPath);
	}
	if (ImGui::SliderFloat("Max Height##CombatTimerMaxHeight", &Settings::MaxCombatTimerWindowHeight, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][MAX_COMBAT_TIMER_WINDOW_HEIGHT] = Settings::MaxCombatTimerWindowHeight;
		Settings::Save(SettingsPath);
	}
	/* Previous Times */
	ImGui::Text("Previous Times Window Sizing");
	if (ImGui::SliderFloat("Min Width##PreviousTimesMinWidth", &Settings::MinPreviousTimesWindowWidth, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_PREVIOUS_TIMES_KEY][MIN_PREVIOUS_TIMES_WINDOW_WIDTH] = Settings::MinPreviousTimesWindowWidth;
		Settings::Save(SettingsPath);
	}
	if (ImGui::SliderFloat("Max Width##PreviousTimesMaxWidth", &Settings::MaxPreviousTimesWindowWidth, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_PREVIOUS_TIMES_KEY][MAX_PREVIOUS_TIMES_WINDOW_WIDTH] = Settings::MaxPreviousTimesWindowWidth;
		Settings::Save(SettingsPath);
	}
	if (ImGui::SliderFloat("Min Height##PreviousTimesMinHeight", &Settings::MinPreviousTimesWindowHeight, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_PREVIOUS_TIMES_KEY][MIN_PREVIOUS_TIMES_WINDOW_HEIGHT] = Settings::MinPreviousTimesWindowHeight;
		Settings::Save(SettingsPath);
	}
	if (ImGui::SliderFloat("Max Height##PreviousTimesMaxWidth", &Settings::MaxPreviousTimesWindowHeight, 100.0f, 1500.0f, "%.3f px")) {
		Settings::Settings[WINDOW_PREVIOUS_TIMES_KEY][MAX_PREVIOUS_TIMES_WINDOW_HEIGHT] = Settings::MaxPreviousTimesWindowHeight;
		Settings::Save(SettingsPath);
	}
}

void RenderCombatTimerSettings() {
	ImGui::Text("Display Elements");
	if (ImGui::Checkbox("Display Combat Status", &Settings::DisplayCombatStatus)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_COMBAT_STATUS] = Settings::DisplayCombatStatus;
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Display Final Time", &Settings::DisplayFinalTime)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_FINAL_TIME] = Settings::DisplayFinalTime;
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Display Minutes", &Settings::DisplayMinutes)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_MINUTES] = Settings::DisplayMinutes;
		if (!Settings::DisplayMinutes)
		{
			Settings::DisplayHours = false;
			ImGui::Checkbox("Display Hours", &Settings::DisplayHours);
			Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_HOURS] = Settings::DisplayHours;
		}
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Display Hours", &Settings::DisplayHours)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_HOURS] = Settings::DisplayHours;
		if (Settings::DisplayHours)
		{
			Settings::DisplayMinutes = true;
			ImGui::Checkbox("Display Minutes", &Settings::DisplayMinutes);
			Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_MINUTES] = Settings::DisplayMinutes;
		}
		else {
			Settings::DisplayMinutes = false;
			ImGui::Checkbox("Display Minutes", &Settings::DisplayMinutes);
			Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_MINUTES] = Settings::DisplayMinutes;
		}
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Display Start Timestamp", &Settings::DisplayStartTimestamp)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_START_TIMESTAMP] = Settings::DisplayStartTimestamp;
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Display End Timestamp", &Settings::DisplayEndTimestamp)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_END_TIMESTAMP] = Settings::DisplayEndTimestamp;
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Display Full Timestamp Date", &Settings::DisplayFullTimestampDate)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][DISPLAY_FULL_TIMESTAMP_DATE] = Settings::DisplayFullTimestampDate;
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Use Time Units", &Settings::UseTimeUnits)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][USE_TIME_UNITS] = Settings::UseTimeUnits;
		Settings::Save(SettingsPath);
	}
}

void RenderWindowSettings() {
	if (ImGui::Checkbox("Show Combat Timer Window", &Settings::ShowWindowCombatTimer)) {
		Settings::Settings[WINDOW_COMBAT_TIMER_KEY][SHOW_WINDOW_COMBAT_TIMER] = Settings::ShowWindowCombatTimer;
		Settings::Save(SettingsPath);
	}
	if (ImGui::Checkbox("Show Previous Times Window", &Settings::ShowWindowPreviousTimes)) {
		Settings::Settings[WINDOW_PREVIOUS_TIMES_KEY][SHOW_WINDOW_PREVIOUS_TIMES] = Settings::ShowWindowPreviousTimes;
		Settings::Save(SettingsPath);
	}
}

void ToggleShowWindowCombatTimer(const char* keybindIdentifier, bool isRelease) {
	if (isRelease) return;
	APIDefs->Log(ELogLevel_DEBUG, ADDON_NAME, std::format("Keybind {} was pressed.", keybindIdentifier).c_str());
	Settings::ShowWindowCombatTimer = !Settings::ShowWindowCombatTimer;
	Settings::Settings[WINDOW_COMBAT_TIMER_KEY][SHOW_WINDOW_COMBAT_TIMER] = Settings::ShowWindowCombatTimer;
	Settings::Save(SettingsPath);
}

void ToggleShowWindowPreviousTimes(const char* keybindIdentifier, bool isRelease) {
	if (isRelease) return;
	APIDefs->Log(ELogLevel_DEBUG, ADDON_NAME, std::format("Keybind {} was pressed.", keybindIdentifier).c_str());
	Settings::ShowWindowPreviousTimes = !Settings::ShowWindowPreviousTimes;
	Settings::Settings[WINDOW_COMBAT_TIMER_KEY][SHOW_WINDOW_PREVIOUS_TIMES] = Settings::ShowWindowPreviousTimes;
	Settings::Save(SettingsPath);
}