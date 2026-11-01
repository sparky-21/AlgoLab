#include<bits/stdc++.h>
using namespace std;
/*int mincostclmstr(int n,vector<int>&cost)
{
  vector<int>dp(n+1);
  dp[0]=0;
  dp[1]=0;

  for(int i=2; i<=n;i++)
  {
      dp[i]= min(dp[i-1]+cost[i-1] ,dp[i-2]+cost[i-2] );
  }
  return dp[n];
}*/

int mincostclmstr(int n, vector<int>& cost)
{
    vector<int> dp(n+1);
    vector<int> parent(n+1,-1);

    dp[0]=0;
    dp[1]=0;

    for(int i=2; i<=n; i++)
    {
        int c1 = dp[i-1] + cost[i-1];
        int c2 = dp[i-2] + cost[i-2];

        if(c1 <= c2)
        {
            dp[i] = c1;
            parent[i] = i-1;
        }
        else
        {
            dp[i] = c2;
            parent[i] = i-2;
        }
    }

    cout<<"Minimum Cost: "<<dp[n]<<endl;

    // Reconstruct path
    vector<int> path;

    int curr = n;

    while(curr != -1)
    {
        path.push_back(curr);
        curr = parent[curr];
    }

    reverse(path.begin(),path.end());

    cout<<"Steps taken: ";

    for(int x : path)
    {
        cout<<x<<" ";
    }

    cout<<endl;

    return dp[n];
}

int main()
{
    int n;
    cin>>n;

    vector<int> cost(n);

    for(int i=0; i<n; i++)
        cin>>cost[i];

    mincostclmstr(n,cost);
}
