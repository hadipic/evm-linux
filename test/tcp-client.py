# coding:utf-8

import signal
import socket
import time
import threading


# 这里需要修改为你电脑局域网IP地址
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 12345))

client.send(b"hello,world")


def main():
    while True:
        streambytes = client.recv(1024)
        data = streambytes.decode('utf-8')
        if not data:
            client.close()
            break
        print(data)
        time.sleep(1)
        client.send(streambytes)


if __name__ == "__main__":
    main()
