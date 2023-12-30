
import math
# daftar titik

arr = [(1, 2), (3, 5), (2, 7), (-1, 5),
       (-10, -10), (-3, 4), (5, -2), (0, 0)]

arr.sort()

print(arr)

def getDistance(a, b):
    return math.sqrt((a[0] - b[0])**2 + (a[1] - b[1])**2)

def stripDist(arr):
    arr.sort()

    dist = 10 ** 10
    for i in range(len(arr)-1):
        for j in range(i+1, len(arr)):
            temp = getDistance(arr[i], arr[j])
            if(temp < dist):
                dist = temp

    return dist

def dnc(arr, n):
    mid = n // 2

    if(n == 2):
        return getDistance(arr[0], arr[1])
    
    s1 = arr[0:mid]
    s2 = arr[mid:]
    min1 = dnc(s1, mid)
    min2 = dnc(s2, n-mid)

    dist = min1 if (min1 < min2) else min2

    strip = []
    for i in range(n):
        if(arr[i][0] < arr[mid][0]):
            strip.append(arr[i])
    
    temp = stripDist(strip)
    return dist if (dist < temp) else temp

print(dnc(arr, len(arr)))