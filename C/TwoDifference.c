// Count all distinct pairs with difference equal to k

/*

Input: arr[] = {1, 5, 3, 4, 2}, k = 3
Output: 2
There are 2 pairs with difference 3, the pairs are {1, 4} and {5, 2}

Input: arr[] = {8, 12, 16, 4, 0, 20}, k = 4
Output: 5
There are 5 pairs with difference 4, the pairs are {0, 4}, {4, 8},
{8, 12}, {12, 16} and {16, 20}

*/

// Approach : Sorting + Binary search
// Time complexity -> O(nlogn), Space complexity -> O(1)

#include <stdio.h>
#include <algorithm>

int binarySearch(int arr[], int i, int j, int num)
{
    if (i > j)
        return -1;

    int mid = i + (i - j) / 2;
    if (arr[mid] == num)
        return mid;
    else if (arr[mid] < num)
        return binarySearch(arr, mid + 1, j, num);
    else
        return binarySearch(arr, i, mid - 1, num);
}

int twoDifference(int arr[], int n, int k)
{
    int count = 0;

    sort(arr, arr + n);

    for (int i = 0; i < n; i++)
    {
        if (binarySearch(arr, i + 1, n - 1, arr[i] + k) != -1 || binarySearch(arr, 0, i - 1, arr[i] + k) != -1)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    // Test input 1
    int arr1[] = {1, 5, 3, 4, 2};
    int k1 = 3;
    // Test input 1
    int arr2[] = {8, 12, 16, 4, 0, 20};
    int k2 = 4;

    printf("Test1: %d", twoDifference(arr1, sizeof(arr1) / sizeof(arr1[0]), k1));
    printf("Test2: %d", twoDifference(arr2, sizeof(arr2) / sizeof(arr2[0]), k2));

    return 0;
}