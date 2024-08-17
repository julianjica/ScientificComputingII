from numba import njit

@njit
def collatz_dir(n):
    dic = {}
    maximum = [0,0]
    for ii in range(1, n + 1):
        count = 0
        val = ii
        while val != 1:
            if val in dic:
                count += dic[val]
                break
            else:
                if val % 2 == 0:
                    val = val // 2
                else:
                    val = 3 * val + 1
            count += 1
        dic[ii] = count
        if count > maximum[0]:
            maximum[0] = count
            maximum[1] = ii
    return maximum



if __name__ == "__main__":
    print(collatz_dir(int(1e6)))
