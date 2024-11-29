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
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <functional>
#include <queue>
#include <unordered_set>

class Solution
{
public:
    // Function to find the next greater element for each element of the array.
    std::vector<long long> nextLargerElement(std::vector<long long> arr, int n)
    {
        std::stack<std::pair<long long, int>> stack;

        for (int i = 0; i < arr.size(); i++)
        {
            while (!stack.empty() && stack.top().first < arr[i])
            {
                arr[stack.top().second] = arr[i];
                stack.pop();
            }
            stack.push(std::make_pair(arr[i], i));
        }

        while (!stack.empty())
        {
            arr[stack.top().second] = -1;
            stack.pop();
        }

        return arr;
    }
    /**
     * Check Mirror in N-ary tree.
     * Given two n-ary trees.
     * Check if they are mirror images of each other or not. You are also given e denoting the number of edges in both trees, and two arrays, A[] and B[].
     * https://www.geeksforgeeks.org/problems/check-mirror-in-n-ary-tree1528/1
     */
    int checkMirrorTree(int n, int e, int A[], int B[])
    {
        std::unordered_map<int, std::stack<int>> tree;

        for (int i = 0; i < 2 * e - 1; i = i + 2)
        {
            if (tree.find(A[i]) == tree.end())
            {
                tree[A[i]] = std::stack<int>();
            }
            tree[A[i]].push(A[i + 1]);
        }

        for (int i = 0; i < 2 * e - 1; i = i + 2)
        {
            if (tree.find(B[i]) == tree.end() || tree[B[i]].top() != B[i + 1])
            {
                return 0;
            }
            tree[B[i]].pop();
        }
        return 1;
    }

    /**
     * Minimum Swaps to Sort.
     * Given an array of n distinct elements.
     * Find the minimum number of swaps required to sort the array in strictly increasing order.
     * https://www.geeksforgeeks.org/problems/minimum-swaps/1
     * Time complexity : O(nlogn), Space complexity: O(n)
     */
    int minSwaps(std::vector<int> &nums)
    {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            map[nums[i]] = i;
        }
        std::sort(nums.begin(), nums.end());

