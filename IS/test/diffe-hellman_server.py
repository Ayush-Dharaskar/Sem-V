import socket
from Crypto.Util.number import getPrime, inverse
import random

# Diffie-Hellman Key Generation
def generate_dh_key(bits=2048):
    p = getPrime(bits)  # Generate a large prime number
    g = 2  # Generator
    a = random.randint(1, p - 2)  # Private key for server (randomly chosen)
    A = pow(g, a, p)  # A = g^a mod p (public key)
    return p, g, a, A

# Server Socket Setup
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12345))
server_socket.listen(1)
print("Server is listening on port 12345...")

# Generate Diffie-Hellman keys for the server
p, g, a, A = generate_dh_key()
print("Server's public key A generated.")

# Wait for client connection
conn, addr = server_socket.accept()
print(f"Connection from {addr} established.")

# Send prime (p), generator (g), and public key (A) to the client
conn.sendall(f"{p},{g},{A}".encode())

# Receive the client's public key B
B = int(conn.recv(4096).decode())
print(f"Received client's public key B: {B}")

# Compute the shared secret on the server side: s_server = B^a mod p
shared_secret_server = pow(B, a, p)
print(f"Shared secret (server): {shared_secret_server}")

# Close connection
conn.close()
server_socket.close()
