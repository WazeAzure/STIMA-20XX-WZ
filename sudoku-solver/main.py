
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
    for y in range(9):
        if(arr[y][col] == val):
            return False
    
    # cek 1 kotak
    square_r = row // 3
    square_c = col // 3

    for i in range(3):
        for j in range(3):
            if(arr[i+square_r][j+square_c] == val):
                return False
    
    return True

def findNextEmpty(r, c):
    while(r < 9):
        while(c < 9):
            if(arr[r][c] == ''):
                return r, c
            c += 1
        c = 0
        r += 1 
    return -1, -1

def bruteForce(rootR, rootC, counter, start_value=1):
    currentY, currentX = rootR, rootC
    if(start_value== 10):
        return False
    if(validValue(currentY, currentX, start_value)):
        print("True")
        print(currentY, currentX, start_value)
        arr[currentY][currentX] = str(start_value)
        # solve(currentY, currentX)
        return True
    else:
        start_value += 1
        print("False")
        bruteForce(rootR, rootC, counter+1, start_value)
        return False

def solve(y=0, x=0, start_value=1):
    r, c = findNextEmpty(y, x)
    if bruteForce(r, c, 0, start_value):
        pass
    else:
        pass

if __name__ == "__main__":
    filename = "test/test1.txt"
    readfile(filename)

    solve()
    

    write_to_file("test/ans1.txt")