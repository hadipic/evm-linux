import socket
s = socket.socket()
s.bind(("127.0.0.1", 8000)) 
s.listen() 
chanel, client = s.accept() 
print(client)
while True:
    recive_content = chanel.recv(1024).decode() 
    if len(recive_content) > 0:
        print(recive_content)
s.close()
