import socket
from Crypto.Util.number import bytes_to_long
import random

# ElGamal Encryption
def elgamal_encrypt(message, p, g, y):
    k = random.randint(1, p - 2)  # Random integer k
    c1 = pow(g, k, p)  # c1 = g^k mod p
    s = pow(y, k, p)  # s = y^k mod p
    c2 = (message * s) % p  # c2 = (message * s) mod p
    return c1, c2

# Client Socket Setup
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12345))

# Receive public key from server
data = client_socket.recv(4096).decode()
p, g, y = map(int, data.split(','))
print(f"Received public key (p, g, y): ({p}, {g}, {y})")

# Message to encrypt (convert string message to number)
message = "Hello, this is a secure message."
message_number = bytes_to_long(message.encode())  # Convert to a long integer
print(f"Message to send (as number): {message_number}")

# Encrypt the message
c1, c2 = elgamal_encrypt(message_number, p, g, y)
print(f"Encrypted message (c1, c2): ({c1}, {c2})")

# Send encrypted message to server
client_socket.sendall(f"{c1},{c2}".encode())

# Close connection
client_socket.close()
