var lv = require('lvgl');
var timer = require('timer');
var label1 = lv.lv_label_create(lv.lv_scr_act());
lv.lv_label_set_text(label1, 'hello');

var b = true;
function timeout() {
    if(b)
        lv.lv_label_set_text(label1, 'hello');
    else
        lv.lv_label_set_text(label1, 'EVM');
    b = !b;
}

var t1 = timer.create();
print(t1.start)
t1.handleTimeout = timeout;
t1.start(500, 500)