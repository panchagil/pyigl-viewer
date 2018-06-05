
#include "bindings.h"

namespace py = pybind11;
PYBIND11_PLUGIN(_pyviewer)
{

    py::module m("_pyviewer");
    python_export_viewer(m);
    python_export_imgui(m);

#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif

    return m.ptr();
}