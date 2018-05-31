#include "PyViewer.h"

namespace pyviewer{
   
    void PyViewer::launch(){
        plugins.push_back(&m_menu);
        igl::opengl::glfw::Viewer::launch();
    }
}