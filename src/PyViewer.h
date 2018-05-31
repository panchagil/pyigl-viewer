#ifndef PY_VIEWER_H
#define PY_VIEWER_H

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/ViewerPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

namespace pyviewer{
    class PyViewer : public igl::opengl::glfw::Viewer {
    
    public:
        void launch();

    igl::opengl::glfw::imgui::ImGuiMenu m_menu;   
    };
}
#endif