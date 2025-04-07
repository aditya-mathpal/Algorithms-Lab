/*
problem statement:
https://leetcode.com/problems/longest-common-subsequence/description/
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int x, int y) {
    return x>y?x:y;
}

int lcs(char* s1, char* s2, int** table) {
    int a = strlen(s1), b = strlen(s2);
    for(int i = 0; i <= a; i++) {
        for(int j = 0; j <= b; j++) {
            if(i == 0 || j == 0) table[i][j] = 0;
            else if(s1[i-1] == s2[j-1]) table[i][j] = table[i-1][j-1] + 1;
            else table[i][j] = max(table[i-1][j], table[i][j-1]);
        }
    }
    return table[a][b];
}

int main() {
    char s1[100], s2[100];
    printf("Enter first string: ");
    fgets(s1, 100, stdin);
    s1[strlen(s1)-1] = 0; // remove newline
    printf("Enter second string: ");
    fgets(s2, 100, stdin);
    s2[strlen(s2)-1] = 0; // remove newline
    int a = strlen(s1), b = strlen(s2);

    int** table = (int**)malloc((a+1) * sizeof(int*));
    for(int i = 0; i <= a; i++) table[i] = (int*)malloc((b+1) * sizeof(int));

    printf("The length of LCS = %d\n", lcs(s1, s2, table));
}

/*
output:
Enter first string: AGBGTAB
Enter second string: GXTXAXB
The length of LCS = 4

a proper test case:
Enter first string: AYBYCYDY
Enter second string: XAXXXXBXXXCXXXDXXX
The length of LCS = 4
*/