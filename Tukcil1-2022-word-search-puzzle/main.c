#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 100 // == 50 // maximum row col . jangan lupa bagi 2 karena ada spasi
#define max_char 100 // maximum karakter dalam 1 baris
#define endl printf("\n")

char* board;
char* wordList;
int* isBoard;
int row=0, col=0, n_word=0;

int getCol(FILE *fptr){
    // get col
    int col = 0;
    char first_line[max_size];
    fgets(first_line, sizeof(first_line), fptr);
    int i=0;
    while(first_line[i]){
        if(first_line[i] != ' ' && first_line[i] != '\n' && first_line[i] != '\r'){
            col++;
        }
        i++;
    }

    // printf("Columns count = %d\n", col);
    return col;
}

int getRow(FILE *fptr){
    // get row
    int row = 1;
    char* temp = (char*)malloc(sizeof(char) * max_size);
    while(fgets(temp, max_size, fptr)){
        if(!strcmp(temp, "\r\n")){
            break;
        }
        // printf("%s", temp);
        row++;
    }
    
    // printf("Row = %d\n", row);
    free(temp);
    return row;
}

int getNWord(FILE *fptr){
    int n = 0;
    char* temp = (char*)malloc(sizeof(char) * max_size);
    while(fgets(temp, max_size, fptr)){
        n++;
    }
    // printf("N Inputs = %d\n", n);
    free(temp);
    return n;
}

void createBoard(FILE **fptr, char *board){
    char* temp = (char*)malloc(sizeof(char) * max_size);
    int j = 0;
    while(fgets(temp, max_size, *fptr)){
        if(!strcmp(temp, "\r\n")){
            break;
        }

        int i=0;
        int count = 0;
        // printf("%s\n", temp);
        while(temp[i]){
            if(temp[i] != ' ' && temp[i] != '\n' && temp[i] != '\r'){
                board[j * col + count] = temp[i];
                count++;
            }
            i++;
        }
        // printf("%d\n", j);
        j++;
    }
    free(temp);
}

void createWordList(FILE *fptr, char *wordList){
    int count = 0;
    char *temp = (char*)malloc(sizeof(char) * (max_char));
    // fgets(temp, max_size, fptr);
    // printf("%s\n", temp);

    while(fgets(temp, max_char, fptr)){
        // printf("worked\n");
        int i=0;
        while(temp[i] != '\r' && temp[i] != '\n'){
            // printf("%c ", temp[i]);
            wordList[count * max_char + i] = temp[i];
            i++;
        }
        wordList[count * max_char + i] = '\0';
        // endl;
        count++;
        // printf("end\n");
    }
    free(temp);
}

void showBoard(char *board){
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            printf("%c ", board[i*col + j]);
        }
        endl;
    }
}

void showIsBoard(int *board){
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            printf("%d ", board[i*col + j]);
        }
        endl;
    }
}

void showWordList(char *wordList){
    for(int i=0; i<n_word; i++){
        int j=0;
        while(wordList[i*max_char + j]){
            printf("%c", wordList[i*max_char + j]);
            j++;
        }
        endl;
    }
}

void readFile(){
    char filename[100] = "test/test-0-small-15x18.txt";

    FILE* fptr;
    
    // get count of row, col, word
    fptr = fopen(filename, "r");
    col = getCol(fptr);
    row = getRow(fptr);
    n_word = getNWord(fptr);
    fclose(fptr);

    // setup board
    fptr = fopen(filename, "r");
    board = (char*)malloc(sizeof(char) * row * col);
    createBoard(&fptr, board);
    showBoard(board);

    isBoard = (int*)malloc(sizeof(int) * row * col);
    memset(isBoard, 0, sizeof(int)*row*col);
    // showBoard(isBoard);


    // setup wordlist
    wordList = (char*)malloc(sizeof(char) * n_word * max_char);
    createWordList(fptr, wordList);
    showWordList(wordList);
    fclose(fptr);
}

int strLen(char *x){
    int i=0;
    while(x[i] != '\0'){
        i++;
    }
    return i;
}

