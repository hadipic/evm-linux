print('Hello EVM')
var timer = require('timer');

function timeout() {
    print('Hello EVM')
}

var t = timer.create();
t.handleTimeout = timeout;
t.start(500, 500);