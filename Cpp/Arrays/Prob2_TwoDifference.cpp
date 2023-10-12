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

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

// Method 1 - Naive approach
// Run two loops to check the pairs with difference equals to k.
int twoDifferentNaiveApproach(vector<int> arr, int k)
{
    int count = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[i] - arr[j] == k || arr[j] - arr[i] == k)
            {
                count++;
            }
        }
    }
    return count;
}

int binarySearch(vector<int> arr, int i, int j, int num)
{
    if (i > j)
        return -1;

    int mid = i + (j - i) / 2;
    if (arr[mid] == num)
        return mid;
    else if (arr[mid] < num)
        return binarySearch(arr, mid + 1, j, num);
    else
        return binarySearch(arr, i, mid - 1, num);
}

// Method 2 - Using Sort O(nlogn) + n Binary search (logn).
// Sort the array with Quick sort and search for the pairs with difference equals to k.
// Time complexity -> O(nlogn), Space complexity -> O(1)
int twoDifferenceWithBinarySearch(vector<int> arr, int k)
{
    int count = 0;

    sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size(); i++)
    {
        while (i - 1 >= 0 && arr[i] == arr[i - 1])
            i++;
        if (i < arr.size() && (binarySearch(arr, i + 1, arr.size() - 1, arr[i] + k) != -1 || binarySearch(arr, 0, i - 1, arr[i] + k) != -1))
        {
            count++;
        }
    }
    return count;
}

// Method 3 - Using Sort O(nlogn) & single linear search O(n)
// Sort the array with Quick sort and search for the pairs with difference equals to k.
// Time complexity -> O(nlogn), Space complexity -> O(1)
// Won't work for duplicates.
int twoDifferenceWithSingeLinearSearch(vector<int> arr, int k)
{
    int count = 0;

    sort(arr.begin(), arr.end());

    int i = 0, j = 0;
    while (j < arr.size())
    {
        if (arr[j] - arr[i] == k)
        {
            count++;
            i++;
            j++;
        }
        else if (arr[j] - arr[i] < k)
        {
            j++;
        }
        else
        {
            i++;
        }
    }
    return count;
}

// Method 4 - Using Hashing O(1) & single linear search O(n)
// Use hashing data structure and search for the pairs with difference equals to k.
// Time complexity -> O(n), Space complexity -> O(n)

int twoDifferenceWithHashing(vector<int> arr, int k)
{
    int count = 0;
    unordered_map<int, int> hashMap;

    for (int i = 0; i < arr.size(); i++)
    {
        if (hashMap.find(arr[i]) != hashMap.end())
        {
            hashMap[arr[i]]++;
        }
        else
        {
            hashMap[arr[i]] = 1;
        }
    }

    for (int i = 0; i < arr.size(); i++)
    {
        if (i < arr.size() && hashMap.find(arr[i]) != hashMap.end())
        {
            if (k == 0)
            {
                if (hashMap[arr[i]] != 1)
                {
                    count++;
                }
            }
            else
            {
                if (hashMap.find(arr[i] + k) != hashMap.end())
                {
                    count++;
                }
                if (hashMap.find(arr[i] - k) != hashMap.end())
                {
                    count++;
                }
            }
            hashMap.erase(arr[i]);
        }
    }
    return count;
}

int main()
{
    // Test input 1
    vector<int> arr1 = {1, 2, 3, 4, 5, 6};
    int k1 = 0;

    cout << "Test(twoDifferentNaiveApproach): " << twoDifferentNaiveApproach(arr1, k1) << endl;
    cout << "Test(twoDifferenceWithBinarySearch): " << twoDifferenceWithBinarySearch(arr1, k1) << endl;
    cout << "Test(twoDifferenceWithSingeLinearSearch): " << twoDifferenceWithSingeLinearSearch(arr1, k1) << endl;
    cout << "Test(twoDifferenceWithHashing): " << twoDifferenceWithHashing(arr1, k1) << endl;

    return 0;
}