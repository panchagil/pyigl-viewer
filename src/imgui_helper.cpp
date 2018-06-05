#include "imgui_helper.h"

#include "imgui_ext.h"

namespace pyviewer {
namespace imgui_helper {
    void BeginWindow(
        const char* name, const float x, const float y, const float w, const float h)
    {
        ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(
            name, nullptr,
            ImGuiWindowFlags_NoSavedSettings);
    }
    bool InputDouble(
        const char* name,
        const std::function<void(const double&)>& setter,
        const std::function<double(void)>& getter)
    {

        double x = getter();
        if (ImGui::InputDouble(name, &x, 1, 10, "%.3f")) {
            setter(x);
            return true;
        }
        return false;
    }

    bool InputInt(
        const char* name,
        const std::function<void(const int&)>& setter,
        const std::function<int(void)>& getter)
    {
        int x = getter();
        if (ImGui::InputInt(name, &x)) {
            setter(x);
            return true;
        }
        return false;
    }
    bool Checkbox(
        const char* name,
        const std::function<void(const bool&)>& setter,
        const std::function<bool(void)>& getter)
    {
        bool x = getter();
        if (ImGui::Checkbox(name, &x)) {
            setter(x);
            return true;
        }
        return false;
    }

    void EndWindow()
    {
        ImGui::End();
    }
}
}