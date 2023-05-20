print('test lvgl')
var lv = require('@native.lvgl');
print(lv)
var arc = lv.lv_arc_create(lv.lv_scr_act());
lv.lv_obj_set_size(arc, 150, 150);
lv.lv_arc_set_rotation(arc, 135);
lv.lv_arc_set_value(arc, 10);
lv.lv_arc_set_mode(arc, 0)
lv.lv_arc_set_bg_angles(arc, 0, 270);
lv.lv_arc_set_angles(arc, 0, 270);