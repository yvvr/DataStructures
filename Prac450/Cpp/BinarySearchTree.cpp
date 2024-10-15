/**
 * @file BinarySearchTree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-10-13
 *
 * @copyright Copyright (c) 2024
 *
 * Sorting algorithms
 *
 * You are given a pointer to the root of a binary search tree and values to be inserted into the tree.
 * Insert the values into their appropriate position in the binary search tree and return the root of the updated binary tree.
 *
 * You just have to complete the function.
 *
 * Input Format :
 *
 * You are given a function,
 *
 * Node * insert (Node * root ,int data) {
 *
 * }
 *
 */

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <unordered_set>
#include <set>
#include <stack>
#include <algorithm>

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    Node *buildTreeFromString(std::string str)
    {
        // Corner Case
        if (str.length() == 0 || str[0] == 'N')
            return NULL;

        // Creating vector of strings from input
        // string after spliting by space
        std::vector<std::string> ip;

        std::istringstream iss(str);
        for (std::string str; iss >> str;)
            ip.push_back(str);

        // Create the root of the tree
        Node *root = new Node(stoi(ip[0]));

        // Push the root to the queue
        std::queue<Node *> queue;
        queue.push(root);

        // Starting from the second element
        int i = 1;
        while (!queue.empty() && i < ip.size())
        {
            // Get and remove the front of the queue
            Node *currNode = queue.front();
            queue.pop();

            // Get the current node's value from the string
            std::string currVal = ip[i];

            // If the left child is not null
            if (currVal != "N")
            {
                // Create the left child for the current node
                currNode->left = new Node(stoi(currVal));

                // Push it to the queue
                queue.push(currNode->left);
            }

            // For the right child
            i++;
            if (i >= ip.size())
                break;
            currVal = ip[i];

            // If the right child is not null
            if (currVal != "N")
            {
                // Create the right child for the current node
                currNode->right = new Node(stoi(currVal));

                // Push it to the queue
                queue.push(currNode->right);
            }
            i++;
        }

        return root;
    }

    void preOrder(Node *root)
    {

        if (root == NULL)
            return;

        std::cout << root->data << " ";

        preOrder(root->left);
        preOrder(root->right);
    }

    void morrisInorderTraversal(Node *node)
    {
        Node *curr = node;
        while (curr != nullptr)
        {
            if (curr->left == nullptr)
            {
                std::cout << curr->data << " ";
                curr = curr->right;
            }
            else
            {
                // Find inorder predecessor
                Node *pred = curr->left;
                while (pred->right != nullptr && pred->right != curr)
                {
                    pred = pred->right;
                }

                if (pred->right == nullptr)
                {
                    pred->right = curr;
                    curr = curr->left;
                }
                else
                {
                    pred->right = nullptr;
                    std::cout << curr->data << " ";
                    curr = curr->right;
                }
            }
        }
    }

    std::pair<bool, int> isBinarySearchTree(Node *root, int max, int min)
    {
        if (root == nullptr)
        {
            return std::make_pair(true, 0);
        }

        auto leftPair = isBinarySearchTree(root->left, root->data, min);
        auto rightPair = isBinarySearchTree(root->right, max, root->data);
        auto isCurrBst = (root->data > min && root->data < max);

        return std::make_pair(isCurrBst && leftPair.first && rightPair.first, 1 + leftPair.second + rightPair.second);
    }

    /**
     * Given the root of a binary tree. Check whether it is a BST or not.
     * Note: We are considering that BSTs can not contain duplicate Nodes.
     * https://www.geeksforgeeks.org/problems/check-for-bst/1
     */
    bool isBST(Node *root)
    {
        if (root == nullptr)
        {
            return true;
        }
        return isBSTUtil(root, INT_MIN, INT_MAX);
    }
    // Largest BST in a Binary Tree
    // Time Complexity : O(n^2)
    // Space Complexity : O(1)
    int largestBst(Node *root)
    {
        // Your code here
        if (root == nullptr)
        {
            return 0;
        }

        auto leftBst = largestBst(root->left);
        auto rightBst = largestBst(root->right);
        auto currNode = isBinarySearchTree(root, INT_MAX, INT_MIN);

        return std::max(std::max(leftBst, rightBst), currNode.first ? currNode.second : 1);
    }

    std::tuple<int, int, int> isBstSubtreeOptimized(Node *root)
    {
        if (root == nullptr)
        {
            return std::make_tuple(INT_MAX, INT_MIN, 0);
        }

        auto leftTuple = isBstSubtreeOptimized(root->left);
        auto rightTuple = isBstSubtreeOptimized(root->right);
        auto isCurrBst = (root->data > std::get<1>(leftTuple) && root->data < std::get<0>(rightTuple));

        if (isCurrBst)
        {
            return std::make_tuple(
                std::min(std::get<0>(leftTuple), root->data),
                std::max(root->data, std::get<1>(rightTuple)),
                1 + std::get<2>(leftTuple) + std::get<2>(rightTuple));
        }

        return std::tuple(INT_MIN, INT_MAX, std::max(std::get<2>(leftTuple), std::get<2>(rightTuple)));
    }

    // Largest BST in a Binary Tree
    // Time Complexity : O(n)
    // Space Complexity : O(1)
    int largestBstOptimized(Node *root)
    {
        // Your code here
        if (root == nullptr)
        {
            return 0;
        }
        auto result = isBstSubtreeOptimized(root);
        return std::get<2>(result);
    }

    /**
     * You are given a Binary Search Tree (BST) with n nodes, each node has a distinct value assigned to it.
     * he goal is to flatten the tree such that, the left child of each element points to nothing (NULL),
     * and the right child points to the next element in the sorted list of elements of the BST.
     * You must accomplish this without using any extra storage, except for recursive calls, which are allowed.
     *
     * Note: If your BST does have a left child, then the system will print a -1 and will skip it, resulting in an incorrect solution.
     *
     * hhttps://www.geeksforgeeks.org/problems/flatten-bst-to-sorted-list--111950/1
     */
    Node *flattenBST(Node *root)
    {
        if (root == nullptr)
        {
            return root;
        }

        return flatternBSTUtil(root).first;
    }

    void printFlattenList(Node *head)
    {
        if (head)
        {
            while (head)
            {
                if (head->left)
                    std::cout << "-1 ";
                std::cout << head->data << " ";
                head = head->right;
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "Empty Tree!!";
        }
    }

    Node *insert(Node *root, int data)
    {
        if (root == nullptr)
        {
            return new Node(data);
        }

        if (root->data < data)
        {
            Node *temp = insert(root->right, data);
            root->right = temp;
        }
        else
        {
            Node *temp = insert(root->left, data);
            root->left = temp;
        }
        return root;
    }

    Node *lca(Node *root, int v1, int v2)
    {
        if ((v1 <= root->data && v2 >= root->data) || (v2 <= root->data && v1 >= root->data))
        {
            return root;
        }
        else if (v1 < root->data && v2 < root->data)
        {
            return lca(root->left, v1, v2);
        }
        else
        {
            return lca(root->right, v1, v2);
        }
    }

    /**
     * Given a Binary Search Tree that contains unique positive integer values greater than 0.
     * The task is to complete the function isDeadEnd which returns true if the BST contains a dead end else returns false.
     * Here Dead End means a leaf node, at which no other node can be inserted.
     *
     * https://www.geeksforgeeks.org/problems/check-whether-bst-contains-dead-end/1
     */
    bool isDeadEnd(Node *root)
    {
        if (root == nullptr)
        {
            return false;
        }

        return isDeadendUtil(root, 0, INT_MAX);
    }

    /**
     * Given two BSTs containing N1 and N2 distinct nodes respectively and given a value x, your task is to complete the function countPairs(),
     * that returns the count of all pairs of (a, b), where a belongs to one BST and b belongs to another BST, such that a + b = x.
     *
     * https://www.geeksforgeeks.org/problems/brothers-from-different-root/1
     */
    int countPairs(Node *root1, Node *root2, int x)
    {
        std::unordered_set<int> set;
        int result = 0;
        preOrderTranverseToBuildSet(root1, set);
        preOrderTranverseToCompareSet(root2, set, result, x);
        return result;
    }

    /**
     * Given a Binary Search Tree of size N, find the Median of its Node values.
     */
    float findMedian(struct Node *root)
    {
        int size = sizeOfBst(root);

        if (size % 2 == 0)
        {
            int k1 = size / 2;
            int k2 = size / 2 + 1;
            int count1 = 0;
            int count2 = 0;

            int val1 = -1;
            int val2 = -1;
            findkthValueInBst(root, k1, val1, count1);
            findkthValueInBst(root, k2, val2, count2);

            return float(val1 + val2) / 2;
        }
        else
        {
            int k = (size + 1) / 2;
            int count = 0;

            int val = -1;
            findkthValueInBst(root, k, val, count);
            return float(val);
        }
    }

    int sizeOfBst(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return 1 + sizeOfBst(root->left) + sizeOfBst(root->right);
    }

    /**
     * Given a Binary Search Tree (BST) and a range l-h(inclusive), count the number of nodes in the BST that lie in the given range.
     * - The values smaller than root go to the left side.
     * - The values greater and equal to the root go to the right side.
     *
     * https://www.geeksforgeeks.org/problems/count-bst-nodes-that-lie-in-a-given-range/1
     */
    int getCount(Node *root, int l, int h)
    {
        int count = 0;
        getCountUtil(root, l, h, count);
        return count;
    }

    /**
     * Replace every element with the least greater element on its right.
     *
     * Given an array arr[] of N integers and replace every element with the least greater element on its right side in the array.
     * If there are no greater elements on the right side, replace it with -1.
     *
     * https://www.geeksforgeeks.org/problems/replace-every-element-with-the-least-greater-element-on-its-right/1
     */
    // Time complexity : O(n^2), Space complexity : O(n)
    std::vector<int> findLeastGreater(std::vector<int> &arr, int n)
    {
        Node *root = NULL;

        for (int i = arr.size() - 1; i >= 0; i--)
        {
            root = insert(root, arr[i]);
            Node *succ = getSuccInBst(root, arr[i]);
            if (succ != nullptr)
            {
                arr[i] = succ->data;
            }
            else
            {
                arr[i] = -1;
            }
        }
        return arr;
    }

    // Time complexity : O(nlogn), Space complexity : O(n)
    std::vector<int> findLeastGreaterWithMultiSetApproch(std::vector<int> &arr, int n)
    {
        std::set<int> set;

        for (int i = arr.size() - 1; i >= 0; i--)
        {
            set.insert(arr[i]);
            std::set<int>::iterator it = set.upper_bound(arr[i]);

            if (it == set.end())
            {
                arr[i] = -1;
            }
            else
            {
                arr[i] = *it;
            }
        }
        return arr;
    }

    // Time complexity : O(nlogn), Space complexity : O(n)
    // https://www.geeksforgeeks.org/replace-every-element-with-the-least-greater-element-on-its-right/
    std::vector<int> findLeastGreaterWithStackApproch(std::vector<int> &arr, int n)
    {
        // Making a temp array of values with indices.
        std::vector<std::pair<int, int>> temp;
        for (int i = 0; i < arr.size(); i++)
        {
            temp.push_back(std::make_pair(arr[i], i));
        }

        // Sort temp array based on values.
        auto comp = [](const std::pair<int, int> &a, const std::pair<int, int> &b)
        {
            return a.first < b.first;
        };
        std::sort(temp.begin(), temp.end(), comp);

        std::vector<int> index(arr.size(), -1);
        std::stack<int> stack;

        for (int i = 0; i < temp.size(); i++)
        {
            while (!stack.empty() && stack.top() < temp[i].second)
            {
                index[stack.top()] = temp[i].first;
                stack.pop();
            }
            stack.push(temp[i].second);
        }
        return index;
    }

    /**
     * Given a Binary Search Tree and a node value X, find if the node with value X is present in the BST or not.
     * https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
     */
    bool search(Node *root, int x)
    {
        if (root == nullptr)
        {
            return false;
        }
        if (root->data > x)
        {
            return search(root->left, x);
        }
        else if (root->data < x)
        {
            return search(root->right, x);
        }
        else
        {
            return true;
        }

        return false;
    }

    /**
     * Given a root node reference of a BST and a key, delete the node with the given key in the BST.
     * Return the root node reference (possibly updated) of the BST.
     * https://leetcode.com/problems/delete-node-in-a-bst/description/
     */
    Node *deleteNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            return root;
        }

        if (root->data > key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (root->data < key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }

            if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            Node *succ = getSucc(root);
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
        return root;
    }

    /**
     * Given the root of a Binary Search Tree. The task is to find the minimum valued element in this given BST.
     * https://www.geeksforgeeks.org/problems/minimum-element-in-bst/1
     */
    int minValue(Node *root)
    {
        if (root->left == nullptr)
        {
            return root->data;
        }
        return leftMost(root)->data;
    }

    /**
     * There is BST given with the root node with the key part as an integer only.
     * You need to find the in-order successor and predecessor of a given key.
     * If either predecessor or successor is not found, then set it to NULL.
     *
     * https://www.geeksforgeeks.org/problems/predecessor-and-successor/1
     */
    void findPreSuc(Node *root, Node *&pre, Node *&suc, int key)
    {
        if (root == nullptr)
        {
            return;
        }
        suc = getSuccInBst(root, key);
        pre = getPredInBst(root, key);
        return;
    }

