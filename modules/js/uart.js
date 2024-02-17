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

var nuart = require("@native.uart");

function Uart(options, callback) {
    nuart.open(this, options, callback)
}

function close(callback) {
    nuart.close(this, callback)
}

function closeSync() {
    nuart.closeSync(this)
}

function write(data, callback) {
    nuart.write(this, data, callback)
}

function writeSync(data) {
    nuart.writeSync(this, data)
}

function read() {
    nuart.read(this)
}

function on(callback) {
    this.emit = callback;
}

Uart.prototype.close = close;
Uart.prototype.closeSync = closeSync;
Uart.prototype.write = write;
Uart.prototype.writeSync = writeSync;
Uart.prototype.read = read;
Uart.prototype.on = on;

var uart = {
    open: function(config, callback) {
        var uartPort = new Uart(config, callback);
        return uartPort;
    }
};

module.exports = uart;
