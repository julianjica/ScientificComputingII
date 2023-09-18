#include <omp.h>
#include <iostream>

int main(int argc, char *argv[])
{
	omp_lock_t writelock;
	omp_init_lock(&writelock);

	omp_set_num_threads(10);
	int val =0;
	#pragma omp parallel
	{
		omp_set_lock(&writelock);
		val++;
		omp_unset_lock(&writelock);
	}
	std::cout << val;
	return 0;
}

