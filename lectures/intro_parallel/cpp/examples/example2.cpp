#include <omp.h>
#include <iostream>
#include <chrono>

int serial_sum(int n)
{
	int suma = 0;
	for (int i = 0; i < n; ++i) {
		suma += i;
	}
	return suma;
}

int parallel_sum(int n)
{
	int suma = 0;
	#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		suma += i;
	}
	return suma;
}

int main(int argc, char *argv[])
{
	int n = 1000000;
	// Serial sum
	auto start = std::chrono::high_resolution_clock::now();
	int serial = serial_sum(n);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> serial_time = end - start;

	// Parallel sum
	start = std::chrono::high_resolution_clock::now();
	int parallel = parallel_sum(n);
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> parallel_time = end - start;

	// Print results
	std::cout << "Serial result: " << serial <<std::endl;
	std::cout << "Parallel result: " << parallel <<std::endl;
	std::cout << "Serial time: " << serial_time.count() << std::endl;
	std::cout << "Parallel time: " << parallel_time.count() << std::endl;
	std::cout << "Speedup: " << serial_time.count() / parallel_time.count() << std::endl;
	return 0;
}
