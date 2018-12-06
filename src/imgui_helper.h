#ifndef PY_VIEWER_IMGUI_HELPER_H
#define PY_VIEWER_IMGUI_HELPER_H

#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

namespace pyviewer {
namespace imgui_helper {

    // Windows
    void BeginWindow(const char* name, const float x, const float y, const float w, const float h, const
                     ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize);
    void EndWindow();

    // Widgets: Main
    bool Checkbox(const char* name, const std::function<void(const bool&)>& setter, const std::function<bool(void)>& getter);
    void PlotLines(const char* label, const std::vector<float>& values, int values_offset = 0,
                   float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));

    // Widgets: Combo
    bool Combo(const char* label, const std::function<void(const int&)>& setter, const std::function<int(void)>& getter, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);

    // Widgets: Input with Keyboard
    bool InputDouble(const char* name, const std::function<void(const double&)>& setter, const std::function<double(void)>& getter,
        double step = 0.0f, double step_fast = 0.0f, const char* format = "%.6f", ImGuiInputTextFlags extra_flags = 0);
    bool InputInt(const char* name, const std::function<void(const int&)>& setter, const std::function<int(void)>& getter);

    // Widgets: Sliders (tip: ctrl+click on a slider to input with keyboard. manually input values aren't clamped, can go off-bounds)
    bool SliderInt(const char* name, const std::function<void(const int&)>& setter, const std::function<int(void)>& getter, int v_min, int v_max);

    bool DragFloat(
        const char* name, const std::function<void(const float&)>& setter, const std::function<float(void)>& getter,
        float v_speed=1.0f, float v_min=0.0f, float v_max=0.0f, const char* format="%.3f");

}
}
#endif
