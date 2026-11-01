
#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int solve(int i, int w, vector<int>& coin,
          vector<vector<int>>& dp)
{
    if(w == 0)
        return 0;

    if(i == coin.size() || w < 0)
        return INF;

    if(dp[i][w] != -1)
        return dp[i][w];

    // Take current coin
    int take = INF;

    if(coin[i] <= w)
        take = 1 + solve(i,w-coin[i],coin,dp);

    // Skip current coin
    int notTake = solve(i+1,w,coin,dp);

    return dp[i][w] = min(take,notTake);
}

int main()
{
    int n,W;
    cin >> n >> W;

    vector<int> coin(n);

    for(int i=0; i<n; i++)
        cin >> coin[i];

    vector<vector<int>> dp(
        n, vector<int>(W+1,-1)
    );

    int ans = solve(0,W,coin,dp);

    if(ans >= INF)
    {
        cout << "Not Possible";
        return 0;
    }

    cout << "Minimum Coins: " << ans << endl;

    // Reconstruct selected coins
    cout << "Coins Used: ";

    int i=0, w=W;

    while(w > 0 && i<n)
    {
        int take = INF;

        if(coin[i] <= w)
            take = 1 + solve(i,w-coin[i],coin,dp);

        int notTake = solve(i+1,w,coin,dp);

        if(take <= notTake)
        {
            cout << coin[i] << " ";
            w -= coin[i];
        }
        else
        {
            i++;
        }
    }

    return 0;
}
/*
#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{
    int n,W;
    cin >> n >> W;

    vector<int> coin(n);

    for(int i=0; i<n; i++)
        cin >> coin[i];

    vector<int> dp(W+1,INF);
    vector<int> parent(W+1,-1);

    dp[0] = 0;

    // Tabulation
    for(int w=1; w<=W; w++)
    {
        for(int i=0; i<n; i++)
        {
            if(coin[i] <= w)
            {
                if(dp[w-coin[i]] != INF &&
                   dp[w-coin[i]]+1 < dp[w])
                {
                    dp[w] = dp[w-coin[i]]+1;
                    parent[w] = coin[i];
                }
            }
        }
    }

    if(dp[W] == INF)
    {
        cout << "Not Possible";
        return 0;
    }

    cout << "Minimum Coins: " << dp[W] << endl;

    // Print selected coins
    cout << "Coins Used: ";

    int w = W;

    while(w > 0)
    {
        cout << parent[w] << " ";
        w -= parent[w];
    }

    return 0;
}
*/
