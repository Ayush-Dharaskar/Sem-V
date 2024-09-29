import random
import sympy
import os
from datetime import datetime, timedelta

class KeyManagementSystem:
    def __init__(self, key_size=1024):
        self.key_size = key_size
        self.keys = {}  # Store keys in memory for now
        self.logs = []
    
    # Rabin Key Generation
    def generate_rabin_keys(self):
        while True:
            # Generate two large primes p and q congruent to 3 mod 4
            p = sympy.randprime(2**(self.key_size//2 - 1), 2**(self.key_size//2))
            q = sympy.randprime(2**(self.key_size//2 - 1), 2**(self.key_size//2))
            if p % 4 == 3 and q % 4 == 3:
                break
        n = p * q
        public_key = n
        private_key = (p, q)
        return public_key, private_key

    # Simulate Secure API for Key Distribution
    def distribute_keys(self, hospital_name):
        public_key, private_key = self.generate_rabin_keys()
        self.keys[hospital_name] = {'public_key': public_key, 'private_key': private_key, 'created_at': datetime.now()}
        self.log_action(f"Distributed keys to {hospital_name}")
        return public_key, private_key

    # Key Revocation
    def revoke_keys(self, hospital_name):
        if hospital_name in self.keys:
            del self.keys[hospital_name]
            self.log_action(f"Revoked keys for {hospital_name}")
            return True
        self.log_action(f"Failed to revoke keys for {hospital_name}, hospital not found")
        return False
    
    # Key Renewal
    def renew_keys(self, hospital_name):
        if hospital_name in self.keys:
            public_key, private_key = self.generate_rabin_keys()
            self.keys[hospital_name] = {'public_key': public_key, 'private_key': private_key, 'created_at': datetime.now()}
            self.log_action(f"Renewed keys for {hospital_name}")
            return public_key, private_key
        self.log_action(f"Failed to renew keys for {hospital_name}, hospital not found")
        return None
    
    # Secure Storage - Here, a simulation with basic encryption can be used (this is simplistic)
    def secure_store_private_keys(self, hospital_name, storage_path='secure_storage'):
        if hospital_name in self.keys:
            private_key = self.keys[hospital_name]['private_key']
            if not os.path.exists(storage_path):
                os.makedirs(storage_path)
            filepath = os.path.join(storage_path, f"{hospital_name}_private_key.txt")
            with open(filepath, 'w') as f:
                f.write(str(private_key))
            self.log_action(f"Stored private key for {hospital_name} securely")
    
    # Auditing and Logging
    def log_action(self, action):
        log_entry = f"{datetime.now()} - {action}"
        self.logs.append(log_entry)
    
    # Get logs
    def get_logs(self):
        return '\n'.join(self.logs)

# Create an instance of the Key Management System with 1024-bit keys
kms = KeyManagementSystem(key_size=1024)

# Example Usage
public_key, private_key = kms.distribute_keys("City Hospital")
print(f"Public Key for City Hospital: {public_key}")
print(f"Private Key for City Hospital: {private_key}")

# Securely store the private key
kms.secure_store_private_keys("City Hospital")

# Revocation Example

kms.renew_keys("City Hospital")
kms.revoke_keys("City Hospital")
# Logs
print(kms.get_logs())
