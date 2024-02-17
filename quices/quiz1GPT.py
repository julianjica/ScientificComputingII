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
abundant_numbers = [i for i in range(12, limit) if is_abundant(i)]

# Step 2: Generate list of all possible sums of two abundant numbers
sums_of_abundants = set()
for i in range(len(abundant_numbers)):
    for j in range(i, len(abundant_numbers)):
        s = abundant_numbers[i] + abundant_numbers[j]
        if s <= limit:
            sums_of_abundants.add(s)

# Step 3: Identify numbers that cannot be represented as the sum of two abundant numbers
non_abundant_sums = [i for i in range(1, limit + 1) if i not in sums_of_abundants]

# Step 4: Sum up those numbers
result = sum(non_abundant_sums)

print("Sum of all positive integers that cannot be written as the sum of two abundant numbers:", result)

