import numpy as np

@profile
def main():
    a = np.random.rand(10*1000*1000)
    b = np.random.rand(10*1000*1000)
    c = np.zeros(10*1000*1000)
    c = a**2 + b**2 + 2*a*b
    del b
    del c

main()
