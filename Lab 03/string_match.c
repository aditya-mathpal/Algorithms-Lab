#include<stdio.h>
#include<string.h>

int main() {
	char str[100], sub[50];
	printf("Enter string: ");
	fgets(str,100,stdin);
	str[strlen(str)-1] = 0;
	printf("Enter substring to search: ");
	fgets(sub,50,stdin);
	sub[strlen(sub)-1] = 0;
	printf("Searching %s in %s\n",sub,str);
	for(int i = 0; i < strlen(str) - strlen(sub); i++) {
		printf("test\n");
		if(str[i] == sub[0]) {
			printf("inner test\n");
			int j;
			for(j = 0; j < strlen(sub); j++) {
				if(str[i+j] != sub[j]) break;
			}
			if(j == strlen(sub)) {
				printf("String found at %d\n",i);
				break;
			}
		}
	}
	return 0;
}