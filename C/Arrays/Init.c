#include <stdio.h>
#include <limits.h>

#define ARRAY_LENGTH 5

int sumOfArray(int arr[])
{
    int sum = 0;
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        sum += arr[i];
        arr[i] += 10;
    }
    return sum;
}

int lengthOfArray(int *arr)
{
    return *(&arr + 1) - arr;
}

float getAverage(int *arr)
{
    int sum = 0;
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        sum += *(arr + i);
    }
    return (float)sum / ARRAY_LENGTH;
}

int getLargest(int *arr)
{
    int max = INT_MIN;
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        if (max < *(arr + i))
        {
            max = arr[i];
        }
    }
    return max;
}

int *getArray()
{
    static int arr[ARRAY_LENGTH] = {15, 25, 35, 45, 55};
    return arr;
}

int main()
{
    printf("Hello world!!, Welcome to C Arrays\n");

    int arr[5];

    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        scanf("%d", &arr[i]);
    }

    int ptrArr[5] = {10, 20, 30, 40, 50};

    int *ptrToArr = &ptrArr[0];

    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        arr[i] += 1;
    }

    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Length of Array: %d\n", size);

    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        printf("Array[%d] value: %d\n", i, arr[i]);
    }

    printf("\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        printf("Array[%d] Address: %d, value: %d\n", i, ptrToArr, *ptrToArr++);
    }

    printf("\n");
    printf("Sum of ptrArr: %d", sumOfArray(ptrArr));

    printf("\n");
    ptrToArr = &ptrArr[0];
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        printf("Array[%d] Address: %d, value: %d\n", i, ptrToArr, *ptrToArr++);
    }

    printf("\n");
    ptrToArr = getArray();
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        printf("Array[%d] Address: %d, value: %d\n", i, ptrToArr, *ptrToArr++);
    }

    printf("\n");
    printf("Average value of Array: %f\n", getAverage(arr));

    printf("\n");
    printf("Max value of Array: %d\n", getLargest(arr));

    return 0;
}