int binarySearch(std::vector<int> arr, int i, int j, int num)
{
    while (i < j)
    {
        int mid = i + (j - i) / 2;
        if (arr[mid] == num)
            break;
        else if (arr[mid] < num)
            i = mid + 1;
        else
            j = mid - 1;
    }
    return arr[i];
}