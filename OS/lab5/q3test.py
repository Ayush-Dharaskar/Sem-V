import hashlib
import time
import random
import string

def generate_random_string(length):
    letters = string.ascii_letters + string.digits
    return ''.join(random.choice(letters) for i in range(length))



def compute_hash(data, algorithm):
    hash_obj = hashlib.new(algorithm)
    hash_obj.update(data.encode('utf-8'))
    return hash_obj.hexdigest()



def analyze_hashing_algorithms(num_strings, min_length, max_length):
    algorithms = ['md5', 'sha1', 'sha256']
    results = {}


    strings = [generate_random_string(random.randint(min_length, max_length)) for _ in range(num_strings)]

    for algo in algorithms:

        start_time = time.perf_counter()
        hashes = [compute_hash(s, algo) for s in strings]
        end_time = time.perf_counter()
        computation_time = end_time - start_time

        # Detect collisions
        hash_set = set()
        collisions = set()
        for h in hashes:
            if h in hash_set:
                collisions.add(h)
            hash_set.add(h)


        results[algo] = {
            'computation_time': computation_time,
            'collisions': len(collisions)
        }

    return results



num_strings = 100
min_length = 20
max_length = 80

results = analyze_hashing_algorithms(num_strings, min_length, max_length)

# Print results
for algo, result in results.items():
    print(f"Algorithm: {algo}")
    print(f"Computation Time: {result['computation_time']} seconds")
    print(f"Number of Collisions: {result['collisions']}")
    print('-' * 30)
