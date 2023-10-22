/**
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
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

bool twoSum(std::vector<int> arr, int sum)
{
    std::unordered_set<int> hashSet;

    for (int i = 0; i < arr.size(); i++)
    {
        if (hashSet.find(sum - arr[i]) != hashSet.end())
        {
            return true;
        }
        hashSet.insert(arr[i]);
    }
    return false;
}

std::vector<int> twoSumWithVec(std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> hashMap;
    std::vector<int> result;

    for (int i = 0; i < nums.size(); i++)
    {
        if (hashMap.find(target - nums[i]) != hashMap.end())
        {
            result.push_back(hashMap[target - nums[i]]);
            result.push_back(i);
            return result;
        }
        hashMap.insert(std::make_pair(nums[i], i));
    }
    return result;
}

int main()
{
    std::vector<int> arr = {0, -1, 2, -3, 1};
    std::vector<int> arr2 = {3, 2, 4};

    std::cout << "Two Sum: " << twoSum(arr, -2) << std::endl;
    std::vector<int> result = twoSumWithVec(arr2, 6);
    if (result.size() != 0)
    {
        std::cout << "Two Sum: [" << result.at(0) << ", " << result.at(1) << "]" << std::endl;
    }
    return 0;
}