
import math
# daftar titik

arr = [(1, 2), (3, 5), (2, 7), (-1, 5),
       (-10, -10), (-3, 4), (5, -2), (0, 0)]

closest = 10 ** 10
closestA = ()
closestB = ()

for i in range(len(arr) - 1):
    for j in range(i+1, len(arr)):
        dist = math.sqrt((arr[i][0] - arr[j][0])**2 + (arr[i][1] - arr[j][1])**2)
        if(dist < closest):
            closest = dist
            closestA = arr[i]
            closestB = arr[j]

print(closest)
print(closestA, closestB)