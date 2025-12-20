/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

var lv = require('@native.lvgl');
var lv_style = require('@native.lv_style');

var image = require('@native.image');
var pages = {};
var currentPage = undefined;

var _set_style_bg_opa = lv_style.set_style_bg_opa;
lv_style.set_style_bg_opa = function(obj, v) {
    _set_style_bg_opa(obj, v * 255);
}

lv_style.set_style_font_size = function(obj, v) {
    var font = lv.lvgl_style_get_font(v);
    lv_style.set_style_text_font(obj, font);
}

var _set_style_text_align = lv_style.set_style_text_align;
lv_style.set_style_text_align = function(obj, align) {
    switch(align) {
    case "center": _set_style_text_align(obj, 2);return;
    case "left": _set_style_text_align(obj, 1);return;
    case "right": _set_style_text_align(obj, 3);return;
    default: _set_style_text_align(obj, 3);return;
    }
}

function Watcher(page) {
    this.$bindings = {}
    var bindings = this.$bindings;
    var data = page.data;
    var keys = Object.keys(data);
    currentPage = page;
    for (var i = 0; i < keys.length; i++) {
        var key = keys[i];
        page[key] = data[key];
    }
    data = page;
    keys.forEach(function(key) {
        var value = data[key];
        Object.defineProperty(data, key,{
            enumerable:true,
            configurable:true,
            get:function() {
                return value;
            },
            set:function(v) {
                if (value === v) {
                    return
                }
                value = v;
                var elements = bindings[key];
                if( elements == undefined ) 
                    return;
                for(var i in elements){
                    var binding = elements[i];
                    var func = binding.set;
                    func(binding.node.$obj, v);
                }
            }
        })
    })
}

Watcher.prototype.bind = function(node, key, set) {
    if(this.$bindings[key] == undefined) {
        this.$bindings[key] = []
    }
       
    this.$bindings[key].push({
        "node": node,
        "set": set
    })
}

function add_event(node, name, cb){
    var obj = node.$obj;
    var that = this;
    switch(name){
    case 'onclick':
        lv.lv_obj_add_flag(obj, lv.LV_OBJ_FLAG_CLICKABLE); 
        lv.lv_obj_add_event_cb(obj, function(obj, code){
            cb.call(that, node, node, lv.indev_get_x() - lv.lv_obj_get_abs_x(obj), lv.indev_get_y() - lv.lv_obj_get_abs_y(obj));
        }, lv.LV_EVENT_CLICKED);
        break;
    case 'onmousedown':
    case 'onpress': 
        lv.lv_obj_add_event_cb(obj, function(obj, code){
            cb.call(that, node, node, lv.indev_get_x() - lv.lv_obj_get_abs_x(obj), lv.indev_get_y() - lv.lv_obj_get_abs_y(obj));
        }, lv.LV_EVENT_PRESSED);
        break;
    case 'onmouseup':
    case 'onrelease': 
        lv.lv_obj_add_event_cb(obj, function(obj, code){
            cb.call(that, node, node, lv.indev_get_x() - lv.lv_obj_get_abs_x(obj), lv.indev_get_y() - lv.lv_obj_get_abs_y(obj));
        }, lv.LV_EVENT_RELEASED);
        break;
    case 'onmousemove':
    case 'onpressing': 
        lv.lv_obj_add_event_cb(obj, function(obj, code){
            cb.call(that, node, node, lv.indev_get_x() - lv.lv_obj_get_abs_x(obj), lv.indev_get_y() - lv.lv_obj_get_abs_y(obj));
        }, lv.LV_EVENT_PRESSING);
        break;
    case 'onlongpress': 
        lv.lv_obj_add_event_cb(obj, function(obj, code){
            cb.call(that, node, node, lv.indev_get_x() - lv.lv_obj_get_abs_x(obj), lv.indev_get_y() - lv.lv_obj_get_abs_y(obj));
        }, lv.LV_EVENT_LONG_PRESSED);
        break;
    case 'onValueChanged': 
        lv.lv_obj_add_event_cb(obj, function(obj, code){
            switch(node.name){
                case "slider":{
                    cb.call(that, node, lv.lv_slider_get_value(obj));
                }break;
                case "picker-view":{
                    cb.call(that, node, lv.lv_roller_get_selected(obj));
                }break;
                case "checkbox":{
                    cb.call(that, node, lv.lv_obj_get_state(obj) & lv.LV_STATE_CHECKED ? true:false);
                }break;
                case "combobox":{
                    cb.call(that, node, lv.lv_dropdown_get_selected(obj));
                }break;
                case "switch":{
                    cb.call(that, node, lv.lv_obj_get_state(obj) & lv.LV_STATE_CHECKED ? true:false);
                }break;
                case "arc":{
                    cb.call(that, node, lv.lv_arc_get_value(obj));
                }break;
            }
        }, lv.LV_EVENT_VALUE_CHANGED);
        break;
    default:
        return;
    }
}

