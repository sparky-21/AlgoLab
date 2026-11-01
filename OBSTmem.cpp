#include<bits/stdc++.h>
using namespace std;
double solve(int i, int j,
             vector<vector<double>>& dp,
             vector<vector<int>>& root,
             vector<int>& key,
             vector<double>& prefix)
{
    if(i>j) return 0;

    if(dp[i][j] !=-1) return dp[i][j];

    long long sum=prefix[j+1]-prefix[i];

    dp[i][j]= DBL_MAX;

    for(int r=i ; r<=j;r++)
    {
        double left = solve(i,r-1,dp,root,key,prefix);
        double right = solve(r+1,j,dp,root,key,prefix);

        double cost = left + right + sum;

        if(cost < dp[i][j])
        {
            dp[i][j] = cost;
            root[i][j] = r;
        }
    }

    return dp[i][j];
}
// Print optimal BST
void printTree(int i, int j,
               vector<vector<int>>& root,
               vector<int>& key,
               string space = "",
               string relation = "Root")
{
    if(i > j)
        return;

    int r = root[i][j];

    cout << space << relation << ": " << key[r] << endl;

    printTree(i,r-1,root,key,space+"    ","L");
    printTree(r+1,j,root,key,space+"    ","R");
}
int main()
{
    int n ;
    cin>>n;

    vector<int>key(n);
    vector<long long>freq(n);

    for(int i=0; i<n; i++) cin>>key[i];
    for(int i=0; i<n; i++) cin>>freq[i];

    vector<double> prefix(n+1,0);

    for(int i=0; i<n; i++)
        prefix[i+1] = prefix[i] + freq[i];

    vector<vector<double>> dp(n, vector<double>(n,-1));

    vector<vector<int>> root(n, vector<int>(n,-1));

    double ans= solve(0,n-1,dp,root,key,prefix);

     cout << fixed << setprecision(4);

    cout << "\nMinimum Search Cost: " << ans << endl;

    // Print DP table
    cout << "\nDP Table:\n";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i<=j)
                cout << setw(10) << dp[i][j];
            else
                cout << setw(10) << "-";
        }
        cout << endl;
    }

    // Print root table
    cout << "\nRoot Table:\n";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i<=j)
                cout << setw(10) << key[root[i][j]];
            else
                cout << setw(10) << "-";
        }
        cout << endl;
    }

    // Print optimal BST
    cout << "\nOptimal Binary Search Tree:\n";

    printTree(0,n-1,root,key);

    return 0;

}
