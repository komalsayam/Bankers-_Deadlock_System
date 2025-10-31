#include <stdio.h> 
#include <stdbool.h>

#define NUM_PROCESSES 3
#define NUM_RESOURCES 3

int main() {
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}  // P2
    };

    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}  // P2
    };

    int available[NUM_RESOURCES] = {3, 3, 2}; 

    int work[NUM_RESOURCES];
    bool finish[NUM_PROCESSES];
    int safeSequence[NUM_PROCESSES];
    int count = 0;

    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < NUM_PROCESSES; i++) {
        finish[i] = false;
    }

    int need[NUM_PROCESSES][NUM_RESOURCES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int p = 0; p < NUM_PROCESSES; p++) {
            if (finish[p] == false) {
                bool canExecute = true;
                for (int r = 0; r < NUM_RESOURCES; r++) {
                    if (need[p][r] > work[r]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int r = 0; r < NUM_RESOURCES; r++) {
                        work[r] += allocation[p][r];
                    }
                    safeSequence[count] = p;
                    finish[p] = true;
                    count++;
                    found = true;
                }
            }
        }

        if (found == false) {
            printf("System is in a deadlocked state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < NUM_PROCESSES; i++) { 
        printf("P%d ", safeSequence[i]);
    } 
    printf("\n");

    return 0;
}