function set_binding_value(node, key, set) {
    this.$watcher.bind(node, key, set)
}

function get_color(val) {
    if( typeof val == 'string') {
        switch(val) {
            case 'red': return lv.lv_color_hex(0xFF0000);
            case 'pink': return lv.lv_color_hex(0xFFC0CB);
            case 'purple': return lv.lv_color_hex(0xA020F0);
            case 'blue': return lv.lv_color_hex(0x0000FF);
            case 'cyan': return lv.lv_color_hex(0x00FFFF);
            case 'green': return lv.lv_color_hex(0x00FF00);
            case 'brown': return lv.lv_color_hex(0x964b00);
            case 'grey': return lv.lv_color_hex(0xC0C0C0);
            case 'lime': return lv.lv_color_hex(0x00FF00);
            case 'yellow': return lv.lv_color_hex(0xFFFF00);
            case 'amber': return lv.lv_color_hex(0xffbf00);
            case 'orange': return lv.lv_color_hex(0xFF6100);
            case 'burlywood': return lv.lv_color_hex(0xDEB887);
            case 'aliceblue': return lv.lv_color_hex(0xF0F8FF);
            case 'antiquewhite': return lv.lv_color_hex(0xFAEBD7);
            case 'aqua': return lv.lv_color_hex(0x00FFFF);
            case 'aquamarine': return lv.lv_color_hex(0x7FFFD4);
            case 'azure': return lv.lv_color_hex(0xF0FFFF);
            case 'beige': return lv.lv_color_hex(0xF5F5DC);
            default: return lv.lv_color_hex(0xFFFFFF);
        }
    } else {
        var _color = lv.lv_color_hex(val);
        return _color;
    }
}

var imageCache = {}

function image_set_src(obj, path) {
    var image_dsc = image.cache[path];
    if( image_dsc ) {
        lv.lv_img_set_src(obj, image_dsc);
        return;
    }
    image_dsc = imageCache[path];
    if ( image_dsc ) {
        lv.lv_img_set_src(obj, image_dsc);
        return;
    } else {
        image_dsc = image.png_decode(path);
        if( image_dsc ) {
            imageCache[path] = image_dsc;
            lv.lv_img_set_src(obj, image_dsc);
        }
    }
}

function evue_setTimeout(period, callback) {
    var that = this;
    return setTimeout(period, function() {
        callback.call(that)
    });
}

function evue_setInterval(period, callback, that) {
    var that = this;
    return setInterval(period, function() {
        callback.call(that)
    });
}

function evue_clearTimeout(id) {
    clearTimeout(id);
}

function evue_clearInterval(id) {
    clearInterval(id);
}

function set_text(id, value) {
    var node = this.$ids[id];
    if ( node ) {
        lv.lv_label_set_text(node['$obj'], value);
    }
}

function get_text(id) {
    var node = this.$ids[id];
    if ( node ) {
        return lv.lv_label_get_text(node['$obj']);
    }
}

var evue_proto = {
    '$add_event': add_event,
    '$set_binding_value': set_binding_value,
    '$get_color': get_color,
    '$image_set_src': image_set_src,
    '$setTimeout': evue_setTimeout,
    '$setInterval': evue_setInterval,
    '$clearTimeout': evue_clearTimeout,
    '$clearInterval': evue_clearInterval,
    '$setText': set_text,
    '$getText': get_text,
    '$getElementById': getElementById,
}

function getElementById(id) {
    return this.$ids[id];
}

function onShow(page) {
    lv.lv_obj_clear_flag(page.$topObj, lv.LV_OBJ_FLAG_HIDDEN);
    if( page.onShow )
        page.onShow();
}

function onHide(page) {
    lv.lv_obj_add_flag(page.$topObj, lv.LV_OBJ_FLAG_HIDDEN);
    if( page.onHide )
        page.onHide();
}

function push(options) {
    if( options.path ) {
        gc();
        var page =  pages[options.path];
        if( currentPage )
            onHide(currentPage);
        if( page ) {
            currentPage = page;
        } else {
            var mod = require(options.path + ".evue.js");
            currentPage = mod.init();
            currentPage.__proto__ = evue_proto;
            pages[options.path] = currentPage;
            currentPage.$watcher = new Watcher(currentPage);
            currentPage.$render();
            if( currentPage.onInit )
                currentPage.onInit();
        }    
        onShow(currentPage);
    }
}

function getCurrentPage() {
    return currentPage;
}

module.exports = {
    push: push,
    getCurrentPage: getCurrentPage
}
