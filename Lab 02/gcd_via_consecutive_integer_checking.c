#include<stdio.h>
#include<stdlib.h>

int gcd(int a, int b, int* opcount) {
    int x = a<b?a:b;
    if(x<=0) {
        printf("Number too small.\n");
        exit(1);
    }
    while(1) {
        if(a%x == 0 && b%x == 0) {
            (*opcount)++;
            return x;
        }
        else {
            x--;
            (*opcount)++;
        }
    }
}

int main() {
    printf("Enter two numbers to calculate GCD (do not enter 0 or lesser): ");
    int x, y, opcount = 0;
    scanf("%d%d",&x,&y);
    printf("GCD is %d\n",gcd(x,y,&opcount));
    printf("%d operations\n",opcount);
    return 0;
}

/*
output:
Enter two numbers to calculate GCD (do not enter 0 or lesser): 12 16
GCD is 4

time efficiency:
Since it's a brute-force approach, it's quite inefficient as compared to Euclid's algorithm, it has a time complexity of O(min(N,M)) where N and M are the inputs.
*/