from mpi4py import MPI

def main():
    comm = MPI.COMM_WORLD
    size = comm.Get_size()
    rank = comm.Get_rank()

    if rank == 0:
        # Process 0 sends a message to Process 1
        message = "Hello from Process 0!"
        comm.send(message, dest=1)
        print(f"Process {rank} sent: '{message}'")
    elif rank == 1:
        # Process 1 receives the message from Process 0
        message = comm.recv(source=0)
        print(f"Process {rank} received: '{message}'")

if __name__ == "__main__":
    main()
