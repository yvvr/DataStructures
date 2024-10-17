/**
 * Copyright (c) 2024
 *
 * Author: Your Name
 * This file is part of the DataStructures project.
 *
 * Modified binary search tree algorithms.
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
#include <sstream>
#include <queue>

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *next;

    Node(int val)
    {
        data = val;
        left = right = next = NULL;
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
                // Create the left child for the current node
                currNode->left = new Node(std::stoi(currVal));

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
                currNode->right = new Node(std::stoi(currVal));

                // Push it to the queue
                queue.push(currNode->right);
            }
            i++;
        }

        return root;
    }

    Node *Inorder(Node *root)
    {
        if (root->left == NULL)
            return root;
        Inorder(root->left);
    }

    /**
     * Populate Inorder Successor for all nodes.
     *
     * Given a Binary Tree, complete the function to populate the next pointer for all nodes.
     * The next pointer for every node should point to the Inorder successor of the node.
     * You do not have to return or print anything. Just make changes in the root node given to you.
     * https://www.geeksforgeeks.org/problems/populate-inorder-successor-for-all-nodes/1
     */
    void populateNext(Node *root)
    {
        Node *curr = root;
        Node *succ = nullptr;
        while (curr != nullptr)
        {
            if (curr->right == nullptr)
            {
                curr->next = succ;
                succ = curr;
                curr = curr->left;
            }
            else
            {
                // Find inorder predecessor
                Node *pred = curr->right;
                while (pred->left != nullptr && pred->left != curr)
                {
                    pred = pred->left;
                }

                if (pred->left == nullptr)
                {
                    pred->left = curr;
                    curr = curr->right;
                }
                else
                {
                    pred->left = nullptr;
                    curr->next = succ;
                    succ = curr;
                    curr = curr->left;
                }
            }
        }
    }
};

int main()
{
    Solution obj;

    std::string treeString;
    std::getline(std::cin, treeString);
    Node *root = obj.buildTree(treeString);

    obj.populateNext(root);
    Node *ptr = obj.Inorder(root);
    while (ptr)
    {
        printf("%d->%d ", ptr->data, ptr->next ? ptr->next->data : -1);
        ptr = ptr->next;
    }
    std::cout << std::endl;

    return 0;
}