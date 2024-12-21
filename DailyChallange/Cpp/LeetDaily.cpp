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
#include <map>
#include <string>
#include <numeric>

class Solution
{
public:
    /**
     * 1475. Final Prices With a Special Discount in a Shop.
     * You are given an integer array prices where prices[i] is the price of the ith item in a shop.
     * There is a special discount for items in the shop. If you buy the ith item,
     * then you will receive a discount equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <= prices[i].
     * Otherwise, you will not receive any discount at all.
     *
     * https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/
     */
    std::vector<int> finalPrices(std::vector<int> &prices)
    {
        std::stack<std::pair<int, int>> stack;
        std::vector<int> res(prices.begin(), prices.end());
        for (int i = 0; i < prices.size(); i++)
        {
            while (!stack.empty() && stack.top().first >= prices[i])
            {
                res[stack.top().second] -= prices[i];
                stack.pop();
            }
            stack.push({prices[i], i});
        }
        return res;
    }

    /**
     * 2182. Construct String With Repeat Limit.
     * You are given a string s and an integer repeatLimit.
     * Construct a new string repeatLimitedString using the characters of s such that no letter appears more than repeatLimit times in a row.
     * You do not have to use all characters from s.
     *
     * https://leetcode.com/problems/construct-string-with-repeat-limit/description/
     */
    std::string repeatLimitedString(std::string s, int repeatLimit)
    {
        std::vector<int> vec(26, 0);
        std::string res;

        for (auto &ch : s)
        {
            vec[ch - 'a']++;
        }

        int currIndex = vec.size() - 1;
        while (currIndex >= 0)
        {
            if (vec[currIndex] == 0)
            {
                currIndex--;
                continue;
            }

            int chLimit = std::min(vec[currIndex], repeatLimit);
            res.append(chLimit, 'a' + currIndex);
            vec[currIndex] -= chLimit;

            if (vec[currIndex] > 0)
            {
                int nextIndex = currIndex - 1;
                while (nextIndex >= 0 && vec[nextIndex] == 0)
                {
                    nextIndex--;
                }

                if (nextIndex < 0)
                {
                    break;
                }
                else
                {
                    res.push_back('a' + nextIndex);
                    vec[currIndex]--;
                }
            }
        }

        return res;
    }

    /**
     * 2832. Maximal Range That Each Element Is Maximum in It.
     * You are given a 0-indexed array nums of distinct integers.
     * Let us define a 0-indexed array ans of the same length as nums in the following way:
     * ans[i] is the maximum length of a subarray nums[l..r], such that the maximum element in that subarray is equal to nums[i].
     *
     * Return the array ans.
     *
     * https://leetcode.com/problems/maximal-range-that-each-element-is-maximum-in-it/description/
     */
    std::vector<int> maximumLengthOfRanges(std::vector<int> &nums)
    {
        // std::vector<int> res(nums.size());
        // std::fill(res.begin(), res.end(), nums.size() - 1);
        // std::stack<int> stack;
        // for (int i = 0; i < nums.size(); i++)
        // {
        //     while (!stack.empty() && nums[stack.top()] < nums[i])
        //     {
        //         res[stack.top()] = i - 1;
        //         stack.pop();
        //     }
        //     stack.push(i);
        // }
        // while (!stack.empty())
        // {
        //     stack.pop();
        // }

        // std::vector<int> resr(nums.size());
        // std::fill(resr.begin(), resr.end(), 0);
        // for (int i = nums.size() - 1; i >= 0; i--)
        // {
        //     while (!stack.empty() && nums[stack.top()] < nums[i])
        //     {
        //         resr[stack.top()] = i + 1;
        //         stack.pop();
        //     }
        //     stack.push(i);
        // }
        // for (int i = 0; i < nums.size(); i++)
        // {
        //     res[i] = res[i] - resr[i] + 1;
        // }
        // return res;

        std::vector<int> res(nums.size());
        std::fill(res.begin(), res.end(), nums.size() - 1);
        std::stack<int> stack;
        for (int i = 0; i < nums.size(); i++)
        {
            while (!stack.empty() && nums[stack.top()] < nums[i])
            {
                stack.pop();
            }
            res[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        while (!stack.empty())
        {
            stack.pop();
        }

        std::vector<int> resr(nums.size());
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            while (!stack.empty() && nums[stack.top()] < nums[i])
            {
                stack.pop();
            }
            resr[i] = stack.empty() ? nums.size() : stack.top();
            stack.push(i);
        }
        for (int i = 0; i < nums.size(); i++)
        {
            res[i] = resr[i] - res[i] - 1;
        }
        return res;
    }
};

int main()
{
    Solution obj;
    // int n;
    // std::cin >> n;
    // std::vector<int> nums(n);
    // for (int i = 0; i < n; i++)
    //     std::cin >> nums[i];

    // std::vector<int> ans = obj.finalPrices(nums);
    // for (int i = 0; i < n; i++)
    //     std::cout << ans[i] << " ";

    // std::string s;
    // std::getline(std::cin, s);
    // int n;
    // std::cin >> n;

    // std::string ans = obj.repeatLimitedString(s, n);
    // std::cout << ans << std::endl;

    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++)
        std::cin >> nums[i];

    std::vector<int> ans = obj.maximumLengthOfRanges(nums);
    for (int i = 0; i < n; i++)
        std::cout << ans[i] << " ";

    return 0;
}