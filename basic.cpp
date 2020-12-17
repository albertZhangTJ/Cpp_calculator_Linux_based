#include "basic.h"
int combination(int l,int s){
    return factorial(l)/factorial(s)/factorial(l-s);
}
int arrangement(int l,int s){
    return factorial(l)/factorial(l-s);
}
int factorial(int x){
    int ans=1;
    for (int i=1;i<=x;i++){
        ans*=i;
    }
    return ans;
}
