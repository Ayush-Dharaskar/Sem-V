from Crypto.Cipher import DES3
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import base64

key = '453f67153a6bd452453f67153f6bd452453f67153a6bd452'

key = bytes.fromhex(key)

plaintext = b"Classified Text"


des3 = DES3.new(key, DES3.MODE_ECB)


plaintext_padded = pad(plaintext, DES3.block_size)


ciphertext = des3.encrypt(plaintext_padded)
ascii_encrypted_text = base64.b64encode(ciphertext).decode('ascii')
print("Ciphertext:", ascii_encrypted_text)


des3_decrypt = DES3.new(key, DES3.MODE_ECB)
decrypted_padded_message = des3_decrypt.decrypt(ciphertext)
decrypted_message = unpad(decrypted_padded_message, DES3.block_size)

print("Decrypted Message:", decrypted_message.decode())
