cmake_minimum_required(VERSION 2.8.12)
project(pyviewer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pyviewer/)
### Compilation flags: adapt to your needs ###
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wall -Wextra -pipe -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

    if(NOT ${CMAKE_BUILD_TYPE} MATCHES Debug)
        message("RELEASE mode")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -flto -O3")
    else()
        message("DEBUG mode")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -O0 -g3 -g")
   endif()
endif()

# ---------------------------------------------------------------------------------
# include LIBIGL
# ---------------------------------------------------------------------------------
option(LIBIGL_USE_STATIC_LIBRARY "Use libigl as static library" OFF)
option(LIBIGL_WITH_ANTTWEAKBAR      "Use AntTweakBar"    OFF)
option(LIBIGL_WITH_CGAL             "Use CGAL"           OFF)
option(LIBIGL_WITH_COMISO           "Use CoMiso"         OFF)
option(LIBIGL_WITH_CORK             "Use Cork"           OFF)
option(LIBIGL_WITH_EMBREE           "Use Embree"         OFF)
option(LIBIGL_WITH_LIM              "Use LIM"            OFF)
option(LIBIGL_WITH_MATLAB           "Use Matlab"         OFF)
option(LIBIGL_WITH_MOSEK            "Use MOSEK"          OFF)
option(LIBIGL_WITH_NANOGUI          "Use Nanogui menu"   OFF)
option(LIBIGL_WITH_OPENGL           "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW      "Use GLFW"           ON)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use IMGUI"         ON)
option(LIBIGL_WITH_PNG              "Use PNG"            ON)
option(LIBIGL_WITH_PYTHON           "Use Python"         OFF)
option(LIBIGL_WITH_TETGEN           "Use Tetgen"         OFF)
option(LIBIGL_WITH_TRIANGLE         "Use Triangle"       OFF)
option(LIBIGL_WITH_VIEWER           "Use OpenGL viewer"  ON)
option(LIBIGL_WITH_XML              "Use XML"            OFF)

find_package(LIBIGL REQUIRED QUIET)
message("${LIBIGL_INCLUDE_DIR}")

set(PYVIEWER_SOURCES
    src/colormap.cpp
    src/colormap.h
    src/viewer.cpp
    src/viewer.h
    src/imgui_colorbar.cpp
    src/imgui_colorbar.h
    src/imgui_helper.cpp
    src/imgui_helper.h
    src/py_viewer.cpp
    src/py_imgui.cpp
    src/py_bindings.cpp
    src/py_bindings.h
)

add_subdirectory(external/pybind11)
pybind11_add_module(_pyviewer ${PYVIEWER_SOURCES})
target_include_directories(_pyviewer PUBLIC "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/py")
target_link_libraries(_pyviewer PUBLIC igl::core igl::opengl igl::opengl_glfw igl::png igl::opengl_glfw_imgui)

