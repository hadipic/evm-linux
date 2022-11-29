var lv = require('lvgl');
var label1 = lv.lv_label_create(lv.lv_scr_act());
lv.lv_label_set_text(label1, 'hello EVM');