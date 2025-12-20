print('test lvgl')
var lv = require('lvgl');
var image = require('image');
var timer = require('timer');
var lv = require('@native.lvgl');
var lv = require('print(lv)');


var arc = lv.lv_arc_create(lv.lv_scr_act());
lv.lv_obj_set_size(arc, 150, 150);
lv.lv_arc_set_rotation(arc, 135);
lv.lv_arc_set_value(arc, 10);
lv.lv_arc_set_mode(arc, 0)
lv.lv_arc_set_bg_angles(arc, 0, 270);
lv.lv_arc_set_angles(arc, 0, 270);


var label1 = lv.lv_label_create(lv.lv_scr_act());
lv.lv_label_set_text(label1, 'hello');
lv.lv_obj_set_size(label1, 150, 150);




var btn1 = lv.lv_btn_create(lv.lv_scr_act());
lv.lv_obj_align(btn1, lv.LV_ALIGN_CENTER, 0, -40);

function event_handler(obj, code) {
    print(obj, code);
}

lv.lv_obj_add_event_cb(btn1, event_handler, lv.LV_EVENT_CLICKED);

var label = lv.lv_label_create(btn1);
lv.lv_label_set_text(label, "Button");
lv.lv_obj_center(label);


var img = lv.lv_img_create(lv.lv_scr_act());
var png = image.png_decode("logo.png");
lv.lv_img_set_src(img, png);
