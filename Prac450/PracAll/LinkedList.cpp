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
#include <unordered_set>
#include <unordered_map>

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
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class MyLinkedList
{
    ListNode *head;
    ListNode *tail;
    int length = 0;

public:
    MyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    int get(int index)
    {
        if (index > length - 1)
        {
            return -1;
        }

        ListNode *curr = head;
        while (index > 0)
        {
            curr = curr->next;
            index--;
        }
        return curr->val;
    }

    void addAtHead(int val)
    {
        ListNode *temp = new ListNode(val);
        temp->next = head;
        head = temp;
        if (tail == nullptr)
        {
            tail = temp;
        }

        length++;
    }

    void addAtTail(int val)
    {
        ListNode *temp = new ListNode(val);

        if (tail == nullptr)
        {
            tail = temp;
            head = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }

        length++;
    }

    void addAtIndex(int index, int val)
    {
        if (index > length)
        {
            return;
        }

        if (index == 0)
        {
            addAtHead(val);
            return;
        }

        if (index == length)
        {
            addAtTail(val);
            return;
        }

        ListNode *curr = head, *prev = nullptr;
        while (index > 0)
        {
            prev = curr;
            curr = curr->next;
            index--;
        }

        ListNode *temp = new ListNode(val);
        prev->next = temp;
        temp->next = curr;
        length++;
    }

    void deleteAtIndex(int index)
    {
        if (index > length - 1)
        {
            return;
        }

        ListNode *curr = head, dummy(0, head), *prev = &dummy;
        int i = index;
        while (i > 0)
        {
            prev = curr;
            curr = curr->next;
            i--;
        }

        prev->next = curr->next;
        head = dummy.next;
        if (index == length - 1)
        {
            tail = prev == &dummy ? nullptr : prev;
        }

        length--;
    }
};

class Solution
{
public:
    /**
     * Helper functions.
     */
    ListNode *createLikedList(std::vector<int> input)
    {
        ListNode *head = nullptr;
        for (int i = input.size() - 1; i >= 0; i--)
        {
            head = new ListNode(input.at(i), head);
        }
        return head;
    }

    Node *createNodeList(std::vector<std::vector<int>> input)
    {
        std::unordered_map<int, Node *> map;
        Node dummy(0), *prev = &dummy, *curr = nullptr;
        int i = 0;
        for (int i = 0; i < input.size(); i++)
        {
            curr = new Node(input.at(i).at(0));
            prev->next = curr;
            prev = prev->next;
            map[i] = curr;
        }

        curr = dummy.next;
        for (int i = 0; i < input.size(); i++)
        {
            curr->random = input.at(i).at(1) == -1 ? nullptr : map[input.at(i).at(1)];
            curr = curr->next;
        }
        return dummy.next;
    }

    void printLikedList(ListNode *head)
    {
        while (head)
        {
            std::cout << head->val << "->";
            head = head->next;
        }
        std::cout << "null" << std::endl;
    }

    void printNodeList(Node *head)
    {
        while (head)
        {
            std::cout << head->val << "->";
            head = head->next;
        }
        std::cout << "null" << std::endl;
    }

