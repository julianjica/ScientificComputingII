from mpi4py import MPI
import numpy as np
import matplotlib.pyplot as plt

def monte_carlo_int(dim, num_samples=int(1e6)):
    comm = MPI.COMM_WORLD
    size = comm.Get_size()
    rank = comm.Get_rank()

    x = np.random.uniform(-1, 1, (num_samples, dim))
    count_inside_circle = np.sum(np.sum(x**2, axis = 1) <= 1) 

    estimated_vol = (count_inside_circle / num_samples) * 2 ** dim

    estimated_vols = comm.gather(estimated_vol, root=0)

    if rank == 0:
        final_estimated_vol = sum(estimated_vols) / size
        return final_estimated_vol
    else:
        return None

if __name__ == "__main__":
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    volumes = [monte_carlo_int(dim) for dim in range(1, 26)]
    
    if rank == 0:
        plt.plot(range(1, 26), volumes)
        plt.show()
