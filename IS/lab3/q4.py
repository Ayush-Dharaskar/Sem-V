import time
from cryptography.hazmat.primitives.asymmetric import rsa, ec
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
import os

def generate_rsa_key_pair():
    start_time = time.time()
    private_key = rsa.generate_private_key(public_exponent=65537, key_size=2048, backend=default_backend())
    public_key = private_key.public_key()
    end_time = time.time()
    key_gen_time = end_time - start_time
    return private_key, public_key, key_gen_time

def generate_ecc_key_pair():
    start_time = time.time()
    private_key = ec.generate_private_key(ec.SECP256R1(), default_backend())
    public_key = private_key.public_key()
    end_time = time.time()
    key_gen_time = end_time - start_time
    return private_key, public_key, key_gen_time

def encrypt_file_rsa(public_key, filename):
    with open(filename, 'rb') as f:
        data = f.read()
    
    # Encrypt the file data using RSA
    encrypted_data = public_key.encrypt(
        data,
        padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None)
    )
    
    return encrypted_data

def decrypt_file_rsa(private_key, encrypted_data):
    decrypted_data = private_key.decrypt(
        encrypted_data,
        padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None)
    )
    return decrypted_data

def encrypt_file_ecc(public_key, filename):
    # Generate symmetric key
    symmetric_key = os.urandom(32)
    
    # Encrypt the symmetric key using ECC
    shared_secret = ec.ECDH().exchange(public_key)
    derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=32,
        salt=None,
        info=b'secure file transfer',
        backend=default_backend()
    ).derive(shared_secret)
    
    # Encrypt the file data
    iv = os.urandom(12)
    cipher = Cipher(algorithms.AES(derived_key), modes.GCM(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    
    with open(filename, 'rb') as f:
        data = f.read()
    
    encrypted_data = encryptor.update(data) + encryptor.finalize()
    return iv + encryptor.tag + encrypted_data

def decrypt_file_ecc(private_key, encrypted_data):
    iv = encrypted_data[:12]
    tag = encrypted_data[12:28]
    ciphertext = encrypted_data[28:]
    
    # Derive the symmetric key
    shared_secret = private_key.exchange(ec.ECDH(), public_key)
    derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=32,
        salt=None,
        info=b'secure file transfer',
        backend=default_backend()
    ).derive(shared_secret)
    
    # Decrypt the file data
    cipher = Cipher(algorithms.AES(derived_key), modes.GCM(iv, tag), backend=default_backend())
    decryptor = cipher.decryptor()
    
    decrypted_data = decryptor.update(ciphertext) + decryptor.finalize()
    return decrypted_data

# Test file encryption and decryption
def test_encryption_decryption(key_gen_func, encrypt_func, decrypt_func, filename):
    private_key, public_key, key_gen_time = key_gen_func()
    
    print(f"Key Generation Time: {key_gen_time:.4f} seconds")
    
    # Measure encryption time
    start_time = time.time()
    encrypted_data = encrypt_func(public_key, filename)
    end_time = time.time()
    encryption_time = end_time - start_time
    print(f"Encryption Time: {encryption_time:.4f} seconds")
    
    # Measure decryption time
    start_time = time.time()
    decrypted_data = decrypt_func(private_key, encrypted_data)
    end_time = time.time()
    decryption_time = end_time - start_time
    print(f"Decryption Time: {decryption_time:.4f} seconds")
    
    # Verify data
    with open(filename, 'rb') as f:
        original_data = f.read()
    assert decrypted_data == original_data, "Decrypted data does not match the original!"
    
    print("Encryption and Decryption successful!")

# Use a sample file for testing
filename = 'sample.txt'
with open(filename, 'wb') as f:
    f.write(os.urandom(1024 * 1024))  # 1 MB file

print("Testing RSA Encryption/Decryption:")
test_encryption_decryption(generate_rsa_key_pair, encrypt_file_rsa, decrypt_file_rsa, filename)

print("\nTesting ECC Encryption/Decryption:")
test_encryption_decryption(generate_ecc_key_pair, encrypt_file_ecc, decrypt_file_ecc, filename)
