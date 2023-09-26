#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])
{
	const int num_threads = 4;
	omp_set_num_threads(num_threads);

#pragma omp parallel
	{
	 int thread_id = omp_get_thread_num();
	 std::cout << "Thread " << thread_id << " started." << std::endl;

	 // Perform some work

	 // Wait for all threads to reach this point
	 #pragma omp barrier

	 // Continue with additional work
	 std::cout << "Thread " << thread_id << " completed." << std::endl;
	}
	return 0;
}
