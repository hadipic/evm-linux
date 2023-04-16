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


function callback(type, data){
    print(type);
    print(data);
}

var uart = new Uart({
    'device':'/dev/pts/4',
    'baudRate':115200,
})
uart.on(callback);