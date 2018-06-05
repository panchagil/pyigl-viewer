#ifndef PY_VIEWER_BINDINGS_H
#define PY_VIEWER_BINDINGS_H

#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


void python_export_viewer(pybind11::module &m);
void python_export_imgui(pybind11::module &m);

#endif