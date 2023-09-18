#include <omp.h>
#include <iostream>

int main(int argc, char *argv[])
{
	const int N = 1000000;
	double sum = 0.0;

	#pragma omp parallel for reduction(+:sum)
	for (int i = 1; i <= N; i++) {
	sum += 1.0 / i;
	}

	std::cout << "Sum: " << sum << std::endl;
	return 0;
}
