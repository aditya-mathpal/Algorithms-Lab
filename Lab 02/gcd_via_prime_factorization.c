#include<stdio.h>
#include<stdlib.h>

int* sieve_of_eratosthenes(int n, int* pCount, int* opcount) {
    int* arr = (int*)calloc((n-1),sizeof(int));
    int count = 0;

    for(int i = 0; (i+2)*(i+2) <= n; i++) {
        (*opcount)++;
        int num = i+2;
        if (arr[i] == 0) {
            for(int j = num * num; j <= n; j += num) {
                (*opcount)++;
                arr[j-2] = 1;
            }
        }
    }
    
    for(int i = 0; i < n - 1; i++) {
        (*opcount)++;
        if(arr[i] == 0) count++;
    }

    int* primes = (int*)malloc(count*sizeof(int));
    int index = 0;
    for(int i = 0; i < n - 1; i++) {
        (*opcount)++;
        if(arr[i] == 0) primes[index++] = i + 2;
    }

    free(arr);
    *pCount = count;
    return primes;
}

int gcd(int a, int b, int* opcount) {
    (*opcount)++;
    int x = a<b?a:b, result = 1, pCount;
    int* arr = sieve_of_eratosthenes(x,&pCount,opcount);

    for(int i = 0; i < pCount; i++) {
        (*opcount)++;
        if(a%arr[i] ==0 && b%arr[i] == 0) {
            result *= arr[i];
            a /= arr[i];
            b /= arr[i];
            i--;
        }
    }

    return result;
}

int main() {
    printf("Enter two numbers to calculate GCD (do not enter 0 or lesser): ");
    int x, y, opcount=0;
    scanf("%d%d",&x,&y);
    printf("GCD is %d\n",gcd(x,y,&opcount));
    printf("%d operations\n",opcount);
    return 0;
}

/*
output:
Enter two numbers to calculate GCD (do not enter 0 or lesser): 12 16
GCD is 4

Time efficiency:
This is quite an inefficient GCD algorithm to compute since the sieve of Eratosthenes has to be implemented to generate all required prime numbers and then further each one has to be checked whether it is a factor of both inputs.
*/