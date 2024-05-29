//
//  main.c
//  DSA Project
//
//  Created by Jaanvi on 15/10/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void minCashFlowRec(int *netAmount, int n, int **answer) {
    int maxCredit = 0, maxDebit = 0;
    for (int i = 1; i < n; i++) {
        if (netAmount[i] > netAmount[maxCredit])
            maxCredit = i;
        if (netAmount[i] < netAmount[maxDebit])
            maxDebit = i;
    }

    if (netAmount[maxCredit] == 0 && netAmount[maxDebit] == 0)
        return;

    int min = (netAmount[maxDebit] < -netAmount[maxCredit]) ? netAmount[maxDebit] : -netAmount[maxCredit];
    netAmount[maxCredit] -= abs(min);
    netAmount[maxDebit] += abs(min);

    answer[maxDebit][maxCredit] = abs(min);

    // Add a base case to ensure termination
    if(netAmount[maxCredit] == 0 || netAmount[maxDebit] == 0)
        return;

    minCashFlowRec(netAmount, n, answer);
}


int** minCashFlow(int **graph, int n) {
    int *netAmount = (int*)calloc(n, sizeof(int));

    for (int p = 0; p < n; p++) {
        for (int i = 0; i < n; i++) {
            netAmount[p] += (graph[i][p] - graph[p][i]);
        }
    }

    int **answer = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        answer[i] = (int*)malloc(n * sizeof(int));
        memset(answer[i], 0, n * sizeof(int));
    }

    minCashFlowRec(netAmount, n, answer);

    return answer;
}

int main(void) {
    int n;
    printf("Enter the number of people: ");
    scanf("%d", &n);

    int **graph = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the names of the people:\n");
    char names[MAX][MAX];
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    int num_debts;
    printf("Enter the number of debts: ");
    scanf("%d", &num_debts);

    printf("Enter the debts in the format 'x y z' where x owes y an amount of z:\n");
    for (int i = 0; i < num_debts; i++) {
        char from, to;
        int amount;
        scanf(" %c %c %d", &from, &to, &amount);
        int from_index = from - 'a', to_index = to - 'a';
        if (from_index >= 0 && from_index < n && to_index >= 0 && to_index < n) {
            graph[from_index][to_index] += amount;
            graph[to_index][from_index] -= amount;
        } else {
            printf("Invalid input, please try again.\n");
            return 1;
        }
    }

    int **result = minCashFlow(graph, n);

    printf("The transactions are as follows:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result[i][j] > 0) {
                printf("Person %c pays %d to Person %c\n", 'a' + i, result[i][j], 'a' + j);
            }
        }
    }

    // free memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
        free(result[i]);
    }
    free(graph);
    free(result);

    return 0;
}
