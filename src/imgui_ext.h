#ifndef IMGUI_EXT_H
#define IMGUI_EXT_H

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGui {
IMGUI_API bool InputScalar(const char* label, void* data_ptr, const void* step = NULL, const void* step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags extra_flags = 0);

IMGUI_API bool InputDouble(const char* label, double* v, double step = 0.0f, double step_fast = 0.0f, const char* format = "%.6f", ImGuiInputTextFlags extra_flags = 0);
}
#endif