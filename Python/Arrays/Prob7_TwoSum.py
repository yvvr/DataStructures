'''
 * @file Prob7_TwoSum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 * Check if pair with given Sum exists in Array (Two Sum)
 *
 * Given an array A[] of n numbers and another number x, the task is to check whether or not there exist two elements in A[] whose sum is exactly x.
 *
 * Input: arr[] = {0, -1, 2, -3, 1}, x= -2
 * Output: Yes
 * Explanation:  If we calculate the sum of the output,1 + (-3) = -2
 *
 * Input: arr[] = {1, -2, 1, 0, 5}, x = 0
 * Output: No
'''

def twoSum(nums, target):
    hashSet = set()

    for i in range(len(nums)):
        if target - nums[i] in hashSet:
            return True
        hashSet.add(nums[i])

    return False

def twoSumWithDic(nums, target):
    result = []
    hashMap = {}

    for i in range(len(nums)):
        if target - nums[i] in hashMap:
            result.append(hashMap[target - nums[i]])
            result.append(i)
            return result
        hashMap[nums[i]] = i

    return result


if __name__ == "__main__":
    nums = [2, 7, 11, 15]
    print("Two sum:", twoSumWithDic(nums, 9))
    print("Two sum:", twoSum(nums, 9))
