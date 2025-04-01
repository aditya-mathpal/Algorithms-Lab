#include<stdio.h>
#include<string.h>

void shiftTable(char* pattern, int* table) {
    int i, m = strlen(pattern);
    for(i = 0; i < 256; i++) table[i] = m;
    for(i = 0; i < m-1; i++) table[pattern[i]] = m - 1 - i;
}

int horspool(char* text, char* pattern, int* table, int* comp) {
    shiftTable(pattern, table);
    int m = strlen(pattern), n = strlen(text), k, i;
    for(int i = m - 1; i < n; i += table[(unsigned char)text[i]]) {
        for(k = 0; k < m && pattern[m - 1 - k] == text[i - k]; k++) (*comp)++;
        if(k == m) return i - m + 1;
    }
    return -1;
}

int main() {
    char text[1000], pattern[100];
    int table[256], comp = 0;
    printf("Enter the string to be searched in: ");
    fgets(text, 1000, stdin);
    printf("Enter string to be searched for: ");
    fgets(pattern, 100, stdin);
    text[strcspn(text, "\n")] = pattern[strcspn(pattern, "\n")] = 0;

    int index = horspool(text, pattern, table, &comp);
    if(index != -1) printf("Pattern found at index %d\n", index);
    else printf("Pattern not found in string\n");
    printf("Number of comparisons: %d\n", comp);
    return 0;
}

/*
output (successful search):
Enter the string to be searched in: test string
Enter string to be searched for: t st
Pattern found at index 3
Number of comparisons: 6

output (unsuccessful search):
Enter the string to be searched in: test string
Enter string to be searched for: abcd
Pattern not found in string
Number of comparisons: 0
*/