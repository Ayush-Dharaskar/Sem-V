import hashlib
import socket
host = 'localhost'
port = 3355
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_socket.bind((host,port))
server_socket.listen(5)
print(f"Server listening on {host}:{port}")

while True:
    client_socket,addr = server_socket.accept()
    print(f"connection from {addr}")

    buff = client_socket.recv(1024)

    hash_val = hashlib.sha256(buff).hexdigest()
    client_socket.send(hash_val.encode())
    client_socket.close()