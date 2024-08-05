from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import base64
# Define the 192-bit key and plaintext message
key_hex = 'FEDCBA9876543210FEDCBA9876543210'
key = bytes.fromhex(key_hex)
plaintext = b"Top Secret Data"

aes = AES.new(key,AES.MODE_ECB)

padded_plaintext = pad(plaintext,AES.block_size)

ciphertext = aes.encrypt(padded_plaintext) 

ascii_encrypted_text = base64.b64encode(ciphertext).decode('ascii')
print("Encrypted text:", ascii_encrypted_text)

decrypted_padded = aes.decrypt(ciphertext)

decrypted_text = unpad(decrypted_padded,AES.block_size)

print("Decrypted text:",decrypted_text)
