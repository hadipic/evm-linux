var lv = require('lvgl');

function Watcher(page) {
    this.bindings = {}
    var bindings = this.bindings;
    var data = page.data;
    var keys = Object.keys(data);
    for (let i = 0; i < keys.length; i++) {
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

module.exports = {
    "Watcher": Watcher,
    "getElementById": getElementById
}