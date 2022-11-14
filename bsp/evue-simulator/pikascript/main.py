import PikaStdLib as std
import pika_lvgl as lv
from PikaStdLib import MemChecker

mem = MemChecker()
mem.now()

class DataBinding:
    _inner_ = []
    def __init__(self, data):
        _bindings_ = {}
        self._inner_.append(_bindings_)
        self._inner_.append(data)

    def __getattr__(self, name):
        data = self._inner_[1]
        return data[name]

    def __setattr__(self, name, value):
        data = self._inner_[1]
        data[name] = value
        _bindings_ = self._inner_[0]
        if name in _bindings_:
            bindings = _bindings_[name]
            for binding in bindings:
                element = binding['element']
                attr = binding['attr']
                _name = attr.replace("-", "_")
                funcName = "set_%s" % _name
                if attr is 'text':
                    value = str(value)
                if hasattr(element, funcName):
                    element.func = getattr(element, funcName)
                    element.func(value)
                else:
                    if hasattr(element, "obj") and element.obj:
                        setattr(element.obj, _name, value)

    def set_binding_value(self, element, attr, key):
        _bindings_ = self._inner_[0]
        if key not in _bindings_:
            _bindings_[key] = []

        _bindings_[key].append({
            "element": element,
            "attr": attr
        })


color = {
    'red': lv.palette_main(lv.PALETTE.RED),
    'pink': lv.palette_main(lv.PALETTE.PINK),
    'purple': lv.palette_main(lv.PALETTE.PURPLE),
    'blue': lv.palette_main(lv.PALETTE.BLUE),
    'cyan': lv.palette_main(lv.PALETTE.CYAN),
    'green': lv.palette_main(lv.PALETTE.GREEN),
    'brown': lv.palette_main(lv.PALETTE.BROWN),
    'grey': lv.palette_main(lv.PALETTE.GREY),
    'lime': lv.palette_main(lv.PALETTE.LIME),
    'yellow': lv.palette_main(lv.PALETTE.YELLOW),
    'orange': lv.palette_main(lv.PALETTE.ORANGE),
    'black': lv.lv_color_hex(0),
    'white': lv.lv_color_hex(0xFFFFFF),
    'amber': lv.palette_main(lv.PALETTE.AMBER)
}

def get_color(v):
    if type(v) == type(1):
        return lv.lv_color_hex(v)
    elif type(v) == type(''):
        if v in color:
            return color[v]
        return color['white']

class Element:
    def __init__(self, obj):
        self.obj = obj
        self.parent = None
        self.onclick = None
        self.__objId = None
        self.obj.add_event_cb(self.__onpressed, lv.EVENT.PRESSED, 0)
        self.__objStyle = lv.style_t()
        self.__objStyle.init()
        self.obj.add_style(self.__objStyle, 0)

    def __onpressed(self, e):
        print(e)

    def render(self):
        pass

    def clear(self):
        pass

    def bind(self, attribute, key):
        pass

    def id(self, v=None):
        pass

    def top(self, v=None):
        if v is None:
            self.obj.get_y()
        else:
            self.obj.set_y(v)

    def left(self, v=None):
        if v is None:
            self.obj.get_x()
        else:
            self.obj.set_x(v)

    def width(self, v=None):
        if v is None:
            self.obj.get_width()
        else:
            self.obj.set_width(v)

    def height(self, v=None):
        if v is None:
            self.obj.get_height()
        else:
            self.obj.set_height(v)

    def style(self, v):
        if 'background-color' in v:
            self.__objStyle.set_bg_color(get_color(v))
        if 'border-width' in v:
            self.__objStyle.set_border_width(v)
        if 'border-color' in v:
            self.__objStyle.set_border_color(v)

class TextElement(Element):
    def __init__(self, element=None):
        if element is None:
            super().__init__(lv.label(lv.scr_act()))
        else:
            super().__init__(lv.label(element.obj))
        
        self.__text = ''

    def value(self, v=None):
        if v is None:
            return self.__text
        else:
            self.obj.set_text(v)

class DivElement(Element):
    def __init__(self, element=None):
        if element is None:
            super().__init__(lv.obj(lv.scr_act()))
        else:
            super().__init__(lv.obj(element.obj))

class ButtonElement(Element):
    def __init__(self, element=None):
        if element is None:
            super().__init__(lv.btn(lv.scr_act()))
        else:
            super().__init__(lv.btn(element.obj))

class ComboboxElement(Element):
    def __init__(self, element=None):
        if element is None:
            super().__init__(lv.dropdown(lv.scr_act()))
        else:
            super().__init__(lv.dropdown(element.obj))

class CheckboxElement(Element):
    def __init__(self, element=None):
        if element is None:
            super().__init__(lv.checkbox(lv.scr_act()))
        else:
            super().__init__(lv.checkbox(element.obj))
            

data = {
    'result': 'Hello EVUE'
}

data = DataBinding(data)

widget0 = DivElement(element=None)
widget0.id('widget0')
widget0.width(240)
widget0.height(240)
widget0.style('')
widget1 = TextElement(element=widget0)
widget1.id('widget1')
widget1.value(v='Hello EVUE')
widget1.render()
widget0.render()
