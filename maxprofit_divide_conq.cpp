#include<bits/stdc++.h>
using namespace std;

void max_cross_subarr(vector<int> &arr, int low, int mid, int high, int &max_left, int &max_right, int &sum)
{
    int left_sum = INT_MIN;
    sum = 0;
    for (int i = mid; i >= low; i--)
    {
        sum += arr[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= high; i++)
    {
        sum += arr[i];
        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = i;
        }
    }
    sum = left_sum + right_sum;
}
void max_subarr(vector<int> &arr, int l, int h, int &max_left, int &max_right, int &sum)
{
    if (l == h)
    {
        max_left = l;
        max_right = h;
        sum = arr[l];
        return;
    }
    int mid = (l + h) / 2;
    int left_max_left, left_max_right, left_sum;
    int right_max_left, right_max_right, right_sum;
    int cross_max_left, cross_max_right, cross_sum;

    max_subarr(arr, l, mid, left_max_left, left_max_right, left_sum);
    max_subarr(arr, mid + 1, h, right_max_left, right_max_right, right_sum);
    max_cross_subarr(arr, l, mid, h, cross_max_left, cross_max_right, cross_sum);

    if (left_sum >= right_sum && left_sum >= cross_sum)
    {
        max_left = left_max_left;
        max_right = left_max_right;
        sum = left_sum;
    }
    else if (right_sum >= cross_sum)
    {
        max_left = right_max_left;
        max_right = right_max_right;
        sum = right_sum;
    }
    else
    {
        max_left = cross_max_left;
        max_right = cross_max_right;
        sum = cross_sum;
    }

}
int main()
{
    vector<int> arr={-6,4,-2,3,-2};
    int n = arr.size();
    int max_left, max_right, sum;
    max_subarr(arr, 0, n - 1, max_left, max_right, sum);
    cout << "Maximum subarray is from index " << max_left << " to " << max_right << " with sum " << sum << endl;
    return 0;
}
