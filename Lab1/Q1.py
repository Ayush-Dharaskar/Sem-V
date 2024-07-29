def mod_inverse(a,b):
    
    for i in range(1,b):
        if (a*i)%b == 1:
            return i
    return None


def affine_encrypt(message,key1,key2):
    message = message.replace(" ","").upper()
    encrypted_message =""
    
    for char in message:
        if(char.isalpha()):
            num = ord(char) - ord('A')
            num =((key1 * num) +key2)%26
            encrypted_char = chr(num + ord('A'))
            encrypted_message+=(encrypted_char)
        else:
            encrypted_message+=(char)
    return encrypted_message

def affine_decrypt(message,key1,key2):
    message = message.replace(" ","").upper()
    decrypted_message =""
    inv1= mod_inverse(key1,26)
    for char in message:
        if(char.isalpha()):
            num = ord(char) - ord('A')
            num =(inv1 * (num -key2))%26
            decrypted_char = chr(num + ord('A'))
            decrypted_message+=(decrypted_char)
        else:
            decrypted_message+=(char)
    return decrypted_message



    
def add_encrypt(message, key):

    message = message.replace(" ", "").upper()
    encrypted_message = ""

  
    for char in message:
        if char.isalpha():  
            num = ord(char) - ord('A')
            num = (num + key) % 26
            encrypted_char = chr(num + ord('A'))
            encrypted_message+=(encrypted_char)
        else:
            encrypted_message+=(char)
    
    return encrypted_message

def add_decrypt(encrypted_message, key):
    decrypted_message = []

    
    for char in encrypted_message:
        if char.isalpha():  
        
            num = ord(char) - ord('A')

            num = (num - key) % 26

            decrypted_char = chr(num + ord('A'))
            decrypted_message.append(decrypted_char)
        else:
            decrypted_message.append(char)
    
    return ''.join(decrypted_message)



def mul_encrypt(message,key):
    message = message.replace(" ","").upper()
    encrypted_message = ""
    
    for char in message:
        if char.isalpha():
            num = ord(char) - ord('A')
            num = (num * key)%26
            encrypt_char = chr(num + ord('A'))
            encrypted_message += encrypt_char
        else:
            encrypted_message += char
            
    return encrypted_message

def mul_decrypt(message,key):
    decrypted_message=""
    
    inv = mod_inverse(key,26)
    print(inv)
    for char in message:
        if char.isalpha():
            num = ord(char) - ord('A')
            num = (num * inv)%26
            decrypt_char = chr(num + ord('A'))
            decrypted_message += decrypt_char
        else:
            decrypted_message += char
    return decrypted_message
    
    
    
    
message = "I am learning information security"
key = 15

encrypted_message = add_encrypt(message, key)
print(f"ADD Encrypted Message: {encrypted_message}")


decrypted_message = add_decrypt(encrypted_message, key)
print(f"ADD Decrypted Message: {decrypted_message}")

encrypted_message = mul_encrypt(message, key)
print(f"Mul Encrypted Message: {encrypted_message}")


decrypted_message = mul_decrypt(encrypted_message, key)
print(f"Mul Decrypted Message: {decrypted_message}")

encrypted_message = affine_encrypt(message, 15,20)
print(f"Affine encrypt Message: {encrypted_message}")

decrypted_message = affine_decrypt(encrypted_message, 15,20)
print(f"Affine decrypt Message: {decrypted_message}")
