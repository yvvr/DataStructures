# Count all distinct pairs with difference equal to k

'''
Input: arr[] = {1, 5, 3, 4, 2}, k = 3
Output: 2
There are 2 pairs with difference 3, the pairs are {1, 4} and {5, 2} 

Input: arr[] = {8, 12, 16, 4, 0, 20}, k = 4
Output: 5
There are 5 pairs with difference 4, the pairs are {0, 4}, {4, 8}, 
{8, 12}, {12, 16} and {16, 20}

'''

# Approach : Sorting + Binary search
# Time complexity -> O(nlogn), Space complexity -> O(1)


def binarySearch(arr, i, j, num):
    if (i > j):
        return -1
    mid = i + (j-i) // 2
    if (arr[mid] == num):
        return mid
    elif (arr[mid] < num):
        return binarySearch(arr, mid+1, j, num)
    else:
        return binarySearch(arr, i, mid-1, num)


def twoDifference(arr, k):
    count = 0

    # sort the array
    arr.sort()

    for i in range(len(arr)):
        if (binarySearch(arr, i+1, len(arr)-1, arr[i] + k) != -1 or binarySearch(arr, 0, i-1, arr[i] + k) != -1):
            count += 1

    return count


if __name__ == "__main__":
    # Test input 1
    arr1 = [1, 5, 3, 4, 2]
    k1 = 3
    # Test input 2
    arr2 = [8, 12, 16, 4, 0, 20]
    k2 = 4

    print(twoDifference(arr1, k1))
    print(twoDifference(arr2, k2))
