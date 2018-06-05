#ifndef PY_VIEWER_IMGUI_HELPER_H
#define PY_VIEWER_IMGUI_HELPER_H

#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

namespace pyviewer {
namespace imgui_helper {

    // Windows
    void BeginWindow(
        const char* name, const float x, const float y, const float w, const float h);
    void EndWindow();

    // Widgets: Main
    bool Checkbox(
        const char* name,
        const std::function<void(const bool&)>& setter,
        const std::function<bool(void)>& getter);

    // Widgets: Input with Keyboard
    bool InputDouble(
        const char* name,
        const std::function<void(const double&)>& setter,
        const std::function<double(void)>& getter);
    bool InputInt(
        const char* name,
        const std::function<void(const int&)>& setter,
        const std::function<int(void)>& getter);

    
}
}
#endif