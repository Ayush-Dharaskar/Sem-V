from Crypto.PublicKey import ElGamal
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Random import get_random_bytes
from datetime import datetime, timedelta
import base64
import os

# DRM Key Management System
class DRMKeyManagement:
    def __init__(self, key_size=1):
        self.key_size = key_size
        self.master_key_pair = None
        self.access_control_list = {}
        self.logs = []
    
    def generate_master_key(self):
        self.master_key_pair = ElGamal.generate(self.key_size, get_random_bytes)
        # self.log_action(f"Generated master public-private key pair with size {self.key_size} bits")
    
    def log_action(self, action):
        log_entry = f"{datetime.now()} - {action}"
        self.logs.append(log_entry)
    
    def get_logs(self):
        return '\n'.join(self.logs)

# Content Encryption Management
class ContentManagement:
    def __init__(self, drm):
        self.drm = drm
    
    def encrypt_content(self, content):
        if self.drm.master_key_pair:
            cipher = PKCS1_OAEP.new(self.drm.master_key_pair.publickey())
            encrypted_content = cipher.encrypt(content.encode())
            self.drm.log_action("Content encrypted using master public key")
            return base64.b64encode(encrypted_content).decode()
        else:
            raise Exception("Master key pair not generated")

# Key Distribution System
class KeyDistribution:
    def __init__(self, drm):
        self.drm = drm
    
    def distribute_private_key(self, customer_id):
        if self.drm.master_key_pair:
            self.drm.access_control_list[customer_id] = {
                'private_key': self.drm.master_key_pair.export_key(),
                'access_granted': datetime.now()
            }
            self.drm.log_action(f"Distributed master private key to customer {customer_id}")
        else:
            raise Exception("Master key pair not generated")
    
    def revoke_private_key(self, customer_id):
        if customer_id in self.drm.access_control_list:
            del self.drm.access_control_list[customer_id]
            self.drm.log_action(f"Revoked access for customer {customer_id}")

# Access Control System
class AccessControl:
    def __init__(self, drm):
        self.drm = drm
    
    def grant_limited_access(self, customer_id, content_id, access_time_minutes=60):
        expiry_time = datetime.now() + timedelta(minutes=access_time_minutes)
        self.drm.access_control_list[customer_id]['content_access'] = {
            'content_id': content_id,
            'expiry_time': expiry_time
        }
        self.drm.log_action(f"Granted limited-time access to customer {customer_id} for content {content_id}")
    
    def revoke_access(self, customer_id, content_id):
        if 'content_access' in self.drm.access_control_list[customer_id]:
            if self.drm.access_control_list[customer_id]['content_access']['content_id'] == content_id:
                del self.drm.access_control_list[customer_id]['content_access']
                self.drm.log_action(f"Revoked access to content {content_id} for customer {customer_id}")

# Key Revocation System
class KeyRevocation:
    def __init__(self, drm):
        self.drm = drm
    
    def revoke_master_key(self):
        if self.drm.master_key_pair:
            self.drm.master_key_pair = None
            self.drm.log_action("Master private key revoked due to security breach")

# Key Renewal System
class KeyRenewal:
    def __init__(self, drm):
        self.drm = drm
    
    def renew_master_key(self, renewal_interval_months=24):
        self.drm.generate_master_key()
        self.drm.log_action(f"Master key renewed after {renewal_interval_months} months")

# Secure Storage for Private Keys
class SecureStorage:
    def __init__(self, drm):
        self.drm = drm
        self.storage_path = "secure_storage/"
    
    def store_private_key(self):
        if not os.path.exists(self.storage_path):
            os.makedirs(self.storage_path)
        
        with open(self.storage_path + "master_private_key.pem", "wb") as file:
            file.write(self.drm.master_key_pair.export_key())
        self.drm.log_action("Master private key securely stored")
    
    def load_private_key(self):
        with open(self.storage_path + "master_private_key.pem", "rb") as file:
            self.drm.master_key_pair = ElGamal.import_key(file.read())
        self.drm.log_action("Master private key loaded from secure storage")

# Auditing and Logging System
class Auditing:
    def __init__(self, drm):
        self.drm = drm
    
    def get_audit_logs(self):
        return self.drm.get_logs()

# Menu-driven system
def menu():
    drm = DRMKeyManagement(key_size=512)
    content_mgmt = ContentManagement(drm)
    key_dist = KeyDistribution(drm)
    access_control = AccessControl(drm)
    key_revocation = KeyRevocation(drm)
    key_renew = KeyRenewal(drm)
    secure_storage = SecureStorage(drm)
    auditing = Auditing(drm)
    
    while True:
        print("\n--- DRM Key Management System ---")
        print("1. Generate Master Key Pair")
        print("2. Encrypt Content")
        print("3. Distribute Private Key to Customer")
        print("4. Grant Limited Access to Customer")
        print("5. Revoke Access for Customer")
        print("6. Revoke Master Private Key")
        print("7. Renew Master Key Pair")
        print("8. Store Master Private Key Securely")
        print("9. Load Master Private Key from Storage")
        print("10. View Audit Logs")
        print("11. Exit")
        
        choice = int(input("Enter your choice: "))
        
        if choice == 1:
            drm.generate_master_key()
            print("Master key pair generated.")
        
        elif choice == 2:
            content = input("Enter content to encrypt: ")
            encrypted_content = content_mgmt.encrypt_content(content)
            print(f"Encrypted Content: {encrypted_content}")
        
        elif choice == 3:
            customer_id = input("Enter customer ID: ")
            key_dist.distribute_private_key(customer_id)
            print(f"Private key distributed to customer {customer_id}.")
        
        elif choice == 4:
            customer_id = input("Enter customer ID: ")
            content_id = input("Enter content ID: ")
            access_time = int(input("Enter access time in minutes: "))
            access_control.grant_limited_access(customer_id, content_id, access_time)
            print(f"Limited access granted to customer {customer_id}.")
        
        elif choice == 5:
            customer_id = input("Enter customer ID: ")
            content_id = input("Enter content ID: ")
            access_control.revoke_access(customer_id, content_id)
            print(f"Access revoked for customer {customer_id}.")
        
        elif choice == 6:
            key_revocation.revoke_master_key()
            print("Master private key revoked.")
        
        elif choice == 7:
            key_renew.renew_master_key()
            print("Master key pair renewed.")
        
        elif choice == 8:
            secure_storage.store_private_key()
            print("Master private key securely stored.")
        
        elif choice == 9:
            secure_storage.load_private_key()
            print("Master private key loaded from secure storage.")
        
        elif choice == 10:
            print("Audit Logs:")
            print(auditing.get_audit_logs())
        
        elif choice == 11:
            print("Exiting...")
            break
        
        else:
            print("Invalid choice, please try again.")

# Run the menu-driven system
if __name__ == "__main__":
    menu()
