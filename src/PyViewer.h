#ifndef PY_VIEWER_H
#define PY_VIEWER_H

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/ViewerPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/MeshGL.h>
#include <igl/igl_inline.h>

namespace pyviewer{
    class PyViewer : public igl::opengl::glfw::Viewer {
    
    public:
        ///@brief launches the viewer with the menu plugin.
        void launch();

        ///@brief A hack to setup dirty flags (e.q to dirty|=flag)
        void dirty(int data_idx, igl::opengl::MeshGL::DirtyFlags flag);

    igl::opengl::glfw::imgui::ImGuiMenu m_menu;   
    };
}
#endif