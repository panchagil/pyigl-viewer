#include "imgui_helper.h"

namespace pyviewer {
namespace imgui_helper {
    void BeginWindow(
        const char* name, const float x, const float y, const float w, const float h, const ImGuiWindowFlags flags)
    {
        ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(name, nullptr, flags);
    }

    bool InputDouble(const char* name, const std::function<void(const double&)>& setter, const std::function<double(void)>& getter,
        double step, double step_fast, const char* format, ImGuiInputTextFlags extra_flags)
    {

        double x = getter();
        if (ImGui::InputDouble(name, &x, step, step_fast, format, extra_flags)) {
            setter(x);
            return true;
        }
        return false;
    }

    bool InputInt(const char* name, const std::function<void(const int&)>& setter, const std::function<int(void)>& getter)
    {
        int x = getter();
        if (ImGui::InputInt(name, &x)) {
            setter(x);
            return true;
        }
        return false;
    }
    bool SliderInt(const char* name, const std::function<void(const int&)>& setter, const std::function<int(void)>& getter, int v_min, int v_max)
    {
        int x = getter();
        if (ImGui::SliderInt(name, &x, v_min, v_max)) {
            setter(x);
            return true;
        }
        return false;
    }
    bool DragFloat(
        const char* name, const std::function<void(const float&)>& setter, const std::function<float(void)>& getter,
        float v_speed, float v_min, float v_max, const char* format)
    {
        float x = getter();
        if (ImGui::DragFloat(name, &x, v_speed, v_min, v_max, format)) {
            setter(x);
            return true;
        }
        return false;
    }
    bool Checkbox(const char* name, const std::function<void(const bool&)>& setter, const std::function<bool(void)>& getter)
    {
        bool x = getter();
        if (ImGui::Checkbox(name, &x)) {
            setter(x);
            return true;
        }
        return false;
    }

    void PlotLines(const char* label, const std::vector<float>& values, int values_offset, float scale_min, float scale_max, ImVec2 graph_size)
    {
        return ImGui::PlotLines(label, values.data(), values.size(), values_offset, nullptr, scale_min, scale_max, graph_size);
    }

    bool Combo(const char* label, const std::function<void(const int&)>& setter, const std::function<int(void)>& getter, const char* items_separated_by_zeros, int popup_max_height_in_items)
    {
        int x = getter();
        if (ImGui::Combo(label, &x, items_separated_by_zeros, popup_max_height_in_items)) {
            setter(x);
            return true;
        }
        return false;
    }

    void EndWindow()
    {
        ImGui::End();
    }

    bool WantCaptureMouse()
    {
        return ImGui::GetIO().WantCaptureMouse;
    }

}
}
