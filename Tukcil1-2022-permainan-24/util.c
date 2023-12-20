#include <stdio.h>

int strLen(char str[]){
    int i=0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int strCompare(char str1[], char str2[]){
    int i=0;
    int len1 = strLen(str1);
    int len2 = strLen(str2);

    if(len1 != len2) return 0;

    while(i < len1){
        if(str1[i] != str2[i]) return 0;
        i++;
    }

    return 1;
}