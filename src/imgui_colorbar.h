#ifndef COLORBAR_H
#define COLORBAR_H

// Original code by Jeremie Dumas @jdumas

#include "colormap.h"
#include <array>

namespace pyviewer {

class ColorbarPlugin {
public:
    void init_colormaps();

    int draw_colormap_combo() const;

    void draw_colorbar(
            const igl::ColorMapType cm,
            const double xmin, double xmax,
            const std::string label_min="", const std::string label_max="") const;

protected:
    std::array<GLuint, igl::NUM_COLOR_MAP_TYPES> colormaps_;

    igl::ColorMapType colormap_type_ = igl::COLOR_MAP_TYPE_VIRIDIS;
};

}
#endif
