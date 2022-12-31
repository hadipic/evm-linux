var lv = require('lvgl');
var image = require('image');
var evue = require('evue.js');


var page = {
    data: {
        result: "Hello EVM",
    },
    onShow: function() {
        this.result = 'Hello EVUE'
    }
}

page.$watcher = new evue.Watcher(page); 
page.$nodes = {}; 
page.$topNodes = {}; 
page.$getElementById = evue.getElementById;  
page.$onShow = evue.onShow;
page.$onHide = evue.onHide;

function render() {

var widget0 = lv.lv_obj_create(lv.lv_scr_act())
print(widget0)
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
page.$watcher.bind(text1, 'text', 'result', 'lv_label_')
page.$nodes['widget0'] = {"type":"div","id":"widget0","attributes":{"class":"container"}};
page.$nodes['widget0']['$obj'] = widget0;
page.$nodes['text1'] = {"type":"text","attributes":{"id":"text1","value":"Hello EVM"}};
page.$nodes['text1']['$obj'] = text1;
page.$topNodes['widget0'] = page.$nodes['widget0'];
}
page.$render = render;
page.$render();

page.$onShow();

module.exports = {
    'page': page
}

