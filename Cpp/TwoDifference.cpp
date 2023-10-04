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

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

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

int twoDifference(vector<int> arr, int k)
{
    int count = 0;

    sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size(); i++)
    {
        while(i - 1 >= 0 && arr[i] == arr[i - 1]) i++;
        if (i < arr.size() && (binarySearch(arr, i + 1, arr.size() - 1, arr[i] + k) != -1 || binarySearch(arr, 0, i - 1, arr[i] + k) != -1))
        {
            count++;
        }
    }
     return count;
}

int main()
{
    // Test input 1
    vector<int> arr1 = {8, 15, 19, 19, 4};
    int k1 = 8;

    cout << "Test1: " << twoDifference(arr1, k1) << endl;

    return 0;
}