/**
 * @file Prob1_FindFloorValueinArray.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-12
 *
 * @copyright Copyright (c) 2023
 *
 *  Given an array of N distinct integers,
 *  find floor value of input ‘key’. Say, A = {-1, 2, 3, 5, 6, 8, 9, 10} and key = 7,
 *  we should return 6 as outcome.
 *
 */

#include <iostream>
#include <vector>
#include <climits>

int binarySearch(std::vector<int> arr, int i, int j, int num)
{
    while (i < j)
    {
        int mid = i + (j - i) / 2;
        if (arr[mid] == num)
            break;
        else if (arr[mid] < num)
            i = mid + 1;
        else
            j = mid - 1;
    }
    return arr[i];
}

int binarySearchFloor(std::vector<int> arr, int i, int j, int num)
{
    if (arr[i] > num)
    {
        return INT_MIN;
    }
    if (arr[j] < num)
    {
        return arr[j];
    }
    while (i < j - 1)
    {
        int mid = i + (j - i) / 2;

        // Combine the < && == operator,
        // as we know there won't arr[mid] == num.
        if (arr[mid] <= num)
            i = mid;
        else
            j = mid;
    }
    return arr[i];
}

int main()
{
    std::vector<int> arr = {-2, 2, 3, 5, 6, 8, 9, 12};
    std::cout << "Floor Value is: " << binarySearchFloor(arr, 0, arr.size() - 1, 7) << std::endl;
    return 0;
}