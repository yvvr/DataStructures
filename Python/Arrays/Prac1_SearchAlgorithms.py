import math

# Method 1: linear search algorithm


def searchElement(arr, n):
    for i in range(0, len(arr)):
        if (arr[i] == n):
            return i
    return -1

# Method 2: binary search algorithm


def binarySearch(arr, i, j, num):
    if i > j:
        return -1
    mid = i + (j - i) // 2
    if arr[mid] == num:
        return i
    elif arr[mid] > num:
        return binarySearch(arr, i, mid - 1, num)
    else:
        return binarySearch(arr, mid + 1, j, num)

# Method 3: sentinal linear search algorithm


def sentinelLinearSearch(arr, num):
    l = len(arr)
    last = arr[l - 1]
    arr[l-1] = num
    i = 0
    while (arr[i] is not num):
        i += 1
    arr[l-1] = last
    if (i < l-1 or arr[l-1] == num):
        return i
    return -1

# Method 4: meta binary search algorithm


def metaBinarySearch(arr, num):
    l = len(arr)
    largest = int(math.log2(l-1)) + 1
    pos = 0

    for i in range(largest - 1, -1, -1):
        if (arr[pos] == num):
            return pos

        new_pos = pos | (1 << i)

        if ((new_pos < l) and (arr[new_pos] <= num)):
            pos = new_pos

    return pos if (arr[pos] == num) else -1

# Method 5: ternary search algorithm


def ternarySearch(arr, num):

    def ts(arr, i, j, num):
        if i > j:
            return -1
        mid1 = i + (j-i)//3
        mid2 = j - (j-i)//3
        if arr[mid1] == num:
            return mid1
        if arr[mid2] == num:
            return mid2
        if arr[mid1] > num:
            return ts(arr, i, mid1-1, num)
        elif arr[mid2] < num:
            return ts(arr, mid2+1, j, num)
        else:
            return ts(arr, mid1+1, mid2-1, num)

    return ts(arr, 0, len(arr) - 1, num)

# Method 6: jump search algorithm


def jumpSearch(arr, num):
    l = len(arr)
    step = int(math.sqrt(l))
    prev = 0
    next = step

    while arr[min(next, l)-1] < num:
        prev = next
        next += step
        if prev >= l:
            return -1

    while arr[prev] < num:
        prev += 1
        if prev == min(next, l):
            return -1

    return prev if arr[prev] == num else -1

# Method 7: linear interpolation search algorithm


def linearInterpolation(arr, num):

    def lInterpolate(arr, i, j, num):
        if i > j:
            return -1

        pos = i + ((num - arr[i]) // (arr[j] - arr[i])) * (j - i)

        if arr[pos] == num:
            return pos
        elif arr[pos] < num:
            return lInterpolate(arr, pos + 1, j, num)
        else:
            return lInterpolate(arr, i, pos - 1, num)

    return lInterpolate(arr, 0, len(arr) - 1, num)

# Method 8: exponential search algorithm


def exponentialSearch(arr, num):
    l = len(arr)
    if arr[0] == num:
        return 0
    pos = 1
    while pos < l and arr[pos] < num:
        pos *= 2

    return binarySearch(arr, pos // 2, min(pos, l - 1), num)

# Method 9: fibonacci search


def fibonacciSearch(arr, num):
    l = len(arr)
    fibm2 = 0
    fibm1 = 1
    fibm = fibm1 + fibm2

    while fibm < l:
        fibm2 = fibm1
        fibm1 = fibm
        fibm = fibm1 + fibm2

    offset = -1
    while fibm > 1:
        i = min(offset + fibm2, l - 1)
        if arr[i] == num:
            return i
        elif arr[i] < num:
            fibm = fibm1
            fibm1 = fibm2
            fibm2 = fibm - fibm1
            offset = i
        else:
            fibm = fibm2
            fibm1 = fibm1 - fibm2
            fibm2 = fibm - fibm1
    return offset + 1 if fibm1 == 1 and arr[offset + 1] == num else -1


if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5, 6, 7, 8]
    # linear search
    print("Element is at:", searchElement(arr, 5))
    # binary search
    print("Element is at:", binarySearch(arr, 0, len(arr) - 1, 7))
    # sentinel linear search
    print("Element is at:", sentinelLinearSearch(arr, 3))
    # meta binary search
    print("Element is at:", metaBinarySearch(arr, 2))
    # ternary search
    print("Element is at:", ternarySearch(arr, 7))
    # jump search
    print("Element is at:", jumpSearch(arr, 3))
    # linear interpolate search
    print("Element is at:", linearInterpolation(arr, 7))
    # exponential search
    print("Element is at:", exponentialSearch(arr, 2))
    # exponential search
    print("Element is at:", fibonacciSearch(arr, 4))
