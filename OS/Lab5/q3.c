#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Function prototypes for sorting methods
void bubbleSort(char *strings[], int n);
void selectionSort(char *strings[], int n);
void printStrings(char *strings[], int n);

int main() {
    int n;
     // 1D array of string pointers

    printf("Enter the number of strings (max %d): ", MAX_STRINGS);
    scanf("%d", &n);
    getchar();  // Consume the newline character after scanf

     char *strings[n];

    // Allocate memory for each string

    for (int i = 0; i < n; i++) {
        strings[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", strings[i]);
    }

    // Create the first child process for Bubble Sort
    pid_t pid1 = fork();
    
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid1 == 0) {
        // First child process: perform Bubble Sort
        printf("Child 1 (PID: %d) performing Bubble Sort...\n", getpid());
        bubbleSort(strings, n);
        printf("Sorted strings using Bubble Sort:\n");
        printStrings(strings, n);
        // exit(0);
    }

    // Create the second child process for Selection Sort
    pid_t pid2 = fork();
    
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid2 == 0) {
        // Second child process: perform Selection Sort
        printf("Child 2 (PID: %d) performing Selection Sort...\n", getpid());
        selectionSort(strings, n);
        printf("Sorted strings using Selection Sort:\n");
        printStrings(strings, n);
        // exit(0);
    }

    // Parent process: Wait for any child process to terminate
    int status;
    pid_t terminated_pid = wait(&status);

    if (terminated_pid > 0) {
        printf("Parent process: Child process (PID: %d) terminated.\n", terminated_pid);
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }

    return 0;
}

// Bubble Sort implementation
void bubbleSort(char *strings[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                char *temp = strings[j];
                strings[j] = strings[j + 1];
                strings[j + 1] = temp;
            }
        }
    }
}

// Selection Sort implementation
void selectionSort(char *strings[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(strings[j], strings[minIdx]) < 0) {
                minIdx = j;
            }
        }
        // Swap strings
        if (minIdx != i) {
            char *temp = strings[i];
            strings[i] = strings[minIdx];
            strings[minIdx] = temp;
        }
    }
}

// Function to print strings
void printStrings(char *strings[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
    }
}
