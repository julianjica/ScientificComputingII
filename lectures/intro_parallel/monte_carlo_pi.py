import random
from mpi4py import MPI

def monte_carlo_pi(num_samples):
    comm = MPI.COMM_WORLD
    size = comm.Get_size()
    rank = comm.Get_rank()

    # Initialize the random number generator with a unique seed for each process
    random.seed(rank)

    # Count the number of points inside the unit circle
    count_inside_circle = 0

    for _ in range(num_samples):
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)
        distance = x**2 + y**2

        if distance <= 1:
            count_inside_circle += 1

    # Calculate the estimated value of π for this process
    estimated_pi = (count_inside_circle / num_samples) * 4

    # Gather the estimated π values from all processes
    estimated_pis = comm.gather(estimated_pi, root=0)

    if rank == 0:
        # Process 0 calculates the final estimate of π
        final_estimated_pi = sum(estimated_pis) / size
        return final_estimated_pi
    else:
        return None

if __name__ == "__main__":
    num_samples = 1000000  # Number of random samples per process

    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()

    # Calculate the estimated π for this process
    estimated_pi = monte_carlo_pi(num_samples)

    if rank == 0:
        # Process 0 prints the final estimate of π
        print(f"Estimated value of π: {estimated_pi:.6f}")

