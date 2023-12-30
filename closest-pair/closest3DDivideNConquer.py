import math

import numpy as np
import matplotlib.pyplot as plt

arr = [(1, 2, 5), (3, 5, -1), (2, 7, 10), (-1, 5, 17),
       (0, -10, -10), (-3, 0, 4), (5, -2, 0), (0, 0, 0)]

def visualizeDots():
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    arr_x = []
    arr_y = []
    arr_z = []

    for i in range(len(arr)):
        arr_x.append(arr[i][0])
        arr_y.append(arr[i][1])
        arr_z.append(arr[i][2])
    
    ax.scatter3D(arr_x, arr_y, arr_z, color='green')

    plt.show()


if __name__ == "__main__":
    arr.sort()

    
    