#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    
    float arr[n];
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    
    sort(arr, arr+n);
    
    if(n % 2){
        printf("%.1f\n", arr[n/2]);
    } else {
        printf("%.1f\n", (arr[n/2] + arr[n/2-1])/2);
    }
    return 0;
}