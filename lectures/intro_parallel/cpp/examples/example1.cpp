#include <omp.h>
#include <iostream>


int main(int argc, char *argv[])
{
	#pragma omp parallel for
	{
		int suma = 0;
		for (int i = 0; i < 1000; ++i) {
			suma = suma + i;
		}
	std::cout << suma;
	}
	return 0;
}