    template <typename T>
    void printVector(std::vector<T> vec)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            std::cout << vec[i] << ",";
        }
    }

    // List starts from here.
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
        if (head == nullptr)
        {
            return head;
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
     * 21. Merge Two Sorted Lists.
     *
     * You are given the heads of two sorted linked lists list1 and list2.
     * Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
     * Return the head of the merged linked list.
     *
     * https://leetcode.com/problems/merge-two-sorted-lists/description/
     */
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *dummyNode = new ListNode();
        ListNode *temp = dummyNode;

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

        ListNode *head = dummyNode->next;
        delete (dummyNode);

        return head;
    }

    /**
     * 141. Linked List Cycle.
     *
     * Given head, the head of a linked list, determine if the linked list has a cycle in it.
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
     * 234. Palindrome Linked List.
     *
     * Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
     * https://leetcode.com/problems/palindrome-linked-list/description/
     */
    bool isPalindrome(ListNode *head)
    {
        ListNode *slowPointer = head, *fastPointer = head;

        while (fastPointer != nullptr && fastPointer->next != nullptr)
        {
            slowPointer = slowPointer->next;
            fastPointer = fastPointer->next->next;
        }

        ListNode *newHead = reverseList(slowPointer);
        ListNode *left = head, *right = newHead;
        while (right != nullptr)
        {
            if (left->val != right->val)
            {
                return false;
            }
            left = left->next;
            right = right->next;
        }

        return true;
    }

    /**
     * 203. Remove Linked List Elements.
     *
     * Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.
     * https://leetcode.com/problems/remove-linked-list-elements/description/
     */
    ListNode *removeElements(ListNode *head, int val)
    {
        ListNode dummy(0, head);
        ListNode *curr = head, *prev = &dummy;

        while (curr)
        {
            if (curr->val == val)
            {
                prev->next = curr->next;
            }
            else
            {
                prev = curr;
            }
            curr = curr->next;
        }

        return dummy.next;
    }

    /**
     * 83. Remove Duplicates from Sorted List.
     *
     * Given the head of a sorted linked list, delete all duplicates such that each element appears only once.
     * Return the linked list sorted as well.
     *
     * https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
     */
    ListNode *deleteDuplicates(ListNode *head)
    {
        // ListNode dummy(INT_MIN, head);
        // ListNode *curr = head, *prev = &dummy;

        // while (curr)
        // {
        //     if (prev->val == curr->val)
        //     {
        //         prev->next = curr->next;
        //     }
        //     else
        //     {
        //         prev = curr;
        //     }
        //     curr = curr->next;
        // }

        // return dummy.next;

        ListNode *curr = head;
        while (curr && curr->next)
        {
            if (curr->next->val == curr->val)
            {
                curr->next = curr->next->next;
            }
            else
            {
                curr = curr->next;
            }
        }

        return head;
    }

    /**
     * 876. Middle of the Linked List.
     *
     * Given the head of a singly linked list, return the middle node of the linked list.
     * If there are two middle nodes, return the second middle node.
     *
     * https://leetcode.com/problems/middle-of-the-linked-list/description/
     */
    ListNode *middleNode(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    /**
     * 160. Intersection of Two Linked Lists.
     *
     * Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.
     * For example, the following two linked lists begin to intersect at node c1:
     *
     * The test cases are generated such that there are no cycles anywhere in the entire linked structure.
     * Note that the linked lists must retain their original structure after the function returns.
     *
     * https://leetcode.com/problems/intersection-of-two-linked-lists/description/
     */
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *listA = headA, *listB = headB;
        while (listA != listB)
        {
            listA = listA ? listA->next : headB;
            listB = listB ? listB->next : headA;
        }
        return listA;
    }

    /**
     * 1669. Merge In Between Linked Lists.
     *
     * You are given two linked lists: list1 and list2 of sizes n and m respectively.
     * Remove list1's nodes from the ath node to the bth node, and put list2 in their place.
     *
     * https://leetcode.com/problems/merge-in-between-linked-lists/description/
     */
    ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2)
    {
        // int cnt = 0;
        // ListNode dummy(0, list1);
        // ListNode *curr1 = list1, *curr2 = list2, *prev1 = &dummy, *prev2 = nullptr;
        // while (curr1 && cnt <= b)
        // {
        //     if (cnt == a)
        //     {
        //         prev1->next = list2;
        //     }
        //     prev1 = curr1;
        //     curr1 = curr1->next;
        //     cnt++;
        // }
        // while (curr2)
        // {
        //     prev2 = curr2;
        //     curr2 = curr2->next;
        // }
        // prev1->next = nullptr;
        // prev2->next = curr1;

        // return dummy.next;

        ListNode *curr = list1;
        int i = 0;
        while (i < a - 1)
        {
            curr = curr->next;
            i++;
        }

        ListNode *tail1 = curr;
        while (i <= b)
        {
            curr = curr->next;
            i++;
        }

        tail1->next = list2;
        while (list2->next)
        {
            list2 = list2->next;
        }
        list2->next = curr;

        return list1;
    }

    /**
     * 143. Reorder List.
     *
     * You are given the head of a singly linked-list. The list can be represented as:
     * L0 → L1 → … → Ln - 1 → Ln
     *
     * Reorder the list to be on the following form:
     * L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
     *
     * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
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
     * 2130. Maximum Twin Sum of a Linked List.
     *
     * In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.
     * https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/description/
     */
    int pairSum(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *curr1 = head;
        ListNode *curr2 = reverseList(slow);
        int maxTwinSum = 0;
        while (curr2)
        {
            maxTwinSum = std::max(maxTwinSum, curr1->val + curr2->val);
            curr1 = curr1->next;
            curr2 = curr2->next;
        }

        return maxTwinSum;
    }

    /**
     * 2487. Remove Nodes From Linked List.
     *
     * You are given the head of a linked list.
     * Remove every node which has a node with a greater value anywhere to the right side of it.
     *
     * Return the head of the modified linked list.
     *
     * https://leetcode.com/problems/remove-nodes-from-linked-list/description/
     */
    ListNode *removeNodes(ListNode *head)
    {
        ListNode *newHead = reverseList(head), *prev = newHead, *curr = newHead->next;
        while (curr)
        {
            if (prev->val > curr->val)
            {
                prev->next = curr->next;
            }
            else
            {
                prev = curr;
            }
            curr = curr->next;
        }

        return reverseList(newHead);
    }

    /**
     * 2181. Merge Nodes in Between Zeros.
     *
     * You are given the head of a linked list, which contains a series of integers separated by 0's. The beginning and end of the linked list will have Node.val == 0.
     * For every two consecutive 0's, merge all the nodes lying in between them into a single node whose value is the sum of all the merged nodes.
     * The modified list should not contain any 0's.
     *
     * https://leetcode.com/problems/merge-nodes-in-between-zeros/description/
     */
    ListNode *mergeNodes(ListNode *head)
    {
        // ListNode *curr = head;
        // ListNode dummy, *prev = &dummy;
        // int sum = 0;
        // while (curr)
        // {
        //     if (curr->val == 0)
        //     {
        //         if (sum != 0)
        //         {
        //             prev->next = new ListNode(sum);
        //             prev = prev->next;
        //         }
        //         sum = 0;
        //     }
        //     else
        //     {
        //         sum += curr->val;
        //     }
        //     curr = curr->next;
        // }

        // return dummy.next;

        ListNode *curr = head->next;
        ListNode *prev = head;
        int sum = 0;
        while (curr)
        {
            if (curr->val != 0)
            {
                sum += curr->val;
            }
            else
            {
                if (sum != 0)
                {
                    curr->val = sum;
                    prev->next = curr;
                    prev = curr;
                }

                sum = 0;
            }
            curr = curr->next;
        }

        return head->next;
    }

    /**
     * 2058. Find the Minimum and Maximum Number of Nodes Between Critical Points.
     *
     * A critical point in a linked list is defined as either a local maxima or a local minima.
     *
     * A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.
     * A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.
     * Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.
     *
     * Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points.
     * If there are fewer than two critical points, return [-1, -1].
     *
     * https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/description/
     */
    std::vector<int> nodesBetweenCriticalPoints(ListNode *head)
    {
        int i = 1, headVal = 0, tailVal = 0;
        ListNode *prev = head;
        ListNode *curr = head->next;
        int min = INT_MAX;
        while (curr)
        {
            if (curr->next &&
                ((curr->val > prev->val && curr->val > curr->next->val) ||
                 (curr->val < prev->val && curr->val < curr->next->val)))
            {
                if (headVal == 0)
                {
                    headVal = i + 1;
                    tailVal = i + 1;
                }
                else
                {
                    min = std::min(min, (i + 1) - tailVal);
                    tailVal = i + 1;
                }
            }
            i++;
            prev = curr;
            curr = curr->next;
        }
        return headVal == tailVal ? std::vector<int>{-1, -1} : std::vector<int>{min, tailVal - headVal};
    }

    /**
     * 3217. Delete Nodes From Linked List Present in Array.
     *
     * You are given an array of integers nums and the head of a linked list.
     * Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.
     *
     * https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/description/
     */
    ListNode *modifiedList(std::vector<int> &nums, ListNode *head)
    {
        std::unordered_set<int> numSet;
        for (int i = 0; i < nums.size(); i++)
        {
            numSet.insert(nums[i]);
        }

        ListNode *curr = head, dummy(0, head), *prev = &dummy;

        while (curr)
        {
            if (numSet.find(curr->val) != numSet.end())
            {
                prev->next = curr->next;
            }
            else
            {
                prev = curr;
            }
            curr = curr->next;
        }

        return dummy.next;
    }

    /**
     * 1721. Swapping Nodes in a Linked List.
     *
     * You are given the head of a linked list, and an integer k.
     * Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
     *
     * https://leetcode.com/problems/swapping-nodes-in-a-linked-list/description/
     */
    ListNode *swapNodes(ListNode *head, int k)
    {
        ListNode *curr = head, *leftNode = nullptr, *rightNode = nullptr;

        while (k > 1)
        {
            curr = curr->next;
            k--;
        }

        leftNode = curr;
        rightNode = head;
        while (curr->next)
        {
            curr = curr->next;
            rightNode = rightNode->next;
        }

        std::swap(rightNode->val, leftNode->val);
        return head;
    }

    /**
     * 138. Copy List with Random Pointer.
     *
     * A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.
     * Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node.
     * Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state.
     * None of the pointers in the new list should point to nodes in the original list.
     *
     * https://leetcode.com/problems/copy-list-with-random-pointer/description/
     */
    Node *copyRandomList(Node *head)
    {
        // std::unordered_map<Node *, Node *> map;
        // Node *curr = head, dummy(0), *dPrev = &dummy;
        // while (curr)
        // {
        //     dPrev->next = new Node(curr->val);
        //     map[curr] = dPrev->next;
        //     dPrev = dPrev->next;
        //     curr = curr->next;
        // }

        // curr = head;
        // while (curr)
        // {
        //     map[curr]->random = map[curr->random];
        //     curr = curr->next;
        // }

        // return dummy.next;

        Node dummy(0), *curr = head, *prev = nullptr;

        while (curr)
        {
            Node *temp = new Node(curr->val);
            Node *nxt = curr->next;
            curr->next = temp;
            temp->next = nxt;
            curr = nxt;
        }

        curr = head;
        while (curr)
        {
            curr->next->random = curr->random ? curr->random->next : nullptr;
            curr = curr->next->next;
        }

        curr = head, prev = &dummy;
        while (curr)
        {
            Node *temp = curr->next;
            curr->next = temp->next;
            prev->next = temp;
            prev = prev->next;
            curr = curr->next;
        }

        return dummy.next;
    }

    /**
     * 2. Add Two Numbers.
     * You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit.
     * Add the two numbers and return the sum as a linked list.
     *
     * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
     *
     * https://leetcode.com/problems/add-two-numbers/description/
     */
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode dummy, *prev = &dummy;
        int carry = 0;

        while (l1 || l2 || carry != 0)
        {
            int d1 = l1 ? l1->val : 0;
            int d2 = l2 ? l2->val : 0;
            int val = d1 + d2 + carry;
            carry = val / 10;
            val = val % 10;
            prev->next = new ListNode(val);
            prev = prev->next;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        return dummy.next;
    }

    /**
     * 445. Add Two Numbers II.
     * You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit.
     * Add the two numbers and return the sum as a linked list.
     *
     * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
     *
     * https://leetcode.com/problems/add-two-numbers-ii/description/
     */
    ListNode *addTwoNumbers2(ListNode *l1, ListNode *l2)
    {
        l1 = reverseList(l1), l2 = reverseList(l2);

        ListNode dummy, *prev = &dummy;
        int carry = 0;

        while (l1 || l2 || carry != 0)
        {
            int d1 = l1 ? l1->val : 0;
            int d2 = l2 ? l2->val : 0;
            int val = d1 + d2 + carry;
            carry = val / 10;
            val = val % 10;
            prev->next = new ListNode(val);
            prev = prev->next;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        return reverseList(dummy.next);
    }

    /**
     * 287. Find the Duplicate Number.
     *
     * Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.
     * There is only one repeated number in nums, return this repeated number.
     *
     * You must solve the problem without modifying the array nums and using only constant extra space.
     *
     * https://leetcode.com/problems/find-the-duplicate-number/description/
     */
    int findDuplicate(std::vector<int> &nums)
    {
        int slow = 0, fast = 0;
        while (true)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast)
            {
                break;
            }
        }

        int slow2 = 0;
        while (true)
        {
            slow = nums[slow];
            slow2 = nums[slow2];
            if (slow == slow2)
            {
                break;
            }
        }

        return slow;
    }

    /**
     * 24. Swap Nodes in Pairs.
     *
     * Given a linked list, swap every two adjacent nodes and return its head.
     * You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)
     *
     * https://leetcode.com/problems/swap-nodes-in-pairs/description/
     */
    ListNode *swapPairs(ListNode *head)
    {
        ListNode *curr = head, dummy(0, head), *prev = &dummy;
        while (curr && curr->next)
        {
            ListNode *nxt = curr->next->next;
            prev->next = curr->next;
            curr->next->next = curr;
            curr->next = nxt;
            prev = curr;
            curr = nxt;
        }
        return dummy.next;
    }

    /**
     * Given the head of a linked list, return the list after sorting it in ascending order.
     *
     * https://leetcode.com/problems/sort-list/description/
     */
    ListNode *sortList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }

        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head1 = head, *head2 = slow->next;
        slow->next = nullptr;

        head1 = sortList(head1);
        head2 = sortList(head2);
        return mergeTwoLists(head1, head2);
    }

    ListNode *mergeLists(ListNode *list1, ListNode *list2)
    {
        ListNode dummy(0), *curr = &dummy;

        while (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                curr->next = list1;
                list1 = list1->next;
            }
            else
            {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }

        curr->next = list1 ? list1 : list2;
        return dummy.next;
    }

    ListNode *splitList(ListNode *head, int step)
    {
        if (!head)
        {
            return nullptr;
        }

        for (int i = 0; i < step - 1 && head->next; i++)
        {
            head = head->next;
        }

        ListNode *nextPart = head->next;
        head->next = nullptr;
        return nextPart;
    }

    ListNode *sortListIte(ListNode *head)
    {
        if (!head || !head->next)
        {
            return head;
        }

        ListNode *cur = head;
        int length = 0;
        while (cur)
        {
            length++;
            cur = cur->next;
        }

        ListNode dummy(0);
        dummy.next = head;
        int step = 1;

        while (step < length)
        {
            ListNode *prev = &dummy, *curr = dummy.next;
            while (curr)
            {
                ListNode *l1 = curr;
                ListNode *l2 = splitList(l1, step);
                curr = splitList(l2, step);
                ListNode *merged = mergeLists(l1, l2);
                prev->next = merged;
                while (prev->next)
                {
                    prev = prev->next;
                }
            }
            step *= 2;
        }

        return dummy.next;
    }

    /**
     * 92. Reverse Linked List II.
     * Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.
     *
     * https://leetcode.com/problems/reverse-linked-list-ii/description/
     */
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        ListNode dummy(0, head), *leftPrev = &dummy, *curr = head;
        int i = 0;
        while (curr)
        {
            if (i + 1 == left)
            {
                break;
            }
            leftPrev = curr;
            curr = curr->next;
            i++;
        }

        ListNode *leftNode = curr;
        while (curr)
        {
            if (i + 1 == right)
            {
                break;
            }
            curr = curr->next;
            i++;
        }

        ListNode *rightNxt = curr->next;
        curr->next = nullptr;
        ListNode *rhead = reverseList(leftNode);
        leftNode->next = rightNxt;
        leftPrev->next = rhead;

        return dummy.next;
    }

    /**
     * 725. Split Linked List in Parts.
     *
     * Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.
     * The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.
     * The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.
     *
     * Return an array of the k parts.
     * https://leetcode.com/problems/split-linked-list-in-parts/description/
     */
    std::vector<ListNode *> splitListToParts(ListNode *head, int k)
    {
        ListNode *curr = head;
        std::vector<ListNode *> result;
        int len = 0;
        while (curr)
        {
            curr = curr->next;
            len++;
        }

        int baseLen = len / k, rem = len % k;
        curr = head;
        while (k > 0)
        {
            result.push_back(curr);
            int r = rem > 0 ? 1 : 0;
            int i = baseLen - 1 + r;
            while (i > 0)
            {
                curr = curr->next;
                i--;
            }

            if (rem > 0)
            {
                rem--;
            }

            if (curr)
            {
                ListNode *temp = curr->next;
                curr->next = nullptr;
                curr = temp;
            }

            k--;
        }

        return result;
    }

    /**
     * Given the head of a singly linked list, sort the list using insertion sort, and return the sorted list's head.
     *
     * The steps of the insertion sort algorithm:
     *
     * Insertion sort iterates, consuming one input element each repetition and growing a sorted output list.
     * At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list and inserts it there.
     * It repeats until no input elements remain.
     *
     * https://leetcode.com/problems/insertion-sort-list/description/
     */
    ListNode *insertionSortList(ListNode *head)
    {
        // ListNode dummy(0, nullptr), *curr = head;
        // while (curr)
        // {
        //     ListNode *lcurr = dummy.next, *prev = &dummy, *currNxt = curr->next;
        //     while (lcurr)
        //     {
        //         if (curr->val < lcurr->val)
        //         {
        //             break;
        //         }
        //         prev = lcurr;
        //         lcurr = lcurr->next;
        //     }
        //     prev->next = curr;
        //     curr->next = lcurr;
        //     curr = currNxt;
        // }

        // return dummy.next;

        ListNode dummy(0, head), *prev = head, *curr = head->next;
        while (curr)
        {
            if (curr->val >= prev->val)
            {
                prev = curr;
                curr = curr->next;
                continue;
            }

            ListNode *temp = &dummy;
            while (curr->val > temp->next->val)
            {
                temp = temp->next;
            }

            prev->next = curr->next;
            curr->next = temp->next;
            temp->next = curr;
            curr = prev->next;
        }

        return dummy.next;
    }

    /**
     * 86. Partition List.
     *
     * Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
     * You should preserve the original relative order of the nodes in each of the two partitions.
     *
     * https://leetcode.com/problems/partition-list/
     */
    ListNode *partition(ListNode *head, int x)
    {
        // ListNode *curr = head, dummy(0, head), dummy2(0, nullptr), *prev = &dummy, *lprev = &dummy2;
        // while (curr)
        // {
        //     ListNode *nxt = curr->next;
        //     if (curr->val < x)
        //     {
        //         prev->next = curr->next;
        //         curr->next = lprev->next;
        //         lprev->next = curr;
        //         lprev = curr;
        //     }
        //     else
        //     {
        //         prev = curr;
        //     }

        //     curr = nxt;
        // }

        // curr = &dummy2;
        // while (curr->next)
        // {
        //     curr = curr->next;
        // }
        // curr->next = dummy.next;

        // return dummy2.next;

        ListNode dummy(0, nullptr), *l1 = &dummy, dummy2(0, nullptr), *l2 = &dummy2;
        while (head)
        {
            if (head->val < x)
            {
                l1->next = head;
                l1 = l1->next;
            }
            else
            {
                l2->next = head;
                l2 = l2->next;
            }
            head = head->next;
        }
        l1->next = dummy2.next;
        l2->next = nullptr;

        return dummy.next;
    }

    /**
     * 61. Rotate List.
     *
     * iven the head of a linked list, rotate the list to the right by k places.
     *
     * https://leetcode.com/problems/rotate-list/description/
     */
    ListNode *rotateRight(ListNode *head, int k)
    {
        ListNode *curr = head;
        int len = 0;
        while (curr)
        {
            curr = curr->next;
            len++;
        }

        if (len == 0)
        {
            return head;
        }

        k = k % len;
        if (k == 0)
        {
            return head;
        }

        curr = head;
        while (k > 0)
        {
            curr = curr->next;
            k--;
        }

        ListNode *curr2 = head;
        while (curr->next)
        {
            curr2 = curr2->next;
            curr = curr->next;
        }

        curr->next = head;
        head = curr2->next;
        curr2->next = nullptr;

        return head;
    }
};

