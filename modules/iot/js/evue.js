var lv = require('lvgl');
var pages = {};
var currentPage = undefined;

function Watcher(page) {
    this.bindings = {}
    var bindings = this.bindings;
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
                    var func = lv[binding.prefix + 'set_' + binding.attr];
                    func(binding.element, v);
                }
            }
        })
    })
}

Watcher.prototype.bind = function(element, attr, key, prefix) {
    if(this.bindings[key] == undefined) {
        this.bindings[key] = []
    }
       
    this.bindings[key].push({
        "element": element,
        "prefix": prefix,
        "attr": attr
    })
}

function getElementById(id) {
    return this.$nodes[id];
}

function onShow() {
    for(var i in this.$topNodes){
        var node = this.$topNodes[i];
        lv.lv_obj_clear_flag(node['$obj'], lv.LV_OBJ_FLAG_HIDDEN);
    }
    if( this.onShow )
        this.onShow();
}

function onHide() {
    for(var i in this.$topNodes){
        var node = this.$topNodes[i];
        lv.lv_obj_add_flag(node['$obj'], lv.LV_OBJ_FLAG_HIDDEN);
    }
    if( this.onHide )
        this.onHide();
}

function push(options) {
    if( options.path ) {
        var page =  pages[options.path]
        if( page ) {
            if( currentPage ) {
                currentPage.onHide();
            }
            currentPage = page;
            currentPage.$onShow();
        } else {
            require(options.path + ".evue.js");
            pages[options.path] = currentPage;
        }        
    }
}

module.exports = {
    "Watcher": Watcher,
    "onShow": onShow,
    "onHide": onHide,
    "push": push,
    "getElementById": getElementById
}