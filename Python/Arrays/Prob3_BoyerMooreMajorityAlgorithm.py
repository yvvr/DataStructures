# Boyer-Moore Majority Voting Algorithm

def findMajorityNumber(arr):
    l = len(arr)
    votes = 0
    candidate = -1

    for i in range(l):
        if votes == 0:
            candidate = arr[i]
            votes += 1
        else:
            if arr[i] == candidate:
                votes += 1
            else:
                votes -= 1

    count = 0
    for i in range(l):
        if (arr[i] == candidate):
            count += 1

    return candidate if count > l // 2 else -1


if __name__ == "__main__":
    arr = [1, 1, 2, 2, 2, 2, 2, 4, 5]
    print("Majority number:", findMajorityNumber(arr))
