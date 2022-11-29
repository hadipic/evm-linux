var so = require("socket");
var id = so.socket(so.AF_INET, so.SOCK_STREAM, 0);
print('connect')
print(so.connect(id, "127.0.0.1", 8000))
