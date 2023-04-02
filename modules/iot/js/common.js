/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
var cached = {}

function Module(path) {
    this.path = path;
    this.module = undefined;
    this.exports = {};
}

Module.prototype.compile = function(path) {
    return __compile__(this, path);
}

function require(path) {
    var m = __require__(path);
    var process = __require__('process');
    if( m != undefined )
        return m;
    m = cached[path];
    if( m != undefined ) {
        return m.exports;
    }
    var prevModule = globalThis.module;
    var module = new Module(path);
    globalThis.module = module;
    var res = module.compile(path);
    if( res ) {
        cached[path] = module;
        globalThis.module = prevModule;
        return module.exports;
    }

    var evm_path = process.EVM_PATH;
    res = module.compile(evm_path + '/modules/iot/js/' + path);
    if( res ) {
        cached[path] = module;
        globalThis.module = prevModule;
        return module.exports;
    }
    
    var module_path = process.EVM_MODULE_PATH;
    res = module.compile(module_path + '/' + path);
    if( res ) {
        cached[path] = module;
        globalThis.module = prevModule;
        return module.exports;
    }
    return undefined;
}

globalThis.require = require;
