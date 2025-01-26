#include<stdio.h>
#include<string.h>

int main() {
	char str[100], sub[50];
	int opcount = 0;
	printf("Enter string: ");
	fgets(str,100,stdin);
	str[strlen(str)-1] = 0;
	printf("Enter substring to search: ");
	fgets(sub,50,stdin);
	sub[strlen(sub)-1] = 0;
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

/*
output:
Enter string: the quick brown fox jumps over the lazy dog
Enter substring to search: dog
Searching "dog" in "the quick brown fox jumps over the lazy dog"
First occurrence of string "dog" found at index 40
43 operations

time efficiency:
Due to how the comparisions are made, this algorithm's efficiency depends a lot on the case, it has omega(m), theta(n*m) and O((n-m+1)*m) time complexity, where n and m are the lengths of the main string and substring respectively.
*/