#include "bindings.h"

#include <imgui/imgui.h>

#include "imgui_helper.h"

namespace py = pybind11;
void python_export_imgui(pybind11::module& m)
{
    py::module me = m.def_submodule("imgui_helper", "");

    py::class_<ImVec2>(me, "ImVec2")
        .def(py::init<float, float>());

    me
        // Windows
        .def("begin_window", &pyviewer::imgui_helper::BeginWindow)
        .def("end_window", &pyviewer::imgui_helper::EndWindow)
        .def("end", &ImGui::End)

        // Parameters stacks (current window)
        .def("push_item_width", &ImGui::PushItemWidth)
        .def("pop_item_width", &ImGui::PopItemWidth)

        // Cursor / Layout
        .def("separator", &ImGui::Separator)
        .def("same_line", &ImGui::SameLine, py::arg("pos_x") = 0.0f, py::arg("spacing_w") = -1.0f)

        // Widgets: Main
        .def("button", &ImGui::Button, py::arg("label"), py::arg("size") = ImVec2(0, 0))
        .def("checkbox", &pyviewer::imgui_helper::Checkbox)

        // Widgets: Input with Keyboard
        .def("input_double", &pyviewer::imgui_helper::InputDouble)
        .def("input_int", &pyviewer::imgui_helper::InputInt)

        // Widgets: Trees
        .def("collapsing_header", [](const char* label) {
            return ImGui::CollapsingHeader(label, ImGuiTreeNodeFlags_DefaultOpen);
        });

    
}