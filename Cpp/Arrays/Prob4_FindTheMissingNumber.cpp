/**
 * @file Prob4_FindTheMissingNumber.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-15
 *
 * @copyright Copyright (c) 2023
 *
 * Find The Missing Number
 *
 * Given an array arr[] of size N-1 with integers in the range of [1, N].
 * The task is to find the missing number from the first N integers.
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdlib.h>

using namespace std;

// Approch 1: Finding array sum.
// Time complexity -> O(n), Space Complexity -> O(1)

int findTheMissingNumberUsingSum(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return ((size + 1) * (size + 2) / 2) - sum;
}

// Approch 2: Using hash set.
// Time complexity -> O(n), Space Compexity -> O(n)

int findTheMissingUsingHashing(vector<int> arr)
{
    int size = arr.size();
    unordered_set<int> set;

    for (int i = 0; i < size; i++)
    {
        set.insert(arr[i]);
    }

    for (int i = 1; i <= size; i++)
    {
        if (set.find(i) == set.end())
        {
            return i;
        }
    }
    return -1;
}

// Approch 3: Using hash table.
// Time complexity -> O(n), Space Compexity -> O(n)

int findTheMissingNumberUsingArrarHashing(vector<int> arr)
{
    int size = arr.size();
    bool hash[10] = {0};

    for (int i = 0; i < size; i++)
    {
        hash[arr[i] - 1] = 1;
    }

    for (int i = 1; i <= size; i++)
    {
        if (hash[i - 1] == 0)
        {
            return i;
        }
    }
    return -1;
}

// Approch 4: Finding array sum (Modification for overflow).
// Time complexity -> O(n), Space Complexity -> O(1)

int findTheMissingNumberUsingSumModification(vector<int> arr)
{
    int sum = 1;
    int counter = 2;

    for (int i = 0; i < arr.size(); i++)
    {
        sum = sum - arr[i] + counter;
        counter++;
    }
    return sum;
}

// Approch 5: Using In array hashing.
// Time complexity -> O(n), Space Compexity -> O(1)

int findTheMissingNumberUsingInArrarHashing(vector<int> arr)
{
    int size = arr.size();
    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) - 1 == size)
        {
            continue;
        }
        arr[abs(arr[i]) - 1] *= -1;
    }

    int missingNumber = size + 1;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] > 0)
        {
            missingNumber = i + 1;
        }
    }
    return missingNumber;
}

// Approch 6: Using cycling sort.
// Time complexity -> O(n), Space Compexity -> O(1)

int findTheMissingNumberUsingCyclingSort(vector<int> arr)
{
    int size = arr.size();
    int i = 0;

    while (i < size)
    {
        int correctValue = arr[i] - 1;
        if (arr[i] < size && i != correctValue)
        {
            swap(arr[i], arr[correctValue]);
        }
        else
        {
            i++;
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (i != arr[i] - 1)
        {
            return i + 1;
        }
    }

    return size + 1;
}

int main()
{
    int arr[] = {1, 2, 4, 6, 3, 7, 8};
    vector<int> vec = {1, 2, 4, 6, 3, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Finding array sum
    cout << "Missing number is: " << findTheMissingNumberUsingSum(arr, size) << endl;
    // Using hash set
    cout << "Missing number is: " << findTheMissingUsingHashing(vec) << endl;
    // Using hash table
    cout << "Missing number is: " << findTheMissingNumberUsingArrarHashing(vec) << endl;
    // Finding array sum (Modification for overflow)
    cout << "Missing number is: " << findTheMissingNumberUsingSumModification(vec) << endl;
    // Using In array hashing
    cout << "Missing number is: " << findTheMissingNumberUsingInArrarHashing(vec) << endl;
    // Using cycling sort
    cout << "Missing number is: " << findTheMissingNumberUsingCyclingSort(vec) << endl;

    return 0;
}