import numpy as np

import pyviewer
from pyviewer import p2e, e2p
from pyviewer import imgui_helper as imgui


__options__ = dict(option1=False)

def obj_accessors(obj, attr):
    """ setter and getter for any class """
    def setter(v): setattr(obj, attr, v)
    def getter(): return getattr(obj, attr)

    return setter, getter

def opt_accessors(key):
    """ setter and getter for global options """
    def setter(v): __options__[key] = v
    def getter(): return __options__[key]

    return setter, getter

class TestApp(object):
    def __init__(self, viewer):
        self.viewer = viewer
        self.menu = viewer.menu
        self.var1 = 1           # integer
        self.var2 = 2.0         # double
        self.var3 = 3.0         # double
        self.use_var3 = False   # boolean 
    
    def button_callback(self):
        # toogle
        self.viewer.data().show_faces = not self.viewer.data().show_faces

def test_menu(app):   
    imgui.begin_window("Test Window", 210, 100, 200, 300)
    if imgui.collapsing_header("Menu Options"):
        imgui.checkbox("show advanced", *opt_accessors("option1"))
        
        if __options__['option1']:
            imgui.push_item_width(90.0 * app.menu.menu_scaling())
            imgui.input_int("var1", *obj_accessors(app, "var1"))
            imgui.input_double("var2", *obj_accessors(app, "var2"))
            
            imgui.input_double("##optional", *obj_accessors(app, "var3"))
            imgui.same_line()
            imgui.checkbox("use var3", *obj_accessors(app, "use_var3"))
            imgui.pop_item_width()
            
        imgui.separator()
        if imgui.button("click me", imgui.ImVec2(-1,0)):
            app.button_callback()

    if imgui.collapsing_header("Viewer Options"):
        imgui.checkbox("show_vertid", *obj_accessors(app.viewer.data(), "show_vertid"))
        imgui.checkbox("show_faceid", *obj_accessors(app.viewer.data(), "show_faceid"))
    imgui.end()



def main(args=None):

    V = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]], dtype=np.float64)
    F = np.array([[0, 1, 2]], dtype=np.int32)

    viewer = pyviewer.PyViewer()
    viewer.data().set_mesh(p2e(V), p2e(F))
    menu = viewer.menu

    app = TestApp(viewer)
    def draw_custom_window(*args):
        test_menu(app)
        
    menu.callback_draw_custom_window = draw_custom_window

    viewer.launch()

if __name__ == "__main__":
    main()