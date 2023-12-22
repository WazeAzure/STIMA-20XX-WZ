#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "listlinier.h"
#include "listlinierS.h"
#include "util.h"

char validInput[13][2] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

char symbols[4] = {'+', '-', '*', '/'};

struct Pair {
    int a;
    int b;
};

List listAns;

/* ====================================================================================== */

int cekSpasi(char buffer[1000]){
    int i=0, counter = 0;
    int status = 1;
    while(buffer[i] && status){
        if(buffer[i] == ' '){
            counter++;
        }
        if(counter > 3){
            status = 0;
            // printf("called\n");
        }
        i++;
        // printf("nilai counter -- %d\n", counter);
    }

    if(!status){
        printf("Argumen yang diberikan lebih dari 4!\n");
    }
    return status;
}

int validateInput(char inp[4][10], int param){
    // cek jumlah argumen
    if(param != 4){
        printf("Mohon maaf input harus 4 angka!\n");
        return 0;
    }

    // cek angka yang di input
    int i=0;
    int j;
    int status = 0;
    for(i=0; i<4; i++){
        j = 0;
        while(!status && j < 13){
            if(strCompare(validInput[j], inp[i]) == 1){
                status = 1;
            }
            j++;
        }

        if(status == 0){
            printf("Input tidak valid! Cek kembali input anda.\n");
            return 0;
        }
        status = 0;
    }

    return 1;
}

void readInput(int k[4]){
    char inp[4][10];
    char buffer[1000];
    int val = 0;
    int param = 0;
    
    while(val != 1){
        fgets(buffer, sizeof(buffer), stdin);
        val = cekSpasi(buffer);

        if(!val) continue;

        param = sscanf(buffer, "%s %s %s %s", inp[0], inp[1], inp[2], inp[3]);
        printf("jumlah param %d\n", param);
        
        val = validateInput(inp, param);
    }
    
    // string to int equivalent
    int i;
    int j;
    for(i=0; i<4; i++){
        for(j=0; j < 13; j++){
            if(strCompare(inp[i], validInput[j]) == 1){
                k[i] = j+1;
                break;
            }
        }
    }

    printf("%s %s %s %s\n", inp[0], inp[1], inp[2], inp[3]);
}

void generateFaktor24(struct Pair* p){
    int x = 24;

    struct Pair pTemp;
    int count = 0;
    for(int i=1; i*i <= x; i++){
        if(x % i == 0){
            pTemp.a = i;
            pTemp.b = x / i;
            p[count] = pTemp;
            count++;
        }
    }
}

void printFaktor24(struct Pair* p){
    for(int i=0; i<4; i++){
        printf("%d %d\n", p[i].a, p[i].b);
    }
}

int getDerajat(char o){
    if(o == '+' || o == '-') return 1;
    else return 2;
}

float eval2(float x, char o, float y){
    if(o == '+') return x + y;
    else if(o == '-') return x - y;
    else if(o == '*') return x * y;
    else if(o == '/') return x / y;
}

float eval3(float x, char o1, float y, char o2, float z){
    int val_o1 = getDerajat(o1);
    int val_o2 = getDerajat(o2);

    if(val_o1 >= val_o2){
        return eval2(eval2(x, o1, y), o2, z);
    } else {
        return eval2(x, o1, eval2(y, o2, z));
    }
}

