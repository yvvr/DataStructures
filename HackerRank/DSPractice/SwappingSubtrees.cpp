/**
 * A binary tree is a tree which is characterized by one of the following properties:
 *
 * It can be empty (null).
 * It contains a root node only.
 * It contains a root node with a left subtree, a right subtree, or both. These subtrees are also binary trees.
 *
 * In-order traversal is performed as Traverse the left subtree. Visit root. Traverse the right subtree.
 *
 * For this in-order traversal, start from the left child of the root node and keep exploring the left subtree until you reach a leaf.
 * When you reach a leaf, back up to its parent, check for a right child and visit it if there is one.
 * If there is not a child, you've explored its left and right subtrees fully. If there is a right child, traverse its left subtree then its right in the same manner.
 * Keep doing this until you have traversed the entire tree.
 *
 * Swap operation:
 *
 * We define depth of a node as follows:
 * - The root node is at depth 1.
 * - If the depth of the parent node is d, then the depth of current node will be d + 1.
 *
 * Given a tree and an integer, k, in one operation, we need to swap the subtrees of all the nodes at each depth h, where h ∈ [k, 2k, 3k,...].
 * In other words, if h is a multiple of k, swap the left and right subtrees of that level.
 *
 * You are given a tree of n nodes where nodes are indexed from [1..n] and it is rooted at 1.
 * You have to perform t swap operations on it, and after each swap operation print the in-order traversal of the current state of the tree.
 *
 * Function Description:
 *
 * Complete the swapNodes function in the editor below.
 * It should return a two-dimensional array where each element is an array of integers representing the node indices of an in-order traversal after a swap operation.
 *
 * swapNodes has the following parameter(s):
 * - indexes: an array of integers representing index values of each node[i], beginning with node[1], the first element, as the root.
 * - queries: an array of integers, each representing a k value.
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

std::string ltrim(const std::string &);
std::string rtrim(const std::string &);
std::vector<std::string> split(const std::string &);

void inorderOfTree(std::vector<std::vector<int>> &indexes, int index, std::vector<int> &result)
{
    if (index < 0)
    {
        return;
    }

    inorderOfTree(indexes, indexes[index][0] - 1, result);
    result.push_back(index + 1);
    inorderOfTree(indexes, indexes[index][1] - 1, result);
}

int findHeight(std::vector<std::vector<int>> &indexes, int index)
{
    if (index < 0)
    {
        return 0;
    }

    int leftHeight = findHeight(indexes, indexes[index][0] - 1);
    int rightHeight = findHeight(indexes, indexes[index][1] - 1);
    return 1 + std::max(leftHeight, rightHeight);
}

/*
 * Complete the 'swapNodes' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */

std::vector<std::vector<int>> swapNodes(std::vector<std::vector<int>> &indexes, std::vector<int> &queries)
{
    int height = findHeight(indexes, 0);
    std::vector<std::vector<int>> results;

    for (int i = 0; i < queries.size(); i++)
    {
        int k = queries[i];
        int nextk = k;
        int level = 0;
        std::queue<int> q;
        
        q.push(0);

        while (!q.empty() && (nextk <= height))
        {
            int qSize = q.size();
            level += 1;

            for (int j = 0; j < qSize; j++)
            {
                int index = q.front();
                q.pop();

                if (indexes[index][0] != -1)
                {
                    q.push(indexes[index][0] - 1);
                }
                if (indexes[index][1] != -1)
                {
                    q.push(indexes[index][1] - 1);
                }

                if (level == nextk)
                {
                    std::swap(indexes[index][0], indexes[index][1]);
                }
            }
            if (level == nextk)
            {
                nextk += k;
            }
        }
        std::vector<int> result;
        inorderOfTree(indexes, 0, result);
        results.push_back(result);
    }
    return results;
}

int main()
{
    std::string n_temp;
    std::getline(std::cin, n_temp);

    int n = std::stoi(ltrim(rtrim(n_temp)));
    std::vector<std::vector<int>> indexes(n);

    for (int i = 0; i < n; i++)
    {
        indexes[i].resize(2);

        std::string indexes_row_temp_temp;
        std::getline(std::cin, indexes_row_temp_temp);
        std::vector<std::string> indexes_row_temp = split(rtrim(indexes_row_temp_temp));

        for (int j = 0; j < 2; j++)
        {
            int indexes_row_item = stoi(indexes_row_temp[j]);
            indexes[i][j] = indexes_row_item;
        }
    }

    std::string queries_count_temp;
    std::getline(std::cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));
    std::vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++)
    {
        std::string queries_item_temp;
        std::getline(std::cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));
        queries[i] = queries_item;
    }

    std::vector<std::vector<int>> result = swapNodes(indexes, queries);

    for (size_t i = 0; i < result.size(); i++)
    {
        for (size_t j = 0; j < result[i].size(); j++)
        {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

std::string ltrim(const std::string &str)
{
    std::string s(str);

    s.erase(
        s.begin(),
        std::find_if(s.begin(), s.end(), [](unsigned char ch)
                     { return !isspace(ch); }));

    return s;
}

std::string rtrim(const std::string &str)
{
    std::string s(str);

    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                     { return !isspace(ch); })
            .base(),
        s.end());

    return s;
}

std::vector<std::string> split(const std::string &str)
{
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while ((end = str.find(" ", start)) != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));
    return tokens;
}
