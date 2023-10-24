'''
 * @file Prac2_SortingAlgorithms.py
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-25
 *
 * @copyright Copyright (c) 2023
 *
 * Sorting algorithms
'''

import random

# Approch 1 : Selection Sort
# Description: Selection sort is a simple and efficient sorting algorithm that works by repeatedly selecting the smallest (or largest)
# element from the unsorted portion of the list and moving it to the sorted portion of the list.
# Time complexity -> O(n^2), Space complexity -> O(1)


def selectionSort(arr):
    for i in range(len(arr)):
        min = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min]:
                min = j
        if i != min:
            arr[i], arr[min] = arr[min], arr[i]


def stableSelectionSort(arr):
    for i in range(len(arr)):
        min = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min]:
                min = j
        if i != min:
            temp = arr[min]
            for k in range(min, i, -1):
                arr[k] = arr[k - 1]
            arr[i] = temp

# Approch 2 : Bubble Sort
# Description: Bubble Sort is the simplest sorting algorithm that works
# by repeatedly swapping the adjacent elements if they are in the wrong order.
# Time complexity -> O(n^2), Space complexity -> O(1)


def bubbleSort(arr):
    for i in range(len(arr) - 1, 0, -1):
        swapped = False
        for j in range(0, i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break

# Approch 3 : Insertion Sort
# Description: To sort an array of size N in ascending order iterate over the array and compare the current element (key) to its predecessor,
# if the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.
# Time complexity -> O(n^2), Space complexity -> O(1)


def insertionSort(arr):
    for i in range(1, len(arr)):
        temp = arr[i]
        for j in range(i-1, -1, -1):
            if arr[j] > temp:
                arr[j + 1] = arr[j]
            else:
                break
        arr[j + 1] = temp

# Approch 4 : Quick Sort
# Description: QuickSort is a sorting algorithm based on the Divide and Conquer algorithm that picks an element
# as a pivot and partitions the given array around the picked pivot by placing the pivot in its correct position in the sorted array.
# Time complexity [Worst case] -> O(n^2), [Best, Average case] -> O(nlogn), Space complexity -> O(1)


def quickSort(arr):

    def partition(arr, l, r):
        i = l - 1
        key = arr[r]
        for j in range(l, r):
            if arr[j] < key:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        if i != r:
            arr[i + 1], arr[j] = arr[j], arr[i + 1]
        return i + 1
    
    def partition_r(arr, l, r):
        rand = random.randrange(l, r)
        arr[rand], arr[r] = arr[r], arr[rand]

        return partition(arr, l, r)

    def sort(arr, i, j):
        if i < j:
            piKey = partition_r(arr, i, j)
            sort(arr, i, piKey - 1)
            sort(arr, piKey + 1, j)

    sort(arr, 0, len(arr) - 1)


if __name__ == "__main__":
    arr = [64, 25, 12, 22, 11]
    arr2 = [64, 25, 12, 22, 11]
    arr3 = [64, 34, 25, 12, 22, 11, 90]
    arr4 = [12, 11, 13, 5, 6]
    arr5 = [10, 7, 8, 9, 1, 5]

    # Selection Sort
    print("Sorted Array (selectionSort):")
    selectionSort(arr)
    print(arr)
    # Stable Selection Sort
    print("Sorted Array (stableSelectionSort):")
    stableSelectionSort(arr2)
    print(arr2)

    # for i in range(10, 3, -1):
    #     print(i, end=' ')
    # for i in range(3, 10)[::-1]:
    #     print(i, end=' ')

    # Bubble Sort
    print("Sorted Array (bubbleSort):")
    bubbleSort(arr3)
    print(arr3)
    # Insertion Sort
    print("Sorted Array (insertionSort):")
    bubbleSort(arr4)
    print(arr4)
    # Insertion Sort
    print("Sorted Array (quickSort):")
    bubbleSort(arr5)
    print(arr5)
