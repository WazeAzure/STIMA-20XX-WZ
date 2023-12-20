#include <stdio.h>
#include "util.c"

char validInput[13][2] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

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

void readInput(int* k1, int *k2, int *k3, int *k4){
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
    
    *k1 = inp[]

    printf("%s %s %s %s", inp[0], inp[1], inp[2], inp[3]);
}

int main(){
    int k1, k2, k3, k4;
    readInput(&k1, &k2, &k3, &k4);

    // printf("%d %d %d %d\n", k1, k2, k3, k4);
    
    return 0;
}