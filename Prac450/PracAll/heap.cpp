#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>

class MinHeap
{
private:
    int *arr;
    int capacity;
    int size;

public:
    MinHeap(int capacity);

    void minHeapify(int i);

    int parent(int i);

    int right(int i);

    int left(int i);

    int extractMin();

    void decreaseKey(int i, int val);

    int getMin();

    void deleteKey(int i);

    void insertKey(int val);

    void swap(int &x, int &y);

    ~MinHeap();
};

MinHeap::MinHeap(int capacity)
{
    this->capacity = capacity;
    arr = new int[capacity];
    size = 0;
}

MinHeap::~MinHeap()
{
}

int MinHeap::parent(int i)
{
    return (i - 1) / 2;
}

int MinHeap::left(int i)
{
    return 2 * i + 1;
}

int MinHeap::right(int i)
{
    return 2 * i + 2;
}

void MinHeap::insertKey(int val)
{
    if (size == capacity)
    {
        return;
    }

    size += 1;
    int i = size - 1;
    arr[i] = val;

    while (i > 0 && arr[parent(i)] > arr[i])
    {
        swap(arr[parent(i)], arr[i]);
        i = parent(i);
    }
}

void MinHeap::minHeapify(int i)
{
    int smallest = i;

    int r = right(i);
    int l = left(i);

    if (l < this->size && arr[smallest] > arr[l])
    {
        smallest = l;
    }

    if (r < this->size && arr[smallest] > arr[r])
    {
        smallest = r;
    }

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        minHeapify(smallest);
    }
}

int MinHeap::extractMin()
{
    if (size == 0)
    {
        return INT_MAX;
    }

    if (size == 1)
    {
        size -= 1;
        return arr[0];
    }

    int root = arr[0];
    arr[0] = arr[size - 1];
    size -= 1;

    minHeapify(0);
    return root;
}

void MinHeap::decreaseKey(int i, int val)
{
    if (i > size - 1)
    {
        return;
    }

    arr[i] = val;
    while (i > 0 && arr[parent(i)] > arr[i])
    {
        swap(arr[parent(i)], arr[i]);
        i = parent(i);
    }
}

void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}

int MinHeap::getMin()
{
    if (size == 0)
    {
        return INT_MAX;
    }

    return arr[0];
}

void MinHeap::swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
};

void print(std::vector<int> &vc)
{
    for (auto i : vc)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int getHeight(std::vector<int> & arr){
    return std::floor(std::log2(arr.size()));
}

int main()
{
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    std::cout << h.extractMin() << " ";
    std::cout << h.getMin() << " ";
    h.decreaseKey(2, 1);
    std::cout << h.getMin() << std::endl;

    std::vector<int> vec = {3, 4, 7, 1, 9, 2, 15};
    std::make_heap(vec.begin(), vec.end());

    std::cout << "The maximum element of heap is : ";
    std::cout << vec.front() << std::endl;

    vec.push_back(50);
    std::push_heap(vec.begin(), vec.end());
    std::cout << "Heap after push_heap(): ";

    print(vec);

    std::sort_heap(vec.begin(), vec.end());
    std::cout << "The heap elements after sorting are: ";
    print(vec);

    std::priority_queue<int> maxPq;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minPq;

    maxPq.push(30);
    maxPq.push(10);
    maxPq.push(20);
    maxPq.push(40);

    std::cout << "Elements removed from priority queue in order:\n";

    while (!maxPq.empty())
    {
        std::cout << maxPq.top() << " ";
        maxPq.pop();
    }

    minPq.push(30);
    minPq.push(10);
    minPq.push(20);
    minPq.push(40);
    std::cout << std::endl;

    std::cout << "Elements removed from priority queue in order:\n";

    while (!minPq.empty())
    {
        std::cout << minPq.top() << " ";
        minPq.pop();
    }

    return 0;
}