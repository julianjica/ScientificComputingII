def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

# Taking user input for the number
num = int(input("Enter a number to calculate its factorial: "))

# Checking if the number is negative
if num < 0:
    print("Factorial is not defined for negative numbers.")
else:
    result = factorial(num)
    print("Factorial of", num, "is", result)
