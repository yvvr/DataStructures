#include <stdio.h>

#define ROW_SIZE 3
#define COL_SIZE 3

int main()
{
    int arr[3][3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < ROW_SIZE; j++)
        {
            for (int k = 0; k < COL_SIZE; k++)
            {
                arr[i][j][k] = i * ROW_SIZE * COL_SIZE + (j * COL_SIZE + k);
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < ROW_SIZE; j++)
        {
            for (int k = 0; k < COL_SIZE; k++)
            {
                printf("%d ", *(*(*(arr + i) + j) + k));
            }
            printf("\n");
        }
        printf("\n");
    }

    // 1. Using array and a array pointer (static jagged array)
    int jArr1[] = {1, 2, 3, 4, 5};
    int jArr2[] = {9, 10, 12, 14};

    int *jArr[] = {jArr1, jArr2};
    int size[] = {5, 4};

    printf("Jagged array:\n");
    for (int i = 0; i < 2; i++)
    {
        int *arrPtr = jArr[i];

        for (int j = 0; j < size[i]; j++)
        {
            printf("%d ", *(arrPtr + j));
        }
        printf("\n");
    }
     
    return 0;
}