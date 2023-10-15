/**
 * @file Prob3_BoyerMooreMajorityAlgorithm.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-15
 *
 * @copyright Copyright (c) 2023
 *
 * Boyer-Moore Majority Voting Algorithm
 */

#include <iostream>

using namespace std;

int findMajorityNumber(int *arr, int size)
{

    int votes = 0;
    int candidate = -1;

    for (int i = 0; i < size; i++)
    {
        if (votes > 0)
        {
            if (candidate == arr[i])
            {
                votes++;
            }
            else
            {
                votes--;
            }
        }
        else
        {
            candidate = arr[i];
            votes++;
        }
    }

    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == candidate)
        {
            count++;
        }
    }

    if (count > size / 2)
    {
        return candidate;
    }

    return -1;
}

int main()
{

    int arr[] = {1, 1, 1, 1, 1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Majority Number: " << findMajorityNumber(arr, size);
    return 0;
}