#include <stdbool.h>
#include <string.h>

// Prototype for the comparison function
typedef int (*CompareFunc)(void* arg1, void* arg2);

bool seqSearch(void* ary, int sizeofElem, int numElem, CompareFunc compare) {
    // Convert the array to a byte pointer for pointer arithmetic
    char* array = (char*) ary;

    // Iterate over each element in the array
    for (int i = 0; i < numElem; i++) {
        // Get the pointer to the current element
        void* currentElem = (void*) (array + i * sizeofElem);

        // Use the compare function to check if the current element is the target
        if (compare(currentElem, ary) == 0) {
            return true;
        }
    }

    // If the loop completes, the target was not found
    return false;
}

// Example of a comparison function
int compareInts(void* arg1, void* arg2) {
    int int1 = *((int*) arg1);
    int int2 = *((int*) arg2);

    if (int1 < int2) return -1;
    if (int1 > int2) return 1;
    return 0;
}

// Main function to test the sequential search
int main() {
    int array[] = {1, 2, 3, 4, 5};
    int numElem = sizeof(array) / sizeof(array[0]);
    int target = 3;

    // Set the target element at the beginning of the array
    int tempArray[numElem + 1];
    tempArray[0] = target;
    memcpy(tempArray + 1, array, numElem * sizeof(int));

    bool found = seqSearch(tempArray, sizeof(int), numElem, compareInts);

    if (found) {
        printf("Element found.\n");
    } else {
        printf("Element not found.\n");
    }

    return 0;
}
