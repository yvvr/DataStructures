/**
 * @file Prac3_LeetEasyProblems.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-05
 *
 * Leetcode easy problems.
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>

/**
 * 242. Valid Anagram
 *
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
 *
 * Example 1:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 *
 * Example 2:
 * Input: s = "rat", t = "car"
 * Output: false
 *
 * Constraints:
 * 1 <= s.length, t.length <= 5 * 104
 * s and t consist of lowercase English letters.
 *
 * https://leetcode.com/problems/valid-anagram/
 *
 * @brief check if given two strings are anagrams or not.
 *
 * @return true if it's anagram ortherwise false.
 */

bool isAnagram(std::string s, std::string t)
{
    if (s.length() != t.length())
    {
        return false;
    }
    std::unordered_map<char, int> map1;
    std::unordered_map<char, int> map2;

    for (int i = 0; i < s.length(); i++)
    {
        if (map1.find(s[i]) == map1.end())
        {
            map1[s[i]] = 1;
        }
        else
        {
            map1[s[i]]++;
        }
    }

    for (int i = 0; i < t.length(); i++)
    {
        if (map2.find(t[i]) == map2.end())
        {
            map2[t[i]] = 1;
        }
        else
        {
            map2[t[i]]++;
        }
    }

    std::unordered_map<char, int>::iterator itr;
    for (itr = map1.begin(); itr != map1.end(); itr++)
    {
        if (map2.find(itr->first) == map2.end() || map2[itr->first] != itr->second)
        {
            return false;
        }
    }
    return true;
}

bool isAnagramWithSingleMap(std::string s, std::string t)
{
    if (s.length() != t.length())
    {
        return false;
    }
    std::unordered_map<char, int> map;

    for (int i = 0; i < s.length(); i++)
    {
        map[s[i]]++;
        map[t[i]]--;
    }

    for (auto pair : map)
    {
        if (pair.second != 0)
        {
            return false;
        }
    }
    return true;
}

/**
 *
 * 1. Two Sum
 *
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 * Constraints:
 * 2 <= nums.length <= 104
 * -109 <= nums[i] <= 109
 * -109 <= target <= 109
 *
 * Only one valid answer exists.
 *
 * https://leetcode.com/problems/two-sum/
 *
 * @brief check if two numbers adds up to target in the array
 *
 * @return returns true if pair exits in array otherwise false.
 */

std::vector<int> twoSum(std::vector<int> &nums, int target)
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

/**
 * 53. Maximum Subarray
 *
 * Given an integer array nums, find the subarray with the largest sum, and return its sum.
 *
 * Example 1:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: The subarray [4,-1,2,1] has the largest sum 6.
 *
 * Example 2:
 * Input: nums = [1]
 * Output: 1
 * Explanation: The subarray [1] has the largest sum 1.
 *
 * Example 3:
 * Input: nums = [5,4,-1,7,8]
 * Output: 23
 * Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 *
 * Constraints:
 * 1 <= nums.length <= 105
 * -104 <= nums[i] <= 104
 *
 * https://leetcode.com/problems/maximum-subarray/
 *
 * @brief Finds maximum subarray sum in the array
 *
 * @return int returns max sum of subarray
 */

int maxSubArray(std::vector<int> &nums)
{
    int maxSum = INT_MIN, sum = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
        maxSum = std::max(maxSum, sum);
        if (sum < 0)
        {
            sum = 0;
        }
    }
    return maxSum;
}

/**
 *
 * 167. Two Sum II - Input Array Is Sorted
 *
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number.
 * Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 < numbers.length.
 *
 * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
 *
 * The tests are generated such that there is exactly one solution. You may not use the same element twice.
 *
 * Your solution must use only constant extra space.
 *
 * Example 1:
 * Input: numbers = [2,7,11,15], target = 9
 * Output: [1,2]
 * Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
 *
 * Example 2:
 * Input: numbers = [2,3,4], target = 6
 * Output: [1,3]
 * Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
 *
 * Example 3:
 * Input: numbers = [-1,0], target = -1
 * Output: [1,2]
 * Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
 *
 * Constraints:
 * 2 <= numbers.length <= 3 * 104
 * -1000 <= numbers[i] <= 1000
 * numbers is sorted in non-decreasing order.
 * -1000 <= target <= 1000
 * The tests are generated such that there is exactly one solution.
 *
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * @brief check if two numbers adds up to target in the sorted array.
 *
 * @return returns list of indices of the two numbers that adds up to sum
 */

std::vector<int> twoSum2(std::vector<int> &numbers, int target)
{
    int i = 0, j = numbers.size() - 1;
    while (i < j)
    {
        int sum = numbers[i] + numbers[j];
        if (sum == target)
        {
            return {i + 1, j + 1};
        }
        else if (sum > target)
        {
            j--;
        }
        else
        {
            i++;
        }
    }
    return {};
}

