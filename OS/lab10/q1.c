#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100

void fifo(int *referenceString, int numPages, int numFrames) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    int pageFaults = 0, i, j, k, flag;

    for (i = 0; i < numFrames; i++) {
        frames[i] = -1; // Initialize frames
    }

    for (i = 0; i < numPages; i++) {
        flag = 0;
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == referenceString[i]) {
                flag = 1; // Page hit
                break;
            }
        }

        if (!flag) {
            frames[pageFaults % numFrames] = referenceString[i]; // Replace the oldest page
            pageFaults++;
        }

        // Display current frames
        printf("Frames after reference %d: ", referenceString[i]);
        for (k = 0; k < numFrames; k++) {
            if (frames[k] != -1) {
                printf("%d ", frames[k]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
    free(frames);
}

void optimal(int *referenceString, int numPages, int numFrames) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    int pageFaults = 0, i, j, k, flag, farthest;

    for (i = 0; i < numFrames; i++) {
        frames[i] = -1; // Initialize frames
    }

    for (i = 0; i < numPages; i++) {
        flag = 0;
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == referenceString[i]) {
                flag = 1; // Page hit
                break;
            }
        }

        if (!flag) {
            // Find the page to replace
            int replaceIndex = 0;
            farthest = -1;

            for (j = 0; j < numFrames; j++) {
                int found = 0;
                for (k = i + 1; k < numPages; k++) {
                    if (frames[j] == referenceString[k]) {
                        found = 1;
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                if (!found) {
                    replaceIndex = j; // If page not found, select this for replacement
                    break;
                }
            }
            frames[replaceIndex] = referenceString[i]; // Replace page
            pageFaults++;
        }

        // Display current frames
        printf("Frames after reference %d: ", referenceString[i]);
        for (k = 0; k < numFrames; k++) {
            if (frames[k] != -1) {
                printf("%d ", frames[k]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
    free(frames);
}

int main() {
    int numFrames, numPages;
    int *referenceString;

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    referenceString = (int *)malloc(numPages * sizeof(int));
    printf("Enter the page reference string (space-separated): ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &referenceString[i]);
    }

    printf("\nSimulating FIFO Page Replacement:\n");
    fifo(referenceString, numPages, numFrames);

    printf("\nSimulating Optimal Page Replacement:\n");
    optimal(referenceString, numPages, numFrames);

    free(referenceString);
    return 0;
}
