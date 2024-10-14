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
};

int main()
{
    Solution tree;
    Node *root = NULL;

    int t;
    int data;

    // std::cin >> t;

    // while (t-- > 0)
    // {
    //     std::cin >> data;
    //     root = tree.insert(root, data);
    // }
    // tree.preOrder(root);

    // Flatten BinarySearchTree
    // root = tree.flattenBST(root);
    // tree.printFlattenList(root);

    std::string str;
    std::getline(std::cin, str);
    root = tree.buildTreeFromString(str);

    // Flatten BinarySearchTree
    // auto ans = tree.flattenBST(root);
    // tree.printFlattenList(ans);

    // Find largest BST
    // std::cout << tree.largestBst(root) << std::endl;
    std::cout << tree.largestBstOptimized(root) << std::endl;

    // Inoder Morris Traversal
    // tree.morrisInorderTraversal(root);

    return 0;
}