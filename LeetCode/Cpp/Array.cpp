/**
 * Copyright (c) 2025
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
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>

class Solution
{
public:
    /**
     * 3110. Score of a String.
     *
     * You are given a string s. The score of a string is defined as the sum of the absolute difference between the ASCII values of adjacent characters.
     * Return the score of s.
     *
     * https://leetcode.com/problems/score-of-a-string/description/
     */
    int scoreOfString(std::string s)
    {
        int score = 0;
        for (int i = 1; i < s.length(); i++)
        {
            score += std::abs(s[i - 1] - s[i]);
        }

        return score;
    }

    /**
     * 1929. Concatenation of Array.
     *
     * Given an integer array nums of length n, you want to create an array ans of length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed).
     * Specifically, ans is the concatenation of two nums arrays.
     *
     * Return the array ans.
     *
     * https://leetcode.com/problems/concatenation-of-array/
     */
    std::vector<int> getConcatenation(std::vector<int> &nums)
    {
        std::vector<int> res(nums);
        for (auto num : nums)
        {
            res.push_back(num);
        }
        return res;
    }

    /**
     * 217. Contains Duplicate
     *
     * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
     *
     * https://leetcode.com/problems/contains-duplicate/
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
     * 242. Valid Anagram
     *
     * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
     *
     * Example 1:
     * Input: s = "anagram", t = "nagaram"
     * Output: true
     *
     * Example 2:
     * Input: s = "rat", t = "car"
     * Output: false
     *
     * https://leetcode.com/problems/valid-anagram/description/
     */
    bool isAnagram(std::string s, std::string t)
    {
        // if (s.length() != t.length())
        // {
        //     return false;
        // }
        // std::unordered_map<char, int> map;

        // for (int i = 0; i < s.length(); i++)
        // {
        //     map[s[i]]++;
        //     map[t[i]]--;
        // }

        // for (auto pair : map)
        // {
        //     if (pair.second != 0)
        //     {
        //         return false;
        //     }
        // }
        // return true;

        if (s.length() != t.length())
        {
            return false;
        }

        std::vector<int> count(26, 0);
        for (int i = 0; i < s.length(); i++)
        {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for (auto val : count)
        {
            if (val != 0)
            {
                return false;
            }
        }

        return true;
    }

    /**
     * Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1.
     *
     * After doing so, return the array.
     *
     * Input: arr = [17,18,5,4,6,1]
     * Output: [18,6,6,6,1,-1]
     *
     * https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/description/
     */
    std::vector<int> replaceElements(std::vector<int> &arr)
    {
        int max = -1;
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            int temp = arr[i];
            arr[i] = max;
            max = std::max(temp, max);
        }

        return arr;
    }

    /**
     * 392. Is Subsequence
     *
     * Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
     * A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
     *
     * Example 1:
     * Input: s = "abc", t = "ahbgdc"
     * Output: true
     *
     * Example 2:
     * Input: s = "axc", t = "ahbgdc"
     * Output: false
     */
    bool isSubsequence(std::string s, std::string t)
    {
        int i = 0, j = 0;
        while (i < s.length() && j < t.length())
        {
            if (s[i] == t[j])
            {
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }

        return i == s.length();
    }

    /**
     * 2486. Append Characters to String to Make Subsequence
     *
     * You are given two strings s and t consisting of only lowercase English letters.
     *
     * Return the minimum number of characters that need to be appended to the end of s so that t becomes a subsequence of s.
     *
     * A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
     *
     * https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/description/
     */
    int appendCharacters(std::string s, std::string t)
    {
        int i = 0, j = 0;
        while (i < s.length() && j < t.length())
        {
            if (s[i] == t[j])
            {
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }

        return s.length() - i;
    }

    /**
     * Given a string s consisting of words and spaces, return the length of the last word in the string.
     * A word is a maximal substring consisting of non-space characters only.
     *
     * Example 1:
     * Input: s = "Hello World"
     * Output: 5
     *
     * Explanation: The last word is "World" with length 5.
     *
     * https://leetcode.com/problems/length-of-last-word/description/
     */
    int lengthOfLastWord(std::string s)
    {
        int i = s.length() - 1, count = 0;
        while (i >= 0 && s[i] == ' ')
        {
            i--;
        }
        while (i >= 0 && s[i] != ' ')
        {
            i--;
            count++;
        }

        return count;
    }

    /**
     * 422. Valid Word Square
     *
     * Given an array of strings words, return true if it forms a valid word square.
     *
     * A sequence of strings forms a valid word square if the kth row and column read the same string, where 0 <= k < max(numRows, numColumns).
     *
     * https://leetcode.com/problems/valid-word-square/description/
     */
    bool validWordSquare(std::vector<std::string> &words)
    {
        // for (int i = 0; i < words.size(); i++)
        // {
        //     std::string col = "";
        //     for (int j = 0; j < words.size(); j++)
        //     {
        //         if (j < words[i].length())
        //         {
        //             col += words[j][i];
        //         }
        //         else
        //         {
        //             break;
        //         }
        //     }
        //     if (words[i] != col)
        //     {
        //         return false;
        //     }
        // }

        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words[i].size(); j++)
            {
                if (j >= words.size() || i >= words[j].size() || words[i][j] != words[j][i])
                {
                    return false;
                }
            }

            return true;
        }

        return true;
    }

    /**
     * 2678. Number of Senior Citizens
     *
     * You are given a 0-indexed array of strings details. Each element of details provides information about a given passenger compressed into a string of length 15. The system is such that:
     * The first ten characters consist of the phone number of passengers.
     * The next character denotes the gender of the person.
     * The following two characters are used to indicate the age of the person.
     * The last two characters determine the seat allotted to that person.
     *
     *
     * Return the number of passengers who are strictly more than 60 years old.
     *
     * https://leetcode.com/problems/number-of-senior-citizens/description/
     */
    int countSeniors(std::vector<std::string> &details)
    {
        int count = 0;
        for (auto citizen : details)
        {
            int age = std::stoi(citizen.substr(11, 2));
            if (age > 60)
            {
                count++;
            }
        }
        return count;
    }

    /**
     * 485. Max Consecutive Ones.
     *
     * Given a binary array nums, return the maximum number of consecutive 1's in the array.
     *
     * https://leetcode.com/problems/max-consecutive-ones/description/
     */
    int findMaxConsecutiveOnes(std::vector<int> &nums)
    {
        int maxCount = 0;
        int count = 0;
        for (auto num : nums)
        {
            if (num == 1)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            maxCount = std::max(maxCount, count);
        }
        return maxCount;
    }

    /**
     * 14. Longest Common Prefix
     *
     * Write a function to find the longest common prefix string amongst an array of strings.
     * If there is no common prefix, return an empty string "".
     *
     * https://leetcode.com/problems/longest-common-prefix/description/
     */
    std::string longestCommonPrefix(std::vector<std::string> &strs)
    {
        std::string minStr = strs[0];
        int minLen = minStr.length();
        for (int i = 1; i < strs.size(); i++)
        {
            int count = 0;
            for (int j = 0; j < strs[i].length() && j < minStr.length(); j++)
            {
                if (strs[i][j] == minStr[j])
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            minLen = std::min(minLen, count);
            minStr = minStr.substr(0, minLen);
        }
        return minStr;
    }

    /**
     * 1408. String Matching in an Array
     *
     * Given an array of string words, return all strings in words that are a substring of another word. You can return the answer in any order.
     *
     * https://leetcode.com/problems/string-matching-in-an-array/description/
     */
    std::vector<std::string> stringMatching(std::vector<std::string> &words)
    {
        std::vector<std::string> result;
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words.size(); j++)
            {
                if (j == i)
                {
                    continue;
                }
                if (words[j].find(words[i]) != std::string::npos)
                {
                    result.push_back(words[i]);
                    break;
                }
            }
        }
        return result;
    }

    /**
     * 249. Group Shifted Strings
     *
     * Perform the following shift operations on a string:
     * Right shift: Replace every letter with the successive letter of the English alphabet, where 'z' is replaced by 'a'. For example, "abc" can be right-shifted to "bcd" or "xyz" can be right-shifted to "yza".
     * Left shift: Replace every letter with the preceding letter of the English alphabet, where 'a' is replaced by 'z'. For example, "bcd" can be left-shifted to "abc" or "yza" can be left-shifted to "xyz".
     *
     * We can keep shifting the string in both directions to form an endless shifting sequence.
     */
    std::vector<std::vector<std::string>> groupStrings(std::vector<std::string> &strings)
    {
        std::unordered_map<std::string, std::vector<std::string>> shiftMap;
        std::vector<std::vector<std::string>> result;
        for (auto &str : strings)
        {
            std::string shiftedStr = "a";
            int shiftValue = str[0] - 'a';
            for (int i = 1; i < str.length(); i++)
            {
                char shiftedChar = ((str[i] - 'a' - shiftValue) % 26 + 26) % 26 + 'a';
                shiftedStr += shiftedChar;
            }
            shiftMap[shiftedStr].push_back(str);
        }

        for (auto &mapPair : shiftMap)
        {
            result.push_back(mapPair.second);
        }
        return result;
    }

    /**
     * 118. Pascal's Triangle.
     *
     * Given an integer numRows, return the first numRows of Pascal's triangle.
     * In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
     *
     * https://leetcode.com/problems/pascals-triangle/description/
     */
    std::vector<std::vector<int>> generate(int numRows)
    {
        std::vector<std::vector<int>> result = {{1}};
        while (result.size() < numRows)
        {
            std::vector<int> nextRow;
            std::vector<int> lastRow = result[result.size() - 1];
            for (int i = 0; i < lastRow.size() + 1; i++)
            {
                int leftValue = i - 1 < 0 ? 0 : lastRow[i - 1];
                int rightValue = i > lastRow.size() - 1 ? 0 : lastRow[i];
                nextRow.push_back(leftValue + rightValue);
            }
            result.push_back(nextRow);
        }
        return result;
    }

    /**
     * 169. Majority Element
     *
     * Given an array nums of size n, return the majority element.
     *
     * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
     *
     * https://leetcode.com/problems/majority-element/description/
     */
    int majorityElement(std::vector<int> &nums)
    {
        int count = 1;
        int majNum = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (count == 0)
            {
                count++;
                majNum = nums[i];
            }
            else
            {
                if (nums[i] == majNum)
                {
                    count++;
                }
                else
                {
                    count--;
                }
            }
        }
        return majNum;
    }

    /**
     * 205. Isomorphic Strings.
     *
     * Given two strings s and t, determine if they are isomorphic.
     * Two strings s and t are isomorphic if the characters in s can be replaced to get t.
     *
     * All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
     *
     * https://leetcode.com/problems/isomorphic-strings/description/
     */
    bool isIsomorphic(std::string s, std::string t)
    {
        if (s.length() != t.length())
        {
            return false;
        }

        std::unordered_map<char, char> sMap;
        std::unordered_map<char, char> tMap;

        for (int i = 0; i < s.length(); i++)
        {
            if (sMap.find(s[i]) != sMap.end())
            {
                if (sMap[s[i]] != t[i])
                {
                    return false;
                }
            }
            else
            {
                sMap[s[i]] = t[i];
            }

            if (tMap.find(t[i]) != tMap.end())
            {
                if (tMap[t[i]] != s[i])
                {
                    return false;
                }
            }
            else
            {
                tMap[t[i]] = s[i];
            }
        }

        return true;
    }

    /**
     * 929. Unique Email Addresses.
     *
     * Every valid email consists of a local name and a domain name, separated by the '@' sign. Besides lowercase letters, the email may contain one or more '.' or '+'.
     * For example, in "alice@leetcode.com", "alice" is the local name, and "leetcode.com" is the domain name
     * If you add periods '.' between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name. Note that this rule does not apply to domain names.
     *
     * https://leetcode.com/problems/unique-email-addresses/description/
     */
    int numUniqueEmails(std::vector<std::string> &emails)
    {
        std::unordered_map<std::string, std::unordered_set<std::string>> emailMap;
        for (auto &email : emails)
        {
            int p = email.find("@");
            std::string localName = email.substr(0, p);
            std::string domainName = email.substr(p + 1, email.length() - p - 1);

            std::string nLocalName = "";
            for (int i = 0; i < localName.length(); i++)
            {
                if (localName[i] == '.')
                {
                    continue;
                }
                if (localName[i] == '+')
                {
                    break;
                }
                nLocalName += localName[i];
            }
            emailMap[domainName].insert(nLocalName);
        }

        int res = 0;
        for (auto &emailSet : emailMap)
        {
            res += emailSet.second.size();
        }

        return res;
    }

    /**
     * 3442. Maximum Difference Between Even and Odd Frequency I
     *
     * You are given a string s consisting of lowercase English letters.
     *
     * Your task is to find the maximum difference diff = freq(a1) - freq(a2) between the frequency of characters a1 and a2 in the string such that:
     * a1 has an odd frequency in the string.
     * a2 has an even frequency in the string.
     *
     * Return this maximum difference.
     */
    int maxDifference(std::string s)
    {
        std::unordered_map<char, int> charMap;
        for (auto &ch : s)
        {
            charMap[ch] += 1;
        }
        int minEven = INT_MAX, maxOdd = INT_MIN;
        for (auto &mapPair : charMap)
        {
            if (mapPair.second % 2 == 0)
            {
                minEven = std::min(minEven, mapPair.second);
            }
            else
            {
                maxOdd = std::max(maxOdd, mapPair.second);
            }
        }
        return maxOdd - minEven;
    }

    /**
     * 27. Remove Element.
     *
     * Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. The order of the elements may be changed.
     * Then return the number of elements in nums which are not equal to val.
     *
     * Consider the number of elements in nums which are not equal to val be k, to get accepted, you need to do the following things:
     * Change the array nums such that the first k elements of nums contain the elements which are not equal to val. The remaining elements of nums are not important as well as the size of nums.
     * Return k.
     *
     * https://leetcode.com/problems/remove-element/description/
     */
    int removeElement(std::vector<int> &nums, int val)
    {
        int i = 0;
        for (int j = 0; j < nums.size(); j++)
        {
            if (nums[j] != val)
            {
                std::swap(nums[i], nums[j]);
                i++;
            }
        }
        return i;
    }

    /**
     * 605. Can Place Flowers
     *
     * You have a long flowerbed in which some of the plots are planted, and some are not. However, flowers cannot be planted in adjacent plots.
     *
     * Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n, return true if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule and false otherwise.
     *
     * https://leetcode.com/problems/can-place-flowers/description/
     */
    bool canPlaceFlowers(std::vector<int> &flowerbed, int n)
    {
        int count = 1;
        int plants = 0;
        for (int i = 0; i < flowerbed.size(); i++)
        {
            if (flowerbed[i] == 1)
            {
                if (count == 1 || count == 2)
                {
                    plants += 0;
                }
                else
                {
                    plants += count / 2;
                }
                count = 0;
            }
            else
            {
                count++;
            }
        }

        count += 1;
        if (count == 1 || count == 2)
        {
            plants += 0;
        }
        else
        {
            plants += count / 2;
        }

        return n <= plants;
    }

    /**
     * 496. Next Greater Element I
     * The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.
     *
     * You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.
     * For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2.
     * If there is no next greater element, then the answer for this query is -1.
     *
     * Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.
     *
     * https://leetcode.com/problems/next-greater-element-i/description/
     */
    std::vector<int> nextGreaterElement(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        std::unordered_map<int, int> nextMap;
        std::stack<int> stack;
        for (int i = nums2.size() - 1; i >= 0; i--)
        {
            while (!stack.empty() && stack.top() < nums2[i])
            {
                stack.pop();
            }

            if (stack.empty())
            {
                nextMap[nums2[i]] = -1;
            }
            else
            {
                nextMap[nums2[i]] = stack.top();
            }

            stack.push(nums2[i]);
        }

        std::vector<int> result;
        for (auto &num : nums1)
        {
            result.push_back(nextMap[num]);
        }

        return result;
    }

    /**
     * 3105. Longest Strictly Increasing or Strictly Decreasing Subarray.
     *
     * You are given an array of integers nums. Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.
     *
     * https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/description/
     */
    int longestMonotonicSubarray(std::vector<int> &nums)
    {
        // int count = 1;
        // int maxSize = INT_MIN;
        // bool isIncreasing = false;
        // for (int i = 0; i < nums.size() - 1; i++)
        // {
        //     if (nums[i] > nums[i + 1])
        //     {
        //         if (isIncreasing)
        //         {
        //             isIncreasing = false;
        //             count = 2;
        //         }
        //         else
        //         {
        //             count++;
        //         }
        //     }
        //     else if (nums[i] < nums[i + 1])
        //     {
        //         if (isIncreasing)
        //         {
        //             count++;
        //         }
        //         else
        //         {
        //             isIncreasing = true;
        //             count = 2;
        //         }
        //     }
        //     else
        //     {
        //         count = 1;
        //     }
        //     maxSize = std::max(maxSize, count);
        // }

        // return maxSize;

        int inc = 1, dec = 1, maxLen = 1;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i + 1] > nums[i])
            {
                inc++;
                dec = 1;
            }
            else if (nums[i + 1] < nums[i])
            {
                dec++;
                inc = 1;
            }
            else
            {
                dec = 1;
                inc = 1;
            }
            maxLen = std::max(maxLen, std::max(inc, dec));
        }
        return maxLen;
    }

    /**
     * 2053. Kth Distinct String in an Array
     *
     * A distinct string is a string that is present only once in an array.
     *
     * Given an array of strings arr, and an integer k, return the kth distinct string present in arr. If there are fewer than k distinct strings, return an empty string "".
     * Note that the strings are considered in the order in which they appear in the array.
     *
     * https://leetcode.com/problems/kth-distinct-string-in-an-array/description/
     */
    std::string kthDistinct(std::vector<std::string> &arr, int k)
    {
        std::unordered_map<std::string, int> strMap;
        for (const auto &str : arr)
        {
            strMap[str] += 1;
        }

        for (const auto &str : arr)
        {
            if (strMap[str] == 1)
            {
                if (k == 1)
                {
                    return str;
                }
                k--;
            }
        }

        return "";
    }

    /**
     * 1800. Maximum Ascending Subarray Sum
     *
     * Given an array of positive integers nums, return the maximum possible sum of an strictly increasing subarray in nums.
     *
     * A subarray is defined as a contiguous sequence of numbers in an array.
     *
     * https://leetcode.com/problems/maximum-ascending-subarray-sum/description/
     */
    int maxAscendingSum(std::vector<int> &nums)
    {
        int maxSum = nums[0];
        int sum = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i - 1] < nums[i])
            {
                sum += nums[i];
            }
            else
            {
                sum = nums[i];
            }
            maxSum = std::max(maxSum, sum);
        }

        return maxSum;
    }
};

