import hashlib
import time
import string
import random




def generate_strings(n,mini,maxi):
    strings =[]
    letters = string.ascii_letters + string.digits
    for i in range(n):
        temp = "".join(random.choice(letters) for _ in range(random.randint(mini,maxi)))
        strings.append(temp)
    return strings

def compute_hash(strings,algo):
    results = []
    for str in strings:
        hash_obj = hashlib.new(algo)
        hash_obj.update(str.encode())
        results.append(hash_obj.hexdigest())

    return results
def analyze_performance(strings):

    algorithms = ['md5','sha1','sha256']
    result = {}

    for algo in algorithms:
        start = time.perf_counter()
        hash_val = compute_hash(strings,algo)
        print(f"{algo}: {hash_val}")
        end = time.perf_counter()
        time_taken = end-start
        result[algo] = time_taken


    return result
length = 20
num = 10
dataset = generate_strings(num,20,80)
hashed = analyze_performance(dataset)
print(dataset)
print(hashed)
