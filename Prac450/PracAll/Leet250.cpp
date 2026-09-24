#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <deque>

/**
 * 1929. Concatenation of Array.
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
 */
bool containsDuplicate(std::vector<int> &nums)
{
    std::unordered_set<int> set;
    for (auto num : nums)
    {
        if (set.find(num) != set.end())
        {
            return true;
        }
        set.insert(num);
    }
    return false;
}

/**
 * 242. Valid Anagram
 */

bool isAnagram(std::string s, std::string t)
{
    if (s.length() != t.length())
    {
        return false;
    }

    std::unordered_map<char, int> map;

    for (int i = 0; i < s.length(); i++)
    {
        map[s[i]] += 1;
        map[t[i]] -= 1;
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

bool isAnagram2(std::string s, std::string t)
{
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
 * 1. Two Sum
 */

std::vector<int> twoSum(std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> map;
    std::vector<int> res;

    for (int i = 0; i < nums.size(); i++)
    {
        if (map.find(target - nums[i]) != map.end())
        {
            res.push_back(map[target - nums[i]]);
            res.push_back(i);
            return res;
        }
        map.insert(std::make_pair(nums[i], i));
    }

    return res;
}

/**
 * 14. Longest Common Prefix
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
 * 49. Group Anagrams
 */
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs)
{
    std::unordered_map<std::string, std::vector<std::string>> map;
    std::vector<std::vector<std::string>> res;

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
        res.push_back(pair.second);
    }
    return res;
}

/**
 * 27. Remove Element
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
 * 169. Majority Element
 */
int majorityElement(std::vector<int> &nums)
{
    int count = 0, res = -1;
    for (auto &num : nums)
    {
        if (count == 0)
        {
            res = num;
        }
        count += (num == res) ? 1 : -1;
    }
    return res;
}

/**
 * 705. Design HashSet
 */
class MyHashSet
{
private:
    std::array<std::vector<int>, 10000> arr;

public:
    MyHashSet() {}

    void add(int key)
    {
        auto &vec = arr[key % 10000];
        if (std::find(vec.begin(), vec.end(), key) == vec.end())
        {
            arr[key % 10000].push_back(key);
        }
    }

    void remove(int key)
    {
        auto &vec = arr[key % 10000];
        vec.erase(std::remove(vec.begin(), vec.end(), key), vec.end());
    }

    bool contains(int key)
    {
        const auto &vec = arr[key % 10000];
        return std::find(vec.begin(), vec.end(), key) != vec.end();
    }
};

struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int val, ListNode *next)
    {
        this->val = val;
        this->next = next;
    }
};

class MyHashSetLL
{
private:
    std::vector<ListNode *> set;

public:
    MyHashSetLL()
    {
        set.resize(10000);
        for (auto &node : set)
        {
            node = new ListNode(0, nullptr);
        }
    }

    void add(int key)
    {
        auto curr = set[key % 10000];
        while (curr->next)
        {
            if (curr->next->val == key)
            {
                return;
            }
            curr = curr->next;
        }
        curr->next = new ListNode(key, nullptr);
    }

