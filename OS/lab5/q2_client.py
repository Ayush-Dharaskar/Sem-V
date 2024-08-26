import socket
import hashlib
import time


host = 'localhost'
port = 3355
mssg = b'Hello World'

client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client_socket.connect((host,port))

client_socket.send(mssg)

hash_recv = client_socket.recv(64).decode()
hash_local = hashlib.sha256(mssg).hexdigest()

print(f"Sent message: {mssg.decode()}")
print(f"Local hash: {hash_local}")
print(f"Received hash: {hash_recv}")


if hash_local == hash_recv:
    print("Data integrity verified: Hashes match.")
else:
    print("Data integrity issue: Hashes do not match.")

client_socket.close()