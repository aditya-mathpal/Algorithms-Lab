#include<stdio.h>
#include<string.h>

int main() {
	char str[100], sub[50];
    printf("Enter length of string and substring: ");
    int n, m, opcount = 0;
    scanf("%d%d", &n, &m);
	printf("Setting string and substring: ");
    // best case is when the substring is at the beginning of the main string
	for(int i = 0; i < n; i++) {
        str[i] = 'a';
        if(i < m) sub[i] = 'a';
    }
    str[n] = 0;
    sub[m] = 0;
	printf("Searching %s in %s\n",sub,str);
	for(int i = 0; i <= strlen(str) - strlen(sub); i++) {
        opcount++;
		if(str[i] == sub[0]) {
			int j;
			for(j = 1; j < strlen(sub); j++) {
                opcount++;
				if(str[i+j] != sub[j]) break;
			}
			if(j == strlen(sub)) {
				printf("First occurance of string \"%s\" found at index %d\n%d operations\n",sub,i,opcount);
				break;
			}
		}
	}
	return 0;
}