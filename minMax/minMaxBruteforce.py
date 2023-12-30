import random

bilangan = []

nBilangan = 100
for i in range(nBilangan):
    bilangan.append(random.randint(1, 100))

print(bilangan)

count = 0

min = bilangan[0]
max = bilangan[0]
for i in range(1, nBilangan):
    count += 1
    if(bilangan[i] > max):
        max = bilangan[i]
    count += 1
    if(bilangan[i] < min):
        min = bilangan[i]

print(min, max)
print("operation:", count)
