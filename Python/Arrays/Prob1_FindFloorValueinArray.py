'''
 Given an array of N distinct integers,
 find floor value of input ‘key’. Say, A = {-1, 2, 3, 5, 6, 8, 9, 10} and key = 7,
 we should return 6 as outcome.
'''


def binarySearch(arr, num):

    def bs(arr, i, j, num):
        if i > j:
            return -1
        mid = i + (j - i) // 2
        if arr[mid] == num:
            return num
        elif arr[mid] > num:
            return bs(arr, i, mid - 1, num)
        else:
            return bs(arr, mid + 1, j, num)

    return bs(arr, 0, len(arr), num)


def binarySearchFloor(arr, num):
    i = 0
    j = len(arr) - 1
    if arr[i] > num:
        return -1
    if arr[j] < num:
        return arr[j]
    while i < j - 1:
        mid = i + (j - i) // 2
        if arr[mid] <= num:
            i = mid
        else:
            j = mid
    return arr[i]


if __name__ == "__main__":
    arr = [-3, 2, 4, 5, 6, 8, 9, 10]
    print("Floor Value is:", binarySearchFloor(arr, -5))
