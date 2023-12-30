import random

bilangan = []

nBilangan = 100
for i in range(nBilangan):
    bilangan.append(random.randint(1, 100))

count = 0

def dnc(arr, n):
    global count
    mid = n // 2
    # basis 1
    if(n == 1):
        # min, max
        return arr[0], arr[0]
    elif(n == 2):
        # count += 1
        if(arr[0] < arr[1]):
            return arr[0], arr[1]
        else:
            # count += 1
            return arr[1], arr[0]

    min1, max1 = dnc(arr[0:mid], mid)
    min2, max2 = dnc(arr[mid:], n-mid)

    max = max1
    min = min1
    count += 1
    if(max2 > max):
        max = max2
    count += 1
    if(min2 < min1):
        min = min2
    return min, max

print(bilangan)
print(dnc(bilangan, nBilangan))
print("operation:", count)