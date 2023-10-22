#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>


void initialize_matrix(bool matrix[][200], float rho, bool toss_coin = false)
{ // This function initializes the matrix based on the initial density rho
	if (toss_coin){
		std::random_device rd;  // Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<> dis(0, 1);	

		for (int ii = 0; ii < 200; ++ii) {
			for (int jj = 0; jj < 200; ++jj) {
				// We throw a coin to check if a cell is alive or dead
				if (dis(gen) <= rho) matrix[ii][jj] = true;
				else matrix[ii][jj] = false;
			}
		}
	}else{
		// Initialize the random number generator with the current time
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// We can also choose beforehand the cells that are going to be alive
		// For this, we generate N = 200 * 200 * rho unique random indices
		int N = 200 * 200 * rho;
		std::vector<int> random_indices;
		for (int ii = 0; ii < N; ++ii) {
			int random_index;
			do{
				random_index = std::rand() % (200 * 200);
			}while(std::find(random_indices.begin(), random_indices.end(), random_index)
					!= random_indices.end()); 
			random_indices.push_back(random_index);
		}
		// And with these we initialize the alive cells
		for (int index = 0; index < N; ++index) {
			int value = random_indices[index];
			int ii = value / 200;
			int jj = value % 200; 
			matrix[ii][jj] = true;
		}
	}
}

void single_iteration(bool matrix[][200])
{
	for (int ii = 0; ii < 200; ++ii) {
		for (int jj = 0; jj < 200; ++jj) {
			// We first count the number of neighbors
			int neighbors = 0;
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; dy++) {
					if (dx == 0 && dy == 0) continue;
					int nx = ii + dx;
					int ny = jj + dy;
					if (nx >= 0 && nx < 200 && ny >= 0 
							&& ny < 200 && matrix[nx][ny]) neighbors++;
				}
			}
			// And now we apply the rules of the game of life
			if (matrix[ii][jj]){
				// If the cell is alive and has less (more) than 2 (3) neighbors,
				// it dies
				if (neighbors < 2 || neighbors > 3) matrix[ii][jj] = false;
			}else{
				// A dead cell becomes alive if it has exactly three neighbors.
				if (neighbors == 3) matrix[ii][jj] = true;
			}
		}
	}
}

float evolve_matrix(bool matrix[][200])
{ // This function evolves the matrix following the rules of the game of life
  // and returns the final density after 500 iterations
	for (int ii = 0; ii < 500; ++ii) {
		single_iteration(matrix);
	}
	// After the iterations, we need to return the final density
	float final_density = 0.;
	for (int ii = 0; ii < 200; ++ii) {
		for (int jj = 0; jj < 200; ++jj) {
			if (matrix[ii][jj]) final_density++;
		}
	}
	return final_density / (200 * 200);
} 

void parallel_execution(int process_id, float* results)
{
	// We initialize the densities that are going to be
	// used in "process_id", using the divisibility equivalence
	// class
	float rho; int index;
	for (int ii = 0; ii < 5; ++ii) {
		index = process_id + 10 * ii;
		rho = index / 49.;
		// We initialize the matrix using the function
		bool matrix[200][200];
		initialize_matrix(matrix, rho);
		results[index] = evolve_matrix(matrix);
	}
}

int main(int argc, char *argv[])
{
	// Now, we are required to use 10 threads
	const int numThreads = 10;
	std::vector<std::thread> threads;
	float results[50] = {0}; //This array will store the results
	for (int ii = 0; ii < numThreads; ++ii) {
		threads.emplace_back(parallel_execution, ii, results);
	}
	for (auto& thread: threads) {
		thread.join();
	}
	
	// We show the results
	for (int ii = 0; ii < 50; ++ii) {
		std::cout << results[ii] << " ";
	}
	return 0;
}
