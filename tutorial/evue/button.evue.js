var lv = require('lvgl');
var image = require('image');
var evue = require('evue.js');
var lv = require('@native.lvgl');

var page = {
    data: {

    },

    onclicked: function(obj, code) {
        print('hello EVUE')
    }
}

//page.$watcher = new evue.Watcher(page); 
//page.$nodes = {}; 
//page.$getElementById = evue.getElementById;  

 
var widget0 = lv.lv_obj_create(lv.lv_scr_act())
//var style = lv.lv_style_create()
//lv.lv_style_init(style)
lv.lv_obj_set_x(widget0,50)
lv.lv_obj_set_y(widget0,50)
lv.lv_obj_set_width(widget0, 240)
lv.lv_obj_set_height(widget0, 240)
lv.lv_obj_add_style(widget0, style, 0)
var widget1 = lv.lv_btn_create(widget0)
//var style = lv.lv_style_create()
//lv.lv_style_init(style)
//lv.lv_obj_add_style(widget1, style, 0)
page.$nodes['widget0'] = {"type":"div","id":"widget0","attributes":{"class":"container"}};
page.$nodes['widget0']['obj'] = widget0;
page.$nodes['widget1'] = {"type":"button","id":"widget1","attributes":{"onclick":"onclicked","value":"click me"}};
page.$nodes['widget1']['obj'] = widget1;
lv.lv_obj_add_event_cb(widget1, page.onclicked, lv.LV_EVENT_CLICKED, 0)
page.onShow();

   

