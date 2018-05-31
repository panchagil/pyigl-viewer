
#include <iostream>

// #include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/ViewerPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

#include <PyViewer.h>
#include <FormHelper.h>

namespace py = pybind11;
PYBIND11_PLUGIN(_pyviewer)
{
    
    py::module m("_pyviewer");    
    py::module::import("pyigl");

    m.def("test", [](const double a){
        std::cout << a << std::endl;
        return a;
    });

    m.def("testb", [](const std::function<double(void)> &getter){
        double a = getter();
        float b = static_cast<float>(a);
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        return std::make_tuple(a, b);
    });

    m.def("testc", [](const double a, const std::function<void(const double &)> &setter){
        setter(a);
        std::cout << a << std::endl;
        return a;
    });

    py::class_<pyviewer::FormHelper>(m,"FormHelper")
        .def(py::init<igl::opengl::glfw::imgui::ImGuiMenu *>())
        .def("begin_window",&pyviewer::FormHelper::BeginWindow)
        .def("end_window",&pyviewer::FormHelper::EndWindow)
        .def("input_float",&pyviewer::FormHelper::InputFloat)
        ;

    py::class_<pyviewer::PyViewer, igl::opengl::glfw::Viewer>(m, "PyViewer")
        .def(py::init<>())
        .def_readwrite("menu", &pyviewer::PyViewer::m_menu)
        .def("launch", &pyviewer::PyViewer::launch);

    py::class_<igl::opengl::glfw::ViewerPlugin>(m, "ViewerPlugin")
        .def(py::init<>());

    py::class_<igl::opengl::glfw::imgui::ImGuiMenu, igl::opengl::glfw::ViewerPlugin>(m, "ImGuiMenu")
        .def(py::init<>())
        .def("init", &igl::opengl::glfw::imgui::ImGuiMenu::init)
        .def("draw_viewer_menu", &igl::opengl::glfw::imgui::ImGuiMenu::draw_viewer_menu)
        .def_readwrite("callback_draw_viewer_menu", &igl::opengl::glfw::imgui::ImGuiMenu::callback_draw_viewer_menu)
        .def_readwrite("callback_draw_custom_window", &igl::opengl::glfw::imgui::ImGuiMenu::callback_draw_custom_window);

#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif

    return m.ptr();
}