
# globar var
arr = []

def readfile(filename):
    file = open(filename, 'r')
    for line in file:
        line = line.strip('\n')
        line = line.replace('X', '')
        row = line.split(' ')
        for i in range(len(row)):
            row[i] = row[i]
        arr.append(row)

def write_to_file(filename):
    file = open(filename, 'w')

    temp = []
    for i in arr:
        i = ['X' if x == '' else x for x in i]
        i = ' '.join(i)
        temp.append(i)
    
    j = '\n'.join(temp)
    file.write(j)

def validValue(row, col, val):
    val = str(val)

    # cek 1 horizontal
    for x in range(9):
        if(arr[row][x] == val):
            return False
    
    # cek 1 vertikal
    # print(row, col)
    for y in range(9):
        if(arr[y][col] == val):
            return False
    
    # cek 1 kotak
    square_r = row // 3
    square_c = col // 3

    for i in range(3):
        for j in range(3):
            if(arr[i + square_r*3][j + square_c*3] == val):
                return False
    
    return True

def findNextEmpty(r, c):
    while(r < 9):
        while(c < 9):
            # print(r, c, "----------")
            if(arr[r][c] == ''):
                return r, c
            c += 1
        c = 0
        r += 1 
    return -1, -1

def bruteForce(rootR, rootC):
    r, c = findNextEmpty(rootR, rootC)
    if(r == c == -1):
        return True
    
    tracker = False
    for i in range(1, 10):
        if(validValue(r, c, i)):
            arr[r][c] = str(i)
            temp = bruteForce(r, c)

            tracker |= temp

    if(not tracker):
        arr[r][c] = ""

    return tracker
        
    

if __name__ == "__main__":
    filename = "test/test1.txt"
    readfile(filename)

    bruteForce(0, 0)
    
    print("final -")
    write_to_file("test/ans1.txt")