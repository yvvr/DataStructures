/**
 * Copyright (c) 2024
 *
 * Author: Your Name
 * This file is part of the DataStructures project.
 *
 * This file is licensed under the MIT License.
 * You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <cstdint>
#include <cstring>
#include <memory>
#include <queue>
#include <array>
#include <stack>
#include <cctype>
#include <numeric>

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

struct TrieNode
{
    std::unordered_map<char, TrieNode *> childMap;
    bool isWord = false;
};

/**
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings.
 * There are various applications of this data structure, such as autocomplete and spellchecker.
 *
 * https://leetcode.com/problems/implement-trie-prefix-tree/description/
 */
class Trie
{
public:
    TrieNode *root = nullptr;

    Trie()
    {
        root = new TrieNode();
    }

    void insert(std::string word)
    {
        TrieNode *temp = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (temp->childMap.find(word[i]) == temp->childMap.end())
            {
                temp->childMap[word[i]] = new TrieNode();
            }
            temp = temp->childMap[word[i]];
        }
        temp->isWord = true;
    }

    bool search(std::string word)
    {
        TrieNode *temp = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (temp->childMap.find(word[i]) == temp->childMap.end())
            {
                return false;
            }
            temp = temp->childMap[word[i]];
        }
        return temp->isWord;
    }

    bool startsWith(std::string prefix)
    {
        TrieNode *temp = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            if (temp->childMap.find(prefix[i]) == temp->childMap.end())
            {
                return false;
            }
            temp = temp->childMap[prefix[i]];
        }
        return true;
    }
};

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Node
{
public:
    int val;
    std::vector<Node *> neighbors;

    Node()
    {
        val = 0;
        neighbors = std::vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = std::vector<Node *>();
    }
    Node(int _val, std::vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class DSU
{
public:
    std::vector<int> parent;
    std::vector<int> rank;

    DSU(int n)
    {
        parent = std::vector<int>(n);
        rank = std::vector<int>(n, 1);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int node)
    {
        int curr = node;
        while (curr != parent[curr])
        {
            parent[curr] = parent[parent[curr]];
            curr = parent[curr];
        }
        return curr;
    }

    bool unionOp(int u, int v)
    {
        int up = find(u);
        int vp = find(v);
        if (up == vp)
        {
            return false;
        }
        if (rank[vp] > rank[up])
        {
            std::swap(up, vp);
        }
        parent[vp] = up;
        rank[up] += rank[vp];
        return true;
    }
};

class DSUforGrid
{
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int count = 0;

public:
    DSUforGrid(std::vector<std::vector<char>> &grid)
    {
        int row = grid.size(), col = grid[0].size();
        parent = std::vector<int>(row * col);
        rank = std::vector<int>(row * col, 1);
        std::iota(parent.begin(), parent.end(), -1);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                parent[i * col + j] = i * col + j;
                count++;
            }
        }
    }

    int find(int node)
    {
        int curr = node;
        while (curr != parent[curr])
        {
            parent[curr] = parent[parent[curr]];
            curr = parent[curr];
        }
        return curr;
    }

    bool unionOp(int u, int v)
    {
        int up = find(u);
        int vp = find(v);
        if (up == vp)
        {
            return false;
        }
        count--;
        if (rank[vp] > rank[up])
        {
            std::swap(up, vp);
        }
        parent[vp] = up;
        rank[up] += rank[vp];
        return true;
    }

    int getCount()
    {
        return count;
    }
};

class Solution
{
public:
    /**
     * 1. Two Sum
     * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
     * You may assume that each input would have exactly one solution, and you may not use the same element twice.
     * You can return the answer in any order.
     *
     * https://leetcode.com/problems/two-sum/description/
     */
    std::vector<int> twoSum(std::vector<int> &nums, int target)
    {
        std::unordered_map<int, int> map;
        std::vector<int> result;

        for (int i = 0; i < nums.size(); i++)
        {
            if (map.find(target - nums[i]) != map.end())
            {
                result.push_back(map[target - nums[i]]);
                result.push_back(i);
                return result;
            }
            map[nums[i]] = i;
        }
        return result;
    }

    /**
     * 121. Best Time to Buy and Sell Stock.
     * You are given an array prices where prices[i] is the price of a given stock on the ith day.
     * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
     * Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
     *
     * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
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
     * 217. Contains Duplicate.
     * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
     *
     * https://leetcode.com/problems/contains-duplicate/description/
     */
    bool containsDuplicate(std::vector<int> &nums)
    {
        std::unordered_set<int> set;
        for (int i = 0; i < nums.size(); i++)
        {
            if (set.find(nums[i]) != set.end())
            {
                return true;
            }
            set.insert(nums[i]);
        }
        return false;
    }