int main()
{
    Solution obj;

    // 2678. Number of Senior Citizens [Input]
    // std::vector<std::string> deatils = {"1313579440F2036", "2921522980M5644"};
    // std::cout << "Number of senior citizens: " << obj.countSeniors(deatils) << "\n";

    // 485. Max Consecutive Ones.
    // std::vector<int> nums = {1, 0, 1, 1, 0, 1};
    // std::cout << "Max Consecutive Ones: " << obj.findMaxConsecutiveOnes(nums) << "\n";

    // 14. Longest Common Prefix
    // std::vector<std::string> strs = {"dog", "racecar", "car"};
    // std::cout << "Longest Common Prefix: " << obj.longestCommonPrefix(strs) << "\n";

    // 1408. String Matching in an Array
    // std::vector<std::string> words = {"leetcode", "et", "code"};
    // std::vector<std::string> result = obj.stringMatching(words);
    // std::cout << "String Matching in an Array: " << std::endl;
    // for (auto &word : result)
    // {
    //     std::cout << word << ", ";
    // }
    // std::cout << std::endl;

    // 249. Group Shifted Strings
    // std::vector<std::string> words = {"abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"};
    // std::vector<std::vector<std::string>> result = obj.groupStrings(words);
    // std::cout << "Group Shifted Strings: " << std::endl;
    // for (auto &list : result)
    // {
    //     std::cout << "[ ";
    //     for (auto &str : list)
    //     {
    //         std::cout << str << ", ";
    //     }
    //     std::cout << " ]";
    // }
    // std::cout << std::endl;

    // 929. Unique Email Addresses
    // std::vector<std::string> emails = {"a@leetcode.com", "b@leetcode.com", "c@leetcode.com"};
    // std::cout << "Unique Email Addresses: " << obj.numUniqueEmails(emails) << "\n";

    // 27. Remove Element
    // std::vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    // int val = 2;
    // std::cout << "Remove Element: " << obj.removeElement(nums, val) << "\n";

    // 496. Next Greater Element I
    std::vector<int> nums1 = {2, 4};
    std::vector<int> nums2 = {1, 2, 3, 4};
    std::vector<int> result = obj.nextGreaterElement(nums1, nums2);
    for (auto &num : result)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}