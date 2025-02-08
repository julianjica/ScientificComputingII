import numpy as np
import matplotlib.pyplot as plt
m = 20 # Numver of faces
n = 1e6 # Number of dice

mean = [0]
def recursive(n, m, mean, l=[]):
    for ii in range(1, m + 1):
        l.append(ii)
        if n > 1:
            recursive(n - 1, m, mean, l)
        else:
            mean[0] += min(l)
        l.pop(-1)
    return mean[0] / m ** n
def exact(n,m):
    suma = 0
    for y in range(1, m + 1):
        suma += y * ((m-y+1)**n/m**n- (m-y)**n/m**n)
    return suma
dice = np.random.randint(1, m + 1, (2,int(n)))
minimum = np.min(dice, axis=0)
print("Mean: ", np.mean(minimum))
#print("Recursive Mean: ", recursive(6, 20, mean))
#suma = 0
#for ii in range(1, m+1):
#    for jj in range(1, m+1):
#        suma += min(ii, jj) / m ** 2
#print("Expected value: ",suma)
#print(suma)
#plt.vlines(suma, 0, .1)
#plt.hist(minimum, bins = m, density = True)
#plt.show()
