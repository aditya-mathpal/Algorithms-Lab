#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int *begin, int *end) {
    while(begin < --end) swap(begin++, end);
}

int next_permutation(int* begin, int* end) {
    int* i = end;
    if(begin == end || begin == --i) return 0;
    while(1) {
        int* j = i;
        --i;
        if(*i < *j) {
            int* k = end;
            while(!(*i < *--k));
            swap(i, k);
            reverse(j, end);
            return 1;
        }
        if(i == begin) {
            reverse(begin, end);
            return 0;
        }
    }
}

int calculate_cost(int* assignment, int numPeople, int numJobs, int **jobs, int *opcount) {
    int total_cost = 0;
    for(int i = 0; i < numPeople; i++) {
        (*opcount)++;
        if(assignment[i] < numJobs) {
            (*opcount)++;
            total_cost += jobs[i][assignment[i]];
        }
    }
    return total_cost;
}

void find_optimal_assignment(int numPeople, int numJobs, int **jobs, int *opcount) {
    int max_assignment_size = numPeople > numJobs ? numPeople : numJobs;
    int* assignment = (int*)malloc(max_assignment_size * sizeof(int));

    for(int i = 0; i < numPeople; i++)
        assignment[i] = -1;

    int min_cost = __INT_MAX__;
    int* optimal_assignment = (int*)malloc(max_assignment_size * sizeof(int));

    int* job_indices = (int*)malloc(numJobs * sizeof(int));
    for(int i = 0; i < numJobs; i++) {
        (*opcount)++;
        job_indices[i] = i;
    }

    do {
        for(int i = 0; i < numPeople && i < numJobs; i++) {
            (*opcount)++;
            assignment[i] = job_indices[i];
        }

        int current_cost = calculate_cost(assignment, numPeople, numJobs, jobs, opcount);
        if(current_cost < min_cost) {
            min_cost = current_cost;
            for(int i = 0; i < numPeople; i++) {
                (*opcount)++;
                optimal_assignment[i] = assignment[i];
            }
        }

    } while(next_permutation(job_indices, job_indices + numJobs));

    printf("Optimal Assignment:\n");
    for(int i = 0; i < numPeople; i++) {
        if(optimal_assignment[i] < numJobs)
            printf("Person %d takes job %d\n", i + 1, optimal_assignment[i] + 1);
        else
            printf("Person %d is unassigned\n", i + 1);
    }
    printf("Total Cost: %d\n", min_cost);

    free(assignment);
    free(optimal_assignment);
    free(job_indices);
}

int main() {
    int numPeople, numJobs, opcount = 0;

    printf("Enter number of people: ");
    scanf("%d", &numPeople);
    printf("Enter number of jobs: ");
    scanf("%d", &numJobs);

    int** jobs = (int**)malloc(numPeople * sizeof(int*));
    for(int i = 0; i < numPeople; i++)
        jobs[i] = (int*)malloc(numJobs * sizeof(int));

    printf("Enter the cost for each job:\n");
    for(int i = 0; i < numPeople; i++) {
        for(int j = 0; j < numJobs; j++) {
            if(j == i+1 || (i == numPeople - 1 && j == 0))
                jobs[i][j] = 1;
            else
                jobs[i][j] = 99999;
        }
    }

    find_optimal_assignment(numPeople, numJobs, jobs, &opcount);

    for(int i = 0; i < numPeople; i++)
        free(jobs[i]);
    free(jobs);

    printf("%d operations\n", opcount);

    return 0;
}