    /**
     * 238. Product of Array Except Self.
     * Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
     * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
     * You must write an algorithm that runs in O(n) time and without using the division operation.
     *
     * https://leetcode.com/problems/product-of-array-except-self/description/
     */
    std::vector<int> productExceptSelf(std::vector<int> &nums)
    {
        std::vector<int> answer(nums.size());
        int pre = 1, post = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            answer[i] = pre;
            pre *= nums[i];
        }
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            answer[i] *= post;
            post *= nums[i];
        }
        return answer;
    }

    /**
     * 53. Maximum Subarray.
     * Given an integer array nums, find the subarray with the largest sum, and return its sum.
     *
     * https://leetcode.com/problems/maximum-subarray/description/
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
     * 152. Maximum Product Subarray.
     * Given an integer array nums, find a subarray that has the largest product, and return the product.
     * The test cases are generated so that the answer will fit in a 32-bit integer.
     *
     * https://leetcode.com/problems/maximum-product-subarray/description/
     */
    int maxProduct(std::vector<int> &nums)
    {
        int maxProd = INT_MIN;
        int currMax = 1, currMin = 1;
        for (auto num : nums)
        {
            int temp = currMax;
            currMax = std::max(num, std::max(num * currMax, num * currMin));
            currMin = std::min(num, std::min(num * temp, num * currMin));
            maxProd = std::max(maxProd, currMax);
        }
        return maxProd;
    }

    /**
     * 153. Find Minimum in Rotated Sorted Array.
     * Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:
     * [4,5,6,7,0,1,2] if it was rotated 4 times.
     * [0,1,2,4,5,6,7] if it was rotated 7 times.
     *
     * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
     * Given the sorted rotated array nums of unique elements, return the minimum element of this array.
     *
     * You must write an algorithm that runs in O(log n) time.
     *
     * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
     */
    int findMin(std::vector<int> &nums)
    {
        int l = 0, r = nums.size() - 1;
        while (l <= r)
        {
            if (nums[l] <= nums[r])
            {
                return nums[l];
            }

            int mid = (l + r) / 2;
            if (nums[mid] > nums[r])
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        return nums[l];
    }

    /**
     * 33. Search in Rotated Sorted Array.
     * There is an integer array nums sorted in ascending order (with distinct values).
     *
     * Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
     * For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
     *
     * Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
     *
     * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
     */
    int search(std::vector<int> &nums, int target)
    {
        int l = 0, r = nums.size() - 1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }

            if (nums[l] <= nums[mid])
            {
                if (target < nums[mid] && target >= nums[l])
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            else
            {
                if (target > nums[mid] && target <= nums[l])
                {
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }

    /**
     * 15. 3Sum.
     * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
     * Notice that the solution set must not contain duplicate triplets.
     *
     * https://leetcode.com/problems/3sum/description/
     */
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (i == 0 || nums[i - 1] != nums[i])
            {
                int j = i + 1, k = nums.size() - 1;
                while (j < k)
                {
                    int sum = nums[j] + nums[k] + nums[i];
                    if (sum < 0)
                    {
                        j++;
                    }
                    else if (sum > 0)
                    {
                        k--;
                    }
                    else
                    {
                        result.push_back({nums[i], nums[j], nums[k]});
                        j++;
                        k--;
                        while (j < k && nums[j] == nums[j - 1])
                        {
                            j++;
                        }
                    }
                }
            }
        }
        return result;
    }

    /**
     * 11. Container With Most Water.
     * You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
     * Find two lines that together with the x-axis form a container, such that the container contains the most water.
     * Return the maximum amount of water a container can store.
     *
     * https://leetcode.com/problems/container-with-most-water/description/
     */
    int maxArea(std::vector<int> &height)
    {
        int l = 0, r = height.size() - 1;
        int maxArea = INT_MIN;
        while (l < r)
        {
            int area = std::min(height[l], height[r]) * (r - l);
            maxArea = std::max(maxArea, area);
            if (height[r] > height[l])
            {
                l++;
            }
            else
            {
                r--;
            }
        }
        return maxArea;
    }

    /**
     * 371. Sum of Two Integers.
     * Given two integers a and b, return the sum of the two integers without using the operators + and -.
     *
     * https://leetcode.com/problems/sum-of-two-integers/description/
     */
    int getSum(int a, int b)
    {
        int sum = a ^ b;
        int carry = (a & b) << 1;
        while (carry != 0)
        {
            int temp = sum;
            sum = sum ^ carry;
            carry = (temp & carry) << 1;
        }
        return sum;
    }

    /**
     * 191. Number of 1 Bits.
     * Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).
     *
     * https://leetcode.com/problems/number-of-1-bits/description/
     */
    int hammingWeight(int n)
    {
        int count = 0;
        while (n != 0)
        {
            count += n & 1;
            n = n >> 1;
        }
        return count;
    }

    /**
     * 338. Counting Bits.
     * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
     *
     * https://leetcode.com/problems/counting-bits/description/
     */
    std::vector<int> countBits(int n)
    {
        // std::vector<int> result(n + 1, 0);
        // int offset = 1;
        // for (int i = 1; i <= n; i++)
        // {
        //     if (i == offset * 2)
        //     {
        //         offset *= 2;
        //     }
        //     result[i] = 1 + result[i - offset];
        // }
        // return result;

        std::vector<int> result(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            result[i] = result[i >> 1] + (i & 1);
        }
        return result;
    }

    /**
     * 268. Missing Number.
     * Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
     *
     * https://leetcode.com/problems/missing-number/description/
     */
    int missingNumber(std::vector<int> &nums)
    {
        int missing = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            missing ^= i ^ nums[i];
        }
        return missing;
    }

    /**
     * 190. Reverse Bits.
     * Reverse bits of a given 32 bits unsigned integer.
     *
     * https://leetcode.com/problems/reverse-bits/
     */
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t reverse = 0;
        for (int i = 0; i < 32; i++)
        {
            reverse += (n & 1) << (31 - i);
            n = n >> 1;
        }
        return reverse;
    }

    /**
     * 70. Climbing Stairs.
     * You are climbing a staircase. It takes n steps to reach the top.
     * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
     *
     * https://leetcode.com/problems/climbing-stairs/description/
     */
    int climbStairs(int n)
    {
        int n0 = 1, n1 = 1;
        for (int i = 2; i <= n; i++)
        {
            int temp = n1;
            n1 = n0 + n1;
            n0 = temp;
        }
        return n1;
    }

    /**
     * 322. Coin Change.
     * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
     * Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
     *
     * You may assume that you have an infinite number of each kind of coin.
     *
     * https://leetcode.com/problems/coin-change/description/
     */
    int coinChange(std::vector<int> &coins, int amount)
    {
        std::vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (int j = 0; j < coins.size(); j++)
            {
                if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX)
                {
                    dp[i] = std::min(dp[i], 1 + dp[i - coins[j]]);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }

    /**
     * 300. Longest Increasing Subsequence.
     * Given an integer array nums, return the length of the longest strictly increasing subsequence.
     *
     * https://leetcode.com/problems/longest-increasing-subsequence/description/
     */
    int lengthOfLIS(std::vector<int> &nums)
    {
        std::vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
        }
        return *(std::max_element(dp.begin(), dp.end()));
    }

    /**
     * 1143. Longest Common Subsequence.
     * Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
     * A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
     * For example, "ace" is a subsequence of "abcde".
     *
     * A common subsequence of two strings is a subsequence that is common to both strings.
     *
     * https://leetcode.com/problems/longest-common-subsequence/description/
     */
    int longestCommonSubsequence(std::string text1, std::string text2)
    {
        // std::vector<std::vector<int>> dp(text1.size() + 1, std::vector<int>(text2.size() + 1, 0));
        // for (int i = 1; i <= text1.size(); i++)
        // {
        //     for (int j = 1; i <= text2.size(); j++)
        //     {
        //         if (text1[i - 1] == text2[j - 1])
        //         {
        //             dp[i][j] = 1 + dp[i - 1][j - 1];
        //         }
        //         else
        //         {
        //             dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        //         }
        //     }
        // }
        // return dp[text1.size()][text2.size()];

        if (text1.size() < text2.size())
        {
            std::swap(text1, text2);
        }

        std::vector<int> dp(text2.size() + 1, 0);
        for (int i = 1; i <= text1.size(); i++)
        {
            int prev = 0;
            for (int j = 1; j <= text2.size(); j++)
            {
                int temp = dp[j];
                if (text1[i - 1] == text2[j - 1])
                {
                    dp[j] = 1 + prev;
                }
                else
                {
                    dp[j] = std::max(dp[j], dp[j - 1]);
                }
                prev = temp;
            }
        }
        return dp[text2.size()];
    }

    /**
     * 139. Word Break.
     * Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
     *
     * Note that the same word in the dictionary may be reused multiple times in the segmentation.
     *
     * https://leetcode.com/problems/word-break/description/
     */
    bool wordBreak(std::string s, std::vector<std::string> &wordDict)
    {
        std::vector<bool> dp(s.length() + 1, false);
        dp[s.length()] = true;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            for (int j = 0; j < wordDict.size(); j++)
            {
                if (i + wordDict[j].length() > s.length())
                {
                    continue;
                }
                else if (s.substr(i, wordDict[j].length()) == wordDict[j])
                {
                    dp[i] = dp[i + wordDict[j].length()];
                }
                if (dp[i])
                {
                    break;
                }
            }
        }
        return dp[0];
    }

    /**
     * 198. House Robber.
     * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed,
     * the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and
     * it will automatically contact the police if two adjacent houses were broken into on the same night.
     *
     * Given an integer array nums representing the amount of money of each house,
     * return the maximum amount of money you can rob tonight without alerting the police.
     *
     * https://leetcode.com/problems/house-robber/description/
     */
    int rob(std::vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return nums[0];
        }
        int sum2 = 0, sum1 = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            int temp = sum1;
            sum1 = std::max(nums[i] + sum2, sum1);
            sum2 = temp;
        }
        return sum1;
    }

    /**
     * 213. House Robber II.
     * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed.
     * All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one.
     * Meanwhile, adjacent houses have a security system connected,
     * and it will automatically contact the police if two adjacent houses were broken into on the same night.
     *
     * Given an integer array nums representing the amount of money of each house,
     * return the maximum amount of money you can rob tonight without alerting the police.
     *
     * https://leetcode.com/problems/house-robber-ii/description/
     */
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

    int rob2(std::vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return nums[0];
        }
        return std::max(sumHelper(nums, 0, nums.size() - 1), sumHelper(nums, 1, nums.size()));
    }

    /**
     * 377. Combination Sum IV.
     * Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.
     * The test cases are generated so that the answer can fit in a 32-bit integer.
     *
     * https://leetcode.com/problems/combination-sum-iv/description/
     */
    int possibleCombinations(std::vector<int> &nums, int target, std::unordered_map<int, int> &map)
    {
        if (target < 0)
        {
            return 0;
        }

        if (target == 0)
        {
            return 1;
        }

        if (map.find(target) != map.end())
        {
            return map[target];
        }

        int count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            count += possibleCombinations(nums, target - nums[i], map);
        }
        map[target] = count;
        return count;
    }

    int combinationSum4(std::vector<int> &nums, int target)
    {
        std::unordered_map<int, int> map;
        return possibleCombinations(nums, target, map);
    }

    int combinationSum4BottomUp(std::vector<int> &nums, int target)
    {
        std::vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; i++)
        {
            for (int j = 0; j < nums.size(); j++)
            {
                if (target - nums[j] >= 0)
                {
                    dp[i] += dp[target - nums[j]];
                }
            }
        }
        return dp[target];
    }

    /**
     * 62. Unique Paths.
     * There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]).
     * The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.
     *
     * Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
     *
     * The test cases are generated so that the answer will be less than or equal to 2 * 109.
     */
    int uniquePaths(int m, int n)
    {
        std::vector<int> dp(n, 1);
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }

    /**
     * You are given an integer array nums.
     * You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
     *
     * Return true if you can reach the last index, or false otherwise.
     *
     * https://leetcode.com/problems/jump-game/description/
     */
    bool canJump(std::vector<int> &nums)
    {
        int goal = nums.size() - 1;
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            if (nums[i] + i >= goal)
            {
                goal = i;
            }
        }
        return goal == 0;
    }

    /**
     * 91. Decode Ways.
     * You have intercepted a secret message encoded as a string of numbers. The message is decoded via the following mapping:
     *
     * Given a string s containing only digits, return the number of ways to decode it. If the entire string cannot be decoded in any valid way, return 0.
     * The test cases are generated so that the answer fits in a 32-bit integer.
     *
     * https://leetcode.com/problems/decode-ways/description/
     */
    int decode(int i, std::string &s, std::vector<int> &dp)
    {
        if (i > s.length() || s[i] == '0')
        {
            return 0;
        }
        if (i == s.length())
        {
            return 1;
        }
        if (dp[i] != -1)
        {
            return dp[i];
        }
        int count = 0;
        if (std::strchr("123456789", s[i]))
        {
            count += decode(i + 1, s, dp);
        }
        if (s[i] == '1' && std::strchr("0123456789", s[i + 1]) || s[i] == '2' && std::strchr("0123456", s[i + 1]))
        {
            count += decode(i + 2, s, dp);
        }
        dp[i] = count;
        return count;
    }

    int numDecodings(std::string s)
    {
        std::vector<int> dp(s.length(), -1);

        return decode(0, s, dp);
    }

    int numDecodingsIterative(std::string s)
    {
        std::vector<int> dp(s.length() + 1, 0);
        dp[s.length()] = 1;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (std::strchr("123456789", s[i]))
            {
                dp[i] += dp[i + 1];
            }
            if (i + 1 < s.length() && (s[i] == '1' && std::strchr("0123456789", s[i + 1]) || s[i] == '2' && std::strchr("0123456", s[i + 1])))
            {
                dp[i] += dp[i + 2];
            }
        }
        return dp[0];
    }

    /**
     * 297. Serialize and Deserialize Binary Tree
     * Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer,
     * or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
     *
     * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work.
     * You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
     *
     * https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/
     */

    void serializeTree(TreeNode *root, std::string &result)
    {
        if (root == nullptr)
        {
            result += "N#";
            return;
        }
        result += (std::to_string(root->data) + "#");
        serializeTree(root->left, result);
        serializeTree(root->right, result);
    }

    // Encodes a tree to a single string.
    std::string serialize(TreeNode *root)
    {
        std::string result = "";
        serializeTree(root, result);
        return result;
    }

    TreeNode *deserializeTree(int &i, std::string data)
    {
        int end = data.find("#", i);
        std::string nodeVal = data.substr(i, end - i);
        if (end != std::string::npos && nodeVal != "N")
        {
            i = end + 1;
            return nullptr;
        }

        TreeNode *node = new TreeNode(std::stoi(nodeVal));
        i = end + 1;

        node->left = deserializeTree(i, data);
        node->right = deserializeTree(i, data);
        return node;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(std::string data)
    {
        int pos = 0;
        return deserializeTree(pos, data);
    }

    /**
     * 572. Subtree of Another Tree.
     * Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
     * A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
     *
     * https://leetcode.com/problems/subtree-of-another-tree/description/
     */
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if (root == nullptr)
        {
            return false;
        }

        return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

    bool isSameTree(TreeNode *root1, TreeNode *root2)
    {
        if (root1 == nullptr && root2 == nullptr)
        {
            return true;
        }
        if (root1 != nullptr || root2 != nullptr)
        {
            return false;
        }
        return root1->data == root2->data && isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right);
    }

    /**
     * 105. Construct Binary Tree from Preorder and Inorder Traversal
     * Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.
     *
     * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
     */
    int getRootIndex(std::vector<int> &inorder, int value, int il, int ir)
    {
        for (int i = il; i <= ir; i++)
        {
            if (inorder[i] == value)
            {
                return i;
            }
        }
        return ir;
    }

    TreeNode *buildTree(std::vector<int> &preorder, int &preIndex, int pl, int pr, std::unordered_map<int, int> &indices)
    {
        if (pl > pr)
        {
            return nullptr;
        }
        TreeNode *node = new TreeNode(preorder[preIndex++]);
        int mid = indices[preorder[preIndex]];
        node->left = buildTree(preorder, preIndex, pl, mid - 1, indices);
        node->right = buildTree(preorder, preIndex, mid + 1, pr, indices);

        return node;
    }

    TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder)
    {
        std::unordered_map<int, int> indices;
        int preIndex = 0;
        for (int i = 0; i < inorder.size(); i++)
        {
            indices[inorder[i]] = i;
        }
        return buildTree(preorder, preIndex, 0, inorder.size() - 1, indices);
    }

    /**
     * 230. Kth Smallest Element in a BST.
     * Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
     *
     * https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/
     */
    int kthSmallest(TreeNode *root, int &count, int k)
    {
        if (root == nullptr)
        {
            return INT_MAX;
        }

        int leftTree = kthSmallest(root->left, count, k);
        if (++count == k)
        {
            return root->data;
        }
        int rightTree = kthSmallest(root->right, count, k);

        return std::min(leftTree, rightTree);
    }

    int kthSmallest(TreeNode *root, int k)
    {
        int count = 0;
        return kthSmallest(root, count, k);
    }

    /**
     * 235. Lowest Common Ancestor of a Binary Search Tree.
     * Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST..
     *
     * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
     *
     * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
     */
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // if (root->data > p->data && root->data > q->data)
        // {
        //     return lowestCommonAncestor(root->left, p, q);
        // }
        // else if (root->data < p->data && root->data < q->data)
        // {
        //     return lowestCommonAncestor(root->right, p, q);
        // }
        // else
        // {
        //     return root;
        // }

        TreeNode *node = root;
        while (node)
        {
            if (node->data > p->data && node->data > q->data)
            {
                node = node->left;
            }
            else if (node->data < p->data && node->data < q->data)
            {
                node = node->right;
            }
            else
            {
                return node;
            }
        }
        return node;
    }

    /**
     * 212. Word Search II.
     * Given an m x n board of characters and a list of strings words, return all words on the board.
     *
     * Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring.
     * The same letter cell may not be used more than once in a word.
     *
     * https://leetcode.com/problems/word-search-ii/description/
     */
    std::vector<std::string> findWords(std::vector<std::vector<char>> &board, std::vector<std::string> &words)
    {
        Trie trie;
        std::unordered_set<std::string> result;
        std::vector<std::vector<bool>> visited(board.size(), std::vector<bool>(board[0].size(), false));

        for (std::string &word : words)
        {
            trie.insert(word);
        }

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                dfsWordSearch2(board, visited, result, i, j, board.size(), board[0].size(), trie.root, "");
            }
        }

        return std::vector<std::string>(result.begin(), result.end());
    }

    void dfsWordSearch2(std::vector<std::vector<char>> &board, std::vector<std::vector<bool>> &visited, std::unordered_set<std::string> &result, int i, int j, int n, int m, TrieNode *root, std::string word)
    {
        if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] == true || root->childMap[board[i][j]] != nullptr)
        {
            return;
        }

        visited[i][j] = true;
        TrieNode *child = root->childMap[board[i][j]];
        word += board[i][j];
        if (child->isWord)
        {
            result.insert(word);
        }

        dfsWordSearch2(board, visited, result, i + 1, j, n, m, child, word);
        dfsWordSearch2(board, visited, result, i, j + 1, n, m, child, word);
        dfsWordSearch2(board, visited, result, i - 1, j, n, m, child, word);
        dfsWordSearch2(board, visited, result, i, j - 1, n, m, child, word);
        visited[i][j] = false;
    }

    /**
     * 23. Merge k Sorted Lists.
     *
     * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
     * Merge all the linked-lists into one sorted linked-list and return it.
     *
     * https://leetcode.com/problems/merge-k-sorted-lists/description/
     */
    ListNode *mergeKLists(std::vector<ListNode *> &lists)
    {
        if (lists.size() == 0)
        {
            return nullptr;
        }

        while (lists.size() > 1)
        {
            std::vector<ListNode *> result;
            for (int i = 0; i < lists.size(); i += 2)
            {
                ListNode *list1 = lists[i];
                ListNode *list2 = nullptr;
                if (i + 1 < lists.size())
                {
                    list2 = lists[i + 1];
                }
                result.push_back(merge(list1, list2));
            }
            lists = result;
        }
        return lists[0];
    }

    ListNode *merge(ListNode *list1, ListNode *list2)
    {
        if (list1 == nullptr)
        {
            return list2;
        }
        if (list2 == nullptr)
        {
            return list1;
        }

        ListNode *dummy = new ListNode();
        ListNode *temp = dummy;

        while (list1 != nullptr && list2 != nullptr)
        {
            if (list1->val < list2->val)
            {
                temp->next = list1;
                temp = temp->next;
                list1 = list1->next;
            }
            else
            {
                temp->next = list2;
                temp = temp->next;
                list2 = list2->next;
            }
        }

        if (list1 != nullptr)
        {
            temp->next = list1;
        }

        if (list2 != nullptr)
        {
            temp->next = list2;
        }

        return dummy->next;
    }

    /**
     * 206. Reverse Linked List.
     * Given the head of a singly linked list, reverse the list, and return the reversed list.
     *
     * https://leetcode.com/problems/reverse-linked-list/description/
     */
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr != nullptr)
        {
            ListNode *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        return prev;
    }

    ListNode *reverseListRec(ListNode *head)
    {
        if (!head)
        {
            return nullptr;
        }
        ListNode *newHead = head;

        if (head->next)
        {
            newHead = reverseListRec(head->next);
            head->next->next = head;
            head->next = nullptr;
        }
        return newHead;
    }

    /**
     * Given head, the head of a linked list, determine if the linked list has a cycle in it.
     *
     * There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.
     * Internally, pos is used to denote the index of the node that tail's next pointer is connected to.
     * Note that pos is not passed as a parameter.
     *
     * Return true if there is a cycle in the linked list. Otherwise, return false.
     *
     * https://leetcode.com/problems/linked-list-cycle/description/
     */
    bool hasCycle(ListNode *head)
    {
        ListNode *slowPointer = head;
        ListNode *fastPointer = head;
        while (fastPointer != nullptr && fastPointer->next != nullptr)
        {
            slowPointer = slowPointer->next;
            fastPointer = fastPointer->next->next;

            if (slowPointer == fastPointer)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * 19. Remove Nth Node From End of List.
     * Given the head of a linked list, remove the nth node from the end of the list and return its head.
     *
     * https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
     */
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummy = new ListNode(0, head);
        ListNode *curr = head;
        for (int i = 0; i < n; i++)
        {
            curr = curr->next;
        }

        ListNode *nthPrevNode = dummy;
        while (curr != nullptr)
        {
            curr = curr->next;
            nthPrevNode = nthPrevNode->next;
        }

        nthPrevNode->next = nthPrevNode->next->next;
        return dummy->next;
    }

    /**
     * 143. Reorder List.
     *
     * You are given the head of a singly linked-list. The list can be represented as:
     * L0 → L1 → … → Ln - 1 → Ln.
     *
     * Reorder the list to be on the following form:
     * L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
     *
     * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
     *
     * https://leetcode.com/problems/reorder-list/description/
     */
    void reorderList(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = slow->next;
        slow->next = nullptr;
        ListNode *curr1 = head;
        ListNode *curr2 = reverseList(head2);
        while (curr2 != nullptr)
        {
            ListNode *temp = curr1->next;
            ListNode *temp2 = curr2->next;
            curr1->next = curr2;
            curr2->next = temp;
            curr1 = temp;
            curr2 = temp2;
        }
    }

    /**
     * 3. Longest Substring Without Repeating Characters.
     * Given a string s, find the length of the longest substring without repeating characters.
     *
     * https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
     */
    int lengthOfLongestSubstring(std::string s)
    {
        int l = 0, r = 0, max_count = 0;
        std::unordered_set<int> set;

        while (r < s.length())
        {
            while (set.find(s[r]) != set.end())
            {
                set.erase(s[l]);
                l++;
            }
            set.insert(s[r]);
            max_count = std::max(max_count, r - l + 1);
            r++;
        }
        return max_count;
    }

    int lengthOfLongestSubstring2(std::string s)
    {
        int begin = 0, max_count = 0;
        std::unordered_map<char, int> cmap;

        for (int i = 0; i < s.length(); i++)
        {
            if (cmap.find(s[i]) != cmap.end())
            {
                begin = std::max(begin, cmap[s[i]]);
            }
            max_count = std::max(max_count, i - begin);
            cmap[s[i]] = i;
        }

        return max_count;
    }

    /**
     * 424. Longest Repeating Character Replacement.
     * You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character.
     * You can perform this operation at most k times.
     * Return the length of the longest substring containing the same letter you can get after performing the above operations.
     *
     * https://leetcode.com/problems/longest-repeating-character-replacement/description/
     */
    int characterReplacement(std::string s, int k)
    {
        int l = 0, r = 0, max_size = INT_MIN, max_freq = 0;
        std::unordered_map<char, int> map;
        auto compare = [](const std::pair<char, int> &a, const std::pair<char, int> &b)
        {
            return a.second < b.second;
        };

        while (r < s.length())
        {
            map[s[r]]++;
            max_freq = std::max(max_freq, map[s[r]]);

            while (r - l + 1 - max_freq > k)
            {
                map[s[l]]--;
                l++;
            }
            max_size = std::max(max_size, r - l + 1);
            r++;
        }
        return max_size;
    }

    /**
     * 49. Group Anagrams.
     * Given an array of strings strs, group the anagrams together. You can return the answer in any order.
     *
     * https://leetcode.com/problems/group-anagrams/description/
     */
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        std::vector<std::vector<std::string>> result;

        for (int i = 0; i < strs.size(); i++)
        {
            std::array<int, 26> chars = {0};
            for (const auto &ch : strs[i])
            {
                chars[ch - 'a']++;
            }

            std::string str;
            for (const auto &val : chars)
            {
                str += "#";
                str += std::to_string(val);
            }

            map[str].push_back(strs[i]);
        }

        for (auto &pair : map)
        {
            result.push_back(pair.second);
        }
        return result;
    }

    /**
     * 20. Valid Parentheses.
     * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
     *
     * https://leetcode.com/problems/valid-parentheses/description/
     */
    bool isValid(std::string s)
    {
        std::unordered_map<char, char> map = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
        std::stack<char> stack;
        for (auto ch : s)
        {
            if (map.count(ch))
            {
                stack.push(ch);
            }
            else
            {
                if (!stack.empty() && ch == map[stack.top()])
                {
                    stack.pop();
                }
                else
                {
                    return false;
                }
            }
        }
        return stack.empty();
    }

    /**
     * 5. Longest Palindromic Substring.
     * Given a string s, return the longest palindromic substring in s.
     */
    std::string longestPalindrome(std::string s)
    {
        int ll = 0, max_length = INT_MIN;
        for (int i = 0; i < s.length(); i++)
        {
            // Odd length.
            int l = i, r = i;
            while (l - 1 >= 0 && r + 1 < s.length() && s[l - 1] == s[r + 1])
            {
                l--;
                r++;
            }
            if (r - l + 1 > max_length)
            {
                max_length = r - l + 1;
                ll = l;
            }

            // Even length.
            if (i + 1 < s.length() && s[i] == s[i + 1])
            {
                l = i, r = i + 1;
                while (l - 1 >= 0 && r + 1 < s.length() && s[l - 1] == s[r + 1])
                {
                    l--;
                    r++;
                }
                if (r - l + 1 > max_length)
                {
                    max_length = r - l + 1;
                    ll = l;
                }
            }
        }
        return s.substr(ll, max_length);
    }

    /**
     * 125. Valid Palindrome.
     * A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters,
     * it reads the same forward and backward. Alphanumeric characters include letters and numbers.
     *
     * https://leetcode.com/problems/valid-palindrome/description/
     */
    bool isPalindrome(std::string s)
    {
        int l = 0, r = s.length() - 1;
        while (l <= r)
        {
            if (!std::isalnum(s[l]))
            {
                l++;
                continue;
            }
            if (!std::isalnum(s[r]))
            {
                r--;
                continue;
            }
            if (std::tolower(s[l]) == std::tolower(s[r]))
            {
                l++;
                r--;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    /**
     * 647. Palindromic Substrings.
     * Given a string s, return the number of palindromic substrings in it.
     * A string is a palindrome when it reads the same backward as forward.
     *
     * A substring is a contiguous sequence of characters within the string.
     *
     * https://leetcode.com/problems/palindromic-substrings/description/
     */
    int countSubstrings(std::string s)
    {
        int ll = 0, count = 0;
        for (int i = 0; i < s.length(); i++)
        {
            // Odd length.
            int l = i, r = i;
            while (l >= 0 && r < s.length() && s[l] == s[r])
            {
                l--;
                r++;
                count++;
            }

            // Even length.
            l = i, r = i + 1;
            while (l >= 0 && r < s.length() && s[l] == s[r])
            {
                l--;
                r++;
                count++;
            }
        }
        return count;
    }

    /**
     * 76. Minimum Window Substring.
     * Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
     * If there is no such substring, return the empty string "".
     *
     * https://leetcode.com/problems/minimum-window-substring/
     */
    std::string minWindow(std::string s, std::string t)
    {
        if (t.empty())
            return "";
        std::unordered_map<char, int> sMap;
        std::unordered_map<char, int> tMap;
        for (auto &ch : t)
        {
            tMap[ch]++;
        }

        int needed_match = tMap.size(), curr_match = 0;
        int l = 0, r = 0, min_length = INT_MAX;
        std::pair<int, int> res = {-1, -1};

        while (r < s.length())
        {
            sMap[s[r]]++;
            if (tMap.count(s[r]) && sMap[s[r]] == tMap[s[r]])
            {
                curr_match++;
            }

            while (curr_match == needed_match)
            {
                if (min_length > r - l + 1)
                {
                    min_length = r - l + 1;
                    res = {l, r};
                }

                sMap[s[l]]--;
                if (tMap.count(s[l]) && sMap[s[l]] < tMap[s[l]])
                {
                    curr_match--;
                }
                l++;
            }
            r++;
        }
        return min_length == INT_MAX ? "" : s.substr(res.first, min_length);
    }

    /**
     * 133. Clone Graph.
     * Given a reference of a node in a connected undirected graph.
     * Return a deep copy (clone) of the graph.
     * Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
     *
     * https://leetcode.com/problems/clone-graph/description/
     */
    Node *cloneGraph(Node *node, std::unordered_map<Node *, Node *> &map)
    {
        if (map.find(node) != map.end())
        {
            return map[node];
        }

        Node *newNode = new Node(node->val);
        for (const auto &nei : node->neighbors)
        {
            newNode->neighbors.push_back(cloneGraph(nei));
        }
        map[node] = newNode;
        return newNode;
    }

    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        std::unordered_map<Node *, Node *> map;
        return cloneGraph(node, map);
    }

    Node *cloneGraphBfs(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        std::unordered_map<Node *, Node *> map;
        std::queue<Node *> queue;

        map[node] = new Node(node->val);
        queue.push(node);

        while (!queue.empty())
        {
            Node *curr = queue.front();
            queue.pop();

            for (auto nei : curr->neighbors)
            {
                if (map.find(nei) != map.end())
                {
                    map[nei] = new Node(nei->val);
                    queue.push(nei);
                }
                curr->neighbors.push_back(map[nei]);
            }
        }
        return map[node];
    }

    /**
     * 261. Graph Valid Tree.
     * You have a graph of n nodes labeled from 0 to n - 1.
     * You are given an integer n and a list of edges where edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the graph.
     * Return true if the edges of the given graph make up a valid tree, and false otherwise.
     *
     * https://leetcode.com/problems/graph-valid-tree/description/
     */
    bool validTree(int i, std::unordered_map<int, std::vector<int>> &map, std::unordered_set<int> &visited, int parent)
    {
        if (visited.find(i) != visited.end())
        {
            return false;
        }
        visited.insert(i);
        for (auto &nei : map[i])
        {
            if (nei == parent)
                continue;
            if (!validTree(nei, map, visited, i))
            {
                return false;
            }
        }
        return true;
    }

    bool validTree(int n, std::vector<std::vector<int>> &edges)
    {
        std::unordered_map<int, std::vector<int>> map;
        std::unordered_set<int> visited;
        for (int i = 0; i < edges.size(); i++)
        {
            map[edges[i][0]].push_back(edges[i][1]);
            map[edges[i][1]].push_back(edges[i][0]);
        }
        return validTree(0, map, visited, -1) && visited.size() == n;
    }

    bool validTreeBfs(int n, std::vector<std::vector<int>> &edges)
    {
        if (edges.size() > n - 1)
            return false;

        std::unordered_map<int, std::vector<int>> map;
        std::unordered_set<int> visited;
        std::queue<std::pair<int, int>> queue;
        for (const auto &edge : edges)
        {
            map[edge[0]].push_back(edge[1]);
            map[edge[1]].push_back(edge[0]);
        }
        queue.push({0, -1});
        visited.insert(0);

        while (!queue.empty())
        {
            std::pair<int, int> pair = queue.front();
            queue.pop();

            for (int nei : map[pair.first])
            {
                if (nei == pair.second)
                    continue;
                if (visited.find(nei) != visited.end())
                    return false;
                visited.insert(nei);
                queue.push({nei, pair.first});
            }
        }
        return visited.size() == n;
    }

    /**
     * 323. Number of Connected Components in an Undirected Graph.
     * You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
     * Return the number of connected components in the graph.
     *
     * https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/description/
     */
    void countComponents(int i, std::unordered_map<int, std::vector<int>> &map, std::unordered_set<int> &visited)
    {
        if (visited.find(i) != visited.end())
        {
            return;
        }
        visited.insert(i);
        for (auto &nei : map[i])
        {
            countComponents(nei, map, visited);
        }
    }

    int countComponents(int n, std::vector<std::vector<int>> &edges)
    {
        std::unordered_map<int, std::vector<int>> map;
        std::unordered_set<int> visited;
        for (const auto &edge : edges)
        {
            map[edge[0]].push_back(edge[1]);
            map[edge[1]].push_back(edge[0]);
        }
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited.find(i) != visited.end())
                continue;
            countComponents(i, map, visited);
            count++;
        }
        return count;
    }

    int countComponentsBfs(int n, std::vector<std::vector<int>> &edges)
    {
        std::unordered_map<int, std::vector<int>> map;
        std::unordered_set<int> visited;
        std::queue<int> queue;
        for (const auto &edge : edges)
        {
            map[edge[0]].push_back(edge[1]);
            map[edge[1]].push_back(edge[0]);
        }
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited.find(i) != visited.end())
            {
                continue;
            }
            queue.push(i);
            visited.insert(i);

            while (!queue.empty())
            {
                int node = queue.front();
                queue.pop();

                for (int nei : map[node])
                {
                    if (visited.find(nei) == visited.end())
                    {
                        visited.insert(nei);
                        queue.push(nei);
                    }
                }
            }
            count++;
        }
        return count;
    }

    int countComponentsUnionAndFind(int n, std::vector<std::vector<int>> &edges)
    {
        if (edges.size() > n - 1)
        {
            return false;
        }

        DSU dsu(n);
        int components = n;
        for (const auto &edge : edges)
        {
            if (dsu.unionOp(edge[0], edge[1]))
            {
                components--;
            }
        }
        return components;
    }

    /**
     * 128. Longest Consecutive Sequence.
     * Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
     * You must write an algorithm that runs in O(n) time.
     *
     * https://leetcode.com/problems/longest-consecutive-sequence/description/
     */
    int longestConsecutive(std::vector<int> &nums)
    {
        std::unordered_set<int> set;
        for (int &num : nums)
        {
            set.insert(num);
        }

        int maxCnt = INT_MIN;
        for (int &num : nums)
        {
            if (set.find(num - 1) == set.end())
            {
                int cnt = 0;
                int val = num;
                while (set.find(val) != set.end())
                {
                    cnt++;
                    val++;
                }
                maxCnt = std::max(maxCnt, cnt);
            }
        }
        return maxCnt;
    }

    /**
     * 200. Number of Islands.
     * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
     * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
     * You may assume all four edges of the grid are all surrounded by water.
     *
     * https://leetcode.com/problems/number-of-islands/description/
     */
    void numIslandsDfs(int i, int j, int n, int m, std::vector<std::vector<char>> &grid, std::vector<std::vector<int>> &visited)
    {
        if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == 0 || visited[i][j] == 1)
        {
            return;
        }
        visited[i][j] = 1;
        numIslandsDfs(i + 1, j, n, m, grid, visited);
        numIslandsDfs(i - 1, j, n, m, grid, visited);
        numIslandsDfs(i, j + 1, n, m, grid, visited);
        numIslandsDfs(i, j - 1, n, m, grid, visited);
    }

    void visitIslandForBfs(int i, int j, int n, int m, std::vector<std::vector<char>> &grid, std::vector<std::vector<int>> &visited, std::queue<std::pair<int, int>> &queue)
    {
        if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == 0 || visited[i][j] == 1)
        {
            return;
        }
        visited[i][j] = 1;
        queue.push({i, j});
    }

    void numIslandsBfs(int i, int j, int n, int m, std::vector<std::vector<char>> &grid, std::vector<std::vector<int>> &visited)
    {
        std::queue<std::pair<int, int>> queue;
        queue.push({i, j});
        visited[i][j] = 1;

        while (!queue.empty())
        {
            auto [r, c] = queue.front();
            queue.pop();

            visitIslandForBfs(r + 1, c, n, m, grid, visited, queue);
            visitIslandForBfs(r - 1, c, n, m, grid, visited, queue);
            visitIslandForBfs(r, c - 1, n, m, grid, visited, queue);
            visitIslandForBfs(r, c + 1, n, m, grid, visited, queue);
        }
    }

    int numIslands(std::vector<std::vector<char>> &grid)
    {
        std::vector<std::vector<int>> visited(grid.size(), std::vector<int>(grid[0].size(), 0));
        int cnt = 0, row = grid.size(), col = grid[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == 1 && visited[i][j] == 0)
                {
                    numIslandsDfs(i, j, row, col, grid, visited);
                    cnt++;
                }
            }
        }
        return cnt;
    }

    int numIslandsBfsOpt(std::vector<std::vector<char>> &grid)
    {
        int cnt = 0, row = grid.size(), col = grid[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == '1')
                {
                    std::queue<std::pair<int, int>> queue;
                    queue.push({i, j});
                    grid[i][j] = '0';
                    cnt++;

                    while (!queue.empty())
                    {
                        auto [r, c] = queue.front();
                        queue.pop();

                        if (r + 1 < row && grid[r + 1][c] == '1')
                        {
                            grid[r + 1][c] = '0';
                            queue.push({r + 1, c});
                        }
                        if (r - 1 >= 0 && grid[r - 1][c] == '1')
                        {
                            grid[r - 1][c] = '0';
                            queue.push({r - 1, c});
                        }
                        if (c + 1 < col && grid[r][c + 1] == '1')
                        {
                            grid[r][c + 1] = '0';
                            queue.push({r, c + 1});
                        }
                        if (c - 1 >= 0 && grid[r][c - 1] == '1')
                        {
                            grid[r][c - 1] = '0';
                            queue.push({r, c - 1});
                        }
                    }
                }
            }
        }
        return cnt;
    }

    int numIslandsBfsOpt(std::vector<std::vector<char>> &grid)
    {
        int cnt = 0, row = grid.size(), col = grid[0].size();
        DSUforGrid dsu(grid);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == '1')
                {
                    grid[i][j] = '0';
                    if (i + 1 < row && grid[i + 1][j] == '1')
                        dsu.unionOp(i * col + j, (i + 1) * col + j);
                    if (i - 1 >= 0 && grid[i - 1][j] == '1')
                        dsu.unionOp(i * col + j, (i - 1) * col + j);
                    if (j + 1 < col && grid[i][j + 1] == '1')
                        dsu.unionOp(i * col + j, i * col + (j + 1));
                    if (j - 1 >= 0 && grid[i][j - 1] == '1')
                        dsu.unionOp(i * col + j, i * col + (j - 1));
                }
            }
        }
        return dsu.getCount();
    }

    /**
     * 417. Pacific Atlantic Water Flow.
     * There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean.
     * The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.
     * 
     * The island is partitioned into a grid of square cells.
     * You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).
     * The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. 
     * Water can flow from any cell adjacent to an ocean into the ocean.
     * 
     * Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
     * 
     * https://leetcode.com/problems/pacific-atlantic-water-flow/description/
     */
    // Custom hash function for std::pair<int, int>
    struct PairHash
    {
        template <typename T1, typename T2>
        std::size_t operator()(const std::pair<T1, T2> &pair) const
        {
            std::size_t h1 = std::hash<T1>{}(pair.first);
            std::size_t h2 = std::hash<T2>{}(pair.second);
            return h1 ^ (h2 << 1); // Combine the hashes
        }
    };

    void paDfs(int i, int j, int n, int m, std::vector<std::vector<int>> &heights, std::unordered_set<std::pair<int, int>, PairHash> &set)
    {
        if (set.find({i, j}) != set.end())
        {
            return;
        }

        set.insert({i, j});
        if (i - 1 >= 0 && heights[i - 1][j] >= heights[i][j])
            paDfs(i - 1, j, n, m, heights, set);
        if (i + 1 < n && heights[i + 1][j] >= heights[i][j])
            paDfs(i + 1, j, n, m, heights, set);
        if (j - 1 >= 0 && heights[i][j - 1] >= heights[i][j])
            paDfs(i, j - 1, n, m, heights, set);
        if (j + 1 < m && heights[i][j + 1] >= heights[i][j])
            paDfs(i, j + 1, n, m, heights, set);
    }

    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>> &heights)
    {
        std::unordered_set<std::pair<int, int>, PairHash> pSet;
        std::unordered_set<std::pair<int, int>, PairHash> aSet;
        std::vector<std::vector<int>> result;
        int row = heights.size(), col = heights[0].size();
        for (int i = 0; i < col; i++)
        {
            paDfs(0, i, row, col, heights, pSet);
            paDfs(row - 1, i, row, col, heights, aSet);
        }
        for (int i = 0; i < row; i++)
        {
            paDfs(i, 0, row, col, heights, pSet);
            paDfs(i, col - 1, row, col, heights, aSet);
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (pSet.find({i, j}) != pSet.end() && aSet.find({i, j}) != aSet.end())
                {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }
};

/**
 * 211. Design Add and Search Words Data Structure.
 * Design a data structure that supports adding new words and finding if a string matches any previously added string.
 *
 * Implement the WordDictionary class:
 *
 * WordDictionary() Initializes the object.
 * void addWord(word) Adds word to the data structure, it can be matched later.
 * bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise.
 * word may contain dots '.' where dots can be matched with any letter.
 *
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 */

class WordDictionary
{
    TrieNode *root = nullptr;

public:
    WordDictionary()
    {
        root = new TrieNode();
    }

    void addWord(std::string word)
    {
        TrieNode *temp = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (temp->childMap.find(word[i]) == temp->childMap.end())
            {
                temp->childMap[word[i]] = new TrieNode();
            }
            temp = temp->childMap[word[i]];
        }
        temp->isWord = true;
    }

    bool search(TrieNode *root, std::string &word, int l)
    {
        TrieNode *temp = root;
        for (int i = l; i < word.length(); i++)
        {
            if (word[i] == '.')
            {
                for (auto nodePair : temp->childMap)
                {
                    if (search(nodePair.second, word, i + 1))
                    {
                        return true;
                    }
                }
                return false;
            }
            else
            {
                if (temp->childMap.find(word[i]) == temp->childMap.end())
                {
                    return false;
                }
                temp = temp->childMap[word[i]];
            }
        }
        return temp->isWord;
    }

    bool search(std::string word)
    {
        return search(root, word, 0);
    }
};

