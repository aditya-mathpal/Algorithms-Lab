#include<stdio.h>
#include<string.h>

void shiftTable(char* pattern, int* table) {
    int i, m = strlen(pattern);
    for(i = 0; i < 256; i++) table[i] = m;
    for(i = 0; i < m-1; i++) table[pattern[i]] = m - 1 - i;
}

int horspool(char* text, char* pattern, int* table) {
    shiftTable(pattern, table);
    int m = strlen(pattern), n = strlen(text), k, i;
    for(int i = m - 1; i < n; i += table[(unsigned char)text[i]]) {
        for(k = 0; k < m && pattern[m - 1 - k] == text[i - k]; k++);
        if(k == m) return i - m + 1;
    }
    return -1;
}

int main() {
    char text[1000], pattern[100];
    int table[256];
    printf("Enter the string to be searched in: ");
    fgets(text, 1000, stdin);
    printf("Enter string to be searched for: ");
    fgets(pattern, 100, stdin);
    text[strcspn(text, "\n")] = pattern[strcspn(pattern, "\n")] = 0;

    int index = horspool(text, pattern, table);
    if(index != -1) printf("Pattern found at index %d.\n", index);
    else printf("Pattern not found in string.\n");
    return 0;
}

/*
output:
Enter the string to be searched in: the quick brown fox jumps over the lazy dog
Enter string to be searched for: ck br 
Pattern found at index 7.
*/