import socket
import random

# Diffie-Hellman Key Generation
def generate_dh_key(p, g):
    b = random.randint(1, p - 2)  # Private key for client
    B = pow(g, b, p)  # B = g^b mod p (public key)
    return b, B

# Client Socket Setup
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12345))

# Receive prime (p), generator (g), and public key (A) from the server
data = client_socket.recv(4096).decode()
p, g, A = map(int, data.split(','))
print(f"Received prime (p), generator (g), and server's public key A: ({p}, {g}, {A})")

# Generate Diffie-Hellman keys for the client
b, B = generate_dh_key(p, g)
print(f"Client's public key B generated: {B}")

# Send the client's public key B to the server
client_socket.sendall(f"{B}".encode())

# Compute the shared secret on the client side: s_client = A^b mod p
shared_secret_client = pow(A, b, p)
print(f"Shared secret (client): {shared_secret_client}")

# Close connection
client_socket.close()
