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
    // Function that constructs BST from its preorder traversal.
    Node *Bst(int pre[], int size)
    {
        // return BstUtil(pre, 0, size - 1);
        int idx = 0;
        return BstUtiloptimized(pre, idx, size, INT_MIN, INT_MAX);
    }

    // A utility function to print postorder traversal of a Binary Tree
    void printPostorder(Node *node)
    {
        if (node == NULL)
            return;
        printPostorder(node->left);
        printPostorder(node->right);
        printf("%d ", node->data);
    }

private:
    int findMidForBstArray(int pre[], int l, int r)
    {
        for (int i = l + 1; i <= r; i++)
        {
            if (pre[i] > pre[l])
            {
                return i;
            }
        }
        return r + 1;
    }

    Node *BstUtil(int pre[], int l, int r)
    {
        if (l > r)
        {
            return nullptr;
        }
        Node *root = new Node(pre[l]);
        int pivot = findMidForBstArray(pre, l, r);

        root->left = BstUtil(pre, l + 1, pivot - 1);
        root->right = BstUtil(pre, pivot, r);

        return root;
    }

    Node *BstUtiloptimized(int pre[], int& idx, int size, int min, int max)
    {
        if (idx >= size)
        {
            return nullptr;
        }

        if (pre[idx] <= min || pre[idx] >= max)
        {
            return nullptr;
        }

        Node *root = new Node(pre[idx]);
        idx++;

        root->left = BstUtiloptimized(pre, idx, size, min, root->data);
        root->right = BstUtiloptimized(pre, idx, size, root->data, max);

        return root;
    }
};

int main()
{
    // Note that size of arr[] is considered 100 according to
    // the constraints mentioned in problem statement.
    int arr[1000], x, n;

    // Input the size of the array
    std::cin >> n;

    // Input the array
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    Solution ob;
    ob.printPostorder(ob.Bst(arr, n));
    std::cout << std::endl;

    return 0;
}