int main()
{
    // std::vector<int> input = {1, 2, 3, 4, 5, 6};
    // int val = 7;
    Solution obj;

    // ListNode *head = obj.createLikedList(input);
    // std::cout << "Is Palindrome LinkedList: " << obj.isPalindrome(head) << std::endl;
    // obj.printLikedList(obj.removeElements(head, val));
    // obj.printLikedList(obj.deleteDuplicates(head));
    // obj.printLikedList(obj.middleNode(head));

    // std::vector<int> list1 = {0, 1, 2, 3, 4, 5, 6};
    // std::vector<int> list2 = {1000000, 1000001, 1000002, 1000003, 1000004};
    // int a = 2, b = 5;

    // obj.printLikedList(obj.mergeInBetween(obj.createLikedList(list1), a, b, obj.createLikedList(list2)));

    // std::vector<int> input 1,4,3,2,5,2= {1, 100000};
    // std::cout << "Max Twin Sum: " << obj.pairSum(obj.createLikedList(input)) << std::endl;

    std::vector<int> input = {1};
    // obj.printLikedList(obj.removeNodes(obj.createLikedList(input)));
    // obj.printLikedList(obj.mergeNodes(obj.createLikedList(input)));
    // obj.printVector(obj.nodesBetweenCriticalPoints(obj.createLikedList(input)));
    // std::vector<int> list = {1, 2, 3};
    // obj.printLikedList(obj.modifiedList(list, obj.createLikedList(input)));
    // obj.printLikedList(obj.swapNodes(obj.createLikedList(input), 1));
    // obj.printLikedList(obj.swapPairs(obj.createLikedList(input)));
    // obj.printLikedList(obj.sortListIte(obj.createLikedList(input)));
    // obj.printLikedList(obj.reverseBetween(obj.createLikedList(input), 2, 4));
    // obj.printLikedList(obj.insertionSortList(obj.createLikedList(input)));
    // obj.printLikedList(obj.partition(obj.createLikedList(input), 3));

    obj.printLikedList(obj.rotateRight(obj.createLikedList(input), 1));

    // std::vector<std::vector<int>> input = {{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    // obj.printNodeList(obj.copyRandomList(obj.createNodeList(input)));

    return 0;
}