/**
 * 295. Find Median from Data Stream.
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * For example, for arr = [2,3,4], the median is 3.
 * For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
 *
 * https://leetcode.com/problems/find-median-from-data-stream/description/
 */
// struct MinHeapCompare
// {
//     bool operator()(int a, int b)
//     {
//         return a > b; // Min-heap
//     }
// };

class MedianFinder
{
    std::priority_queue<int> leftQueue;
    std::priority_queue<int, std::vector<int>, std::greater<int>> rightQueue;

public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        leftQueue.push(num);

        if (!rightQueue.empty() && leftQueue.top() > rightQueue.top())
        {
            leftQueue.pop();
            rightQueue.push(num);
        }

        if (leftQueue.size() > rightQueue.size() + 1)
        {
            int leftTop = leftQueue.top();
            leftQueue.pop();
            rightQueue.push(leftTop);
        }

        if (rightQueue.size() > leftQueue.size() + 1)
        {
            int rightTop = rightQueue.top();
            rightQueue.pop();
            leftQueue.push(rightTop);
        }
    }

    double findMedian()
    {
        if (leftQueue.size() > rightQueue.size())
        {
            return leftQueue.top();
        }
        else if (leftQueue.size() < rightQueue.size())
        {
            return rightQueue.top();
        }
        else
        {
            return (double(leftQueue.top()) + double(rightQueue.top())) / 2;
        }
    }
};