        std::unordered_map<int, bool> visible;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (map[nums[i]] == i || visible[nums[i]])
            {
                continue;
            }
            int count = 0;
            int j = i;
            while (!visible[nums[j]])
            {
                visible[nums[j]] = true;
                j = map[nums[j]];
                count++;
            }
            ans += (count - 1);
        }
        return ans;
    }

    /**
     * Minimum Swaps to Sort optmized greedy algorithm.
     * Given an array of n distinct elements.
     * Find the minimum number of swaps required to sort the array in strictly increasing order.
     * https://www.geeksforgeeks.org/problems/minimum-swaps/1
     * Time complexity : O(n), Space complexity: O(n)
     */
    int minSwapsOpt(std::vector<int> &nums)
    {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            map[nums[i]] = i;
        }
        std::sort(nums.begin(), nums.end());

        int ans = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (map[nums[i]] != i)
            {
                int j = map[nums[i]];
                std::swap(nums[i], nums[j]);
                ans++;
            }
        }
        return ans;
    }
    /**
     * 287. Find the Duplicate Number.
     * Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.
     * There is only one repeated number in nums, return this repeated number.
     * You must solve the problem without modifying the array nums and using only constant extra space.
     * https://leetcode.com/problems/find-the-duplicate-number/description/
     */
    int findDuplicate(std::vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            int index = std::abs(nums[i]);
            if (nums[index - 1] < 0)
            {
                return std::abs(nums[i]);
            }

            nums[index - 1] = -1 * nums[index - 1];
        }
        return -1;
    }

    void permute(std::string &s, int idx)
    {
        if (idx == s.size() - 1)
        {
            std::cout << s << std::endl;
        }

        for (int i = idx; i < s.size(); i++)
        {
            std::swap(s[idx], s[i]);
            permute(s, idx + 1);
            std::swap(s[idx], s[i]);
        }
    }

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

    /**
     * Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
     * https://leetcode.com/problems/partition-equal-subset-sum/description/
     */
    bool canPartition(std::vector<int> &nums)
    {
        std::unordered_map<std::pair<int, int>, bool, PairHash> map;
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1)
        {
            return false;
        }
        int target = sum / 2;
        return dfsCanPartition(nums, 0, 0, target, map);
    }

    bool dfsCanPartition(std::vector<int> &nums, int i, int sum, int target, std::unordered_map<std::pair<int, int>, bool, PairHash> &map)
    {
        if (sum > target)
        {
            return false;
        }

        if (sum == target)
        {
            return true;
        }

        if (map.find({i, sum}) != map.end())
        {
            return map[{i, sum}];
        }

        map[{i, sum}] = dfsCanPartition(nums, i + 1, sum + nums[i], target, map) || dfsCanPartition(nums, i + 1, sum, target, map);

        return map[{i, sum}];
    }

    /**
     * You are given an array of integers arr[]. Your task is to reverse the given array.
     * https://www.geeksforgeeks.org/problems/reverse-an-array/1
     */
    void reverseArray(std::vector<int> &arr)
    {
        for (int i = 0; i < arr.size() / 2; i++)
        {
            std::swap(arr[i], arr[arr.size() - 1 - i]);
        }
    }

    /**
     * Given an array arr. Your task is to find the minimum and maximum elements in the array.
     * Note: Return an array that contains two elements the first one will be a minimum element and the second will be a maximum of an array.
     *
     * https://www.geeksforgeeks.org/problems/find-minimum-and-maximum-element-in-an-array4428/1
     */
    std::pair<long long, long long> getMinMax(std::vector<long long int> arr)
    {
        auto maxIt = std::max_element(arr.begin(), arr.end());
        auto minIt = std::min_element(arr.begin(), arr.end());

        long long int max = INT_MAX, min = INT_MIN;
        if (maxIt != arr.end())
        {
            max = *maxIt;
        }
        if (minIt != arr.end())
        {
            min = *minIt;
        }
        return {max, min};
    }

    int kthSmallest(std::vector<int> &arr, int k)
    {
        int kthSmallest = INT_MIN;
        while (k > 0)
        {
            int smallest = INT_MAX;
            for (int i = 0; i < arr.size(); i++)
            {
                if (smallest > arr[i] && arr[i] > kthSmallest)
                {
                    smallest = arr[i];
                }
            }
            kthSmallest = smallest;
            k--;
        }
        return kthSmallest;
    }

    int kthSmallestelementWithPriorityQueue(std::vector<int> &arr, int k)
    {
        std::priority_queue<int> pq;

        for (auto num : arr)
        {
            pq.push(num);

            if (pq.size() > k)
            {
                pq.pop();
            }
        }
        return pq.top();
    }

    int partition(std::vector<int> &arr, int l, int r)
    {
        int i = l;
        for (int j = l; j < r; j++)
        {
            if (arr[j] <= arr[r])
            {
                std::swap(arr[i], arr[j]);
                i++;
            }
        }
        std::swap(arr[i], arr[r]);
        return i;
    }

    int KthSmallestWithQuickSelect(std::vector<int> &arr, int l, int r, int k)
    {
        if (k > 0 && k <= r - l + 1)
        {
            int pivot = partition(arr, l, r);

            if (pivot - l == k - 1)
            {
                return arr[pivot];
            }

            if (pivot - l > k - 1)
            {
                return KthSmallestWithQuickSelect(arr, l, pivot - 1, k);
            }
            else
            {
                return KthSmallestWithQuickSelect(arr, pivot + 1, r, k - pivot + l - 1);
            }
        }
        return INT_MAX;
    }

    /**
     * Sort 0s, 1s and 2s
     * Given an array arr containing only 0s, 1s, and 2s. Sort the array in ascending order.
     * https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s4231/1
     */
    void sort012(std::vector<int> &arr)
    {
        int i = 0, j = 0, k = arr.size() - 1;

        while (j <= k)
        {
            if (arr[j] == 0)
                std::swap(arr[i++], arr[j++]);
            else if (arr[j] == 1)
                j++;
            else
                std::swap(arr[j], arr[k--]);
        }
    }

    /**
     * Union of Arrays with Duplicates
     * Given two arrays a[] and b[], the task is to find the number of elements in the union between these two arrays.
     * https://www.geeksforgeeks.org/problems/union-of-two-arrays3538/1
     */
    int findUnion(std::vector<int> &a, std::vector<int> &b)
    {
        std::unordered_set<int> set;
        for (int num : a)
        {
            set.insert(num);
        }
        for (int num : b)
        {
            set.insert(num);
        }
        return set.size();
    }
    /**
     * Kadane's Algorithm
     *
     * Given an integer array arr[]. You need to find and return the maximum sum possible from all the subarrays.
     * https://www.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1
     */
    int maxSubarraySum(std::vector<int> &arr)
    {
        int maxSum = INT_MIN, sum = 0;
        for (auto num : arr)
        {
            sum += num;
            maxSum = std::max(maxSum, sum);
            sum = sum < 0 ? 0 : sum;
        }
        return maxSum;
    }
    /**
     * Minimize the Heights I
     *
     * Given a positive integer k and an array arr[] denoting heights of towers, you have to modify the height of each tower either by increasing or decreasing them by k only once.
     * Find out what could be the possible minimum difference of the height of shortest and longest towers after you have modified each tower.
     * https://www.geeksforgeeks.org/problems/minimize-the-heights-i/1
     */
    int getMinDiff(int k, std::vector<int> &arr)
    {
        std::sort(arr.begin(), arr.end());
        int res = arr[arr.size() - 1] - arr[0];
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] - k < 0)
            {
                continue;
            }
            int min = std::min(arr[0] + k, arr[i] - k);
            int max = std::max(arr[i - 1] + k, arr[arr.size() - 1] - k);
            res = std::min(res, max - min);
        }
        return res;
    }

    /**
     * Given an array arr[] of non-negative integers. Each array element represents the maximum length of the jumps that can be made forward from that element.
     * This means if arr[i] = x, then we can jump any distance y such that y ≤ x.
     * Find the minimum number of jumps to reach the end of the array starting from the first element.
     * If an element is 0, then you cannot move through that element.
     */
    int minJumps(std::vector<int> &arr)
    {
        // std::vector<int> result(arr.size(), INT_MAX);
        // result[0] = 0;
        // for (int i = 0; i < arr.size(); i++)
        // {
        //     for (int j = 0; j < i; j++)
        //     {
        //         if (arr[j] != 0 && j + arr[j] >= i && result[j] != INT_MAX)
        //         {
        //             result[i] = std::min(result[i], result[j] + 1);
        //         }
        //     }
        // }
        // return result[arr.size() - 1] != INT_MAX ? result[arr.size() - 1] : -1;

        // for (int i = arr.size() - 2; i >= 0; i--)
        // {
        //     for (int j = 1; j <= arr[i]; j++)
        //     {
        //         if (i + j <= arr.size() - 1 && result[i + j] != INT_MAX)
        //         {
        //             result[i] = std::min(result[i], result[i + j] + 1);
        //         }
        //     }
        // }
        // return result[0] != INT_MAX ? result[0] : -1;

        // Greedy algorithm.
        int result = 0;
        int l = 0, r = 0;

        while (r < arr.size() - 1)
        {
            int fartest = 0;
            for (int i = l; i <= r; i++)
            {
                fartest = std::max(fartest, i + arr[i]);
            }
            if (fartest <= r)
            {
                return -1;
            }
            l = r + 1;
            r = fartest;
            result += 1;
        }
        return result;
    }
    /**
     * K-th element of two Arrays
     * Given two sorted arrays arr1 and arr2 and an element k.
     * The task is to find the element that would be at the kth position of the combined sorted array.
     *
     * https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1
     */
    int kthElement(int k, std::vector<int> &arr1, std::vector<int> &arr2)
    {
        std::sort(arr1.begin(), arr1.end());
        std::sort(arr2.begin(), arr2.end());

        int i = 0, j = 0, l = 0;

        while (i < arr1.size() && j < arr2.size())
        {
            if (arr1[i] < arr2[j])
            {
                if (l == k - 1)
                {
                    return arr1[i];
                }
                i++;
                l++;
            }
            else
            {
                if (l == k - 1)
                {
                    return arr2[j];
                }
                j++;
                l++;
            }
        }

        while (i < arr1.size())
        {
            if (l == k - 1)
            {
                return arr1[i];
            }
            i++;
            l++;
        }

        while (j < arr2.size())
        {
            if (l == k - 1)
            {
                return arr2[j];
            }
            j++;
            l++;
        }

        return -1;
    }

    int kthElementWithPq(int k, std::vector<int> &arr1, std::vector<int> &arr2)
    {
        std::priority_queue<int> pq;
        for (auto num : arr1)
        {
            pq.push(num);
            if (pq.size() > k)
            {
                pq.pop();
            }
        }

        for (auto num : arr2)
        {
            pq.push(num);
            if (pq.size() > k)
            {
                pq.pop();
            }
        }

        return pq.top();
    }

    /**
     * Merge Intervals
     *
     * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
     * and return an array of the non-overlapping intervals that cover all the intervals in the input.
     *
     * https://leetcode.com/problems/merge-intervals/description/
     */
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals)
    {
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int> &a, const std::vector<int> &b)
                  { return a[0] < b[0]; });
        std::vector<std::vector<int>> result;

        int len = 1;
        while(len < intervals.size()) {

        }
    }
};

int main()
{
    // int n;
    // std::cin >> n;
    // std::vector<long long> arr(n);
    // for (int i = 0; i < n; i++)
    //     std::cin >> arr[i];

    // Solution obj;
    // std::vector<long long> res = obj.nextLargerElement(arr, n);
    // for (long long i : res)
    //     std::cout << i << " ";
    // std::cout << std::endl;

    // int n, e;

    // std::cin >> n >> e;
    // int A[2 * e], B[2 * e];

    // for (int i = 0; i < 2 * e; i++)
    //     std::cin >> A[i];

    // for (int i = 0; i < 2 * e; i++)
    //     std::cin >> B[i];

    // Solution ob;
    // std::cout << ob.checkMirrorTree(n, e, A, B) << std::endl;

    Solution obj;
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++)
        std::cin >> nums[i];

    // int ans = obj.minSwapsOpt(nums);
    // std::cout << ans << "\n";

    // Solution obj;
    // std::string s;
    // std::getline(std::cin, s);

    // std::cout << "------PERMUTE-------" << std::endl;
    // obj.permute(s, 0);

    bool ans = obj.canPartition(nums);
    std::cout << ans << "\n";

    return 0;
}