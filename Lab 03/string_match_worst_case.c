#include<stdio.h>
#include<string.h>

int main() {
	char str[100], sub[50];
    printf("Enter length of string and substring: ");
    int n, m, opcount = 0;
    scanf("%d%d", &n, &m);
	printf("Setting string and substring: ");
    // worst case is when the substring is at the end of the main string and only the last character of both are distinct from all other characters
	// also for any n, m = (n+1)/2 gives the worst case time efficiency (round off to either side in case of even n)
	for(int i = 0; i < n - 1; i++) {
        str[i] = 'a';
        if(i < m - 1) sub[i] = 'a';
    }
    str[n-1] = 'b';
    sub[m-1] = 'b';
    str[n] = 0;
    sub[m] = 0;
	printf("Searching \"%s\" in \"%s\"\n",sub,str);
	for(int i = 0; i <= strlen(str) - strlen(sub); i++) {
		opcount++;
		if(str[i] == sub[0]) {
			int j;
			for(j = 1; j < strlen(sub); j++) {
				opcount++;
				if(str[i+j] != sub[j]) break;
			}
			if(j == strlen(sub)) {
				printf("First occurrence of string \"%s\" found at index %d\n%d operations",sub,i,opcount);
				break;
			}
		}
	}
	return 0;
}