int main()
{
    Solution obj;
    // int n;
    // int target;
    // std::cin >> n;
    // std::vector<int> nums(n);
    // for (int i = 0; i < n; i++)
    //     std::cin >> nums[i];
    // std::cin >> target;

    // int a, b;
    // std::cin >> a >> b;

    // int n;
    // std::cin >> n;

    // std::string s1;
    // std::getline(std::cin, s1);
    // int n;
    // std::cin >> n;
    // std::vector<std::string> wordDict;
    // for (int i = 0; i < n; i++)
    // {
    //     std::string s2;
    //     std::getline(std::cin, s2);
    //     wordDict.push_back(s2);
    // }

    // int n, target;
    // std::cin >> n;
    // std::vector<int> nums(n);
    // for (int i = 0; i < n; i++)
    //     std::cin >> nums[i];
    // std::cin >> target;

    // std::string s;
    // std::getline(std::cin, s);

    // int ans = obj.numDecodings(s);
    // std::cout << "Ans: " << ans << std::endl;

    // TreeNode *node = new TreeNode(1);
    // node->left = new TreeNode(2);
    // node->right = new TreeNode(3);
    // node->right->left = new TreeNode(4);
    // node->right->right = new TreeNode(5);

    // std::string out = obj.serialize(node);
    // std::cout << out << std::endl;

    // TreeNode *ans = obj.deserialize(out);

    // int n;
    // std::cin >> n;
    // std::vector<int> nums(n);
    // for (int i = 0; i < n; i++)
    //     std::cin >> nums[i];

    // int n2;
    // std::cin >> n2;
    // std::vector<int> nums2(n2);
    // for (int i = 0; i < n2; i++)
    //     std::cin >> nums2[i];

    // TreeNode *ans = obj.buildTree(nums, nums2);

    // std::vector<ListNode *> vec;
    // ListNode *l1 = new ListNode(1);
    // l1->next = new ListNode(4);
    // l1->next->next = new ListNode(5);
    // vec.push_back(l1);

    // ListNode *l2 = new ListNode(1);
    // l2->next = new ListNode(3);
    // l2->next->next = new ListNode(4);
    // vec.push_back(l2);

    // ListNode *l3 = new ListNode(2);
    // l3->next = new ListNode(6);
    // vec.push_back(l3);

    // ListNode *res = obj.mergeKLists(vec);
    // while (res != nullptr)
    // {
    //     std::cout << res->val << "->";
    //     res = res->next;
    // }

    // MedianFinder medianFinder;
    // medianFinder.addNum(1);
    // medianFinder.addNum(2);

    // std::cout << "Median:" << medianFinder.findMedian() << std::endl;

    // medianFinder.addNum(3);
    // std::cout << "Median:" << medianFinder.findMedian() << std::endl;

    std::string s;
    std::getline(std::cin, s);

    std::string s2;
    std::getline(std::cin, s2);

    std::string ans = obj.minWindow(s, s2);
    std::cout << "Ans: " << ans << std::endl;

    return 0;
}