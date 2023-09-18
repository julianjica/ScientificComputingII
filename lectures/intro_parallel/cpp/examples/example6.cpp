#include <iostream>
#include <thread>
#include <vector>

void hello_function(int thread){
    std::cout << "Hello world from thread " << thread << std::endl;
}

int main(){
    const int numThreads = 5;
    // We create a vector that is going to contain all threads
    std::vector<std::thread> threads;
    for (int ii=0; ii<numThreads; ii++){
        // We add a new thread to the threads vector
        threads.emplace_back(hello_function, ii);
        // We first put the function name and then its argument/s
    }
    // Wait for all threads to finish
    for (auto& thread: threads){
        thread.join();
    }
    return 0;
}
