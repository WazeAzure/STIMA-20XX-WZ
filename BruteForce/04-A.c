#include <stdio.h>
#include <stdlib.h>

void getInput(int *arr, int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            int temp;
            scanf("%d", &temp);
            *(arr + j + (c * i)) = temp;
        }
    }
}

void showArr(int *arr, int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%d ", *(arr + j  + (c * i)));
        }
        printf("\n");
    }
}

int sumbVertikal(int arr[], int arr2[], int r, int c){
    int midC = c/2;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            // printf("%d %d\n", c*i+j, c*i + c-1-j);
            if(arr[(c*i)+j] != arr2[(c*i) + (c-1-j)]){
                return 0;
            }
        }
    }
    return 1;
}

int sumbHorizontal(int arr[], int arr2[], int r, int c){
    int midR = (r)/2;
    for(int j=0; j<c; j++){
        for(int i=0; i<r; i++){
            // printf("%d %d\n", c*i+j, c*(r-1-i) + j);
            if(arr[(c*i)+j] != arr2[(c*(r-1-i)) + j]){
                // printf("called");
                return 0;
            }
        }
    }
    return 1;
}

int identik(int arr[], int arr2[], int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(arr[(c*i) + j] != arr2[(c*i) + j]){
                return 0;
            }
        }
    }
    return 1;
}

int sumbKaBa(int arr[], int arr2[], int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            // printf("%d %d\n", (c*i)+j, i  + (c * j));
            if(arr[(c*i)+j] != arr2[i  + (c * j)]){
                // printf("called");
                return 0;
            }
        }
    }
    return 1;
}

int sumbKiBa(int arr[], int arr2[], int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            // printf("%d %d\n", (c*i)+j, ((r*c)-i-1) - (c*j));
            if(arr[(c * i) + j] != arr2[((r*c)-i-1) - (c*j)]){
                return 0;
            }
        }
    }
    return 1;
}

int main(){
    int r, c;
    scanf("%d %d", &r, &c);
    
    int *arr = (int*)malloc(sizeof(int) * r * c);
    getInput(arr, r, c);
    
    int r2, c2;
    scanf("%d %d", &r2, &c2);
    int *arr2 = (int*)malloc(sizeof(int) * r2 * c2);
    getInput(arr2, r2, c2);
    
    // showArr(arr, r, c);
    // showArr(arr2, r2, c2);

    // different size, no;
    if(r != r2 && c != c2){
        printf("tidak identik\n");
        return 0;
    }

    if(identik(arr, arr2, r, c)){ // identik
        printf("identik\n");
    } else if(sumbVertikal(arr, arr2, r, c)){ // sumb vertikal
        printf("vertikal\n");
    } else if(sumbHorizontal(arr, arr2, r, c)){ // sumb horizontal
        printf("horisontal\n");
    } else if(sumbKiBa(arr, arr2, r, c)){ // sumb kiri bawah
        printf("diagonal kiri bawah\n");
    } else if(sumbKaBa(arr, arr2, r, c)){ // sumb kanan bawah
        printf("diagonal kanan bawah\n");
    } else {
        printf("tidak identik\n");
    }

    free(arr);
    free(arr2);
}