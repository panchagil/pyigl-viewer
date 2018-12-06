#ifndef COLORMAP_H
#define COLORMAP_H

// Original code by Jeremie Dumas @jdumas

#include <igl/colormap.h>
#include <igl/opengl/gl.h>
#include <Eigen/Dense>

namespace pyviewer{

void colormap(const igl::ColorMapType cm, Eigen::MatrixXd &rgb);

void texture_from_colormap(const Eigen::MatrixXd &rgb, GLuint & id);

}

#endif
