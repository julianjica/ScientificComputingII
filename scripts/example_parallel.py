import multiprocessing as mp
import time

def square_from_to(limits):
    start, end = limits
    for ii in range(start, end):
        print(ii ** 2, end=" ")

def control_unit(n, m):
    pool = mp.Pool(processes = m)
    intervals = [(ii, ii + int(n / m)) for ii in range(0, n, int(n / m))]
    output = pool.map(square_from_to, intervals)

if __name__ == "__main__":
    n = int(input("n > "))
    m = int(input("m > "))
    begin_time = time.process_time()
    square_from_to((0, n))
    end1 = time.process_time() - begin_time
    print("")
    begin_time = time.process_time()
    control_unit(n, m)
    end2 = time.process_time() - begin_time
    print("\nSequential: %f s\nParallel: %f s"%(end1,end2))
