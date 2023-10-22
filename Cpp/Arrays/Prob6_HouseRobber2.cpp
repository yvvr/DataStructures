/**
 * @file Prob6_HouseRobber2.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed.
 * All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Example 1:
 * Input: nums = [2,3,2]
 * Output: 3
 * Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
 * Example 2:
 * Input: nums = [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 * Total amount you can rob = 1 + 3 = 4.
 * Example 3:
 * Input: nums = [1,2,3]
 * Output: 3
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Approch 1: Tabulation method.
// Time complexity -> O(n), Space Complexity -> O(1)

int sumHelper(std::vector<int> &nums, int l, int r)
{
    int sum2 = 0, sum1 = nums[l];
    for (int i = l + 1; i < r; i++)
    {
        int temp = sum1;
        sum1 = std::max(nums[i] + sum2, sum1);
        sum2 = temp;
    }
    return sum1;
}

int findMaxSum(std::vector<int> &nums)
{
    if (nums.size() == 1)
    {
        return nums[0];
    }
    return std::max(sumHelper(nums, 0, nums.size() - 1), sumHelper(nums, 1, nums.size()));
}

int main()
{
    std::vector<int> arr = {0};

    std::cout << "Max Sum: " << findMaxSum(arr) << std::endl;
    return 0;
}