int kasusKurung2(int numbers[4]){
    /*
    + - / * --> 4
    4! --> 24
    total 96 cara untuk 1 kurung
    kasus kurung 2 elemen
    */

    int i, j, k; // lambang
    int count = 0;
    
    float sum = 0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            for(k=0; k<4; k++){
                // [0] i [1] j [2] k [3]

                sum = eval2(numbers[2], symbols[k], numbers[3]);

                sum = eval2(eval2(numbers[0], symbols[i], numbers[1]), symbols[j], sum);
                if(sum == 24){
                    printf("(%d %c %d) %c (%d %c %d)\n", numbers[0], symbols[i], numbers[1], symbols[j], numbers[2], symbols[k], numbers[3]);

                    count++;
                }
                
                // kasus kemiripan
                // if((symbols[i] == '+' || symbols[i] == '*') && symbols[i] == symbols[j] && symbols[j] == symbols[k]) continue;

                // if((symbols[i] == '*' && symbols[j] == '+' && symbols[k] == '+') ||
                // (symbols[i] == '+' && symbols[j] == '*' && symbols[k] == '+') ||
                // (symbols[i] == '+' && symbols[j] == '+' && symbols[k] == '*')) {
                //     sum = eval2(numbers[1], symbols[j], numbers[2]);

                //     sum = eval3(numbers[0], symbols[i], sum, symbols[k], numbers[3]);
                //     if(sum == 24){
                //         printf("%d %c (%d %c %d) %c %d\n", numbers[0], symbols[i], numbers[1], symbols[j], numbers[2], symbols[k], numbers[3]);
                //         count++;
                //     }
                //     continue;
                // }

                /* KURUNG 3 */
                sum = eval2(eval2(numbers[0], symbols[i], numbers[1]), symbols[j], numbers[2]);

                sum = eval2(sum, symbols[k], numbers[3]);
                if(sum == 24){
                    printf("((%d %c %d) %c %d) %c %d\n", numbers[0], symbols[i], numbers[1], symbols[j], numbers[2], symbols[k], numbers[3]);
                    count++;
                }

                // kasus kemiripan
                if((symbols[i] == '+' || symbols[i] == '*') && symbols[i] == symbols[j] && symbols[j] == symbols[k]) continue;

                if(getDerajat(symbols[i]) == getDerajat(symbols[j])) continue;

                sum = eval2(numbers[0], symbols[i], eval2(numbers[1], symbols[j], numbers[2]));

                sum = eval2(sum, symbols[k], numbers[3]);
                if(sum == 24){
                    printf("(%d %c (%d %c %d)) %c %d\n", numbers[0], symbols[i], numbers[1], symbols[j], numbers[2], symbols[k], numbers[3]);
                    count++;
                }

                sum = eval2(eval2(numbers[1], symbols[j], numbers[2]), symbols[k], numbers[3]);

                sum = eval2(numbers[0], symbols[i], sum);
                if(sum == 24){
                    printf("%d %c ((%d %c %d) %c %d)\n", numbers[0], symbols[i], numbers[1], symbols[j], numbers[2], symbols[k], numbers[3]);
                    count++;
                }

                if(getDerajat(symbols[j]) == getDerajat(symbols[k])) continue;

                sum = eval2(numbers[1], symbols[j], eval2(numbers[2], symbols[k], numbers[3]));

                sum = eval2(numbers[0], symbols[i], sum);
                if(sum == 24){
                    printf("%d %c (%d %c (%d %c %d))\n", numbers[0], symbols[i], numbers[1], symbols[j], numbers[2], symbols[k], numbers[3]);
                    count++;
                }
            }
        }
    }
    
    return count;
}

int bruteForce(int numbers[4]){
    int countSolution = 0;
    int numbersSum = numbers[0] + numbers[1] + numbers[2] + numbers[3];

    List cekUrutan;
    CreateList(&cekUrutan);

    int tempNumbers[4] = {0, 0, 0, 0};
    for(int k1=1; k1<=4; k1++){
        for(int k2=1; k2<=4; k2++){
            if(k2 == k1) continue;
            for(int k3=1; k3<=4; k3++){
                if(k3 == k2 || k3 == k1) continue;
                tempNumbers[0] = numbers[k1-1];
                tempNumbers[1] = numbers[k2-1];
                tempNumbers[2] = numbers[k3-1];
                tempNumbers[3] = numbersSum - tempNumbers[0] - tempNumbers[1] - tempNumbers[2];
                
                // printf("---- %d %d %d %d ----\n", tempNumbers[0], tempNumbers[1], tempNumbers[2], tempNumbers[3]);
                insertLast(&cekUrutan, tempNumbers);
                // printList(cekUrutan);
                // printf("\n");
                // printf("%d %d %d %d -- tempNumbers\n", tempNumbers[0], tempNumbers[1], tempNumbers[2], tempNumbers[3]);
            }
        }
    }

    Address p = cekUrutan;
    while(p != NULL){
        countSolution += kasusKurung2(p->info);
        p = NEXT(p);
    }
    
    return countSolution;
}

int main(){
    CreateList(&listAns);

    printf("Silahkan pilih!\n1. Input sendiri\n2. Random\n");
    int pilihan;
    scanf("%d", &pilihan);

    int ans;
    int k[4];
    clock_t start_time, end_time;

    if(pilihan == 1){
        readInput(k);
    } else if(pilihan == 2){
        srand(time(NULL));
        
        for(int i=0; i<4; i++){
            k[i] = (rand() % 13) + 1;
        }
    }

    printf("%d %d %d %d\n", k[0], k[1], k[2], k[3]);

    start_time = clock();
    ans = bruteForce(k);
    end_time = clock();

    printf("banyaknya solusi - %d\n", ans);
    printf("waktu eksekusi - %fs\n", ((double) (end_time - start_time) / CLOCKS_PER_SEC));

    printf("\nMau tulis ke file? YES (1) or NO (2)\n");
    int isSave;
    scanf("%d", &isSave);

    if(isSave == 1){
        printf("Masukkan nama file\n");
        char filename[100];
        scanf("%s", filename);

        FILE *fptr;
        fptr = fopen(filename, "w");
        fprintf(fptr, "Input Masukan: ");
        fprintf(fptr, "%s %s %s %s\n", validInput[k[0]-1], validInput[k[1]-1], validInput[k[2]-1], validInput[k[3]-1]);
        fprintf(fptr, "Solusi: %d ditemukan!\n", ans);
    }
    return 0;
}