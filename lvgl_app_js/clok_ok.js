// upward_hands_clock.js
print("Upward Hands Clock - Adjusting Pivot Lower...");

var lv = require('@native.lvgl');
var image = require('@native.image');

var scr = lv.lv_scr_act();

// متغیرهای全局 برای عقربه‌ها
var hour_hand = null;
var minute_hand = null;
var second_hand = null;

// تابع چرخش
function rotateHand(hand, angle) {
    if (hand && typeof lv.lv_img_set_angle === 'function') {
        lv.lv_img_set_angle(hand, angle);
        return true;
    }
    return false;
}

// تابع تنظیم موقعیت اولیه
function setInitialHandPositions() {
    var now = new Date();
    var hours = now.getHours();
    var minutes = now.getMinutes();
    var seconds = now.getSeconds();
    
    var second_angle = seconds * 6;
    var minute_angle = minutes * 6 + seconds * 0.1;
    var hour_angle = (hours % 12) * 30 + minutes * 0.5;
    
    rotateHand(second_hand, second_angle);
    rotateHand(minute_hand, minute_angle);
    rotateHand(hour_hand, hour_angle);
    
    print("Time: " + hours + ":" + minutes + ":" + seconds);
    print("Angles - H:" + hour_angle.toFixed(1) + "° M:" + minute_angle.toFixed(1) + "° S:" + second_angle + "°");
}

// لود تصاویر

    var clock_bg = lv.lv_img_create(scr);
    var bg_img = image.png_decode("watch.png");
    lv.lv_img_set_src(clock_bg, bg_img);
    lv.lv_obj_center(clock_bg);
    print("✓ Background loaded");

// لود عقربه‌ها با pivot پایین‌تر (یک‌سوم ارتفاع)
function loadHand(image_name) {

        var hand = lv.lv_img_create(scr);
        var img_data = image.png_decode(image_name);
        lv.lv_img_set_src(hand, img_data);
        lv.lv_obj_align(hand, lv.LV_ALIGN_CENTER, 0, 0);
        
        return hand;
   
}

// لود عقربه‌ها با pivot پایین‌تر
second_hand = loadHand("second.png");
// دوم: عقربه دقیقه  
minute_hand = loadHand("minute.png");
// سوم: عقربه ساعت (کوتاه‌ترین)
hour_hand = loadHand("hour.png");


// تنظیم موقعیت اولیه
setInitialHandPositions();

// تابع به‌روزرسانی زمان
function updateClock() {
    var now = new Date();
    var hours = now.getHours();
    var minutes = now.getMinutes();
    var seconds = now.getSeconds();
    
    var second_angle = seconds * 6;
    var minute_angle = minutes * 6 + seconds * 0.1;
    var hour_angle = (hours % 12) * 30 + minutes * 0.5;
    
    rotateHand(second_hand, second_angle);
    rotateHand(minute_hand, minute_angle);
    rotateHand(hour_hand, hour_angle);
}

// شروع به‌روزرسانی
if (typeof lv.lv_img_set_angle === 'function') {
    setInterval(updateClock, 1000);
    print("✓ Clock animation started!");
}

print("🎯 Hands should now be positioned HIGHER!");
print("📌 Pivot at 70% height makes hands move upward");
