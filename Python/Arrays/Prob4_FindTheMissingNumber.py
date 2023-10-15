'''
Find The Missing Number

Given an array arr[] of size N-1 with integers in the range of [1, N],
the task is to find the missing number from the first N integers.
'''

# 1. Finding array sum.
# Time complexity -> O(n), Space Complexity -> O(1)


def findTheMissingNumberUsingSum(arr):
    l = len(arr)
    sum = 0
    for i in range(l):
        sum += arr[i]
    return (l + 2) * (l + 1) // 2 - sum

if __name__ == "__main__":
    arr = [1, 2, 4, 6, 3, 7, 8]
    # Finding array sum
    print("Missing number is:", findTheMissingNumberUsingSum(arr))