/**
 * 21. Merge Two Sorted Lists
 * 
 * You are given the heads of two sorted linked lists list1 and list2.
 * 
 * Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
 * 
 * Return the head of the merged linked list.
 * 
 * Example 1:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 * 
 * Example 2:
 * Input: list1 = [], list2 = []
 * Output: []
 * 
 * Example 3:
 * Input: list1 = [], list2 = [0]
 * Output: [0]
 * 
 * @brief Merges the two lists into one sorted list
 * 
 * @return ListNode* returns the head of the merged linked list.
 */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    ListNode *head = new ListNode();
    ListNode *temp = head;

    while (list1 && list2)
    {
        if (list1->val < list2->val)
        {
            temp->next = list1;
            list1 = list1->next;
        }
        else
        {
            temp->next = list2;
            list2 = list2->next;
        }
        temp = temp->next;
    }

    if (list1)
    {
        temp->next = list1;
    }
    if (list2)
    {
        temp->next = list2;
    }
    // Delete dummy node.
    temp = head;
    head = head->next;
    delete(temp);

    return head;
}

void printListNode(ListNode *head)
{
    std::cout << "Merged List Node:" << std::endl;
    while (head)
    {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

/**
 * 121. Best Time to Buy and Sell Stock
 * 
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * 
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 * 
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 * 
 * Example 1:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 * Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
 * 
 * Example 2:
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transactions are done and the max profit = 0.
 * 
 * Constraints:
 * 1 <= prices.length <= 105
 * 0 <= prices[i] <= 104
 * 
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * 
 * @brief Calculatest the maximum profit by buying and selling stock with given price array.
 * 
 * @return int return the maximum profit you can achieve from this transaction
 */

int maxProfit(std::vector<int> &prices)
{
    int i = 0, j = 0;
    int maxProfit = 0;

    while (j < prices.size())
    {
        int profit = prices[j] - prices[i];
        if (profit > 0)
        {
            maxProfit = std::max(maxProfit, profit);
            j++;
        }
        else
        {
            i = j;
            j++;
        }
    }
    return maxProfit;
}

/**
 * 88. Merge Sorted Array
 * 
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
 * 
 * Merge nums1 and nums2 into a single array sorted in non-decreasing order.
 * 
 * The final sorted array should not be returned by the function, but instead be stored inside the array nums1.
 * To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
 * 
 * Example 1:
 * Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 * Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
 * The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
 * 
 * Example 2:
 * Input: nums1 = [1], m = 1, nums2 = [], n = 0
 * Output: [1]
 * Explanation: The arrays we are merging are [1] and [].
 * The result of the merge is [1].
 * 
 * Example 3:
 * Input: nums1 = [0], m = 0, nums2 = [1], n = 1
 * Output: [1]
 * Explanation: The arrays we are merging are [] and [1].
 * The result of the merge is [1].
 * 
 * Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
 * 
 * https://leetcode.com/problems/merge-sorted-array/
 * 
 * @brief Merges two integer arrays.
 * 
 * @return null 
 */

void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n)
{
    int i = m - 1, j = n - 1;
    int k = m + n - 1;
    while (i >= 0 && j >= 0)
    {
        if (nums1[i] >= nums2[j])
        {
            nums1[k] = nums1[i];
            i--;
        }
        else
        {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
    while (j >= 0)
    {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}

void printVec(std::vector<int> arr)
{
    std::cout << "Nums 1: ";
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // Is Anagram
    std::cout << "Is Anagram :" << isAnagram("anagram", "nagaram") << std::endl;
    std::cout << "Is Anagram :" << isAnagramWithSingleMap("anagram", "nagaram") << std::endl;
    // Two sum
    std::vector<int> arr = {0, -1, 2, -3, 1};
    std::vector<int> result = twoSum(arr, 3);
    if (result.size() != 0)
    {
        std::cout << "Two Sum: [" << result.at(0) << ", " << result.at(1) << "]" << std::endl;
    }
    // Maximum Subarray
    std::vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "Maximum subarray: " << maxSubArray(arr1) << std::endl;
    // Two Sum 2
    std::vector<int> arr2 = {0, -1, 2, -3, 1};
    std::vector<int> result2 = twoSum(arr2, 3);
    std::cout << "Two Sum2: [" << result2.at(0) << ", " << result2.at(1) << "]" << std::endl;
    // Merge two sorted lists
    ListNode * list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);
    ListNode * list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    ListNode * resultNode = mergeTwoLists(list1, list2);
    printListNode(resultNode);
    // Buy and Sell Stock
    std::vector<int> prices = {7,1,5,3,6,4};
    std::cout << "Maximum profit: " << maxProfit(prices) << std::endl;
    // Merge Sorted Array
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    std::vector<int> nums2 = {2, 5, 6};
    std::cout << "Merge Sorted Array (Before): "<< std::endl;
    printVec(nums1);
    merge(nums1, 3, nums2, 3);
    std::cout << "Merge Sorted Array (After): "<< std::endl;
    printVec(nums1);

    return 0;
}