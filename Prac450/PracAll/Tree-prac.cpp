#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
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

struct TreeNodeN
{
    int val;
    std::vector<TreeNodeN *> children;

    TreeNodeN() {}
    TreeNodeN(int x) : val(x) {}
    TreeNodeN(int x, std::vector<TreeNodeN *> children) : val(x), children(children) {}
};

struct pair_hash
{
    std::size_t operator()(const std::pair<int, int> &pair) const
    {
        return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
    }
};

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

std::vector<int> inorderTraversal(TreeNode *root)
{
    std::stack<TreeNode *> stack;
    std::vector<int> res;

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

std::vector<int> inorderMorris(TreeNode *root)
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
                pred->right = curr;
                curr = curr->left;
            }
            else
            {
                res.push_back(curr->val);
                pred->right = nullptr;
                curr = curr->right;
            }
        }
    }
    return res;
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

std::vector<int> preorderTraversal(TreeNode *root)
{
    std::stack<TreeNode *> stack;
    std::vector<int> res;

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

std::vector<int> preorderTraversalMorris(TreeNode *root)
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

std::vector<int> postorderIteration(TreeNode *root)
{
    std::stack<TreeNode *> stack;
    std::vector<int> res;

    TreeNode *curr = root;
    while (curr || !stack.empty())
    {
        if (curr)
        {
            res.push_back(curr->val);
            stack.push(curr->left);
            curr = curr->right;
        }
        else
        {
            curr = stack.top();
            stack.pop();
        }
    }

    std::reverse(res.begin(), res.end());

    return res;
}

std::vector<int> postorderMorris(TreeNode *root)
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
            TreeNode *succ = curr->right;
            while (succ->left && succ->left != curr)
            {
                succ = succ->left;
            }

            if (!succ->left)
            {
                res.push_back(curr->val);
                succ->left = curr;
                curr = curr->right;
            }
            else
            {
                succ->left = nullptr;
                curr = curr->left;
            }
        }
    }

    std::reverse(res.begin(), res.end());

    return res;
}

void postOrderNthUtil(TreeNodeN *root, std::vector<int> &res)
{
    if (root == nullptr)
    {
        return;
    }

    for (auto child : root->children)
    {
        postOrderNthUtil(child, res);
    }

    res.push_back(root->val);
}

std::vector<int> postorderN(TreeNodeN *root)
{
    std::vector<int> res;
    postOrderNthUtil(root, res);
    return res;
}

std::vector<TreeNode *> generateTreesUtil(int i, int j, std::unordered_map<std::pair<int, int>, std::vector<TreeNode *>, pair_hash> &map)
{

    std::vector<TreeNode *> result;

    if (i > j)
    {
        return {nullptr};
    }

    if (map.find({i, j}) != map.end())
    {
        return map[{i, j}];
    }

    for (int k = i; k <= j; k++)
    {
        auto leftTrees = generateTreesUtil(i, k - 1, map);
        auto rightTrees = generateTreesUtil(k + 1, j, map);

        for (auto rightTree : rightTrees)
        {
            for (auto leftTree : leftTrees)
            {
                TreeNode *root = new TreeNode(k);
                root->right = rightTree;
                root->left = leftTree;
                result.push_back(root);
            }
        }
    }

    map[{i, j}] = result;
    return result;
}

std::vector<TreeNode *> generateTrees(int n)
{
    std::unordered_map<std::pair<int, int>, std::vector<TreeNode *>, pair_hash> map;
    return generateTreesUtil(1, n, map);
}

TreeNode *invertTree(TreeNode *root)
{
    if (!root)
    {
        return nullptr;
    }

    TreeNode *temp = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(temp);
    return root;
}

void invertTree2(TreeNode *root)
{
    if (!root)
    {
        return;
    }

    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invertTree2(root->left);
    invertTree2(root->right);
}

int maxDepth(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

std::pair<int, int> diameterOfBinaryTreeUtil(TreeNode *root)
{
    if (!root)
    {
        return {0, 0};
    }

    auto left = diameterOfBinaryTreeUtil(root->left);
    auto right = diameterOfBinaryTreeUtil(root->right);

    return {
        1 + std::max(left.first, right.first),
        std::max({left.second, right.second, left.first + right.first})};
}

int diameterOfBinaryTree(TreeNode *root)
{
    if (!root)
    {
        return 0;
    }

    auto left = diameterOfBinaryTreeUtil(root->left);
    auto right = diameterOfBinaryTreeUtil(root->right);

    return std::max({left.second, right.second, left.first + right.first});
}

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

bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (!p && !q)
    {
        return true;
    }

    if (!p || !q)
    {
        return false;
    }

    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

bool isSameTree(TreeNode *root1, TreeNode *root2)
{
    if (root1 == nullptr && root2 == nullptr)
    {
        return true;
    }
    if (root1 == nullptr || root2 == nullptr)
    {
        return false;
    }
    return root1->val == root2->val &&
           isSameTree(root1->left, root2->left) &&
           isSameTree(root1->right, root2->right);
}

bool isSubtree(TreeNode *root, TreeNode *subRoot)
{
    if (root == nullptr)
    {
        return false;
    }

    return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) ||
           isSubtree(root->right, subRoot);
}

TreeNode *sortedArrayToBSTutil(std::vector<int> &nums, int l, int r)
{
    if (l > r)
    {
        return nullptr;
    }

    int mid = (l + r) / 2;
    TreeNode *root = new TreeNode(nums[mid]);
    root->left = sortedArrayToBSTutil(nums, l, mid - 1);
    root->right = sortedArrayToBSTutil(nums, mid + 1, r);

    return root;
}

TreeNode *sortedArrayToBST(std::vector<int> &nums)
{
    return sortedArrayToBSTutil(nums, 0, nums.size() - 1);
}

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