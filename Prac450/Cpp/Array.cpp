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
#include <vector>
#include <stack>

class Solution
{
public:
    // Function to find the next greater element for each element of the array.
    std::vector<long long> nextLargerElement(std::vector<long long> arr, int n)
    {
        std::stack<std::pair<long long, int>> stack;

        for (int i = 0; i < arr.size(); i++)
        {
            while (!stack.empty() && stack.top().first < arr[i])
            {
                arr[stack.top().second] = arr[i];
                stack.pop();
            }
            stack.push(std::make_pair(arr[i], i));
        }

        while (!stack.empty())
        {
            arr[stack.top().second] = -1;
            stack.pop();
        }

        return arr;
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::vector<long long> arr(n);
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    Solution obj;
    std::vector<long long> res = obj.nextLargerElement(arr, n);
    for (long long i : res)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}