#include <omp.h>
#include <iostream>

int main(int argc, char *argv[])
{
	int num_threads = 10; // For example
	omp_set_num_threads(num_threads);
	#pragma omp parallel
	{
	    int thread_id = omp_get_thread_num();
	    int num_threads_used = omp_get_num_threads();
	    std::cout << "Hello World from thread " << thread_id << "/"
	    << num_threads_used << std::endl;
	}
	return 0;
}
