#include<bits/stdc++.h>
using namespace std;
int maxCrossingSum(vector<int>&a,int low ,int mid, int high ,int& start, int& end )
{
    int leftSum=INT_MIN;
    int leftIndex=mid;
    int sum=0;

    for(int i=mid;i>=low;i--)
    {
        sum += a[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            leftIndex = i;
        }
    }
      int rightSum = INT_MIN;
    sum = 0;
    int rightIndex = mid + 1;

    for (int i = mid + 1; i <= high; i++)
    {
        sum += a[i];

        if (sum > rightSum)
        {
            rightSum = sum;
            rightIndex = i;
        }
    }

    start = leftIndex;
    end = rightIndex;

    return leftSum + rightSum;
}
int maxsubsum(vector<int>&a,int low , int high , int &start ,int &end)
{
    if(low==high)
    {
        start=end=low;
        return a[low];
    }
    int mid = low + (high - low) / 2;
    int leftstart,leftend;
    int rightstart,rightend;
    int crossstart,crossend;

    int leftsum= maxsubsum(a,low,mid,leftstart,leftend);
    int rightsum=maxsubsum(a,mid+1,high,rightstart,rightend);
    int crossSum = maxCrossingSum(a, low, mid, high,
                                  crossstart, crossend);

    // Find the maximum among three cases
    if (leftsum >= rightsum && leftsum >= crossSum)
    {
        start = leftstart;
        end = leftend;
        return leftsum;
    }
    else if (rightsum >= leftsum && rightsum >= crossSum)
    {
        start = rightstart;
        end = rightend;
        return rightsum;
    }
    else
    {
        start = crossstart;
        end = crossend;
        return crossSum;
    }

}
int main()
{
    int n; cin>>n;

    vector<int>a(n);

    for(int i=0;i<n;i++) cin>>a[i];
    int start,end;
    int msum = maxsubsum(a,0,n-1,start,end);

     cout << "\nMaximum Subarray Sum: " << msum << endl;

    cout << "Maximum Subarray: ";
    for (int i = start; i <= end; i++)
        cout << a[i] << " ";

    cout << endl;

    return 0;

}
