#include "py_bindings.h"

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/ViewerPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

#include <igl/colormap.h>

#include <viewer.h>

namespace py = pybind11;

void python_export_viewer(pybind11::module &m){
    py::module::import("pyigl");

    py::class_<pyviewer::PyViewer, igl::opengl::glfw::Viewer>(m, "PyViewer")
        .def(py::init<>())
        .def_readwrite("menu", &pyviewer::PyViewer::m_menu)
        .def("launch", &pyviewer::PyViewer::launch)
        .def("launch_stoppable", &pyviewer::PyViewer::launch_stoppable)
        .def("pause_rendering", &pyviewer::PyViewer::pause_rendering)
        .def("resume_rendering", &pyviewer::PyViewer::resume_rendering)
        .def("append_mesh", &pyviewer::PyViewer::append_mesh)
        .def("dirty", &pyviewer::PyViewer::dirty)
        .def("set_flat_face_colors", &pyviewer::PyViewer::set_flat_face_colors)
        .def("move", &pyviewer::PyViewer::move)
        .def_readwrite("data_list", &pyviewer::PyViewer::data_list);

    py::class_<igl::opengl::glfw::ViewerPlugin>(m, "ViewerPlugin")
        .def(py::init<>());

    py::class_<igl::opengl::glfw::imgui::ImGuiMenu, igl::opengl::glfw::ViewerPlugin>(m, "ImGuiMenu")
        .def(py::init<>())
        .def("init", &igl::opengl::glfw::imgui::ImGuiMenu::init)
        .def("menu_scaling", &igl::opengl::glfw::imgui::ImGuiMenu::menu_scaling)
        .def("draw_viewer_menu", &igl::opengl::glfw::imgui::ImGuiMenu::draw_viewer_menu)
        .def_readwrite("callback_draw_viewer_window", &igl::opengl::glfw::imgui::ImGuiMenu::callback_draw_viewer_window) 
        .def_readwrite("callback_draw_viewer_menu", &igl::opengl::glfw::imgui::ImGuiMenu::callback_draw_viewer_menu)
        .def_readwrite("callback_draw_custom_window", &igl::opengl::glfw::imgui::ImGuiMenu::callback_draw_custom_window);

    py::enum_<igl::ColorMapType>(m, "ColorMapType")
        .value("INFERNO", igl::ColorMapType::COLOR_MAP_TYPE_INFERNO)
        .value("JET", igl::ColorMapType::COLOR_MAP_TYPE_JET)
        .value("MAGMA", igl::ColorMapType::COLOR_MAP_TYPE_MAGMA)
        .value("PARULA", igl::ColorMapType::COLOR_MAP_TYPE_PARULA)
        .value("PLASMA", igl::ColorMapType::COLOR_MAP_TYPE_PLASMA)
        .value("VIRIDIS", igl::ColorMapType::COLOR_MAP_TYPE_VIRIDIS)
        .export_values();
}
