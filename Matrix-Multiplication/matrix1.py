import time
# matrix1 = [[1, 2],
#            [4, 5]]
# matrix2 = [[1, 2],
#            [4, 5]]

# matrix1 = [[ 1,  2,  3,  4],
#            [ 4,  5,  6,  7],
#            [ 7,  8,  9, 10],
#            [10, 11, 12, 13]]
# matrix2 = [[ 1,  2,  3,  4],
#            [ 4,  5,  6,  7],
#            [ 7,  8,  9, 10],
#            [10, 11, 12, 13]]

matrix1 = []
matrix2 = []

for i in range(0, 16):
    temp = []
    for j in range(1, 17):
        temp.append((16 * i) + j)
    matrix1.append(temp)
    matrix2.append(temp)

print(matrix1)

def splitArr(m1):
    midR = len(m1)//2
    midC = len(m1[0])//2

    a11, a12, a21, a22 = [], [], [], []

    # atas - bawah
    atas = m1[:midR]
    bawah = m1[midR:]

    for x in atas:
        a11.append(x[:midC])
        a12.append(x[midC:])
    for x in bawah:
        a21.append(x[:midC])
        a22.append(x[midC:])
    
    return a11, a12, a21, a22

def combineArr(a11, a12, a21, a22):
    C = []

    # print("-------")
    # print(a11, a12)
    # print(a21, a22)
    # print("-------")

    for i in range(len(a11)):
        C.append([*a11[i], *a12[i]])
    for i in range(len(a21)):
        C.append([*a21[i], *a22[i]])

    # print(C)
    return C

def addMatriks2(a, b):
    # print(a, b, n)
    c = [[0 for j in range(len(a[0]))] for i in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a[0])):
            c[i][j] = a[i][j] + b[i][j]
    
    return c

def minMatriks2(a, b):
    # print(a, b, n)
    c = [[0 for j in range(len(a[0]))] for i in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a[0])):
            c[i][j] = a[i][j] - b[i][j]
    
    return c

def KaliMatriks2(m1, m2, n):
    # print(n)
    # print("===============================")
    if(n == 1):
        # print(m1, m2, "----")
        return [[m1[0][0] * m2[0][0]]]
    
    a11, a12, a21, a22 = splitArr(m1)
    b11, b12, b21, b22 = splitArr(m2)

    c11 = addMatriks2(KaliMatriks2(a11, b11, n//2), KaliMatriks2(a12, b21, n//2))
    # print(c11, "======")
    c12 = addMatriks2(KaliMatriks2(a11, b12, n//2), KaliMatriks2(a12, b22, n//2))
    c21 = addMatriks2(KaliMatriks2(a21, b11, n//2), KaliMatriks2(a22, b21, n//2))
    c22 = addMatriks2(KaliMatriks2(a21, b12, n//2), KaliMatriks2(a22, b22, n//2))
    C = combineArr(c11, c12, c21, c22)
    return C

def KaliMatriksStrassen(m1, m2, n):
    if(n == 1):
        return [[m1[0][0] * m2[0][0]]]

    a11, a12, a21, a22 = splitArr(m1)
    b11, b12, b21, b22 = splitArr(m2)

    m1 = KaliMatriksStrassen(minMatriks2(a12, a22), addMatriks2(b21, b22), n//2)
    m2 = KaliMatriksStrassen(addMatriks2(a11, a22), addMatriks2(b11, b22), n//2)
    m3 = KaliMatriksStrassen(minMatriks2(a11, a21), addMatriks2(b11, b12), n//2)
    m4 = KaliMatriksStrassen(addMatriks2(a11, a12), b22, n//2)
    m5 = KaliMatriksStrassen(a11, minMatriks2(b12, b22), n//2)
    m6 = KaliMatriksStrassen(a22, minMatriks2(b21, b11), n//2)
    m7 = KaliMatriksStrassen(addMatriks2(a21, a22), b11, n//2)

    c11 = addMatriks2(minMatriks2(addMatriks2(m1, m2), m4), m6)
    c12 = addMatriks2(m4, m5)
    c21 = addMatriks2(m6, m7)
    c22 = minMatriks2(addMatriks2(minMatriks2(m2, m3), m5), m7)

    C = combineArr(c11, c12, c21, c22)
    return C

if __name__ == "__main__":
    print(time.time())
    start_a = time.time()
    a = KaliMatriks2(matrix1, matrix2, len(matrix1))
    end_a = time.time()
    # print(a)
    start_b = time.time()
    b = KaliMatriksStrassen(matrix1, matrix2, len(matrix1))
    end_b = time.time()
    # print(b)
    print(time.time())
    print("Time a:", (end_a - start_a) * 10**3, "ms")
    print("Time b:", (end_b - start_b) * 10**3, "ms")