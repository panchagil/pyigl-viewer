import numpy as np

import pyviewer
from pyviewer import p2e, e2p


class App(object):
    pass


def main(args=None):

    V = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]], dtype=np.float64)
    F = np.array([[0, 1, 2]], dtype=np.int32)

    viewer = pyviewer.PyViewer()
    viewer.data().set_mesh(p2e(V), p2e(F))
    menu = viewer.menu
    helper = pyviewer.FormHelper(menu)

    app = App()
    app.float1 = 1.0

    def getter():
        return app.float1

    def setter(v):
        app.float1 = v

    def my_window(**args):
        helper.begin_window("Test Window", 210, 100, 100, 100)
        if(helper.input_float("float1##test", setter, getter)):
            print(app.float1)
        helper.end_window()

    menu.callback_draw_custom_window = my_window

    viewer.launch()

if __name__ == "__main__":
    main()