x=[1.0]*(2048*2048) # We create a massive list
a=str(x[0]) # We create a new variable by just takin the first element of x
a+=" is a one..." # Append some words
del x			# Free the memory
print(a) # Print the variable