import random
import time
import logging
from sympy import isprime

# Configure logging
logging.basicConfig(filename='key_management.log', level=logging.INFO)

# In-memory key storage for demonstration
key_storage = {}

def generate_prime(bits):
    """Generate a random prime number of specified bit length."""
    while True:
        candidate = random.getrandbits(bits)
        if isprime(candidate):
            return candidate

def rabin_keygen(bits):
    """Generate a public and private key pair for the Rabin cryptosystem."""
    p = generate_prime(bits // 2)
    q = generate_prime(bits // 2)
    n = p * q
    return n, (p, q)  # Return public key (n) and private keys (p, q)

def log_operation(operation, facility_id):
    """Log key management operations."""
    logging.info(f'{operation} for facility {facility_id} at {time.ctime()}')


class KeyManagementService:
    def __init__(self):
        self.key_storage = {}

    def generate_keys(self, facility_id, key_size=1024):
        """Generate and store keys for a facility."""
        public_key, private_keys = rabin_keygen(key_size)
        self.key_storage[facility_id] = {
            'public_key': public_key,
            'private_keys': private_keys,
            'creation_time': time.time(),
            'expiry_time': time.time() + (365 * 24 * 60 * 60)  # Set expiry to 1 year
        }
        log_operation('Key Generation', facility_id)
        return public_key, private_keys

    def revoke_keys(self, facility_id):
        """Revoke keys for a facility."""
        if facility_id in self.key_storage:
            del self.key_storage[facility_id]
            log_operation('Key Revocation', facility_id)
            return f'Keys revoked for {facility_id}'
        else:
            return 'Facility not found'

    def renew_keys(self, facility_id, key_size=1024):
        """Renew keys for a facility."""
        if facility_id in self.key_storage:
            public_key, private_keys = rabin_keygen(key_size)
            self.key_storage[facility_id] = {
                'public_key': public_key,
                'private_keys': private_keys,
                'creation_time': time.time(),
                'expiry_time': time.time() + (365 * 24 * 60 * 60)  # Renew for 1 year
            }
            log_operation('Key Renewal', facility_id)
            return public_key, private_keys
        else:
            return 'Facility not found'

    def check_key_expiry(self, facility_id):
        """Check if the keys for a facility have expired."""
        if facility_id in self.key_storage:
            expiry_time = self.key_storage[facility_id]['expiry_time']
            if time.time() > expiry_time:
                return True  # Key has expired
            else:
                return False  # Key is valid
        else:
            return 'Facility not found'


def main():
    kms = KeyManagementService()
    
    while True:
        print("\nCentralized Key Management Service")
        print("1. Generate Keys")
        print("2. Revoke Keys")
        print("3. Renew Keys")
        print("4. Check Key Expiry")
        print("5. Exit")
        
        choice = input("Select an option: ")
        
        if choice == '1':
            facility_id = input("Enter facility ID: ")
            public_key, private_keys = kms.generate_keys(facility_id)
            print(f"Keys generated for {facility_id}. Public Key: {public_key}")
        
        elif choice == '2':
            facility_id = input("Enter facility ID to revoke: ")
            result = kms.revoke_keys(facility_id)
            print(result)
        
        elif choice == '3':
            facility_id = input("Enter facility ID to renew: ")
            public_key, private_keys = kms.renew_keys(facility_id)
            print(f"Keys renewed for {facility_id}. Public Key: {public_key}")

        elif choice == '4':
            facility_id = input("Enter facility ID to check expiry: ")
            is_expired = kms.check_key_expiry(facility_id)
            if is_expired is True:
                print(f"The keys for {facility_id} have expired.")
            elif is_expired is False:
                print(f"The keys for {facility_id} are still valid.")
            else:
                print(is_expired)

        elif choice == '5':
            print("Exiting the service.")
            break
        else:
            print("Invalid option. Please try again.")

if __name__ == "__main__":
    main()
