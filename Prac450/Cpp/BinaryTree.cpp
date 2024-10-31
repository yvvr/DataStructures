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
#include <stack>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

class Solution
{
public:
    Node *buildTree(std::string str)
    {
        // Corner Case
        if (str.length() == 0 || str[0] == 'N')
            return nullptr;

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

    /**
     * Diameter of a Binary Tree
     *
     * The diameter of a tree (sometimes called the width) is the number of nodes on the longest path between two end nodes.
     * https://www.geeksforgeeks.org/problems/diameter-of-binary-tree/1
     */
    int diameter(Node *root)
    {
        return diameterUtil(root).second;
    }

    // The given root is the root of the Binary Tree
    // Return the root of the generated BST
    Node *binaryTreeToBST(Node *root)
    {
        Node *bstRoot = nullptr;
        binaryTreeToBstUtil(root, &bstRoot);
        return bstRoot;
    }

    /**
     * Construct BST from given preorder traversal using Stack
     *
     * Given preorder traversal of a binary search tree, construct the BST.
     * https://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversal-using-stack/
     */
    Node *constructTree(int pre[], int size)
    {
        if (size == 0)
        {
            return nullptr;
        }

        std::stack<Node *> stack;
        Node *root = new Node(pre[0]);
        stack.push(root);

        for (int i = 1; i < size; i++)
        {
            Node *temp = nullptr;
            while (!stack.empty() && stack.top()->data < pre[i])
            {
                temp = stack.top();
                stack.pop();
            }

            if (temp == nullptr)
            {
                stack.top()->left = new Node(pre[i]);
                stack.push(stack.top()->left);
            }
            else
            {
                temp->right = new Node(pre[i]);
                stack.push(temp->right);
            }
        }

        return root;
    }

    /**
     * Check if Tree is Isomorphic.
     * Given two Binary Trees. Check whether they are Isomorphic or not.
     * https://www.geeksforgeeks.org/problems/check-if-tree-is-isomorphic/1
     */
    bool isIsomorphic(Node *root1, Node *root2)
    {
        if (root1 == nullptr && root2 == nullptr)
        {
            return true;
        }

        if (root1 == nullptr || root2 == nullptr)
        {
            return false;
        }

        return root1->data == root2->data && isIsomorphic(root1->left, root2->left) && isIsomorphic(root1->right, root2->right) || isIsomorphic(root1->right, root2->left) && isIsomorphic(root1->left, root2->right);
    }

    void printInorder(struct Node *node)
    {
        if (node == NULL)
            return;

        printInorder(node->left);
        printf("%d ", node->data);
        printInorder(node->right);
    }

    /**
     * Function to check whether a binary tree is foldable or not.
     * Given a binary tree, check if the tree can be folded or not.
     * A tree can be folded if left and right subtrees of the tree are structure wise mirror image of each other.
     * An empty tree is considered as foldable.
     * https://www.geeksforgeeks.org/problems/foldable-binary-tree/1
     */
    bool IsFoldable(Node *root)
    {
        return IsFoldableUtil(root, root);
    }

    /**
     * Symmetric Tree.
     * Given a Binary Tree. Check whether it is Symmetric or not, i.e. whether the binary tree is a Mirror image of itself or not.
     * https://www.geeksforgeeks.org/problems/symmetric-tree/1
     */
    bool isSymmetric(struct Node *root)
    {
        return isSymmetricutil(root, root);
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
    }

    std::pair<int, int> diameterUtil(Node *root)
    {
        if (root == nullptr)
        {
            return {0, 0};
        }

        auto leftDiameter = diameterUtil(root->left);
        auto rightDiameter = diameterUtil(root->right);
        auto maxDiamterFromSubTrees = std::max(leftDiameter.second, rightDiameter.second);

        return {1 + std::max(leftDiameter.first, rightDiameter.first), std::max(maxDiamterFromSubTrees, 1 + leftDiameter.first + rightDiameter.first)};
    }

    bool IsFoldableUtil(Node *root1, Node *root2)
    {
        if (root1 == nullptr && root2 == nullptr)
        {
            return true;
        }

        if (root1 == nullptr || root2 == nullptr)
        {
            return false;
        }

        return IsFoldableUtil(root1->left, root2->right) && IsFoldableUtil(root1->right, root2->left);
    }

    bool isSymmetricutil(struct Node *root1, struct Node *root2)
    {
        if (root1 == nullptr && root2 == nullptr)
        {
            return true;
        }

        if (root1 == nullptr || root2 == nullptr)
        {
            return false;
        }

        return root1->data == root2->data && isSymmetricutil(root1->left, root2->right) && isSymmetricutil(root1->right, root2->left);
    }
};

int main()
{
    Solution obj;
    std::string s;
    std::getline(std::cin, s);
    Node *root = obj.buildTree(s);

    // Node *res = obj.binaryTreeToBST(root);
    // obj.printInorder(res);
    // std::cout << std::endl;

    // int pre[] = {10, 5, 1, 7, 40, 50};
    // int size = sizeof(pre) / sizeof(pre[0]);

    // Node *root = obj.constructTree(pre, size);

    // std::cout << "Inorder traversal of the constructed tree: \n";
    // obj.printInorder(root);

    // Diameter of a Binary Tree
    // std::cout << obj.diameter(root) << std::endl;

    // std::string s1, s2;
    // getline(std::cin, s1);
    // getline(std::cin, s2);
    // Node *root1 = obj.buildTree(s1);
    // Node *root2 = obj.buildTree(s2);
    // if (obj.isIsomorphic(root1, root2))
    //     std::cout << "Yes" << std::endl;
    // else
    //     std::cout << "No" << std::endl;

    // Foldable Binary Tree
    // if (obj.IsFoldable(root))
    // {
    //     std::cout << "Yes\n";
    // }
    // else
    // {
    //     std::cout << "No\n";
    // }

    // Symmetric Tree
    if (obj.isSymmetric(root))
    {
        std::cout << "Yes\n";
    }
    else
    {
        std::cout << "No\n";
    }

    return 0;
}