/**
 *
 * Tree - Preorder - Traversal
 *
 * Complete the function in the editor below, which has  parameter: a pointer to the root of a binary tree.
 * It must print the values in the tree's preorder traversal as a single line of space-separated values.
 *
 * Input Format :
 * Our test code passes the root node of a binary tree to the preOrder function.
 *
 * Output Format :
 * Print the tree's preorder traversal as a single line of space-separated values.
 *
 */

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>

struct Node
{
    int data;
    Node *right;
    Node *left;

    Node(int data)
    {
        this->data = data;
        right = nullptr;
        left = nullptr;
    }
};

class Solution
{
public:
    Node *insert(Node *root, int data)
    {
        if (root == NULL)
        {
            return new Node(data);
        }
        else
        {
            Node *cur;
            if (data <= root->data)
            {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else
            {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    void preOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        std::cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void postOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        postOrder(root->left);
        postOrder(root->right);
        std::cout << root->data << " ";
    }

    void inOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        inOrder(root->left);
        std::cout << root->data << " ";
        inOrder(root->right);
    }

    int height(Node *root)
    {
        if (root == nullptr)
        {
            return -1;
        }

        return 1 + std::max(height(root->left), height(root->right));
    }

    void topView(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        std::queue<std::pair<Node *, int>> q;
        std::map<int, Node *> resMap;

        q.push(std::make_pair(root, 0));
        while (!q.empty())
        {
            auto curr = q.front();
            q.pop();

            Node *currNode = curr.first;
            int currDis = curr.second;

            if (currNode->left != nullptr)
            {
                q.push(std::make_pair(currNode->left, currDis - 1));
            }
            if (currNode->right != nullptr)
            {
                q.push(std::make_pair(currNode->right, currDis + 1));
            }
            if (resMap.find(currDis) == resMap.end())
            {
                resMap[currDis] = currNode;
            }
        }

        for (auto it = resMap.begin(); it != resMap.end(); it++)
        {
            std::cout << it->second->data << " ";
        }
        return;
    }

    void levelOrder(Node *root)
    {

        if (root == nullptr)
        {
            return;
        }

        std::queue<Node *> q;

        q.push(root);
        while (!q.empty())
        {
            auto currNode = q.front();
            q.pop();

            if (currNode->left != nullptr)
            {
                q.push(currNode->left);
            }
            if (currNode->right != nullptr)
            {
                q.push(currNode->right);
            }
            std::cout << currNode->data << " ";
        }
        return;
    }

    std::vector<std::vector<int>> levelOrderTrav(Node *root)
    {
        std::vector<std::vector<int>> result;
        if (root == nullptr)
        {
            return result;
        }

        std::queue<Node *> q;

        q.push(root);
        while (!q.empty())
        {
            std::vector<int> level;
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                auto currNode = q.front();
                q.pop();

                if (currNode->left != nullptr)
                {
                    q.push(currNode->left);
                }
                if (currNode->right != nullptr)
                {
                    q.push(currNode->right);
                }
                level.push_back(currNode->data);
            }
            result.push_back(level);
        }
        return result;
    }

    std::vector<std::vector<int>> levelOrderTrav(Node *root)
    {
        std::vector<std::vector<int>> result;
        if (root == nullptr)
        {
            return result;
        }

        std::stack<Node *> stack1;
        std::stack<Node *> stack2;

        stack1.push(root);
        while (!stack1.empty() || !stack2.empty())
        {
            std::vector<int> level;
            if (!stack1.empty())
            {
                while (!stack1.empty())
                {
                    Node *currNode = stack1.top();
                    stack1.pop();
                    if (currNode->left != nullptr)
                    {
                        stack2.push(currNode->left);
                    }
                    if (currNode->right != nullptr)
                    {
                        stack2.push(currNode->right);
                    }
                    level.push_back(currNode->data);
                }
            }
            else
            {
                while (!stack2.empty())
                {
                    Node *currNode = stack2.top();
                    stack2.pop();
                    if (currNode->right != nullptr)
                    {
                        stack1.push(currNode->right);
                    }
                    if (currNode->left != nullptr)
                    {
                        stack1.push(currNode->left);
                    }
                    level.push_back(currNode->data);
                }
            }
            result.push_back(level);
        }
        return result;
    }

    bool isBalanced(Node *root)
    {
        return isBalancedUtil(root).second;
    }

    std::pair<int, bool> isBalancedUtil(Node *root)
    {
        if (root == nullptr)
        {
            return {0, true};
        }

        auto leftPair = isBalancedUtil(root->left);
        auto rightPair = isBalancedUtil(root->right);
        bool isBalanced = leftPair.second && rightPair.second && std::abs(leftPair.first - rightPair.first) <= 1;
        
        return { 1 + std::max(leftPair.first, rightPair.first), isBalanced };
    }

}; // End of Solution

int main()
{

    Solution tree;
    Node *root = NULL;

    int t;
    int data;

    std::cin >> t;

    while (t-- > 0)
    {
        std::cin >> data;
        root = tree.insert(root, data);
    }

    // tree.preOrder(root);

    // Print height of the tree
    // std::cout << tree.height(root) << std::endl;

    // Print top view of the tree
    tree.topView(root);

    return 0;
}