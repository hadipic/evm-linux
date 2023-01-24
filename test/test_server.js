var tcp = require('tcp');
var so = tcp.create();

function createTCP() {
  return tcp.create();
}

function onread(socket, nread, isEOF, buffer) {
    print(buffer);
    print(nread);
}

function onconnection(status, clientHandle) {
  clientHandle.owner = {};
  clientHandle.onread = onread;
  clientHandle.readStart();
}

so.createTCP = createTCP;
so.onconnection = onconnection;
var err = so.bind('0.0.0.0', 12345);
print(err);
so.listen(12345);
