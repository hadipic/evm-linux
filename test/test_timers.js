print('Hello EVM')
var timer = require('@native.timer');

function Timer() {
    this.handle = timer.create();
}

Timer.prototype.start = function(period, repeat) {
    timer.start(this.handle, period, repeat)
}

Timer.prototype.stop = function() {
    timer.stop(this.handle)
}

Timer.prototype.on = function(callback) {
    this.handle.handleTimeout = callback
}

function timeout() {
    print('Hello EVM')
}

var t = new Timer()
t.on(timeout);
t.start(500, true);