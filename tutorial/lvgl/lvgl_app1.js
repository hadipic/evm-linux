var lv = require('@native.lvgl');

// ==================== Arc ====================
var arc = lv.lv_arc_create(lv.lv_scr_act());
lv.lv_obj_set_size(arc, 150, 150);
lv.lv_arc_set_rotation(arc, 135);
lv.lv_arc_set_value(arc, 10);
lv.lv_arc_set_mode(arc, 0);
lv.lv_arc_set_bg_angles(arc, 0, 270);
lv.lv_arc_set_angles(arc, 0, 270);

// ==================== هندلر ====================
function arc_event_handler(obj, code) {
    if (code === lv.LV_EVENT_VALUE_CHANGED) {
        console.log("Arc value changed:", lv.lv_arc_get_value(obj));
    }
}
lv.lv_obj_add_event_cb(arc, arc_event_handler, lv.LV_EVENT_VALUE_CHANGED);

// ==================== Task handler ====================
// این قسمت ضروریه تا LVGL UI و رویدادها اجرا بشه
setInterval(function() {
    lv.task_handler();
}, 20);

console.log("✅ Arc ready with task handler and event support");

