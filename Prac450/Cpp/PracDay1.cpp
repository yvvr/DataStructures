/**
 * @file PracDay1.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <climits>
#include <queue>

/**
 * Write a program to reverse an array or string.
 *
 * Given an array (or string), the task is to reverse the array/string.
 *
 * Examples :
 *
 * Input  : arr[] = {1, 2, 3}
 * Output : arr[] = {3, 2, 1}
 *
 * Input :  arr[] = {4, 5, 1, 2}
 * Output : arr[] = {2, 1, 5, 4}
 */

/**
 * @brief Given an array (or string), the task is to reverse the array/string.
 *
 * @param arr - array to be reversed.
 */
void reverseArray(std::vector<int> &arr)
{
    int n = arr.size() - 1;
    for (int i = 0; i < arr.size() / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - i];
        arr[n - i] = temp;
    }
}

/**
 * @brief Given an array (or string), the task is to reverse the array/string using recursion.
 *
 * @param arr - array to be reversed.
 */
void reverseArrayRec(std::vector<int> &arr, int i)
{
    if (i < arr.size() / 2)
    {
        int temp = arr[i];
        arr[i] = arr[arr.size() - i - 1];
        arr[arr.size() - i - 1] = temp;
        reverseArrayRec(arr, i + 1);
    }
}

/**
 * @brief find the maximum and the minimum element of the array using the minimum number of comparisons.
 *
 * Maximum and minimum of an array using minimum number of comparisons.
 *
 * Given an array of size N. The task is to find the maximum and the minimum element of the array using the minimum number of comparisons.
 *
 * Input: arr[] = {3, 5, 4, 1, 9}
 * Output: Minimum element is: 1, Maximum element is: 9
 *
 * Input: arr[] = {22, 14, 8, 17, 35, 3}
 * Output:  Minimum element is: 3, Maximum element is: 35
 *
 * @param arr - array of elements
 * @return std::pair<int, int> - return pair of numbers represents min and max
 */
std::pair<int, int> findMinAndMax(const std::vector<int> &arr)
{
    int min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < arr.size(); i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
        }
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return std::make_pair(min, max);
}

/**
 * @brief - find the Kth smallest element in the given array
 *
 * Given an array arr[] and an integer K where K is smaller than size of array, the task is to find the Kth smallest element in the given array.
 *
 * It is given that all array elements are distinct.
 *
 * Example 1:
 *
 * Input:
 * N = 6
 * arr[] = 7 10 4 3 20 15
 * K = 3
 * L=0 R=5
 *
 * Output : 7
 *
 * Explanation :
 * 3rd smallest element in the given
 * array is 7.
 *
 * Example 2:
 *
 * Input:
 * N = 5
 * arr[] = 7 10 4 20 15
 * K = 4 L=0 R=4
 *
 * Output : 15
 *
 * Explanation :
 * 4th smallest element in the given array is 15.
 *
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(log(n))
 *
 * Constraints:
 *
 * 1 <= N <= 105
 * L==0
 * R==N-1
 * 1<= arr[i] <= 105
 * 1 <= K <= N
 *
 * @param arr - given array of elements
 * @return int - kth smallest element.
 */
int kthSmallest(std::vector<int> arr, int k)
{
    std::priority_queue<int> queue;
    for (int i = 0; i < arr.size(); i++)
    {
        if (queue.size() < k)
        {
            queue.push(arr[i]);
        }
        else if (arr[i] < queue.top())
        {
            queue.pop();
            queue.push(arr[i]);
        }
    }
    return queue.top();
}

/**
 * @brief
 *
 * Move all negative numbers to beginning and positive to end with constant extra space.
 *
 * An array contains both positive and negative numbers in random order. Rearrange the array elements so that all negative numbers appear before all positive numbers.
 *
 * Examples :
 * Input: -12, 11, -13, -5, 6, -7, 5, -3, -6
 * Output: -12 -13 -5 -7 -3 -6 11 6 5
 *
 * @param arr - array of elements which need to be sorted.
 */
void insertElement(std::vector<int> &arr, int l, int r)
{
    int temp = arr[r];
    for (int i = r; i > l; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[l] = temp;
}

void mergePositiveNegativeNumbers(std::vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *arr1 = new int[n1];
    int *arr2 = new int[n2];

    for (int i = 0; i < n1; i++)
    {
        arr1[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        arr2[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && arr1[i] < 0)
    {
        arr[k++] = arr1[i++];
    }
    while (j < n2 && arr2[j] < 0)
    {
        arr[k++] = arr2[j++];
    }
    while (i < n1)
    {
        arr[k++] = arr1[i++];
    }
    while (j < n2)
    {
        arr[k++] = arr2[j++];
    }
    delete arr1;
    delete arr2;
}

void mergeSortPositiveNegativeNumbers(std::vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSortPositiveNegativeNumbers(arr, l, m);
        mergeSortPositiveNegativeNumbers(arr, m + 1, r);
        mergePositiveNegativeNumbers(arr, l, m, r);
    }
}

void sortPostiveNegativeNumbers(std::vector<int> &arr)
{
    int l = -1;

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < 0)
        {
            insertElement(arr, ++l, i);
        }
    }
}

void print(std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    // Reverse an Array.
    print(arr);
    reverseArray(arr);
    print(arr);

    arr = {10, 7, 8, 9, 1, 5};
    // Reverse an Array using recursion.
    print(arr);
    reverseArrayRec(arr, 0);
    print(arr);

    arr = {64, 34, 25, 12, 22, 11, 90};
    // Find Min and Max.
    std::pair<int, int> result = findMinAndMax(arr);
    std::cout << "Min value: " << result.first << " , Max value: " << result.second << std::endl;

    arr = {64, 34, 25, 12, 22, 11, 90};
    // Find Kth Smallest element.
    std::cout << "Kth Smallest value: " << kthSmallest(arr, 3) << std::endl;

    arr = {-1, 2, -3, 4, 5, 6, -7, 8, 9};
    // Sort positive negative elements.
    sortPostiveNegativeNumbers(arr);
    print(arr);

    arr = {-4, 2, -3, 4, 5, 6, -7, 8, 9};
    // Sort positive negative elements with merge sort.
    mergeSortPositiveNegativeNumbers(arr, 0, arr.size() - 1);
    print(arr);

    return 0;
}