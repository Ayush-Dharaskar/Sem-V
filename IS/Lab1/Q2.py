def genkeyword(mssg,key):
    
    key = key.upper()
    keyword = ""
    for i in range(len(mssg)):
        keyword += key[i%len(key)]
    return keyword


def autokey_encrypt(message,key):
    keyword=""
    keyword  = chr(key+ord('A'))
    keyword += message[:len(message)-1]
    print(keyword)
    
    print(keyword)
    
def vignere_encrypt(message,key):
    message = message.replace(" ",'').upper()
    keyword = genkeyword(message,key)
    encrypted_message =""


    for i in range(len(message)):
        
        num1 = ord(message[i]) - ord('A')
        num2 = ord(keyword[i]) - ord('A')
        en_char = chr((num1+num2)%26 + ord('A'))
        encrypted_message += en_char
    return encrypted_message


def vignere_decrypt(message,key):
    message = message.replace(" ",'').upper()
    keyword = genkeyword(message,key)
    encrypted_message =""

    for i in range(len(message)):
        
        num1 = ord(message[i]) - ord('A')
        num2 = ord(keyword[i]) - ord('A')
        en_char = chr((num1-num2)%26 + ord('A'))
        encrypted_message += en_char
    return encrypted_message
    
message = "the house is being sold tonight"
key= "dollars"
print(vignere_encrypt(message,key))
print(vignere_decrypt(vignere_encrypt(message,key),key))

autokey_encrypt(message,7)