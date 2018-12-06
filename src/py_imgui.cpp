#include "py_bindings.h"

#include <imgui/imgui.h>

#include <imgui_colorbar.h>
#include <imgui_helper.h>

namespace py = pybind11;
void python_export_imgui(pybind11::module& m)
{
    py::module me = m.def_submodule("imgui_helper", "");

    py::class_<ImVec2>(me, "ImVec2")
        .def(py::init<float, float>());

    py::class_<ImVec4>(me, "ImVec4")
        .def(py::init<float, float, float, float>());

    me
        // Windows
        .def("begin_window", &pyviewer::imgui_helper::BeginWindow,
             py::arg("name"), py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"), py::arg("flags") = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize)
        .def("end_window", &pyviewer::imgui_helper::EndWindow)
        .def("end", &ImGui::End)

        // Parameters stacks (shared)
        .def("push_style_color", [](const int idx, const ImVec4& col) {
            return ImGui::PushStyleColor((ImGuiCol)idx, col);
        })
        .def("pop_style_color", &ImGui::PopStyleColor)

        // Parameters stacks (current window)
        .def("push_item_width", &ImGui::PushItemWidth)
        .def("pop_item_width", &ImGui::PopItemWidth)

        // Cursor / Layout
        .def("separator", &ImGui::Separator)
        .def("same_line", &ImGui::SameLine, //
            py::arg("pos_x") = 0.0f, py::arg("spacing_w") = -1.0f)

        // Widgets: Text
        .def("text", [](const std::string& text) {
            return ImGui::Text("%s", text.c_str());
        })
        // Widgets: Main
        .def("button", &ImGui::Button, //
            py::arg("label"), py::arg("size") = ImVec2(0, 0))
        .def("checkbox", &pyviewer::imgui_helper::Checkbox)
        .def("plot_lines", &pyviewer::imgui_helper::PlotLines, //
            py::arg("label"), py::arg("values"), py::arg("values_offset") = 0, py::arg("scale_min") = FLT_MAX, py::arg("scale_max") = FLT_MAX, py::arg("graph_size") = ImVec2(0, 0))

        // Widgets: Combo
        .def("combo", &pyviewer::imgui_helper::Combo, //
            py::arg("label"), py::arg("setter"), py::arg("getter"), py::arg("items_separated_by_zeros"), py::arg("popup_max_height_in_items") = -1)

        // Widgets: Input with Keyboard
        .def("input_double", &pyviewer::imgui_helper::InputDouble, //
            py::arg("name"), py::arg("setter"), py::arg("getter"), py::arg("step") = 0.0, py::arg("step_fast") = 0.0, py::arg("format") = "%.6f", py::arg("extra_flags") = 0)
        .def("input_int", &pyviewer::imgui_helper::InputInt)

        // Widgets: Sliders (tip: ctrl+click on a slider to input with keyboard. manually input values aren't clamped, can go off-bounds)
        .def("slider_int", &pyviewer::imgui_helper::SliderInt)

        // Widgets: Drags (tip: ctrl+click on a drag box to input with keyboard. manually input values aren't clamped, can go off-bounds)
        .def("drag_float", &pyviewer::imgui_helper::DragFloat, //
            py::arg("name"), py::arg("setter"), py::arg("getter"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0.0, py::arg("v_max") = 1.0, py::arg("format") = "%.6f")

        // Widgets: Trees
        .def("collapsing_header", [](const char* label, bool p_open, bool default_open) {
            auto flags = default_open ? ImGuiTreeNodeFlags_DefaultOpen : !ImGuiTreeNodeFlags_DefaultOpen;
            return ImGui::CollapsingHeader(label, &p_open, flags);
        },
            py::arg("label"), py::arg("p_open") = true, py::arg("default_open") = true);

    py::class_<pyviewer::ColorbarPlugin>(me, "ColorbarPlugin")
        .def(py::init<>())
        .def("init_colormaps", &pyviewer::ColorbarPlugin::init_colormaps)
        .def("draw_colormap_combo", &pyviewer::ColorbarPlugin::draw_colormap_combo)
        .def("draw_colorbar", &pyviewer::ColorbarPlugin::draw_colorbar);
}
