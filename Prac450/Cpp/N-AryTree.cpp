/**
 * Copyright (c) 2024
 *
 * Author: Your Name
 * This file is part of the DataStructures project.
 *
 * N-Ary tree algorithms.
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
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>

struct Node
{
    int data;
    std::vector<Node *> children;

    Node(int data)
    {
        this->data = data;
    }
};

struct CNode
{
    wchar_t data;
    std::vector<CNode *> children;

    CNode(wchar_t data)
    {
        this->data = data;
    }
};

class Solution
{
    int mod = 1e9 + 7;

public:
    void preorder(CNode *root)
    {
        if (root == nullptr)
        {
            return;
        }

        std::wcout << root->data << " ";
        for (auto child : root->children)
        {
            preorder(child);
        }
    }

    int depthOfNTree(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int maxDepth = 0;
        for (auto child : root->children)
        {
            maxDepth = std::max(maxDepth, depthOfNTree(child));
        }

        return maxDepth + 1;
    }

    int sumNodes(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int sum = root->data;
        for (int i = 0; i < root->children.size(); i++)
        {
            sum += sumNodes(root->children[i]);
        }

        return sum;
    }

    int sumNodesWithLevelOrder(Node *root)
    {
        int sum = 0;
        std::queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();

            sum += node->data;
            for (auto child : node->children)
            {
                q.push(child);
            }
        }

        return sum;
    }

    void serialize(CNode *root, FILE *fp)
    {
        if (root == nullptr)
        {
            return;
        }

        fprintf(fp, "%c ", root->data);

        for (int i = 0; i < root->children.size(); i++)
        {
            serialize(root->children[i], fp);
        }

        fprintf(fp, "%lc ", '#');
        return;
    }

    CNode *deserialize(FILE *fp)
    {
        char c;
        if (!fscanf(fp, "%lc ", &c) || c == '#')
        {
            return nullptr;
        }

        CNode *root = new CNode(c);
        while (true)
        {
            CNode *child = deserialize(fp);
            if (child != nullptr)
            {
                root->children.push_back(child);
            }
            else
            {
                break;
            }
        }

        return root;
    }

    /**
     * Check if the given n-ary tree is a binary tree
     * Given an n-ary tree, the task is to check whether the given tree is binary or not.
     * https://www.geeksforgeeks.org/check-if-the-given-n-ary-tree-is-a-binary-tree/?ref=lbp
     */
    bool isBinaryTree(struct CNode *root)
    {
        if (root == nullptr)
        {
            return true;
        }

        bool isBinary = root->children.size() <= 2;
        for (int i = 0; i < root->children.size(); i++)
        {
            isBinary = isBinary && isBinaryTree(root->children[i]);
            if (!isBinary)
            {
                return isBinary;
            }
        }
        return isBinary;
    }

    /**
     * Largest element in an N-ary Tree
     * Given an n-ary tree containing positive node values, the task is to find the node with the largest value in the given n-ary tree.
     * https://www.geeksforgeeks.org/largest-element-in-an-n-ary-tree/?ref=lbp
     */
    int findLargestNode(Node *root)
    {
        if (root == nullptr)
        {
            return INT_MIN;
        }

        int max = root->data;

        for (auto child : root->children)
        {
            max = std::max(max, findLargestNode(child));
        }
        return max;
    }

    void printGraphicallyNTree(Node *root)
    {
        std::vector<bool> flags(depthOfNTree(root), true);
        printGraphicallyNTreeUtil(root, flags, 0, true);
    }

    std::string ConvertCanonical(std::unordered_map<int, std::vector<int>> &tree, int vertex, int parent)
    {
        std::vector<std::string> childForms;
        std::string canonical = "(";

        for (auto neighbour : tree[vertex])
        {
            if (neighbour == parent)
            {
                continue;
            }

            childForms.push_back(ConvertCanonical(tree, neighbour, vertex));
        }

        std::sort(childForms.begin(), childForms.end());

        for (auto child : childForms)
        {
            canonical += child;
        }
        canonical += ")";

        return canonical;
    }

    int countSubtreesUtil(int cur, int par, std::vector<std::vector<int>> graph, int &ans)
    {
        int res = 1;

        for (int i = 0; i < graph[cur].size(); i++)
        {

            int v = graph[cur][i];

            if (v == par)
                continue;
            res = (res * (countSubtreesUtil(v, cur, graph, ans) + 1)) % mod;
        }

        ans = (ans + res) % mod;

        return res;
    }

    /**
     * Function to count the number of subtrees in the given tree.
     */
    void countSubtrees(int N, std::vector<std::pair<int, int>> &adj)
    {
        std::vector<std::vector<int>> graph;
        int ans = 0;

        for (int i = 0; i < N - 1; i++)
        {
            int a = adj[i].first;
            int b = adj[i].second;

            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        countSubtreesUtil(0, -1, graph, ans);

        // Print count of subtrees
        std::cout << ans + 1;
    }

    CNode *createDummyCTree()
    {
        CNode *root = new CNode('A');
        root->children.push_back(new CNode('B'));
        root->children.push_back(new CNode('C'));
        root->children.push_back(new CNode('D'));
        root->children[0]->children.push_back(new CNode('E'));
        root->children[0]->children.push_back(new CNode('F'));
        root->children[2]->children.push_back(new CNode('G'));
        root->children[2]->children.push_back(new CNode('H'));
        root->children[2]->children.push_back(new CNode('I'));
        root->children[2]->children.push_back(new CNode('J'));
        root->children[0]->children[1]->children.push_back(new CNode('K'));
        return root;
    }

    void addedge(std::unordered_map<int, std::vector<int>> &tree, int a, int b)
    {
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

private:
    void printGraphicallyNTreeUtil(Node *root, std::vector<bool> flags, int depth, bool isLast)
    {
        if (root == nullptr)
        {
            return;
        }

        for (int i = 1; i < depth; i++)
        {
            if (flags[i])
            {
                std::cout << "|   ";
            }
            else
            {
                std::cout << "    ";
            }
        }

        if (depth == 0)
        {
            std::cout << root->data << std::endl;
        }
        else
        {
            std::cout << "+--- " << root->data << std::endl;
        }

        if (isLast)
        {
            flags[depth] = false;
        }

        for (int i = 0; i < root->children.size(); i++)
        {
            printGraphicallyNTreeUtil(root->children[i], flags, depth + 1, (i == root->children.size() - 1));
        }

        flags[depth] = true;
    }
};

int main()
{
    Solution obj;

    // Creating a generic tree
    // Node *root = new Node(20);
    // (root->children).push_back(new Node(2));
    // (root->children).push_back(new Node(34));
    // (root->children).push_back(new Node(50));
    // (root->children).push_back(new Node(60));
    // (root->children).push_back(new Node(70));
    // (root->children[0]->children).push_back(new Node(15));
    // (root->children[0]->children).push_back(new Node(20));
    // (root->children[0]->children).push_back(new Node(90));
    // (root->children[1]->children).push_back(new Node(30));
    // (root->children[2]->children).push_back(new Node(40));
    // (root->children[2]->children).push_back(new Node(100));
    // (root->children[2]->children).push_back(new Node(20));
    // (root->children[0]->children[1]->children).push_back(new Node(25));
    // (root->children[0]->children[1]->children).push_back(new Node(50));

    // std::cout << obj.sumNodes(root) << std::endl;
    // std::cout << obj.sumNodesWithLevelOrder(root) << std::endl;

    // FILE *fp = fopen("tree.txt", "w");
    // if (fp == nullptr)
    // {
    //     puts("Could not open file");
    //     return 0;
    // }
    // obj.serialize(obj.createDummyCTree(), fp);
    // fclose(fp);

    // // Let us deserialize the stored tree into root1
    // fp = fopen("tree.txt", "r");
    // CNode *root1 = obj.deserialize(fp);

    // printf("Constructed N-Ary Tree from file is \n");
    // obj.preorder(root1);

    // Check if the given n-ary tree is a binary tree
    // CNode *root = new CNode('A');
    // (root->children).push_back(new CNode('B'));
    // (root->children).push_back(new CNode('C'));
    // (root->children).push_back(new CNode('G'));
    // (root->children[0]->children).push_back(new CNode('D'));
    // (root->children[0]->children).push_back(new CNode('E'));
    // (root->children[1]->children).push_back(new CNode('F'));

    // std::cout << (obj.isBinaryTree(root) ? "Yes" : "No");

    // Print N-ary tree graphically
    // obj.printGraphicallyNTree(root);

    // Given N-ary Tree 1
    std::unordered_map<int, std::vector<int>> tree;
    obj.addedge(tree, 1, 3);
    obj.addedge(tree, 1, 2);
    obj.addedge(tree, 1, 5);
    obj.addedge(tree, 3, 4);
    obj.addedge(tree, 4, 8);
    obj.addedge(tree, 4, 9);
    obj.addedge(tree, 3, 6);
    obj.addedge(tree, 6, 7);

    // Given N-ary Tree 2
    std::unordered_map<int, std::vector<int>> tree2;
    obj.addedge(tree2, 1, 3);
    obj.addedge(tree2, 3, 4);
    obj.addedge(tree2, 3, 5);
    obj.addedge(tree2, 1, 8);
    obj.addedge(tree2, 8, 9);
    obj.addedge(tree2, 1, 2);
    obj.addedge(tree2, 2, 6);
    obj.addedge(tree2, 2, 7);

    std::string cononicalTree = obj.ConvertCanonical(tree, 1, -1);
    std::string cononicalTree2 = obj.ConvertCanonical(tree2, 3, -1);

    if (cononicalTree == cononicalTree2)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;

    return 0;
}