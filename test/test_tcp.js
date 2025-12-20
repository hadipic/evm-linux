var tcp = require("tcp");
var so = tcp.create();

function onconnection(status) {
    print(status)
}

function writecb(status) {
    print(status)
}

so.owner = {}
so.onread = function(socket, nread, isEOF, buffer) {
    print(buffer);
    print(nread);
}

so.connect("127.0.0.1", 12345, onconnection)
so.readStart();
so.write("hello EVM", writecb);
so.close()

