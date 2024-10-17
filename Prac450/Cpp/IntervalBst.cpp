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
#include <vector>

struct Interval
{
    int low;
    int high;
};

struct INTNode
{
    Interval *i;
    int max;
    INTNode *left, *right;

    INTNode(Interval i)
    {
        this->i = new Interval(i);
        this->left = nullptr;
        this->right = nullptr;
        max = i.high;
    }
};

INTNode *insert(INTNode *root, Interval i)
{
    if (root == nullptr)
    {
        return new INTNode(i);
    }

    int l = root->i->low;
    if (i.low < l)
    {
        root->left = insert(root->left, i);
    }
    else
    {
        root->right = insert(root->right, i);
    }

    if (root->max < i.high)
    {
        root->max = i.high;
    }
    return root;
}

bool isOVerlap(Interval i1, Interval i2)
{
    if (i1.low < i2.high && i2.low < i1.high)
        return true;

    return false;
}

void overlapInterval(INTNode *root, Interval i, std::vector<Interval *> &result)
{
    if (root == nullptr)
    {
        return;
    }

    if (isOVerlap(*(root->i), i))
    {
        result.push_back(root->i);
    }

    if (root->left != nullptr && root->left->max >= i.low)
    {
        return overlapInterval(root->left, i, result);
    }

    return overlapInterval(root->right, i, result);
}

void printConflictingIntervals(Interval appt[], int n)
{
    INTNode *root = NULL;
    root = insert(root, appt[0]);

    for (int i = 1; i < n; i++)
    {
        std::vector<Interval *> result;
        overlapInterval(root, appt[i], result);

        for (auto res : result)
        {
            if (res != NULL)
                std::cout << "[" << appt[i].low << "," << appt[i].high << "] Conflicts with [" << res->low << "," << res->high << "]\n";
        }

        // Insert this appointment
        root = insert(root, appt[i]);
    }
}

// Driver program to test above functions
int main()
{
    // Let us create interval tree shown in above figure
    Interval appt[] = {{1, 5}, {3, 7}, {2, 6}, {10, 15}, {5, 6}, {4, 100}};
    int n = sizeof(appt) / sizeof(appt[0]);

    std::cout << "Following are conflicting intervals\n";
    printConflictingIntervals(appt, n);

    return 0;
}