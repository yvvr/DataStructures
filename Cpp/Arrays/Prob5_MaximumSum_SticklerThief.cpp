/**
 * @file Prob5_MaximumSum(SticklerThief).cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 * Given an array arr[] of positive numbers,
 * The task is to find the maximum sum of a subsequence such that no 2 numbers in the sequence should be adjacent in the array.
 *
 * Input: arr[] = {5, 5, 10, 100, 10, 5}
 * Output: 110
 * Explanation: Pick the subsequence {5, 100, 5}.
 * The sum is 110 and no two elements are adjacent. This is the highest possible sum.
 *
 * Input: arr[] = {3, 2, 7, 10}
 * Output: 13
 * Explanation: The subsequence is {3, 10}. This gives sum = 13.
 * This is the highest possible sum of a subsequence following the given criteria
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Approch 1: Using Simple Recursion.
// Time complexity -> O(2^n), Space Complexity -> O(n)

int dfsHelper(std::vector<int> arr, int i)
{
    if (i >= arr.size())
    {
        return 0;
    }
    return std::max(dfsHelper(arr, i + 1), arr[i] + dfsHelper(arr, i + 2));
}

int sumDfs(std::vector<int> arr)
{
    return dfsHelper(arr, 0);
}

// Approch 2: Tabulation method.
// Time complexity -> O(n), Space Complexity -> O(1)

int findMaxSum(int arr[], int n)
{
    if (n == 1)
    {
        return arr[0];
    }
    int sum2 = 0, sum1 = arr[0];
    for (int i = 1; i < n; i++)
    {
        int temp = sum1;
        sum1 = std::max(arr[i] + sum2, sum1);
        sum2 = temp;
    }
    return sum1;
}

int main()
{
    std::vector<int> arr = {5, 5, 10, 100, 10, 5};
    int arr2[] = {5, 5, 10, 100, 10, 5};

    std::cout << "Max Sum: " << findMaxSum(arr2, sizeof(arr2) / sizeof(arr2[0])) << std::endl;
    std::cout << "Max Sum: " << sumDfs(arr) << std::endl;

    return 0;
}