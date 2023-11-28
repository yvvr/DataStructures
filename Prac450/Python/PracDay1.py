'''
 * @file PracDay1.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-27
 *
 * @copyright Copyright (c) 2023
 *
'''

'''
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
'''


def reverseArray(arr):
    for i in range(len(arr)//2):
        arr[i], arr[len(arr) - i - 1] = arr[len(arr) - i - 1], arr[i]


'''
 * @brief Given an array (or string), the task is to reverse the array/string using recursion.
 *
 * @param arr - array to be reversed.
'''


def reverseArrayRec(arr, i):
    if i < len(arr) // 2:
        arr[i], arr[len(arr) - i - 1] = arr[len(arr) - i - 1], arr[i]
        reverseArrayRec(arr, i + 1)


'''
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
'''


def findMinAndMaxSum(arr):
    min = float("inf")
    max = float("-inf")
    for i in range(len(arr)):
        if min > arr[i]:
            min = arr[i]
        if max < arr[i]:
            max = arr[i]
    return min + max


if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5, 6, 7, 8]
    # Reverse an Array
    print(arr)
    reverseArray(arr)
    print(arr)

    arr = [64, 34, 25, 12, 22, 11, 90]
    # Reverse an Array with recursion
    print(arr)
    reverseArray(arr)
    print(arr)

    arr = [64, 34, 25, 12, 22, 11, 90]
    # find min, max sum
    print("Min-Max sum:", findMinAndMaxSum(arr))
