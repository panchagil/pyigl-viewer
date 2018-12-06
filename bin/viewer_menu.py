import argparse

import numpy as np

import pyviewer
from bin.qt_kernel import in_process_kernel, internal_kernel
from pyviewer import p2e, e2p
from pyviewer import imgui_helper as imgui


def obj_accessors(obj, attr):
    """ setter and getter for any class """
    def setter(v): setattr(obj, attr, v)
    def getter(): return getattr(obj, attr)

    return setter, getter

class TestApp(object):
    def __init__(self):

        self.viewer = pyviewer.PyViewer()
        self.menu = self.viewer.menu
        self.menu.callback_draw_custom_window = self.test_menu
        # add some data
        V = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]], dtype=np.float64)
        F = np.array([[0, 1, 2]], dtype=np.int32)

        self.viewer.data().set_mesh(p2e(V), p2e(F))

        # dummy variables for the ui
        self.var1 = 1           # integer
        self.var2 = 2.0         # double
        self.var3 = 3.0         # double
        self.use_var3 = False   # boolean


    def button_callback(self):
        self.viewer.data().show_faces = not self.viewer.data().show_faces

    def stop_viewer(self):
        self.viewer.pause_rendering()

    def test_menu(self):
        imgui.begin_window("Test Window", 210, 100, 200, 300)
        if imgui.button("stop viewer", imgui.ImVec2(-1, 0)):
            self.stop_viewer()
        if imgui.collapsing_header("Menu Options"):
            imgui.push_item_width(90.0 * self.menu.menu_scaling())
            imgui.input_int("var1", *obj_accessors(self, "var1"))
            imgui.input_double("var2", *obj_accessors(self, "var2"))

            imgui.input_double("##optional", *obj_accessors(self, "var3"))
            imgui.same_line()
            imgui.checkbox("use var3", *obj_accessors(self, "use_var3"))
            imgui.pop_item_width()

            imgui.separator()
            if imgui.button("click me", imgui.ImVec2(-1,0)):
                self.button_callback()

        if imgui.collapsing_header("Viewer Options"):
            imgui.checkbox("show_vertid", *obj_accessors(self.viewer.data(), "show_vertid"))
            imgui.checkbox("show_faceid", *obj_accessors(self.viewer.data(), "show_faceid"))
        imgui.end()

    def launch(self):
        self.viewer.launch(True, False)

    def start(self):
        self.viewer.launch_stoppable(True, False)

def main(args=None):
    parser = argparse.ArgumentParser()
    parser.add_argument('--qtconsole', dest='qtconsole', action='store_true', default=False)
    parser.add_argument('--inprocess', dest='inprocess', action='store_true', default=False)
    args = parser.parse_args()

    app = TestApp()
        

    if args.qtconsole:
        if  args.inprocess:
            in_process_kernel(env=dict(app=app))
        else:
            internal_kernel(env=dict(app=app))
    else:
        app.launch()



if __name__ == "__main__":
    main()
