#include <iostream>


void copy_matrix(int (*obj)[2][2], int (*result)[2][2])
{
	for (int ii = 0; ii < 2; ii++) {
		int* assist1 = *(result +ii);
		int* assist2 = *(obj +ii);
		for (int jj = 0; jj < 2; jj++) {
			*(assist1 +jj) = *(assist2 +jj);
		}
	}
}

int main(int argc, char *argv[])
{
	int matrix[2][2] ={{1,2},{3,4}};
	int result[2][2];
	copy_matrix(&matrix, &result);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
