#include "viewer.h"

namespace pyviewer {

void PyViewer::launch(const bool resizable, const bool fullscreen)
{
    plugins.push_back(&m_menu);
    igl::opengl::glfw::Viewer::launch(resizable, fullscreen);
}

void PyViewer::launch_stoppable(const bool resizable, const bool fullscreen)
{
    if (!initialized) {
        plugins.push_back(&m_menu);
        igl::opengl::glfw::Viewer::launch_init(resizable, fullscreen);
        initialized = true;
    }
    stopped = false;
    launch_stoppable_rendering();
}

void PyViewer::pause_rendering()
{
    stopped = true;
}

void PyViewer::resume_rendering()
{
    stopped = false;
    launch_stoppable_rendering();
}

bool PyViewer::launch_stoppable_rendering()
{
    bool done = false;
    while (!done && !stopped) {
        done = !igl::opengl::glfw::Viewer::launch_rendering(false);
    }
    if (done) {
        igl::opengl::glfw::Viewer::launch_shut();
    }
    return EXIT_SUCCESS;
}

void PyViewer::dirty(unsigned long data_idx, igl::opengl::MeshGL::DirtyFlags flag)
{
    data_list[data_idx].dirty |= flag;
}

void PyViewer::set_flat_face_colors(const unsigned long data_idx, const Eigen::MatrixXd& colors)
{
    data_list[data_idx].set_face_based(true);
    data_list[data_idx].set_colors(colors);
    for (unsigned i = 0; i < colors.rows(); ++i) {
        data_list[data_idx].F_material_diffuse.row(i) << colors.row(i), 1;
        data_list[data_idx].F_material_ambient.row(i) << 0.1 * colors.row(i), 1;
        data_list[data_idx].F_material_specular.row(i) << 0.1 * colors.row(i), 1;
    }
    data_list[data_idx].dirty |= igl::opengl::MeshGL::DIRTY_DIFFUSE;
}
void PyViewer::move(int x, int y)
{
    if (window) {
        glfwSetWindowPos(window, int(x / highdpi), int(y / highdpi));
    }
}

}
