from Crypto.Util.number import getPrime, inverse, bytes_to_long, long_to_bytes
import random

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a
# Generate RSA key pair
def generate_random_e(phi_n):
    while True:
        e = random.randint(2, phi_n - 1)  # Generate random integer in the range (2, phi_n)
        if gcd(e, phi_n) == 1:  # Check if e is coprime with phi_n
            return e

def generate_rsa_keys(bits=2048):
    # Step 1: Generate two distinct prime numbers
    p = getPrime(bits // 2)
    q = getPrime(bits // 2)

    # Step 2: Calculate n
    n = p * q

    # Step 3: Calculate the totient
    phi_n = (p - 1) * (q - 1)

    # Step 4: Choose public exponent e
    e = generate_random_e(phi_n) # Common choice for e

   # Step 5: Calculate private exponent d
    d = inverse(e, phi_n)

    return (n, e), (n, d)


# RSA encryption function
def rsa_encrypt(public_key, message):
    n, e = public_key
    # Convert message to integer
    m = bytes_to_long(message)
    # Encrypt the message
    c = pow(m, e, n)
    return c


# RSA decryption function
def rsa_decrypt(private_key, ciphertext):
    n, d = private_key
    # Decrypt the ciphertext
    m = pow(ciphertext, d, n)
    # Convert integer back to bytes
    decrypted_message = long_to_bytes(m)
    return decrypted_message


# Main code
if __name__ == "__main__":
    # Message to be encrypted
    message = b'Asymmetric Encryption'

    # Generate RSA public and private keys
    public_key, private_key = generate_rsa_keys(bits=2048)

    # Encrypt the message with the public key
    ciphertext = rsa_encrypt(public_key, message)
    print(f"Encrypted ciphertext (integer): {ciphertext}")

    # Decrypt the ciphertext with the private key
    decrypted_message = rsa_decrypt(private_key, ciphertext)
    print("Decrypted message:", decrypted_message.decode())

# from sympy import mod_inverse
#
# # RSA parameters (using larger primes for practicality)
# p = 61
# q = 53
# n = p * q
# phi_n = (p - 1) * (q - 1)
#
#
# def gcd(p, q):
#     # Use Euclid's algorithm to find the GCD.
#     while q != 0:
#         p, q = q, p % q
#     return p
#
#
# def coprime(nm):
#     for i in range(2, nm):
#         if gcd(i, nm) == 1:
#             return i
#     return None
#
#
# e = coprime(phi_n)
# # Compute private key d
# d = mod_inverse(e, phi_n)
# print(d)
#
#
# # RSA encryption function
# def rsa_encrypt(message, n, e):
#     encmsg = []
#     for char in message:
#         encmsg.append((pow(ord(char), e)) % n)
#
#     return encmsg
#
#
# # RSA decryption function
# def rsa_decrypt(encrypted_int, n, d):
#     decmsg = ""
#     for i in encrypted_int:
#         decmsg += chr(pow(i, d) % n)
#
#     return decmsg
#
#
# # Example message
# message = "Asymmetric Encryption"
#
# # Encrypt the message
# encrypted_message = rsa_encrypt(message, n, e)
# print("Encrypted message (integer):", encrypted_message)
#
# # Decrypt the message
# decrypted_message = rsa_decrypt(encrypted_message, n, d)
# print("Decrypted message:", decrypted_message)