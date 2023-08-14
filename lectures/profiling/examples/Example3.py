import numpy as np

@profile
def main():
	a = np.array([[1,2],[4,3]])
	b = np.array([[1,2],[4,3]])
	c = np.arange(2) + 1

	print("a= ", a)
	print("b= ", b)
	print(np.dot(a,b))
	print(a @ b)
	
main()
