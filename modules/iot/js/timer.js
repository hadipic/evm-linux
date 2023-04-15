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

function _setTimeout(callback, time) {
    var t = new Timer()
    t.on(callback);
    t.start(time, false);
    t.start();
    return t;
}

function _clearTimeout(timer) {
    timer.stop();
}

globalThis.setTimeout = _setTimeout;
globalThis.clearTimeout = _clearTimeout;
