'''
 * @file Prob5_MaximumSum(SticklerThief).py
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 *
 * Given an array arr[] of positive numbers, 
 * The task is to find the maximum sum of a subsequence such that no 2 numbers in the sequence should be adjacent in the array.
 * 
 * Input: arr[] = {5, 5, 10, 100, 10, 5}
 * Output: 110
 * Explanation: Pick the subsequence {5, 100, 5}.
 * The sum is 110 and no two elements are adjacent. This is the highest possible sum.
 * 
 * Input: arr[] = {3, 2, 7, 10}
 * Output: 13
 * Explanation: The subsequence is {3, 10}. This gives sum = 13.
 * This is the highest possible sum of a subsequence following the given criteria
'''


def findMaxSum(nums):
    sum2 = 0
    sum1 = 0

    for num in nums:
        temp = max(num + sum2, sum1)
        sum1, sum2 = temp, sum1

    return sum1


if __name__ == "__main__":
    arr = [5, 5, 10, 100, 10, 5]
    print("Max Sum:", findMaxSum(arr))