void checkKey(int rootX, int rootY, int directionX, int directionY, int wordIdx){
    // printf("called\n");
    int currentX = rootX, currentY = rootY;
    int count = 0;
    int wordLen = strLen(&wordList[wordIdx * max_char]);
    int isTrue = 0;
    int tempX=0, tempY=0;

    // printf("---- %d\n", wordLen);
    
    // printf("worked\n");
    // define boundary
    while(currentX >= 0 && currentX < col && currentY >= 0 && currentY < row && !isTrue){
        // printf("%c \n", board[currentY * col + currentX]);
        // printf("currentX, currentY - %d %d\n", currentX, currentY);
        if(board[currentY * col + currentX] == wordList[wordIdx * max_char + count]){
            // printf("%c %c\n", board[currentY * col + currentX], wordList[wordIdx * max_char + count]);
            count++;
            // rootX = currentX;
            // rootY = currentY;
            // printf("count = %d\n", count);
            if(wordLen == count){
                isTrue = 1;
                tempX = currentX - (directionX * (wordLen - 1));
                tempY = currentY - (directionY * (wordLen - 1));
                // break;
            }
        } else {
            count = 0;
        }
        // printf("currentX currentY - %d %d\n", currentX, currentY);
        // movement
        currentX += directionX;
        currentY += directionY;
    }
    // endl;

    // printf("OUT OF LOOP\n");
    // printf("isTrue ? - %d\n", isTrue);
    // if(isTrue){
    //     isBoard[currentY * col + currentX] = 1;
        // printf("TRUE\n");
    // }
    // printf("tempX, tempY - %d %d\n", tempX, tempY);
    while(!(tempX + directionX == currentX && tempY + directionY == currentY) && isTrue){
        // printf("tempX, tempY - currentX, currentY == (%d, %d) (%d, %d)\n", tempX, tempY, currentX, currentY);
        // printf("called\n");

        if(directionX == -1 || (directionX == 0 && directionY == -1)){
            isBoard[tempY * col + tempX] = 2;
        } else if(directionX == 1 || (directionX == 0 && directionY == 1)){
            isBoard[tempY * col + tempX] = 1;
        }
        // isBoard[tempY * col + tempX] = 1;
        tempX += directionX;
        tempY += directionY;
    }
    if(isTrue){
        // ketinggalan angka terakhir harus diubah juga
        if(directionX == -1 || (directionX == 0 && directionY == -1)){
            isBoard[tempY * col + tempX] = 2;
        } else if(directionX == 1 || (directionX == 0 && directionY == 1)){
            isBoard[tempY * col + tempX] = 1;
        }
    }
}

void bruteForce(){
    for(int r=0; r<row; r++){
        for(int c=0; c<col; c++){
            // printf("%d %d\n", r, c);
            // iterate through all words
            for(int k=0; k<n_word; k++){
                // printf("%d %d %d\n", r, c, k);
                // spread 8 direction
                checkKey(c, r, 1, 0, k); // right
                checkKey(c, r, 1, 1, k); // down right
                checkKey(c, r, 0, 1, k); // down
                checkKey(c, r, -1, 1, k); // down left
                checkKey(c, r, -1, 0, k); // left
                checkKey(c, r, -1, -1, k); // up left
                checkKey(c, r, 0, -1, k); // up 
                checkKey(c, r, 1, -1, k); // up right 
            }
            // printf("----------------------------------------\n");
        }
    }
}

void showAnswer(){
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(isBoard[i * col + j] == 2){
                printf("\033[1;32m%c\033[1;0m ", board[i * col + j]);
            } else if(isBoard[i * col + j] == 1){
                printf("\033[1;34m%c\033[1;0m ", board[i * col + j]);
            } else {
                printf("_ ");
            }
        }
        endl;
    }
}

int main(){
    readFile();

    bruteForce();

    showBoard(board);
    endl;
    showIsBoard(isBoard);
    endl;
    showAnswer();
    return 0;
}