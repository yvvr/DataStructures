/**
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
 */

#include <iostream>

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
    
    void preOrder(Node *root)
    {

        if (root == NULL)
            return;

        std::cout << root->data << " ";

        preOrder(root->left);
        preOrder(root->right);
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
};

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
    tree.preOrder(root);

    return 0;
}