private:
    std::pair<Node *, Node *> flatternBSTUtil(Node *root)
    {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr))
        {
            return std::make_pair(root, root);
        }
        auto leftPair = flatternBSTUtil(root->left);
        auto rightPair = flatternBSTUtil(root->right);

        if (leftPair.second)
        {
            leftPair.second->right = root;
        }
        root->right = rightPair.first;
        root->left = nullptr;
        auto head = leftPair.first ? leftPair.first : root;
        auto tail = rightPair.second ? rightPair.second : root;

        return std::make_pair(head, tail);
    }

    bool isDeadendUtil(Node *root, int min, int max)
    {
        if (root == nullptr)
        {
            return false;
        }

        if (root->left == nullptr && root->right == nullptr)
        {
            return root->data - 1 == min && root->data + 1 == max;
        }

        return isDeadendUtil(root->left, min, root->data) || isDeadendUtil(root->right, root->data, max);
    }

    void preOrderTranverseToBuildSet(Node *root, std::unordered_set<int> &set)
    {
        if (root == nullptr)
        {
            return;
        }
        set.insert(root->data);
        preOrderTranverseToBuildSet(root->left, set);
        preOrderTranverseToBuildSet(root->right, set);
    }

    void preOrderTranverseToCompareSet(Node *root, std::unordered_set<int> &set, int &result, int x)
    {
        if (root == nullptr)
        {
            return;
        }
        if (set.find(x - root->data) != set.end())
        {
            result++;
        }
        preOrderTranverseToCompareSet(root->left, set, result, x);
        preOrderTranverseToCompareSet(root->right, set, result, x);
    }

    void findkthValueInBst(Node *root, int k, int &value, int &count)
    {
        if (root == nullptr)
        {
            return;
        }
        findkthValueInBst(root->left, k, value, count);
        if (++count == k)
        {
            value = root->data;
        }
        findkthValueInBst(root->right, k, value, count);
    }

    void getCountUtil(Node *root, int l, int h, int &count)
    {
        if (root == nullptr)
        {
            return;
        }
        if (root->data >= l && root->data <= h)
        {
            count++;
        }
        getCountUtil(root->left, l, h, count);
        getCountUtil(root->right, l, h, count);
    }

    Node *getSuccUsingMorris(Node *root, int target)
    {
        Node *curr = root;
        Node *succ = nullptr;
        bool targetFound = false;

        while (curr != nullptr)
        {
            if (curr->left == nullptr)
            {
                if (targetFound && curr->data != target)
                {
                    succ = curr;
                    targetFound = false;
                }
                if (curr->data == target)
                {
                    targetFound = true;
                }
                curr = curr->right;
            }
            else
            {
                // Find inorder predecessor
                Node *pred = curr->left;
                while (pred->right != nullptr && pred->right != curr)
                {
                    pred = pred->right;
                }

                if (pred->right == nullptr)
                {
                    pred->right = curr;
                    curr = curr->left;
                }
                else
                {
                    pred->right = nullptr;
                    if (targetFound && curr->data != target)
                    {
                        succ = curr;
                        targetFound = false;
                    }
                    if (curr->data == target)
                    {
                        targetFound = true;
                    }
                    curr = curr->right;
                }
            }
        }

        return succ;
    }

    Node *getSuccUsingRevInorder(Node *root, int target, Node *&last)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        Node *succ = getSuccUsingRevInorder(root->right, target, last);

        if (succ != nullptr)
        {
            return succ;
        }

        if (root->data == target)
        {
            return last;
        }

        last = root;
        return getSuccUsingRevInorder(root->left, target, last);
    }

    Node *getSuccInBst(Node *root, int target)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (root->data == target && root->right != nullptr)
        {
            return leftMost(root->right);
        }

        Node *succ = nullptr;
        Node *curr = root;

        while (curr != nullptr)
        {
            if (target < curr->data)
            {
                succ = curr;
                curr = curr->left;
            }
            else if (target >= curr->data)
            {
                curr = curr->right;
            }
            else
            {
                break;
            }
        }
        return succ;
    }

    Node *getPredInBst(Node *root, int target)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (root->data == target && root->left != nullptr)
        {
            return rightMost(root->left);
        }

        Node *pred = nullptr;
        Node *curr = root;

        while (curr != nullptr)
        {
            if (target <= curr->data)
            {
                curr = curr->left;
            }
            else if (target > curr->data)
            {
                pred = curr;
                curr = curr->right;
            }
            else
            {
                break;
            }
        }
        return pred;
    }

    Node *leftMost(Node *node)
    {
        Node *curr = node;
        while (curr->left != nullptr)
            curr = curr->left;
        return curr;
    }

    Node *rightMost(Node *node)
    {
        Node *curr = node;
        while (curr->right != nullptr)
            curr = curr->right;
        return curr;
    }

    Node *getSucc(Node *curr)
    {
        curr = curr->right;
        while (curr != nullptr && curr->left != nullptr)
        {
            curr = curr->left;
        }
        return curr;
    }

    bool isBSTUtil(Node *root, int min, int max)
    {
        if (root == nullptr)
        {
            return true;
        }
        return (root->data > min && root->data < max) && isBSTUtil(root->left, min, root->data) && isBSTUtil(root->right, root->data, max);
    }
};

