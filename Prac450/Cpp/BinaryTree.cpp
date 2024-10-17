/**
 * Copyright (c) 2024
 *
 * Author: Your Name
 * This file is part of the DataStructures project.
 *
 * Modified binary tree algorithms.
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
#include <string>
#include <vector>
#include <sstream>
#include <queue>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

class Solution
{
public:
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

                // Create the left child for the current Node
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

    // The given root is the root of the Binary Tree
    // Return the root of the generated BST
    Node *binaryTreeToBST(Node *root)
    {
        Node *bstRoot = nullptr;
        binaryTreeToBstUtil(root, &bstRoot);
        return bstRoot;
    }

    void printInorder(struct Node *node)
    {
        if (node == NULL)
            return;

        printInorder(node->left);
        printf("%d ", node->data);
        printInorder(node->right);
    }

private:
    Node *insertBst(Node *root, int data)
    {
        if (root == nullptr)
        {
            return new Node(data);
        }

        if (root->data < data)
        {
            Node *temp = insertBst(root->right, data);
            root->right = temp;
        }
        else
        {
            Node *temp = insertBst(root->left, data);
            root->left = temp;
        }
        return root;
    }

    void binaryTreeToBstUtil(Node *root, Node **bstRoot)
    {
        if (root == nullptr)
        {
            return;
        }
        binaryTreeToBstUtil(root->left, bstRoot);
        *bstRoot = insertBst(*bstRoot, root->data);
        binaryTreeToBstUtil(root->right, bstRoot);
    };

    int main()
    {
        Solution obj;
        std::string s;
        std::getline(std::cin, s);
        Node *root = obj.buildTree(s);

        Node *res = obj.binaryTreeToBST(root);
        obj.printInorder(res);
        std::cout << std::endl;
        return 0;
    }