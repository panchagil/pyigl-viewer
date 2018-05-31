#include "FormHelper.h"

#include "imgui_ext.h"

namespace pyviewer {

FormHelper::FormHelper(igl::opengl::glfw::imgui::ImGuiMenu* menu)
    : m_menu(menu)
{
}

void FormHelper::BeginWindow(
    const char *name, const float x, const float y, const float w, const float h)
{
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiSetCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(
        name, nullptr,
        ImGuiWindowFlags_NoSavedSettings);
}
bool FormHelper::InputFloat(
    const char *name, 
    const std::function<void(const double &)> &setter,
    const std::function<double(void)> &getter){
    
    double x = getter();
    if(ImGui::InputDouble(name, &x, 1, 10, "%.3f")){
        setter(x);
        return true;
    }
    return false;
}

void FormHelper::EndWindow(){
    ImGui::End();
}
}