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
        if(root==nullptr){
            return;
        }

        std::queue<std::pair<Node*, int>> q;
        std::map<int, Node*> resMap;

        q.push(std::make_pair(root, 0));
        while(!q.empty()){
            auto curr = q.front();
            q.pop();

            Node* currNode = curr.first;
            int currDis = curr.second;

            if(currNode->left!=nullptr) {
                q.push(std::make_pair(currNode->left, currDis - 1));
            }
            if(currNode->right!=nullptr){
                q.push(std::make_pair(currNode->right, currDis + 1));
            }
            if(resMap.find(currDis) == resMap.end()){
                resMap[currDis] = currNode;
            }
        }

        for(auto it = resMap.begin(); it!=resMap.end(); it++){
            std::cout << it->second->data << " ";
        }
        return;
    }

    void levelOrder(Node * root) {

        if(root==nullptr){
            return;
        }

        std::queue<Node*> q;

        q.push(root);
        while(!q.empty()){
            auto currNode = q.front();
            q.pop();

            if(currNode->left!=nullptr) {
                q.push(currNode->left);
            }
            if(currNode->right!=nullptr){
                q.push(currNode->right);
            }
            std::cout << currNode->data << " ";
        }
        return;
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