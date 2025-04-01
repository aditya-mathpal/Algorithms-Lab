#include <stdio.h>
#include<stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int* weights, int* values, int n, int capacity) {
    int** dp = (int**)malloc((n+1) * sizeof(int*));
    for(int i = 0; i <= n; i++)
        dp[i] = (int*)calloc(capacity+1,sizeof(int));
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            else dp[i][w] = dp[i - 1][w];
        }
    return dp[n][capacity];
}

int main() {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);
    int* weights = (int*)malloc(n * sizeof(int));
    int* values = (int*)malloc(n * sizeof(int));
    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &weights[i]);
    printf("Enter values of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &values[i]);
    printf("Enter capacity of knapsack: ");
    scanf("%d", &capacity);
    int maxValue = knapsack(weights, values, n, capacity);
    printf("Maximum value in knapsack: %d\n", maxValue);
    return 0;
}

/*
output:
Enter number of items: 4
Enter weights of items:
2 1 3 2
Enter values of items:
12 10 20 15
Enter capacity of knapsack: 5
Maximum value in knapsack: 37
*/