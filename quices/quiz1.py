import numpy as np
def find_divisors_sum(n):
    divisors_sum = 0
    for i in range(1, int(n**0.5) + 1):
        if n % i == 0:
            divisors_sum += i
            if i != 1 and i != n // i:
                divisors_sum += n // i
    return divisors_sum

def is_abundant(n):
    return find_divisors_sum(n) > n

# Upper limit
limit = 28123

# Step 1: Find abundant numbers
abundant_numbers = np.array([i for i in range(12, limit) if is_abundant(i)])
X, Y = np.meshgrid(abundant_numbers, abundant_numbers)
sums = X + Y
sums = sums.reshape(sums.size)

# Step 2: Identify numbers that cannot be represented as the sum of two abundant numbers
hashmap = np.full(limit, False)
hashmap[(sums - 1)[(sums - 1 < limit)]] = True
non_abundant_sums = np.arange(1, limit + 1)[~hashmap]

# Step 4: Sum up those numbers
result = sum(non_abundant_sums)

print("Sum of all positive integers that cannot be written as the sum of two abundant numbers:", result)


