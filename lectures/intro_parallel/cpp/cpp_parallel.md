---
author: Julián Jiménez-Cárdenas
---

# OpenMP
In this class, we will introduce how to program in parallel using `C++` and `OpenMP`. The first step to use this library is to include it:
```cpp
#include <omp.h>
```
In Windows this library should be included in your standard distribution (i.e., Visual Studio C/C++ compiler). On GNU/Unix systems, you can install it on bash
```bash
sudo apt install openmp
sudo pacman -S libomp
brew install libomp
```

---

### OpenMP directives

The second step is to enclose the code that you want to execute in parallel using the following syntax:
```cpp
#pragma omp <list of directives>
{
    // Code block to be executed in parallel
}
```
One of the directives is `parallel`,
```cpp
#pragma omp parallel
```
With this instruction, a new team of threads is created. Nevertheless, this runs the risk that multiple threads try to access a single resource, which slows down the execution. To fix this in the case of `for` loops, we use `omp for`.

---

### `omp for`
```cpp
#pragma omp parallel for
```
This instruction will:
1. Create a new team of threads just for the use of a `for` loop.
2. Each execution of the `for` loop will be assigned to a different thread.
3. Once execution of all threads is complete, all threads in the team are merged to the original team that is master thread.

#### Example
```cpp
#pragma omp parallel for
{
    int suma = 0;
    for(int ii = 0; i < 1000; ii++)
        suma = suma + ii;
}
```
See `example1.cpp` for a working example, and see `example2.cpp` to test speedup.

---

#### Number of threads
We can set the number of threads through
```cpp
int num_threads = 4; // For example
omp_set_num_threads(num_threads);

#pragma omp parallel
{
    int thread_id = omp_get_thread_num();
    int num_threads_used = omp_get_num_threads();
    std::cout << "Hello World from thread " << thread_id << "/"
    << num_threads_used << std::endl;
}
```
A working example of this can be found at `example3.cpp`. When specifying the threads, it is common to use the `-fopenmp` flag to compile the script, namely,
```bash 
g++ -o output example3.cpp -fopenmp
```
Note that we can use `OpenMP` to run serial programs concurrently.

---

### Barriers
As you may noticed, `OpenMP` programs operate within a single address space, where all threads have access to the same memory space.

This approach can be useful to do pipeline architectures, where you have a set of tasks to do. In such a case, you'd like that threads runs concurrently these tasks in order. In this context, if we want to set a barrier that should be reached for all threads before proceeding, we use `#pragma omp barrier`. 

Consider the following example.

---

### Barriers
```cpp
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
```

---

### Global and local variables
The region where we declare the variable will determine if this variable is global (shared accross threads) or local. Namely,

```cpp
// The following variable will be global, because it is
// declared prior to the parallel zone.
int global;
#pragma omp parallel
{
    // On the other hand, this one is local, as it is
    // declared inside the parallel zone.
    int local;
}
```
If we want to reduce the local variables, we can use the `reduction` clause. See the following example:
```cpp
const int N = 1000000;
double sum = 0.0;

#pragma omp parallel for reduction(+:sum)
for (int i = 1; i <= N; i++) {
    sum += 1.0 / i;
}

std::cout << "Sum: " << sum << std::endl;
```


---

### Concurrency problems (synchronization)
See the following code:
```cpp
omp_set_num_threads(10);
int val =0;
#pragma omp parallel
{
    val++;
}
std::cout << val;
```
The working example can be found in `example4.cpp`. If you run this program multiple times, you will get different results. We've already faced this problem in `Python`, and we solve it using the same approach: **locking and unlocking variables**.

---

#### (Un)locking variables
```cpp
omp_lock_t writelock;
omp_init_lock(&writelock);

// Stuff without synchronization problems
omp_set_lock(&writelock);
// Execution using one thread at a time
omp_unset_lock(&writelock);
// Other stuff
omp_destroy_lock(&writelock);
```
Modify `example4.py` to make it consistent. You can also use `#pragma omp critical`:
```cpp
#pragma omp parallel
{
    // Some stuff
    #pragma omp critical
    {
        // One thread at the time
    }
    // Some other stuff
}
```


---

### Your working example
Recall the Collatz Conjecture:

Every number can approach 1 after succesive applications of n/2 (if it is even) or 3n+1 (if it is odd). Get the total number of steps to  arrive to 1 for all numbers between 1 and N=300. 

For example, if N=4, 

1 (already at one, so we do 0 steps)

2 -> 1 (1 step)

3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1 (7 steps)

4 -> 2 -> 1 (2 steps)

so your code should return 10 in this case.

---

### Introduction to pointers

Pointers are variables that store memory addresses, allowing to access and manipulate data in memory. They are usually used to
- Dynamic memory allocation (not needed from C++11 and later).
- Working with arrays.
- Passing data efficiently to functions.

You declare them using the following syntax:
```cpp
type* pointerName;
```
Let's go to `examples/example7.cpp`.

---

# Concurrency TS (Technical Specification)
This Library is more focused on distributed memory, as we initialize threads independently, in a similar fashion than `multiprocessing` library in `Python`. Consider the following example:

```cpp
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
        threads.emplace_back(hello_function, ii)
        // We first put the function name and then its argument/s
    }
    // Wait for all threads to finish
    for (auto& thread: threads){
        thread.join();
    }
    return 0;
}
```
The working example of this program can be found in `example6.cpp`.

---

## Saving results 
Suppose that we want to save the results of the parallel function in an array. Then, we can pass the pointers to the parallel function. See the following working example.
```cpp
void threadFunction(int id, int* result){
    // Result is an integer pointer
    *result = id * 3;
}

int main(){
    const int num_threads = 6;
    // Array to store the results
    int results[num_threads];

    // Array to store the threads
    std::vector<std::threads> threads;

    for (int ii=0; ii < num_threads; ii++){
        threads.emplace_back(threadFunction, ii, &results[ii])
    }
    for (auto& thread : threads){
        thread.join()
    }
}
```