    void remove(int key)
    {
        auto first = set[key % 10000];
        ListNode *prev = first, *curr = first->next;
        while (curr)
        {
            if (curr->val == key)
            {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    bool contains(int key)
    {
        auto curr = set[key % 10000];
        while (curr->next)
        {
            if (curr->next->val == key)
            {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
};

/**
 * 706. Design HashMap
 */

struct MapListNode
{
    int key;
    int val;
    MapListNode *next;

    MapListNode(int key, int val, MapListNode *next)
    {
        this->key = key;
        this->val = val;
        this->next = next;
    }
};

class MyHashMap
{
private:
    std::vector<MapListNode *> map;

public:
    MyHashMap()
    {
        map.resize(10000);
        for (auto &node : map)
        {
            node = new MapListNode(0, 0, nullptr);
        }
    }

    void put(int key, int value)
    {
        auto curr = map[key % 10000];
        while (curr->next)
        {
            if (curr->next->key == key)
            {
                curr->next->val = value;
                return;
            }
            curr = curr->next;
        }
        curr->next = new MapListNode(key, value, nullptr);
    }

    int get(int key)
    {
        auto curr = map[key % 10000];
        while (curr->next)
        {
            if (curr->next->key == key)
            {
                return curr->next->val;
            }
            curr = curr->next;
        }
        return -1;
    }

    void remove(int key)
    {
        auto first = map[key % 10000];
        MapListNode *prev = first, *curr = first->next;
        while (curr)
        {
            if (curr->key == key)
            {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
};

class MyHashMap
{
private:
    std::array<std::vector<std::pair<int, int>>, 10000> arr;

public:
    void put(int key, int value)
    {
        auto &vec = arr[key % 10000];
        auto it = std::find_if(
            vec.begin(), vec.end(),
            [key](const std::pair<int, int> &p)
            { return p.first == key; });
        if (it == vec.end())
        {
            vec.push_back({key, value});
        }
        else
        {
            *it = {key, value};
        }
    }

    int get(int key)
    {
        auto &vec = arr[key % 10000];
        auto it = std::find_if(
            vec.begin(), vec.end(),
            [key](const std::pair<int, int> &p)
            { return p.first == key; });
        return it == vec.end() ? -1 : it->second;
    }

    void remove(int key)
    {
        auto &vec = arr[key % 10000];
        auto it = std::remove_if(
            vec.begin(), vec.end(),
            [key](const std::pair<int, int> &p)
            { return p.first == key; });
        vec.erase(it, vec.end());
    }
};

/**
 * 912. Sort an Array
 */
void merge(std::vector<int> &arr, int l, int m, int r)
{
    int i = l, j = m + 1, k = 0;
    std::vector<int> temp(r - l + 1);
    while (i <= m && j <= r)
    {
        if (arr[i] < arr[j])
        {
            temp[k] = arr[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
            k++;
        }
    }

    while (i <= m)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= r)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int i = l; i <= r; i++)
    {
        arr[i] = temp[i - l];
    }
}

void mergeSort(std::vector<int> &arr, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

std::vector<int> sortArray(std::vector<int> &nums)
{
    if (!nums.empty())
    {
        mergeSort(nums, 0, nums.size() - 1);
    }
    return nums;
}

void heapify(std::vector<int> &arr, int n, int i)
{
    int l = (i << 1) + 1;
    int r = (i << 1) + 2;
    int largestNode = i;

    if (l < n && arr[l] > arr[largestNode])
    {
        largestNode = l;
    }

    if (r < n && arr[r] > arr[largestNode])
    {
        largestNode = r;
    }

    if (largestNode != i)
    {
        std::swap(arr[i], arr[largestNode]);
        heapify(arr, n, largestNode);
    }
}

void heapSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/**
 * 75. Sort Colors
 */
void sortColors(std::vector<int> &nums)
{
    int l = 0, r = nums.size() - 1;
    int i = 0;

    while (i <= r)
    {
        if (nums[i] == 0)
        {
            std::swap(nums[i], nums[l]);
            i++;
            l++;
        }
        else if (nums[i] == 2)
        {
            std::swap(nums[i], nums[r]);
            r--;
        }
        else
        {
            i++;
        }
    }
}

/**
 * 347. Top K Frequent Elements
 */
std::vector<int> topKFrequent(std::vector<int> &nums, int k)
{
    if (nums.size() == k)
    {
        return nums;
    }

    std::map<int, int> freqMap;
    std::vector<int> result;

    for (int i = 0; i < nums.size(); i++)
    {
        freqMap[nums[i]] += 1;
    }

    auto comp = [&freqMap](int below, int above)
    {
        return freqMap[below] > freqMap[above];
    };
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);

    for (auto freq : freqMap)
    {
        pq.push(freq.first);
        if (pq.size() > k)
        {
            pq.pop();
        }
    }

    while (!pq.empty())
    {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}

std::string encode(std::vector<std::string> &strs)
{
    std::string ans;
    for (std::string &str : strs)
    {
        ans += std::to_string(str.length());
        ans += "#";
        ans += str;
    }
    return ans;
}

std::vector<std::string> decode(std::string s)
{
    std::vector<std::string> res;
    int i = 0;
    while (i < s.size())
    {
        int j = i;
        while (s[j] != '#')
        {
            j++;
        }
        int length = std::stoi(s.substr(i, j - i));
        i = j + 1;
        j = i + length;
        res.push_back(s.substr(i, length));
        i = j;
    }
    return res;
}

/**
 * 304. Range Sum Query 2D - Immutable
 */
class NumMatrix
{
    std::vector<std::vector<int>> sum;

public:
    NumMatrix(std::vector<std::vector<int>> &matrix)
    {
        int ROWS = matrix.size(), COLS = matrix[0].size();
        sum = std::vector<std::vector<int>>(ROWS + 1, std::vector<int>(COLS + 1, 0));

        for (int r = 0; r < ROWS; r++)
        {
            int preSum = 0;
            for (int c = 0; c < COLS; c++)
            {
                preSum += matrix[r][c];
                int above = sum[r][c + 1];
                sum[r + 1][c + 1] = preSum + above;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        row1++;
        col1++;
        row2++;
        col2++;
        int bottomRight = sum[row2][col2];
        int above = sum[row1 - 1][col2];
        int left = sum[row2][col1 - 1];
        int topLeft = sum[row1 - 1][col1 - 1];
        return bottomRight - above - left + topLeft;
    }
};

/**
 * 122. Best Time to Buy and Sell Stock II
 */
int maxProfit(std::vector<int> &prices)
{
    int profit = 0;
    for (int i = 1; i < prices.size(); i++)
    {
        if (prices[i] > prices[i - 1])
        {
            profit += prices[i] - prices[i - 1];
        }
    }
    return profit;
}

/**
 * 229. Majority Element II
 */
std::vector<int> majorityElementII(std::vector<int> &nums)
{
    std::unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++)
    {
        map[nums[i]] += 1;
        if (map.size() > 2)
        {
            for (auto it = map.begin(); it != map.end();)
            {
                it->second--;

                if (it->second == 0)
                {
                    it = map.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    std::vector<int> res;
    for (auto &pair : map)
    {
        int frequency = 0;
        for (int num : nums)
        {
            if (num == pair.first)
                frequency++;
        }

        if (frequency > nums.size() / 3)
        {
            res.push_back(pair.first);
        }
    }

    return res;
}

/**
 * 560. Subarray Sum Equals K
 */
int subarraySum(std::vector<int> &nums, int k)
{
    std::unordered_map<int, int> map = {{0, 1}};
    int pSum = 0, res = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        pSum += nums[i];
        if (map.find(pSum - k) != map.end())
        {
            res += map[pSum - k];
        }
        map[pSum] += 1;
    }
    return res;
}

/**
 * 41. First Missing Positive
 */
int firstMissingPositive(std::vector<int> &nums)
{
    for (auto &num : nums)
    {
        if (num < 0)
        {
            num = 0;
        }
    }

    for (int i = 0; i < nums.size(); i++)
    {
        int pos = std::abs(nums[i]) - 1;
        if (pos >= 0 && pos < nums.size())
        {
            nums[pos] = nums[pos] == 0 ? -1 * (nums.size() + 1) : std::abs(nums[pos]) * -1;
        }
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] >= 0)
        {
            return i + 1;
        }
    }
    return nums.size() + 1;
}

/**
 * 344. Reverse String
 */
void reverseString(std::vector<char> &s)
{
    int l = 0, r = s.size() - 1;
    while (l < r)
    {
        std::swap(s[l], s[r]);
        l++;
        r--;
    }
}

/**
 * 125. Valid Palindrome
 */
bool isPalindrome(std::string s)
{
    int l = 0, r = s.length() - 1;
    while (l < r)
    {
        while (l < r && !std::isalnum(s[l]))
        {
            l++;
        }
        while (l < r && !std::isalnum(s[r]))
        {
            r--;
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
 * 680. Valid Palindrome II
 */
bool ispalindrome(std::string &s, int l, int r)
{
    while (l < r)
    {
        if (s[l] != s[r])
        {
            return false;
        }
        l++;
        r--;
    }
    return true;
}
bool validPalindrome(std::string s)
{
    int l = 0, r = s.length() - 1;
    while (l < r && s[l] == s[r])
    {
        l++;
        r--;
    }
    return ispalindrome(s, l + 1, r) || ispalindrome(s, l, r - 1);
}

/**
 * 1768. Merge Strings Alternately
 */
std::string mergeAlternately(std::string word1, std::string word2)
{
    int l = 0, r = 0;
    std::string res;
    while (l < word1.length() && r < word2.length())
    {
        res += word1[l++];
        res += word2[r++];
    }
    while (l < word1.length())
    {
        res += word1[l++];
    }
    while (r < word2.length())
    {
        res += word2[r++];
    }
    return res;
}

/**
 * 26. Remove Duplicates from Sorted Array
 */
int removeDuplicates(std::vector<int> &nums)
{
    int l = 1, r = 1;
    while (r < nums.size())
    {
        if (nums[r - 1] == nums[r])
        {
            r++;
            continue;
        }
        nums[l++] = nums[r++];
    }
    return l;
}

/**
 * 18. 4Sum
 */
void kSum(std::vector<int> &nums, std::vector<int> &quad, std::vector<std::vector<int>> &res, int k, int start, int target)
{
    if (k == 2)
    {
        int l = start, r = nums.size() - 1;
        while (l < r)
        {
            int sum = nums[l] + nums[r];
            if (sum == target)
            {
                quad.push_back(nums[l]);
                quad.push_back(nums[r]);
                res.push_back(quad);
                quad.pop_back();
                quad.pop_back();
                l++;
                r--;
                while (l < r && nums[l] == nums[l - 1])
                    l++;
                while (l < r && nums[r] == nums[r + 1])
                    r--;
            }
            else if (sum > target)
            {
                r--;
            }
            else
            {
                l++;
            }
        }
        return;
    }

    for (int i = start; i < nums.size() - k + 1; i++)
    {
        if (i > start && nums[i] == nums[i - 1])
        {
            continue;
        }
        quad.push_back(nums[i]);
        kSum(nums, quad, res, k - 1, i + 1, target - nums[i]);
        quad.pop_back();
    }
}

std::vector<std::vector<int>> nSum(std::vector<int> &nums, int target)
{
    std::vector<std::vector<int>> res;
    std::vector<int> quad;
    if (nums.size() < 4)
    {
        return {};
    }

    std::sort(nums.begin(), nums.end());
    kSum(nums, quad, res, 4, 0, target);
    return res;
}

/**
 * 189. Rotate Array
 */
void reverse(std::vector<int> &nums, int l, int r)
{
    while (l < r)
    {
        std::swap(nums[l], nums[r]);
        l++;
        r--;
    }
}

void rotate(std::vector<int> &nums, int k)
{
    int n = nums.size();
    k %= n;

    reverse(nums, 0, k - 1);
    reverse(nums, k, n - 1);
    reverse(nums, 0, n - 1);
}

/**
 * 881. Boats to Save People
 */
int numRescueBoats(std::vector<int> &people, int limit)
{
    int l = 0, r = people.size() - 1;
    int boats = 0;
    std::sort(people.begin(), people.end());

    while (l < r)
    {
        if (people[l] + people[r] <= limit)
        {
            l++;
            r--;
        }
        else if (people[l] > people[r])
        {
            l++;
        }
        else
        {
            r--;
        }
        boats++;
    }
    return boats;
}

/**
 * 42. Trapping Rain Water
 */
int trap(std::vector<int> &height)
{
    if (height.empty())
    {
        return 0;
    }

    int l = 0, r = height.size() - 1;
    int leftMax = height[l], rightMax = height[r];
    int res = 0;
    while (l < r)
    {
        if (leftMax < rightMax)
        {
            l++;
            leftMax = std::max(leftMax, height[l]);
            res += leftMax - height[l];
        }
        else
        {
            r--;
            rightMax = std::max(rightMax, height[r]);
            res += rightMax - height[r];
        }
    }
    return res;
}

/**
 * 567. Permutation in String
 */
bool isValidIncl(std::array<int, 26> &s1map, std::array<int, 26> &s2map)
{
    for (int i = 0; i <= 26; i++)
    {
        if (s1map[i] < s2map[i])
        {
            return false;
        }
    }
    return true;
}

bool checkInclusion(std::string s1, std::string s2)
{
    // std::array<int, 26> s1map = {0};
    // std::array<int, 26> s2map = {0};
    // int l = 0, r = 0;

    // for (int i = 0; i < s1.length(); i++)
    // {
    //     s1map[s1[i] - 'a'] += 1;
    // }

    // while (r < s2.length())
    // {
    //     s2map[s2[r] - 'a'] += 1;
    //     while (isValidIncl(s1map, s2map))
    //     {
    //         if (r - l + 1 == s1.size())
    //         {
    //             return true;
    //         }
    //         s2map[s2[l] - 'a'] -= 1;
    //         l++;
    //     }
    //     r++;
    // }

    // return false;

    if (s1.length() > s2.length())
    {
        return false;
    }

    std::vector<int> s1Count(26, 0);
    std::vector<int> s2Count(26, 0);
    for (int i = 0; i < s1.length(); i++)
    {
        s1Count[s1[i] - 'a']++;
        s2Count[s2[i] - 'a']++;
    }

    int matches = 0;
    for (int i = 0; i < 26; i++)
    {
        if (s1Count[i] == s2Count[i])
        {
            matches++;
        }
    }

    int l = 0;
    for (int r = s1.length(); r < s2.length(); r++)
    {
        if (matches == 26)
        {
            return true;
        }

        int index = s2[r] - 'a';
        s2Count[index]++;
        if (s1Count[index] == s2Count[index])
        {
            matches++;
        }
        else if (s1Count[index] + 1 == s2Count[index])
        {
            matches--;
        }

        index = s2[l] - 'a';
        s2Count[index]--;
        if (s1Count[index] == s2Count[index])
        {
            matches++;
        }
        else if (s1Count[index] - 1 == s2Count[index])
        {
            matches--;
        }
        l++;
    }

    return matches == 26;
}

/**
 * 209. Minimum Size Subarray Sum
 */
int minSubArrayLen(int target, std::vector<int> &nums)
{
    int l = 0, r = 0, sum = 0;
    int minLen = INT_MAX;
    while (r < nums.size())
    {
        sum += nums[r];
        while (sum >= target)
        {
            minLen = std::min(minLen, r - l + 1);
            sum -= nums[l];
            l++;
        }
        r++;
    }

    return minLen == INT_MAX ? 0 : minLen;
}

/**
 * 658. Find K Closest Elements
 */
std::vector<int> findClosestElements(std::vector<int> &arr, int k, int x)
{
    // int l = 0, r = arr.size() - 1;
    // while (l < r)
    // {
    //     int mid = (l + r) / 2;
    //     if (arr[mid] < x)
    //     {
    //         l = mid + 1;
    //     }
    //     else
    //     {
    //         r = mid;
    //     }
    // }

    // l = l - 1;
    // r = l + 1;
    // while (r - l - 1 < k)
    // {
    //     if (l < 0)
    //     {
    //         r++;
    //     }
    //     else if (r >= arr.size())
    //     {
    //         l--;
    //     }
    //     else if (abs(arr[l] - x) <= abs(arr[r] - x))
    //     {
    //         l--;
    //     }
    //     else
    //     {
    //         r++;
    //     }
    // }

    // return std::vector<int>(arr.begin() + l + 1, arr.begin() + r);

    int l = 0, r = arr.size() - k;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (x - arr[mid] > arr[mid + k] - x)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return std::vector<int>(arr.begin() + l, arr.begin() + l + k);
}

/**
 * 239. Sliding Window Maximum
 */
std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k)
{
    std::deque<int> queue;
    std::vector<int> res;
    int l = 0;

    for (int r = 0; r < nums.size(); r++)
    {
        while (queue.size() > 0 && nums[queue.back()] < nums[r])
        {
            queue.pop_back();
        }

        queue.push_back(r);

        if (l > queue.front())
        {
            queue.pop_front();
        }

        if (r >= k - 1)
        {
            res.push_back(nums[queue.front()]);
            l++;
        }
    }
    return res;
}

/**
 * 136. Single Number
 */
int singleNumber(std::vector<int> &nums)
{
    int res = 0;
    for (auto num : nums)
    {
        res = res ^ num;
    }
    return res;
}

/**
 * 191. Number of 1 Bits
 */
int hammingWeight(int n)
{
    int count = 0;
    while (n)
    {
        count += n & 1;
        n = n >> 1;
    }
    return count;
}

/**
 * 338. Counting Bits
 */
std::vector<int> countBits(int n)
{
    std::vector<int> result(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        result[i] = result[i >> 1] + (i & 1);
    }
    return result;
}

/**
 * 67. Add Binary
 */
std::string addBinary(std::string a, std::string b)
{
    // std::reverse(a.begin(), a.end());
    // std::reverse(b.begin(), b.end());

    // int i = 0, carry = 0;
    // std::string res;
    // while (i < std::max(a.size(), b.size()))
    // {
    //     int abit = i < a.size() ? a[i] - '0' : 0;
    //     int bbit = i < b.size() ? b[i] - '0' : 0;
    //     int sum = abit + bbit + carry;
    //     res = std::to_string(sum % 2) + res;
    //     carry = sum / 2;
    //     i++;
    // }

    // if (carry != 0)
    // {
    //     res = std::to_string(1) + res;
    // }
    // return res;

    std::string res = "";
    int carry = 0;

    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0)
    {
        int digitA = i >= 0 ? a[i] - '0' : 0;
        int digitB = j >= 0 ? b[j] - '0' : 0;

        int sum = digitA + digitB + carry;
        res = std::to_string(sum % 2) + res;
        carry = sum / 2;

        i--;
        j--;
    }

    return res;
}

/**
 * 7. Reverse Integer
 */
int reverse(int x)
{
    // [-2^31, 2^31 - 1]
    // [-2147483648, 2147483647]
    int min = INT32_MIN, max = INT32_MAX;
    int sum = 0;
    while (x != 0)
    {
        int digit = x % 10;
        if (sum > max / 10 || (sum == max / 10 && digit > max % 10))
        {
            return 0;
        }
        if (sum < min / 10 || (sum == min / 10 && digit < min % 10))
        {
            return 0;
        }
        sum = sum * 10 + digit;
        x = x / 10;
    }
    return sum;
}

/**
 * 201. Bitwise AND of Numbers Range
 */
int rangeBitwiseAnd(int left, int right)
{
    int count = 0;
    while (left != right)
    {
        left >>= 1;
        right >>= 1;
        count++;
    }
    return left << count;
}

/**
 * 3133. Minimum Array End
 */
long long minEnd(int n, int x)
{
    long long res = x;
    long long x_i = 1, n_i = 1;

    while (n_i <= n - 1)
    {
        if ((x_i & x) == 0)
        {
            if ((n_i & n) == 1)
            {
                res = res | x_i;
            }
            n_i = n_i << 1;
        }
        x_i = x_i << 1;
    }
    return res;
}

int main()
{
    return 0;
}