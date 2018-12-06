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
        ///@brief launches the viewer with the menu plugin
        /// and starts the rendering loop
        void launch(const bool resizable = true, const bool fullscreen = false);
        void launch_stoppable(const bool resizable = true, const bool fullscreen = false);
        bool launch_stoppable_rendering();
        void pause_rendering();
        void resume_rendering();

        ///@brief A hack to setup dirty flags (e.q to dirty|=flag)
        void dirty(unsigned long data_idx, igl::opengl::MeshGL::DirtyFlags flag);

        ///@brief OpenGL context move
        void move(int x,int y);

        igl::opengl::glfw::imgui::ImGuiMenu m_menu;
        bool stopped = false;
        bool initialized = false;


    };
}
#endif
