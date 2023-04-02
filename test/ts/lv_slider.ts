var t1 = clock();
var lv = require('@native.lvgl');

var slider = lv.lv_slider_create(lv.lv_scr_act());
lv.lv_obj_set_x(slider, 50);
lv.lv_obj_set_y(slider, 50);

function slider_changed(obj, code){
    print(lv.lv_slider_get_value(obj));
}
var i = 0;
for(i = 0; i < 1000000; i = i + 1){

}

lv.lv_obj_add_event_cb(slider, slider_changed, lv.LV_EVENT_VALUE_CHANGED);
print(clock() - t1)