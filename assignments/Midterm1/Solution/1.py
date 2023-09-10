import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm

class HeatEquationSolver:
    def __init__(self):
        self.k = self.get_value("k", 0.005)
        self.h = self.get_value("h", 0.1)
        self.T = self.get_value("T", 50)
        
        self.memory_allocation()
        self.evolution()

    def get_value(self, string, default):
        try:
            value = float(input(f"Value for {string} (def={default}) > "))
            return value
        except ValueError:
            return default

    def memory_allocation(self):
        self.J = int(np.pi / self.h) # Space partition size
        self.N = int(self.T / self.k) # Time partition size

        self.memory = np.zeros((self.N, self.J), dtype = np.longfloat)
        # Setting initial and boundary conditions
        space_grid = np.linspace(0, np.pi, self.J)
        self.memory[0] = np.sin(space_grid) 
    
    def evolution(self):
        for ii in tqdm(range(1, self.N)):
            self.memory[ii][1:self.J -1] = self.memory[ii - 1][1:self.J-1]  + (self.k / self.h ** 2) * (self.memory[ii - 1][2:] - 2 * self.memory[ii - 1][1:self.J -1] + self.memory[ii - 1][:self.J - 2])

    def plot(self, type = "colormap"):
        space = np.linspace(0, np.pi, self.J)
        time = np.linspace(0, self.T, self.N)
        spacetime = np.meshgrid(space, time)
        
        if type == "colormap":
            plt.pcolor(spacetime[0], spacetime[1], self.memory)
            plt.xlabel("Position")
            plt.ylabel("Time")
            plt.colorbar()
        elif type == "3D":
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d') 
            ax.plot_surface(spacetime[0], spacetime[1], self.memory)
            ax.set_xlabel("Position")
            ax.set_ylabel("Time")
            ax.set_zlabel("Temperature")
        elif type == "animation":

        plt.show()

if __name__ == "__main__":
    obj = HeatEquationSolver()
    print(obj.memory)
    obj.plot("colormap")
