#include <vector>
#include <thread>
#include <iostream>


void threadFunction(int id, int* result){
         // Result is an integer pointer
         *result = id * 3;
     }

     int main(){
         const int num_threads = 6;
         // Array to store the results
         int results[num_threads];

         // Array to store the threads
         std::vector<std::thread> threads;

         for (int ii=0; ii < num_threads; ii++){
             threads.emplace_back(threadFunction, ii, &results[ii]);
         }
         for (auto& thread : threads){
             thread.join();
         }

	 for (int ii = 0; ii < num_threads; ii++) {
	 	
	 	std::cout << results[ii] << std::endl;
	 } /* for (int ii = 0; ii < num_threads; ii++) */
     }
