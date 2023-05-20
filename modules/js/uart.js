/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
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
