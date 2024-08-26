def hashfn(mssg):
    val = 5381
    for i in mssg:
        val  = (val*33) + ord(i)

    return val & 0xFFFFFFFF

mssg = 'Ayush'
hash_val = hashfn(mssg)
print(hash_val)