#ifndef SHARED_H
#define SHARED_H

#include <filesystem>

#include "submodules/mumble/Mumble.h"
#include "submodules/nexus/Nexus.h"

extern const char* ADDON_NAME;

extern std::filesystem::path AddonPath;
extern std::filesystem::path SettingsPath;

extern AddonAPI* APIDefs;
extern NexusLinkData* NexusLink;
extern HMODULE hSelf;
extern Mumble::Data* MumbleLink;

extern const char* KB_TOGGLE_SHOW_WINDOW_COMBAT_TIMER;
extern const char* KB_TOGGLE_SHOW_WINDOW_PREVIOUS_TIMES;

#endif