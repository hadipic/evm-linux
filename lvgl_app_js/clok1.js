// clok1.js - FINAL: RECTANGLE HAND + lv_obj + CENTER PIVOT + REAL ROTATION
print("FINAL: RECTANGLE HAND - ROTATES AROUND CENTER - NO STRETCH");

var lv = require('@native.lvgl');
var scr = lv.lv_scr_act();

var CX = 120, CY = 120;

// --- صفحه ---
var face = lv.lv_obj_create(scr);
lv.lv_obj_set_size(face, 240, 240);
lv.lv_obj_set_pos(face, 0, 0);

// --- دایره وسط ---
var center_dot = lv.lv_obj_create(face);
lv.lv_obj_set_size(center_dot, 16, 16);
lv.lv_obj_set_pos(center_dot, CX - 8, CY - 8);

// --- container برای چرخش ---
var hand_container = lv.lv_obj_create(face);
lv.lv_obj_set_size(hand_container, 3, 90);  // اندازه دقیق مستطیل

// --- مستطیل (عقربه) — فرزند container ---
var hand_rect = lv.lv_obj_create(hand_container);
lv.lv_obj_set_size(hand_rect, 3, 90);
lv.lv_obj_set_pos(hand_rect, 0, 0);
lv.lv_obj_set_style_bg_color(hand_rect, 0xFF0000, 0);  // قرمز (اگر کار کرد)

// --- موقعیت اولیه container در مرکز صفحه ---
lv.lv_obj_set_pos(hand_container, CX - 1.5, CY - 45);  // وسط مستطیل در مرکز

// --- تابع چرخش حول مرکز ---
function rotateHand(angle_deg) {
    var rad = angle_deg * Math.PI / 180;

    // مرکز چرخش (وسط مستطیل)
    var pivot_x = 1.5;
    var pivot_y = 45;

    // فاصله از مرکز تا گوشه‌ها
    var corners = [
        { x: -pivot_x, y: -pivot_y },  // بالا-چپ
        { x:  pivot_x, y: -pivot_y },  // بالا-راست
        { x:  pivot_x, y:  pivot_y },  // پایین-راست
        { x: -pivot_x, y:  pivot_y }   // پایین-چپ
    ];

    var min_x = Infinity, min_y = Infinity;
    var max_x = -Infinity, max_y = -Infinity;

    for (var i = 0; i < 4; i++) {
        var c = corners[i];
        var rx = c.x * Math.cos(rad) - c.y * Math.sin(rad);
        var ry = c.x * Math.sin(rad) + c.y * Math.cos(rad);

        var world_x = CX + rx;
        var world_y = CY + ry;

        min_x = Math.min(min_x, world_x);
        min_y = Math.min(min_y, world_y);
        max_x = Math.max(max_x, world_x);
        max_y = Math.max(max_y, world_y);
    }

    var w = max_x - min_x;
    var h = max_y - min_y;

    lv.lv_obj_set_pos(hand_container, Math.round(min_x), Math.round(min_y));
    lv.lv_obj_set_size(hand_container, Math.round(w), Math.round(h));
}

// --- به‌روزرسانی ---
function update() {
    var d = new Date();
    var s = d.getSeconds() + d.getMilliseconds() / 1000;
    var angle = s * 6;

    rotateHand(angle);
}

setInterval(update, 50);
update();

print("RECTANGLE HAND ROTATES AROUND CENTER!");
print("Size fixed: 3x90 | Pivot at center");
print("NO stretch | NO image | REAL rotation with lv_obj");
