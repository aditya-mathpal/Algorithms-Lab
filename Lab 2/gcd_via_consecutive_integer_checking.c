#include<stdio.h>
#include<stdlib.h>

int gcd(int a, int b) {
    int x = a<b?a:b;
    if(x<=0) {
        printf("Number too small.\n");
        exit(1);
    }
    while(1) {
        if(a%x == 0 && b%x == 0) return x;
        else x--;
    }
}

int main() {
    printf("Enter two numbers to calculate GCD (do not enter 0 or lesser): ");
    int x, y;
    scanf("%d%d",&x,&y);
    printf("GCD is %d",gcd(x,y));
    return 0;
}

/*
output:
Enter two numbers to calculate GCD (do not enter 0 or lesser): 12 16
GCD is 4
*/