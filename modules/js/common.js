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

var cached = {}

function Module(path) {
    this.path = path;
    this.module = undefined;
    this.exports = {};
}

Module.prototype.require_js = function(path) {
    return __require_js__(this, path);
}

Module.prototype.require_bc = function(path) {
    return __require_bc__(this, path);
}

function require(path) {
    var m = __require_module__(path);
    var process = __require_module__('process');
    if( m != undefined )
        return m;
    m = cached[path];
    if( m != undefined ) {
        return m.exports;
    }
    var prevModule = globalThis.module;
    var app_path = process.APP_PATH;

    var module = new Module(path);
    globalThis.module = module;
    var res = module.require_bc(app_path + '/' + path + '.bc');
    if( !res )
        res = module.require_js(app_path + '/' + path);

    if( res ) {
        cached[path] = module;
        globalThis.module = prevModule;
        return cached[path].exports;
    }

    var module_path = process.EVM_MODULE_PATH;
    res = module.require_bc(module_path + '/' + path + '.bc');
    if( !res )
        res = module.require_js(module_path + '/' + path);

    if( res ) {
        cached[path] = module;
        
        globalThis.module = prevModule;
        return cached[path].exports;
    }
    return undefined;
}

globalThis.require = require;
