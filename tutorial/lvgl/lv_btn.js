var lv = require('lvgl');
var btn1 = lv.lv_btn_create(lv.lv_scr_act());
lv.lv_obj_align(btn1, lv.LV_ALIGN_CENTER, 0, -40);

function event_handler(obj, code) {
    print(obj, code);
}

lv.lv_obj_add_event_cb(btn1, event_handler, lv.LV_EVENT_CLICKED);

var label = lv.lv_label_create(btn1);
lv.lv_label_set_text(label, "Button");
lv.lv_obj_center(label);
