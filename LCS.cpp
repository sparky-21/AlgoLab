
#include<bits/stdc++.h>
using namespace std;

// 1. Recursion
int LCS(string x,string y,int i,int j)
{
    if(i==x.size() || j==y.size())
        return 0;

    if(x[i]==y[j])
        return 1+LCS(x,y,i+1,j+1);

    return max(LCS(x,y,i,j+1),
               LCS(x,y,i+1,j));
}

// 2. Memoization
int LCSmem(string x,string y,int i,int j,
           vector<vector<int>>&dp)
{
    if(i==x.size() || j==y.size())
        return 0;

    if(dp[i][j]!=-1)
        return dp[i][j];

    if(x[i]==y[j])
        return dp[i][j]=1+LCSmem(x,y,i+1,j+1,dp);

    return dp[i][j]=max(
        LCSmem(x,y,i,j+1,dp),
        LCSmem(x,y,i+1,j,dp)
    );
}

// 3. Tabulation
int LCStab(string x,string y,vector<vector<int>>&dp)
{
    int n=x.size();
    int m=y.size();

    dp.assign(n+1,vector<int>(m+1,0));

    for(int i=n-1;i>=0;i--)
    {
        for(int j=m-1;j>=0;j--)
        {
            if(x[i]==y[j])
                dp[i][j]=1+dp[i+1][j+1];

            else
                dp[i][j]=max(dp[i+1][j],dp[i][j+1]);
        }
    }

    return dp[0][0];
}

// 4. Print actual LCS
string printLCS(string x,string y,vector<vector<int>>&dp)
{
    int n=x.size();
    int m=y.size();

    string ans="";
    int i=0,j=0;

    while(i<n && j<m)
    {
        if(x[i]==y[j])
        {
            ans+=x[i];
            i++;
            j++;
        }

        else if(dp[i+1][j]>=dp[i][j+1])
        {
            i++;
        }

        else
        {
            j++;
        }
    }

    return ans;
}

int main()
{
    string x,y;
    cin>>x>>y;

    cout<<"Recursion: "<<LCS(x,y,0,0)<<endl;

    vector<vector<int>>dp1(
        x.size(),vector<int>(y.size(),-1)
    );

    cout<<"Memoization: "<<LCSmem(x,y,0,0,dp1)<<endl;

    vector<vector<int>>dp;

    int ans=LCStab(x,y,dp);

    cout<<"Tabulation: "<<ans<<endl;

    cout<<"Common Subsequence: "<<printLCS(x,y,dp)<<endl;

    return 0;
}
