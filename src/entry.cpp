#include <Windows.h>
#include <chrono>

#include "submodules/nexus/Nexus.h"
#include "submodules/mumble/Mumble.h"
#include "submodules/imgui/imgui.h"
#include "shared.h"
#include "settings.h"
#include "version.h"
#include "timer.h"
#include "gui.h"

AddonDefinition AddonDef = {};

void AddonOptions() {
	ImGui::Separator();
	ImGui::Text(ADDON_NAME);
	RenderWindowSettings();
	RenderCombatTimerSettings();
	RenderWindowSizingSettings();
}
void AddonRender() {
	RenderWindowCombatTimer();
	RenderWindowPreviousTimes();
}
void AddonLoad(AddonAPI* addonApi) {
	APIDefs = addonApi;
	ImGui::SetCurrentContext((ImGuiContext*)APIDefs->ImguiContext); // cast to ImGuiContext*
	ImGui::SetAllocatorFunctions((void* (*)(size_t, void*))APIDefs->ImguiMalloc, (void(*)(void*, void*))APIDefs->ImguiFree); // on imgui 1.80+
	NexusLink = (NexusLinkData*)APIDefs->DataLink.Get("DL_NEXUS_LINK");
	MumbleLink = (Mumble::Data*)APIDefs->DataLink.Get("DL_MUMBLE_LINK");
	AddonPath = APIDefs->Paths.GetAddonDirectory("combat_timer");
	std::filesystem::create_directory(AddonPath);
	SettingsPath = APIDefs->Paths.GetAddonDirectory("combat_timer/settings.json");
	Settings::Load(SettingsPath);
	APIDefs->Renderer.Register(ERenderType_Render, AddonRender);
	APIDefs->Renderer.Register(ERenderType_OptionsRender, AddonOptions);
	APIDefs->Log(ELogLevel_DEBUG, ADDON_NAME, "<c=#00ff00>Combat Timer</c> was loaded.");
	APIDefs->InputBinds.RegisterWithString(KB_TOGGLE_SHOW_WINDOW_COMBAT_TIMER, ToggleShowWindowCombatTimer, "(null)");
	APIDefs->InputBinds.RegisterWithString(KB_TOGGLE_SHOW_WINDOW_PREVIOUS_TIMES, ToggleShowWindowPreviousTimes, "(null)");
}
void AddonUnload() {
	APIDefs->Renderer.Deregister(AddonRender);
	APIDefs->Renderer.Deregister(AddonOptions);
	APIDefs->Log(ELogLevel_DEBUG, ADDON_NAME, "<c=#ff0000>Combat Timer</c> was unloaded.");
}
extern "C" __declspec(dllexport) AddonDefinition* GetAddonDef() {
	AddonDef.Signature = 2712;
	AddonDef.APIVersion = NEXUS_API_VERSION;
	AddonDef.Name = ADDON_NAME;
	AddonDef.Version.Major = V_MAJOR;
	AddonDef.Version.Minor = V_MINOR;
	AddonDef.Version.Build = V_BUILD;
	AddonDef.Version.Revision = V_REVISION;
	AddonDef.Author = "Linka";
	AddonDef.Description = "Displays the time spent in combat.";
	AddonDef.Load = AddonLoad;
	AddonDef.Unload = AddonUnload;
	AddonDef.Flags = EAddonFlags_None;
	AddonDef.Provider = EUpdateProvider_GitHub;
	AddonDef.UpdateLink = "https://github.com/Linkaaaaa/GW2CombatTimer";
	return &AddonDef;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: hSelf = hModule; break;
	case DLL_PROCESS_DETACH: break;
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	}
	return TRUE;
}