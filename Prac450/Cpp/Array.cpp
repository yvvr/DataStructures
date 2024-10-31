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

    int ans = obj.minSwapsOpt(nums);
    std::cout << ans << "\n";

    return 0;
}