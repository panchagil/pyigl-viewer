#include "bindings.h"

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/ViewerPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

#include <PyViewer.h>

namespace py = pybind11;

void python_export_viewer(pybind11::module &m){
    py::module::import("pyigl");

    py::class_<pyviewer::PyViewer, igl::opengl::glfw::Viewer>(m, "PyViewer")
        .def(py::init<>())
        .def_readwrite("menu", &pyviewer::PyViewer::m_menu)
        .def("launch", &pyviewer::PyViewer::launch)
        .def("append_mesh", &pyviewer::PyViewer::append_mesh)
        .def("dirty", &pyviewer::PyViewer::dirty)
        .def_readwrite("data_list", &pyviewer::PyViewer::data_list);

    py::class_<igl::opengl::glfw::ViewerPlugin>(m, "ViewerPlugin")
        .def(py::init<>());

    py::class_<igl::opengl::glfw::imgui::ImGuiMenu, igl::opengl::glfw::ViewerPlugin>(m, "ImGuiMenu")
        .def(py::init<>())
        .def("init", &igl::opengl::glfw::imgui::ImGuiMenu::init)
        .def("menu_scaling", &igl::opengl::glfw::imgui::ImGuiMenu::menu_scaling)
        .def("draw_viewer_menu", &igl::opengl::glfw::imgui::ImGuiMenu::draw_viewer_menu)
        .def_readwrite("callback_draw_viewer_menu", &igl::opengl::glfw::imgui::ImGuiMenu::callback_draw_viewer_menu)
        .def_readwrite("callback_draw_custom_window", &igl::opengl::glfw::imgui::ImGuiMenu::callback_draw_custom_window);

}