print('test image lvgl')

var lv = require('@native.lvgl');
//var lv = require('print(lv)');
var lv = require('@native.image');

//var lv = require('lvgl');
//var image = require('image');



var img = lv.lv_img_create(lv.lv_scr_act());
var png = image.png_decode("logo.png");
lv.lv_img_set_src(img, png);



