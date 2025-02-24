/*
Problem statement:
Use a recursive decrease-and-conquer approach to calculate the GCD of all elements per row of a matrix.
Print the GCD for each row.
*/

#include<stdio.h>
#include<stdlib.h>

int GCD(int x, int y) {
    if(x == 0) return y;
    return GCD(y%x, x);
}

void rowGCD(int** mat, int n, int m, int recur, int* results) {
    if(recur == m) return;
    int g = mat[recur][0];
    for(int i = 1; i < n; i++)
        g = GCD(g, mat[recur][i]);
    results[recur] = g;
    rowGCD(mat, n, m, recur+1, results);
}

int main() {
    int n, m;
    printf("Enter number of rows:\n");
    scanf("%d", &m);
    printf("Enter number of columns:\n");
    scanf("%d", &n);
    int** mat = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++)
        mat[i] = (int*)malloc(n * sizeof(int));
    
    printf("\nEnter elements of the matrix:\n");
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    printf("\nEntered matrix is:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            printf("%d\t", mat[i][j]);
        printf("\n");
    }
    printf("\n");

    int* results = (int*)malloc(n * sizeof(int));

    rowGCD(mat, n, m, 0, results);
    for(int i = 0; i < m; i++)
        printf("GCD of row %d: %d\n", i+1, results[i]);
    
    return 0;
}

/*
output:
Enter number of rows:
2
Enter number of columns:
3

Enter elements of the matrix:
240 72 48 360 180 90

Entered matrix is:
240     72      48
360     180     90

GCD of row 1: 24
GCD of row 2: 90
*/