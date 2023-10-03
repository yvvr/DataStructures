#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 3
#define COL_SIZE 3

int main() {

    // Dynamically allocation of 2D array

    // 1. Using a single pointer and a 1D array.
    // Allocate a memory block of ROW_SIZE x COL_SIZE
    // access the elements with simple pointer arithmetic.

    printf("Method 1:\n");
    int *ptr = (int *)malloc((ROW_SIZE * COL_SIZE) * sizeof(int));

    for (int i = 0; i < ROW_SIZE * COL_SIZE; i++)
    {
        *(ptr + i) = i;
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            printf("%d ", *(ptr + i * COL_SIZE + j));
        }
        printf("\n");
    }
    printf("\n");
    free(ptr);

    // 2. Using arrays of pointers.

    printf("Method 2:\n");

    int *ptr2[ROW_SIZE];
    for (int i = 0; i < ROW_SIZE; i++)
    {
        *(ptr2 + i) = (int *)malloc((COL_SIZE) * sizeof(int));
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            *(*(ptr2 + i) + j) = i * COL_SIZE + j;
        }
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            printf("%d ", *(*(ptr2 + i) + j));
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < ROW_SIZE; i++)
    {
        free(*(ptr2 + i));
    }

    // 3. Using pointer to pointer.
    // create array of pointers dynamically using double pointer.

    printf("Method 3:\n");

    int **ptr3 = (int **)malloc(ROW_SIZE * sizeof(int *));

    for (int i = 0; i < ROW_SIZE; i++)
    {
        *(ptr3 + i) = (int *)malloc((COL_SIZE) * sizeof(int));
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            *(*(ptr3 + i) + j) = i * COL_SIZE + j;
        }
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            printf("%d ", *(*(ptr3 + i) + j));
        }
        printf("\n");
    }
    printf("\n");
    free(ptr3);

    // 4. Using double pointer and one malloc call.

    printf("Method 4:\n");

    int **ptr4 = (int **)malloc(ROW_SIZE * sizeof(int *) + (COL_SIZE * ROW_SIZE) * sizeof(int));

    int *arr = (int *)(ptr4 + ROW_SIZE);

    for (int i = 0; i < ROW_SIZE; i++)
    {
        *(ptr4 + i) = arr + i * COL_SIZE;
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            *(*(ptr4 + i) + j) = i * COL_SIZE + j;
        }
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            printf("%d ", *(*(ptr4 + i) + j));
        }
        printf("\n");
    }
    printf("\n");
    free(ptr4);

    // 5. Using pointer to variable length Array (VLA).

    printf("Method 5:\n");

    int(*ptr5)[ROW_SIZE][COL_SIZE] = malloc(sizeof(*ptr5));

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            *(*(*ptr5 + i) + j) = i * COL_SIZE + j;
        }
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            printf("%d ", *(*(*ptr5 + i) + j));
        }
        printf("\n");
    }
    printf("\n");
    free(ptr5);

    // 6. Using pointer to first row of VLA.

    printf("Method 6:\n");

    int(*ptr6)[COL_SIZE] = malloc(ROW_SIZE * sizeof(*ptr6));

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            *(*(ptr6 + i) + j) = i * COL_SIZE + j;
        }
    }

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            printf("%d ", *(*(ptr6 + i) + j));
        }
        printf("\n");
    }
    printf("\n");
    free(ptr6);

    return 0;
}