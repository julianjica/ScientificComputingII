#include <iostream>

int d=4;

int pow(int a, int b)
{
	int result = 1;
	for (int i = 0; i < b; ++i) 
		result = result * a;
	return result;
}

int main(int argc, char *argv[])
{
	int a, b; //Declaration
	a = 5; b = 3; //Initialization
	std::cout << 1.0 * a / b << std::endl; //explicit casting into double
	const double c = 1.67; // declaration and initialization in the same line
	std::cout << c << std::endl;

	bool f = true;
	std::cout << (f & false) << std::endl;
	std::cout << (f | false) << std::endl;
	std::cout << d << std::endl;

	// Arrays 
	int array[5];
	for (int i = 0; i < 5; ++i) {
		array[i] = i * i;
	}
	std::cout << array[4] << std::endl;
	int array2[] = {2,3,4,5,6};

	// Matrices
	int N, M;
	N = 2; M = 2;
	double double_array[N][M];
	int i;
	std::cout << std::endl;
	for (i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			double_array[i][j] = i + j;
			std::cout << double_array[i][j] << " ";
		}
		std::cout << std::endl;
	}

	// Conditionals
	std::cout  << std::endl;
	if (2 < 3){
		std::cout << "2 is smaller than 3" << std::endl;
	}

	if (4 > 5) {
		std::cout << "4 is greater than 5" << std::endl;
	}else{
		std::cout << "4 is smaller or equal than 5" << std::endl;
	}

	std::cout << std::endl;
	// Functions
	std::cout << pow(2,4) << std::endl;
	return 0;
}

