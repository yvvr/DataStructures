/**
 * Given below is a binary tree. The task is to print the top view of binary tree.
 * Top view of a binary tree is the set of nodes visible when the tree is viewed from the top. For the given below tree
 *         1
 *       /   \
 *      2      3
 *    /  \    / \
 *   4    5  6   7
 *
 * Top view will be: 4 2 1 3 7
 * Note: Return nodes from leftmost node to rightmost node.
 * Also if 2 nodes are outside the shadow of the tree and are at same position then consider the left ones only(i.e. leftmost).
 *
 * For ex - 1 2 3 N 4 5 N 6 N 7 N 8 N 9 N N N N N will give 8 2 1 3 as answer. Here 8 and 9 are on the same position but 9 will get shadowed.
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>
#include <map>

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Function to Build Tree
Node *buildTree(std::string str)
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

class Solution
{
public:

    // Function to return a list of nodes visible from the top view
    // from left to right in Binary Tree.
    std::vector<int> topView(Node *root)
    {
        std::vector<int> result;

        if(root==nullptr){
            return result;
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
            result.push_back(it->second->data);
        }
        return result;
    }
};

int main()
{

    int tc;
    std::cin >> tc;
    std::cin.ignore(256, '\n');

    while (tc--)
    {
        std::string treeString;
        std::getline(std::cin, treeString);

        Solution ob;
        Node *root = buildTree(treeString);
        std::vector<int> vec = ob.topView(root);
        for (int x : vec)
            std::cout << x << " ";
        std::cout << std::endl;
    }
    return 0;
}