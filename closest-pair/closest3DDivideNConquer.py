import math

import numpy as np
import matplotlib.pyplot as plt

arr = [(1, 2, 5), (3, 5, -1), (2, 7, 10), (-1, 5, 17),
       (0, -10, -10), (-3, 0, 4), (5, -2, 0), (0, 0, 0)]

def visualizeDots(pointA, pointB):
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
    
    ax.scatter3D(pointA[0], pointA[1], pointA[2], color='red')
    ax.scatter3D(pointB[0], pointB[1], pointB[2], color='red')
    ax.plot([pointA[0], pointB[0]], [pointA[1], pointB[1]], [pointA[2], pointB[2]], color='red', ls='dotted')

    ax.text(pointA[0], pointA[1], pointA[2], '(%d, %d, %d)'%(pointA[0], pointA[1], pointA[2]), color='red')
    ax.text(pointB[0], pointB[1], pointB[2], '(%d, %d, %d)'%(pointB[0], pointB[1], pointB[2]), color='red')
    
    mid = ((pointA[0] + pointB[0]) / 2, (pointA[1] + pointB[1]) / 2, (pointA[2] + pointB[2]) / 2)
    ax.text(mid[0], mid[1], mid[2], '%f'%(getDistance(pointA, pointB)), color='red')
    plt.show()

def getDistance(a, b):
    dimension = len(a)
    temp = 0
    for i in range(dimension):
        temp += (a[i] - b[i])**2
    return math.sqrt(temp)

def stripDist(arr):
    arr.sort() # sort x-axis

    dist = getDistance(arr[0], arr[1])
    pointA = arr[0]
    pointB = arr[1]

    for i in range(len(arr)-1):
        for j in range(i+1, len(arr)):
            temp = getDistance(arr[i], arr[j])

            if(temp < dist):
                dist = temp
                pointA = arr[i]
                pointB = arr[j]

    return dist, pointA, pointB

def dnc(arr, n):

    mid = n // 2

    if(n == 2):
        return getDistance(arr[0], arr[1]), arr[0], arr[1]

    s1 = arr[:mid]
    s2 = arr[mid:]
    min1, pointA1, pointB1 = dnc(s1, mid)
    min2, pointA2, pointB2 = dnc(s2, n-mid)

    dist = min1
    pointA = pointA1
    pointB = pointB1

    if(min2 < min1):
        dist = min2
        pointA = pointA2
        pointB = pointB2

    strip = []
    for i in range(n):
        if(abs(arr[i][0] - arr[mid][0]) <= dist):
            strip.append(arr[i])
    
    print("strip:", strip)
    
    temp, pointA3, pointB3 = stripDist(strip)
    
    if(temp < dist):
        return temp, pointA3, pointB3
    else:
        return dist, pointA, pointB

def bf(arr):
    dist = getDistance(arr[0], arr[1])
    pointA = arr[0]
    pointB = arr[1]

    for i in range(len(arr)-1):
        for j in range(i+1, len(arr)):
            temp = getDistance(arr[i], arr[j])
            if(temp < dist):
                dist = temp
                pointA = arr[i]
                pointB = arr[j]
    
    return dist, pointA, pointB

if __name__ == "__main__":
    arr.sort() # sort x-axis

    ans, pointA, pointB = dnc(arr, len(arr))
    ans1, pointA1, pointB1 = bf(arr)
    print(arr)
    print("closest distance dnc:", ans)
    print("points dnc:", pointA, pointB)
    print("closest distance bf:", ans1)
    print("points bf:", pointA1, pointB1)
    visualizeDots(pointA, pointB)