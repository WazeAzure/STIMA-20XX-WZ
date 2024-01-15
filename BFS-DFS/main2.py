import os
import time
import multiprocessing

maze = []
movement = [(1, 0), (0, 1), (-1, 0), (0, -1)]

def showMaze(maze):
    os.system('clear')
    for i in maze:
        print(' '.join(i))
    time.sleep(100/1000)

def initMaze():
    f = open('maze.txt', 'r')

    for line in f:
        line = line.strip()
        temp = [*line]
        map(lambda x : '.' if (x == ' ') else x, temp)
        maze.append(temp)
    
    f.close()

def getNextMove(c, visited):
    ans = []
    for move in movement:
        newR = c[0] + move[0]
        newC = c[1] + move[1]

        if(maze[newR][newC] != '#' and visited[newR][newC] != 1):
            ans.append((newR, newC))
    return ans


def TraverseRec(c, visited, endChar):
    visited[c[0]][c[1]] = 1
    if(maze[c[0]][c[1]] == endChar):
        print("FOUND!!")
        return True
    
    maze[c[0]][c[1]] = '.'
    
    showMaze(maze)


    nextMove = getNextMove(c, visited)

    for n in nextMove:
        x = TraverseRec(n, visited, endChar)
        if(x):
            return True
    
    return False

queueList = []
def BFS(c, visited, endChar):
    global queueList

    visited[c[0]][c[1]] = 1
    if(maze[c[0]][c[1]] == endChar):
        print("FOUND!!")
        return True
    
    maze[c[0]][c[1]] = '.'
    
    showMaze(maze)

    nextMove = getNextMove(c, visited)

    for x in nextMove:
        queueList.append(x)

    while(queueList):
        tempC = queueList.pop(0)
        x = BFS(tempC, visited, endChar)
        if(x):
            return True
    return False


if __name__ == "__main__":
    initMaze()
    oR, oC = len(maze)-3, len(maze[0])-3

    # print(maze)
    visited = [[0 for col in range(len(maze[0]))] for row in range(len(maze))]

    # BFS((oR, oC), visited, 'S')
    TraverseRec((oR, oC), visited, 'S')