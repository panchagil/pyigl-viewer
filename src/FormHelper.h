#ifndef PY_VIEWER_FORM_HELPER_H
#define PY_VIEWER_FORM_HELPER_H

#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

namespace pyviewer {
class FormHelper {
public:
    FormHelper(igl::opengl::glfw::imgui::ImGuiMenu* menu);
    void BeginWindow(
        const char *name, const float x, const float y, const float w, const float h);
    void EndWindow();
    bool InputFloat(
        const char *name, 
        const std::function<void(const double &)> &setter,
        const std::function<double(void)> &getter);
    igl::opengl::glfw::imgui::ImGuiMenu* m_menu;
};
}
#endif