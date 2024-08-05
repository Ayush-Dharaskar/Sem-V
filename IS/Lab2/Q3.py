from Crypto.Cipher import DES, AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import time


message = b"Performance Testing of Encryption Algorithms"


def des_test(message):
    key = get_random_bytes(8)
    cipher = DES.new(key, DES.MODE_ECB)
    

    padded_message = pad(message, DES.block_size)
    

    start_time = time.time()
    encrypted_message = cipher.encrypt(padded_message)
    encryption_time = time.time() - start_time
    

    start_time = time.time()
    decrypted_padded_message = cipher.decrypt(encrypted_message)
    decrypted_message = unpad(decrypted_padded_message, DES.block_size)
    decryption_time = time.time() - start_time
    
    return encryption_time, decryption_time, key,decrypted_message


def aes_test(message):
    key = get_random_bytes(32)
    cipher = AES.new(key, AES.MODE_ECB)
    

    padded_message = pad(message, AES.block_size)
    

    start_time = time.time()
    encrypted_message = cipher.encrypt(padded_message)
    encryption_time = time.time() - start_time
    

    start_time = time.time()
    decrypted_padded_message = cipher.decrypt(encrypted_message)
    decrypted_message = unpad(decrypted_padded_message, AES.block_size)
    decryption_time = time.time() - start_time
    
    return encryption_time, decryption_time, key,decrypted_message

des_enc_time, des_dec_time, des_key,des_decrypt = des_test(message)
aes_enc_time, aes_dec_time, aes_key,aes_decrypt = aes_test(message)

print(f"DES Key: {des_key.hex()}")
print(f"DES decrypted_message: {des_decrypt}")
print(f"DES Encryption Time: {des_enc_time:.6f} seconds")
print(f"DES Decryption Time: {des_dec_time:.6f} seconds")
print(f"AES-256 Key: {aes_key.hex()}")
print(f"AES decrypted_message: {aes_decrypt}")
print(f"AES-256 Encryption Time: {aes_enc_time:.6f} seconds")
print(f"AES-256 Decryption Time: {aes_dec_time:.6f} seconds")
