
#include<bits/stdc++.h>
using namespace std;

// Function to print the optimal BST
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

    // Left subtree
    printTree(i, r-1, root, key, space+"    ", "L");

    // Right subtree
    printTree(r+1, j, root, key, space+"    ", "R");
}

int main()
{
    int n;
    cin >> n;

    vector<int> key(n);
    vector<long long> freq(n);

    // Input keys
    for(int i=0; i<n; i++)
        cin >> key[i];

    // Input frequencies
    for(int i=0; i<n; i++)
        cin >> freq[i];

    // Prefix sum
    vector<long long> prefix(n+1,0);

    for(int i=0; i<n; i++)
        prefix[i+1] = prefix[i] + freq[i];

    // DP table
    vector<vector<long long>> dp(
        n, vector<long long>(n,0)
    );

    // Root table
    vector<vector<int>> root(
        n, vector<int>(n,-1)
    );

    // Tabulation
    for(int len=1; len<=n; len++)
    {
        for(int i=0; i<=n-len; i++)
        {
            int j = i+len-1;

            dp[i][j] = LLONG_MAX;

            // Frequency sum of current interval
            long long sum = prefix[j+1]-prefix[i];

            // Try every key as root
            for(int r=i; r<=j; r++)
            {
                long long left = 0;
                long long right = 0;

                if(r>i)
                    left = dp[i][r-1];

                if(r<j)
                    right = dp[r+1][j];

                long long cost = left + right + sum;

                if(cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Print minimum cost
    cout << "\nMinimum Search Cost: "
         << dp[0][n-1] << endl;

    // Print DP table
    cout << "\nDP Table:\n";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i<=j)
                cout << setw(6) << dp[i][j];
            else
                cout << setw(6) << "-";
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
                cout << setw(6) << key[root[i][j]];
            else
                cout << setw(6) << "-";
        }
        cout << endl;
    }

    // Print actual optimal BST
    cout << "\nOptimal Binary Search Tree:\n";

    printTree(0,n-1,root,key);

    return 0;
}

