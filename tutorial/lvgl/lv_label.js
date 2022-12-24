var lv = require('lvgl');
var label1 = lv.lv_label_create(lv.lv_scr_act());
lv.lv_label_set_text(label1, 'hello');

var b = true;
function timer() {
    if(b)
        lv.lv_label_set_text(label1, 'hello');
    else
        lv.lv_label_set_text(label1, 'EVM');
    b = !b;
}

setInterval(timer, 500);
gc();
show();