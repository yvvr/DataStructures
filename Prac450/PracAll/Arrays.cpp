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
#include <algorithm>

class Solution
{
public:
    void printList(std::vector<int> &nums)
    {
        for (int num : nums)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    /**
     * 2366. Minimum Replacements to Sort the Array.
     *
     * You are given a 0-indexed integer array nums.
     * In one operation you can replace any element of the array with any two elements that sum to it.
     *
     * For example, consider nums = [5,6,7]. In one operation, we can replace nums[1] with 2 and 4 and convert nums to [5,2,4,7].
     * Return the minimum number of operations to make an array that is sorted in non-decreasing order.
     *
     * https://leetcode.com/problems/minimum-replacements-to-sort-the-array/
     */
    long long minimumReplacement(std::vector<int> &nums)
    {
    }

    /**
     * Minimum swaps to sort an array.
     *
     * Given an array arr[] of distinct elements, find the minimum number of swaps required to sort the array.
     *
     * https://www.geeksforgeeks.org/dsa/minimum-number-swaps-required-sort-array/
     */
    int minSwaps(std::vector<int> &nums)
    {
        std::vector<int> temp(nums.begin(), nums.end());
        std::sort(temp.begin(), temp.end());

        std::unordered_map<int, int> pos;
        for (int i = 0; i < nums.size(); i++)
            pos[nums[i]] = i;

        int swaps = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (temp[i] != nums[i])
            {
                int index = pos[temp[i]];
                std::swap(nums[i], nums[index]);

                pos[nums[i]] = i;
                pos[nums[index]] = index;

                swaps++;
            }
        }
        
        return swaps;
    }
};

int main()
{
    Solution obj;
    std::vector<int> nums = {1};

    std::cout << "Min Replacement Value: " << obj.minimumReplacement(nums) << std::endl;
    return 0;
}