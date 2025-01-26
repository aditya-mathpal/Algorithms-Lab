#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int calculateSum(int *set, int *subset, int n, int bool, int *opcount) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        (*opcount)++;
        if(bool && subset[i]) sum += set[i];
        else if(!bool && !subset[i]) sum += set[i];
    }
    return sum;
}

void partitionProblem(int *set, int n) {
    int totalSubsets = pow(2, n), found = 0, opcount = 0;

    for(int i = 0; i < totalSubsets; i++) {
        int *subset = (int*)malloc(n*sizeof(int));

        for(int j = 0; j < n; j++) {
            opcount++;
            subset[j] = (i & (1 << j)) ? 1 : 0;
        }

        int subsetSum = calculateSum(set, subset, n, 1, &opcount);
        int complementSum = calculateSum(set, subset, n, 0, &opcount);

        if(subsetSum == complementSum) {
            found = 1;
            printf("Partition Found:\nSubset 1: ");
            for(int j = 0; j < n; j++)
                if(subset[j]) printf("%d ", set[j]);
            printf("\nSubset 2: ");
            for(int j = 0; j < n; j++)
                if(!subset[j]) printf("%d ", set[j]);
            printf("\n%d operations\n", opcount);
            break;
        }
    }

    if(!found)
        printf("No partition found.\n%d operations", opcount);
}

int main() {
    printf("Enter number of elements in the set: ");
    int n, *set;
    scanf("%d", &n);
    set = (int*)malloc(n*sizeof(int));
    printf("Enter elements of the array: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &set[i]);
    partitionProblem(set, n);
    free(set);
    return 0;
}

/*
output:
Enter number of elements in the set: 3
Enter elements of the array: 1 2 3
Partition Found:
Subset 1: 1 2
Subset 2: 3
36 operations

time efficiency:
this algorithm is highly inefficient since it has to generate powersets for a given set, which has a time complexity of omega(n), theta(2^n), and O(2^n) where n is the size of the set.

best case:
for any n, the best case is when one of the two resulting sets contains only one element, and that element is the first one in the main set. this results in omega(n) time complexity.

worst case:
for any n, the worst case is when there is no valid partition, this results in all posibilities being tested and gives an O(2^n) time complexity.
*/