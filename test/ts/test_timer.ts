var timer = require("@native.timer");

function timeout() {
    print("hello EVM");
}

var t = timer.create();
t.handleTimeout = timeout;
t.start(100, 500);