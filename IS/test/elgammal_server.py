import socket
from Crypto.Util.number import getPrime, inverse, bytes_to_long

# ElGamal Decryption
def elgamal_decrypt(c1, c2, p, x):
    s = pow(c1, x, p)  # Compute s = c1^x mod p
    s_inv = inverse(s, p)  # Modular inverse of s mod p
    decrypted_message = (c2 * s_inv) % p
    return decrypted_message

# Key Generation (ElGamal with Large Numbers)
def generate_keys(bits=2048):
    p = getPrime(bits)  # Generate a large prime number for p
    g = 2  # Generator
    x = getPrime(bits // 2)  # Private key x (randomly chosen)
    y = pow(g, x, p)  # Public key y = g^x mod p
    return p, g, y, x

# Server Socket Setup
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12345))
server_socket.listen(1)
print("Server is listening on port 12345...")

# Generate keys
p, g, y, x = generate_keys()
print("Keys generated.")
print(f"Server public key (p, g, y): ({p}, {g}, {y})")

# Wait for client connection
conn, addr = server_socket.accept()
print(f"Connection from {addr} established.")

# Send public key to client
conn.sendall(f"{p},{g},{y}".encode())

# Receive encrypted message
data = conn.recv(4096).decode()  # Receive larger data
c1, c2 = map(int, data.split(','))

# Decrypt the message
decrypted_message = elgamal_decrypt(c1, c2, p, x)
print(f"Decrypted message: {decrypted_message}")

# Close connection
conn.close()
server_socket.close()
