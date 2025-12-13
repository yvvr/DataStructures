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
#include <queue>
#include <unordered_map>
#include <map>
#include <string>
#include <unordered_set>
#include <algorithm>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node1
{
public:
    int val;
    std::vector<Node1 *> children;

    Node1() {}

    Node1(int _val)
    {
        val = _val;
    }

    Node1(int _val, std::vector<Node1 *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Node2
{
public:
    int val;
    Node2 *left;
    Node2 *right;
    Node2 *parent;
    std::vector<Node2 *> children;
};

class Node
{
public:
    bool val;
    bool isLeaf;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft;
    Node *bottomRight;

    Node()
    {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    /**
     * 94. Binary Tree Inorder Traversal
     *
     * Given the root of a binary tree, return the inorder traversal of its nodes' values.
     *
     * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
     */
    std::vector<int> inorderTraversal(TreeNode *root)
    {
        std::vector<int> res;
        inorder(root, res);

        return res;
    }

    std::vector<int> inorderTravIte(TreeNode *root)
    {
        std::vector<int> res;
        std::stack<TreeNode *> stack;
        TreeNode *curr = root;

        while (curr || !stack.empty())
        {
            while (curr)
            {
                stack.push(curr);
                curr = curr->left;
            }
            curr = stack.top();
            stack.pop();

            res.push_back(curr->val);
            curr = curr->right;
        }

        return res;
    }

    std::vector<int> inorderTravMorris(TreeNode *root)
    {
        std::vector<int> res;
        TreeNode *cur = root;

        while (cur)
        {
            if (!cur->left)
            {
                res.push_back(cur->val);
                cur = cur->right;
            }
            else
            {
                TreeNode *pred = cur->left;
                while (pred->right && pred->right != cur)
                {
                    pred = pred->right;
                }

                if (!pred->right)
                {
                    pred->right = cur;
                    cur = cur->left;
                }
                else
                {
                    pred->right = nullptr;
                    res.push_back(cur->val);
                    cur = cur->right;
                }
            }
        }

        return res;
    }

    /**
     * 144. Binary Tree Preorder Traversal.
     *
     * Given the root of a binary tree, return the preorder traversal of its nodes' values.
     *
     * https://leetcode.com/problems/binary-tree-preorder-traversal/description/
     */

    std::vector<int> preorderTraversal(TreeNode *root)
    {
        std::vector<int> res;
        preorder(root, res);

        return res;
    }

    std::vector<int> preorderTravIte(TreeNode *root)
    {
        std::vector<int> res;
        std::stack<TreeNode *> stack;
        TreeNode *curr = root;

        while (curr || !stack.empty())
        {
            if (curr)
            {
                res.push_back(curr->val);
                stack.push(curr->right);
                curr = curr->left;
            }
            else
            {
                curr = stack.top();
                stack.pop();
            }
        }

        return res;
    }

    std::vector<int> preorderTravMorris(TreeNode *root)
    {
        std::vector<int> res;
        TreeNode *curr = root;

        while (curr)
        {
            if (!curr->left)
            {
                res.push_back(curr->val);
                curr = curr->right;
            }
            else
            {
                TreeNode *pred = curr->left;
                while (pred->right && pred->right != curr)
                {
                    pred = pred->right;
                }

                if (!pred->right)
                {
                    res.push_back(curr->val);
                    pred->right = curr;
                    curr = curr->left;
                }
                else
                {
                    pred->right = nullptr;
                    curr = curr->right;
                }
            }
        }

        return res;
    }

    /**
     * 145. Binary Tree Postorder Traversal.
     *
     * Given the root of a binary tree, return the postorder traversal of its nodes' values.
     */
    std::vector<int> postorderTraversal(TreeNode *root)
    {
        std::vector<int> res;
        postorder(root, res);

        return res;
    }

    std::vector<int> postorderTravMorris(TreeNode *root)
    {
        std::vector<int> res;
        TreeNode *curr = root;

        while (curr)
        {
            if (!curr->right)
            {
                res.push_back(curr->val);
                curr = curr->left;
            }
            else
            {
                TreeNode *pred = curr->right;
                while (pred->left && pred->left != curr)
                {
                    pred = pred->left;
                }

                if (!pred->left)
                {
                    res.push_back(curr->val);
                    pred->left = curr;
                    curr = curr->right;
                }
                else
                {
                    pred->left = nullptr;
                    curr = curr->left;
                }
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }

    /**
     * 590. N-ary Tree Postorder Traversal.
     *
     * Given the root of an n-ary tree, return the postorder traversal of its nodes' values.
     * Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples).
     *
     * https://leetcode.com/problems/n-ary-tree-postorder-traversal/description/
     */
    void postOrderNth(Node1 *root, std::vector<int> &res)
    {
        if (root == nullptr)
        {
            return;
        }

        for (auto child : root->children)
        {
            postOrderNth(child, res);
        }

        res.push_back(root->val);
    }

    std::vector<int> postorder(Node1 *root)
    {
        std::vector<int> res;
        postOrderNth(root, res);
        return res;
    }

    /**
     * 226. Invert Binary Tree.
     *
     * Given the root of a binary tree, invert the tree, and return its root.
     *
     * https://leetcode.com/problems/invert-binary-tree/description/
     */
    TreeNode *invertTree(TreeNode *root)
    {
        // if(!root) {
        //     return root;
        // }

        // TreeNode* temp = root->left;
        // root->left = invertTree(root->right);
        // root->right = invertTree(temp);

        // return root;

        if (!root)
            return root;
        std::stack<TreeNode *> stack;
        stack.push(root);
        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            stack.pop();
            std::swap(node->left, node->right);
            if (node->left)
                stack.push(node->left);
            if (node->right)
                stack.push(node->right);
        }

        return root;
    }

    /**
     * 543. Diameter of Binary Tree.
     *
     * Given the root of a binary tree, return the length of the diameter of the tree.
     *
     * The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
     * The length of a path between two nodes is represented by the number of edges between them.
     */
    std::pair<int, int> diameterOfBinaryTreeHelper(TreeNode *root)
    {
        if (!root)
        {
            return {0, 0};
        }

        auto left = diameterOfBinaryTreeHelper(root->left);
        auto right = diameterOfBinaryTreeHelper(root->right);

        return {std::max(left.first, right.first), std::max(left.second, right.second, 1 + left.first + right.first)};
    }

    int diameterOfBinaryTree(TreeNode *root)
    {
        if (!root)
        {
            return 0;
        }

        auto left = diameterOfBinaryTreeHelper(root->left);
        auto right = diameterOfBinaryTreeHelper(root->right);

        return std::max(left.second, right.second, 1 + left.first + right.first);
    }

    /**
     * 100. Same Tree.
     *
     * Given the roots of two binary trees p and q, write a function to check if they are the same or not.
     *
     * Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.
     *
     * https://leetcode.com/problems/same-tree/description/
     */
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        std::stack<std::pair<TreeNode *, TreeNode *>> stack;
        stack.push({p, q});

        while (!stack.empty())
        {
            auto [node1, node2] = stack.top();
            stack.pop();

            if (!node1 && !node2)
                continue;
            if (!node1 || !node2 || node1->val != node2->val)
                return false;

            stack.push({node1->right, node2->right});
            stack.push({node1->left, node2->left});
        }

        return true;
    }

    /**
     * 108. Convert Sorted Array to Binary Search Tree
     * Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.
     *
     * https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/
     */
    TreeNode *sortedArrayToBST(std::vector<int> &nums)
    {
        if (nums.empty())
        {
            return nullptr;
        }

        int mid = nums.size() / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        std::vector<int> left(nums.begin(), nums.begin() + mid);
        std::vector<int> right(nums.begin() + mid + 1, nums.end());
        root->left = sortedArrayToBST(left);
        root->right = sortedArrayToBST(right);
        return root;
    }

    TreeNode *sortedArrayToBSTHelper(std::vector<int> &nums, int l, int r)
    {
        if (l > r)
        {
            return nullptr;
        }

        int mid = (l + r) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBSTHelper(nums, l, mid - 1);
        root->right = sortedArrayToBSTHelper(nums, mid + 1, r);

        return root;
    }

    /**
     * 617. Merge Two Binary Trees.
     *
     * You are given two binary trees root1 and root2.
     * Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of the new tree.
     *
     * Return the merged tree.
     *
     * Note: The merging process must start from the root nodes of both trees.
     *
     * https://leetcode.com/problems/merge-two-binary-trees/description/
     */
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
    {
        if (!root1)
            return root2;
        if (!root2)
            return root1;

        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);

        return root1;
    }

    /**
     * 112. Path Sum.
     *
     * Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.
     * A leaf is a node with no children.
     *
     * https://leetcode.com/problems/path-sum/description/
     */
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return false;
        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val) ||
               (targetSum - root->val == 0 && !root->left && !root->right);
    }

    /**
     * 199. Binary Tree Right Side View.
     *
     * Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
     *
     * https://leetcode.com/problems/binary-tree-right-side-view/description/
     */
    std::vector<int> rightSideView(TreeNode *root)
    {
        std::vector<int> res;
        std::queue<TreeNode *> queue;

        queue.push(root);
        while (!queue.empty())
        {
            int len = queue.size();

            TreeNode *lastNode = nullptr;
            for (int i = 0; i < len; i++)
            {
                TreeNode *node = queue.front();
                queue.pop();

                if (node)
                {
                    queue.push(node->left);
                    queue.push(node->right);

                    lastNode = node;
                }
            }

            if (lastNode)
            {
                res.push_back(lastNode->val);
            }
        }

        return res;
    }

    /**
     * 1448. Count Good Nodes in Binary Tree.
     *
     * Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.
     *
     * Return the number of good nodes in the binary tree.
     *
     * https://leetcode.com/problems/count-good-nodes-in-binary-tree/description/
     */

    int goodNodes(TreeNode *root)
    {
        return goodNodesHelper(root, INT_MIN);
    }

    int goodNodesHelper(TreeNode *root, int maxVal)
    {
        if (!root)
            return 0;

        int isGood = root->val >= maxVal ? 1 : 0;

        return isGood + goodNodesHelper(root->left, std::max(maxVal, root->val)) + goodNodesHelper(root->right, std::max(maxVal, root->val));
    }

    /**
     * 98. Validate Binary Search Tree.
     *
     * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
     *
     * A valid BST is defined as follows:
     * The left subtree of a node contains only nodes with keys strictly less than the node's key.
     * The right subtree of a node contains only nodes with keys strictly greater than the node's key.
     * Both the left and right subtrees must also be binary search trees.
     */
    bool isValidBST(TreeNode *root)
    {
        return valid(root, LONG_MIN, LONG_MAX);
    }

    bool valid(TreeNode *node, long left, long right)
    {
        if (!node)
        {
            return true;
        }

        if (!(left < node->val && node->val < right))
        {
            return false;
        }
        return valid(node->left, left, node->val) &&
               valid(node->right, node->val, right);
    }

    /**
     * 2331. Evaluate Boolean Binary Tree.
     *
     * You are given the root of a full binary tree with the following properties:
     * Leaf nodes have either the value 0 or 1, where 0 represents False and 1 represents True.
     * Non-leaf nodes have either the value 2 or 3, where 2 represents the boolean OR and 3 represents the boolean AND.
     *
     * The evaluation of a node is as follows:
     * If the node is a leaf node, the evaluation is the value of the node, i.e. True or False.
     * Otherwise, evaluate the node's two children and apply the boolean operation of its value with the children's evaluations.
     * Return the boolean result of evaluating the root node.
     *
     * A full binary tree is a binary tree where each node has either 0 or 2 children. A leaf node is a node that has zero children.
     * https://leetcode.com/problems/evaluate-boolean-binary-tree/description/
     */
    bool evaluateTree(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            return root->val;
        }

        bool left = evaluateTree(root->left);
        bool right = evaluateTree(root->right);

        if (root->val == 2)
        {
            return left || right;
        }
        else
        {
            return left && right;
        }
    }

    /**
     * 872. Leaf-Similar Trees.
     *
     * Consider all the leaves of a binary tree, from left to right order, the values of those leaves form a leaf value sequence.
     *
     * https://leetcode.com/problems/leaf-similar-trees/description/
     */
    void dfsLeafSimilar(TreeNode *root, std::vector<int> &res)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            res.push_back(root->val);
        }

        dfsLeafSimilar(root->left, res);
        dfsLeafSimilar(root->right, res);
    }

    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {
        std::vector<int> leafRes1;
        std::vector<int> leafRes2;

        dfsLeafSimilar(root1, leafRes1);
        dfsLeafSimilar(root2, leafRes2);

        if (leafRes1.size() != leafRes2.size())
        {
            return false;
        }

        for (int i = 0; i < leafRes1.size(); i++)
        {
            if (leafRes1[i] != leafRes2[i])
            {
                return false;
            }
        }

        return true;
    }

    /**
     * 938. Range Sum of BST.
     *
     * Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].
     *
     * https://leetcode.com/problems/range-sum-of-bst/description/
     */
    int rangeSumBST(TreeNode *root, int low, int high)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (root->val > high)
        {
            return rangeSumBST(root->left, low, high);
        }

        if (root->val < low)
        {
            return rangeSumBST(root->right, low, high);
        }

        return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    }

    /**
     * 2196. Create Binary Tree From Descriptions.
     *
     * You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,
     * If isLefti == 1, then childi is the left child of parenti.
     * isLefti == 0, then childi is the right child of parenti.
     * Construct the binary tree described by descriptions and return its root.
     *
     * The test cases will be generated such that the binary tree is valid.
     *
     * https://leetcode.com/problems/create-binary-tree-from-descriptions/description/
     */
    TreeNode *createBinaryTree(std::vector<std::vector<int>> &descriptions)
    {
        std::unordered_map<int, TreeNode *> map;
        std::unordered_map<int, int> parentMap;

        for (auto des : descriptions)
        {
            int parent = des[0];
            int child = des[1];
            int isLeft = des[2];

            TreeNode *parentNode = map[parent], *childNode = map[child];

            if (parentNode == nullptr)
            {
                parentNode = new TreeNode(parent);
                map[parent] = parentNode;
            }

            if (childNode == nullptr)
            {
                childNode = new TreeNode(child);
                map[parent] = childNode;
            }

            if (isLeft)
            {
                parentNode->left = childNode;
            }
            else
            {
                parentNode->right = childNode;
            }
            parentMap[child] = parent;
        }

        int root = descriptions[0][0];
        while (parentMap.find(root) != parentMap.end())
        {
            root = parentMap[root];
        }

        return map[root];
    }

    /**
     * 314. Binary Tree Vertical Order Traversal
     *
     * Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).
     *
     * If two nodes are in the same row and column, the order should be from left to right.
     *
     * https://leetcode.com/problems/binary-tree-vertical-order-traversal/description/
     */
    std::vector<std::vector<int>> verticalOrder(TreeNode *root)
    {
        if (!root)
        {
            return {};
        }

        std::unordered_map<int, std::vector<int>> map;
        std::queue<std::pair<TreeNode *, int>> queue;
        queue.push({root, 0});
        int minDist = 0, maxDist = 0;

        while (!queue.empty())
        {
            auto [node, dist] = queue.front();
            queue.pop();
            map[dist].push_back(node->val);
            minDist = std::min(minDist, dist);
            maxDist = std::max(maxDist, dist);

            if (node->left)
            {
                queue.push({node->left, dist + 1});
            }

            if (node->right)
            {
                queue.push({node->right, dist - 1});
            }
        }

        std::vector<std::vector<int>> res;
        for (int dist = minDist; dist <= maxDist; dist++)
        {
            res.push_back(map[dist]);
        }

        return res;
    }

    /**
     * 606. Construct String from Binary Tree
     *
     * Given the root node of a binary tree, your task is to create a string representation of the tree following a specific set of formatting rules.
     * The representation should be based on a preorder traversal of the binary tree and must adhere to the following guidelines:
     *
     * Node Representation: Each node in the tree should be represented by its integer value.
     * Parentheses for Children: If a node has at least one child (either left or right), its children should be represented inside parentheses. Specifically:
     * If a node has a left child, the value of the left child should be enclosed in parentheses immediately following the node's value.
     * If a node has a right child, the value of the right child should also be enclosed in parentheses. The parentheses for the right child should follow those of the left child.
     *
     * https://leetcode.com/problems/construct-string-from-binary-tree/description/
     */

    void tree2strHelper(TreeNode *root, std::string &res)
    {
        if (!root)
        {
            return;
        }

        res += "(" + std::to_string(root->val);
        if (!root->left && root->right)
        {
            res += "()";
        }
        tree2strHelper(root->left, res);
        tree2strHelper(root->right, res);
        res += ")";
    }

    std::string tree2str(TreeNode *root)
    {
        // if (root == nullptr)
        // {
        //     return "";
        // }
        // if (root->left == nullptr && root->right == nullptr)
        // {
        //     return std::to_string(root->val);
        // }

        // std::string leftStr = tree2str(root->left);
        // std::string rigthStr = tree2str(root->right);
        // std::string res = std::to_string(root->val) + "(" + leftStr + ")";

        // if (root->right != nullptr)
        // {
        //     res += "(" + rigthStr + ")";
        // }

        // return res;

        std::string res;
        tree2strHelper(root, res);
        return res.substr(1, res.size() - 2);
    }

    /**
     * 236. Lowest Common Ancestor of a Binary Tree.
     *
     * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
     * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
     *
     * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
     */
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root)
        {
            return nullptr;
        }

        if (root == p || root == q)
        {
            return root;
        }

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        return !left && !right ? root : !left ? left
                                              : right;
    }

    /**
     * 1650. Lowest Common Ancestor of a Binary Tree III
     *
     * Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).
     *
     * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/description/
     */
    Node2 *lowestCommonAncestor(Node2 *p, Node2 *q)
    {
        // std::unordered_set<Node *> pSet;
        // Node *p1 = p, *p2 = q;
        // while (p1)
        // {
        //     pSet.insert(p1);
        //     p1 = p1->parent;
        // }

        // while (p2)
        // {
        //     if (pSet.find(p2) != pSet.end())
        //     {
        //         return p2;
        //     }
        //     p2 = p2->parent;
        // }

        // return nullptr;

        Node2 *p1 = p, *p2 = q;
        while (p1 != p2)
        {
            p1 = p1 ? p1->parent : q;
            p2 = p2 ? p2->parent : p;
        }

        return p1;
    }

    /**
     * 450. Delete Node in a BST.
     *
     * Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
     *
     * Basically, the deletion can be divided into two stages:
     *
     * Search for a node to remove.
     * If the node is found, delete the node.
     *
     * https://leetcode.com/problems/delete-node-in-a-bst/description/
     */
    TreeNode *getSucc(TreeNode *curr)
    {
        curr = curr->right;
        while (curr != nullptr && curr->left != nullptr)
        {
            curr = curr->left;
        }
        return curr;
    }

    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (root == nullptr)
        {
            return root;
        }

        if (root->val > key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (root->val < key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if (root->left == nullptr)
            {
                TreeNode *temp = root->right;
                delete root;
                return temp;
            }

            if (root->right == nullptr)
            {
                TreeNode *temp = root->left;
                delete root;
                return temp;
            }

            TreeNode *succ = getSucc(root);
            root->val = succ->val;
            root->right = deleteNode(root->right, succ->val);
        }

        return root;
    }

    /**
     * 701. Insert into a Binary Search Tree.
     *
     * You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion.
     * It is guaranteed that the new value does not exist in the original BST.
     */
    TreeNode *insertIntoBST(TreeNode *root, int val)
    {
        // if (root == nullptr)
        // {
        //     return new TreeNode(val);
        // }

        // if (root->val < val)
        // {
        //     root->right = insertIntoBST(root->right, val);
        // }
        // else
        // {
        //     root->left = insertIntoBST(root->left, val);
        // }

        // return root;

        if (!root)
        {
            return new TreeNode(val);
        }

        TreeNode *curr = root;
        while (true)
        {
            if (val > curr->val)
            {
                if (!curr->right)
                {
                    curr->right = new TreeNode(val);
                    return root;
                }
                curr = curr->right;
            }
            else
            {
                if (!curr->left)
                {
                    curr->left = new TreeNode(val);
                    return root;
                }
                curr = curr->left;
            }
        }
    }

    /**
     * 2471. Minimum Number of Operations to Sort a Binary Tree by Level.
     *
     * You are given the root of a binary tree with unique values.
     * In one operation, you can choose any two nodes at the same level and swap their values.
     *
     * Return the minimum number of operations needed to make the values at each level sorted in a strictly increasing order.
     *
     * The level of a node is the number of edges along the path between it and the root node.
     *
     * https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/
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

    int minimumOperations(TreeNode *root)
    {
        std::queue<TreeNode *> queue;
        queue.push(root);
        int minOps = 0;

        while (!queue.empty())
        {
            std::vector<int> level;
            int len = queue.size();
            for (int i = 0; i < len; i++)
            {
                auto node = queue.front();
                queue.pop();
                level.push_back(node->val);

                if (node->left)
                    queue.push(node->left);
                if (node->right)
                    queue.push(node->right);
            }

            minOps += minSwaps(level);
        }
        return minOps;
    }

    /**
     * 2415. Reverse Odd Levels of Binary Tree
     *
     * Given the root of a perfect binary tree, reverse the node values at each odd level of the tree.
     * For example, suppose the node values at level 3 are [2,1,3,4,7,11,29,18], then it should become [18,29,11,7,4,3,1,2].
     *
     * Return the root of the reversed tree.
     *
     * https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/description/
     */
    TreeNode *reverseOddLevels(TreeNode *root)
    {
        if (!root)
        {
            return nullptr;
        }
        std::queue<TreeNode *> queue;

        queue.push(root);
        int level = 0;

        while (!queue.empty())
        {
            int len = queue.size();
            std::vector<TreeNode *> currLevelNodes;
            for (int i = 0; i < len; i++)
            {
                TreeNode *node = queue.front();
                queue.pop();

                if (level % 2 == 1)
                {
                    currLevelNodes.push_back(node);
                }

                if (node->left)
                {
                    queue.push(node->left);
                }

                if (node->right)
                {
                    queue.push(node->right);
                }
            }

            int l = 0, r = currLevelNodes.size() - 1;
            while (l < r)
            {
                int temp = currLevelNodes[l]->val;
                currLevelNodes[l]->val = currLevelNodes[r]->val;
                currLevelNodes[r]->val = temp;
                l++;
                r--;
            }

            level++;
        }

        return root;
    }

    /**
     * 530. Minimum Absolute Difference in BST.
     *
     * Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.
     */
    void getMinDfs(TreeNode *node, TreeNode *&prev, int &res)
    {
        if (!node)
            return;

        getMinDfs(node->left, prev, res);
        if (prev)
        {
            res = std::min(res, node->val - prev->val);
        }
        prev = node;
        getMinDfs(node->right, prev, res);
    }

    int getMinimumDifference(TreeNode *root)
    {
        TreeNode *prev = nullptr;
        int res = INT_MAX;

        getMinDfs(root, prev, res);
        return res;
    }

    /**
     * 2641. Cousins in Binary Tree II
     *
     * Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.
     * Two nodes of a binary tree are cousins if they have the same depth with different parents.
     *
     * Return the root of the modified tree.
     *
     * https://leetcode.com/problems/cousins-in-binary-tree-ii/description/
     */
    TreeNode *replaceValueInTree(TreeNode *root)
    {
        if (!root)
        {
            return nullptr;
        }

        std::queue<std::pair<TreeNode *, int>> queue;
        queue.push({root, 0});
        int currLevelSum = root->val;

        while (!queue.empty())
        {
            int len = queue.size();
            int nextLevelSum = 0;
            for (int i = 0; i < len; i++)
            {
                auto [node, siblSum] = queue.front();
                queue.pop();
                node->val = currLevelSum - node->val - siblSum;

                int rightSiblSum = node->left ? node->left->val : 0;
                int leftSiblSum = node->right ? node->right->val : 0;

                if (node->left)
                {
                    nextLevelSum += node->left->val;
                    queue.push({node->left, leftSiblSum});
                }

                if (node->right)
                {
                    nextLevelSum += node->right->val;
                    queue.push({node->right, rightSiblSum});
                }
            }
            currLevelSum = nextLevelSum;
        }
        return root;
    }

    /**
     * Kth Largest Sum in a Binary Tree.
     *
     * You are given the root of a binary tree and a positive integer k.
     * The level sum in the tree is the sum of the values of the nodes that are on the same level.
     *
     * Return the kth largest level sum in the tree (not necessarily distinct). If there are fewer than k levels in the tree, return -1.
     *
     * https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/description/
     */
    long long kthLargestLevelSum(TreeNode *root, int k)
    {
        std::queue<TreeNode *> queue;
        std::priority_queue<int, std::vector<int>, std::greater<int>> pqueue;
        queue.push(root);

        while (!queue.empty())
        {
            int len = queue.size();
            int levelSum = 0;
            for (int i = 0; i < len; i++)
            {
                auto node = queue.front();
                queue.pop();
                levelSum += node->val;

                if (node->left)
                    queue.push(node->left);
                if (node->right)
                    queue.push(node->right);
            }

            if (pqueue.size() < k)
            {
                pqueue.push(levelSum);
            }
            else if (pqueue.top() < levelSum)
            {
                pqueue.pop();
                pqueue.push(levelSum);
            }
        }

        return pqueue.size() == k ? pqueue.top() : -1;
    }

    /**
     * 1367. Linked List in Binary Tree.
     *
     * Given a binary tree root and a linked list with head as the first node.
     * Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
     * In this context downward path means a path that starts at some node and goes downwards.
     *
     * https://leetcode.com/problems/linked-list-in-binary-tree/description/
     */
    bool verifyLinkedList(ListNode *head, TreeNode *root)
    {
        if (head == nullptr)
        {
            return true;
        }

        if (root == nullptr)
        {
            return false;
        }

        if (head->val == root->val)
        {
            return isSubPath(head->next, root->left) || isSubPath(head->next, root->right);
        }

        return false;
    }

    bool isSubPath(ListNode *head, TreeNode *root)
    {
        if (verifyLinkedList(head, root))
        {
            return true;
        }
        if (root == nullptr)
        {
            return false;
        }

        return isSubPath(head, root->left) || isSubPath(head, root->right);
    }

    /**
     * 1443. Minimum Time to Collect All Apples in a Tree.
     *
     * Given an undirected tree consisting of n vertices numbered from 0 to n-1, which has some apples in their vertices.
     * You spend 1 second to walk over one edge of the tree. Return the minimum time in seconds you have to spend to collect all apples in the tree, starting at vertex 0 and coming back to this vertex.
     *
     * https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/description/
     */
    int minTimeDfs(std::unordered_map<int, std::vector<int>> &map, std::vector<bool> &hasApple, int node, int parent)
    {
        int time = 0;

        for (int nei : map[node])
        {
            if (nei == parent)
                continue;
            int childTime = minTimeDfs(map, hasApple, nei, node);
            if (childTime > 0 || hasApple[nei])
            {
                time += 2 + childTime;
            }
        }

        return time;
    }

    int minTime(int n, std::vector<std::vector<int>> &edges, std::vector<bool> &hasApple)
    {
        std::unordered_map<int, std::vector<int>> map;
        for (auto edge : edges)
        {
            map[edge[0]].push_back(edge[1]);
        }

        return minTimeDfs(map, hasApple, 0, -1);
    }

    /**
     * 652. Find Duplicate Subtrees.
     *
     * Given the root of a binary tree, return all duplicate subtrees.
     * For each kind of duplicate subtrees, you only need to return the root node of any one of them.
     *
     * Two trees are duplicate if they have the same structure with the same node values.
     *
     * https://leetcode.com/problems/find-duplicate-subtrees/description/
     */

    /**
     * 107. Binary Tree Level Order Traversal II
     *
     * Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root).
     */
    std::vector<std::vector<int>> levelOrderBottom(TreeNode *root)
    {
        std::stack<std::vector<int>> level;
        std::queue<TreeNode *> queue;
        std::vector<std::vector<int>> res;
        if (!root)
        {
            return res;
        }

        queue.push(root);
        while (!queue.empty())
        {
            int len = queue.size();
            std::vector<int> currLevel;
            for (int i = 0; i < len; i++)
            {
                TreeNode *node = queue.front();
                queue.pop();
                currLevel.push_back(node->val);

                if (node->left)
                {
                    queue.push(node->left);
                }

                if (node->right)
                {
                    queue.push(node->right);
                }
            }
            level.push(currLevel);
        }

        while (!level.empty())
        {
            std::vector<int> list = level.top();
            res.push_back(list);
            level.pop();
        }

        return res;
    }

    void levelOrderBottomDfsHelper(TreeNode *root, std::vector<std::vector<int>> &levels, int level)
    {
        if (levels.size() == level)
        {
            levels.push_back(std::vector<int>());
        }

        levels[level].push_back(root->val);
        if (root->left != NULL)
            levelOrderBottomDfsHelper(root->left, levels, level + 1);
        if (root->right != NULL)
            levelOrderBottomDfsHelper(root->right, levels, level + 1);
    }

    std::vector<std::vector<int>> levelOrderBottomDfs(TreeNode *root)
    {
        std::vector<std::vector<int>> levels;
        if (root == NULL)
            return levels;
        levelOrderBottomDfsHelper(root, levels, 0);
        std::reverse(levels.begin(), levels.end());
        return levels;
    }

    /**
     * 109. Convert Sorted List to Binary Search Tree.
     *
     * Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height-balanced binary search tree.
     */
    TreeNode *sortedListToBST(ListNode *head)
    {
        if (!head)
        {
            return nullptr;
        }

        if (!head->next)
        {
            return new TreeNode(head->val);
        }

        ListNode dummy(0, head), *slow = &dummy, *fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *mid = slow->next;
        slow->next = nullptr;

        TreeNode *root = new TreeNode(mid->val);
        ListNode *head2 = mid->next;
        mid->next = nullptr;

        root->left = sortedListToBST(head);
        root->right = sortedListToBST(head2);

        return root;
    }

    int findSizeSortedListToBST(ListNode *head)
    {
        ListNode *curr = head;
        int len = 0;
        while (curr != NULL)
        {
            curr = curr->next;
            len += 1;
        }
        return len;
    }

    TreeNode *sortedListToBSTInoderHelper(int l, int r, ListNode **head)
    {
        if (l > r)
        {
            return nullptr;
        }

        int mid = (l + r) / 2;

        TreeNode *left = sortedListToBSTInoderHelper(l, mid - 1, head);
        TreeNode *root = new TreeNode((*head)->val);
        *head = (*head)->next;

        root->left = left;
        root->right = sortedListToBSTInoderHelper(mid + 1, l, head);

        return root;
    }

    TreeNode *sortedListToBSTInoder(ListNode *head)
    {
        int size = findSizeSortedListToBST(head);
        return sortedListToBSTInoderHelper(0, size - 1, &head);
    }

    /**
     * 156. Binary Tree Upside Down.
     *
     * Given the root of a binary tree, turn the tree upside down and return the new root.
     * You can turn a binary tree upside down with the following steps:
     * The original left child becomes the new root.
     * The original root becomes the new right child.
     * The original right child becomes the new left child.
     *
     * https://leetcode.com/problems/binary-tree-upside-down
     */
    TreeNode *upsideDownBinaryTree(TreeNode *root)
    {
        TreeNode *curr = root, *parent = nullptr, *left = nullptr, *right = nullptr;
        while (curr)
        {
            left = curr->left;
            curr->left = right;

            right = curr->right;
            curr->right = parent;

            parent = curr;
            curr = left;
        }

        return parent;
    }

    TreeNode *upsideDownBinaryTreeDfs(TreeNode *root)
    {
        if (!root || !root->left)
        {
            return root;
        }

        TreeNode *newRoot = upsideDownBinaryTreeDfs(root->left);
        root->left->left = root->right;
        root->left->right = root;
        root->left = nullptr;
        root->right = nullptr;

        return newRoot;
    }

    /**
     * 652. Find Duplicate Subtrees.
     *
     * Given the root of a binary tree, return all duplicate subtrees.
     * For each kind of duplicate subtrees, you only need to return the root node of any one of them.
     * Two trees are duplicate if they have the same structure with the same node values.
     *
     * https://leetcode.com/problems/find-duplicate-subtrees/description/
     */
    int findDuplicateSubtreesDfs(TreeNode *root, std::unordered_map<std::string, int> &idMap, std::unordered_map<int, int> &count, std::vector<TreeNode *> &res)
    {
        // if (!root)
        // {
        //     return "N";
        // }

        // std::string currStr = std::to_string(root->val) + "," + findDuplicateSubtreesDfs(root->left, set, resMap) + "," + findDuplicateSubtreesDfs(root->right, set, resMap);
        // if (set.find(currStr) != set.end())
        // {
        //     resMap[currStr] = root;
        // }
        // else
        // {
        //     set.insert(currStr);
        // }

        // return currStr;

        // if (!root)
        //     return "N";
        // std::string s = std::to_string(root->val) + "," + findDuplicateSubtreesDfs(root->left, subtrees, res) + "," + findDuplicateSubtreesDfs(root->right, subtrees, res);
        // if (subtrees[s].size() == 1)
        // {
        //     res.push_back(root);
        // }
        // subtrees[s].push_back(root);
        // return s;

        if (!root)
            return -1;
        std::string cur = std::to_string(findDuplicateSubtreesDfs(root->left, idMap, count, res)) + "," +
                          std::to_string(root->val) + "," +
                          std::to_string(findDuplicateSubtreesDfs(root->right, idMap, count, res));
        if (idMap.find(cur) == idMap.end())
        {
            idMap[cur] = idMap.size();
        }
        int curId = idMap[cur];
        count[curId]++;
        if (count[curId] == 2)
        {
            res.push_back(root);
        }
        return curId;
    }

    std::vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
    {
        // std::unordered_set<std::string> set;
        // std::unordered_map<std::string, TreeNode *> resMap;
        // std::vector<TreeNode *> res;

        // findDuplicateSubtreesDfs(root, set, resMap);
        // for (auto [_, node] : resMap)
        // {
        //     res.push_back(node);
        // }

        // return res;

        // std::unordered_map<std::string, std::vector<TreeNode *>> subtrees;
        // std::vector<TreeNode *> res;
        // findDuplicateSubtreesDfs(root, subtrees, res);

        std::unordered_map<std::string, int> idMap;
        std::unordered_map<int, int> count;
        std::vector<TreeNode *> res;

        findDuplicateSubtreesDfs(root, idMap, count, res);

        return res;
    }

    /**
     * 427. Construct Quad Tree.
     *
     * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
     * Return the root of the Quad-Tree representing grid.
     *
     * A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:
     *
     * val: True if the node represents a grid of 1's or False if the node represents a grid of 0's. Notice that you can assign the val to True or False when isLeaf is False, and both are accepted in the answer.
     *
     * isLeaf: True if the node is a leaf node on the tree or False if the node has four children.
     *
     * https://leetcode.com/problems/construct-quad-tree/
     */
    bool isLeaf(int r, int c, int n, std::vector<std::vector<int>> &grid)
    {
        // int val = grid[rs][cs];
        // for (int i = rs; i <= re; i++)
        // {
        //     for (int j = cs; j <= ce; j++)
        //     {
        //         if (grid[i][j] != val)
        //         {
        //             return false;
        //         }
        //     }
        // }

        // return true;

        int val = grid[r][c];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[r + i][c + j] != val)
                {
                    return false;
                }
            }
        }

        return true;
    }

    Node *constructDfs(int r, int c, int n, std::vector<std::vector<int>> &grid)
    {
        bool isleaf = isLeaf(r, c, n, grid);
        if (isleaf)
        {
            return new Node(grid[r][c], true);
        }

        n = n / 2;
        Node *topLeft = constructDfs(r, c, n, grid);
        Node *topRight = constructDfs(r, c + n, n, grid);
        Node *bottomLeft = constructDfs(r + n, c, n, grid);
        Node *bottomRight = constructDfs(r + n, r + n, n, grid);
        return new Node(grid[r][c], false, topLeft, topRight, bottomLeft, bottomRight);
    }

    Node *construct(std::vector<std::vector<int>> &grid)
    {
        return constructDfs(0, 0, grid.size(), grid);
    }

    /**
     * 958. Check Completeness of a Binary Tree.
     *
     * Given the root of a binary tree, determine if it is a complete binary tree.
     * In a complete binary tree, every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible.
     * It can have between 1 and 2h nodes inclusive at the last level h.
     *
     * https://leetcode.com/problems/check-completeness-of-a-binary-tree/description/
     */
    bool isCompleteTree(TreeNode *root)
    {
        std::queue<TreeNode *> queue;
        queue.push(root);

        while (!queue.empty())
        {
            TreeNode *node = queue.front();
            queue.pop();

            if (node)
            {
                queue.push(node->left);
                queue.push(node->right);
            }
            else
            {
                while (!queue.empty())
                {
                    if (queue.front())
                    {
                        return false;
                    }
                    queue.pop();
                }
            }
        }
        return true;
    }

    /**
     * 129. Sum Root to Leaf Numbers.
     *
     * You are given the root of a binary tree containing digits from 0 to 9 only.
     * Each root-to-leaf path in the tree represents a number.
     *
     * For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
     * Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.
     *
     * A leaf node is a node with no children.
     *
     * https://leetcode.com/problems/sum-root-to-leaf-numbers/description/
     */
    void sumNumbersUtil(TreeNode *root, int sum, int &res)
    {
        if (!root)
        {
            return;
        }

        if (!root->left && !root->right)
        {
            res += sum * 10 + root->val;
            return;
        }

        sum = sum * 10 + root->val;

        sumNumbersUtil(root->left, sum, res);
        sumNumbersUtil(root->right, sum, res);
    }

    int sumNumbers(TreeNode *root)
    {
        int res = 0;
        sumNumbersUtil(root, 0, res);

        return res;
    }

    /**
     * 889. Construct Binary Tree from Preorder and Postorder Traversal.
     * 
     * Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.
     * If there exist multiple answers, you can return any of them.
     * 
     * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/
     */
    TreeNode* constructFromPrePost(std::vector<int>& preorder, std::vector<int>& postorder) {
        
    }

private:
    void inorder(TreeNode *root, std::vector<int> &res)
    {
        if (!root)
        {
            return;
        }

        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }

    void preorder(TreeNode *root, std::vector<int> &res)
    {
        if (!root)
        {
            return;
        }

        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }

    void postorder(TreeNode *root, std::vector<int> &res)
    {
        if (!root)
        {
            return;
        }

        postorder(root->left, res);
        postorder(root->right, res);
        res.push_back(root->val);
    }
};