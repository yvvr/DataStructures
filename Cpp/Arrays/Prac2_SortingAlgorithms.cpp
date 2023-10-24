/**
 * @file Prac2_SortingAlgorithms.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-25
 *
 * @copyright Copyright (c) 2023
 *
 * Sorting algorithms
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

// Approch 1 : Selection Sort
// Description: Selection sort is a simple and efficient sorting algorithm that works by repeatedly selecting the smallest (or largest)
// element from the unsorted portion of the list and moving it to the sorted portion of the list.
// Time complexity -> O(n^2), Space complexity -> O(1)

void selectionSort(std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        if (i != min)
        {
            std::swap(arr[i], arr[min]);
        }
    }
}

void stableSelectionSort(std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        if (i != min)
        {
            int temp = arr[min];
            for (int k = min; k > i; k--)
            {
                arr[k] = arr[k - 1];
            }
            arr[i] = temp;
        }
    }
}

// Approch 2 : Bubble Sort
// Description: Bubble Sort is the simplest sorting algorithm that works
// by repeatedly swapping the adjacent elements if they are in the wrong order.
// Time complexity -> O(n^2), Space complexity -> O(1)

void bubbleSort(std::vector<int> &arr)
{
    for (int i = arr.size() - 1; i > 0; i--)
    {
        bool swapped = false;
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }
}

// Approch 3 : Insertion Sort
// Description: To sort an array of size N in ascending order iterate over the array and compare the current element (key) to its predecessor,
// if the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.
// Time complexity -> O(n^2), Space complexity -> O(1)

void insertionSort(std::vector<int> &arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        int temp = arr[i], j;
        for (j = i - 1; j >= 0 && arr[j] > temp; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

// Approch 4 : Quick Sort
// Description: QuickSort is a sorting algorithm based on the Divide and Conquer algorithm that picks an element
// as a pivot and partitions the given array around the picked pivot by placing the pivot in its correct position in the sorted array.
// Time complexity [Worst case] -> O(n^2), [Best, Average case] -> O(nlogn), Space complexity -> O(1)

int partition(std::vector<int> &arr, int l, int r)
{
    int i = l - 1;
    int key = arr[r];

    for (int j = l; j < r; j++)
    {
        if (arr[j] < key)
        {
            std::swap(arr[++i], arr[j]);
        }
    }
    if (i != r)
    {
        std::swap(arr[++i], arr[r]);
    }
    return i;
}

int partition_r(std::vector<int> &arr, int l, int r)
{
    srand(time(NULL));
    int rand = l + std::rand() % (r - l);

    std::swap(arr[rand], arr[r]);
    return partition(arr, l, r);
}

void quickSort(std::vector<int> &arr, int i, int j)
{
    if (i < j)
    {
        int piKey = partition_r(arr, i, j);
        quickSort(arr, i, piKey - 1);
        quickSort(arr, piKey + 1, j);
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
    std::vector<int> arr = {64, 25, 12, 22, 11};
    std::vector<int> arr2 = {64, 25, 12, 22, 11};
    std::vector<int> arr3 = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> arr4 = {12, 11, 13, 5, 6};
    std::vector<int> arr5 = {10, 7, 8, 9, 1, 5};

    std::cout << "Sorted Array (selectionSort):" << std::endl;
    selectionSort(arr);
    print(arr);

    std::cout << "Sorted Array (stableSelectionSort):" << std::endl;
    stableSelectionSort(arr2);
    print(arr2);

    std::cout << "Sorted Array (bubbleSort):" << std::endl;
    bubbleSort(arr3);
    print(arr3);

    std::cout << "Sorted Array (insertionSort):" << std::endl;
    insertionSort(arr4);
    print(arr4);

    std::cout << "Sorted Array (quickSort):" << std::endl;
    quickSort(arr5, 0, arr5.size() - 1);
    print(arr5);

    return 0;
}