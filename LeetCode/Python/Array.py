"""
Copyright (c) 2025

Author: Your Name
This file is part of the DataStructures project.

This file is licensed under the MIT License.
You may obtain a copy of the License at

https://opensource.org/licenses/MIT

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""

from typing import List


class Solution:
    """
    * 3110. Score of a String.
    *
    * You are given a string s. The score of a string is defined as the sum of the absolute difference between the ASCII values of adjacent characters.
    * Return the score of s.
    *
    * https://leetcode.com/problems/score-of-a-string/description/
    """

    def scoreOfString(self, s: str) -> int:
        score = 0
        for i in range(1, len(s)):
            score += abs(ord(s[i - 1]) - ord(s[i]))
        return score

    """
    * 1929. Concatenation of Array.
    *
    * Given an integer array nums of length n, you want to create an array ans of length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed).
    * Specifically, ans is the concatenation of two nums arrays.
    *
    * Return the array ans.
    *
    * https://leetcode.com/problems/concatenation-of-array/
    """

    def getConcatenation(self, nums: List[int]) -> List[int]:
        # res = nums.copy()
        # res.extend(nums)
        return nums + nums

    """
    * 217. Contains Duplicate
    *
    * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
    *
    * https://leetcode.com/problems/contains-duplicate/
    """

    def containsDuplicate(self, nums: List[int]) -> bool:
        res = set()
        for num in nums:
            if num in res:
                return True
            res.add(num)
        return False

    """
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
    """

    def isAnagram(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        count = [0] * 26

        for i in range(len(s)):
            count[ord(s[i]) - ord("a")] += 1
            count[ord(t[i]) - ord("a")] -= 1

        for num in count:
            if num != 0:
                return False
        return True

    """
    * Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1.
    *
    * After doing so, return the array.
    *
    * Input: arr = [17,18,5,4,6,1]
    * Output: [18,6,6,6,1,-1]
    *
    * https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/description/
    """

    def replaceElements(self, arr: List[int]) -> List[int]:
        rightMax = -1
        for i in range(len(arr) - 1, -1, -1):
            temp = arr[i]
            arr[i], rightMax = rightMax, max(temp, rightMax)
        return arr

    """
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
    *
    * https://leetcode.com/problems/is-subsequence/
    """

    def isSubsequence(self, s: str, t: str) -> bool:
        i = j = 0
        while i < len(s) and j < len(t):
            if s[i] == t[j]:
                i += 1
            j += 1
        return i == len(s)

    """
    * 2486. Append Characters to String to Make Subsequence
    *
    * You are given two strings s and t consisting of only lowercase English letters.
    *
    * Return the minimum number of characters that need to be appended to the end of s so that t becomes a subsequence of s.
    *
    * A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
    *
    * https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/description/
    """

    def appendCharacters(self, s: str, t: str) -> int:
        i = j = 0
        while i < len(s) and j < len(t):
            if s[i] == t[j]:
                j += 1
            i += 1
        return len(t) - j

    """
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
    """

    def lengthOfLastWord(self, s: str) -> int:
        i, count = len(s) - 1, 0
        while i >= 0 and s[i] == " ":
            i -= 1
        while i >= 0 and s[i] != " ":
            i -= 1
            count += 1
        return count

    """
    * 422. Valid Word Square
    *
    * Given an array of strings words, return true if it forms a valid word square.
    *
    * A sequence of strings forms a valid word square if the kth row and column read the same string, where 0 <= k < max(numRows, numColumns).
    *
    * https://leetcode.com/problems/valid-word-square/description/
    """

    def validWordSquare(self, words: List[str]) -> bool:
        for i in range(len(words)):
            for j in range(len(words[i])):
                if j >= len(words) or i >= len(words[j]) or words[i][j] != words[j][i]:
                    return False
        return True


if __name__ == "__main__":
    pass
