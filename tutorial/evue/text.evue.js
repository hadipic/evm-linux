var lv = require('lvgl');
var image = require('image');



var nodes = {}
var _bindings_ = {}
function dataBinding(data) {
    Object.keys(data).forEach(function(key){
        var value = data[key];
        Object.defineProperty(data, key,{
            enumerable:true,
            configurable:true,
            get:function() {
                return value;
            },
            set:function(v) {
                if (value === v) {
                    return
                }
                value = v;
                var elements = _bindings_[key];
                if( elements != undefined ) {
                    for(var i in elements){
                        var binding = elements[i];
                        var func = lv[binding.prefix + 'set_' + binding.attr];
                        func(binding.element, v);
                    }
                    
                }
            }
        })
    })
}

function set_binding_value(element, attr, key, prefix) {
    if(_bindings_[key] == undefined) {
        _bindings_[key] = []
    }
       
    _bindings_[key].push({
        "element": element,
        "prefix": prefix,
        "attr": attr
    })
}

var page = {
    data: {
        result: "Hello EVM",
    },
    onShow: function() {
        data.result = 'Hello EVUE'
    }
}


var data = page.data;

dataBinding(data);

function getElementById(id) {
    return nodes[id];
}    

var widget0 = lv.lv_obj_create(lv.lv_scr_act())
var style = lv.lv_style_create()
lv.lv_style_init(style)
lv.lv_obj_set_x(widget0,50)
lv.lv_obj_set_y(widget0,50)
lv.lv_obj_set_width(widget0, 240)
lv.lv_obj_set_height(widget0, 240)
lv.lv_obj_set_flex_flow(widget0, lv.LV_FLEX_FLOW_ROW_WRAP)
lv.lv_obj_add_style(widget0, style, 0)
var text1 = lv.lv_label_create(widget0)
var style = lv.lv_style_create()
lv.lv_style_init(style)
lv.lv_label_set_text(text1, 'Hello EVM')
lv.lv_obj_add_style(text1, style, 0)
set_binding_value(text1, 'text', 'result', 'lv_label_')
nodes['widget0'] = {"type":"div","id":"widget0","attributes":{"class":"container"}};
nodes['widget0']['obj'] = widget0;
nodes['text1'] = {"type":"text","attributes":{"id":"text1","value":"Hello EVM"}};
nodes['text1']['obj'] = text1;
page.onShow();

