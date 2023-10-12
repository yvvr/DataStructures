#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Method 1: Linear search

int linearSearch(int *arr, int len, int num)
{
    for (int i = 0; i < len; i++)
    {
        if (*(arr + i) == num)
        {
            return i;
        }
    }
    return -1;
}

// Method 2: Binary Search

int binarySearch(std::vector<int> arr, int i, int j, int num)
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

// Method 3: Sentinel Linear Search

int sentinalLinearSearch(std::vector<int> arr, int num)
{
    int len = arr.size();
    int last = arr[len - 1];

    arr[len - 1] = num;
    int i = 0;
    while (arr[i] != num)
    {
        i++;
    }
    arr[len - 1] = last;

    if (i < len - 1 || last == num)
    {
        return i;
    }
    return -1;
}

// Method 4: Meta binary search

int metaBinarySearch(std::vector<int> arr, int num)
{
    int len = arr.size();
    int largest = log2(len - 1) + 1;
    int pos = 0;
    for (int i = largest; i >= 0; i--)
    {
        if (arr[pos] == num)
        {
            return pos;
        }

        int newPos = pos | (1 << i);
        if (newPos < len && arr[newPos] <= num)
        {
            pos = newPos;
        }
    }
    return arr[pos] == num ? pos : -1;
}

// Method 5: Ternary search

int ternarySearch(std::vector<int> arr, int i, int j, int num)
{
    if (i > j)
    {
        return -1;
    }
    int mid1 = i + (j - i) / 3;
    int mid2 = j - (j - i) / 3;
    if (arr[mid1] == num)
    {
        return mid1;
    }
    if (arr[mid2] == num)
    {
        return mid2;
    }
    if (arr[mid1] > num)
    {
        return ternarySearch(arr, i, mid1 - 1, num);
    }
    else if (arr[mid2] < num)
    {
        return ternarySearch(arr, mid2 + 1, j, num);
    }
    else
    {
        return ternarySearch(arr, mid1 + 1, mid2 - 1, num);
    }
}

// Method 6: Jump Search

int jumpSearch(std::vector<int> arr, int num)
{
    int len = arr.size() - 1;
    int step = sqrt(arr.size());
    int prev = 0;
    int next = step;

    while (arr[std::min(next, len) - 1] < num)
    {
        prev = next;
        next += step;
        if (prev >= len)
        {
            return -1;
        }
    }

    while (arr[prev] < num)
    {
        prev++;
        if (prev == std::min(next, len))
        {
            return -1;
        }
    }
    return arr[prev] == num ? prev : -1;
}

// Method 7: Linear Interpolation

int linearInterpolation(std::vector<int> arr, int i, int j, int num)
{
    if (i > j)
    {
        return -1;
    }

    int pos = i + ((double)(num - arr[i]) / (arr[j] - arr[i])) * (j - i);

    if (arr[pos] == num)
    {
        return pos;
    }
    else if (arr[pos] < num)
    {
        return linearInterpolation(arr, pos + 1, j, num);
    }
    else
    {
        return linearInterpolation(arr, i, pos - 1, num);
    }
}

// Method 8: exponential search

int exponentialSearch(std::vector<int> arr, int num)
{
    int len = arr.size();

    if (arr[0] == num)
    {
        return 0;
    }
    int pos = 1;
    while (pos < len && arr[pos] < num)
    {
        pos *= 2;
    }
    return binarySearch(arr, pos / 2, std::min(pos, len - 1), num);
}

// Method 9: fibonacci search

int fibonacciSearch(std::vector<int> arr, int num)
{
    int len = arr.size();
    int fibm2 = 0;
    int fibm1 = 1;
    int fibm = fibm1 + fibm2;

    while (fibm < len)
    {
        fibm2 = fibm1;
        fibm1 = fibm;
        fibm = fibm1 + fibm2;
    }

    int offset = -1;
    while (fibm > 1)
    {
        int i = std::min(offset + fibm2, len - 1);

        if (arr[i] == num)
        {
            return i;
        }
        else if (arr[i] < num)
        {
            fibm = fibm1;
            fibm1 = fibm2;
            fibm2 = fibm - fibm1;
            offset = i;
        }
        else
        {
            fibm = fibm2;
            fibm1 = fibm1 - fibm2;
            fibm2 = fibm - fibm1;
        }
    }
    if (fibm1 && arr[offset + 1] == num)
        return offset + 1;
    return -1;
}

int main()
{

    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};

    // linear Search
    std::cout << "Element is at: " << linearSearch(arr, sizeof(arr) / sizeof(arr[0]), 5) << std::endl;
    // binary Search
    std::cout << "Element is at: " << binarySearch(vec, 0, vec.size() - 1, 7) << std::endl;
    // sentinel linear search
    std::cout << "Element is at: " << sentinalLinearSearch(vec, 3) << std::endl;
    // meta binary search
    std::cout << "Element is at: " << metaBinarySearch(vec, 2) << std::endl;
    // ternary search
    std::cout << "Element is at: " << ternarySearch(vec, 0, vec.size() - 1, 7) << std::endl;
    // jump search
    std::cout << "Element is at: " << jumpSearch(vec, 3) << std::endl;
    // linear interpolation search
    std::cout << "Element is at: " << linearInterpolation(vec, 0, vec.size() - 1, 7) << std::endl;
    // exponential search
    std::cout << "Element is at: " << exponentialSearch(vec, 2) << std::endl;
    // fibonacci search
    std::cout << "Element is at: " << fibonacciSearch(vec, 4) << std::endl;

    return 0;
}