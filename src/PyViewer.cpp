#include "PyViewer.h"

namespace pyviewer {

void PyViewer::launch()
{
    plugins.push_back(&m_menu);
    igl::opengl::glfw::Viewer::launch();
}

void PyViewer::dirty(int data_idx, igl::opengl::MeshGL::DirtyFlags flag){
    data_list[data_idx].dirty |= flag;
}
}