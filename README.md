# pyigl-viewer
python wrapper for igl viewer with ImGui integration


## Installation
This wrapper extends your current installation of pyigl
- make sure to install pyigl before installing this extension
- add `pybind11` under the folder `external/`. !IMPORTANT it needs to be the same pybind11 that you use for libigl. 

Next, to install our extension use the provided `setup.py` file. This will take care of calling cmake, make, and installing the .so library in the correct path.

You can use one of the following commands (standard python setup)
1. `python setup.py install`: this will copy the library to your python site-packages
2. `python setup.py develop`: this will create a symbolic link to the site-packages.
2. `python setup.py build --debug develop`: this will compile the library with the DEBUG setup.

Installing in development mode allows you to modify the python files and see the changes without having to re-install.
Changes to C++ files need to be compiled again.

## Usage
I've added a script under build with that uses the functions currently wrapped. It also shows how it can be used to modify libigl viewer variables.
```
python bin/viewer_menu.py
```
Since python doesn't handle int or doble pointers, I've used the same trick that NanoGUI used on its wrappers: setter and getter functions.

```python
imgui.input_int("var1", *obj_accessors(app, "var1"))
```
[![screenshot tool](https://github.com/panchagil/pyigl-viewer/wiki/images/viewer_menu.png)](https://github.com/panchagil/pyigl-viewer/wiki/images/viewer_menu.png)

## Source Code
I've only wrapped a few functions of ImGui for now. The structure to wrap more is simple, so feel free to add yours and send a pull request.

- `py/imgui.cpp` containts the python wrappers. Some ImGui functions can be wrapped direcly with `.def("function", &ImGUI::function)`. More complex wrappers, like the ones that work with int pointers, are in `src/imgui_helper.cpp`.
- `py/pyviewer.cpp` contains wrappers for some functions of libigl Viewer that are not exposed in pyigl. This can eventually be moved to pyigl but I keep them here to speedup development. (The compiling time of pyigl is to large, this wrappers are ligther an compile faster)
- `src/imgui_ext.cpp` containts new ImGui widgets. At this time, it only includes InputDouble copied from ImGui v1.62 which is still not integrated to libigl.

