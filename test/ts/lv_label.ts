var lv = require('@native.lvgl');
var timer = require("@native.timer");
var label1 = lv.lv_label_create(lv.lv_scr_act());
lv.lv_label_set_text(label1, 'hello');

var a = 0;

function timeout() {
    if( a == 0){
        lv.lv_label_set_text(label1, 'hello');
        a = 1;
    } else {
        lv.lv_label_set_text(label1, 'EVM');
        a = 0;
    }
}

var t = timer.create();
t.handleTimeout = timeout;
t.start(100, 500); 