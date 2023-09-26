#include <iostream>

void square_array(int* array, int size)
{
	for (int ii = 0 ; ii < size; ii++) {
		*(array + ii) = *(array + ii) * *(array + ii);	
	} /* for (int ii = 0 ; ii < size; ii++) */	
}
int main(int argc, char *argv[])
{
	int* pointer; // This pointer points to an integer
	int value = 1;
	pointer = &value; // The pointer is initialized with the
			  // address of value
	std::cout << pointer << std::endl; // we get a memory alloc.
	
	// Of course, we could declare and initialize the pointer
	// in a single line
	int* secPointer = &value;
	// A pointer can point to a null value (non-valid mem. alloc.)
	int* thiPointer = nullptr;

	// Dereferencing Pointer (aka, accesing its value)
	//std::cout << *pointer << std::endl;
	
	// Pointer Arithmetic
	int array[] = {1,2,3,4};
	pointer = array;
	//std::cout << *(array+2) << std::endl;
	*(array + 3) = 5;
	//std::cout << *(array + 3) << std::endl;
	
	// Passing to functions
	square_array(array, 4);
	for (int ii = 0; ii < 4; ii++) {
		std::cout << *(array + ii) << std::endl;
	} /* for (int ii = 0; ii < 4; ii++) */

	// N-dim matrix pointers
	int count = 0;
	int matrix[2][2];
	int* assistPointer = nullptr;
	for (int ii = 0; ii < 2; ii++) {
		assistPointer = *(matrix + ii);
		for (int jj = 0; jj < 2; jj++) {
			*(assistPointer + jj) = count;
			count++;
		} /* for (int jj = 0; jj < 2; jj++) */
	} /* for (int ii = 0; ii < 2; ii++) */
	for (int ii = 0; ii < 2; ii++) {
		for (int jj = 0; jj < 2; jj++) {
			std::cout << matrix[ii][jj] << " ";
		} /* for (int jj = 0; jj < 2; jj++) */
		std::cout << std::endl;
	} /* for (int ii = 0; ii < 2; ii++) */
	return 0;
}
