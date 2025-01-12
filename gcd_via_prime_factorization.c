#include<stdio.h>
#include<stdlib.h>

int isPrime(int x) {
    for(int i = 2; i*i <= x; i++) {
        if(x%i == 0) return 0;
    }
    return 1;
}

int gcd(int a, int b) {
    int x = a<b?a:b, result = 1;
    for(int i = 2; i < x; i++) {
        if(isPrime(i)) {
            if(a%i == 0 && b%i == 0) {
                result *= i;
                a /= i;
                b /= i;
                i--;
            }
        }
    }
    return result;
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

Time efficiency:
This is quite an inefficient GCD algorithm to compute since every element has to be checked if it's prime and then further checked whether it's a factor of both inputs. It has a time complexity of O(N^(3/2)) where N is the minimum of the two inputs, making it more inefficient than the consecutive integer checking method.
*/