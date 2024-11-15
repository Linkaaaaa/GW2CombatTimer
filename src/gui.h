#ifndef GUI_H
#define GUI_H

#include "submodules/imgui/imgui.h"

void RenderWindowCombatTimer();
void RenderWindowPreviousTimes();
void RenderWindowSettings();
void RenderCombatTimerSettings();
void RenderWindowSizingSettings();

void ToggleShowWindowCombatTimer(const char* keybindIdentifier, bool isRelease);
void ToggleShowWindowPreviousTimes(const char* keybindIdentifier, bool isRelease);

namespace gui {
	const ImGuiWindowFlags windowFlags = (
		ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoNav
		| ImGuiWindowFlags_NoNavFocus
		);
	const ImGuiTableFlags tableFlags = (
		ImGuiTableFlags_Resizable
		| ImGuiTableFlags_Reorderable
		| ImGuiTableFlags_Hideable
		| ImGuiTableFlags_Borders
		| ImGuiTableFlags_ContextMenuInBody
		| ImGuiTableFlags_RowBg
		);
	const ImGuiTableColumnFlags columnFlags = (
		ImGuiTableColumnFlags_WidthStretch
		);
}

#endif