int main()
{
    Solution tree;
    Node *root = NULL;

    // int t;
    // int data;

    // std::cin >> t;

    // while (t-- > 0)
    // {
    //     std::cin >> data;
    //     root = tree.insert(root, data);
    // }

    // std::string str;
    // std::getline(std::cin, str);
    // root = tree.buildTreeFromString(str);

    // Print preorder of the BST.
    // tree.preOrder(root);

    // Flatten BinarySearchTree
    // root = tree.flattenBST(root);
    // tree.printFlattenList(root);

    // Flatten BinarySearchTree
    // auto ans = tree.flattenBST(root);
    // tree.printFlattenList(ans);

    // Find largest BST
    // std::cout << tree.largestBst(root) << std::endl;
    // std::cout << tree.largestBstOptimized(root) << std::endl;

    // Inoder Morris Traversal
    // tree.morrisInorderTraversal(root);

    // Is Dead Tree
    // std::cout << tree.isDeadEnd(root) << std::endl;

    // Brothers From Different Roots
    // std::string tree1, tree2;
    // std::getline(std::cin, tree1);
    // std::getline(std::cin, tree2);
    // Node *root1 = tree.buildTreeFromString(tree1);
    // Node *root2 = tree.buildTreeFromString(tree2);
    // int x;
    // std::cin >> x;

    // std::cout << tree.countPairs(root1, root2, x) << "\n";

    // Median of BST
    // std::cout << tree.findMedian(root) << "\n";

    // Replace every element with the least greater element on its right
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    Solution ob;
    // std::vector<int> ans = ob.findLeastGreater(arr, n);
    std::vector<int> ans = ob.findLeastGreaterWithStackApproch(arr, n);
    for (auto it : ans)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    return 0;
}