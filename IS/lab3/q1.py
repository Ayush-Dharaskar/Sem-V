from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Util.number import bytes_to_long, long_to_bytes
import base64
# Generate RSA key pair (public and private keys)
key = RSA.generate(2048)
public_key = key.publickey()

# Extract the components of the RSA key pair
n = key.n  # Modulus
e = key.e  # Public exponent
d = key.d  # Private exponent

# Message to be encrypted
message = "Asymmetric Encryption"

# Step 1: Encrypt the message using the public key (n, e)
cipher = PKCS1_OAEP.new(public_key)
ciphertext = cipher.encrypt(message.encode())

# Step 2: Decrypt the ciphertext using the private key (n, d)
cipher_decrypt = PKCS1_OAEP.new(key)
decrypted_message = cipher_decrypt.decrypt(ciphertext).decode()
ciphertext=base64.b64encode(ciphertext).decode('ascii')
# Print the results
print(f"Original Message: {message}")
print(f"Ciphertext (as bytes): {ciphertext}")
print(f"Decrypted Message: {decrypted_message}")
