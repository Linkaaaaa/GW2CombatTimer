#include <filesystem>

#include "submodules/nexus/Nexus.h"
#include "submodules/mumble/Mumble.h"

const char* ADDON_NAME = "Combat Timer";

std::filesystem::path AddonPath;
std::filesystem::path SettingsPath;

HMODULE hSelf = nullptr;
AddonAPI* APIDefs = nullptr;
NexusLinkData* NexusLink = nullptr;
Mumble::Data* MumbleLink = nullptr;

const char* KB_TOGGLE_SHOW_WINDOW_COMBAT_TIMER = "KB Toggle: Show Window Combat Timer";
const char* KB_TOGGLE_SHOW_WINDOW_PREVIOUS_TIMES = "KB Toggle: Show Window Previous Times";
