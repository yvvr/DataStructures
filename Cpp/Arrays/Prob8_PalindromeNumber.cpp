/**
 * @file Prob8_PalindromeNumber.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 * Palindrome Number
 * 
 * Given an integer x, return true if x is a palindrome, and false otherwise.
 * 
 * Example 1:
 * Input: x = 121
 * Output: true
 * Explanation: 121 reads as 121 from left to right and from right to left.
 * 
 * Example 2:
 * Input: x = -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
 * 
 * Example 3:
 * Input: x = 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <string>

// Approch 1: Reversing the num with simple math.
// Time complexity -> O(n), Space Complexity -> O(1)

bool isPalindrome(int num)
{
    if (num != std::abs(num))
    {
        return false;
    }
    int temp = num, revNum = 0;

    while (temp > 0)
    {
        revNum = revNum * 10 + temp % 10;
        temp = temp / 10;
    }

    return revNum == num;
}

// Approch 1: Reversing the num using string.
// Time complexity -> O(n), Space Complexity -> O(1)

bool isPalindromeWithString(int num)
{
    if (num != std::abs(num))
    {
        return false;
    }
    std::string str = std::to_string(num);

    int len = str.length();

    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - i - 1])
        {
            return false;
        }
    }
    return true;
}

int main() {
    int num = 1212112121;

    std::cout<< "Is Palindrome: " << isPalindrome(num) << std::endl;
    std::cout<< "Is Palindrome: " << isPalindromeWithString(num) << std::endl;

    return 0;
}